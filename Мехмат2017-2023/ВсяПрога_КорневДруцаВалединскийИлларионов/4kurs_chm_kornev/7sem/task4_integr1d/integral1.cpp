#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



static char* type_of_func;



double func1(double x){
    return exp(x)*sqrt(x);  //integral:0.5e^(x)(sinx-cosx)
			    //4-th derivative:-4e^(x)sinx
			    //6-th derivative:-8e^(x)cosx

}



double func2(double x){
    return exp(x); //initially sqrt(x)exp(x), but sqrt(x) is weight
}


double integral1(double a, double b){
    return 0.5*exp(b)*(sin(b)-cos(b))-0.5*exp(a)*(sin(a)-cos(a));

}

double otsenka1_simpson(double a, double b){
    return 4*exp(b)*pow(b-a,5)/1536;

}
double otsenka1_gauss(double a, double b){
    return 8*exp(b)*pow(b-a,7)*pow(2,-10)/720;

}

double gauss_kvadr(double a, double b, double (*myfunc)(double x)){
    double c1=0.5*(b-a)*5.0/9.0;
    double c2=0.5*(b-a)*8.0/9.0;
    double c3=0.5*(b-a)*5.0/9.0;
   
    double x1=0.5*(a+b)+0.5*(b-a)*(-sqrt(0.6));
    double x2=0.5*(a+b);
    double x3=0.5*(a+b)+0.5*(b-a)*(sqrt(0.6));
	
    return c1*myfunc(x1)+c2*myfunc(x2)+c3*myfunc(x3);

}

double simpson_kvadr(double a, double b, double (*myfunc)(double x)){
    double c1=(b-a)/6.0;
    double c2=4*(b-a)/6.0;
    double c3=(b-a)/6.0;
   
    double x1=a;
    double x2=0.5*(a+b);
    double x3=b;
	
    return c1*myfunc(x1)+c2*myfunc(x2)+c3*myfunc(x3);


}


//---------------------------------------------------------------------------------------------------------------------------------------
double sostavn_gauss(double N, double a, double b, double (*myfunc)(double x)){
    double h=(b-a)/N;
    double otv=0;
    for (int i=1; i<=N; i=i+1){
	otv=otv+gauss_kvadr(a+(i-1)*h, a+i*h, myfunc);
	}
    return otv;


}

//---------------------------------------------------------------------------------------------------------------------------------------

double trapezia_kvadr(double a, double b, double (*myfunc)(double x)){
           
    double c1=2.0/(15.0*(a-b))*(pow(b,1.5)*(3*b-5*b)-pow(a,1.5)*(3*a-5*b));
    double c2=2.0/(15.0*(b-a))*(pow(b,1.5)*(3*b-5*a)-pow(a,1.5)*(3*a-5*a));
    //printf("a=%f b=%f c1=%f c2=%f\n", a,b,c1,c2);

    double x1=a;
    double x2=b;
    	
    return c1*myfunc(x1)+c2*myfunc(x2);

}



double sostavn_trapezia(double N, double a, double b, double (*myfunc)(double x)){
    double h=(b-a)/N;
    double otv=0;
    for (int i=1; i<=N; i=i+1){
	otv=otv+trapezia_kvadr(a+(i-1)*h, a+i*h, myfunc);
	}
    return otv;


}



//---------------------------------------------------------------------------------------------------------------------------------------


int main(int argc, char** argv){
    printf("Hello!\n ");
    
    //part1:gauss vs simpson with n=3
    FILE* fout_gauss_vs_simpson;
    fout_gauss_vs_simpson=fopen("fout_gauss_vs_simpson.txt","w");
    if (fout_gauss_vs_simpson==NULL) {printf("Cannot open fout_gauss_vs_simpson.txt"); return -1;}

    double a=0.0;
    double b=1.0;
    
 

    
    for (int i=0; i<15; i=i+1){
	double kv_g=gauss_kvadr(a,b,func1);
	double integr_g=integral1(a,b);
	double err_g= abs(kv_g-integr_g);
	double otsenka_g=otsenka1_gauss(a,b);
	printf("gauss: %d %le %le %le %le\n", i , integr_g, kv_g, err_g, otsenka_g);

	double kv_s=simpson_kvadr(a,b,func1);
	double integr_s=integral1(a,b);
	double err_s= abs(kv_s-integr_s);
	double otsenka_s=otsenka1_simpson(a,b);
	printf("simpson: %d %le %le %le %le\n", i , integr_s, kv_s, err_s, otsenka_s);

	fprintf(fout_gauss_vs_simpson," %d %le %le\n", i, err_g, err_s);
	b=b/2;
    }
        
    fclose(fout_gauss_vs_simpson);

    //part2: sustavn gauss
    FILE* fout_sostavn_gauss;
    fout_sostavn_gauss=fopen("fout_sostavn_gauss.txt","w");
    if (fout_sostavn_gauss==NULL) {printf("Cannot open fout_sostavn_gauss.txt"); return -1;}


    a=0.0;
    b=25.0;
    double N_max=100;
    double true_integral=integral1(a,b);
    double tek_integral=0.0;
    double tek_err=0.0;

    for (int N=1; N<=N_max; N=N+1){
	tek_integral = sostavn_gauss(N,a,b,func1);
	tek_err=abs(tek_integral-true_integral);
	fprintf(fout_sostavn_gauss," %d %le %le\n", N, log(N), log(1/tek_err));
	

    }

    fclose(fout_sostavn_gauss);

    //part3: sostavn trapezia for func2 with weight

    FILE* fout_sostavn_trapezia;
    fout_sostavn_trapezia=fopen("fout_sostavn_trapezia.txt","w");
    if (fout_sostavn_trapezia==NULL) {printf("Cannot open fout_sostavn_trapezia.txt"); return -1;}


    a=0.0;
    b=1.0;
    N_max=100;
    true_integral=1.25563;
    tek_integral=0.0;
    tek_err=0.0;

    for (int N=1; N<=N_max; N=N+1){
	tek_integral = sostavn_trapezia(N,a,b,func2);
	tek_err=abs(tek_integral-true_integral);
	//printf("%d %le %le %le \n", N , true_integral, tek_integral, tek_err);
	fprintf(fout_sostavn_trapezia," %d %le %le\n", N, log(N), log(1/tek_err));
		

    }

    fclose(fout_sostavn_trapezia);

    printf("Goodbuy!\n");
    
    return 0;

}
