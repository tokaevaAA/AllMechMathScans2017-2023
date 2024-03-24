#include<stdio.h>
#include<stdlib.h>

int main(void){

    int N;
    scanf("%d",&N);
    int tek_digit;
    
    if(N==0){printf("%d\n",0); return 0;}
    while(N!=0){tek_digit=N%10;
                printf("%d",tek_digit);
                N=N/10;
                }
    printf("\n");
    
	
    return 0;
}
