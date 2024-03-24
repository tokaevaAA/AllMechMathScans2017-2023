#include<stdio.h>
#include<stdlib.h>

int get_power(int N, int p){
    return pow(N,p);
}
int main(void){

    int N;
    int p;
    scanf("%d %d",&N,&p);
    int otv=get_power(N,p);
    printf("%d\n",otv);
    
	
    return 0;
}
