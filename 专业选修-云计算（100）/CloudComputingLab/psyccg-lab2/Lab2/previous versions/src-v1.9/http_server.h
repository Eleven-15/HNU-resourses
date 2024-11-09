#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "thread_pool.h"
#include <string>

class HTTPServer
{
public:
    // HTTPServer(const std::string &ip, int port, int threads, const std::string &proxy, bool proxy_specified);
    HTTPServer(){};
    void init(const std::string &ip, int port, int threads, const std::string &proxy, bool proxy_specified);
    void start();
    void stop();

private:
    std::string ip_;
    int port_;
    int threads_;
    std::string proxy_;
    bool proxy_specified_;
    int server_sock_;

    void handle_request(int client_sock);
    std::string parse_request(const std::string &request);
    void send_response(int client_sock, const std::string &response);
    std::string get_response_from_server(const std::string &request);
    std::string generate_message(std::string version, std::string status, std::string content_type, std ::string body);
    std::string get_static(std::string url);
    std::string get_data(std::string url);
    std::string construct_static(std::string type, std::string http_version);
    std::string data_query(std::string method, std::string data, std::string &status);
};

#endif
