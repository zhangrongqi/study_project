#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <atomic>
//#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

// 跨平台通用方案
#if defined(_WIN32)
using ssize_t = long;  // MinGW/Cygwin 兼容
#else
using ssize_t = ssize_t;  // POSIX 系统
#endif

namespace TCPIP_data_transmission
{
    namespace Client
    {
        constexpr int BUFFER_SIZE = 4096;    // 单个数据块大小
        constexpr int MAX_THREADS = 4;       // 最大工作线程数
        constexpr int HEADER_SIZE = 12;      // 块头信息大小

#pragma pack(push, 1)
        struct Block {
            uint64_t position;  // 文件中的起始位置
            uint32_t size;      // 数据块实际大小
            char data[BUFFER_SIZE]; // 数据内容
        };
#pragma pack(pop)

        class FileSender {
        public:
            FileSender(const std::string& host, int port, const std::string& filePath)
                : host_(host), port_(port), filePath_(filePath) {
            }

            bool sendData() {
                if (!initNetwork()) return false;
                if (!splitFile()) return false;

                std::vector<std::thread> sendWorkers;
                for (int i = 0; i < MAX_THREADS; ++i) {
                    sendWorkers.emplace_back(&FileSender::workerThread, this);
                }

                fillQueue();

                {
                    std::unique_lock<std::mutex> lock(queueMutex_);
                    queueCond_.wait(lock, [this] { return blockQueue_.empty() && isCompleted_; });
                }

                {
                    std::lock_guard<std::mutex> lock(sendMutex_);
                    exitFlag_ = true;
                }
                queueCond_.notify_all();

                for (auto& t : sendWorkers) t.join();
                cleanup();
                return true;
            }

        private:
            bool initNetwork() {
#ifdef _WIN32
                WSADATA wsaData;
                if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
                    std::cerr << "WSAStartup failed" << std::endl;
                    return false;
                }
#endif

                sock_ = socket(AF_INET, SOCK_STREAM, 0);
                if (sock_ < 0) {
#ifdef _WIN32
                    std::cerr << "Socket error: " << WSAGetLastError() << std::endl;
#else
                    std::cerr << "Socket error" << std::endl;
#endif
                    return false;
                }

                sockaddr_in serverAddr{};
                serverAddr.sin_family = AF_INET;
                serverAddr.sin_port = htons(port_);
                if (inet_pton(AF_INET, host_.c_str(), &serverAddr.sin_addr) <= 0) {
                    std::cerr << "Invalid address" << std::endl;
                    return false;
                }

                if (connect(sock_, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
                    std::cerr << "Connection failed" << std::endl;
                    return false;
                }
                return true;
            }

            bool splitFile() {
                file_.open(filePath_, std::ios::binary | std::ios::ate);
                if (!file_) {
                    std::cerr << "File open failed" << std::endl;
                    return false;
                }

                fileSize_ = file_.tellg();
                file_.seekg(0, std::ios::beg);
                totalBlocks_ = (fileSize_ + BUFFER_SIZE - 1) / BUFFER_SIZE;
                return true;
            }

            void fillQueue() {
                char buffer[BUFFER_SIZE];
                for (uint64_t pos = 0; pos < fileSize_; pos += BUFFER_SIZE) {
                    Block block{};
                    block.position = pos;
                    block.size = min(BUFFER_SIZE, fileSize_ - pos);

                    file_.read(buffer, block.size);
                    std::copy(buffer, buffer + block.size, block.data);

                    {
                        std::unique_lock<std::mutex> lock(queueMutex_);
                        blockQueue_.push(block);
                    }
                    queueCond_.notify_one();
                }

                {
                    std::lock_guard<std::mutex> lock(sendMutex_);
                    isCompleted_ = true;
                }
                queueCond_.notify_all();
            }

            void workerThread() {
                while (true) {
                    Block block{};
                    {
                        std::unique_lock<std::mutex> lock(queueMutex_);
                        queueCond_.wait(lock, [this] {
                            return !blockQueue_.empty() || (isCompleted_ && blockQueue_.empty());
                            });

                        if (isCompleted_ && blockQueue_.empty()) break;

                        block = blockQueue_.front();
                        blockQueue_.pop();
                    }

                    sendBlock(block);
                }
            }

            void sendBlock(const Block& block) {
                std::lock_guard<std::mutex> lock(sendMutex_);

                // 发送块头信息（网络字节序）
                uint64_t netPos = htonl(block.position);
                uint32_t netSize = htonl(block.size);

                if (send(sock_, (char*)&netPos, sizeof(netPos), 0) != sizeof(netPos) ||
                    send(sock_, (char*)&netSize, sizeof(netSize), 0) != sizeof(netSize)) {
                    std::cerr << "Header send failed" << std::endl;
                    return;
                }

                // 发送块数据
                ssize_t sent = send(sock_, block.data, block.size, 0);
                if (sent != block.size) {
                    std::cerr << "Data send failed" << std::endl;
                }
            }

            void cleanup() {
#ifdef _WIN32
                closesocket(sock_);
                WSACleanup();
#else
                close(sock_);
#endif
                file_.close();
            }

            std::string host_;
            int port_;
            std::string filePath_;
            std::ifstream file_;
            uint64_t fileSize_ = 0;
            uint64_t totalBlocks_ = 0;

