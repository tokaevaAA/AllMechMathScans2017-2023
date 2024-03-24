#include<stdio.h>
#include<stdlib.h>

int check(int n){
    int sum=0;
    
    for (int d=1; d<n; d=d+1){
        if (n%d==0){sum+=d;}
    }
    
    if (sum==n && n!=1){return 1;}
    else {return 0;}
}
int main(void){
    int n;
    int otv=0;
    while (scanf("%d",&n)==1 && n!=0){
        if (check(n)){printf("%d ",n);}
    }
    printf("\n");
    
	
    return 0;
}
