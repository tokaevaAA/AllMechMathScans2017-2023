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
    int i=0;
    for(i=0; i<n; i=i+1) fprintf(g,"%c", a[i]);
    }




char* readbe(FILE*f, int* lengthB){
    int k;
    char* B = (char*)malloc(0*(sizeof(char)));
    char tekchar=0;
    k=fscanf(f,"%c", &tekchar);

    while (k==1){
        if (strncmp(&tekchar, " ",1) == 0) break;
        if (strncmp(&tekchar, "\n",1) == 0) break;
        B = (char*)realloc(B, *lengthB +1);
        B[*lengthB] = tekchar;
        *lengthB = *lengthB +1;
        fscanf(f, "%c", &tekchar);
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
    int lengthmas = 0;


    char* B = readbe(f, &lengthB);
    char* E = readbe(f, &lengthE);
    
    
    pechat(B, lengthB);
    pechat(E, lengthE);

    //printf("%d %d\n", lengthB, lengthE);

    int k;
    char tekchar;
    k = fscanf(f,"%c",&tekchar);
    int vnutri=0;
    
    int indb=0;
    int inde =0;

    char* buf = (char*)malloc(0*(sizeof(char)));
    int lenbuf=0;

    int i=0;

    
    while(k==1){
        if (vnutri==0){
            if (strncmp(&tekchar,&B[indb],1) != 0) {
                indb=0;
                pechatfile(g,buf,lenbuf);
                //pechat(buf,lenbuf);
                fprintf(g,"%c",tekchar);
                buf = (char*)realloc(buf,0);
                lenbuf=0;}
            
            if (strncmp(&tekchar,&B[indb],1) == 0) {
                indb = indb +1;
                buf = (char*)realloc(buf, lenbuf+1);
                buf[lenbuf] = tekchar;
                lenbuf=lenbuf+1;
                if (indb==lengthB){vnutri=1;indb =0;}}         }

        else if (vnutri==1){
            if (strncmp(&tekchar,&E[inde],1) !=0){
                inde = 0;
                buf = (char*)realloc(buf, lenbuf+1);
                buf[lenbuf] = tekchar;
                lenbuf=lenbuf+1;}
            if (strncmp(&tekchar,&E[inde],1)==0){
                inde=inde+1;
                buf = (char*)realloc(buf, lenbuf+1);
                buf[lenbuf] = tekchar;
                lenbuf=lenbuf+1;
                if(inde == lengthE){
                    inde=0;
                    //pechatfilemid(g,buf,lengthB,(lenbuf-lengthE));
                    buf = (char*)realloc(buf,0);
                    lenbuf =0;
                    vnutri=0;
                    }
                }
            }
                
    k=fscanf(f,"%c",&tekchar);
    }
    
    pechatfile(g, buf,lenbuf);
    fclose(f);
    fclose(g);
    free(B);
    free(E);
    free(buf);
    return 1;
    



}
