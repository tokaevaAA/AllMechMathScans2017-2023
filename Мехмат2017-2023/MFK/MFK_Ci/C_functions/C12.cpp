#include<stdio.h>
#include<stdlib.h>
#include <math.h>

double sinus(double x_gradusov){
    double x_radian=x_gradusov*2*M_PI/360;
    double otv=0.0;
    int n=0;
    double n_fact=1;
    while (fabs(pow(x_radian,2*n+1)/n_fact)>=0.001){
        otv+=pow(-1,n)*pow(x_radian,2*n+1)/n_fact;
        n=n+1;
        n_fact*=2*n*(2*n+1);
    }
    return otv;
    
}
int main(void){
    int x_grad;
    scanf("%d",&x_grad);
    double otv=sinus(x_grad);
    printf("%0.3f\n",otv);
    
    
    
	
    return 0;
}
