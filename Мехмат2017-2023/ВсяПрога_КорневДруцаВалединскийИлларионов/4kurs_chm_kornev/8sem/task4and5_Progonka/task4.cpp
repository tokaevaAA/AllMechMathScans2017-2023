#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double* progonka_abc(int N, double* a, double* b, double* c, double* f, double* y){
    double* alpha = static_cast<double*>(malloc((N+1)*sizeof(double)));
    double* beta = static_cast<double*>(malloc((N+1)*sizeof(double)));
    alpha[0]=0;
    beta[0]=0;
    alpha[1]=b[0]/c[0];
    beta[1]=f[0]/c[0];
    for (int i=1; i<=N-1; i=i+1){
        alpha[i+1]=b[i]/(c[i]-a[i]*alpha[i]);
        beta[i+1]=(f[i]+a[i]*beta[i])/(c[i]-a[i]*alpha[i]);
    }
    y[N]=(f[N]+a[N]*beta[N])/(c[N]-a[N]*alpha[N]);
    for(int i=N-1; i>=0; i=i-1){
        y[i]=alpha[i+1]*y[i+1]+beta[i+1];
    }
    
    
    free(alpha);
    free(beta);
    return y;
    
}

double* reshalka_stationar_Laplace_WithMyEdgeConditions(int N, double* u, double func(double), double p(double)){
    double h=1/(N-0.5);
    double* a = static_cast<double*>(malloc((N+1)*sizeof(double)));
    double* b = static_cast<double*>(malloc((N+1)*sizeof(double)));
    double* c = static_cast<double*>(malloc((N+1)*sizeof(double)));
    double* f = static_cast<double*>(malloc((N+1)*sizeof(double)));
    //------------------
    c[0]=1;
    for (int i=1; i<=N-1; i=i+1){
        c[i]=2/(h*h)+p(i*h);
    }
    c[N]=-1;
    //--------------
    b[0]=0;
    for (int i=1; i<=N-1; i=i+1){
        b[i]=1/(h*h);
    }
    b[N]=100500;
    //---------------------
    a[0]=100500;
    for (int i=1; i<=N-1; i=i+1){
        a[i]=1/(h*h);
    }
    a[N]=-1; //because true a_N=1, but in our notation all a are with minus!
    //--------------------
    f[0]=0;
    for (int i=1; i<=N-1; i=i+1){
        f[i]=func(i*h);
    }
    f[N]=0;
    //-------------------
    
    //pechat_matrix(N, a, b, c, f);
    u=progonka_abc(N, a, b, c, f, u);
    
    free(a);
    free(b);
    free(c);
    free(f);
    return u;
}



double* yavn(int N, double h, int M, double tau,  double* y_tek, double* y_next){
    for (int i=1; i<=M; i=i+1){
        for (int j=1; j<=N-1; j=j+1){
            y_next[j]=y_tek[j]+tau*(y_tek[j-1]-2*y_tek[j]+y_tek[j+1])/(h*h);
        }
        y_next[0]=0;
        y_next[N]=y_next[N-1];
        y_tek=y_next;
        
    }
    return y_next;
}

void pechat_vectorVFILE(int N, double* mas, FILE*f){
    for (int i=0; i<=N; i=i+1){
        fprintf(f,"%f ", mas[i]);
    }
    fprintf(f,"\n");
}

double* neyavn(int N, double h, int M, double tau,  double* y_tek, double* y_next){
    double* a = static_cast<double*>(malloc((N+1)*sizeof(double)));
    double* b = static_cast<double*>(malloc((N+1)*sizeof(double)));
    double* c = static_cast<double*>(malloc((N+1)*sizeof(double)));
    double* f = static_cast<double*>(malloc((N+1)*sizeof(double)));
    FILE* fout =fopen("file_for_surface.txt","w");
    
    for (int k=1; k<=M; k=k+1){
        
        //------------------
        c[0]=1;
        for (int i=1; i<=N-1; i=i+1){
            c[i]=2/(h*h)+1/tau;
        }
        c[N]=-1;
        //--------------
        b[0]=0;
        for (int i=1; i<=N-1; i=i+1){
            b[i]=1/(h*h);
        }
        b[N]=100500;
        //---------------------
        a[0]=100500;
        for (int i=1; i<=N-1; i=i+1){
            a[i]=1/(h*h);
        }
        a[N]=-1; //because true a_N=1, but in our notation all a are with minus!
        //--------------------
        f[0]=0;
        for (int i=1; i<=N-1; i=i+1){
            f[i]=y_tek[i]/tau;
        }
        f[N]=0;
        //-------------------
        
        y_next=progonka_abc(N, a, b, c, f, y_next);
        pechat_vectorVFILE(N, y_next, fout);
        y_tek=y_next;
        
        
    }
    fclose(fout);
    free(a);
    free(b);
    free(c);
    free(f);
    return y_next;
}


void pechat_vector(int N, double* mas){
    for (int i=0; i<=fmin(N,10); i=i+1){
        printf("%f ", mas[i]);
    }
    if (N>10){printf("...");}
    printf("\n");
}





void pechat_matrix(int N, double* a, double* b, double* c, double* f){
    for (int i=0; i<=N; i=i+1){
        for (int j=0; j<=N; j=j+1){
            if (j==i-1){printf("%f ",-a[i]);}
            else if (j==i){printf("%f ",c[i]);}
            else if (j==i+1){printf("%f ",-b[i]);}
            else{printf("%f ",0.0);}
        }
        printf("| %f\n",f[i]);
    }
    
    printf("\n");
    
}



