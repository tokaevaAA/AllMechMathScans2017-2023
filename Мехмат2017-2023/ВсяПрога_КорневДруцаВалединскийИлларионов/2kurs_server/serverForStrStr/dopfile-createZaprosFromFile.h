
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//-------------------------------------------------------------------------------------
void createZaprosFromFile(FILE*f, char** massivproperties,char** massivgorodov, int* matchingProperties,
		int* table0, int* table1, int* table2, int* table3, int* table4, int* table5, int* table6, int* table7,int* table8,char** massivplanes){
    int filenepust;
    int a;
    int i=0; int j=0; int k=0;
    char tekslovo[20];



   char teksymbol;
    char buf[128]; 
     k=fscanf(f,"%c",&teksymbol);
    while(k==1){buf[i]=teksymbol; i=i+1; k=fscanf(f,"%c",&teksymbol);}
    printf("START BUF\n");
    for(i=0; i<128;i=i+1){printf("%c",buf[i]);}
    printf("END BUF\n");
    printf("\n");
    

    char* pos;
    for(i=0;i<Nproperties;i=i+1){pos=strstr(buf,massivproperties[i]);
				 if (pos!=0){matchingProperties[i]=1;
                                            printf("mproperty %s\n",massivproperties[i]);
									      
					    }
				}

    for(i=0;i<Nproperties;i=i+1){if (matchingProperties[i]==1) printf("propi=%d\n",i);}

 
   //we have created a table of properties existing in the current zapros
   //properties: from(0) to(1) day(2) month(3) year(4) freemest(5) price(6) registrate(7)

    
 
    

    

    if(matchingProperties[0]==1) {
	     printf("case=0\n");
	     for(j=0; j<Ngorodov; j=j+1){table0[j]=0;}
	     char tekgorod[20];
	     pos=strstr(buf,"from");										  
	     sscanf(pos+4,"%d",&a);
	     int sdvig=0;
	     for(j=0; j<a; j=j+1){sscanf(pos+6+sdvig,"%s",tekgorod);
				  sdvig=sdvig+int(strlen(tekgorod))+1;
				  //printf("tekgorod=%s\n",tekgorod);
				  for(k=0;k<Ngorodov; k=k+1){
							     if (strcmp(tekgorod,massivgorodov[k])==0){table0[k]=1;
                       										       //printf("goodgorod %s\n",tekgorod);
												       }
							     }
				 }
		}

     if(matchingProperties[1]==1) {
	     printf("case=1\n");
	     for(j=0; j<Ngorodov; j=j+1){table1[j]=0;}
	     char tekgorod[20];
	     pos=strstr(buf,"to");										  
	     sscanf(pos+2,"%d",&a);
	     int sdvig=0;
	     for(j=0; j<a; j=j+1){sscanf(pos+4+sdvig,"%s",tekgorod);
				  sdvig=sdvig+int(strlen(tekgorod))+1;
				  //printf("tekgorod=%s\n",tekgorod);
				  for(k=0;k<Ngorodov; k=k+1){
							     if (strcmp(tekgorod,massivgorodov[k])==0){table1[k]=1;
                       										       //printf("goodgorod %s\n",tekgorod);
												       }
							     }
				 }
		}
        

         if(matchingProperties[2]==1) {
	     printf("case=2\n");
	     pos=strstr(buf,"day");										  
	     sscanf(pos+3,"%d %d ",&table2[0],&table2[1]);
				      }
         if(matchingProperties[3]==1) {
	     printf("case=3\n");
	     pos=strstr(buf,"month");										  
	     sscanf(pos+5,"%d %d ",&table3[0],&table3[1]);
				      }
         

        if(matchingProperties[4]==1) {
	     printf("case=4\n");
	     pos=strstr(buf,"year");										  
	     sscanf(pos+4,"%d %d ",&table4[0],&table4[1]);
				      }
        if(matchingProperties[5]==1) {
	     printf("case=5\n");
	     pos=strstr(buf,"freemest");										  
	     sscanf(pos+8,"%d %d ",&table5[0],&table5[1]);
				      }

         if(matchingProperties[6]==1) {
	     printf("case=6\n");
	     pos=strstr(buf,"price");										  
	     sscanf(pos+5,"%d %d ",&table6[0],&table6[1]);
				      }


        if(matchingProperties[7]==1) { table7[0]=1;}
      


       if(matchingProperties[8]==1) {
	     printf("case=8\n");
	     for(j=0; j<Nplanes; j=j+1){table8[j]=0;}
	     char tekplane[20];
	     pos=strstr(buf,"plane");										  
	     sscanf(pos+5,"%d",&a);
	     int sdvig=0;
	     for(j=0; j<a; j=j+1){sscanf(pos+7+sdvig,"%s",tekplane);
				  sdvig=sdvig+int(strlen(tekplane))+1;
				  //printf("tekplane=%s\n",tekplane);
				  for(k=0;k<Nplanes; k=k+1){
							     if (strcmp(tekplane,massivplanes[k])==0){table8[k]=1;
                       										       //printf("matching plane:%s\n",massivplanes[k]);

												       }
							     }
				 }
		}

											
												  

                 									
 											
                 									
                 									

}
