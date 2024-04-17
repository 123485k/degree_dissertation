#include "modbus-server.hpp"

#include <modbus/modbus.h>

#include <cstdint>
#include <cstring>
#include <iostream>
#include <thread>


bool ModbusSlave::initModbus(std::string Host_Name = "0.0.0.0",
                             std::string port = "502", bool debugging = true) {
  ctx = modbus_new_tcp_pi(Host_Name.c_str(), port.c_str());
  modbus_set_debug(ctx, debugging);
  if (ctx == nullptr) {
    std::cerr << "There was an error allocating the modbus\n";
    throw -1;
  }
  m_modbusSocket = modbus_tcp_pi_listen(ctx, 1);
  mapping = modbus_mapping_new(m_numBits, m_numInputBits, m_numInputRegisters,
                               m_numRegisters);
  if (mapping == nullptr) {
    std::cerr << "Unable to assign mapping: " << modbus_strerror(errno) << "\n";
    modbus_free(ctx);
    m_initialized = false;
    return false;
  }
  m_initialized = true;
  return true;
}

ModbusSlave::ModbusSlave(std::string host, std::string port) {
  initModbus(host, port, false);
}

ModbusSlave::~ModbusSlave() {
  modbus_mapping_free(mapping);
  modbus_close(ctx);
  modbus_free(ctx);
}
void ModbusSlave::recieveMessages() {
  uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];
  int master_socket;
  int rc;
  fd_set refset;
  fd_set rdset;
  int fdmax;                        // Maximum file descriptor number
  FD_ZERO(&refset);                 // Clear the reference set of socket
  FD_SET(m_modbusSocket, &refset);  // Add the server socket
  fdmax = m_modbusSocket;           // Keep track of the max file descriptor
  for (;;) {
    rdset = refset;
    if (select(fdmax + 1, &rdset, NULL, NULL, NULL) == -1) {
      std::cerr << "Server select() failure.\n";
      break;
    }

    /* Run through the existing connections looking for data to be
     * read */
    for (master_socket = 0; master_socket <= fdmax; master_socket++) {
      if (!FD_ISSET(master_socket, &rdset)) {
        continue;
      }

      if (master_socket == m_modbusSocket) {
        /* A client is asking a new connection */
        socklen_t addrlen;
        struct sockaddr_in clientaddr;
        int newfd;

        /* Handle new connections */
        addrlen = sizeof(clientaddr);
        memset(&clientaddr, 0, sizeof(clientaddr));
        newfd =
            accept(m_modbusSocket, (struct sockaddr *)&clientaddr, &addrlen);
        if (newfd == -1) {
          std::cout << "Server accept() error\n";
        } else {
          FD_SET(newfd, &refset);

          if (newfd > fdmax) {
            /* Keep track of the maximum */
            fdmax = newfd;
          }
          std::cout << "New connection from " << inet_ntoa(clientaddr.sin_addr)
                    << ":" << clientaddr.sin_port << " on socket " << newfd
                    << "\n";
        }
      } else {
        modbus_set_socket(ctx, master_socket);
        rc = modbus_receive(ctx, query);
        if (rc > 0) {
          modbus_reply(ctx, query, rc, mapping);
        } else if (rc == -1) {
          /* This example server in ended on connection closing or
           * any errors. */
          std::cout << "Connection closed on socket "<< master_socket << "\n" ;
          close(master_socket);
          /* Remove from reference set */
          FD_CLR(master_socket, &refset);

          if (master_socket == fdmax) {
            fdmax--;
          }
        }
      }
    }
  }
}

void ModbusSlave::run() {
  std::thread loop([this]() {
    while (true) {
      if (m_initialized)
        recieveMessages();
      else
        m_initialized = true;
    }
  });
  loop.detach();
  return;
}


float ModbusSlave::getRegFloat_cdab(uint16_t regaddr)
{
  return modbus_get_float_cdab(&mapping->tab_registers[regaddr]);
}

bool ModbusSlave::setInputRegFloat_dcba(uint16_t regaddr, float value)
{
  if(regaddr > m_numInputBits -2)
    return false;
  slavemutex.lock();
  modbus_set_float_dcba(value, &mapping->tab_input_registers[regaddr]);
  slavemutex.unlock();
  return true;
}