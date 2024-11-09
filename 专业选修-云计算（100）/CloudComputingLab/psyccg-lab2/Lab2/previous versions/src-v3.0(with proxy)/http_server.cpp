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
    // http://www.example.com:80
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
                // 此时给定的proxy没有给定端口号
                // 暂且认为默认80
                proxy_port_ = 80;
                proxy_name_ = proxy.substr(hostname_start);
                // std::cerr << "[server::proxy] Wrong proxy address" << std::endl;
                // return 1;
            }
        }
        else
        {
            std::cerr << "[server::proxy] Wrong proxy address" << std::endl;
            return 1;
        }
        std::cout << "parsing: proxy_name: " << proxy_name_ << std::endl;
        std::cout << "parsing: proxy_port: " << proxy_port_ << std::endl;
    }
    return 0;
}

// 创建Server
void HTTPServer::start()
{
    // 自检本地static基础页面是否可以获取
    if (construct_static("404", "HTTP/1.1") == "ERROR" || construct_static("501", "HTTP/1.1") == "ERROR" || construct_static("index", "HTTP/1.1") == "ERROR")
    {
        std::cerr << "Error: Failed to fetch basic local static resources \n";
        return;
    }

    // 创建套接字
    server_sock_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock_ == -1)
    {
        std::cerr << "Error: Failed to create socket\n";
        return;
    }

    // 设置地址重用选项(关键!:可以快速重用端口)
    int opt = 1;
    if (setsockopt(server_sock_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        std::cerr << "Setsockopt failed\n";
        return;
    }

    // 设置Keep - Alive选项
    int keepalive = 1;
    if (setsockopt(server_sock_, SOL_SOCKET, SO_KEEPALIVE, &keepalive, sizeof(int)) < 0)
    {
        std::cerr << "Set SO_KEEPALIVE failed\n";
        return;
    }

    // Bind socket to address
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip_.c_str());
    server_addr.sin_port = htons(port_);
    if (bind(server_sock_, (sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cerr << "Error: Failed to bind socket to address\n";
        close(server_sock_);
        return;
    }

    // Listen for incoming connections
    if (listen(server_sock_, 10) == -1)
    {
        std::cerr << "Error: Failed to listen for connections\n";
        close(server_sock_);
        return;
    }

    std::cout << "Server started at " << ip_ << ":" << port_ << std::endl;

    ThreadPool pool; // Use ThreadPool
    pool.init(threads_);

    // Accept incoming connections and handle them
    int count = 0;
    while (true)
    {
        sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_sock = accept(server_sock_, (sockaddr *)&client_addr, &client_addr_len);
        if (client_sock == -1)
        {
            std::cerr << "Error: Failed to accept incoming connection\n";
            continue;
        }

        std::cout << "New connection accepted [connection number" << count << "]\n";
        count++;

        // Handle the request in a new thread
        pool.enqueue(&HTTPServer::handle_request, this, client_sock); // Use ThreadPool
    }
}

// 关闭server
void HTTPServer::stop()
{
    // 关闭服务器套接字
    std::cout << "close HTTP Server" << std::endl;
    close(server_sock_);
}

// 处理连接请求
void HTTPServer::handle_request(int client_sock)
{
    // Receive request from client
    char buffer[4096];
    int bytes_received = recv(client_sock, buffer, sizeof(buffer), 0);
    if (bytes_received <= 0)
    {
        close(client_sock);
        return;
    }
    // 解析请求
    std::string request(buffer, bytes_received);
    std::string response = parse_request(request);
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
    // if (DEBUG)
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

    // 处理GET POST
    if (proxy_specified_)
    {
        // 开启代理
        std::string server_response = get_response_from_server(request);
        return server_response;
    }
    else
    {
        // 未开启代理
        try
        {
            if (method == "GET")
            {
                // std::string response = process_get(url, http_version);
                // return response;
                bool if_pipeline = true;
                std::string line;
                std::getline(iss, line);
                std::getline(iss, line); // 读取Host : 127.0.0.1 : 8080这一行，丢弃不做处理
                std::getline(iss, line); // User - Agent :
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
                    std::string response = "";
                    std::istringstream iss2(request); // 重新获取request完整副本
                    while (iss2 >> method >> url >> http_version)
                    {
                        // 将当前行添加到当前请求中
                        // std::cout << "view url" << std::endl;
                        // std::cout << url << std::endl;
                        response += process_get(url, http_version);
                        std::getline(iss2, line);
                        std::getline(iss2, line);
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
                    size_t delimiter_pos = header.find(':');
                    if (delimiter_pos != std::string::npos)
                    {
                        std::string key = header.substr(0, delimiter_pos);
                        std::string value = header.substr(delimiter_pos + 2); // +2 to skip ': ' after key
                        headers[key] = value;
                        if (key == "Content-Type")
                            received_content_type = value;
                    }
                    received_content = header;
                }
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
                std::cerr << "Error: " << std::endl;
                return "ERROR";
            }
        }
        catch (const std::runtime_error &error)
        {
            // 错误处理机制
            std::cerr << "Error: " << error.what() << std::endl;
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
        std::cerr << "failed to fetch file : " << static_path << std::endl;
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
        std::cerr << "failed to fetch file : " << data_path << std::endl;
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
        return "ERROR";
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
            std::cerr << "failed to fetch file : " << data_path << std::endl;
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
            std::cerr << "failed to fetch file : " << data_path << std::endl;
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
        // std::cout << id << std::endl
        //           << name << std::endl;

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
                    std::cerr << "Error: Failed to open not_found.json file" << std::endl;
                }
            }
        }
        else
        {
            ret = "ERROR";
            std::cerr << "Error: Failed to open data.json file" << std::endl;
        }
    }
    return ret;
}

