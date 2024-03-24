#include<stdio.h>
#include<stdlib.h>

int main(void){
    
    int a;
    int b;
    int c;
    scanf("%d%d%d",&a,&b,&c);
    
    int m12=(a>=b)?a:b;
    int m23=(b>=c)?b:c;
    int m=(m12>=m23)?m12:m23;
    printf("%d\n",m);
    
	
    return 0;
}