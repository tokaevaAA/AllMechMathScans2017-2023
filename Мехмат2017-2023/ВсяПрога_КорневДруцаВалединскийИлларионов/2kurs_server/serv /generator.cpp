#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Nplanes 7
#define Ngorodov 168
#define Nflights 10
#define Ngorodovfrom 168
#define Ngorodovto 168

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

int amountgoroda(){
    FILE*f;
    f=fopen("onlygoroda.txt","r");
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
//--------------------------------------------------------------------------------------------------------------------------------------------------



void changelistgoroda(){
    FILE*f;
    FILE*g;
    f=fopen("input.txt","r");
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

//-----------------------------------------------------------------------------------------------------------------------------------------------------

int   getmasofplanes(char** massivplanes,int* massivmest){
    
    FILE*f;
    f=fopen("planes.txt","r");
    if (f==0){printf("Cannot open planes.txt");return -1; }
    
    
    
    rewind(f);
    int i=0;
    char  tekslovo[20];  //slovo of 20 symbols
    int tekchislo;
    
    for(i=0;i<2*Nplanes;i++)
    {

      if (i%2 ==0){fscanf(f,"%s",tekslovo);
    		    massivplanes[i/2] = new char[strlen(tekslovo)+1];
    		     strcpy(massivplanes[i/2],tekslovo);
    		     //printf("plane=%s\n",massivplanes[i/2]);
    		     }
    else if (i%2 ==1){fscanf(f,"%d",&tekchislo);
    		    massivmest[i/2] = tekchislo;
    		    //printf("seats=%d\n",massivmest[i/2]);
    		    }
    
    }
    
    
    fclose(f);
    return 0;


}
//-----------------------------------------------------------------------------------------------------------------------------------------------------



int  getmasofgorodov(char** massivgorodov){
    
    FILE*f;
    f=fopen("onlygoroda.txt","r");
    if (f==0){printf("Cannot open planes.txt");return -1; }
    
    
    
    rewind(f);
    int i=0;
    char  tekslovo[20];  //slovo of 20 symbols
    
    for(i=0;i<Ngorodov;i++)
    {

	fscanf(f,"%s",tekslovo);
	massivgorodov[i] = new char[strlen(tekslovo)+1];
	strcpy(massivgorodov[i],tekslovo);
	//printf("gorod=%s\n",massivgorodov[i]);
    }
    
    
    fclose(f);
    return 0;


}

//------------------------------------------------------------------------------------------------------------------------------------------------------





void getbase(Flight* baseflights, char** massivgorodov, char** massivplanes,int* massivmest){
    int j=0;
    for(j=0;j<Nflights;j=j+1){
    
	int a1 = rand() %Ngorodov;
	int a2 = rand() %Ngorodov;
	int b = rand() %Nplanes;
	int c1=1+ rand()%30;
	int c2=rand()%12;
	int c3=2019;
	int d=rand()%1000;
	Date tekdate;
	tekdate.Set(c1,c2,c3);
	//printf("a1= %d a2=%d  b=%d \n",a1,a2,b);
	baseflights[j].Set(massivgorodov[a1],massivgorodov[a2],massivplanes[b],massivmest[b],massivmest[b],tekdate,d);
    }


}

//----------------------------------------------------------------------------------------------------------------------------------------------------

void  find_po_date(Flight* baseflights, int* goodindexes,Date* date1,Date* date2){
    int j=0;
    for (j=0;j<Nflights;j=j+1){if ( (baseflights[j].date.day >= date1->day) &&(baseflights[j].date.day <= date2->day) &&
				    (baseflights[j].date.month >= date1->month)&&(baseflights[j].date.month <= date2->month)) {goodindexes[j]=1;}
			      }

}


//---------------------------------------------------------------------------------------------------------------------------------------------------

int  popadaet_po_date(int j,Flight* baseflights,Date* date1,Date* date2){
    
    int otv=0;
    if ( (baseflights[j].date.day >= date1->day) &&(baseflights[j].date.day <= date2->day) &&
				    (baseflights[j].date.month >= date1->month)&&(baseflights[j].date.month <= date2->month)) {otv=1;}
			
    return otv;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------
int popadaet_po_gorodyfrom(char**massivgorodov, int* goodgoroda,char* tekgorod){
    //printf("888\n");
    //printf("tekgorod=%s\n",tekgorod);
    //printf(" %s %s %s\n",[88].from,baseflights[89].from,baseflights[90].from);
    int i=0;
    int otv=0;
    for (i=0; i<Ngorodovfrom;i=i+1){if((goodgoroda[i]==1)&&(strcmp(massivgorodov[i],tekgorod)==0)){otv=1;}}
    //printf("999\n");
    return otv;



}

//--------------------------------------------------------------------------------------------------------------------------------------------------
int popadaet_po_gorodyto(char** massivgorodov, int* goodgoroda,char* tekgorod){
    int i=0; 
    int otv=0;
    for (i=0; i<Ngorodovto;i=i+1){if((goodgoroda[i]==1)&&(strcmp(massivgorodov[i],tekgorod)==0)){otv=1;}}
    return otv;



}
//---------------------------------------------------------------------------------------------------------------------------------------------------
void pechatpomassivu(Flight* baseflights,int length, int* mas){
    int i=0;
    for (i=0;i<length;i=i+1){if(mas[i]==1){baseflights[i].pechat();}}
    printf("\n");
    

}

//-------------------------------------------------------------------------------------------------------------------------------------------------------
void  otvet_na_zapros(FILE*f,Flight* baseflights,char** massivgorodov){
    int estzapros=0;
    

    char tekslovo[30];
    estzapros=fscanf(f,"%s",tekslovo);
    printf("tekslovo=%s\n",tekslovo);
    while(estzapros==1){
		if (strcmp(tekslovo,"findpodate")==0) {printf("findpodate\n");
					     int i=0;
					     int a1,a2,a3,b1,b2,b3;
					     fscanf(f,"%d %d %d",&a1,&a2,&a3); fscanf(f,"%d %d %d",&b1,&b2,&b3);
					     Date date1; Date date2; date1.Set(a1,a2,a3); date2.Set(b1,b2,b3);
					    // date1.pechat(); date2.pechat();
					     
					     int goodindexes[Nflights];
					     for(i=0;i<Nflights;i=i+1) {goodindexes[i]=0;if (popadaet_po_date(i,baseflights,&date1,&date2)==1){goodindexes[i]=1;}}
    
					     //find_po_date(baseflights,goodindexes,&date1,&date2);
					     pechatpomassivu(baseflights,Nflights,goodindexes);
     
					    }
		if (strcmp(tekslovo,"findpogorodam")==0){printf("findpogorodam\n");
							 int i=0; int j=0; 
							 //int k=0;
							 int a1; int a2;
							 char tekgorod[20];
							 fscanf(f,"%d",&a1);
							 //printf("a1=%d\n",a1);
							 int gorodafrom[Ngorodov]; for(i=0;i<Ngorodov;i=i+1){gorodafrom[i]=0; }
							 int gorodato[Ngorodov];   for(i=0;i<Ngorodov;i=i+1){gorodato[i]=0; }
							 
							 for(i=0;i<a1;i=i+1){fscanf(f,"%s",tekgorod);
									     for(j=0;j<Ngorodov;j=j+1){if(strcmp(massivgorodov[j],tekgorod)==0){gorodafrom[j]=1;}}
									     }
							 
							 for(i=0; i<Ngorodov; i=i+1){if(gorodafrom[i]==1){printf("%s ",massivgorodov[i]);}}
							 printf("\n");
							 
							 fscanf(f,"%d",&a2);
							 for(i=0;i<a2;i=i+1){fscanf(f,"%s",tekgorod);
									     for(j=0;j<Ngorodov;j=j+1){if(strcmp(massivgorodov[j],tekgorod)==0){gorodato[j]=1;}}
									     }
							 for(i=0; i<Ngorodov; i=i+1){if(gorodato[i]==1){printf("%s ",massivgorodov[i]);}}
							 printf("\n");
							 
							 /*
							 int k=0;
							 for (i=0; i<Nflights; i=i+1){for (j=0;j<Ngorodovfrom;j=j+1){if ((gorodafrom[j]==1)&&(strcmp(massivgorodov[j],baseflights[i].from)==0)){for(k=0; k<Ngorodovto;k=k+1){if ((gorodato[k]==1)&&(strcmp(massivgorodov[k],baseflights[i].to)==0)){baseflights[i].pechat();}
																											    }
																							       }
														    }
										     }
							*/
							
							
							printf("%s\n",massivgorodov[80]);
							for(i=0;i<Nflights; i=i+1){printf("I=%d ",i);if((popadaet_po_gorodyfrom(massivgorodov,gorodafrom,baseflights[i].from)==1)&&
										      (popadaet_po_gorodyto(massivgorodov,gorodato,baseflights[i].to)==1)){baseflights[i].pechat();}
														  
										  }
							
							}
		
		estzapros=fscanf(f,"%s",tekslovo);
		printf("tekslovo=%s\n",tekslovo);
		}

}
//------------------------------------------------------------------------------------------------------------------------------------------------
int main(){

    printf("Hello \n");
    int i=0;
    int j=0;
    
    //changelistgoroda();
    //amountgoroda();
    
    
    char* massivplanes[Nplanes];
    int  massivmest[Nplanes];
    char* massivgorodov[Ngorodov];
    getmasofplanes(massivplanes,massivmest);
    getmasofgorodov(massivgorodov);
    
    //for (i=0; i<Nplanes; i=i+1){printf("plane=%s\n",massivplanes[i]);}
    //for (i=0; i<Nplanes; i=i+1){printf("all seats=%d\n",massivmest[i]);}
    //for (i=0; i<Ngorodov; i=i+1){printf("goroda=%s\n",massivgorodov[i]);}
    
    
    Flight baseflights[Nflights];
    getbase(baseflights,massivgorodov,massivplanes,massivmest);
    
    FILE* file_base;
    file_base=fopen("initialbase.txt","w");
    for(j=0;j<Nflights;j=j+1){baseflights[j].pechatvfile(file_base);}
    fclose(file_base);
    
    FILE*f;
    f=fopen("zapros.txt","r");
    otvet_na_zapros(f,baseflights,massivgorodov);
    fclose(f);
    /*
    int goodindexes[Nflights];
    for(i=0;i<Nflights;i=i+1) {goodindexes[i]=0;}
    Date date1;
    Date date2;
    date1.Set(1,1,2019);
    date2.Set(28,3,2019);
    find_po_date(baseflights,goodindexes,&date1,&date2);
    pechatpomassivu(baseflights,Nflights,goodindexes);
    */
    
    for (i=0; i<Nplanes; i=i+1){free(massivplanes[i]);}
    for (i=0; i<Ngorodov; i=i+1){free(massivgorodov[i]);}
    
    printf("\n size of Flight=%ld\n",sizeof(Flight));
    printf("Goodbye\n");
    return 0;


}