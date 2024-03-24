#include<stdio.h>
#include<stdlib.h>


int main(void){
    int n;
    scanf("%d",&n);
    int cnt=0;
    for (int i=0; i<=n/6; i=i+1){
        for (int j=0; j<=n/8; j=j+1){
            if (6*i + 8*j==n){cnt+=1;}
        }
    }
    if (n==0){printf("%d\n",0);}
    else {printf("%d\n",cnt);}
	
    return 0;
}
