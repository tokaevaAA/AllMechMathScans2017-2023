
#include <stdio.h>
#include <stdlib.h>

void getbase(Flight* baseflights, char** massivgorodov, char** massivplanes,int* massivmest){
    int j=0;
    for(j=0;j<Nflights;j=j+1){
    
	int a1 = rand() %Ngorodov;
	int a2 = rand() %Ngorodov;
	int b = rand() %Nplanes;
	int c1=rand()%30;
	int c2=rand()%12;
	int c3=2019;
	int d=rand()%1000;
	Date tekdate;
	tekdate.Set(c1,c2,c3);
	//printf("a1= %d a2=%d  b=%d \n",a1,a2,b);
	baseflights[j].Set(massivgorodov[a1],massivgorodov[a2],massivplanes[b],massivmest[b],massivmest[b],tekdate,d);
    }


}
