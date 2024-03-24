#include<stdio.h>
#include<stdlib.h>

int main(void){

    int N;
    scanf("%d",&N);
    for(int i=1; i<=N; i=i+1){printf("%d %d %d\n",i,i*i,i*i*i);}
	
    return 0;
}