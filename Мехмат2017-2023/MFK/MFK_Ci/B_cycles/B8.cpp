#include<stdio.h>
#include<stdlib.h>

int main(void){

    int N;
    scanf("%d",&N);
    
    int tek_digit;
    int cnt=0;
    while(N!=0){tek_digit=N%10;
                if (tek_digit==9){cnt+=1;}
                N=N/10;
                }
    
    if (cnt==1) {printf("YES\n");}
    else {{printf("NO\n");}}
	
    return 0;
}
