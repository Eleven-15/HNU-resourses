// http_response.cpp

#include "http_response.h"
#include "utils.h"
#include <iostream>

using namespace std;

string HTTPResponse::generateResponse()
{
    if (request.getMethod() == "GET")
    {
        return handleGET();
    }
    else if (request.getMethod() == "POST")
    {
        return handlePOST();
    }
    else
    {
        // 其他请求方法暂不支持，返回501 Not Implemented
        return "HTTP/1.1 501 Not Implemented\r\n\r\n";
    }
}

string HTTPResponse::handleGET()
{
    // 处理GET请求...
}

string HTTPResponse::handlePOST()
{
    // 处理POST请求...
}
