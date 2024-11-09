#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "thread_pool.h"
#include <string>

class HTTPServer
{
public:
    // 默认构造函数
    HTTPServer(){};
    // 初始化server
    bool init(const std::string &ip, int port, int threads, const std::string &proxy, bool proxy_specified);
    // 创建Server
    void start();
    // 关闭server
    bool stop();

private:
    const int buffer_size = 4096;
    std::string ip_;
    int port_;
    int threads_;
    int server_sock_;

    // proxy
    bool proxy_specified_;
    std::string proxy_;
    std::string proxy_name_;
    int proxy_port_;

    // 解析报文并返回结果
    void handle_request(int client_sock);
    std::string parse_request(const std::string &request);
    // 构建返回报文
    std::string generate_message(std::string version, std::string status, std::string content_type, std ::string body);
    // 发送返回报文
    void send_response(int client_sock, const std::string &response);

    // 获取本地资源
    // 获取静态资源
    std::string get_static(std::string url);
    // 获取data文件夹内的资源
    std::string get_data(std::string url);
    // 获取404，501，index页面
    std::string construct_static(std::string type, std::string http_version);

    // 处理请求
    // 处理get请求
    std::string process_get(std::string url, std::string http_version);
    // 处理post请求
    std::string process_post(std::string url, std::string http_version, std::string received_content);
    // 处理get-advanced中的data查询问题
    std::string data_query(std::string method, std::string data, std::string &status);

    // proxy相关：解析请求，连接目标服务器并返回结果，返回结果
    std::string get_response_from_server(const std::string &request);
};

#endif
