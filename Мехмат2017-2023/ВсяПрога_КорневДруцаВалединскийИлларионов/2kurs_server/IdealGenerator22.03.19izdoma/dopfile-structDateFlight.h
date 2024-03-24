
#include <stdio.h>
#include <stdlib.h>

class Date;
class Flight;
void  find_po_date(Flight* baseflights, int* goodindexes,Date* date1, Date* date2);
//--------------------------------------------------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------------
class  Date{
    friend class Flight;
    friend void  find_po_date(Flight* baseflights, int* goodindexes,Date* date1,Date* date2);
    friend void  otvet_na_zapros(FILE*f,Flight* baseflights,char** massivgorodov);
    friend int  popadaet_po_date(int j,Flight* baseflights,Date* date1,Date* date2);
    friend int popadaet_po_gorodyfrom(char** massivgorodov, int* goodgoroda,char* tekgorod);
    friend int popadaet_po_gorodyto(char** massivgorodov, int* goodgoroda,char* tekgorod);

    friend void popadaetPoGorodamFrom(int* matchingFlights, Flight* baseflights, char** massivgorodov,int* table);
    friend void popadaetPoGorodamTo(int* matchingFlights, Flight* baseflights, char** massivgorodov,int* table);
    friend void popadaetPoDay(int* matchingFlights, Flight* baseflights, int* table);
    friend void popadaetPoMonth(int* matchingFlights, Flight* baseflights, int* table);
    friend void popadaetPoYear(int* matchingFlights, Flight* baseflights, int* table);
    friend void popadaetPoFreemest(int* matchingFlights, Flight* baseflights, int* table);
    friend void popadaetPoPrice(int* matchingFlights, Flight* baseflights, int* table);
    friend void wantToBuy(int* matchingFlights, Flight* baseflights, int* table);
    friend void popadaetPoPlane(int* matchingFlights, Flight* baseflights, int* table,char** massivplanes);
    
    private:
	int day;
	int month;
	int year;
    public:
	Date(){}
	void Set(int tekday,int tekmonth,int tekyear){day=tekday;month=tekmonth;year=tekyear;}
	void pechat(){printf("day=%d  month=%d  year=%d  ", day,month,year);}
	void pechatvfile(FILE*f){fprintf(f," day=%d  month=%d year=%d  ", day,month,year);}
	


};


//---------------------------------------------------------------------------------------------------------------------------------------------------
class Flight{
    friend class Date;
    friend void  find_po_date(Flight* baseflights, int* goodindexes,Date* date1, Date* date2);
    friend void  otvet_na_zapros(FILE*f,Flight* baseflights,char** massivgorodov);
    friend int  popadaet_po_date(int j,Flight* baseflights,Date* date1,Date* date2);
    friend int popadaet_po_gorodyfrom(char** massivgorodov, int* goodgoroda,char* tekgorod);
    friend int popadaet_po_gorodyto(char** massivgorodov, int* goodgoroda,char* tekgorod);

    friend void popadaetPoGorodamFrom(int* matchingFlights, Flight* baseflights, char** massivgorodov,int* table);
    friend void popadaetPoGorodamTo(int* matchingFlights, Flight* baseflights, char** massivgorodov,int* table);
    friend void popadaetPoDay(int* matchingFlights, Flight* baseflights, int* table);
    friend void popadaetPoMonth(int* matchingFlights, Flight* baseflights, int* table);
    friend void popadaetPoYear(int* matchingFlights, Flight* baseflights, int* table);
    friend void popadaetPoFreemest(int* matchingFlights, Flight* baseflights, int* table);
    friend void popadaetPoPrice(int* matchingFlights, Flight* baseflights, int* table);
    friend void wantToBuy(int* matchingFlights, Flight* baseflights, int* table);
    friend void popadaetPoPlane(int* matchingFlights, Flight* baseflights, int* table,char** massivplanes);




    private:
	char* from;
	char* to;
	char* plane;
	int maxmest;
	int freemest;
	Date date;
	int price;
	
    public:
	Flight(){}
	void Set(char* tekfrom,char* tekto,char* tekplane,int tekmaxmest,int tekfreemest,Date tekdate,int tekprice){
	                    from = new char[strlen(tekfrom)+1]; strcpy(from,tekfrom);
                            to = new char[strlen(tekto)+1]; strcpy(to,tekto);
			    plane = new char[strlen(tekplane)+1]; strcpy(plane,tekplane);
			    
			    maxmest=tekmaxmest;
			    freemest=tekfreemest;
			    date=tekdate;
			    price=tekprice;
			    }
	~Flight(){free(from);free(to);free(plane);}
	void pechat(){printf("\n from %s   to %s   plane %s   maxmest=%d   freemest=%d ", from,to,plane,maxmest,freemest);date.pechat(); printf("price=%d  ",price);}
	void pechatvfile(FILE*f){
			    fprintf(f,"\n from %s   to %s   plane %s   maxmest=%d  freemest=%d  ", from,to,plane,maxmest,freemest);
			    date.pechatvfile(f);
			    fprintf(f,"price=%d ",price);
			    }

};

//-----------------------------------------------------------------------------------------------------------------------------------------------