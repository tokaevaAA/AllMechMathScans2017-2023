#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


double h(double x, double y, double a_x, double b_x, double a_y, double b_y){
    return -37.75*sin(M_PI*2*x/(b_x-a_x))*sin(M_PI*2*y/(b_y-a_y))-0.3775*sin(M_PI*1*x/(b_x-a_x))*sin(M_PI*3*y/(b_y-a_y))
    -0.3775*sin(M_PI*3*x/(b_x-a_x))*sin(M_PI*1*y/(b_y-a_y));
    
}


void pechat_vector(int N, double* B){
    printf("Start Pechat vector:\n");
    for (int i=0; i<=fmin(N,5); i=i+1){
	    printf("%f ",B[i]);
    }
    printf("\n");
    printf("End Pechat vector\n");
}

void pechat_matrix(int N_x, int N_y, double* B){
   
    for (int j=0; j<=fmin(N_y,5); j=j+1){
	for (int i=0; i<=fmin(N_x,5); i=i+1){
	    printf("%f ",B[j*(N_x+1)+i]);
        }
        printf("\n");
    }
    printf("\n");
    
}


//---------------------------------------------------------------------------------------------------------------------------------------

double scal_proizv_vect_phi_m(double* vect, int m, double a_x, double b_x, int N_x,  double h_x){
    double otv=0;
    for (int i=1; i<=N_x-1; i=i+1) otv=otv+vect[i]*sin(M_PI*m*(a_x+i*h_x)/(b_x-a_x));
    otv=otv*h_x;
    return otv;
	
}

double scal_proizv_vect_ksi_n(double* vect, int n, double a_y, double b_y, int N_y,  double h_y){
    double otv=0;
    for (int j=1; j<=N_y-1; j=j+1) otv=otv+vect[j]*sin(M_PI*n*(a_y+j*h_y)/(b_y-a_y));
    otv=otv*h_y;
    return otv;
	
}



double scal_proizv_phi_phi(int m, double a_x, double b_x, int N_x,  double h_x){
    double otv=0;
    for (int i=1; i<=N_x-1; i=i+1) otv=otv+sin(M_PI*m*(a_x+i*h_x)/(b_x-a_x))*sin(M_PI*m*(a_x+i*h_x)/(b_x-a_x));
    otv=otv*h_x;
    return otv;
	
}

double scal_proizv_ksi_ksi(int n, double a_y, double b_y, int N_y,  double h_y){
    double otv=0;
    for (int j=1; j<=N_y-1; j=j+1) otv=otv+sin(M_PI*n*(a_y+j*h_y)/(b_y-a_y))*sin(M_PI*n*(a_y+j*h_y)/(b_y-a_y));
    otv=otv*h_y;
    return otv;
	
}


double* f2c(double* mas_f, double* mas_c,  double a_x, double b_x, double a_y,double b_y, int N_x, int N_y, double h_x, double h_y){
 
    double* dop_x=(double*)malloc((N_x+1)*(sizeof(double)));
    double* dop_y=(double*)malloc((N_y+1)*(sizeof(double)));
    for (int i=0; i<=N_x; i=i+1){dop_x[i]=0;}
    for (int i=0; i<=N_y; i=i+1){dop_y[i]=0;}

    for (int j=1; j<=N_y-1; j=j+1) {
        for (int i=1; i<=N_x-1; i=i+1){dop_x[i]=mas_f[j*(N_x+1)+i];}
        for (int i=1; i<=N_x-1; i=i+1){
            mas_c[j*(N_x+1) +i] = scal_proizv_vect_phi_m(dop_x, i, a_x, b_x, N_x, h_x)/scal_proizv_phi_phi(i, a_x,b_x, N_x, h_x);
        }
    }

    
    for (int i=1; i<=N_x-1; i=i+1) {
        for (int j=1; j<=N_y-1; j=j+1){dop_y[j]=mas_c[j*(N_x+1)+i];}
        for (int j=1; j<=N_y-1; j=j+1){ mas_c[j*(N_x+1) +i] = scal_proizv_vect_ksi_n(dop_y, j, a_y,b_y, N_y, h_y)/scal_proizv_ksi_ksi(j, a_y,b_y, N_y, h_y);
        }
    }
    
    free(dop_x);
    free(dop_y);
    return mas_c;

}


