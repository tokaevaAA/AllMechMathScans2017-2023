#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int is_happy_number(int n){
    int sum=0;
    int proizv=1;
    while (n!=0){
        sum+=n%10;
        proizv*=n%10;
        n=n/10;
    }
    int otv;
    if (sum==proizv){otv=1;}
    else {otv=0;}
    return otv;
    
}
int main(void){
    int n;
    scanf("%d",&n);
    int otv=is_happy_number(n);
    if (otv==1){printf("YES\n");}
    else{printf("NO\n");}
    
    
    
	
    return 0;
}
