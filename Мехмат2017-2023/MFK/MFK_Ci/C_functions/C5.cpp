#include<stdio.h>
#include<stdlib.h>

int get_sum(int N){
    int otv=0;
    for (int i=1; i<=N; i=i+1){otv+=i;}
    return otv;
}
int main(void){

    int N;
    scanf("%d",&N);
    int otv=get_sum(N);
    printf("%d\n",otv);
    
	
    return 0;
}
