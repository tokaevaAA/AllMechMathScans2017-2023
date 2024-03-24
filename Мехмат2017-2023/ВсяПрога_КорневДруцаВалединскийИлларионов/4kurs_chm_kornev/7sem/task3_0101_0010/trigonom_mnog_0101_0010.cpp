#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>



static char* type_of_func;



double func(double x, double y){
    double otv=0;
    
    if (strcmp(type_of_func,"myfunc1")==0){ return x*x + cos(5*x*x*x - 2);}
    else if (strcmp(type_of_func,"myfunc2")==0){return sin(M_PI*2.5*x)*sin(M_PI*2*y);}
    else {return x*(x-2)*y*(y-1);} //(strcmp(type_of_func,"mufunc3")==0)

}


int minim(int a, int b){
    return (a<b)?a:b;
}





void pechat_vector(int N, double* B){
    printf("Start Pechat vector:\n");
    for (int i=0; i<=minim(N,10); i=i+1){
	    printf("%f ",B[i]);
    }
    printf("\n");
    printf("End Pechat vector\n");
}

void pechat_matrix(int N_x, int N_y, double* B){
   
    for (int j=0; j<=minim(N_y,10); j=j+1){
	for (int i=0; i<=minim(N_x,10); i=i+1){
	    printf("%f ",B[j*(N_x+1)+i]);
        }
        printf("\n");
    }
    printf("\n");
    
}






int generate_input(double a_x, double a_y, double b_x, double b_y, int N_x, int N_y, char* tip_uzlov, const char* filename){
    FILE*fout;
    fout=fopen(filename,"w");
    if (fout==0) {printf("Cannot open %s\n", filename); return -1;}
 
    if (strcmp(tip_uzlov,"ravnom")==0){ printf("ravnom uzl\n");
					
					double h_x = (b_x-a_x)/(N_x-0.5);
  					double h_y = (b_y-a_y)/(N_y-0.5);

					for (int j=0; j<=N_y; j=j+1) {
					    for (int i=0; i<=N_x; i=i+1){
						fprintf(fout, "%f ", func(a_x + i*h_x, a_y + (j-0.5)*h_y));
						
					    }
					    fprintf(fout,"\n");
					    
					}

					fprintf(fout,"\n");

					for (int j=0; j<=N_y; j=j+1) {
					    for (int i=0; i<=N_x; i=i+1){
						fprintf(fout, "(%f:%f) ", a_x + i*h_x, a_y + (j-0.5)*h_y);
					    }
					    fprintf(fout,"\n");
					}
					fprintf(fout,"\n");

					
				      }
					
    
    fclose(fout);
    return 0;
					
}

//---------------------------------------------------------------------------------------------------------------------------------------

double scal_proizv_vect_phi_m(double* vect, int m, double a_x, int N_x,  double h_x){
    double otv=0;
    for (int i=1; i<=N_x-1; i=i+1) otv=otv+vect[i]*sin(M_PI*(m-0.5)*(a_x+i*h_x));
    otv=otv*h_x;
    return otv;
	
}

double scal_proizv_vect_ksi_n(double* vect, int n, double a_y, int N_y,  double h_y){
    double otv=0;
    for (int j=1; j<=N_y-1; j=j+1) otv=otv+vect[j]*sin(M_PI*n*(a_y+(j-0.5)*h_y));
    otv=otv*h_y;
    return otv;
	
}



double scal_proizv_phi_phi(int m, double a_x, int N_x,  double h_x){
    double otv=0;
    for (int i=1; i<=N_x-1; i=i+1) otv=otv+sin(M_PI*(m-0.5)*(a_x+i*h_x))*sin(M_PI*(m-0.5)*(a_x+i*h_x));
    otv=otv*h_x;
    return otv;
	
}

double scal_proizv_ksi_ksi(int n, double a_y, int N_y,  double h_y){
    double otv=0;
    for (int j=1; j<=N_y-1; j=j+1) otv=otv+sin(M_PI*n*(a_y+(j-0.5)*h_y))*sin(M_PI*n*(a_y+(j-0.5)*h_y));
    otv=otv*h_y;
    return otv;
	
}


double* f2c(double* mas_f, double* mas_c,  double* dop_x, double* dop_y, double a_x, double a_y, int N_x, int N_y, double h_x, double h_y){


    for (int j=1; j<=N_y-1; j=j+1) {
        for (int i=1; i<=N_x-1; i=i+1){dop_x[i]=mas_f[j*(N_x+1)+i];}
        for (int i=1; i<=N_x-1; i=i+1){
            mas_c[j*(N_x+1) +i] = scal_proizv_vect_phi_m(dop_x, i, a_x, N_x, h_x)/scal_proizv_phi_phi(i, a_x, N_x, h_x);
        }
    }

    
    for (int i=1; i<=N_x-1; i=i+1) {
        for (int j=1; j<=N_y-1; j=j+1){dop_y[j]=mas_c[j*(N_x+1)+i];}
        for (int j=1; j<=N_y-1; j=j+1){ mas_c[j*(N_x+1) +i] = scal_proizv_vect_ksi_n(dop_y, j, a_y, N_y, h_y)/scal_proizv_ksi_ksi(j, a_y, N_y, h_y);
        }
    }
   
    return mas_c;

}






double trig_mnog(int N_x, int N_y, double uzel_x, double uzel_y, double* mas_c){
    double otv=0;
    for (int m=1; m<=N_x-1; m=m+1){
	for (int n=1; n<=N_y-1; n=n+1){
 		otv=otv + mas_c[n*(N_x+1)+m]*sin(M_PI*(m-0.5)*uzel_x)*sin(M_PI*n*uzel_y);
	}
    }
    return otv;
}


