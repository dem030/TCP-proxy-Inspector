#include "relay.h"
#include "keywords.h"
#include "logger.h"

static int send_all(int fd, const void *data, size_t len){
    int counter = 0;
    while (counter < len){
        int send_byte_rem = len - counter;
        int ret = send(fd, (const uint8_t *) data + counter , send_byte_rem, 0);
        if (ret > 0 ){
            counter += ret;   
        }
        else if (ret == 0){
            return -1;
        }
        else{
            if (errno == EINTR){
                continue;
            }else{
            return -1;
            }
        }
    }
    return len;
}



int sort_stream(int sockfdclient,int sockfdserver){
    uint8_t buf[4096];
    FILE  *fop = openfile("../log.txt");
    if (fop == NULL) {
    printf("[-] Impossibile aprire il file log.txt\n");
    return -1;
}
       
    fd_set read_set;
    int len = 0;
    while(1){
        FD_ZERO(&read_set);
        FD_SET(sockfdclient, &read_set);
        FD_SET(sockfdserver, &read_set);
        int n = select((sockfdclient > sockfdserver ? sockfdclient : sockfdserver) + 1, &read_set, NULL, NULL, NULL);
        /*se i dati li ha il client li legge e li manda al server*/
        if(FD_ISSET(sockfdclient, &read_set)){
            len = recv(sockfdclient, buf, sizeof(buf), 0);
            if(len <= 0){
                printf("[-] client disconnesso (fd=%d)\n", sockfdclient);
                closefile(fop);
                return -1;
            }
            if(check_buff(buf, len) == 0){
                if(send_all(sockfdserver, buf, len) == -1) {
                    closefile(fop);
                    return -1;
                }
            write_log(fop, UPSTREAM, buf, len);
            
        }else{
            printf("[-] messaggio bloccato (fd=%d)\n", sockfdclient);
            
        }
        }
        
        if(FD_ISSET(sockfdserver, &read_set)){
            len = recv(sockfdserver, buf, sizeof(buf), 0);
            if(len <= 0){
                printf("[-] server disconnesso (fd=%d)\n", sockfdserver);
                closefile(fop);
                return -1;
                
            }
            if(check_buff(buf, len) == 0){
                if(send_all(sockfdclient, buf, len) == -1){
                    closefile(fop);
                    return -1;
                }
                write_log(fop, DOWNSTREAM, buf, len);
                
            }else{
                printf("[-] messaggio bloccato (fd=%d)\n", sockfdserver);
                
            }
        }
            
    }
    
}
