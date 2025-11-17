//
// Created by kemptonburton on 11/17/2025.
//

#ifndef TCP_H
#define TCP_H

#include <string>
#include <iostream>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

class TCPClient {
public:
    TCPClient(const std::string& ip, int port)
        : server_ip(ip), server_port(port), sock(-1), connected(false) {
#ifdef _WIN32
        WSADATA wsa;
        WSAStartup(MAKEWORD(2,2), &wsa);
#endif
    }

    ~TCPClient() { disconnect();
#ifdef _WIN32
        WSACleanup();
#endif
    }

    bool isConnected() const { return connected; }

    // Attempt to connect (blocking until success)
    bool connectBlocking() {
        if (connected) return true;

        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) return false;

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(server_port);
        addr.sin_addr.s_addr = inet_addr(server_ip.c_str());

        if (::connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
#ifdef _WIN32
            closesocket(sock);
#else
            close(sock);
#endif
            sock = -1;
            return false;
        }

        connected = true;
        std::cout << "[TCP] Connected!\n";
    }

    void disconnect() {
        if (!connected) return;
#ifdef _WIN32
        closesocket(sock);
#else
        close(sock);
#endif
        connected = false;
        sock = -1;
        std::cout << "[TCP] Disconnected\n";
    }

    // Blocking receive (reads up to buffer size)
    bool receiveLine(std::string& out) {
        if (!connected) return false;

        char buffer[256];
        int bytes = recv(sock, buffer, sizeof(buffer)-1, 0);

        if (bytes <= 0) {
            disconnect();
            return false;
        }

        buffer[bytes] = '\0';
        out = buffer;
        return true;
    }

    // Blocking send
    void sendLine(const std::string& msg) {
        if (!connected) return;
        std::string m = msg + "\n";
        send(sock, m.c_str(), (int)m.size(), 0);
    }

private:
    std::string server_ip;
    int server_port;
    int sock;
    bool connected;
};

#endif //TCP_H
