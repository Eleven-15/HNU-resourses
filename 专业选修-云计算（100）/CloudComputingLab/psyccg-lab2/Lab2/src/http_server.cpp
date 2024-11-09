// http_server.cpp

#include "http_server.h"
#include "json.hpp" // json
#include "thread_pool.h"
#include <arpa/inet.h>
#include <cstring>
#include <fstream> // ostringstream
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <regex> // 正则表达式
#include <sstream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

using json = nlohmann::json;

// 初始化server
bool HTTPServer::init(const std::string &ip, int port, int threads, const std::string &proxy, bool proxy_specified)
{
    ip_ = ip;
    port_ = port;
    threads_ = threads;
    proxy_ = proxy;
    proxy_specified_ = proxy_specified;

    // 解析proxy，得到proxy name & port
    // e.g. http://www.example.com:80
    if (proxy_specified)
    {
        size_t protocol_pos = proxy.find("://");
        if (protocol_pos != std::string::npos)
        {
            size_t hostname_start = protocol_pos + 3; // "://" 的长度为3
            size_t hostname_end = proxy.find(":", hostname_start);
            if (hostname_end != std::string::npos)
            {
                proxy_name_ = proxy.substr(hostname_start, hostname_end - hostname_start);
                // 查找端口号
                std::string proxy_port_str = proxy.substr(hostname_end + 1);
                proxy_port_ = stoi(proxy_port_str);
            }
            else
            {
                // 此时给定的proxy没有给定端口号，此时末尾不会出现冒号，故直接截取到结尾
                // 暂且认为默认80
                proxy_port_ = 80;
                proxy_name_ = proxy.substr(hostname_start);
                // std::cerr << "[server::proxy] Wrong proxy address" << std::endl;
                // return 1;
            }
        }
        else
        {
            std::cerr << "[ERROR] HTTPServer::init>> Wrong proxy address" << std::endl;
            return 1;
        }
        std::cout << "parsing proxy as below" << std::endl;
        std::cout << "parsing: proxy_name: " << proxy_name_ << std::endl;
        std::cout << "parsing: proxy_port: " << proxy_port_ << std::endl;
        std::cout << "-------------------------------------------" << std::endl;
    }
    return 0;
}

