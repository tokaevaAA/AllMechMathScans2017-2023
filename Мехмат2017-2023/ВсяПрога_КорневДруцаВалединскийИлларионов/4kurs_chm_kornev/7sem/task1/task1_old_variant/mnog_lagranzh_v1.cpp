#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define A(i,j) A[(i-1)*n+(j-1)]
#define X(i) X[i-1]
#define B(i) B[i-1]
#define mas1(i) mas1[i-1]
#define mas2(i) mas2[i-1]





static char* type_of_func;



double func(double x){
    if (strcmp(type_of_func,"myfunc")==0){return x*x +cos(5*x*x*x - 2);}
    else if (strcmp(type_of_func,"runge")==0){return 1/(25*x*x + 1);}
    else {return (x>0)?x:-x;} //(strcmp(type_of_func,"modul")==0)

}


int minim(int a, int b){
    return (a<b)?a:b;

}


void pechat_matrix(int n, double* A){
    printf("Start Pechat matrix:\n");
    for (int i=0; i<(minim(n,5)); i=i+1){
	for (int j=0; j<minim(n,5); j=j+1){
	    printf("%f ",A[i*n+j]);
	}
	printf("\n");
    }
    printf("End Pechat matrix\n");
}


void pechat_vector(int n, double* B){
    printf("Start Pechat vector:\n");
    for (int i=0; i<minim(n,5); i=i+1){
	    printf("%f ",B[i]);
    }
    printf("\n");
    printf("End Pechat vector\n");
}

void pechat_matrix_rasshir(int n, double* A, double* B){
    //if (n>15) return;
    printf("Start Pechat matrix:\n");
    for (int i=0; i<minim(n,5); i=i+1){
	for (int j=0; j<minim(n,5); j=j+1){
	    printf("%f ",A[i*n+j]);
	}
	printf(" | ");
        
	printf("%f ",B[i]);
        
	printf("\n");
    }
    printf("End Pechat matrix\n");
}






int generate_input(double a, double b, int n, char* tip_uzlov, const char* filename){
    FILE*fout;
    fout=fopen(filename,"w");
    if (fout==0) {printf("Cannot open %s\n", filename); return -1;}
 
    if (strcmp(tip_uzlov,"ravnom")==0) {printf("ravnom uzl\n");
					double h = (b-a)/(n-1);
					for (int i=0; i<=n-1; i=i+1) fprintf(fout, "%f ", a + i*h);
					fprintf(fout,"\n");
					for (int i=0; i<=n-1; i=i+1) fprintf(fout,"%f ", func(a + i*h));
					}

    if (strcmp(tip_uzlov,"chebushov")==0){printf("chebushov uzl\n");
				         for (int i=n; i>=1; i=i-1) fprintf(fout, "%f ", (a+b)/2 + 0.5*(b-a)*cos(M_PI*(2*i-1)/(2*n)));
					 fprintf(fout,"\n");
					 for (int i=n; i>=1; i=i-1) fprintf(fout,"%f \n", func((a+b)/2 + 0.5*(b-a)*cos(M_PI*(2*i-1)/(2*n))));
					
					}
    fclose(fout);
    return 0;
					
}

//---------------------------------------------------------------------------------------------------------------------------------------

int one_step(int n, int k, double* A, double* X , double* B){
    //printf("STEP =%d\n",k);

    double s=0;  double skal_product;
    for (int j=k+1; j<n+1; j=j+1){s=s+(A(j,k))*(A(j,k));} //printf("s=%f\n",s);

    double norma_Ak= sqrt( (A(k,k))*(A(k,k))+s ); //printf("norma_Ak=%f\n",norma_Ak);

    X(k)=A(k,k)-norma_Ak;
    
    double norma_X=sqrt( (X(k))*(X(k)) +s ); //printf("norma_X=%f\n",norma_X);
    
    
    
     if (k<n){
   
	if (norma_X<0.00000000000001){printf("Net obratnoy : norma=0; k=%d.\n",k); return -1;}

	//for(int j=1; j<k; j=j+1){X(j)=0;}
	if(k>1) X(k-1)=0;
	
	
	X(k)=X(k)/norma_X;
	for(int j=k+1; j<n+1; j=j+1){X(j)=(A(j,k))/norma_X;}
	
	
	for(int j=k;j<n+1;j=j+1){
	    skal_product=0;
	    for(int i=k;i<n+1;i=i+1){skal_product = skal_product+X(i)*A(i,j);}
            for(int i=k;i<n+1;i=i+1){A(i,j)=A(i,j)-2*skal_product*X(i);}
	    	    
	}

	
	skal_product=0;
	for(int i=k;i<n+1;i=i+1){skal_product = skal_product+X(i)*B(i);}
        for(int i=k;i<n+1;i=i+1){B(i)=B(i)-2*skal_product*X(i);}
	    	    
    
    }
    
    //pechat_matrix_rasshir(n,A,B);
    return 0;

}


