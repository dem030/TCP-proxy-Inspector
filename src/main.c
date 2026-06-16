#include "main.h"



volatile int running = 1;

void sig_handler(int sig) {
    (void)sig;
    running = 0;
}


int main(int argc, char *argv[]){
    if(argc != 4) {  
        printf("Uso: %s <porta_locale> <ip_remoto> <porta_remota>\n", argv[0]);
    return -1;
    }
    signal(SIGINT, sig_handler);
    int key = load_key("../keywords.txt");
    if(key == -1) {
        printf("[-] Errore caricamento keyword\n");
        return -1;
    }

    int server_fd = wait_conn(atoi(argv[1]));

    while(running) {
        int client_fd = acc_conn(server_fd);
        if(client_fd == -1) {
            continue;
        }
        int new_fd = fork();
        if (new_fd == 0)
        {
            int remote_fd = conn(argv[2], atoi(argv[3]));
            sort_stream(client_fd,remote_fd);
            exit(0);

        }else if (new_fd > 0 ){
            close(client_fd);
        }else if (new_fd == -1)
        {
            perror("fork");
            close(client_fd);
            continue;
        }
    }
    free_banlist();
    close(server_fd);
    return 0;
}