double* c2f(double* mas_c, double* mas_u,  double a_x, double b_x, double a_y,double b_y, int N_x, int N_y, double h_x, double h_y){

    double* dop_y=(double*)malloc((N_y+1)*(sizeof(double)));
    for (int i=0; i<=N_y; i=i+1){dop_y[i]=0;}
    
    
    for (int j=1; j<=N_y-1; j=j+1) {
        for (int i=1; i<=N_x-1; i=i+1){
            double sum=0.0;
            for (int m=1; m<=N_x-1; m=m+1){ sum+=mas_c[j*(N_x+1)+m]*sin(M_PI*m*(a_x+i*h_x)/(b_x-a_x));}
            mas_u[j*(N_x+1) +i] = sum;
            
        }
    }
    
  
    
    for (int i=1; i<=N_x-1; i=i+1) {
        for (int j=1; j<=N_y-1; j=j+1){dop_y[j]=mas_u[j*(N_x+1)+i];}
        for (int j=1; j<=N_y-1; j=j+1){
            double sum=0.0;
            for (int n=1; n<=N_y-1; n=n+1){sum+=dop_y[n]*sin(M_PI*n*(a_y+j*h_y)/(b_y-a_y));}
            mas_u[j*(N_x+1) +i] = sum;
        }
    }

    
    free(dop_y);
    return mas_u;

}

double trig_mnog(double a_x, double b_x, double a_y, double b_y, int N_x, int N_y, double uzel_x, double uzel_y, double* mas_c){
    double otv=0;
    for (int m=1; m<=N_x-1; m=m+1){
	for (int n=1; n<=N_y-1; n=n+1){
 		otv=otv + mas_c[n*(N_x+1)+m]*sin(M_PI*m*uzel_x/(b_x-a_x))*sin(M_PI*n*uzel_y/(b_y-a_y));
	}
    }
    return otv;
}


double get_lambda(int n, double h, double a, double b){
    return 4*sin(0.5*M_PI*n*h/(b-a))*sin(0.5*M_PI*n*h/(b-a))/(h*h);
}

double* solve_laplas(double* mas_u, double* mas_f, double k, double p, double a_x, double b_x, double a_y, double b_y, int N_x, int N_y, double h_x, double h_y){
    double* mas_c=(double*)malloc((N_x+1)*(N_y+1)*(sizeof(double)));
    double* mas_d=(double*)malloc((N_x+1)*(N_y+1)*(sizeof(double)));
    
    
    for (int j=0; j<=N_y; j=j+1){
        for (int i=0; i<=N_x; i=i+1){
            mas_c[j*(N_x+1)+i]=0;
            mas_d[j*(N_x+1)+i]=0;
        }
    }
    

    
    mas_d=f2c(mas_f, mas_d, a_x, b_x, a_y, b_y, N_x, N_y, h_x, h_y);
    
   
    
    for (int j=1; j<=N_y-1; j=j+1){
        for (int i=1; i<=N_x-1; i=i+1){
            mas_c[j*(N_x+1)+i]=mas_d[j*(N_x+1)+i]/(k*(get_lambda(i,h_x, a_x, b_x)+get_lambda(j,h_y,a_y,b_y))+p);
        }
    }
    
    /*
    for (int j=0; j<=N_y; j=j+1){
        for (int i=0; i<=N_x; i=i+1){
            mas_u[j*(N_x+1)+i]=trig_mnog(a_x, b_x, a_y, b_y, N_x, N_y, a_x+i*h_x, a_y+j*h_y, mas_c);
        }
    }
    */
    
    
    mas_u=c2f(mas_c, mas_u, a_x, b_x, a_y, b_y, N_x, N_y, h_x, h_y);
    
    free(mas_c);
    free(mas_d);
    
    return mas_u;
}

double* get_skobka(double* mas_skobka, double* mas_omega, double* mas_ksi, int N_x, int N_y, double h_x, double h_y){
    for (int j=1; j<=N_y-1; j=j+1){
        for (int i=1; i<=N_x-1; i=i+1){
            double ksi_x=(mas_ksi[j*(N_x+1)+i+1]-mas_ksi[j*(N_x+1)+i-1])/(2*h_x);
            double ksi_y=(mas_ksi[(j+1)*(N_x+1)+i]-mas_ksi[(j-1)*(N_x+1)+i])/(2*h_y);
            double omega_x=(mas_omega[j*(N_x+1)+i+1]-mas_omega[j*(N_x+1)+i-1])/(2*h_x);
            double omega_y=(mas_omega[(j+1)*(N_x+1)+i]-mas_ksi[(j-1)*(N_x+1)+i])/(2*h_y);
            mas_skobka[j*(N_x+1)+i]=ksi_x*omega_y-ksi_y*omega_x;
        }
    }
    return mas_skobka;
}

//---------------------------------------------------------------------------------------------------------------------------------------


