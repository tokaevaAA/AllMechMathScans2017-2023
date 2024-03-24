#include <stdio.h>
#include <stdlib.h>



void changelistgoroda(){
    FILE*f;
    FILE*g;
    f=fopen("dano-gorodawithnumbers.txt","r");
    if(f==0){printf("cannot open dano-gorodawithnumbers.txt"); }
    g=fopen("onlygoroda.txt","w");
    char teksymbol;
    int k=0;
    k=fscanf(f,"%c",&teksymbol);
    while(k==1){
	if((65<= int(teksymbol))&&(int(teksymbol)<=90)) {fprintf(g,"%c",teksymbol);}
	if((97<= int(teksymbol))&&(int(teksymbol)<=122)) {fprintf(g,"%c",teksymbol);}
	if(32== int(teksymbol)) {fprintf(g,"%c",teksymbol);}
	if(10== int(teksymbol)) {fprintf(g,"%c",teksymbol);}
	k=fscanf(f,"%c",&teksymbol);
    }

    fclose(f);
    fclose(g);


}
//-----------------------------------------------------------------------------------

int amountgoroda(){
    FILE*f;
    f=fopen("dano-onlygoroda.txt","r");
    if (f==0){printf("cannot open dano-onlygoroda.txt"); return -1;}
    char tekslovo[20];
    int k=0;
    int cnt=0;
    k=fscanf(f,"%s",tekslovo);
    while(k==1){cnt=cnt+1; k= fscanf(f,"%s",tekslovo);}
    printf("amountgoroda=%d\n",cnt);
    rewind(f);
    fclose(f);
    return cnt;
}


