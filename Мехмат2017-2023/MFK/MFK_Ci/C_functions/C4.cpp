#include<stdio.h>
#include<stdlib.h>

int f(int x){
    int otv;
    if (x<-2){otv=4;}
    else if (x>=2){otv=x*x+4*x+5;}
    else {otv=x*x;}
    return otv;
}
int main(void){

    int a;
    int tek_f;
    int max_f;
    int cnt=0;
    while(scanf("%d",&a)==1 && a!=0){
        tek_f=f(a);
        if (cnt==0){max_f=tek_f;}
        else {max_f=fmax(tek_f,max_f);}
        cnt+=1;
    }
    printf("%d\n",max_f);
    
	
    return 0;
}
