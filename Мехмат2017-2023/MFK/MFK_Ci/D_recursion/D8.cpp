#include<stdio.h>
#include<stdlib.h>

void pechat(int a,int b){
    if (a==b){printf("%d ",a);}
    else if (a<b){printf("%d ",a); pechat(a+1,b);}
    else {printf("%d ",a); pechat(a-1,b);}
}

int main(void){
    
    int a;
    int b;
    scanf("%d%d",&a,&b);
    pechat(a,b);
    printf("\n");
	
    return 0;
}
