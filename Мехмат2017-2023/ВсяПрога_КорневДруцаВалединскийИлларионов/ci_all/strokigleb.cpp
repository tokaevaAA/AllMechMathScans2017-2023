#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void pechat(char* a, int n){
    //printf("start pechat\n");
    int i=0;
    for(i=0; i<n; i=i+1) printf("%c", a[i]);
    printf("\n");
    //printf("end pechat\n");
    }

void pechatfile(FILE*g, char* a, int n){
    printf("pechatfile\n");
    fprintf(g,"1");
    int i=0;
    for(i=0; i<n; i=i+1) fprintf(g,"%c", a[i]);
    fprintf(g,"1");
    }


char* readbe(FILE*f, int* lengthB){
    int k;
    char* B = (char*)malloc(0*(sizeof(char)));
    char tekchar=0;
    k=fscanf(f,"%c", &tekchar);

    while (k==1){
        //petite(B, *lengthB);
        if (strncmp(&tekchar, " ",1) == 0) break;
        if (strncmp(&tekchar, "\n",1) == 0) break;
        B = (char*)realloc(B, *lengthB +1);
        B[*lengthB] = tekchar;
        *lengthB = *lengthB +1;
        fscanf(f, "%c", &tekchar);
        }
    return B;
    }


char* readword(FILE*f, int* lengthB, char dobavka){
    int k;
    char* B = (char*)malloc(0*(sizeof(char)));
    
    B = (char*)realloc(B, *lengthB +1);
    B[*lengthB] = dobavka;
    *lengthB = *lengthB +1;

    //if (strncmp(&dobavka, " ",1) == 0){return B;}
    if (strncmp(&dobavka, "\n",1) == 0) {return B;}

 
    char tekchar=0;
    k=fscanf(f,"%c", &tekchar);

    while (k==1){

  
        B = (char*)realloc(B, *lengthB +1);
        B[*lengthB] = tekchar;
        *lengthB = *lengthB +1;

        //if (strncmp(&tekchar, " ",1) == 0){break;}
        if (strncmp(&tekchar, "\n",1) == 0) {break;}


 

 
 
         k=fscanf(f, "%c", &tekchar);
        }
    return B;
    }
    


int main(void){
    
    FILE*f;
    f = fopen("input.txt", "r");
    if (f==0) {printf("Cannot open input.txt"); return -1;}

    FILE*g;
    g = fopen("output.txt", "w");


    int lengthB = 0;
    int lengthE = 0;
    int lengthword = 0;
    int lenbuf =0;

    char* B = readbe(f, &lengthB);
    char* E = readbe(f, &lengthE);
    char* buf = (char*)malloc(0*sizeof(char));
    
    pechat(B, lengthB);
    pechat(E, lengthE);

    //printf("%d %d\n", lengthB, lengthE);
    
    int k;
    int vnutri=0;
    char dobavka;
    char* tekword;
    k = fscanf(f, "%c", &dobavka);
    while (k==1) {
        tekword = readword(f,&lengthword, dobavka);
        pechat(tekword, lengthword);
        pechatfile(g,tekword,lengthword);
        lengthword =0;
        k= fscanf(f,"%c", &dobavka);

       }
   
    return 1;
    



}
