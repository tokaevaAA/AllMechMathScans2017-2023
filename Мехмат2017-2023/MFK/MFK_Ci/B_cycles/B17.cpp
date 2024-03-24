#include<stdio.h>
#include<stdlib.h>


int main(void){
    
    double sum=1;
    int n=2;
    while ( 2*(n-1)/((2*n-1)*pow(3,n-1)) >= 0.001){
        sum+=pow(-1,n)*(2*(n-1))/((2*n-1)*pow(3,n-1));
        n+=1;
    }
    printf("%0.3f\n",sum);
    
    
	
    return 0;
}