void obratny_hod(int n, int k, double* A, double* B){
    //printf("obratny_hod, k=%d\n",k);
    double Akk=A(k,k);
    for (int j=k;j<n+1;j=j+1){A(k,j)=A(k,j)/Akk;}
    B(k)=B(k)/Akk;
        
    for(int i=k-1; i>0; i=i-1){ B(i)= B(i)-A(i,k)*B(k);}
    

    for(int i=k-1; i>0; i=i-1){A(i,k)=0;} //not compulsory
			  
    //pechat_matrix_rasshir(n,A,B);
    


}


int  algoritm(int n, double* A, double* X, double* B){
    int flag=0;
    for (int k=1; k<n+1; k=k+1){flag=one_step(n,k,A,X,B);
				 if (flag==-1){return -k;}
				}
    if (abs(A(n,n))<0.00000000000001) return -(n+1);
    for (int k=n; k>0; k=k-1){obratny_hod(n,k,A,B);}
    return 0;

}


double P_n_1(int n, double x, double* B){
    double t=1.0;
    double otv=0;
    for (int i=0; i<=n-1; i=i+1){otv=otv+B[i]*t; t=t*x;}
    return otv;


}

double F_i(int n, int i, double x, double* mas1){
    double otv=1;
    for (int j=1; j<=n; j=j+1){ if (j!=i) {otv=otv*(x-mas1(j))/(mas1(i)-mas1(j)); } }
    return otv;

}

double L_n(int n,  double x, double* mas1, double* mas2){
    double otv=0;
    for (int i=1; i<=n; i=i+1){ otv=otv + mas2(i)*F_i(n,i, x,mas1); }
    return otv;

}



//---------------------------------------------------------------------------------------------------------------------------------------


