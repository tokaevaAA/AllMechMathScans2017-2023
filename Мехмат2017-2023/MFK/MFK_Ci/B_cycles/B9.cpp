#include<stdio.h>
#include<stdlib.h>

int main(void){

    int N;
    scanf("%d",&N);
    
    int tek_digit;
    int res=1;
    while(N!=0){tek_digit=N%10;
                if (tek_digit%2==1){res=0; break;}
                N=N/10;
                }
    
    if (res==1) {printf("YES\n");}
    else {{printf("NO\n");}}
	
    return 0;
}
