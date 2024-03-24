#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctime>
#include "Algoritm.h"


#define a(i,j) a[(i-1)*n+(j-1)]
#define anew(i,j) anew[(i-1)*n+(j-1)]
#define e(i,j) e[(i-1)*n+(j-1)]
#define x(i) x[i-1]

int minim(int a, int b){
    return (a<b)?a:b;

}

double func (int i, int j){
	double otv;
	//otv= 1.0/(1+i+j);
	otv=-fabs(i-j);
	//printf("i+j=%d\n",i+j);
	//otv=0;
	if (i==999) otv=0;;
	return otv;

}

void pechat_matrix(int n, double* a){
    //if (n>15) return;
    printf("Start Pechat matrix:\n");
    for (int i=0; i<(minim(n,5)); i=i+1){
	for (int j=0; j<minim(n,5); j=j+1){
	    printf("%f ",a[i*n+j]);
	}
	printf("\n");
    }
    printf("End Pechat matrix\n");
}


void pechat_vector(int n, double* b){
    //if (n>15) return;
    printf("Start Pechat vector:\n");
    for (int i=0; i<minim(n,5); i=i+1){
	
	    printf("%f\n",b[i]);
	
    }
    printf("End Pechat vector\n");
}


void pechat_matrix_rasshir(int n, double* a, double* e){
    if (n>15) return;
    printf("Start Pechat matrix:\n");
    for (int i=0; i<minim(n,5); i=i+1){
	for (int j=0; j<minim(n,5); j=j+1){
	    printf("%f ",a[i*n+j]);
	}
	printf(" | ");
        for (int j=0; j<minim(n,5); j=j+1){
	    printf("%f ",e[i*n+j]);
        }
	printf("\n");
    }
    printf("End Pechat matrix\n");
}



int get_matrix_from_file(int n, double* a,FILE*f){
    int n0;
    fscanf(f,"%d",&n0);
    printf("n0=%d\n",n0);
    if (n0 != n){printf("Matrix size does not match; Program terminates;\n"); return -1;}

    for (int i=1; i<n+1; i=i+1){
	for (int j=1; j<n+1; j=j+1){
	    fscanf(f,"%lf ",&a(i,j));    
        }
        	
    }
    return 0;
    
}

int get_matrix_po_formule(int n, double*a){
    //printf("get po formule\n");
    for (int i=1; i<n+1; i=i+1){
	for (int j=1; j<n+1; j=j+1){
	    //a(i,j)=1.0/(1+i+j);
	    a(i,j)=func(i,j);
	    //printf("i=%d j=%d 1/(1+i+j)= %f\n",i,j,1.0/(1+i+j));    
        }
        
    }
    //pechat_matrix(n,a);
    return 0;

}


int get_matrix(int n, double* a,  int argv, char** argc ){
    int otv=0;
    if (argv==3){
    	FILE*f;
    	f=fopen(argc[2],"r"); if (f==0){printf("Cannot open %s\n",argc[2]);}

	otv= get_matrix_from_file(n,a,f);
        fclose(f);
	}

    else if (argv ==2){
    otv= get_matrix_po_formule(n,a);

    }
    return otv;
	
	
}

/*

void one_step(int n, int k, double* a, double* x , double* e){
    printf("STEP =%d\n",k);

    double s=0; int j=0; int l=0; double skal_product;
    for ( j=k+1; j<n+1; j=j+1){s=s+(a(j,k))*(a(j,k));}
    //printf("s=%f\n",s);

    double norma_ak= sqrt( (a(k,k))*(a(k,k))+s );
    //printf("norma_ak=%f\n",norma_ak);

    x(k)=a(k,k)-norma_ak;
    for(j=k+1; j<n+1; j=j+1){x(j)=a(j,k);}
    double norma_x=sqrt( (x(k))*(x(k)) +s );
    //printf("norma_x=%f\n",norma_x);
    
    if (k!=n || ( k==n && norma_ak > a(k,k))){
	for(j=1; j<k; j=j+1){x(j)=0;}

	for(j=k; j<n+1; j=j+1){x(j)=x(j)/norma_x;}
        //pechat_vector(n,x);
	
	for(j=1;j<n+1;j=j+1){
	    skal_product=0;
	    for(l=1;l<n+1;l=l+1){
		    skal_product = skal_product+x(l)*a(l,j);
		
	    }
            for(l=1;l<n+1;l=l+1){
		    a(l,j)=a(l,j)-2*skal_product*x(l);
		
	    }
	    	    
	}

	for(j=1;j<n+1;j=j+1){
	    skal_product=0;
	    for(l=1;l<n+1;l=l+1){
		    skal_product = skal_product+x(l)*e(l,j);
		
	    }
            for(l=1;l<n+1;l=l+1){
		    e(l,j)=e(l,j)-2*skal_product*x(l);
		
	    }
	    	    
	}
    
    }
    
        
    
    
    //pechat_matrix_rasshir(n,a,e);
    
   


}


void obratny_hod(int n, int k, double* a, double* e){
    printf("obratny_hod, k=%d\n",k);
    int i; int j; int l=0; double akk=a(k,k);
    for (i=k;i<n+1;i=i+1){a(k,i)=a(k,i)/akk;}
    for (i=1;i<n+1;i=i+1){e(k,i)=e(k,i)/akk;}
    
    //pechat_matrix_rasshir(n,a,e);

    
    for(j=k-1; j>0; j=j-1){ 
	for (l=1; l<n+1; l=l+1){
		e(j,l)= e(j,l)-a(j,k)*e(k,l);
				}
    }

    for(j=k-1; j>0; j=j-1){a(j,k)=0;}
			  
    //pechat_matrix_rasshir(n,a,e);
    


}


void algoritm(int n, double* a, double* x, double* e){
    for (int k=1; k<n+1; k=k+1){one_step(n,k,a,x,e);}
    for (int k=n; k>0; k=k-1){obratny_hod(n,k,a,e);}

}


*/


