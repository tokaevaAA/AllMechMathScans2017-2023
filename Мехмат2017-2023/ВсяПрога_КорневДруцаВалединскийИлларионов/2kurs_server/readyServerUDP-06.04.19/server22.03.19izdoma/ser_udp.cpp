
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

#include "mainProgramTreatingZapros.h"

#define PORT     5556
#define BUFLEN   512

void printFlightBuf(int i,char* buf1,Flight* baseflights){
    printf("start putting Flight into buf1\n");
    unsigned int pos=0;
    pos = sprintf(buf1,"from %s ",baseflights[i].from);
    pos =pos +  sprintf(buf1+pos,"to %s ",baseflights[i].to);
    pos =pos +  sprintf(buf1+pos,"plane %s ",baseflights[i].plane);
    pos =pos +  sprintf(buf1+pos,"maxmest %d ",baseflights[i].maxmest);
    pos =pos +  sprintf(buf1+pos,"freemest%d ",baseflights[i].freemest);
    pos =pos +  sprintf(buf1+pos,"day %d ",baseflights[i].date.day);
    pos =pos +  sprintf(buf1+pos,"month %d ",baseflights[i].date.month);
    pos =pos +  sprintf(buf1+pos,"year %d ",baseflights[i].date.year);
    pos =pos +  sprintf(buf1+pos,"price %d ",baseflights[i].price);
    
}


int main(void)
{

    int sock; int i=0; int j=0;
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

//-----------------------------------------------------------------------------------
    char* massivplanes[Nplanes];
    int  massivmest[Nplanes];
    char* massivgorodov[Ngorodov];
    Flight baseflights[Nflights];
    char* massivproperties[Nproperties];
    getmasofplanes(massivplanes,massivmest);
    getmasofgorodov(massivgorodov);
    getbase(baseflights,massivgorodov,massivplanes,massivmest);
    getproperties(massivproperties);

    FILE* file_base;
    file_base=fopen("initialbase.txt","w");
    for(j=0;j<Nflights;j=j+1){baseflights[j].pechatvfile(file_base);}
    fclose(file_base);

    
    int matchingProperties[Nproperties];
    
    int table0[Ngorodov]; 	//from
    int table1[Ngorodov]; 	//to
    int table2[2];   		//day
    int table3[2];   		//month
    int table4[2];   		//year
    int table5[2];   		//freemest
    int table6[2];     		//price
    int  table7[1];  		//buy
    int table8[Nplanes]; 	//plane
    
    int matchingFlights[Nflights];

//-----------------------------------------------------------------------------------------------




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
        printf("HELLO start treating  zapros\n");
        
           for (i=0; i<Nproperties; i=i+1){matchingProperties[i]=0;}
           for(i=0; i<Nflights; i=i+1){matchingFlights[i]=1;}


           for(i=0; i<Ngorodov; i=i+1){table0[i]=1;} 	//from
           for(i=0; i<Ngorodov; i=i+1){table1[i]=1;}  	//to
           table2[0]=0;    table2[1]=29;    		//day
           table3[0]=0;    table3[1]=12;  		//month
           table4[0]=2019; table4[1]=2019;  		//year
    	   table5[0]=0;    table5[1]=1000;  		//freemest
           table6[0]=0;    table6[1]=1000;   		//price
           table7[0]=0;					//buy
           for(i=0; i<Nplanes; i=i+1){table8[i]=1;}	//plane
	    
	    
	   FILE*f3; f3=fopen("generalzapros.txt","w");
	   for(i=0; i< BUFLEN; i=i+1){fprintf(f3,"%c",buf[i]);if (buf[i]=='#') break;}
	   fclose(f3);
	    FILE*f;
           f=fopen("generalzapros.txt","r");
           if (f==0) {printf("Cannot open generalzapros.txt");}
           rewind(f);
           createZaprosFromFile(f, massivproperties, massivgorodov, matchingProperties, table0, table1, table2, table3, table4, table5, table6, table7,table8,massivplanes);
           fclose(f);

           selectPoZaprosu(matchingFlights, matchingProperties, baseflights,massivgorodov, table0, table1, table2, table3, table4, table5, table6, table7,table8,massivplanes);



           FILE*otvetfile;
           otvetfile=fopen("otvetNaGeneralZapros.txt","w");
           int cnt=0; 
           
           for (i=0; i<Nflights; i=i+1){if (matchingFlights[i]==1){cnt=cnt+1;printf("good i=%d\n",i);baseflights[i].pechatvfile(otvetfile);}}
           fprintf(otvetfile,"#");
           fclose(otvetfile);


          

           //printf("\n size of Flight=%ld\n",sizeof(Flight));
           printf("GOODBYE end treating zapros\n");
          


//------------------------------------------------------------------------

        
//--------------------

        FILE*f2;
        f2=fopen("otvetNaGeneralZapros.txt","r");
        if (f2==0){printf("cannot open otvetNaGeneralZapros\n");}
        else {printf("can open otvetNaGeneralZapros\n");}
        
        char teksymbol;
        int k=fscanf(f2,"%c",&teksymbol);
        int jj=0;
         while(k==1){if (int(teksymbol)==35) {break;}buf[jj]=teksymbol;jj=jj+1;fscanf(f2,"%c",&teksymbol);}
        buf[jj]=0;
        printf("%s\n",buf);
        fclose(f2);


//------------------------       
/*	char buf1[512];
	for (i=0; i <Nflights; i=i+1){if(matchingFlights[i]==1) {printf("i=%d\n",i);
								printFlightBuf(i,buf1,baseflights);
								fprintf(stdout,"flights: %s",buf1);
								}
				     } 
        
        
*/
        
//-----------------------------------------------------------------my program ends
	printf("cnt=%d\n",cnt);
	int otv; otv=cnt;
        fprintf(stdout,"sending back amount good flights: %d",otv);
        nbytes = sendto(sock,&otv, sizeof(int), 0,(struct sockaddr*)&client, sizeof(client));
        
        
        
	for (i=0; i <Nflights; i=i+1){if(matchingFlights[i]==1) {
								printFlightBuf(i,buf,baseflights);
								fprintf(stdout,"sending back: %s",buf);
    								nbytes = sendto(sock,buf, strlen(buf)+1, 0,(struct sockaddr*)&client, sizeof(client));
    								if( nbytes<0 ) {
        							fprintf(stderr,"Server: cannot send data echo\n");
        							perror("Server");
    										}
								}
				     } 
        
        
    /*    
        printf("\n");
        fprintf(stdout,"sending back: %s",buf);
        nbytes = sendto(sock,buf, strlen(buf)+1, 0,(struct sockaddr*)&client, sizeof(client));
        
        
        if( nbytes<0 ) {
            fprintf(stderr,"Server: cannot send data echo\n");
            perror("Server");
        }
        
*/

    }
    for (i=0; i<Nplanes; i=i+1){free(massivplanes[i]);}
    for (i=0; i<Ngorodov; i=i+1){free(massivgorodov[i]);}
    for (i=0; i<Nproperties; i=i+1){free(massivproperties[i]);}

    return 0;
}
