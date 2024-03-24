#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int main(void){

    int n;
    scanf("%d",&n);
    int cnt_digits=log10(n)+1;
    int* mas=(int*)malloc(cnt_digits*sizeof(int));
    int i=0;
    while(n!=0){mas[i]=n%10; i=i+1; n=n/10;}
    
    for (int j=cnt_digits-1; j>=0; j=j-1){
        printf("%d ",mas[j]);
    }
    printf("\n");
    free(mas);
    
    
	
    return 0;
}
