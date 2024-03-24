#include <stdio.h>
#include <math.h>
#include "Algoritm.h"
#include "matrices.h"
#include "ARGS.h"
#include "synchronize.h"



#define matrix(i,j) matrix[(i-1)*n +j-1]
#define obr_matrix(i,j) obr_matrix[(i-1)*n +j-1]
#define stolb(i) stolb[(i-1)]


#define a(i,j) a[(i-1)*n+(j-1)]
#define anew(i,j) anew[(i-1)*n+(j-1)]
#define e(i,j) e[(i-1)*n+(j-1)]




void one_step(ARGS* pargs, int k){
   
    
    double* matrix = pargs->matrix;
    double* obr_matrix = pargs->obr_matrix;
    
    double* stolb=pargs->stolb;
    int thread_num =pargs-> thread_num;
    int total_threads =pargs-> total_threads;
    int n=pargs->n;
   

   
    synchronize(total_threads);
      
    int step=k;
    
    int amount_kuskov = int(step-1)/(int (total_threads));
    int start_stolb=thread_num + amount_kuskov*total_threads;
    int pos_in_kusok=step%total_threads;
    if (step%total_threads==0) pos_in_kusok=total_threads;
    if(pos_in_kusok > thread_num) start_stolb=start_stolb + total_threads;
    //printf("thread_num=%d step=%d  amount_kuskov=%d start_stolb=%d\n", thread_num,step,amount_kuskov,start_stolb);
    
    
        
    double skal_product;

    for(int j=start_stolb; j<=n; j=j+total_threads){
         skal_product=0;
	 for(int l=k;l<=n;l=l+1){
	     skal_product = skal_product+stolb(l)*matrix(l,j);
	    }
          for(int l=k; l<=n; l=l+1){
		  matrix(l,j)=matrix(l,j)-2*skal_product*stolb(l);
		
	  }
	    	    
    }

    for(int j=thread_num; j<=n; j=j+total_threads){
	skal_product=0;
	for(int l=k; l<n+1;l=l+1){
		skal_product = skal_product+stolb(l)*obr_matrix(l,j);
		
	}
        for(int l=k; l<=n;l=l+1){
		obr_matrix(l,j)=obr_matrix(l,j)-2*skal_product*stolb(l);
	}
	    	    
    }
    //synchronize(total_threads);
    
    

}





void metod_otraj_not_threaded(ARGS* pargs){
    
    int n=pargs->n;
    double* matrix = pargs->matrix;
    double* stolb=pargs->stolb;
    //int otv;
    
    double my_almost_null=pargs->norma*1e-10;
    if (pargs->thread_num==1){printf("my almost_null =%le\n",my_almost_null);}
    

    for (int k=1; k<=n-1; k=k+1){
        
	double s=0;  
        for ( int j=k+1; j<n+1; j=j+1){s=s+(matrix(j,k))*(matrix(j,k));} //printf("s=%f\n",s);
	
	if (s< my_almost_null && fabs(matrix(k,k))<my_almost_null){printf("Net obratnoy : norma stolba=0; k=%d.\n",k); *pargs->has_obr_matrix=-1;return;}

	//a esli  (s==0 && fabs(matrix(k,k))>0) - then we are simply multiplying by edinichna matrix, it means nothing is needed to do
	

        
        double norma_ak= sqrt( (matrix(k,k))*(matrix(k,k))+s ); //printf("norma_ak=%f\n",norma_ak);

	//for(int j=1; j<k; j=j+1){stolb(j)=0;}
        if (pargs->thread_num==1){stolb(k)=matrix(k,k)-norma_ak;
        
    
        double norma_x=sqrt( (stolb(k))*(stolb(k)) +s ); //printf("norma_x=%f\n",norma_x);
    
    	if (norma_x<my_almost_null){printf("Net obratnoy : norma_x=0; k=%d.\n",k);*pargs->has_obr_matrix=-2; return; }

	stolb(k)=stolb(k)/norma_x;
	for(int j=k+1; j<n+1; j=j+1){stolb(j)=(matrix(j,k))/norma_x;}
        }
        
	one_step(pargs,k);
        synchronize(pargs->total_threads);
	
	
    }
    
    
    synchronize(pargs->total_threads);
   
    if(fabs(matrix(n,n))<my_almost_null){printf("Nety obr: a(n,n)=0;\n"); *pargs->has_obr_matrix=-3; }
    
    
    if (pargs->thread_num==1){for (int k=n; k>0; k=k-1){obratny_hod(n,k,pargs->matrix,pargs->obr_matrix);}}
    
    

}

void  obratny_hod(int n, int k, double* a, double* e){
        
    int i; 
    int j; 
    int l=0; 
    double akk=a(k,k);

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






