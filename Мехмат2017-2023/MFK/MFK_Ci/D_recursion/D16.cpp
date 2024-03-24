#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is2pow(int n){
    if (n==1){return 1;}
    if (n%2==1){return 0;}
    else {return is2pow(n/2);}
}
int main(void){
    int n;
    scanf("%d",&n);
    int otv=is2pow(n);
    if (otv==1){printf("YES\n");}
    else{printf("NO\n");}
	
    return 0;
}