int main(int argc, char** argv){
    printf("Hello!\n ");
    
    if (argc != 6) {printf("Usage: ./a.out a b n ravnom/chebushov myfunc/runge/modul \n"); return -1;}
    
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    int n = atoi(argv[3]);
    type_of_func = argv[5];
    printf("a=%f b=%f n=%d is_ravnom=%d %s\n", a,b,n, strcmp(argv[4], "ravnom"),type_of_func);

    
    int flag=generate_input(a, b, n, argv[4],"input.txt");
    if (flag==-1) {printf("Problems in generate_input. Program terminates.\n"); return -1;}

    
    FILE*fin;
    fin=fopen("input.txt","r");
    if (fin==0) {printf("Cannot open input.txt. Program terminates. \n");  return -1;}


    double* A=(double*)malloc(n*n*(sizeof(double)));
    double* X=(double*)malloc(n*(sizeof(double)));
    double* B=(double*)malloc(n*(sizeof(double)));
    double* mas1=(double*)malloc(n*(sizeof(double)));
    double* mas2=(double*)malloc(n*(sizeof(double)));
    
    
    

    
    for (int i=1; i<=n; i=i+1){ double t;
				fscanf(fin,"%lf",&t);
				A(i,1)=1.0;
				for (int j=2; j<=n; j=j+1) {A(i,j)=t*A(i,j-1);};
				mas1(i)=t;
				}
    for (int i=1; i<=n; i=i+1){ double t;
				fscanf(fin,"%lf",&t);
				B(i)=t;
				mas2(i)=t;
				}
    fclose(fin);

    
    //pechat_matrix_rasshir(n,A,B);

    flag=algoritm(n,A,X,B);
    //for (int k=1; k<n+1; k=k+1){one_step(n,k,A,X,B);}
    //for (int k=n; k>0; k=k-1){obratny_hod(n,k,A,B);}


    printf("flag=%d\n",flag);
    if(flag < 0 ){printf("Net obratnoy! Program terminates!\n");free(A); free(B); free(X); free(mas1); free(mas2); return -1;}

    //pechat_matrix_rasshir(n,A,B);

    
    char* output_name =(char*)malloc(50*(sizeof(double)));
    output_name=strcat(output_name,"output_");
    char tmp_str[30];
    //tmp_str[0]=n/10 +'0';//tmp_str[1]=n%10+'0';//tmp_str[2]=0;
    sprintf(tmp_str,"%d",n);
    printf("tmp_str=%s\n", tmp_str);
    output_name=strcat(output_name, tmp_str);
    output_name=strcat(output_name,argv[4]);
    output_name=strcat(output_name,argv[5]);
    output_name=strcat(output_name, ".txt");
    printf("output_name=%s\n", output_name);


       
    if (strcmp(argv[4],"ravnom")==0) {FILE*fout;
    				      fout=fopen(output_name,"w");
    				      if (fout==0) {printf("Cannot open output_ravnom.txt\n"); return -1;}
                                      double m= n+ (2*n-2);
			    	      double h = (b-a)/(m-1);
				      for (int i=0; i<=m-1; i=i+1) {double uzel = a +i*h;
				 				     fprintf(fout,"%f  %f %f %f %le %le %le \n", 
											uzel, func(uzel), P_n_1(n,uzel,B),L_n(n,uzel,mas1,mas2),
											func(uzel)- P_n_1(n,uzel,B),func(uzel) - L_n(n,uzel,mas1,mas2),
											P_n_1(n,uzel,B) - L_n(n,uzel,mas1,mas2));
                                 				     printf("%f  %f %f %f %le %le %le \n", 
											uzel, func(uzel), P_n_1(n,uzel,B), L_n(n,uzel,mas1,mas2),
											func(uzel)- P_n_1(n,uzel,B),func(uzel) - L_n(n,uzel,mas1,mas2),
											P_n_1(n,uzel,B) - L_n(n,uzel,mas1,mas2));
			      					     }
				      fclose(fout);
					
					}

    if (strcmp(argv[4],"chebushov")==0){FILE*fout;
    				        fout=fopen(output_name,"w");
    				        if (fout==0) {printf("Cannot open output_chebushov.txt\n"); return -1;}
					
				        for (int i=n; i>=1; i=i-1) {double uzel = mas1(i);
				 				     fprintf(fout,"%f  %f %f %f %le %le %le \n", 
											uzel, func(uzel), P_n_1(n,uzel,B),L_n(n,uzel,mas1,mas2),
											func(uzel)- P_n_1(n,uzel,B),func(uzel) - L_n(n,uzel,mas1,mas2),
											P_n_1(n,uzel,B) - L_n(n,uzel,mas1,mas2));
                                 				     printf("%f  %f %f %f %le %le %le\n", 
											uzel, func(uzel), P_n_1(n,uzel,B),L_n(n,uzel,mas1,mas2),
  											func(uzel)- P_n_1(n,uzel,B),func(uzel) - L_n(n,uzel,mas1,mas2),
											P_n_1(n,uzel,B) - L_n(n,uzel,mas1,mas2));
								     if (i >=2){double h = (mas1(i)-mas1(i-1))/3;
										double dopuzel1= uzel-h;
										double dopuzel2= uzel-2*h;
										fprintf(fout,"%f  %f %f %f %le %le %le\n", 
											dopuzel1, func(dopuzel1), P_n_1(n,dopuzel1,B),L_n(n,dopuzel1,mas1,mas2),
											func(dopuzel1)- P_n_1(n,dopuzel1,B),func(dopuzel1) - L_n(n,dopuzel1,mas1,mas2),
											P_n_1(n,dopuzel1,B) - L_n(n,dopuzel1,mas1,mas2));
                                 				                printf("%f  %f %f %f %le %le %le\n", 
											dopuzel1, func(dopuzel1), P_n_1(n,dopuzel1,B),L_n(n,dopuzel1,mas1,mas2),
											func(dopuzel1)- P_n_1(n,dopuzel1,B),func(dopuzel1) - L_n(n,dopuzel1,mas1,mas2),
											P_n_1(n,dopuzel1,B) - L_n(n,dopuzel1,mas1,mas2));
										fprintf(fout,"%f  %f %f %f %le %le %le \n", 
											dopuzel2, func(dopuzel2), P_n_1(n,dopuzel2,B),L_n(n,dopuzel2,mas1,mas2),
											func(dopuzel2)- P_n_1(n,dopuzel2,B),func(dopuzel2) - L_n(n,dopuzel2,mas1,mas2),
											P_n_1(n,dopuzel2,B) - L_n(n,dopuzel2,mas1,mas2));
                                 				     		printf("%f  %f %f %f %le %le %le\n", 
											dopuzel2, func(dopuzel2), P_n_1(n,dopuzel2,B),L_n(n,dopuzel2,mas1,mas2),
											func(dopuzel2)- P_n_1(n,dopuzel2,B),func(dopuzel2) - L_n(n,dopuzel2,mas1,mas2),
											P_n_1(n,dopuzel2,B) - L_n(n,dopuzel2,mas1,mas2));
										}
			      					    }


					}


    //set terminal png  size 640,480
    //set output "plot_ravnom_func.png"
    //plot 'output_ravnom_uzel_func_P_n_1_L_n.txt' using 1:2 with lines, 'output_ravnom_uzel_func_P_n_1_L_n.txt' using 1:3 with lines, 'output_ravnom_uzel_func_P_n_1_L_n.txt' using 1:4 with lines,  'output_ravnom_uzel_func_P_n_1_L_n.txt' using 1:2 with points 
    //plot 'output_chebushov_uzel_func_P_n_1_L_n.txt' using 1:2 with lines, 'output_chebushov_uzel_func_P_n_1_L_n.txt' using 1:3 with lines, 		'output_chebushov_uzel_func_P_n_1_L_n.txt' using 1:4 with lines

   
    free(A); 
    free(B);
    free(X);
    free(mas1);
    free(mas2);
    free(output_name);
    
    
    
    printf("Goodbuy!\n");
    return 0;

}
