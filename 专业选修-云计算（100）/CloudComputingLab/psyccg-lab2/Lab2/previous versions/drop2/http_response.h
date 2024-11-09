// http_response.h

#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include "http_request.h"
#include <string>

// HTTP响应类
class HTTPResponse
{
public:
    HTTPResponse(const HTTPRequest &request, bool proxyMode, const std::string &proxyAddr)
        : request(request), proxyMode(proxyMode), proxyAddr(proxyAddr) {}

    // 生成HTTP响应
    std::string generateResponse();

private:
    const HTTPRequest &request; // HTTP请求对象
    bool proxyMode;             // 是否为代理模式
    std::string proxyAddr;      // 代理地址

    // 处理HTTP GET请求
    std::string handleGET();

    // 处理HTTP POST请求
    std::string handlePOST();
};

#endif // HTTP_RESPONSE_H
