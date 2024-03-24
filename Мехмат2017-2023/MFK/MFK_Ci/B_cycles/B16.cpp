#include<stdio.h>
#include<stdlib.h>

int main(void){
    
    int a;
    int b;
    int tmp;
    scanf("%d",&a);
    scanf("%d",&b);
    
    
    while (a!=b){if (a<b){tmp=a; a=b; b=tmp;}
        a=a-b;
    }
    printf("%d\n",a);
    
	
    return 0;
}
