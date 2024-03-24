#include<stdio.h>
#include<stdlib.h>

int is_prime(int n, int delitel){
    if (n==1){return 0;}
    if (delitel==n){return 1;}
    else {return (n%delitel!=0)&&is_prime(n, delitel+1);}
}

int main(void){
    
    int n;
    scanf("%d",&n);
    int otv=is_prime(n,2);
    if (otv==1){printf("YES\n");}
    else{printf("NO\n");}
	
    return 0;
}
