
#include<stdio.h>
#include<stdlib.h>



//-----------------------------------------------------------------------------------------------------------------------
void popadaetPoGorodamFrom(int* matchingFlights, Flight* baseflights, char** massivgorodov,int* table){
    int i=0; int j=0;
    int sovpalo=0;
    for(i=0; i<Nflights;i=i+1){
				sovpalo=0; 
				for(j=0; j<Ngorodov;j=j+1){if ((table[j]==1)&&(strcmp(baseflights[i].from,massivgorodov[j])==0)){sovpalo=1;}
							 }
				if (sovpalo==0) matchingFlights[i]=0;

    }





}
//-------------------------------------------------------------------------------------------------------------------------------
void popadaetPoGorodamTo(int* matchingFlights, Flight* baseflights, char** massivgorodov,int* table){
    int i=0; int j=0;
    int sovpalo=0;
    for(i=0; i<Nflights;i=i+1){
				sovpalo=0; 
				for(j=0; j<Ngorodov;j=j+1){if ((table[j]==1)&&(strcmp(baseflights[i].to,massivgorodov[j])==0)){sovpalo=1;}
							 }
				if (sovpalo==0) matchingFlights[i]=0;

    }





}


//--------------------------------------------------------------------------------------------------------------------------------
void popadaetPoDay(int* matchingFlights, Flight* baseflights, int* table){
    int i=0;
    for (i=0;i<Nflights; i=i+1){if((baseflights[i].date.day <table[0])||(baseflights[i].date.day >table[1])){matchingFlights[i]=0;}}
     




}

//-----------------------------------------------------------------------------------------------------------------------------------
void popadaetPoMonth(int* matchingFlights, Flight* baseflights, int* table){
    int i=0;
    for (i=0;i<Nflights; i=i+1){if((baseflights[i].date.month <table[0])||(baseflights[i].date.month >table[1])){matchingFlights[i]=0;}}
     




}
//--------------------------------------------------------------------------------------------------------------------------
void popadaetPoYear(int* matchingFlights, Flight* baseflights, int* table){
    int i=0;
    for (i=0;i<Nflights; i=i+1){if((baseflights[i].date.year <table[0])||(baseflights[i].date.year >table[1])){matchingFlights[i]=0;}}
     




}

//--------------------------------------------------------------------------------------------------------------------------
void popadaetPoFreemest(int* matchingFlights, Flight* baseflights, int* table){
    int i=0;
    for (i=0;i<Nflights; i=i+1){if((baseflights[i].freemest <table[0])||(baseflights[i].freemest >table[1])){matchingFlights[i]=0;}}
     




}

//--------------------------------------------------------------------------------------------------------------------------
void popadaetPoPrice(int* matchingFlights, Flight* baseflights, int* table){
    int i=0;
    for (i=0;i<Nflights; i=i+1){if((baseflights[i].price <table[0])||(baseflights[i].price >table[1])){matchingFlights[i]=0;}}
     




}
//--------------------------------------------------------------------------------------------------------------------------
void wantToBuy(int* matchingFlights, Flight* baseflights, int* table){
    //printf("want to buy "); printf("buy=%d\n",table[0]); 
    int i=0;
    for (i=0;i<Nflights; i=i+1){if((matchingFlights[i]==1)&&(table[0]==1)){ baseflights[i].freemest--;}}
     




}

//-------------------------------------------------------------------------------------------------------------------------------
void popadaetPoPlane(int* matchingFlights, Flight* baseflights, int* table, char** massivplanes){
    int i=0; int j=0;
    int sovpalo=0;
    for(i=0; i<Nflights;i=i+1){
				sovpalo=0; 
				for(j=0; j<Nplanes;j=j+1){if ((table[j]==1)&&(strcmp(baseflights[i].plane,massivplanes[j])==0)){sovpalo=1;}
							 }
				if (sovpalo==0) matchingFlights[i]=0;

    }





}



