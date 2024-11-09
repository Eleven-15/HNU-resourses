// http_request.h

#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <string>

// HTTP请求类
class HTTPRequest
{
public:
    explicit HTTPRequest(int clientSocket) : clientSocket(clientSocket) {}

    // 解析HTTP请求
    bool parseRequest();

    // 获取请求方法
    std::string getMethod() const { return method; }

    // 获取请求路径
    std::string getPath() const { return path; }

private:
    int clientSocket;   // 客户端套接字
    std::string method; // 请求方法
    std::string path;   // 请求路径
};

#endif // HTTP_REQUEST_H
