#include<stdio.h>
#include<stdlib.h>

int check_if_prime(int n){
    int d=2;
    int otv=1;
    while (d*d<=n){
        if (n%d==0){otv=0; break;}
        d=d+1;
    }
    return otv;
}

void print_simple(int n){
    for (int d=2; d<=n; d=d+1){
        if (check_if_prime(d) && n%d==0){printf("%d ", d); print_simple(n/d); break;}
    }
}
int main(void){
    int n;
    scanf("%d",&n);
    print_simple(n);
    printf("\n");
    
    
    
	
    return 0;
}
