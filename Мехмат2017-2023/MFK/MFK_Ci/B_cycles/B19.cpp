#include<stdio.h>
#include<stdlib.h>


int main(void){
    
    int N;
    scanf("%d",&N);
    int sum=0;
    while(N!=0){sum+=N%10; N=N/10;}
    if (sum==10){printf("YES\n");}
    else{printf("NO\n");}
    
    
    
	
    return 0;
}
