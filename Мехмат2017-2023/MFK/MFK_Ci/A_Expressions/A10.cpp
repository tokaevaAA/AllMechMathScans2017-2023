#include<stdio.h>
#include<stdlib.h>

int main(void){
    
    int a;
    int b;
    int c;
    int d;
    int e;
    scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);
    
    int m12=(a<=b)?a:b;
    int m23=(b<=c)?b:c;
    int m45=(d<=e)?d:e;
    int m123=(m12<=m23)?m12:m23;
    int m=(m123<=m45)?m123:m45;

    printf("%d\n",m);
    
	
    return 0;
}