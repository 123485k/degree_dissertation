#pragma once

#include <arpa/inet.h>
#include <modbus-tcp.h>
#include <modbus.h>
#include <netinet/in.h>
#include <sys/select.h>

#include <cstdint>
#include <mutex>
#include <string>

class ModbusSlave
{
public:
    ModbusSlave(std::string host = "0.0.0.0", std::string port = "502");
    ~ModbusSlave();

public:
    bool initModbus(std::string Host_Name, std::string port, bool debugging);
    void recieveMessages();
    void run();
    float getRegFloat_cdab(uint16_t addr);
    bool setInputRegFloat_dcba(uint16_t addr, float value);

private:
    std::mutex slavemutex;
    modbus_t* ctx{nullptr};
    bool m_initialized{false};
    int m_modbusSocket{-1};
    modbus_mapping_t* mapping{nullptr};
    // Mapping
    int m_numBits{50000};
    int m_numInputBits{50000};
    int m_numRegisters{50000};
    int m_numInputRegisters{50000};
};