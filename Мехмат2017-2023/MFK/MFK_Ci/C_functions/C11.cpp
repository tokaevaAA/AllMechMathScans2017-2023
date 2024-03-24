#include<stdio.h>
#include<stdlib.h>


int gcd(int a, int b){
    if (a==0){return b;}
    if (b==0){return a;}
    if (a==b){return a;}
    if (a<b){return gcd(b,a);}
    if (a%2==0 && b%2==0){return 2*gcd(a/2,b/2);}
    else if (a%2==0 && b%2==1){return gcd(a/2,b);}
    else if (a%2==1 && b%2==0){return gcd(a,b/2);}
    else {return gcd((a-b)/2,b);}
    
}
int main(void){
    int a;
    int b;
    scanf("%d%d",&a,&b);
    int otv=gcd(a, b);
    printf("%d\n",otv);
    
    
    
	
    return 0;
}