            std::queue<Block> blockQueue_;
            std::mutex queueMutex_;
            std::condition_variable queueCond_;
            std::mutex sendMutex_;
            std::atomic<bool> isCompleted_{ false };
            std::atomic<bool> exitFlag_{ false };

#ifdef _WIN32
            SOCKET sock_;
#else
            int sock_;
#endif
        };
    }

    namespace Server
    {
        constexpr int MAX_THREADS = 4;
#pragma pack(push, 1)
        struct BlockHeader {
            uint64_t position;  // 文件中的起始位置
            uint32_t size;      // 数据块实际大小
        };
#pragma pack(pop)

        class FileReceiver {
        public:
            FileReceiver(int port, const std::string& savePath)
                : port_(port), savePath_(savePath), stopFlag_(false) {
            }

            void start() {
                initNetwork();
                startWorkerThreads();
                acceptConnections();
                stopWorkerThreads();
                cleanup();
            }

        private:
            void initNetwork() {
#ifdef _WIN32
                WSADATA wsaData;
                if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
                    std::cerr << "WSAStartup failed" << std::endl;
                    return;
                }
#endif

                serverSock_ = socket(AF_INET, SOCK_STREAM, 0);
                if (serverSock_ < 0) {
                    std::cerr << "Socket creation failed" << std::endl;
                    return;
                }

                sockaddr_in serverAddr{};
                serverAddr.sin_family = AF_INET;
                serverAddr.sin_port = htons(port_);
                serverAddr.sin_addr.s_addr = INADDR_ANY;

                if (bind(serverSock_, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
                    std::cerr << "Bind failed" << std::endl;
                    return;
                }

                if (listen(serverSock_, SOMAXCONN) < 0) {
                    std::cerr << "Listen failed" << std::endl;
                    return;
                }
            }

            void startWorkerThreads() {
                for (int i = 0; i < MAX_THREADS; ++i) {
                    workers_.emplace_back(&FileReceiver::workerThread, this);
                }
            }

            void stopWorkerThreads() {
                {
                    std::lock_guard<std::mutex> lock(queueMutex_);
                    stopFlag_ = true;
                }
                queueCond_.notify_all();
                for (auto& t : workers_) {
                    if (t.joinable()) t.join();
                }
            }

            void acceptConnections() {
                while (!stopFlag_) {
                    sockaddr_in clientAddr{};
                    socklen_t clientLen = sizeof(clientAddr);
                    int clientSock = accept(serverSock_, (sockaddr*)&clientAddr, &clientLen);

                    if (clientSock >= 0) {
                        std::lock_guard<std::mutex> lock(queueMutex_);
                        clientQueue_.push(clientSock);
                        queueCond_.notify_one();
                    }
                }
            }

            void workerThread() {
                while (true) {
                    int clientSock = -1;
                    {
                        std::unique_lock<std::mutex> lock(queueMutex_);
                        queueCond_.wait(lock, [this] {
                            return !clientQueue_.empty() || stopFlag_;
                            });

                        if (stopFlag_ && clientQueue_.empty()) break;
                        clientSock = clientQueue_.front();
                        clientQueue_.pop();
                    }

                    processClient(clientSock);
                }
            }

            void processClient(int clientSock) {
                std::ofstream outFile(savePath_, std::ios::binary | std::ios::app);
                if (!outFile) {
                    std::cerr << "File create failed" << std::endl;
                    closeClient(clientSock);
                    return;
                }

                try {
                    while (true) {
                        BlockHeader header{};
                        if (recv(clientSock, (char*)&header, sizeof(header), 0) != sizeof(header)) {
                            break;
                        }

                        uint64_t position = ntohl(header.position);
                        uint32_t size = ntohl(header.size);

                        std::vector<char> buffer(size);
                        ssize_t received = recv(clientSock, buffer.data(), size, 0);
                        if (received != size) break;

                        std::lock_guard<std::mutex> fileLock(fileMutex_);
                        outFile.seekp(position);
                        outFile.write(buffer.data(), size);
                    }
                }
                catch (...) {
                    std::cerr << "Client processing error" << std::endl;
                }

                closeClient(clientSock);
            }

            void closeClient(int clientSock) {
#ifdef _WIN32
                closesocket(clientSock);
#else
                close(clientSock);
#endif
            }

            void cleanup() {
#ifdef _WIN32
                closesocket(serverSock_);
                WSACleanup();
#else
                close(serverSock_);
#endif
            }

            int port_;
            std::string savePath_;
            int serverSock_;

#ifdef _WIN32
            WSADATA wsaData_;
#endif

            std::queue<int> clientQueue_;
            std::vector<std::thread> workers_;
            std::mutex queueMutex_;
            std::condition_variable queueCond_;
            std::atomic<bool> stopFlag_{ false };
            std::mutex fileMutex_;
        };

        int main() {
            FileReceiver receiver(8080, "received_file.bmp");
            receiver.start();
            return 0;
        }
    }
    
}

//int main() {
//    FileSender sender("127.0.0.1", 8080, "large_file.bmp");
//    if (sender.sendData()) {
//        std::cout << "File sent successfully" << std::endl;
//    }
//    else {
//        std::cerr << "File send failed" << std::endl;
//    }
//    return 0;
//}

//int main() {
//    FileReceiver receiver(8080, "received_file.bmp");
//    receiver.start();
//    return 0;
//}