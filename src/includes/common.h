#ifndef COMMON_H
#define COMMON_H

#include <string>

#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_PATCH 0
#define VERSION_STR "1.0.0"

inline std::string getPlatformName()
{
    #ifdef PLATFORM_LINUX
        return "Linux";
    #elif defined(PLATFORM_MACOS)
        return "macOS";
    #elif defined(PLATFORM_WINDOWS)
        return "Windows";
    #else
        return "Unknown";
    #endif
}

#ifdef PLATFORM_WINDOWS
    #include <winsock2.h>
    #include <windows.h>
    #include <ws2tcpip.h>
    typedef SOCKET socket_t;
    #define socket_close closesocket
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <fcntl.h>
    typedef int socket_t;
    #define socket_close close
#endif

#endif // COMMON_H
