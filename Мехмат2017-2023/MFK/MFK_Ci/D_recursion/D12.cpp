#include<stdio.h>
#include<stdlib.h>

void pechat(int k, int n, int* global_cnt, int my_cnt){
    if (*global_cnt<n && my_cnt<k){
        printf("%d ",k);
        *global_cnt+=1;
        pechat(k,n,global_cnt, my_cnt+1);
        
    }
}

int main(void){
    
    int n;
    scanf("%d",&n);
    int cnt=0;
    for (int k=1; k<=n; k=k+1){
        pechat(k,n,&cnt,0);
        if (cnt==n){break;}
    }
    printf("\n");
    
	
    return 0;
}
