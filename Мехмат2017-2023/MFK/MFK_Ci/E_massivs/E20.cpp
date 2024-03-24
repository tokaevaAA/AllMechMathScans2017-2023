#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int comparator(const void* a, const void* b){
    return -(*(int*)a)%10+(*(int*)b)%10;
}

int main(){
    int n;
    scanf("%d",&n);
    int cnt_digits=log10(n)+1;
    int* mas=(int*)malloc(cnt_digits*sizeof(int));
    int i=0;
    while(n!=0){mas[i]=n%10; i=i+1; n=n/10;}
    
    qsort(mas,cnt_digits,sizeof(int),comparator);
    for (int j=0; j<cnt_digits; j=j+1){
        printf("%d",mas[j]);
    }
    printf("\n");
    free(mas);
    
}

