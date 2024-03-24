#include<stdio.h>
#include<stdlib.h>

unsigned long int  factorial(unsigned long int n){
    if (n==0 || n==1){return 1;}
    else return n*factorial(n-1);
}

int main(void){
    unsigned long int  n;
    scanf("%lu",&n);
    unsigned long otv=factorial(n);
    printf("%lu\n",otv);
    
    
    
    
	
    return 0;
}
