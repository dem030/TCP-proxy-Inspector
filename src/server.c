#include "server.h"


/*apre un socket per il server e aspetta la connessione*/
int wait_conn(int port){
    int server_fd;
    struct sockaddr_in sockaddr;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd == -1) {
        perror("socket");
        return -1;
    }
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = INADDR_ANY;
    sockaddr.sin_port = htons(port);
    if((bind(server_fd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) == -1) || (listen(server_fd, 5) == -1)) {
        perror("bind or listen");
        return -1;
    }

    printf("server in ascolto su porta %d \n", port);
    return server_fd;
}
/*crea un socket per il client e accetta la connessione*/
int acc_conn(int sockfd){
    int client_fd;
    struct sockaddr_in client_addr;
    socklen_t addr_len = sizeof(client_addr);
    client_fd = accept(sockfd, (struct sockaddr *)&client_addr, &addr_len);
    if(client_fd == -1) {
        perror("accept");
        return -1;
    }
    return client_fd;
}
/*crea un socket per il client e si connette al server*/
int conn(const char *ip, int port) {
    int sockfd;
    struct sockaddr_in sockaddr;

    sockfd= socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1) {
        perror("socket");
        return -1;
    }
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_port = htons(port);
    if(inet_pton(AF_INET, ip, &sockaddr.sin_addr) <= 0) {
        perror("inet_pton");
        return -1;
    }
    if(connect(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) == -1) {
        perror("connect");
        return -1;
    }
    return sockfd;
}