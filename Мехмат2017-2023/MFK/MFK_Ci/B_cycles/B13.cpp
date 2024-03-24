#include<stdio.h>
#include<stdlib.h>

int main(void){

    int N;
    scanf("%d",&N);
    int tek_digit;
    int max_digit=N%10;
    int min_digit=N%10;
    while(N!=0){tek_digit=N%10;
                if(tek_digit<min_digit){min_digit=tek_digit;}
                if(tek_digit>max_digit){max_digit=tek_digit;}
                N=N/10;
                }
    printf("%d %d\n",min_digit,max_digit);
    
    
    return 0;
}