double u0(double x){
    return sin(M_PI*0.5*x);
}



double* put_Stationar_solution(int N, double* mas, double real_solutionStat(double)){
    for (int i=0; i<=N; i=i+1){
        double h=1/(N-0.5);
        double x_i = i*h;
        mas[i] = real_solutionStat(x_i);
    }
    return mas;
}
double* put_NotStationar_solution(int N, double T, double* mas, double real_solutionNotStat(double, double)){
    for (int i=0; i<=N; i=i+1){
        double h=1/(N-0.5);
        double x_i = i*h;
        mas[i] = real_solutionNotStat(x_i, T);
    }
    return mas;
}

double get_err(int N, double* a, double* b){
    double otv=0.0;
    for (int i=0; i<=N; i=i+1){
        otv=fmax(otv, fabs(a[i]-b[i]));
    }
    return otv;
}

//=================================================================================================
int main(int argc, char** argv){
    printf("Hello!\n");
    if (argc != 4) {printf("Usage: ./a.out N M T\n"); return -1;}
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    double T = atof(argv[3]);
    double h=1/(N-0.5);
    double tau=T/M;
    double err;
    double* a = static_cast<double*>(malloc((N+1)*sizeof(double)));
    double* b = static_cast<double*>(malloc((N+1)*sizeof(double)));
    double* c = static_cast<double*>(malloc((N+1)*sizeof(double)));
    double* f = static_cast<double*>(malloc((N+1)*sizeof(double)));
    double* u = static_cast<double*>(malloc((N+1)*sizeof(double)));
    double* u_real = static_cast<double*>(malloc((N+1)*sizeof(double)));
    double* y_tek = static_cast<double*>(malloc((N+1)*sizeof(double)));
    double* y_next = static_cast<double*>(malloc((N+1)*sizeof(double)));
    
    
    //--------------------------------------------------
    printf("Test1: stationar for for func(x)=x; p(x)=0; -u''=x\n");
    printf("u calculated:\n");
    u=reshalka_stationar_Laplace_WithMyEdgeConditions(N, u,[](double x)->double{return x;},[](double x)->double{return 0.0;});
    pechat_vector(N,u);
    printf("u real:0.5*x - x*x*x/6\n");
    u_real=put_Stationar_solution(N, u_real, [](double x)->double{return 0.5*x - x*x*x/6;});
    pechat_vector(N,u_real);
    err=get_err(N, u, u_real);
    printf("err=%le\n",err);
    printf("\n");
    
    
    //--------------------------------------------------------
    printf("Test2: stationar for func(x)=x; p(x)=-10; -u''-10u=x;\n");
    printf("u calculated:\n");
    u=reshalka_stationar_Laplace_WithMyEdgeConditions(N, u,[](double x)->double{return x;},[](double x)->double{return -10.0;});
    pechat_vector(N,u);
    printf("u real:0.01*(sqrt(10)*(1/cos(sqrt(10)))*sin(sqrt(10)*x) - 10*x);\n");
    u_real=put_Stationar_solution(N, u_real, [](double x)->double{return 0.01*(sqrt(10)*(1/cos(sqrt(10)))*sin(sqrt(10)*x) - 10*x);});
    pechat_vector(N,u_real);
    err=get_err(N, u, u_real);
    printf("err=%le\n",err);
    printf("\n");
    
    
    //--------------------------------------------------------
    printf("Test3:  Yavn method for Notstationar with func(x)=0; p(x)=0; u't-u''xx=0;\n");
    for (int i=0; i<=N; i=i+1){
        y_tek[i]=u0(i*h);
    }
    y_next=yavn(N, h, M, tau, y_tek, y_next);
    printf("y_next from yavn for p=0; f=0 u't-u''xx=0\n");
    pechat_vector(N,y_next);
    printf("y_tochnoe for p=0; f=0 u't-u''xx=0\n");
    u_real=put_NotStationar_solution(N, T, u_real, [](double x, double t)->double{return exp(-M_PI*M_PI*t/4)*sin(M_PI*0.5*x);});
    pechat_vector(N,u_real);
    err=get_err(N, y_next, u_real);
    printf("err=%le\n",err);
    printf("\n");
    
    //----------------------------------------------------
    printf("Test4:  NeYavn method for Notstationar with func(x)=0; p(x)=0; u't-u''xx=0;\n");
    for (int i=0; i<=N; i=i+1){
        y_tek[i]=u0(i*h);
    }
    y_next=neyavn(N, h, M, tau, y_tek, y_next);
    printf("y_next from neyavn for Notstationar with func(x)=0; p(x)=0; u't-u''xx=0;\n");
    pechat_vector(N,y_next);
    printf("y_tochnoe for p=0; f=0 u't-u''xx=0;\n");
    u_real=put_NotStationar_solution(N, T, u_real, [](double x, double t)->double{return exp(-M_PI*M_PI*t/4)*sin(M_PI*0.5*x);});
    pechat_vector(N,u_real);
    err=get_err(N, y_next, u_real);
    printf("err=%le\n",err);
    //-----------------------------------------------------------
    
    free(a);
    free(b);
    free(c);
    free(f);
    free(u);
    free(u_real);
    free(y_tek);
    free(y_next);
    

    
    printf("Goodbuy!\n");
    
}