void nevazka_matrix_mult(int n,  double* a, double* e , double* anew){
    double tmp;
    int i; int j; int l;
    
    
        
    for (i=1; i<n+1; i=i+1){
	for ( j=1; j<n+1; j=j+1){
	    //printf("i=%d j=%d \n",i,j);
	    tmp=0;
	    for(l=1; l<n+1;l=l+1){tmp=tmp+a(i, l)*e(l,j); }
            anew(i,j)=tmp;
	}
    }
        
    for (i=1; i<n+1; i=i+1){
	for (j=1; j<n+1; j=j+1){
            e(i,j)=anew(i,j);
	}
    }
    printf("a*e=\n");
    pechat_matrix(n,anew);
    
}



double nevazka(int n, double* a, double* e){

    double* anew=(double*)malloc(n*n*sizeof(double));
    
    nevazka_matrix_mult(n,a,e,anew);
   
    for (int i=1; i<n+1; i=i+1){e(i,i)=e(i,i)-1;}
    
    
    double tmp=0; 
    double tekmax=0;

    for (int i=1; i<n+1; i=i+1){
	tmp=0;
	for (int j=1; j<n+1; j=j+1){
            tmp=tmp+fabs(e(i,j));
	}
	if (tmp>tekmax) tekmax=tmp;
    }
    free(anew);
    return tekmax;
    


}





int main(int argv,char** argc){
    printf("Hello\n");
    //printf("minim(3,2)=%d\n",minim(3,2));
    //printf("argv=%d argc[0]= %s argc[1]= %s \n",argv,argc[0],argc[1]);
    if (argv==1){printf("Invalid input; you had to enter n.\n"); return 0;}
    
    int n=atoi(argc[1]);
    printf("n=%d\n",n);
    
    
    double* a=(double*)malloc(n*n*sizeof(double));
    
    
    int smogli_prochitat=get_matrix(n,a,argv,argc);
    if (smogli_prochitat== -1){return -1;}

    //pechat_matrix(n,a);
    

    double* x=(double*)malloc(n*(sizeof(double)));
    double* e=(double*)malloc(n*n*(sizeof(double)));

    
    for (int i=1; i<n+1; i=i+1){
	for (int j=1; j<n+1; j=j+1){
            if(i==j) {e(i,j)=1;}
     	    else {e(i,j)=0;}
	}
    }


    double t= clock();
    
    
    //for (int k=1; k<n+1; k=k+1){one_step(n,k,a,x,e);}
    //for (int k=n; k>0; k=k-1){obratny_hod(n,k,a,e);}
    int flag=algoritm(n,a,x,e);

    //pechat_matrix_rasshir(n,a,e);
    //pechat_matrix(n,e);


    t=(clock()-t)/CLOCKS_PER_SEC;
    printf("time needed:= %f\n",t);
    
    pechat_matrix(n,e);
    
    if (flag==-1) printf("Net obratnoy, a(n,n)==0 !\n");
    if (flag!=-1){
    
    get_matrix(n,a,argv,argc);
    double nev=nevazka(n,a,e);
    printf("nevazka= %le\n",nev);
    }

    free(a);
    free(x);
  
    free(e);

    
   
    printf("Goodbuy\n");
   
    
    return 0;
    


}