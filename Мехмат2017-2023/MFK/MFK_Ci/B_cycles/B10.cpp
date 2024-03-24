#include<stdio.h>
#include<stdlib.h>

int main(void){

    int N;
    scanf("%d",&N);
    
    int tek_digit;
    int res=1;
    int next_digit=N%10;
    N=N/10;
    while(N!=0){tek_digit=N%10;
                if (tek_digit>=next_digit){res=0; break;}
                N=N/10;
                next_digit=tek_digit;
                }
    
    if (res==1) {printf("YES\n");}
    else {{printf("NO\n");}}
	
    return 0;
}
