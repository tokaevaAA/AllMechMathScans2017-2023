#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Algoritm.h"

#define a(i,j) a[(i-1)*n+(j-1)]
#define anew(i,j) anew[(i-1)*n+(j-1)]
#define e(i,j) e[(i-1)*n+(j-1)]
#define x(i) x[i-1]

void pechat_vector(int n, double* x);
void pechat_matrix_rasshir(int n, double*a,double*e);


int one_step(int n, int k, double* a, double* x , double* e){
    printf("STEP =%d\n",k);

    double s=0; int j=0; int l=0; double skal_product;
    for ( j=k+1; j<n+1; j=j+1){s=s+(a(j,k))*(a(j,k));} //printf("s=%f\n",s);

    double norma_ak= sqrt( (a(k,k))*(a(k,k))+s ); //printf("norma_ak=%f\n",norma_ak);

    x(k)=a(k,k)-norma_ak;
    //for(j=k+1; j<n+1; j=j+1){x(j)=a(j,k);}
    
    double norma_x=sqrt( (x(k))*(x(k)) +s ); //printf("norma_x=%f\n",norma_x);
    
    
    
     if (k<n){
    //else if (k!=n ){
	if (norma_x<0.00000000000001){printf("Net obratnoy : norma=0; k=%d.\n",k); return -1;}
	//for(j=1; j<k; j=j+1){x(j)=0;}
	if(k>1) x(k-1)=0;
	
	
	x(k)=x(k)/norma_x;
	for(j=k+1; j<n+1; j=j+1){x(j)=(a(j,k))/norma_x;}
	
        //pechat_vector(n,x);
	
	for(j=k;j<n+1;j=j+1){
	    skal_product=0;
	    for(l=k;l<n+1;l=l+1){
		    skal_product = skal_product+x(l)*a(l,j);
		    
		
	    }
            for(l=k;l<n+1;l=l+1){
		    a(l,j)=a(l,j)-2*skal_product*x(l);
		
	    }
	    	    
	}

	for(j=1;j<n+1;j=j+1){
	    skal_product=0;
	    for(l=k;l<n+1;l=l+1){
		    skal_product = skal_product+x(l)*e(l,j);
		
	    }
            for(l=k;l<n+1;l=l+1){
		    e(l,j)=e(l,j)-2*skal_product*x(l);
		
	    }
	    	    
	}
    
    
    }
    
        
    
    
    pechat_matrix_rasshir(n,a,e);
    return 0;
    
   


}


void obratny_hod(int n, int k, double* a, double* e){
    //printf("obratny_hod, k=%d\n",k);
    int i; int j; int l=0; double akk=a(k,k);
    for (i=k;i<n+1;i=i+1){a(k,i)=a(k,i)/akk;}
    for (i=1;i<n+1;i=i+1){e(k,i)=e(k,i)/akk;}
    
    //pechat_matrix_rasshir(n,a,e);

    
    for(j=k-1; j>0; j=j-1){ 
	for (l=1; l<n+1; l=l+1){
		e(j,l)= e(j,l)-a(j,k)*e(k,l);
				}
    }

    //for(j=k-1; j>0; j=j-1){a(j,k)=0;}
			  
    //pechat_matrix_rasshir(n,a,e);
    


}


int  algoritm(int n, double* a, double* x, double* e){
    int flag=0;
    for (int k=1; k<n+1; k=k+1){flag=one_step(n,k,a,x,e);
				 if (flag==-1){return -1;}
				}
    if (a(n,n)<0.00000000000001) return -1;
    for (int k=n; k>0; k=k-1){obratny_hod(n,k,a,e);}
    return 0;

}
