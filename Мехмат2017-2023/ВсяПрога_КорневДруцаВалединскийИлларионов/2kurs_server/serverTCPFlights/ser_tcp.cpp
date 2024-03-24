
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "mainProgramTreatingZapros.h"


#define PORT    5555
#define BUFLEN  512




int  readFromClient (int fd, char *buf)
{
    int  nbytes;

    nbytes = read(fd,buf,BUFLEN);
    if ( nbytes<0 ) {
        // ошибка чтения
        perror ("Server: read failure");
        return -1;
    } else if ( nbytes==0 ) {
        // больше нет данных
        return -1;
    } else {
        // есть данные
        fprintf(stdout,"Server got message: %s\n",buf);
        return 0;
    }
}



void  writeToClient (int fd, char *buf)
{
    int  nbytes;
    unsigned char *s;

    for (s=(unsigned char*)buf; *s; s++) *s = toupper(*s);
    nbytes = write(fd,buf,strlen(buf)+1);
    fprintf(stdout,"Write back: %s\nnbytes=%d\n",buf,nbytes);
    
    if ( nbytes<0 ) {
        perror ("Server: write failure");
    }
}



int  main (void)
{

    int     i, err, opt=1;
    int     sock, new_sock;
    fd_set  active_set, read_set;
    struct  sockaddr_in  addr;
    struct  sockaddr_in  client;
    char    buf[BUFLEN];
    socklen_t  size;

    // Создаем TCP сокет для приема запросов на соединение
    sock = socket (PF_INET, SOCK_STREAM, 0);
    if ( sock<0 ) {
        perror ("Server: cannot create socket");
        exit (EXIT_FAILURE);
    }
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char*)&opt,sizeof(opt));

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

    // Создаем очередь на 3 входящих запроса соединения
    err = listen(sock,3);
    if ( err<0 ) {
        perror ("Server: listen queue failure");
        exit(EXIT_FAILURE);
    }

    // Подготавливаем множества дескрипторов каналов ввода-вывода.
    // Для простоты не вычисляем максимальное значение дескриптора,
    // а далее будем проверять все дескрипторы вплоть до максимально
    // возможного значения FD_SETSIZE.
    FD_ZERO(&active_set);
    FD_SET(sock, &active_set);

    // Основной бесконечный цикл проверки состояния сокетов
    while (1) {
        // Проверим, не появились ли данные в каком-либо сокете.
        // В нашем варианте ждем до фактического появления данных.
        read_set = active_set;
        if ( select(FD_SETSIZE,&read_set,NULL,NULL,NULL)<0 ) {
            perror("Server: select  failure");
            exit (EXIT_FAILURE);
        }

        // Данные появились. Проверим в каком сокете.
        for (i=0; i<FD_SETSIZE; i++) {
            if ( FD_ISSET(i,&read_set) ) {
                if ( i==sock ) {
                    // пришел запрос на новое соединение
                    size = sizeof(client);
                    new_sock = accept(sock,(struct sockaddr*)&client,&size);
                    if ( new_sock<0 ) {
                        perror("accept");
                        exit (EXIT_FAILURE);
                    }
                    fprintf (stdout, "Server: connect from host %s, port %hu.\n",
                            inet_ntoa(client.sin_addr),
                            ntohs(client.sin_port));
                    FD_SET(new_sock, &active_set);
                } else {
                    // пришли данные в уже существующем соединени
                    err = readFromClient(i,buf);
                    if ( err<0 ) {
                        // ошибка или конец данных
                        close (i);
                        FD_CLR(i,&active_set);
                    } else {
                        // данные прочитаны нормально
                        writeToClient(i,buf);
                        close (i);
                        FD_CLR (i,&active_set);
                        // а если это команда закончить работу?
                        if ( !strcmp(buf,"STOP") ) {
                            close(sock);
                            return 0;
                        }
                    }
                }
            }
        }
    }
}



