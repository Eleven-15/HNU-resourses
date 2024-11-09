#ifndef __UTILS_H__
#define __UTILS_H__

#define LISTENQ 1024 // 监听队列长度,操作系统默认值为SOMAXCONN
#include <string>

namespace wsver
{

    namespace utils
    {
        int createListenFd(std::string ip, int port); // 创建监听描述符
        int setNonBlocking(int fd);                   // 设置非阻塞模式
    }

} // namespace wsver

#endif