// proxy使用
std::string HTTPServer::get_response_from_server(const std::string &request)
{
    // TODO 该部分尚未完成
    // Parse the request to get the host and port
    std::istringstream iss(request);
    std::string method, url, http_version;
    iss >> method >> url >> http_version;
    // if (true)
    //     std::cout
    //         << "method=" << method << std::endl
    //         << "url=" << url << std::endl
    //         << "http_version=" << http_version << std::endl;
    // std::cout << request << std::endl;

    std::string host_name;
    std::string host_port;

    // 创建套接字
    int host_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (host_sock == -1)
    {
        std::cerr << "[server::proxy] failed to create a socket" << std::endl;
        return "ERROR";
    }

    // 解析目标地址
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;          // 地址族
    server_addr.sin_port = htons(proxy_port_); // 端口号：HTTP 默认端口是 80

    struct hostent *server = gethostbyname(proxy_name_.c_str());
    std::cout << "Resolved host name: " << server->h_name << std::endl;
    if (server == nullptr)
    {
        std::cerr << "Error: Failed to resolve host.\n";
        return "ERROR";
    }
    memcpy(&server_addr.sin_addr.s_addr, server->h_addr, server->h_length);

    // 连接到服务器
    if (connect(host_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cerr << "Error: Failed to connect to server.\n";
        return "ERROR";
    }

    // 发送消息
    std::string message = "";
    message = message + method + " " + url + " " + http_version + "\r\n";
    message = message + "Host: " + server->h_name + "\r\n";
    message = message + "Connection: close\r\n\r\n";
    // std::cout << "send to server message:\n"
    //           << message << std::endl;

    if (send(host_sock, message.c_str(), message.size(), 0) == -1)
    {
        std::cerr << "Error: Failed to send message.\n";
        return "ERROR";
    }

    // 接收响应
    const int buffer_size = 4096;
    char buffer[buffer_size];
    std::string response;

    int bytes_received;
    while ((bytes_received = recv(host_sock, buffer, buffer_size - 1, 0)) > 0)
    {
        buffer[bytes_received] = '\0';
        response += buffer;
    }

    if (bytes_received == -1)
    {
        std::cerr << "Error: Failed to receive response.\n";
        return "ERROR";
    }

    // 打印响应
    // std::cout << "Response:\n"
    //           << response << std::endl;

    // 关闭套接字
    close(host_sock);

    return response;
}
