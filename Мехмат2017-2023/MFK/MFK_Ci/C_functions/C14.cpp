#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int check_sum_digits(int n){
    int otv=0;
    while (n!=0){
        otv+=n%10;
        n=n/10;
        otv=otv%2;
    }
    return otv;
    
}
int main(void){
    int n;
    scanf("%d",&n);
    int otv=check_sum_digits(n);
    if (otv==1){printf("NO\n");}
    else{printf("YES\n");}
    
    
    
	
    return 0;
}
