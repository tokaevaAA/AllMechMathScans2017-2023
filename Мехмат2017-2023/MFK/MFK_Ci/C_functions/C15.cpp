#include<stdio.h>
#include<stdlib.h>
#include <math.h>

int grow_up(int n){
    if (n/10==0){return 1;}
    int otv=1;
    int prev=n%10;
    n=n/10;
    while(n!=0){
        if (n%10 >= prev){return 0;}
        prev=n%10;
        n=n/10;
    }
    
    return otv;
    
}
int main(void){
    int n;
    scanf("%d",&n);
    int otv=grow_up(n);
    if (otv==1){printf("YES\n");}
    else{printf("NO\n");}
    
    
    
	
    return 0;
}
