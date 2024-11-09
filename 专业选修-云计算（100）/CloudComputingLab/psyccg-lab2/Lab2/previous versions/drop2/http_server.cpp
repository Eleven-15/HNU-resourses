// http_server.cpp

#include "http_server.h"
#include "http_request.h"
#include "http_response.h"
#include "thread_pool.h"
#include "utils.h"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

void HTTPServer::start()
{
    // 初始化服务器套接字
    int serverSocket = initServerSocket();
    if (serverSocket == -1)
    {
        std::cerr << "Failed to initialize server socket." << std::endl;
        return;
    }

    // 创建线程池并启动线程
    createThreadPool();

    // 监听客户端连接并处理请求
    struct sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    while (true)
    {
        int clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket == -1)
        {
            std::cerr << "Failed to accept client connection." << std::endl;
            continue;
        }
        // 处理客户端请求
        handleClientRequest(clientSocket);
    }

    // 关闭服务器套接字
    close(serverSocket);
}

int HTTPServer::initServerSocket() const
{
    // 创建服务器套接字
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        std::cerr << "Failed to create server socket." << std::endl;
        return -1;
    }

    // 设置服务器地址和端口
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
    serverAddr.sin_port = htons(port);

    // 绑定服务器套接字到地址和端口
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "Failed to bind server socket to address and port." << std::endl;
        close(serverSocket);
        return -1;
    }

    // 监听连接请求
    if (listen(serverSocket, 10) == -1)
    {
        std::cerr << "Failed to listen for connections." << std::endl;
        close(serverSocket);
        return -1;
    }

    return serverSocket;
}

void HTTPServer::handleClientRequest(int clientSocket) const
{
    // 解析HTTP请求
    HTTPRequest request(clientSocket);
    if (!request.parseRequest())
    {
        std::cerr << "Failed to parse HTTP request." << std::endl;
        close(clientSocket);
        return;
    }

    // 生成HTTP响应
    HTTPResponse response(request, proxyMode, proxyAddr);
    std::string httpResponse = response.generateResponse();

    // 发送HTTP响应
    ssize_t bytesSent = send(clientSocket, httpResponse.c_str(), httpResponse.size(), 0);
    if (bytesSent == -1)
    {
        std::cerr << "Failed to send HTTP response." << std::endl;
    }

    // 关闭客户端套接字
    close(clientSocket);
}

void HTTPServer::createThreadPool() const
{
    // 创建线程池
    ThreadPool threadPool(numThreads);

    // 启动线程池
    threadPool.enqueue([]
                       {
        while (true) {
            // 处理任务...
        } });
}
