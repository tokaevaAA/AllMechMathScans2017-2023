#include<stdio.h>
#include<stdlib.h>

void perevod(int n){
    if (n/2==0) {printf("%d",n);}
    else { perevod(n/2); printf("%d",n%2);  }
}

int main(void){
    int n;
    scanf("%d",&n);
    perevod(n);
    printf("\n");
	
    return 0;
}
