#include "http_server.h"
#include <cstdlib> // 包含 std::atoi 和 std::atof 函数
#include <getopt.h>
#include <iostream>
#include <signal.h> // 关停服务器
#include <string>

#define DEBUG 1
//  ./http_server --ip 127.0.0.1 --port 8080 --threads 4 --proxy http://www.example.com:80

// 由于加入了sigint信号以及处理例程，server必须定义在全局
HTTPServer server;

// 在sigint信号发生时，主动关闭服务器
// （事实上并未解决快速再次使用时端口占用问题，该问题由端口复用解决）
void signal_handler(int signal)
{
    if (signal == SIGINT)
    {
        std::cout << "Received SIGINT. Shutting down server..." << std::endl;
        if (server.stop() != 0)
        {
            std::cerr << "[ERROR] signal_handler >> server stop error" << std::endl;
        };
        exit(0);
    }
}

int main(int argc, char **argv)
{
    // 定义参数列表并解析参数
    const char *short_opts = "i:p:t:";
    const option long_opts[] = {
        {"ip", required_argument, nullptr, 'i'},
        {"port", required_argument, nullptr, 'p'},
        {"threads", required_argument, nullptr, 't'},
        {"proxy", required_argument, nullptr, 'x'},
        {nullptr, 0, nullptr, 0}};

    int opt;
    const char *ip = nullptr;
    const char *port = nullptr;
    const char *threads = nullptr;
    const char *proxy = nullptr;
    bool proxy_specified = false;

    while ((opt = getopt_long(argc, argv, short_opts, long_opts, nullptr)) != -1)
    {
        switch (opt)
        {
        case 'i':
            ip = optarg;
            break;
        case 'p':
            port = optarg;
            break;
        case 't':
            threads = optarg;
            break;
        case 'x':
            proxy = optarg;
            proxy_specified = true;
            break;
        default:
            std::cerr << "[ERROR] Usage: " << argv[0] << " -i <ip> -p <port> -t <threads> --proxy <proxy>" << std::endl;
            return 1;
        }
    }

    // 检查是否提供了必需的参数
    if (ip == nullptr || port == nullptr || threads == nullptr)
    {
        std::cerr << "[Error] main >> Missing required arguments." << std::endl;
        std::cerr << "Usage: " << argv[0] << " -i <ip> -p <port> -t <threads> --proxy <proxy>" << std::endl;
        return 1;
    }

    // 向终端回显参数(用于确认参数是否被正确读取)
    std::cout << "main >> parameters are as below" << std::endl;
    std::cout << "IP: " << ip << std::endl;
    std::cout << "Port: " << port << std::endl;
    std::cout << "Threads: " << threads << std::endl;
    if (proxy_specified)
    {
        std::cout << "Proxy specified." << std::endl;
        std::cout << "Proxy: " << proxy << std::endl;
    }
    else
    {
        std::cout << "No proxy specified." << std::endl;
    }
    std::cout << "-------------------------------------" << std::endl;

    // 处理参数，转换为int或string
    int port_num = std::atoi(port);
    int threads_num = std::atoi(threads);
    std::string ip_string(ip);
    if (proxy_specified == 0)
    {
        proxy = "";
    }
    std::string proxy_string(proxy);

    // 初始化server
    if (server.init(ip_string, port_num, threads_num, proxy_string, proxy_specified) != 0)
    {
        std::cerr << "[ERROR] main >> server init error" << std::endl;
    };
    // 启动server
    server.start();

    return 0; //  应该永远不会到这一行的
}
