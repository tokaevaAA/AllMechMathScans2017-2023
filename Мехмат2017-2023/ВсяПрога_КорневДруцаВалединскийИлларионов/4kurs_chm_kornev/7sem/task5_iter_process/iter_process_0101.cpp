#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



static char* type_of_func;


int minim(int a, int b){
    return (a<b)?a:b;
}




double func(double x){
    if (strcmp(type_of_func,"myfunc1")==0){ return x*x + cos(5*x*x*x - 2);}
    else if (strcmp(type_of_func,"myfunc2")==0){return sin(M_PI*2.5*x);}
    else {return (x>0.5)?-1+x:-x;} //(strcmp(type_of_func,"mufunc3")==0)

}

double p(double x){
    //return 10.0;
    return 1+x*x;
}

double pmin(int N, double* mas_x){
    double otv=p(mas_x[1]);
    for (int i=2; i<=N-1; i=i+1){otv=fmin(otv, p(mas_x[i]));}
    return otv;
}

double pmax(int N, double* mas_x){
    double otv=p(mas_x[1]);
    for (int i=2; i<=N-1; i=i+1){otv=fmax(otv, p(mas_x[i]));}
    return otv;
}



double p0(double x){
    return 0.5*p(x);

}

double p0_3(int N, double* mas_x){
    return 0.5*(pmax(N,mas_x) +pmin(N,mas_x));

}


double get_m(int N, double* mas_x){
    double otv=(pow(M_PI*(1.0-0.5),2)+p(mas_x[1]))/(pow(M_PI*(1.0-0.5),2)+p0(mas_x[1]));
    for (int i=2; i<=N-1; i=i+1){otv=fmin(otv,(pow(M_PI*(i-0.5),2)+p(mas_x[i]))/(pow(M_PI*(i-0.5),2)+p0(mas_x[i]))); }
    return otv;

}

double get_M(int N, double* mas_x){
    double otv=(pow(M_PI*(1.0-0.5),2)+p(mas_x[1]))/(pow(M_PI*(1.0-0.5),2)+p0(mas_x[1]));
    for (int i=2; i<=N-1; i=i+1){otv=fmax(otv,(pow(M_PI*(i-0.5),2)+p(mas_x[i]))/(pow(M_PI*(i-0.5),2)+p0(mas_x[i]))); }
    return otv;

}


double get_tau(){
   //return 1.0;
   return 2.0/(1.0 + p(1.0)/p0(1.0));
  
}

double get_tau_new(int N, double* mas_x){
   //return 1.0;
   //return 2.0/(1.0 + p(1.0)/p0(1.0));
   return 2.0/(get_m(N, mas_x) + get_M(N,mas_x)+1);
   
}

double get_tau(int N, double* mas_x){
   //return 1.0;
   return 2.0/(1.0 + p(1.0)/p0_3(N, mas_x));
  
}

double lambda_n(int n, double h){
    return 4*sin(0.5*M_PI*(n-0.5)*h)*sin(0.5*M_PI*(n-0.5)*h)/(h*h);

}







void pechat_vector(int N, double* B){
    //printf("Start Pechat vector:\n");
    for (int i=0; i<=minim(N,10); i=i+1){
	    printf("%f ",B[i]);
    }
    printf("\n");
    //printf("End Pechat vector\n");
}






int generate_input(double a, double b, int N, char* tip_uzlov, const char* filename){
    FILE*fout;
    fout=fopen(filename,"w");
    if (fout==0) {printf("Cannot open %s\n", filename); return -1;}
 
    if (strcmp(tip_uzlov,"ravnom")==0) {printf("ravnom uzl\n");
					
					double h = (b-a)/(N-0.5);
					for (int i=0; i<=N; i=i+1) fprintf(fout, "%f ", a + i*h);
					fprintf(fout,"\n");
					for (int i=0; i<=N; i=i+1) fprintf(fout,"%f ", func(a + i*h));
					}

    
    fclose(fout);
    return 0;
					
}

//---------------------------------------------------------------------------------------------------------------------------------------

double scal_proizv_fphi(double* mas_f, int n, double a, int N,  double h){
    double otv=0;
    for (int k=1; k<=N-1; k=k+1) otv=otv+mas_f[k]*sin(M_PI*(n-0.5)*(a+k*h));
    otv=otv*h;
    return otv;
	
}

double scal_proizv_phi_phi(int n, double a, int N,  double h){
    double otv=0;
    for (int k=1; k<=N-1; k=k+1) otv=otv+sin(M_PI*(n-0.5)*(a+k*h))*sin(M_PI*(n-0.5)*(a+k*h));
    otv=otv*h;
    return otv;
	
}

double* f2c(double* mas_f, double* mas_c, double a, int N, double h){
    mas_c[0]=0.0;
    mas_c[N]=0.0;
    for(int n=1; n <=N-1; n=n+1) mas_c[n]=scal_proizv_fphi(mas_f, n, a, N, h)/scal_proizv_phi_phi(n, a, N, h);
    return mas_c;

}


double trig_mnog(int N, double uzel, double* mas_c){
    double otv=0;
    for (int n=1; n<=N-1; n=n+1) otv=otv + mas_c[n]*sin(M_PI*(n-0.5)*uzel);
    return otv;
}


double A_ytek(int i, double h, int N,  double* mas_ytek, double* mas_x){
    if (i==1){return 2*mas_ytek[1]/(h*h) - mas_ytek[2]/(h*h) + p(mas_x[1])*mas_ytek[1];}
    else if (i==N-1) {return -mas_ytek[N-2]/(h*h) + 1*mas_ytek[N-1]/(h*h)  + p(mas_x[N-1])*mas_ytek[N-1];}
    else {return -mas_ytek[i-1]/(h*h) + 2*mas_ytek[i]/(h*h) - mas_ytek[i+1]/(h*h)+ p(mas_x[i])*mas_ytek[i];}

}

