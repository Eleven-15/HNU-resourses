// http_request.cpp

#include "http_request.h"
#include "utils.h"
#include <iostream>

using namespace std;

bool HTTPRequest::parseRequest()
{
    // 从客户端套接字读取HTTP请求
    string request = recvData(clientSocket);
    if (request.empty())
    {
        cerr << "Failed to receive HTTP request." << endl;
        return false;
    }

    // 解析HTTP请求行
    size_t pos = request.find("\r\n");
    if (pos == string::npos)
    {
        cerr << "Failed to parse HTTP request line." << endl;
        return false;
    }

    string requestLine = request.substr(0, pos);
    vector<string> tokens = splitString(requestLine, ' ');
    if (tokens.size() != 3)
    {
        cerr << "Invalid HTTP request line." << endl;
        return false;
    }

    method = tokens[0];
    path = tokens[1];

    return true;
}