//---------------------------------------------------------------------------------------------------------------------------------------


int main(int argc, char** argv){
    printf("Hello!\n ");
    
    if (argc != 9) {printf("Usage: ./a.out a_x b_x N_x a_y b_y N_y ravnom myfunc1/myfunc2/myfunc3 \n"); return -1;}
    
    double a_x = atof(argv[1]);
    double b_x = atof(argv[2]);
    int N_x = atoi(argv[3]);
    double a_y = atof(argv[4]);
    double b_y = atof(argv[5]);
    int N_y = atoi(argv[6]);
    type_of_func = argv[8];
    printf("a_x=%f b_x=%f  N_x=%d a_y=%f  b_y=%f  N_y=%d is_ravnom=%d %s\n", a_x, b_x, N_x, a_y,  b_y,  N_y, strcmp(argv[7], "ravnom"),type_of_func);

    
    int flag=generate_input(a_x, a_y, b_x, b_y, N_x, N_y,  argv[7],"input.txt");
    if (flag==-1) {printf("Problems in generate_input. Program terminates.\n"); return -1;}
    
    
    
    FILE*fin;
    fin=fopen("input.txt","r");
    if (fin==0) {printf("Cannot open input.txt. Program terminates. \n");  return -1;}

    
    //double* mas_x=(double*)malloc((N_x+1)*(N_y+1)*(sizeof(double)));
    double* mas_f=(double*)malloc((N_x+1)*(N_y+1)*(sizeof(double)));
    double* mas_c=(double*)malloc((N_x+1)*(N_y+1)*(sizeof(double)));
    double* dop_x=(double*)malloc((N_x+1)*(sizeof(double)));
    double* dop_y=(double*)malloc((N_y+1)*(sizeof(double)));

    for (int i=0; i<=N_x; i=i+1){dop_x[i]=0;}
    for (int i=0; i<=N_y; i=i+1){dop_y[i]=0;}

    for (int j=0; j<=N_y; j=j+1){
        for (int i=0; i<=N_x; i=i+1){ 
            mas_c[j*(N_x+1)+i]=0;
        }
    }

    
   
    for (int j=0; j<=N_y; j=j+1){
        for (int i=0; i<=N_x; i=i+1){ 
            fscanf(fin,"%lf",&mas_f[j*(N_x+1)+i]);
        }
    }

    fclose(fin);

    double h_x = (b_x-a_x)/(N_x-0.5);
    double h_y = (b_y-a_y)/(N_y-0.5);
    
    //printf("Matrix f:\n");
    //pechat_matrix(N_x, N_y, mas_f);
   
    
    mas_c=f2c(mas_f, mas_c, dop_x, dop_y, a_x, a_y, N_x, N_y, h_x, h_y);
    printf("Matrix c:\n");
    pechat_matrix(N_x,N_y,mas_c);

       
    
    char* output_name =(char*)malloc(50*(sizeof(double)));
    printf("output_name=%s\n",output_name);

    output_name=strcpy(output_name,"output_");
    printf("output_name=%s\n",output_name);


    char tmp_str[10];
    sprintf(tmp_str,"%d%d",N_x,N_y);
    printf("tmp_str=%s\n", tmp_str);
    output_name=strcat(output_name, tmp_str);
    output_name=strcat(output_name,argv[7]);
    output_name=strcat(output_name,argv[8]);
    output_name=strcat(output_name, ".txt");
    printf("output_name=%s\n", output_name);


       
    if (strcmp(argv[7],"ravnom")==0) {FILE* fout;
    				      fout=fopen(output_name,"w");
    				      if (fout==0) {printf("Cannot open %s\n",output_name); return -1;}

				      double err=abs(func(a_x,a_y) - trig_mnog(N_x,N_y,a_x,a_y,mas_c));

                                      
			    	      double h1_x = h_x/3;
  				      double h1_y = h_y/3;
				      
				      
				      for (int j=0; j<(b_y+0.5*h_y)/h1_y  ; j=j+1 ) {
				          for (int i=0; i<=(b_x+0.5*h_x)/h1_x; i=i+1) {
								     double uzel_x = a_x+i*h1_x;
								     double uzel_y = (a_y-h_y/2) +j*h1_y;
							
				 				     printf("%f:%f %f %f %le \n", uzel_y, uzel_x, func(uzel_x,uzel_y), 	trig_mnog(N_x,N_y,uzel_x,uzel_y,mas_c), 											func(uzel_x,uzel_y)-trig_mnog(N_x,N_y,uzel_x,uzel_y,mas_c));
							//fprintf(fout,"%f %f %f %le \n", uzel, func(uzel), trig_mnog(N,uzel,mas_c),func(uzel)- trig_mnog(N,uzel,mas_c));
						
								    err=fmax(err, abs(func(uzel_x,uzel_y)-trig_mnog(N_x,N_y,uzel_x,uzel_y,mas_c)));
								    
                                 	}
				     }


				      printf("err=%le\n",err);
				      fclose(fout);
				
				
				      FILE* fout_for_find_p;
    				      fout_for_find_p=fopen("fout_for_find_p.txt","a");
				      if (fout_for_find_p==0) {printf("Cannot open fout_for_find_p.txt\n"); }
				      fprintf(fout_for_find_p, "%d %f %f\n", N_x, log(N_x*N_y), log(1/err));				
				      fclose(fout_for_find_p);
				

				    }

    printf("output_name:%p\n",output_name);
    free(output_name);
    
    
    free(mas_f);
    free(mas_c);
    free(dop_x);
    free(dop_y);
    
    
    
    
    printf("Goodbuy!\n");
    
    return 0;

}