// 创建Server
void HTTPServer::start()
{
    // 自检本地static基础页面是否可以获取
    // 基础页面后面很常用，必须先检查。
    if (construct_static("404", "HTTP/1.1") == "ERROR" || construct_static("501", "HTTP/1.1") == "ERROR" || construct_static("index", "HTTP/1.1") == "ERROR")
    {
        std::cerr << "[Error] HTTPServer::start >> Failed to fetch basic local static resources \n";
        return;
    }

    // 创建套接字
    server_sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock_ == -1)
    {
        std::cerr << "[Error] HTTPServer::start >> Failed to create socket\n";
        return;
    }

    // 设置地址重用选项(关键!:可以快速重用端口)
    // 若没有此段，关闭server并立刻重启会导致端口被占用，无法通过测评
    int opt = 1;
    if (setsockopt(server_sock_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        std::cerr << "[ERROR] HTTPServer::start >> Failed to set sockopt\n";
        return;
    }

    // 设置Keep-Alive选项
    int keepalive = 1;
    if (setsockopt(server_sock_, SOL_SOCKET, SO_KEEPALIVE, &keepalive, sizeof(int)) < 0)
    {
        std::cerr << "[ERROR] HTTPServer::start >> Failed to set SO_KEEPALIVE\n";
        return;
    }

    // 绑定socket到地址
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip_.c_str());
    server_addr.sin_port = htons(port_);
    if (bind(server_sock_, (sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cerr << "[ERROR] HTTPServer::start >> Failed to bind socket to address\n";
        close(server_sock_);
        return;
    }

    // 设置监听
    if (listen(server_sock_, 50) == -1)
    {
        std::cerr << "[ERROR] HTTPServer::start >> Failed to listen for connections\n";
        close(server_sock_);
        return;
    }

    std::cout << "HTTPServer started at " << ip_ << ":" << port_ << std::endl;

    // 实例化线程池并初始化线程池
    ThreadPool pool; // Use ThreadPool
    pool.init(threads_);

    // 主进程监听在localhost，等待连接并分配任务给线程
    // 启用count可以看到当前处理的任务的编号
    // int count = 0;
    while (true)
    {
        sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_sock = accept(server_sock_, (sockaddr *)&client_addr, &client_addr_len);
        if (client_sock == -1)
        {
            std::cerr << "[ERROR] HTTPServer::start >>  Failed to accept incoming connection\n";
            continue;
        }

        // std::cout << "New connection accepted [connection number" << count << "]\n";
        // count++;

        // Handle the request in a new thread
        pool.enqueue(&HTTPServer::handle_request, this, client_sock); // Use ThreadPool
    }

    return; // 应该永远不会到这一行的
}

// 关闭server
bool HTTPServer::stop()
{
    // 关闭服务器套接字
    std::cout << "close HTTP Server" << std::endl;
    close(server_sock_);
    return 0;
}

// 处理连接请求
void HTTPServer::handle_request(int client_sock)
{
    // 设置接受与缓冲区
    char buffer[buffer_size];
    int bytes_received = recv(client_sock, buffer, sizeof(buffer), 0);
    if (bytes_received <= 0)
    {
        close(client_sock);
        return;
    }
    // 解析请求
    std::string request(buffer, bytes_received);
    std::string response = parse_request(request);
    // (这一个处理是自己加的) 其余所有错误统一归结为501内部错误，向client返回
    if (response == "ERROR")
    {
        response = "";
        response += "HTTP/1.1 500 Internal Server Error\r\n";
        response += "Content-Type: text/plain\r\n\r\n";
        response += "Internal Server Error : An unexpected error occurred while processing your request.Please try again later.\r\n";
    }

    // 这段可以看到进入与流出handle_request函数时的报文
    // std::cout << std::endl
    //           << std::endl;
    // std::cout << ">>>>>>> process procedure in local server <<<<<<<" << std::endl;
    // std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>START " << std::endl;
    // std::cout << ">>>>>>>>>>>>>>>[request content] " << std::endl
    //           << request << std::endl;
    // std::cout << ">>>>>>>>>>>>>>>[response content] " << std::endl
    //           << response << std::endl;
    // std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>END " << std::endl;
    // std::cout << std::endl
    //           << std::endl;

    // 发送返回报文
    send_response(client_sock, response);
    // 关闭连接
    close(client_sock);
}

// 解析报文并返回结果
std::string HTTPServer::parse_request(const std::string &request)
{
    // 从报文中分离method,url,http_version,data
    std::istringstream iss(request);
    std::string method, url, http_version;
    std::string received_content;      // POST专属:: content是data部分
    std::string received_content_type; // POST专属:: content的类型
    iss >> method >> url >> http_version;

    // 查看解析出报文的第一行
    //     std::cout
    //         << "method=" << method << std::endl
    //         << "url=" << url << std::endl
    //         << "http_version=" << http_version << std::endl;
    // std::cout << request << std::endl;

    // GET 标准格式
    // GET / test / test.html HTTP / 1.1
    // Host : 127.0.0.1 : 8080
    // User - Agent : curl / 7.68.0
    // Accept : */*

    // GET pipeline 标准格式
    // GET /index.html HTTP / 1.1
    // Host : 127.0.0.1 : 8080
    //
    // GET /404.html HTTP / 1.1
    // Host : 127.0.0.1 : 8080
    //
    // GET /501.html HTTP / 1.1
    // Host : 127.0.0.1 : 8080
    //

    // POST标准格式
    // POST / api / upload HTTP / 1.1
    // Host : 127.0.0.1 : 8080
    // User - Agent : curl / 7.68.0
    // Accept : */*
    // Content-Type: application/json
    // Content-Length: 21
    //
    // {"id":1,"name":"Foo"}

    // 对于其它请求，只需要返回501.html
    if (method != "GET" && method != "POST")
    {
        std::string response = construct_static("501", http_version);
        return response;
    }

    // 处理GET & POST
    if (proxy_specified_)
    {
        // 开启代理
        std::string server_response = get_response_from_server(request);
        if (server_response == "ERROR")
        {
            std::cerr << "[Error] HTTPServer::parse_request >> Failed to get correct proxy ans. Wrong in proxy." << std::endl;
        }
        return server_response;
    }
    else
    {
        // 未开启代理
        try
        {
            if (method == "GET")
            {
                // 若不需要pipeline，则只需下面这两行即可完成任务
                // std::string response = process_get(url, http_version);
                // return response;

                // 判断是否是pipeline请求
                // pipeline：一般POST无pipeline，这里就只有GET有pipeline
                // 逻辑是上面展示的pipeline-GET请求与普通GET请求的区别
                // 查看是否有User-Agent行，若有则为普通GET请求，否则为pipeline请求
                bool if_pipeline = true; // 该请求是否是pipeline请求
                std::string line;
                // 从头开始读取request行，试图确定request是否pipeline
                std::getline(iss, line); // getline和流处理>>不是同一个指针，故这里还是要重新读第一行GET /index.html HTTP / 1.1，丢弃不做处理
                std::getline(iss, line); // 读取Host : 127.0.0.1 : 8080这一行，丢弃不做处理
                std::getline(iss, line); // 读取User - Agent :这一行，看有没有、
                // 查看标准判断的标准是不是我们的判断逻辑
                // std::cout << "view judge standard" << std::endl;
                // std::cout << line << std::endl;
                if (line.length() >= 11 && line.substr(0, 11) == "User-Agent:")
                    if_pipeline = false;

                if (if_pipeline == false)
                {
                    // 处理非流水线情况
                    // std::cout << ">>process non-pipeline" << std::endl;
                    std::string response = process_get(url, http_version);
                    return response;
                }
                else
                {
                    // 处理流水线情况
                    // std::cout << ">>process pipeline" << std::endl;
                    // 逻辑，逐个根据单个请求调用get方法得到答案，写回，最后打包一起返回
                    std::string response = "";
                    std::istringstream iss2(request); // 重新获取request完整副本
                    while (iss2 >> method >> url >> http_version)
                    {
                        // std::cout << "view url" << std::endl;
                        // std::cout << url << std::endl;

                        // 将当前请求的结果添加到结果中
                        response += process_get(url, http_version);
                        std::getline(iss2, line); // 读取Host : 127.0.0.1 : 8080这一行，不做处理
                        std::getline(iss2, line); // 读取空行，不做处理
                    }
                    // std::cout << "view response" << std::endl;
                    // std::cout << response << std::endl;
                    return response;
                }
            }
            else if (method == "POST")
            {
                // POST另外需要content和content_type
                // 从报文中分离header中的信息
                std::unordered_map<std::string, std::string> headers;
                std::string header;
                while (std::getline(iss, header) && header != "\r\n")
                {
                    // 逻辑：使用冒号分割，得到key和value
                    size_t delimiter_pos = header.find(':');
                    if (delimiter_pos != std::string::npos)
                    {
                        std::string key = header.substr(0, delimiter_pos);
                        std::string value = header.substr(delimiter_pos + 2); // +2 to skip ': ' after key
                        headers[key] = value;
                        if (key == "Content-Type")
                            received_content_type = value;
                    }
                    received_content = header; // post方法的data就在最后一行，这样覆盖最终得到的就是data
                }
                // 查看request的每一行
                // for (const auto &header_pair : headers)
                // {
                //     std::cout << header_pair.first << ": " << header_pair.second << std::endl;
                // }
                // std::cout << received_content << std::endl;
                // std::cout << received_content_type << std::endl;
                std::string response = process_post(url, http_version, received_content);
                return response;
            }
            else
            {
                // 该段不会被访问
                std::cerr << "[Error] HTTPServer::parse_request >> Here is not to visit " << std::endl;
                return "ERROR";
            }
        }
        catch (const std::runtime_error &error)
        {
            // 错误处理机制
            std::cerr << "[Error] HTTPServer::parse_request >> runtime_error!\n"
                      << error.what() << std::endl;
            return "ERROR";
        }
    }
}

// 构建返回报文
std::string HTTPServer::generate_message(std::string version, std::string status, std::string content_type, std ::string body)
{
    // e.g.
    // HTTP/1.1 200 OK
    // Content-Type: text/html
    // Content-Length: 76
    //
    // < html > <head><title> Simple Response</ title></ head><body><h1> Hello,World !</ h1></ body></ html>

    std::string ret = "";
    ret = ret + version + " " + status + "\r\n";
    ret = ret + "Content-Type: " + content_type + "\r\n";
    ret = ret + "Content-Length: " + std::to_string(body.size()) + "\r\n";
    ret = ret + "\r\n";
    ret = ret + body;
    return ret;
}

// 发送返回报文
void HTTPServer::send_response(int client_sock, const std::string &response)
{
    send(client_sock, response.c_str(), response.size(), 0);
}

// 获取静态资源
std::string HTTPServer::get_static(std::string url)
{
    std::string ret;
    std::string static_path = "../static";
    static_path += url;
    std::ifstream file(static_path);
    if (file)
    {
        std::ostringstream oss;
        oss << file.rdbuf();
        ret = oss.str();
    }
    else
    {
        ret = "ERROR";
        std::cerr << "[Error] HTTPServer::get_static >> Failed to fetch file : " << static_path << std::endl;
    }
    return ret;
}

// 获取data文件夹内的资源
std::string HTTPServer::get_data(std::string url)
{
    std::string ret;
    std::string data_path = "../data";
    data_path += url;
    std::ifstream file(data_path);
    if (file)
    {
        std::ostringstream oss;
        oss << file.rdbuf();
        ret = oss.str();
    }
    else
    {
        ret = "ERROR";
        std::cerr << "[Error] HTTPServer::get_data >> Failed to fetch file : " << data_path << std::endl;
    }
    return ret;
}

// 获取404，501，index页面
std::string HTTPServer::construct_static(std::string type, std::string http_version)
{
    std::string status = "";
    std::string body = "";
    if (type == "404")
    {
        status = "404 Not Found";
        body = get_static("/404.html");
    }
    else if (type == "501")
    {
        status = "501 Not Implemented";
        body = get_static("/501.html");
    }
    else if (type == "index")
    {
        status = "200 OK";
        body = get_static("/index.html");
    }
    std::string content_type = "text/html";
    std::string ret = generate_message(http_version, status, content_type, body);
    if (body == "ERROR")
        return "ERROR"; // server运行前检验过，这个情况应该不会发生
    return ret;
}

// 处理get请求
std::string HTTPServer::process_get(std::string url, std::string http_version)
{
    std::string response = "";     // 返回报文
    std::string status = "";       // 状态码
    std::string content_type = ""; // 类型
    std::string body = "";         // 文本

    if (url.length() >= 4 && url.substr(0, 4) == "/api")
    {
        url = url.substr(4);
        // 2 access web services for getting data
        // basic
        // | path | get data | status code | content type |
        // | -- - | -- - | -- - | -- - |
        // | / api / check | strings in `data.txt` | 200 | text / plain |
        // | any other error paths | / {static files} / 404.html | 404 | text / html |
        if (url.length() >= 6 && url.substr(0, 6) == "/check")
        {
            url = url.substr(6);
            status = "200 OK";
            content_type = "text/plain";
            body = data_query("check", "", status);
            response = generate_message(http_version, status, content_type, body);
            // if (response == "ERROR")
            // {
            //     // 未找到对应的txt文件，返回404
            //     std::cerr << "ERROR: failed to fetch data.txt" << std::endl; // 这是一个本地错误
            //     response = construct_static("404", http_version);
            //     return response;
            // }
        }
        // advanced
        // | path | get data | status code | content type |
        // | -- - | -- - | -- - | -- - |
        // | / api / list | all objects in `data.json` | 200 | application / json |
        // | / api / search? [id =`value1`&name =`value2`] | all objects that match<br /> `*.id == value1 &&*.name == value2` <br /> in `/ data / data.json` | 200 | application / json |
        // | / api / search? [id =`value1`&name =`value2`] | if no object matches,return all objects<br /> in `/ data / not_found.json` | 404 | application / json |
        // | any other error paths | / {static files} / 404.html | 404 | text / html |
        // > The query string format is a regular expression: `id = [0 - 9] + &name = [a - zA - Z0 - 9] +`.
        // > If you do not want to parse json file,you could store the data in memory instead of reading file every time.
        else if (url.length() >= 5 && url.substr(0, 5) == "/list")
        {
            url = url.substr(5);
            status = "200 OK";
            content_type = "application/json";
            body = data_query("list", "", status);
            response = generate_message(http_version, status, content_type, body);
        }
        else if (url.length() >= 7 && url.substr(0, 7) == "/search")
        {
            url = url.substr(8);
            status = "200 OK";
            content_type = "application/json";
            body = data_query("search", url, status);
            response = generate_message(http_version, status, content_type, body);
        }
        else
        {
            // 其余错误路径
            response = construct_static("404", http_version);
        }
    }
    else
    {
        // 1 access static files
        // target( basic + advanced )
        // | path | files in local fs | status code | content type |
        // | --- | --- | --- | --- |
        // | /, /index.html | /`{static dir}`/index.html | 200 | text/html |
        // | /404.html | /`{static dir}`/404.html | 404 | text/html |
        // | /501.html | /`{static dir}`/501.html | 501 | text/html |
        // | [/\*]/\*.html | /`{static dir}`[/\*]/\*.html | 200 | text/html |
        // | [/\*]/\*.js | /`{static dir}`[/\*]/\*.js | 200 | text/javascript |
        // | [/\*]/\*.css | /`{static dir}`[/\*]/\*.css | 200 | text/css |
        // | [/\*]/\*.json | /`{static dir}`[/\*]/\*.json | 200 | application/json |
        // | any other error paths | /`{static dir}`/404.html | 404 | text/html |
        if (url == "/")
            url = "/index.html";

        // 解析url
        if (url == "/index.html" || url == "/404.html" || url == "/501.html")
        {
            // 处理基础html格式
            if (url == "/404.html")
                response = construct_static("404", http_version);
            else if (url == "/501.html")
                response = construct_static("501", http_version);
            else if (url == "/index.html")
                response = construct_static("index", http_version);
            else
                response = "ERROR";
        }
        else
        {
            // 处理其余html
            if ((url.length() >= 5) && url.substr(url.length() - 5) == ".html")
            {
                content_type = "text/html";
                body = get_static(url);
            }
            else if ((url.length() >= 5) && url.substr(url.length() - 5) == ".json")
            {
                content_type = "application/json";
                body = get_static(url);
            }
            else if ((url.length() >= 4) && url.substr(url.length() - 4) == ".css")
            {
                content_type = "text/css";
                body = get_static(url);
            }
            else if ((url.length() >= 3) && url.substr(url.length() - 3) == ".js")
            {
                content_type = "text/javascript";
                body = get_static(url);
            }
            else
            {
                // 类型不正确
                body = "ERROR";
            }

            if (body != "ERROR")
            {
                status = "200 OK";
                response = generate_message(http_version, status, content_type, body);
            }
            else
            {
                // 未找到该路径
                response = construct_static("404", http_version);
            }
        }
    }
    return response;
}

// 处理post请求
std::string HTTPServer::process_post(std::string url, std::string http_version, std::string received_content)
{
    std::string response = "";     // 返回报文
    std::string status = "";       // 状态码
    std::string content_type = ""; // 类型
    std::string body = "";         // 文本

    // basic
    if (url.length() >= 9 && url.substr(0, 9) == "/api/echo")
    {
        // | path | content | status code | content type |
        // | -- - | -- - | -- - | -- - |
        // | / api / echo | echo the data received | 200 | application / x - www - form - urlencoded |
        // | / api / echo | if the data format is error,send strings<br /> in `/ data / error.txt` | 404 | text / plain |
        // | any other error paths | / {static files} / 404.html | 404 | text / html |

        // 检查数据格式是否正确
        // id=[0-9]+&name=[a-zA-Z0-9]+
        std::regex pattern("id\\=[0-9]+\\&name\\=[a-zA-Z0-9]+");
        if (!std::regex_match(received_content, pattern))
        {
            // 数据格式错误，发送error消息
            body = get_data("/error.txt");
            status = "404 Not Found";
            content_type = "application/x-www-form-urlencoded";
            response = generate_message(http_version, status, content_type, body);
        }
        else
        {
            // 数据格式正确，返回上传数据
            body = received_content;
            status = "200 OK";
            content_type = "application/x-www-form-urlencoded";
            response = generate_message(http_version, status, content_type, body);
        }
    }
    // advanced
    else if (url.length() >= 11 && url.substr(0, 11) == "/api/upload")
    {
        // | path | content | status code | content type |
        // | -- - | -- - | -- - | -- - |
        // | / api / upload | echo the data received | 200 | application / json |
        // | / api / upload | if the data format is error,send strings<br /> in `/ data / error.json` | 404 | application / json |
        // | any other error paths | / {static files} / 404.html | 404 | text / html |
        std::regex pattern("\\{\"id\":([0-9]+),\"name\":\"([a-zA-Z0-9]+)\"\\}");
        if (!std::regex_match(received_content, pattern))
        {
            // 数据格式错误，发送error消息
            body = get_data("/error.json");
            status = "404 Not Found";
            content_type = "application/json";
            response = generate_message(http_version, status, content_type, body);
        }
        else
        {
            // 数据格式正确，返回上传数据
            body = received_content;
            status = "200 OK";
            content_type = "application/json";
            response = generate_message(http_version, status, content_type, body);
        }
    }
    else
    {
        // 其余错误路径
        response = construct_static("404", http_version);
    }
    return response;
}

// 处理get-advanced中的data查询问题
std::string HTTPServer::data_query(std::string method, std::string data, std::string &status)
{
    std::string data_path = "../data";
    std::string ret;
    if (method == "check")
    {
        data_path += "/data.txt";
        std::ifstream file(data_path);
        if (file)
        {
            std::ostringstream oss;
            oss << file.rdbuf();
            ret = oss.str();
        }
        else
        {
            ret = "ERROR";
            std::cerr << "[Error] HTTPServer::data_query >> Failed to fetch file : " << data_path << std::endl;
        }
    }
    else if (method == "list")
    {
        data_path += "/data.json";
        std::ifstream file(data_path);
        if (file)
        {
            std::ostringstream oss;
            oss << file.rdbuf();
            ret = oss.str();
        }
        else
        {
            ret = "ERROR";
            std::cerr << "[Error] HTTPServer::data_query >> Failed to fetch file : " << data_path << std::endl;
        }
    }
    else if (method == "search")
    {
        std::string visit_data_path = data_path + "/data.json";

        // 分离id/name
        std::istringstream iss(data);
        std::string key_value_pair;
        std::string id_str, name;
        int id;
        while (std::getline(iss, key_value_pair, '&'))
        {
            std::istringstream iss_pair(key_value_pair);
            std::string key, value;

            if (std::getline(std::getline(iss_pair, key, '='), value, '='))
            {
                if (key == "id")
                {
                    id_str = value;
                }
                else if (key == "name")
                {
                    name = value;
                }
            }
        }
        id = stoi(id_str);
        // std::cout << id << std::endl << name << std::endl;

        std::ifstream file(visit_data_path);
        if (file.is_open())
        {
            json jsonData;
            file >> jsonData;
            file.close();

            // 迭代JSON数组并筛选匹配条件的对象
            json matchedObjects;
            for (const auto &obj : jsonData)
            {
                if (obj["id"] == id && obj["name"] == name)
                {
                    matchedObjects.push_back(obj);
                }
            }

            if (!matchedObjects.empty())
            {
                // 返回匹配的JSON对象
                ret = matchedObjects.dump(); // 输出JSON对象，无缩进
            }
            else
            {
                // 如果没有匹配的对象，返回另一个 JSON 文件中的所有对象
                std::string notFoundJsonFilePath = data_path + "/not_found.json";
                std::ifstream notFoundFile(notFoundJsonFilePath);
                if (notFoundFile.is_open())
                {
                    json notFoundData;
                    notFoundFile >> notFoundData;
                    notFoundFile.close();
                    ret = notFoundData.dump(); // 输出JSON对象，缩进为4个空格
                    status = "404 Not Found";  // 返回 HTTP 状态码 404, 这里使用传实参的方法来更改，破坏了封装性，但暂时没更好的方法
                }
                else
                {
                    ret = "ERROR";
                    std::cerr << "[Error] HTTPServer::data_query >> Failed to open not_found.json file" << std::endl;
                }
            }
        }
        else
        {
            ret = "ERROR";
            std::cerr << "[Error] HTTPServer::data_query >> Failed to open data.json file" << std::endl;
        }
    }
    return ret;
}

// proxy使用
std::string HTTPServer::get_response_from_server(const std::string &request)
{
    // 从报文中分离method,url,http_version,data
    std::istringstream iss(request);
    std::string method, url, http_version;
    iss >> method >> url >> http_version;

    // 查看解析出报文的第一行
    // std::cout
    //     << "method=" << method << std::endl
    //     << "url=" << url << std::endl
    //     << "http_version=" << http_version << std::endl;
    // std::cout << request << std::endl;

    std::string host_name; // 服务器名 e.g. www.example.com
    std::string host_port; // 端口 一般是80

    // 创建套接字
    int host_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (host_sock == -1)
    {
        std::cerr << "[ERROR] HTTPServer::proxy >> Failed to create a socket" << std::endl;
        return "ERROR";
    }

    // 解析目标地址
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;                                   // 地址族
    server_addr.sin_port = htons(proxy_port_);                          // 端口号：HTTP 默认端口是 80
    struct hostent *server = gethostbyname(proxy_name_.c_str());        // 解析并获取目标地址
    std::cout << "Resolved host name: " << server->h_name << std::endl; // 向终端输出
    if (server == nullptr)
    {
        // 未成功解析目标地址
        std::cerr << "[ERROR] HTTPServer::proxy >> Failed to resolve host.\n";
        return "ERROR";
    }
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length); // 将构建结果放入server_addr内

    // 连接到目标服务器
    if (connect(host_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cerr << "[ERROR] HTTPServer::proxy >> Failed to connect to server.\n";
        return "ERROR";
    }

    // 构建报文
    std::string message = "";
    message = message + method + " " + url + " " + http_version + "\r\n";
    message = message + "Host: " + server->h_name + "\r\n";
    message = message + "Connection: close\r\n\r\n"; // 该句一定要加，否则默认长连接，则会阻塞在这里
    // std::cout << "send to server message:\n" << message << std::endl;

    // 发送报文
    if (send(host_sock, message.c_str(), message.size(), 0) == -1)
    {
        std::cerr << "[ERROR] HTTPServer::proxy >> Failed to send message.\n";
        return "ERROR";
    }

    // 设置接受与缓冲区
    char buffer[buffer_size];
    std::string response;
    // 接受响应
    int bytes_received;
    while ((bytes_received = recv(host_sock, buffer, buffer_size - 1, 0)) > 0)
    {
        buffer[bytes_received] = '\0';
        response += buffer;
    }
    if (bytes_received == -1)
    {
        std::cerr << "[ERROR] HTTPServer::proxy >> Failed to receive response.\n";
        return "ERROR";
    }

    // 向终端打印响应
    // std::cout << "Response:\n" << response << std::endl;

    // 关闭套接字
    close(host_sock);

    // 返回结果，正常情况是答案，若为ERROR则出错
    return response;
}