/*
double A_ytek(int i, double h, int N,  double* mas_ytek, double* mas_x){
    return mas_ytek[i]*(lambda_n(i,h) + p(mas_x[i]));
}
*/


double get_norma_of_err(double h, int N, double* mas_f, double* mas_ynext, double* mas_x ){
    double otv=0.0;
    for (int i=1; i<=N-1; i=i+1){otv = otv + (mas_f[i] -A_ytek(i, h, N, mas_ynext, mas_x))*(mas_f[i] -A_ytek(i, h, N, mas_ynext, mas_x)); }
    otv=otv*h;
    return sqrt(otv);
}

//---------------------------------------------------------------------------------------------------------------------------------------


int main(int argc, char** argv){
    printf("Hello!\n ");
    
    if (argc != 6) {printf("Usage: ./a.out a b N ravnom myfunc1/myfunc2/myfunc3 \n"); return -1;}
    
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int N = atoi(argv[3]);
    type_of_func = argv[5];
    printf("a=%f b=%f N=%d is_ravnom=%d %s\n", a,b,N, strcmp(argv[4], "ravnom"),type_of_func);

    
    int flag=generate_input(a, b, N, argv[4],"input.txt");
    if (flag==-1) {printf("Problems in generate_input. Program terminates.\n"); return -1;}

    
    FILE*fin;
    fin=fopen("input.txt","r");
    if (fin==0) {printf("Cannot open input.txt. Program terminates. \n");  return -1;}

    
    double* mas_x=(double*)malloc((N+1)*(sizeof(double)));
    double* mas_ytek=(double*)malloc((N+1)*(sizeof(double)));
    double* mas_ynext=(double*)malloc((N+1)*(sizeof(double)));
    double* mas_z=(double*)malloc((N+1)*(sizeof(double)));
    double* mas_alpha=(double*)malloc((N+1)*(sizeof(double)));


    double* mas_f=(double*)malloc((N+1)*(sizeof(double)));
    double* mas_g=(double*)malloc((N+1)*(sizeof(double)));
    double* mas_d=(double*)malloc((N+1)*(sizeof(double)));
        
    

    
    for (int i=0; i<=N; i=i+1){ fscanf(fin,"%lf",&mas_x[i]);}
    for (int i=0; i<=N; i=i+1){ fscanf(fin,"%lf",&mas_f[i]);}
    fclose(fin);

    double h=(b-a)/(N-0.5);
    //double tau = get_tau();
    double tau = get_tau(N,mas_x);
    double err=0;

    double tau_new = get_tau_new(N, mas_x);
    double m=get_m(N, mas_x);
    double M=get_M(N, mas_x);
    printf("m=%f M=%f tau=%f tau_new=%f\n", m,M,tau,tau_new);
   
    
    
    //printf("Vector x:\n");
    //pechat_vector(N,mas_x);
    //printf("Vector f:\n");
    //pechat_vector(N,mas_f);

    
    for (int i=0; i<=N; i=i+1) {mas_ytek[i]=0.0;}
    for (int i=0; i<=N; i=i+1) {mas_ynext[i]=0.0;}
    for (int i=0; i<=N; i=i+1) {mas_z[i]=0.0;}
    for (int i=0; i<=N; i=i+1) {mas_g[i]=0.0;}
    for (int i=0; i<=N; i=i+1) {mas_d[i]=0.0;}

   
            
    for (int k=0; k<=500; k=k+1){
        for (int i=1; i<=N-1; i=i+1){mas_ytek[i]=mas_ynext[i];}
        //printf("Vector y_tek:\n");
        //pechat_vector(N, mas_ytek);

	for (int i=1; i<=N-1; i=i+1){mas_g[i]=mas_f[i]-A_ytek(i, h, N, mas_ytek, mas_x);}
	//printf("Vector g:\n");
	//pechat_vector(N,mas_g);

        mas_d=f2c(mas_g, mas_d, a, N, h);
        //printf("Vector d:\n");
        //pechat_vector(N,mas_d);

        for (int i=1; i<=N-1; i=i+1){mas_alpha[i]=mas_d[i]/(lambda_n(i,h) + p0(mas_x[i]));}
        //printf("Vector alpha:\n");
        //pechat_vector(N,mas_alpha);

        for (int i=1; i<=N-1; i=i+1){mas_z[i]=trig_mnog(N, mas_x[i], mas_alpha);}
        //printf("Vector z:\n");
        //pechat_vector(N,mas_z);

        //for (int i=1; i<=N-1; i=i+1) {printf("%f ", A_ytek(i, h, N, mas_z, mas_x));}
        //printf("\n");

        for (int i=1; i<=N-1; i=i+1){mas_ynext[i]=mas_ytek[i] + tau*mas_z[i];}

        //printf("Vector ynext:\n");
        //pechat_vector(N,mas_ynext);

	err=get_norma_of_err(h, N, mas_f, mas_ynext, mas_x );
        printf("k=%d err=%le\n", k+1, err);
        pechat_vector(N, mas_ynext);
        if (err<0.0000000001){printf("END: k=%d\n",k+1); break;}
    }
    
    
    free(mas_x);
    free(mas_ytek);
    free(mas_ynext);
    free(mas_z);
    free(mas_alpha);
    free(mas_f);
    free(mas_g);
    free(mas_d);
    
    
    
    
    printf("Goodbuy!\n");
    
    return 0;

}
