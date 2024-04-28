#pragma once

#include <arpa/inet.h>
#include <modbus-tcp.h>
#include <netinet/in.h>
#include <sys/select.h>

#include <cstdint>
#include <mutex>
#include <string>
#include <thread>

class ModbusSlave
{
public:
    ModbusSlave(std::string& host, std::string& port);
    ~ModbusSlave();

public:
    bool initModbus(std::string& Host_Name, std::string& port, bool debugging);
    void recieveMessages();
    void start();
    void stop();
    float getRegFloat_cdab(uint16_t addr);
    bool setInputRegFloat_dcba(uint16_t addr, float value);

private:
    void run();
    std::mutex slavemutex_;
    modbus_t* ctx_{nullptr};
    std::thread m_thread;
    bool m_initialized{false};
    int m_modbusSocket{-1};
    bool m_running{false};
    modbus_mapping_t* mapping{nullptr};
    // Mapping
    int m_numBits{50000};
    int m_numInputBits{50000};
    int m_numRegisters{50000};
    int m_numInputRegisters{50000};
};