#include<stdio.h>
#include<stdlib.h>

int get_sum(int n){
    if (n/10==0){return n;}
    else {return n%10+get_sum(n/10);}
}

int main(void){
    
    int n;
    scanf("%d",&n);
    int otv=get_sum(n);
    printf("%d\n",otv);
	
    return 0;
}
