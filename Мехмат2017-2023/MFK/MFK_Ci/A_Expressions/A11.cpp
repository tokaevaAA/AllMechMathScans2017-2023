#include<stdio.h>
#include<stdlib.h>

int main(void){
    
    int a;
    int b;
    int c;
    int d;
    int e;
    scanf("%d%d%d%d%d",&a,&b,&c,&d,&e);

    int mx12=(a>=b)?a:b;
    int mx23=(b>=c)?b:c;
    int mx45=(d>=e)?d:e;
    int mx123=(mx12>=mx23)?mx12:mx23;
    int mx=(mx123>=mx45)?mx123:mx45;

    
    int mn12=(a<=b)?a:b;
    int mn23=(b<=c)?b:c;
    int mn45=(d<=e)?d:e;
    int mn123=(mn12<=mn23)?mn12:mn23;
    int mn=(mn123<=mn45)?mn123:mn45;

    printf("%d\n",mn+mx);
    
	
    return 0;
}