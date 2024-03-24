#include<stdio.h>
#include<stdlib.h>

int is_prime(int n){
    if (n==1){return 0;}
    int otv=1;
    for (int d=2; d*d<=n; d=d+1){
        if (n%d==0){otv=0; break;}
    }
    return otv;
        
}

void pechat(int n){
    for (int d=2; d<=n; d=d+1){
        if (n%d==0 && is_prime(d)){
            printf("%d ",d);
            pechat(n/d);
            break;
        }
    }
}

int main(void){
    
    int n;
    scanf("%d",&n);
    pechat(n);
    printf("\n");
    
	
    return 0;
}
