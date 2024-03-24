
#include <math.h>
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

// Определимся с номером порта и другими константами.
#define PORT    5555
#define BUFLEN  512

// Две вспомогательные функции для чтения/записи 
int   readFromClient(int fd, char *buf);
void  writeToClient (int fd, char *buf);


void solveEquation(double a, double b, double c, double* x1, double* x2, int* amountRoots){
    printf("solve equation function\n");
    if(a>0.0000000000000000001){
    printf("jjjj\n");
    double D=b*b -4*a*c;
    if (D<0) {printf("D<0\n");*amountRoots=0;}
    else if (D>0) {printf("D>0\n");*amountRoots=2;*x1 = 0.5*(b + sqrt(D))/a;*x2 = 0.5*(b - sqrt(D))/a;}
    else   {*amountRoots=1;*x1 = 0.5*(-b + sqrt(D))/a;*x2 = 0.5*(-b - sqrt(D))/a;}
    }
    else{*amountRoots=1;*x1=-c/b;*x2=-c/b;}
}

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
    unsigned char* s;

    for (s=(unsigned char*)buf; *s; s++) *s = toupper(*s);
    nbytes = write(fd,buf,strlen(buf)+1);
    fprintf(stdout,"Write back: %s\n nbytes=%d\n",buf,nbytes);
    
    if ( nbytes<0 ) {
        perror ("Server: write failure");
    }
}


#define OUTLEN 100000
char outbuf[OUTLEN];

void  myWriteToClient (int fd, char *buf)
{
    int  nbytes;
    

    double a; double b; double c;
    char*  pos=strstr(buf,"a=");
    sscanf(pos+2,"%lf",&a);
    pos=strstr(buf,"b=");
    sscanf(pos+2,"%lf",&b);
    pos=strstr(buf,"c=");
    sscanf(pos+2,"%lf",&c);
    
    double x1; double x2; int amountRoots;
    solveEquation(a,b,c,&x1,&x2,&amountRoots);
    printf("otvet:x1=%f x2=%f amRoots=%d \n", x1,x2,amountRoots);
    
    

    
    
    int pos1=0;
    pos1 = sprintf(outbuf,"HTTP/1.1 200 OK\r\n");
    pos1 =pos1+sprintf(outbuf+pos1,"Connection: close\r\n");
    pos1 =pos1+ sprintf(outbuf+pos1,"Content-type: text/html\r\n");
    pos1 =pos1+ sprintf(outbuf+pos1,"Content-lengh: 200\r\n");
    pos1 =pos1+ sprintf(outbuf+pos1,"\r\n");
    
    pos1 =pos1+ sprintf(outbuf+pos1,"<!DOCTYPE html>\r\n");
    pos1 =pos1+ sprintf(outbuf+pos1,"<html>\r\n");
    pos1 =pos1+ sprintf(outbuf+pos1,"<head>\r\n");
    pos1 =pos1+ sprintf(outbuf+pos1,"</head>\r\n");
    pos1 =pos1+ sprintf(outbuf+pos1,"<body>\r\n");
    pos1 =pos1+ sprintf(outbuf+pos1,"<h1>We are solving quadratic equation</h1>\r\n");
    pos1 =pos1+ sprintf(outbuf+pos1,"<h1>Your zapros was:</h1>\r\n");
    pos1 =pos1+ sprintf(outbuf+pos1,"<p>a=%f b=%f c=%f </p>\r\n",a,b,c);
    
    pos1 =pos1+ sprintf(outbuf+pos1,"<form action=\"http://@127.0.0.1:5555\">a:<input type=\"text\" name=\"a\" value=\"%f\">\r\n",a);
    pos1 =pos1+ sprintf(outbuf+pos1,"<input type=\"text\" name=\"b\" value=\"%f\">\r\n",b);
    pos1 =pos1+ sprintf(outbuf+pos1,"<input type=\"text\" name=\"c\" value=\"%f\">\r\n",c);
    pos1 =pos1+ sprintf(outbuf+pos1,"<input type=\"submit\" value=\"calculate\"></form>\r\n");
    
    
    pos1 =pos1+ sprintf(outbuf+pos1,"<h1>Your otvet is:</h1>\r\n");
    printf("amRoots=%d\n",amountRoots);
    if (amountRoots>=1){pos1 =pos1+ sprintf(outbuf+pos1,"<p> amountRoots=%d </p><p> x1=%f</p><p> x2=%f  </p>\r\n",amountRoots,x1,x2); }   
    if (amountRoots==0){pos1 =pos1+ sprintf(outbuf+pos1,"<p>no Roots</p>\r\n"); }
    pos1 =pos1+ sprintf(outbuf+pos1,"</body>\r\n");
    pos1 =pos1+ sprintf(outbuf+pos1,"</html>\r\n");
    
    
    
    printf("outbuf:\n");
    int g;
    for (g=0;g<200;g=g+1){printf("%c",outbuf[g]);}
    nbytes = write(fd,outbuf,strlen(outbuf)+1);
    
    sprintf(buf,"a=%f b=%f c=%f  x1=%f x2=%f amRoots=%d",a,b,c,x1,x2,amountRoots);
    //nbytes = write(fd,buf,strlen(buf)+1);
    fprintf(stdout,"Write back: %s\n nbytes=%d\n",buf,nbytes);
    
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
                        myWriteToClient(i,buf);
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





