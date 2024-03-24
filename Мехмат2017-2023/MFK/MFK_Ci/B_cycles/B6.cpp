#include<stdio.h>
#include<stdlib.h>

int main(void){

    int N;
    scanf("%d",&N);
    int last_digit=N%10;
    int tek_digit;
    N=N/10;
    int res=0;
    while(N!=0){tek_digit=N%10;  
	        if (tek_digit==last_digit){res=1; break;}
		N=N/10;
		last_digit=tek_digit;
		}
    if (res==1) {printf("YES\n");}
    else {{printf("NO\n");}}
	
    return 0;
}