#include "tcp_server.h"

tcp_server::tcp_server()
{

}

tcp_server::~tcp_server()
{

}


void tcp_server::createSocket()
{
if((serverSock_fd = socket(AF_INET, SOCK_STREAM,0)) < 0)
    {
        perror("socket()\n");
        return;
    }

    int option = 1;
    setsockopt(serverSock_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(portNum);

    if(bind(serverSock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <0)
    {
        perror("bind()");
        return;
    }

    if(listen(serverSock_fd, 8) < 0)
    {
        perror("listen()");
        return;
    }
}