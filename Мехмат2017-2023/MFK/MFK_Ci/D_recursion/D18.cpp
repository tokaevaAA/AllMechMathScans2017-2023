#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void print_even_digits(int n){
    if (n!=0){
        print_even_digits(n/10);
        if ((n%10)%2==0) {printf("%d ",n%10);}
    }
}
int main(void){
    int n;
    scanf("%d",&n);
    print_even_digits(n);
    printf("\n");
	
    return 0;
}
