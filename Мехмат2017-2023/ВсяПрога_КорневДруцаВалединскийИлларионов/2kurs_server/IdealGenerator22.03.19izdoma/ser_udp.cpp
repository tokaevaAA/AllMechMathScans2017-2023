
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define PORT     5556
#define BUFLEN   512

int main(void)
{

    int sock;
    int nbytes, err;
	unsigned int size; 
    struct sockaddr_in addr;
    struct sockaddr_in client;
    char  buf[BUFLEN];


    // Создаем UDP сокет для приема сообщений
    sock = socket (PF_INET, SOCK_DGRAM, 0);
    if ( sock<0 ) {
        perror ("Server: cannot create socket");
        exit (EXIT_FAILURE);
    }
    int opt=1;
    setsockopt(sock, SOL_SOCKET,SO_REUSEADDR,(char*)&opt,sizeof(opt));

    // Заполняем адресную структуру и
    // связываем сокет с любым адресом
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    err = bind(sock,(struct sockaddr*)&addr,sizeof(addr));
    if ( err<0 ) {
        perror ("Server: cannot bind socket");
        exit (EXIT_FAILURE);
    }
    fprintf(stdout,"Server is ready to get data\n");

    // Основной бесконечный цикл ожидания сообщений
    while (1) {
        //
        memset(buf,0,BUFLEN);

        // читаем данные от клиента; ждем на этом месте, пока они появятся
        size = sizeof(client);
        nbytes = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)&client, &size);
        if( nbytes<0 ) {
            perror ("Server: read failure");
            continue;
        }
        fprintf(stdout,"Server has got message: %s\n",buf);
        fprintf(stdout,"from %s port %u\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));

        // эхо-ответ
        sprintf(buf+strlen(buf)," echo\n");
        
//-------------------------------------------------------my program starts
        FILE*f;
        f=fopen("otvetNaGeneralZapros.txt","r");
        if (f==0){printf("cannot open otvetNaGeneralZapros\n");}
        else {printf("can open otvetNaGeneralZapros\n");}
        
        char teksymbol;
        int k=fscanf(f,"%c",&teksymbol);int j=0;
         while(k==1){if (int(teksymbol)==35) {break;}buf[j]=teksymbol;j=j+1;fscanf(f,"%c",&teksymbol);}
        buf[j]=0;
        printf("%s\n",buf);
        fclose(f);
        
//-----------------------------------------------------------------my program ends
        fprintf(stdout,"sending back: %s",buf);
        nbytes = sendto(sock,buf, strlen(buf)+1, 0,
                    (struct sockaddr*)&client, sizeof(client));
        if( nbytes<0 ) {
            fprintf(stderr,"Server: cannot send data echo\n");
            perror("Server");
        }
    }
    return 0;
}
