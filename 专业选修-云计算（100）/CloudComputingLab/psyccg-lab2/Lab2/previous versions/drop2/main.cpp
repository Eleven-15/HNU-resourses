// #include "HttpServer.h"
#include <cstdlib> // 包含 std::atoi 和 std::atof 函数
#include <getopt.h>
#include <iostream>

#define DEBUG 1
//  ./http_server --ip 127.0.0.1 --port 8080 --threads 4 --proxy http://example.com:80
using namespace std;

void printUsage()
{
	std::cout << "Usage: http-server [OPTIONS]" << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "  -i, --ip <IP>           Specify the server IP address" << std::endl;
	std::cout << "  -p, --port <PORT>       Selects which port the HTTP server listens on for incoming connections" << std::endl;
	std::cout << "  --proxy <PROXY>         Selects an \"upstream\" HTTP server to proxy" << std::endl;
	std::cout << "  -t, --threads <THREADS> Number of threads if you use multi-thread" << std::endl;
}

int main(int argc, char **argv)
{
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
			std::cerr << "Usage: " << argv[0] << " -i <ip> -p <port> -t <threads> --proxy <proxy>" << std::endl;
			return 1;
		}
	}

	// 检查是否提供了必需的参数
	if (ip == nullptr || port == nullptr || threads == nullptr)
	{
		std::cerr << "Error: Missing required arguments." << std::endl;
		std::cerr << "Usage: " << argv[0] << " -i <ip> -p <port> -t <threads> --proxy <proxy>" << std::endl;
		return 1;
	}

	// 在这里使用解析到的参数执行相应的操作
	if (DEBUG)
	{
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
	}

	int port = std::atoi(port);
	int threads = std::atoi(threads);
	std::string ip_string(ip);
	std::string proxy_string(proxy);
	HttpServer server(ip_string, port_num, threads_num, proxy_string);
	server.run();

	// // 解析命令行参数
	// string ip = "127.0.0.1"; // 默认IP地址
	// int port = 8080;		 // 默认端口号
	// int threads = 4;		 // 默认线程池大小
	// bool proxyMode = false;	 // 默认非代理模式
	// string proxyAddr = "";	 // 默认代理地址

	// parseCommandLineArgs(argc, argv, ip, port, threads, proxyMode, proxyAddr);

	// // 创建并启动HTTP服务器
	// HTTPServer server(ip, port, threads, proxyMode, proxyAddr);
	// server.start();

	return 0;
}
