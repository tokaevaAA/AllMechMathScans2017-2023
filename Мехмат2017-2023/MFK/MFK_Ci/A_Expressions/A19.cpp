#include<stdio.h>
#include<stdlib.h>

int main(void){
    
    int a;
    int b;
    int c;
    int res=1;
    scanf("%d%d%d",&a,&b,&c);
    if (a+b<=c){res=0;}
    if (b+c<=a){res=0;}
    if (a+c<=b){res=0;}

    if (res==1){printf("YES\n");}
    else {printf("NO\n");}

    return 0;
}