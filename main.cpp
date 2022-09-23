#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>


#define TCP_PORT 5100

int main(int argc, char **argv)
{
    int serverSock_fd, clientSock_fd;
    socklen_t clen;
    int n;
    struct sockaddr_in servaddr, cliaddr;
    char mesg[BUFSIZ];

    if((serverSock_fd = socket(AF_INET, SOCK_STREAM,0)) < 0)
    {
        perror("socket()");
        return -1;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(TCP_PORT);

    if(bind(serverSock_fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) <0)
    {
        perror("bind()");
        return -1;
    }

    if(listen(serverSock_fd, 8) < 0)
    {
        perror("listen()");
        return -1;
    }

    clen = sizeof(cliaddr);
    do
    {
        clientSock_fd = accept(serverSock_fd, (struct sockaddr *)&cliaddr, &clen);

        inet_ntop(AF_INET, &cliaddr.sin_addr, mesg, BUFSIZ);
        printf("Client is connected : %s\n", mesg);

        if((n = read(clientSock_fd, mesg, BUFSIZ)) <= 0)
        perror("read()");
        printf("Received data  : %s", mesg);

        if(write(clientSock_fd, mesg, n) <= 0)
            perror("write()");

        close(clientSock_fd);
    } while (strncmp(mesg, "q", 1));

    close(serverSock_fd);

    return 0;
    
}