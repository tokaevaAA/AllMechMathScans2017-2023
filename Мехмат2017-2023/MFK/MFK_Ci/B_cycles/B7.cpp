#include<stdio.h>
#include<stdlib.h>

int main(void){

    int N;
    scanf("%d",&N);
    int mas[10];
    for (int i=0; i<10; i=i+1){mas[i]=0;}
    int tek_digit;
    int res=0;
    while(N!=0){tek_digit=N%10;
		mas[tek_digit]+=1;
		N=N/10;
		}
    for(int i=0; i<10; i=i+1){if (mas[i]>=2){res=1; break;}}
    if (res==1) {printf("YES\n");}
    else {{printf("NO\n");}}
	
    return 0;
}