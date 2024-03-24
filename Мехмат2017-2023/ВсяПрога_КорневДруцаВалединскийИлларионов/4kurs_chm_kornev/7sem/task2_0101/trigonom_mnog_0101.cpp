#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



static char* type_of_func;



double func(double x){
    if (strcmp(type_of_func,"myfunc1")==0){ return x*x + cos(5*x*x*x - 2);}
    else if (strcmp(type_of_func,"myfunc2")==0){return sin(M_PI*5.5*x);}
    else {return (x>0.5)?-1+x:-x;} //(strcmp(type_of_func,"mufunc3")==0)

}


int minim(int a, int b){
    return (a<b)?a:b;
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

double scal_proizv_fphi(double* mas_f, int n, int a, int N,  double h){
    double otv=0;
    for (int k=1; k<=N-1; k=k+1) otv=otv+mas_f[k]*sin(M_PI*(n-0.5)*(a+k*h));
    otv=otv*h;
    return otv;
	
}

double scal_proizv_phi_phi(int n, int a, int N,  double h){
    double otv=0;
    for (int k=1; k<=N-1; k=k+1) otv=otv+sin(M_PI*(n-0.5)*(a+k*h))*sin(M_PI*(n-0.5)*(a+k*h));
    otv=otv*h;
    return otv;
	
}

double* f2c(double* mas_f, double* mas_c, int a, int N, double h){
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
    double* mas_f=(double*)malloc((N+1)*(sizeof(double)));
    double* mas_c=(double*)malloc((N+1)*(sizeof(double)));
        
    

    
    for (int i=0; i<=N; i=i+1){ fscanf(fin,"%lf",&mas_x[i]);}
    for (int i=0; i<=N; i=i+1){ fscanf(fin,"%lf",&mas_f[i]);}
    fclose(fin);

    double h=(b-a)/(N-0.5);
    
    printf("Vector x:\n");
    pechat_vector(N,mas_x);
    printf("Vector f:\n");
    pechat_vector(N,mas_f);
    mas_c=f2c(mas_f, mas_c, a, N, h);
    printf("Vector c:\n");
    pechat_vector(N,mas_c);

            
    
    char* output_name =(char*)malloc(50*(sizeof(double)));

    output_name=strcpy(output_name,"output_");
    char tmp_str[3];
    sprintf(tmp_str,"%d",N);
    printf("tmp_str=%s\n", tmp_str);
    output_name=strcat(output_name, tmp_str);
    output_name=strcat(output_name,argv[4]);
    output_name=strcat(output_name,argv[5]);
    output_name=strcat(output_name, ".txt");
    printf("output_name=%s\n", output_name);


       
    if (strcmp(argv[4],"ravnom")==0) {FILE* fout;
    				      fout=fopen(output_name,"w");
    				      if (fout==0) {printf("Cannot open %s\n",output_name); return -1;}

				      double err=fmax(func(a) - trig_mnog(N,a,mas_c),-func(a) - trig_mnog(N,a,mas_c));

                                      //double m= N+ (2*N-2);
			    	      double h1 = h/3;
				      for (int i=0; i<=(1+0.5*h)/h1; i=i+1) {double uzel = a +i*h1;
				 				     printf("%f %f %f %le \n", uzel, func(uzel), trig_mnog(N,uzel,mas_c),func(uzel)- trig_mnog(N,uzel,mas_c));
								     fprintf(fout,"%f %f %f %le \n", uzel, func(uzel), trig_mnog(N,uzel,mas_c),func(uzel)- trig_mnog(N,uzel,mas_c));
								    err=fmax(err,abs(func(uzel)- trig_mnog(N,uzel,mas_c)));
								    
                                 				   }
				      printf("err=%f\n",err);
				      fclose(fout);
				
				      FILE* fout_for_find_p;
    				      fout_for_find_p=fopen("fout_for_find_p.txt","a");
				      if (fout_for_find_p==0) {printf("Cannot open fout_for_find_p.txt\n"); }
				      fprintf(fout_for_find_p, "%d %f %f\n", N, log(N), log(1/err));				
				      fclose(fout_for_find_p);

				    }

   

    
    
    free(mas_f);
    free(mas_c);
    free(output_name);
    
    
    
    printf("Goodbuy!\n");
    
    return 0;

}
