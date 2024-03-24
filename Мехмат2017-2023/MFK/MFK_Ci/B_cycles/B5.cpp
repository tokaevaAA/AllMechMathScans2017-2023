#include<stdio.h>
#include<stdlib.h>

int main(void){

    int N;
    scanf("%d",&N);
    int sum=0;
    while(N!=0){sum=sum+N%10; N=N/10;}
    printf("%d\n",sum);
	
    return 0;
}