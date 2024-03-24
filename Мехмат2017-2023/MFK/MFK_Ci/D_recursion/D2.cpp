#include<stdio.h>
#include<stdlib.h>

int get_sum(int n){
    if (n==1) {return 1;}
    else {return n+get_sum(n-1);}
}

int main(void){
    int n;
    scanf("%d",&n);
    int otv=get_sum(n);
    printf("%d\n",otv);
	
    return 0;
}
