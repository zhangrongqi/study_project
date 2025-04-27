#pragma once
#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <arpa/inet.h>
#endif

class TcpClient {
public:
    TcpClient() : sock(-1), running(false) {}

    ~TcpClient() {
        disconnect();
    }

    bool connect(const std::string& ip, int port) {
        // 创建套接字
#ifdef _WIN32
        sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock == INVALID_SOCKET) return false;
#else
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) return false;
#endif

        // 设置服务器地址
        sockaddr_in server_addr{};
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);

        // 连接服务器
        if (::connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            close_socket();
            return false;
        }

        // 启用心跳检测
        enable_keepalive();
        start_heartbeat();

        running = true;
        return true;
    }

    void disconnect() {
        running = false;
        close_socket();
    }

    bool is_running()
    {
        return running.load();
    }

private:
    int sock;
    std::atomic<bool> running;

    void close_socket() {
#ifdef _WIN32
        if (sock != INVALID_SOCKET) {
            closesocket(sock);
            sock = INVALID_SOCKET;
        }
#else
        if (sock >= 0) {
            close(sock);
            sock = -1;
        }
#endif
    }

    void enable_keepalive() {
        int opt = 1;
#ifdef _WIN32
        setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE,
            (const char*)&opt, sizeof(opt));

        // Windows专用参数设置
        tcp_keepalive keepalive = { 0 };
        keepalive.onoff = 1;
        keepalive.keepalivetime = 5000;    // 5秒开始探测
        keepalive.keepaliveinterval = 1000; // 1秒探测间隔

        DWORD bytes_returned;
        WSAIoctl(sock, SIO_KEEPALIVE_VALS,
            &keepalive, sizeof(keepalive),
            NULL, 0, &bytes_returned, NULL, NULL);
#else
        setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE,
            &opt, sizeof(opt));

        // Linux专用参数设置
        int keepidle = 5;     // 5秒空闲后开始探测
        int keepcnt = 3;      // 最多重试3次
        int keepintvl = 1;    // 1秒探测间隔

        setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE,
            &keepidle, sizeof(keepidle));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPCNT,
            &keepcnt, sizeof(keepcnt));
        setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL,
            &keepintvl, sizeof(keepintvl));
#endif
    }

    void start_heartbeat() {
        std::thread([this]() {
            while (running) {
                // 发送PING包
                std::string ping_msg = "PING";
                int sent = send(sock, ping_msg.c_str(), ping_msg.size(), 0);

                if (sent <= 0) {
                    //TO DO： 发送心跳失败，尝试断线检测
                    check_disconnect();
                    break;
                }

                // 等待服务器响应
                char buffer[1024] = { 0 };
                auto start = std::chrono::steady_clock::now();
                while (std::chrono::duration_cast<std::chrono::seconds>(
                    std::chrono::steady_clock::now() - start).count() < 3) {
#ifdef _WIN32
                    fd_set readfds;
                    FD_ZERO(&readfds);
                    FD_SET(sock, &readfds);
                    timeval timeout{ 3, 0 };
                    int ret = select(sock + 1, &readfds, NULL, NULL, &timeout);
#else
                    fd_set readfds;
                    FD_ZERO(&readfds);
                    FD_SET(sock, &readfds);
                    timeval timeout{ 3, 0 };
                    int ret = select(sock + 1, &readfds, NULL, NULL, &timeout);
#endif
                    if (ret <= 0) continue;

                    size_t received = recv(sock, buffer, sizeof(buffer) - 1, 0);
                    if (received > 0) {
                        buffer[received] = '\0';
                        if (std::string(buffer) == "PONG") {
                            // TO DO： 处理心跳反馈
                            break;
                        }
                    }
                    else {
                        check_disconnect();
                        return;
                    }
                }

                // TO DO： 处理断连事务
                check_disconnect();
                break;
            }
            }).detach();
    }

    void check_disconnect() {
        int error = 0;
#ifdef _WIN32
        int len = sizeof(error);
        getsockopt(sock, SOL_SOCKET, SO_ERROR, (char*)&error, &len);
        if (error == WSAECONNRESET || error == WSAENETDOWN) {
            std::cerr << "检测到断线: " << error << std::endl;
#elif __linux__
        error = errno;
        if (error == ECONNRESET || error == ENETUNREACH) {
            std::cerr << "检测到断线: " << strerror(error) << std::endl;
#endif
            disconnect();
        }
        }
    };

int main() {
    TcpClient client;

#ifdef _WIN32
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    if (client.connect("127.0.0.1", 8080)) {
        std::cout << "已连接到服务器" << std::endl;
        // 模拟业务通信
        for (int i = 0; i < 10; ++i) {
            if (!client.is_running()) break;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    else {
        std::cerr << "连接服务器失败" << std::endl;
    }

#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}