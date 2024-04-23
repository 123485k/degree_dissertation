# An Modbus TCP/IP Server
This is a simple Modbus TCP/IP server written in C++.
It is intended to be used as a test server for Modbus TCP/IP clients.
## Build
```shell
$ git clone https://github.com/123485k/degree_dissertation --recurse-submodules
$ mkdir -p degree_dissertation/build
$ cd degree_dissertation/build
$ cmake .. && cmake --build .
```
## Usage
```shell
$ modbusapp -h
Modbus Server
Usage: modbusapp [OPTIONS]

Options:
  -h,--help                   Print this help message and exit
  -l,--listen TEXT [0.0.0.0]  Server listening address
  -p,--port INT [502]         Server listening port
```