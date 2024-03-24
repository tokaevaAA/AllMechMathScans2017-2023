#include<stdio.h>
#include<stdlib.h>


int main(void){
    
    double sum=1.0;
    double d=0.0;
    int n=2;
    int fib_nm2=1;
    int fib_nm1=1;
    int fib_n;
    while (1){
        fib_n=fib_nm2+fib_nm1;
        d=pow(-1,n)*(2*(n-1))/((fib_n)*pow(3,n-1));
        sum+=d;
        //printf("%f %f %f\n",d,abs(d),sum);
        if (fabs(d)<0.001){break;}
        n+=1;
        fib_nm2=fib_nm1;
        fib_nm1=fib_n;
        
    }
    printf("%0.3f\n",sum);
    
    
	
    return 0;
}
