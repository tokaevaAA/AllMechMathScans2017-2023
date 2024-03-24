#include <stdio.h>
#include <stdlib.h>





int main(void){
    
    FILE* fout=fopen("output.txt","w");
    FILE* fin=fopen("input.txt","r");
    if (fin==0){printf("Cannot open input.txt\n");}
    char tek;
    char prev;
    int cnt=0;
    while (fscanf(fin,"%c",&tek)==1 && tek!=EOF && tek!='\n'){
        prev=tek;
        cnt+=1;
    }
    //printf("prev=%c\n",prev);
    
    int new_cnt=0;
    int cnt_written=0;
    rewind(fin);
   
    while (fscanf(fin,"%c",&tek)==1 && tek!=EOF){
        if (tek==prev && new_cnt!=cnt-1){
            if (cnt_written==0){fprintf(fout,"%d", new_cnt);}
            else{fprintf(fout," %d", new_cnt);}
            cnt_written+=1;
        }
        new_cnt+=1;
        
    }
    fclose(fin);
    fclose(fout);
    
    
    return 0;
}

