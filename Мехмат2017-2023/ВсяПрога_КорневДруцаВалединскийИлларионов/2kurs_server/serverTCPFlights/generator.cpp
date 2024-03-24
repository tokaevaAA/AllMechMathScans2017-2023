#define Nplanes 7
#define Ngorodov 154
#define Nflights 15
#define Nproperties 9


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dopfile-structDateFlight.h"
#include "dopfile-create&countgoroda.h"
#include "dopfile-getGorodaPlanesProperties.h"
#include "dopfile-getBase.h"
#include "dopfile-createZaprosFromFile.h"
#include "dopfile-popadaetFunctions0-9.h"



//------------------------------------------------------------------------------------------------------------------
void selectPoZaprosu(int* matchingFlights, int* matchingProperties, Flight* baseflights, char** massivgorodov,
		int* table0, int* table1, int* table2, int* table3, int* table4, int* table5, int* table6, int* table7,int* table8,char** massivplanes){
	if (matchingProperties[0]==1) popadaetPoGorodamFrom(matchingFlights, baseflights,massivgorodov, table0);
        if (matchingProperties[1]==1) popadaetPoGorodamTo(matchingFlights, baseflights,massivgorodov, table1);
        if (matchingProperties[2]==1) popadaetPoDay(matchingFlights, baseflights, table2);
        if (matchingProperties[3]==1) popadaetPoMonth(matchingFlights, baseflights, table3);
        if (matchingProperties[4]==1) popadaetPoYear(matchingFlights, baseflights, table4);
        if (matchingProperties[5]==1) popadaetPoFreemest(matchingFlights, baseflights, table5);
        if (matchingProperties[6]==1) popadaetPoPrice(matchingFlights, baseflights, table6);
        if (matchingProperties[8]==1) popadaetPoPlane(matchingFlights, baseflights, table8,massivplanes);

        if (matchingProperties[7]==1) {wantToBuy(matchingFlights, baseflights, table7);}
	




}
//----------------------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------------------
int main(){

    printf("HELLO \n");
    int i=0;
    int j=0;
    
    //changelistgoroda();
    //amountgoroda();
    
    
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
    

    FILE*f;
    f=fopen("generalzapros.txt","r");
    if (f==0) {printf("Cannot open generalzapros.txt");}

    int matchingProperties[Nproperties];
    for (i=0; i<Nproperties; i=i+1){matchingProperties[i]=0;}
    

    int table0[Ngorodov]; for(i=0; i<Ngorodov; i=i+1){table0[i]=1;} 	//from
    int table1[Ngorodov]; for(i=0; i<Ngorodov; i=i+1){table1[i]=1;}  	//to
    int table2[2];   table2[0]=0;    table2[1]=29;    			//day
    int table3[2];   table3[0]=0;    table3[1]=12;  			//month
    int table4[2];   table4[0]=2019; table4[1]=2019;  			//year
    int table5[2];   table5[0]=0;    table5[1]=1000;  			//freemest
    int table6[2];   table6[0]=0;    table6[1]=1000;   			//price
    int  table7[1];  table7[0]=0;					//buy
    int table8[Nplanes]; for(i=0; i<Nplanes; i=i+1){table8[i]=1;}	//plane

    createZaprosFromFile(f, massivproperties, massivgorodov, matchingProperties, table0, table1, table2, table3, table4, table5, table6, table7,table8,massivplanes);
    fclose(f);

    int matchingFlights[Nflights]; for(i=0; i<Nflights; i=i+1){matchingFlights[i]=1;}
    selectPoZaprosu(matchingFlights, matchingProperties, baseflights,massivgorodov, table0, table1, table2, table3, table4, table5, table6, table7,table8,massivplanes);

    
    
    FILE*otvetfile;
    otvetfile=fopen("otvetNaGeneralZapros.txt","w");
    for (i=0; i<Nflights; i=i+1){if (matchingFlights[i]==1){printf("good i=%d\n",i);baseflights[i].pechatvfile(otvetfile);}}
    fprintf(otvetfile,"#");
    fclose(otvetfile);
    

    for (i=0; i<Nplanes; i=i+1){free(massivplanes[i]);}
    for (i=0; i<Ngorodov; i=i+1){free(massivgorodov[i]);}
    for (i=0; i<Nproperties; i=i+1){free(massivproperties[i]);}
    
    //printf("\n size of Flight=%ld\n",sizeof(Flight));
    printf("GOODBYE\n");
    return 0;


}