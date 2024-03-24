#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

// Определимся с портом, адресом сервера и другими константами.
// В данном случае берем произвольный порт и адрес обратной связи
// (тестируем на одной машине).
#define  SERVER_PORT     5555
#define  SERVER_NAME    "127.0.0.1"
#define  BUFLEN          512

// Две вспомогательные функции для чтения/записи 
void  writeToServer  (int fd);
void  readFromServer (int fd);


void  writeToServer (int fd)
{   printf("Start writing to server\n");
    int   nbytes;
    char  buf[BUFLEN];

    fprintf(stdout,"Send to server from 3coefficient.txt\n ");
    //fgets(buf,BUFLEN,stdin);
    //buf[strlen(buf)-1] = 0;
    
    
    FILE*f1;
    f1=fopen("3coefficient.txt","r");
    if (f1==0) printf("Cannot open 3coefficient.txt\n");
    
    
    char teksymbol;
     int j=0;
    for (j=0; j<BUFLEN; j=j+1){buf[j]=0;}
    int k=fscanf(f1,"%c",&teksymbol);
    j=0;
    while(k==1){
		buf[j]=teksymbol; 
		k=fscanf(f1,"%c",&teksymbol);
		j=j+1;}
    printf("\nbuf=:");
    for (j=0; j<BUFLEN; j=j+1){printf("%c",buf[j]);}
    fclose(f1);
    
    
    
    printf("\nend buf\n");
    nbytes = write (fd,buf,strlen(buf)+1);
    if ( nbytes<0 ) { perror("write"); exit (EXIT_FAILURE); }
}


void  readFromServer (int fd)
{
    int   nbytes;
    char  buf[BUFLEN];

    nbytes = read(fd,buf,BUFLEN);
    if ( nbytes<0 ) {
        // ошибка чтения
        perror ("read"); exit (EXIT_FAILURE);
    } else if ( nbytes==0 ) {
        // нет данных для чтения
        fprintf (stderr,"Client: no message\n");
    } else {
        // ответ успешно прочитан
        fprintf (stdout,"Server's replay: %s\n",buf);
    }
}




int  main (void)
{

    int err;
    int sock;
    struct sockaddr_in server_addr;
    struct hostent* hostinfo;

    // Получаем информацию о сервере по его DNS имени
    // или точечной нотации IP адреса.
    hostinfo = gethostbyname(SERVER_NAME);
    if ( hostinfo==NULL ) {
        fprintf (stderr, "Unknown host %s.\n",SERVER_NAME);
        exit (EXIT_FAILURE);
    }

    // Заполняем адресную структуру для последующего
    // использования при установлении соединения
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr = *(struct in_addr*) hostinfo->h_addr;

    // Создаем TCP сокет.
    sock = socket(PF_INET, SOCK_STREAM, 0);
    if ( sock<0 ) {
        perror ("Client: socket was not created");
        exit (EXIT_FAILURE);
    }

    // Устанавливаем соединение с сервером
    err = connect (sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if ( err<0 ) {
        perror ("Client:  connect failure");
        exit (EXIT_FAILURE);
    }
    fprintf (stdout,"Connection is ready\n");

    // Обмениваемся данными
    writeToServer(sock);
    readFromServer(sock);

    // Закрываем socket
    close (sock);
//}
    exit (EXIT_SUCCESS);
}






