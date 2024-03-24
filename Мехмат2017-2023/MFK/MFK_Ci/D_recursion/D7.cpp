#include<stdio.h>
#include<stdlib.h>

void pechat(int n){
    if (n==1){printf("%d ",n);}
    else{printf("%d ",n); pechat(n-1);}
}

int main(void){
    
    int n;
    scanf("%d",&n);
    pechat(n);
    printf("\n");
	
    return 0;
}
