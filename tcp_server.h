#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#pragma once
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


class tcp_server
{
private:
    int serverSock_fd;   // Server Socket에 대한 File Discripter
    int clientSock_fd;
    int portNum;

    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;
    socklen_t clnt_addr_size;
    

public:
    tcp_server();
    ~tcp_server();
    void createSocket();



};

#endif