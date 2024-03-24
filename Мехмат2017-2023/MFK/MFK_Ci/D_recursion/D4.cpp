#include<stdio.h>
#include<stdlib.h>

void pechat_digits(int n){
    if (n/10==0) {printf("%d ",n);}
    else { pechat_digits(n/10); printf("%d ",n%10);  }
}

int main(void){
    int n;
    scanf("%d",&n);
    pechat_digits(n);
    printf("\n");
	
    return 0;
}
