
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>


#define  SERVER_PORT    5556
#define  SERVER_NAME   "127.0.0.1"
#define  BUFLEN         512
#define  NCOPY          1


int main(void)
{
    int sock;
    int nbytes, i, err;
	unsigned int  size;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    struct hostent *hostinfo;
    char   buf[BUFLEN];

    // Получаем информацию о сервере по его DNS имени
    // или точечной нотации IP адреса.
    hostinfo = gethostbyname(SERVER_NAME);
    if ( hostinfo==NULL ) {
        fprintf (stderr, "Unknown host %s.\n",SERVER_NAME);
        exit (EXIT_FAILURE);
    }

    // Заполняем адресную структуру для последующего
    // использования при посылке сообщения
    server_addr.sin_family = hostinfo->h_addrtype;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr = *(struct in_addr*) hostinfo->h_addr;

    // Создаем UDP сокет.
    sock = socket(AF_INET,SOCK_DGRAM,0);
    if ( sock<0 ) {
        perror ("Client: socket was not created");
        exit (EXIT_FAILURE);
    }

    // Привязываем сокет к произвольному адресу
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    client_addr.sin_port = htons(0);
    err = bind(sock, (struct sockaddr*)&client_addr, sizeof(client_addr));
    if ( err<0 ) {
        perror ("Client: cannot bind socket");
        exit (EXIT_FAILURE);
    }

    // Посылаем на сервер NCOPY копий одного и того же сообщения,
    // текст которого вводится из файла generalzapros.txt
    fprintf(stdout,"Client: ready to send your message >");
    fgets(buf,BUFLEN,stdin);
    int j=0;
    
    /*
    FILE*f1; 
    f1=fopen("generalzapros.txt","w");
    while(buf[j]!='0'){fprintf(f1,"%c",buf[j]);j=j+1;}
    fclose(f1);
    */
    
    
    
    FILE*f; f=fopen("generalzapros.txt","r");
    char teksymbol;
    int k=fscanf(f,"%c",&teksymbol);
    while(k==1){buf[j]=teksymbol;k=fscanf(f,"%c",&teksymbol);j=j+1;} 
    fclose(f);
    
    
    size = strlen(buf);
    for(i=0; i<NCOPY; i++) {
        // дописываем в конец сообщения порядковый номер копии
        sprintf(buf+size," \n (copy %d) ",i);
        // отсылаем на сервер
        fprintf(stdout,"Sending zapros:\n %s\n",buf);
        nbytes = sendto(sock,buf, strlen(buf)+1, 0,
                    (struct sockaddr*)&server_addr,
                    sizeof(server_addr));
        if( nbytes<0 ) {
            fprintf(stderr,"Client: cannot send data copy %d\n",i);
            perror("Client");
            close(sock);
            exit (EXIT_FAILURE);
        }
    }

    // Пробуем получить ответ сервера.
    fprintf(stdout,"Getting server's replay\n");
    // отменяем на сокете режим ожидания данных при их отсутствии.
    fcntl(sock,F_SETFL,O_NONBLOCK);
    // Делаем NCOPY+2 попытки с задержкой между ними в 1 секунду.
    for (i=0;i<NCOPY+2;i++) {
        sleep(1);
        size = sizeof(server_addr);
        nbytes = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)&server_addr, &size);
        if( nbytes<0 ) {
            perror ("Client: read failure");
            continue;
        } else if ( nbytes==0 ) {
            fprintf(stdout,"The end\n");
            break;
        }
        fprintf(stdout,"%d bytes in replay: \n%s\n",nbytes,buf);
    }

    return 0;
}
