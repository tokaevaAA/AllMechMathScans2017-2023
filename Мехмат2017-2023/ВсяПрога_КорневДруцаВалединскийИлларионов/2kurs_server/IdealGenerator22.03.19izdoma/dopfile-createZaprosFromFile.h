
#include<stdio.h>
#include<stdlib.h>


//-------------------------------------------------------------------------------------
void createZaprosFromFile(FILE*f, char** massivproperties,char** massivgorodov, int* matchingProperties,
		int* table0, int* table1, int* table2, int* table3, int* table4, int* table5, int* table6, int* table7,int* table8,char** massivplanes){
    int filenepust;
    int a;
    int i=0; int j=0; int k=0;
    

   
    char tekslovo[20];
    

    filenepust=fscanf(f,"%s",tekslovo);
    while(filenepust==1){
    
    for(i=0;i<Nproperties;i=i+1){if (strcmp(tekslovo,massivproperties[i])==0){matchingProperties[i]=1;
                                                                    	      printf("matching property %s\n",tekslovo);
									      
									     }
				}


    filenepust=fscanf(f,"%s",tekslovo);
    }
    rewind(f);
//we have created a table of properties existing in the current zapros
//properties: from(0) to(1) day(2) month(3) year(4) freemest(5) price(6) registrate(7)

    
 
    

    filenepust=fscanf(f,"%s",tekslovo);
    while(filenepust==1){
    for(i=0;i<Nproperties;i=i+1){if (strcmp(tekslovo,massivproperties[i])==0){//printf("i=%d\n",i); 
									      		if(i==0) {printf("case=0\n");
												  for(j=0; j<Ngorodov; j=j+1){table0[j]=0;}
												  char tekgorod[20];
												  rewind(f);
												  fscanf(f,"%s",tekgorod);
												  while ((strcmp(tekgorod,massivproperties[i])!=0)){
																fscanf(f,"%s",tekgorod);
																		    }
												  fscanf(f,"%d",&a);
												  for (j=0; j<a;j=j+1){fscanf(f,"%s",tekgorod);
															for(k=0;k<Ngorodov; k=k+1){
													if (strcmp(tekgorod,massivgorodov[k])==0){table0[k]=1;}
																		  }
														       }
												  

												 }
                 									if(i==1) {printf("case=1\n");
												  for(j=0; j<Ngorodov; j=j+1){table1[j]=0;}
												  char tekgorod[20];
												  rewind(f);
												  fscanf(f,"%s",tekgorod);
												  while ((strcmp(tekgorod,massivproperties[i])!=0)){
																fscanf(f,"%s",tekgorod);
																		    }

												  fscanf(f,"%d",&a);
												  
												  for (j=0; j<a;j=j+1){fscanf(f,"%s",tekgorod);
															for(k=0;k<Ngorodov; k=k+1){
													if (strcmp(tekgorod,massivgorodov[k])==0){table1[k]=1;}
																		  }
														       }
												 }
 											if(i==2) {printf("case=2\n"); 
 												  char tekgorod[20];
												  rewind(f);
												  fscanf(f,"%s",tekgorod);
												  while ((strcmp(tekgorod,massivproperties[i])!=0)){
																fscanf(f,"%s",tekgorod);
																		    }
												  fscanf(f,"%d",&table2[0]);fscanf(f,"%d",&table2[1]);}
                 									if(i==3) {printf("case=3\n");
                 										  char tekgorod[20];
												  rewind(f);
												  fscanf(f,"%s",tekgorod);
												  while ((strcmp(tekgorod,massivproperties[i])!=0)){
																fscanf(f,"%s",tekgorod);
																		    }
												  fscanf(f,"%d",&table3[0]);fscanf(f,"%d",&table3[1]);}
											if(i==4) {printf("case=4\n");
												  char tekgorod[20];
												  rewind(f);
												  fscanf(f,"%s",tekgorod);
												  while ((strcmp(tekgorod,massivproperties[i])!=0)){
																fscanf(f,"%s",tekgorod);
																		    }
												  fscanf(f,"%d",&table4[0]);fscanf(f,"%d",&table4[1]);}
                 									if(i==5) {printf("case=5\n");
                 										  char tekgorod[20];
												  rewind(f);
												  fscanf(f,"%s",tekgorod);
												  while ((strcmp(tekgorod,massivproperties[i])!=0)){
																fscanf(f,"%s",tekgorod);
																		    }
												  fscanf(f,"%d",&table5[0]);fscanf(f,"%d",&table5[1]);}
 											if(i==6) {printf("case=6\n");
 												  char tekgorod[20];
												  rewind(f);
												  fscanf(f,"%s",tekgorod);
												  while ((strcmp(tekgorod,massivproperties[i])!=0)){
																fscanf(f,"%s",tekgorod);
																		    }
												  fscanf(f,"%d",&table6[0]);fscanf(f,"%d",&table6[1]);}
                 									if(i==7) {printf("case=7\n");
                 										  char tekgorod[20];
												  rewind(f);
												  fscanf(f,"%s",tekgorod);
												  while ((strcmp(tekgorod,massivproperties[i])!=0)){
																fscanf(f,"%s",tekgorod);
																		    }
                 										  table7[0]=1;}
   											if(i==8) {printf("case=8\n");
												  for(j=0; j<Nplanes; j=j+1){table8[j]=0;}
												  char tekgorod[20];
												  rewind(f);
												  fscanf(f,"%s",tekgorod);
												  while ((strcmp(tekgorod,massivproperties[i])!=0)){
																fscanf(f,"%s",tekgorod);
																		    }
												  fscanf(f,"%d",&a); printf("amountplanes=%d\n",a);
												  char tekplane[20];
												  for(j=0;j<a;j=j+1){
														     fscanf(f,"%s",tekplane);
                          									  
									                 for(k=0; k<Nplanes; k=k+1){if (strcmp(tekplane,massivplanes[k])==0){printf("matching plane:%s\n",massivplanes[k]);table8[k]=1;}}
														    }

												  }

										       
									      
									     }
				}


    filenepust=fscanf(f,"%s",tekslovo);
    }





}
