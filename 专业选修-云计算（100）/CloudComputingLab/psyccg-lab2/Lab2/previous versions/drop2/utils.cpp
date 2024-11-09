// utils.cpp

#include "utils.h"
#include <cstring>
#include <iostream>
#include <unistd.h>

std::string recvData(int clientSocket)
{
    const int bufferSize = 1024;
    char buffer[bufferSize];
    std::string data;

    ssize_t bytesReceived = recv(clientSocket, buffer, bufferSize, 0);
    if (bytesReceived <= 0)
    {
        std::cerr << "Failed to receive data." << std::endl;
        return data;
    }

    data.append(buffer, bytesReceived);

    return data;
}

std::vector<std::string> splitString(const std::string &s, char delimiter)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}
