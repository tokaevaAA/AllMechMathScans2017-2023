#include<stdio.h>
#include<stdlib.h>

unsigned long long get_wheat(int N){
    unsigned long long otv=pow(2,N-1);
    return otv;
}
int main(void){

    int N;
    scanf("%d",&N);
    unsigned long long otv=get_wheat(N);
    printf("%llu\n",otv);
    
	
    return 0;
}
