#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int is_prime(int n){
    if (n==0 || n==1){return 0;}
    int otv=1;
    for (int d=2; d*d<=n; d=d+1){
        if (n%d==0){return 0;}
    }
    
    return otv;
    
}
int main(void){
    int n;
    scanf("%d",&n);
    int otv=is_prime(n);
    if (otv==1){printf("YES\n");}
    else{printf("NO\n");}
    
    
    
	
    return 0;
}
