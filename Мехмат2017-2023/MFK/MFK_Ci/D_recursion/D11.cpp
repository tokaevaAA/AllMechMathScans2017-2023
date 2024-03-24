#include<stdio.h>
#include<stdlib.h>

int count1(int n){
    if (n/2==0){return n%2;}
    else {return n%2+count1(n/2);}
}

int main(void){
    
    int n;
    scanf("%d",&n);
    int otv=count1(n);
    printf("%d\n",otv);
	
    return 0;
}
