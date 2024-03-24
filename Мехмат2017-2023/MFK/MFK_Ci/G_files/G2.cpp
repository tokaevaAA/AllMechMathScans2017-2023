#include <stdio.h>
#include <stdlib.h>





int main(void){
    
    FILE* fout=fopen("output.txt","w");
    FILE* fin=fopen("input.txt","r");
    if (fin==0){printf("Cannot open input.txt\n");}
    int n;
    fscanf(fin,"%d",&n);
    int j=0;
    int mas[4]={2,4,6,8};
    for (int i=0; i<n/2; i=i+1){
        fprintf(fout,"%c",'A'+i);
        fprintf(fout,"%d",mas[j]);
        j=(j+1)%4;
    }
    fclose(fin);
    fclose(fout);
    
    
    return 0;
}

