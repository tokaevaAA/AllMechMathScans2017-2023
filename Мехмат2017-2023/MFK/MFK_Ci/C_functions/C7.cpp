#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void change_base(int N, int p){
    if (N==0){printf("0\n"); return;}
    int cnt_digits=log10(N)/log10(p)+1;
    int* chislo_in_p_reversed=(int*)(malloc(cnt_digits*sizeof(int)));
    int i=0;
    while (N!=0){chislo_in_p_reversed[i]=N%p; N=N/p; i=i+1;}
    for(int j=cnt_digits-1; j>=0; j=j-1){printf("%d",chislo_in_p_reversed[j]);}
    printf("\n");
    free(chislo_in_p_reversed);
    
}

int main(void){

    int N;
    int p;
    scanf("%d%d",&N,&p);
    change_base(N,p);
    
    
    
	
    return 0;
}
