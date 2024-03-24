#include<stdio.h>
#include<stdlib.h>

int main(void){

    int N;
    scanf("%d",&N);
    int tek_digit;
    int cnt_even_digits=0;
    int cnt_odd_digits=0;
    while(N!=0){tek_digit=N%10;
                if(tek_digit%2==0){cnt_even_digits+=1;}
                if(tek_digit%2==1){cnt_odd_digits+=1;}
                N=N/10;
                }
    printf("%d %d\n",cnt_even_digits,cnt_odd_digits);
    
	
    return 0;
}
