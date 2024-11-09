// utils.h

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

// 接收数据
std::string recvData(int clientSocket);

// 分割字符串
std::vector<std::string> splitString(const std::string &s, char delimiter);

#endif // UTILS_H
