#include <stdio.h>
#include <stdlib.h>





int main(void){
    
    FILE* fout=fopen("output.txt","w");
    FILE* fin=fopen("input.txt","r");
    
    
    char mas[100];
    char c;
    int cnt=0;
    while(fscanf(fin,"%c",&c)==1 && c!=EOF && c!='\n'){
        mas[cnt]=c;
        cnt+=1;
        fprintf(fout,"%c",c);
    }
    for (int i=0; i<2; i=i+1){
        fprintf(fout,", ");
        for (int p=0; p<cnt; p=p+1){
            fprintf(fout,"%c",mas[p]);
        }
    }
    fprintf(fout," %d",cnt);
    fclose(fin);
    fclose(fout);
    
    
    return 0;
}

