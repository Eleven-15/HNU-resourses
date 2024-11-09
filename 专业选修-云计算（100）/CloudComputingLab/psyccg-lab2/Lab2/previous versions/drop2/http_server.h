// http_server.h

#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <string>

// HTTP服务器类
class HTTPServer
{
public:
    HTTPServer(const std::string &ip, int port, int numThreads, bool proxyMode, const std::string &proxyAddr)
        : ip(ip), port(port), numThreads(numThreads), proxyMode(proxyMode), proxyAddr(proxyAddr) {}

    // 启动HTTP服务器
    void start();

private:
    std::string ip;        // IP地址
    int port;              // 端口号
    int numThreads;        // 线程数
    bool proxyMode;        // 是否为代理模式
    std::string proxyAddr; // 代理地址

    // 初始化服务器套接字
    int initServerSocket() const;

    // 处理客户端请求
    void handleClientRequest(int clientSocket) const;

    // 创建线程池并启动线程
    void createThreadPool() const;
};

#endif // HTTP_SERVER_H
