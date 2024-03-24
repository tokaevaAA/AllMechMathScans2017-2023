#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void Swap(int a,int b, int* mas)
{
    int t=mas[a];
    mas[a]=mas[b];
    mas[b]=t;
}

int main(){
    int n;
    scanf("%d",&n);
    int cnt_digits=log10(n)+1;
    int* mas=(int*)malloc(cnt_digits*sizeof(int));
    int i=0;
    while(n!=0){mas[cnt_digits-1-i]=n%10; i=i+1; n=n/10;}
    
    int max_otv=n;
    int otv_a=-1;
    int otv_b=-1;
    for (int a=0; a<cnt_digits; a=a+1){
        for (int b=a+1; b<cnt_digits; b=b+1){
            int tek_otv=0;
            Swap(a,b,mas);
            for (int j=0; j<cnt_digits; j=j+1){
                tek_otv+=mas[j]*pow(10,cnt_digits-j-1);
            }
            if (tek_otv > max_otv){max_otv=tek_otv; otv_a=a; otv_b=b;}
            Swap(a,b,mas);
            //printf("a=%d b=%d tek_otv=%d\n",a,b,tek_otv);
        }
    }
    
    if (otv_a!=-1 && otv_b!=-1){
        //printf("a=%d b=%d\n",otv_a,otv_b);
        Swap(otv_a,otv_b,mas);
    }
    
    for (int j=0; j<cnt_digits; j=j+1){
        printf("%d",mas[j]);
    }
    printf("\n");
    free(mas);
    
}

