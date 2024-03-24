int   getmasofplanes(char** massivplanes,int* massivmest){
    
    FILE*f;
    f=fopen("dano-planes.txt","r");
    if (f==0){printf("Cannot open dano-planes.txt");return -1; }
    
    
    
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
    f=fopen("dano-onlygoroda.txt","r");
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
int  getproperties(char** massivproperties){
    
    FILE*f;
    f=fopen("dano-zaprosproperties.txt","r");
    if (f==0){printf("Cannot open dano-zaprosproperties.txt");return -1; }
    rewind(f);
    int i=0;
    char  tekslovo[20];  //slovo of 20 symbols
    
    for(i=0;i<Nproperties;i++)
    {

	fscanf(f,"%s",tekslovo);
	massivproperties[i] = new char[strlen(tekslovo)+1];
	strcpy(massivproperties[i],tekslovo);
	//printf("tekproperty=%s\n",massivproperties[i]);
    }
    
    
    fclose(f);
    return 0;


}




