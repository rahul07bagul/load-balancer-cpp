#pragma once
#include <string>
#include <cstdint>
#include <windows.h>
#include <atomic>
#include <chrono>

class Server {
public:
    Server(const std::string& host, uint16_t port);
    std::string getAddress() const;
    uint16_t getPort() const;
    std::string getId() const;
    bool isHealthy() const;
    void setHealthStatus(bool status);
    std::chrono::system_clock::time_point getLastHealthCheckTime() const;
    void setLastHealthCheckTime(std::chrono::system_clock::time_point t);
    uint64_t getRequestCount() const { return request_count_.load(); }
    void incrementRequestCount() { request_count_.fetch_add(1); }

private:
    std::string host_;
    uint16_t port_;
    bool is_healthy_;
    std::string id_;
    std::chrono::system_clock::time_point last_health_check_time_;
    std::atomic<uint64_t> request_count_{0};
};