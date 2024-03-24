#define Nplanes 7
#define Ngorodov 154
#define Nflights 155
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
