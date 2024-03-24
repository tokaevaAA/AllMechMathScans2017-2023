#include<stdio.h>
#include<stdlib.h>

int main(void){
    
    int a;
    int b;
    int c;
    scanf("%d%d%d",&a,&b,&c);
    int sum=a+b+c;
    int prod=a*b*c;
    printf("%d+%d+%d=%d\n",a,b,c,sum);
    printf("%d*%d*%d=%d\n",a,b,c,prod);
	
    return 0;
}