int main(int argc, char** argv){
    printf("Hello!\n ");
    
    if (argc != 7) {printf("Usage: ./a.out a_x b_x N_x a_y b_y N_y ravnom myfunc1/myfunc2/myfunc3 \n"); return -1;}
    
    double a_x = atof(argv[1]);
    double b_x = atof(argv[2]);
    int N_x = atoi(argv[3]);
    double a_y = atof(argv[4]);
    double b_y = atof(argv[5]);
    int N_y = atoi(argv[6]);
    printf("a_x=%f b_x=%f  N_x=%d a_y=%f  b_y=%f  N_y=%d\n", a_x, b_x, N_x, a_y,  b_y,  N_y);

    double h_x = (b_x-a_x)/N_x;
    double h_y = (b_y-a_y)/N_y;

    double k=2.83*0.0001;
    double b=1;
    double tau=0.01;
    int T_steps=100;
    
    double* mas_f=(double*)malloc((N_x+1)*(N_y+1)*(sizeof(double)));
    double* mas_c=(double*)malloc((N_x+1)*(N_y+1)*(sizeof(double)));
    
    for (int j=0; j<=N_y; j=j+1){
        for (int i=0; i<=N_x; i=i+1){ 
            mas_c[j*(N_x+1)+i]=0;
        }
    }
    
    for (int j=0; j<=N_y; j=j+1){
        for (int i=0; i<=N_x; i=i+1){ 
            mas_f[j*(N_x+1)+i]=h(a_x + i*h_x, a_y + j*h_y, a_x, b_x, a_y, b_y);
        }
    }

    
    mas_c=f2c(mas_f, mas_c, a_x, b_x, a_y, b_y,  N_x, N_y, h_x, h_y);
    printf("Matrix c:\n");
    pechat_matrix(N_x,N_y,mas_c);
    
    
    
    double* mas_omega_tek=(double*)malloc((N_x+1)*(N_y+1)*(sizeof(double)));
    double* mas_ksi_tek=(double*)malloc((N_x+1)*(N_y+1)*(sizeof(double)));
    double* mas_skobka=(double*)malloc((N_x+1)*(N_y+1)*(sizeof(double)));
    double* mas_omega_next=(double*)malloc((N_x+1)*(N_y+1)*(sizeof(double)));
    double* mas_ksi_next=(double*)malloc((N_x+1)*(N_y+1)*(sizeof(double)));
    
    for (int j=0; j<=N_y; j=j+1){
        for (int i=0; i<=N_x; i=i+1){
            mas_omega_tek[j*(N_x+1)+i]=0;
            mas_ksi_tek[j*(N_x+1)+i]=0;
            mas_skobka[j*(N_x+1)+i]=0;
            mas_omega_next[j*(N_x+1)+i]=0;
            mas_ksi_next[j*(N_x+1)+i]=0;
        }
    }
    
    
    FILE* fout=fopen("output.txt", "w");
    
    
    for (int t=1; t<=T_steps; t=t+1){
        //printf("t=%d\n",t);
        mas_skobka=get_skobka(mas_skobka, mas_omega_tek, mas_ksi_tek,N_x,N_y,h_x,h_y);
        for (int j=0; j<=N_y; j=j+1){
            for (int i=0; i<=N_x; i=i+1){
                mas_f[j*(N_x+1)+i]=-mas_skobka[j*(N_x+1)+i] + h(a_x + i*h_x, a_y + j*h_y, a_x, b_x, a_y, b_y) + mas_omega_tek[j*(N_x+1)+i]/tau;
            }
        }
        //pechat_matrix(N_x, N_y, mas_f);
        mas_omega_next=solve_laplas(mas_omega_next, mas_f, k, b+1/tau, a_x, b_x, a_y, b_y, N_x, N_y, h_x, h_y);
        //pechat_matrix(N_x, N_y, mas_omega_next);
        mas_ksi_next=solve_laplas(mas_ksi_next, mas_omega_next, 1, 0, a_x, b_x, a_y, b_y, N_x, N_y, h_x, h_y);
       
        
        
        
        for (int j=0; j<=N_y; j=j+1){
            for (int i=0; i<=N_x; i=i+1){
                fprintf(fout, "%f %f %f\n", a_x+i*h_x, a_y+j*h_y, mas_ksi_tek[j*(N_x+1)+i]);
                
            }
        }
        fprintf(fout, "\n");
        fprintf(fout, "\n");
        
        
        
        for (int j=0; j<=N_y; j=j+1){
            for (int i=0; i<=N_x; i=i+1){
                mas_omega_tek[j*(N_x+1)+i]=mas_omega_next[j*(N_x+1)+i];
                mas_ksi_tek[j*(N_x+1)+i]=mas_ksi_next[j*(N_x+1)+i];
            }
        }
        //pechat_matrix(N_x,N_y, mas_ksi_tek);
        
        
    }
    
    fclose(fout);
    
    free(mas_f);
    free(mas_c);
    
    free(mas_omega_tek);
    free(mas_ksi_tek);
    free(mas_skobka);
    free(mas_omega_next);
    free(mas_ksi_next);
    
    printf("Goodbuy!\n");
    
    return 0;

}
