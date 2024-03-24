#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctime>
#include <math.h>
#include "matrices.h"
//#include "get_time.h"
#include "synchronize.h"

#define matrix(i,j) matrix[(i-1)*n +j-1]
#define obr_matrix(i,j) obr_matrix[(i-1)*n +j-1]
#define stolb(i) stolb[(i-1)]


typedef struct _ARGS
{
  double* matrix;      
  double* obr_matrix;
  double* stolb;      
  int n;                
  int thread_num;       
  int total_threads;    
} ARGS;


//static long int threads_total_time = 0;
//static pthread_mutex_t threads_total_time_mutex = PTHREAD_MUTEX_INITIALIZER;


int one_step(ARGS* pargs,int step){
    double* matrix = pargs->matrix;
    double* obr_matrix = pargs->obr_matrix;
    
    double* stolb=pargs->stolb;
    int thread_num =pargs-> thread_num;
    int total_threads =pargs-> total_threads;
    int n=pargs->n;
    
    if(int(matrix(step,step))==0){ printf("matrix(step,step)==0!");return -1;}
    
    synchronize(total_threads);
    if(thread_num==3)printf("Stolb in step= %d thread %d :",step,thread_num);
    synchronize(total_threads);
    if(thread_num==3) print_vector(stolb,n);
    synchronize(total_threads);
      
    
    int amount_kuskov = int(step-1)/(int (total_threads));
    int start_stolb=thread_num + amount_kuskov*total_threads;
    int pos_in_kusok=step%total_threads;
    if (step%total_threads==0) pos_in_kusok=total_threads;
    if(pos_in_kusok > thread_num) start_stolb=start_stolb + total_threads;
    printf("thread_num=%d step=%d  amount_kuskov=%d start_stolb=%d\n", thread_num,step,amount_kuskov,start_stolb);
    
    
    
    for(int j=thread_num;j<=n;j=j+total_threads){
	for(int i=step+1; i<=n; i=i+1){
	    matrix(i,j)=matrix(i,j)-stolb(i)*matrix(step,j)/matrix(step,step);
	}
     
    }
    
    for(int j=thread_num;j<=n;j=j+total_threads){
	for(int i=step+1; i<=n; i=i+1){
	    obr_matrix(i,j)=obr_matrix(i,j)-stolb(i)*obr_matrix(step,j)/obr_matrix(step,step);
	}
     
    }
    
    synchronize(total_threads);
    if(thread_num==3){printf("After step %d:\n",step);print_matrix(matrix,n);}
    synchronize(total_threads);
  

    return 0;
}

int gauss_not_threaded(ARGS* pargs){
    int n=pargs->n;
    double* matrix = pargs->matrix;
    double* stolb=pargs->stolb;
    int otv;
    //int total_threads=pargs->total_threads;

    for (int step=1; step<=n; step=step+1){
	for (int i=step; i<=n; i=i+1){stolb(i)=matrix(i,step);}
	otv=one_step(pargs,step);
	if(otv==-1) return -1;
    }
    return 0;
}


void* func_for_thread (void* pa)
{
  ARGS* pargs = (ARGS*)pa;
  long int t;
  

  printf ("Thread %d started\n", pargs->thread_num);

  //t = get_time ();     
  
  //printf ("Hello from Thread %d \n", pargs->thread_num);
  
  //double* matrix = pargs->matrix;
  //double* obr_matrix = pargs->obr_matrix;
  //int thread_num =pargs-> thread_num;
  //int total_threads =pargs-> total_threads;
  //int n=pargs->n;
  
  
  int otv=gauss_not_threaded(pargs);
  if (otv==-1){printf("Net obratnoy!\n");}
  
  /*
  for (int i=1; i<= n; i=i+1){
     for(int j=thread_num;j<=n;j=j+total_threads){
	//matrix(i,j)=thread_num;
	obr_matrix(i,j)=thread_num;
     }

  }
  */
  
  
  //t = get_time () - t;  
  //pthread_mutex_lock (&threads_total_time_mutex);
  //threads_total_time += t;
  //pthread_mutex_unlock (&threads_total_time_mutex);

  printf ("Thread %d finished, time = %ld\n",pargs->thread_num, t);

  return 0;
}



int main (int argc, char * argv[])
{
  pthread_t* threads;
  ARGS* args;
  int nthreads;
  long int t_full;

  int n;                
  double* matrix;       
  double* obr_matrix;
  double* stolb;       
  int i;

  if (!(argc == 3 || argc==4) || !(nthreads = atoi (argv[1])) || !(n = atoi (argv[2]))){
      printf ("Usage: %s nthreads n\n", argv[0]);
      return 1;
    }

  if (!(threads = (pthread_t*)malloc (nthreads * sizeof (pthread_t)))){
      fprintf (stderr, "Not enough memory!\n");
      return 1;
    }
  if (!(args = (ARGS*) malloc (nthreads * sizeof (ARGS)))){
      fprintf (stderr, "Not enough memory!\n");
      return 2;
    }

  if (!(matrix = (double*)malloc (n * n * sizeof (double)))){
      fprintf (stderr, "Not enough memory!\n");
      return 3;
    }
    
  if (!(obr_matrix = (double*) malloc (n*n * sizeof (double)))){
      fprintf (stderr, "Not enough memory!\n");
      return 4;
    }


 if (!(stolb = (double*) malloc (n * sizeof (double)))){
      fprintf (stderr, "Not enough memory!\n");
      return 5;
    }
 


  
  int smogli_prochitat=get_matrix (matrix, n, argc, argv);
  if (smogli_prochitat ==-1){printf("Cannot read matrix; program terminates.\n"); 
                            free (threads);free (args);free (matrix);free (obr_matrix);free(stolb);
 			    return -1;}

  init_vector (stolb, n);
  
  if(argc==4){
  FILE*f;
  f=fopen("input.txt","r");
  if(f==0){printf("Cannot open file\n"); return -1;}
  for(int i=1;i<=n; i=i+1){
    for(int j=1; j<=n; j=j+1){
    fscanf(f,"%lf",&matrix(i,j));
    }
  }
  
  fclose(f);
  }
  
  printf ("Matrix:\n");
  print_matrix (matrix, n);
  printf ("Stolb:\n");
  print_vector (stolb, n);
  
  
  for(int i=1; i<=n; i=i+1)
    for(int j=1; j<=n; j=j+1)
	obr_matrix(i,j)=1;
  printf ("Obr_Matrix:\n");
  print_matrix(obr_matrix,n);
 
 



  
  for (i = 0; i < nthreads; i++){
      args[i].matrix = matrix;
      args[i].obr_matrix =obr_matrix;
      args[i].n = n;
      args[i].thread_num = i+1;
      args[i].total_threads = nthreads;
      args[i].stolb=stolb;
    }

  
  //t_full = get_full_time ();
  t_full=clock();
  
  for (i = 0; i < nthreads; i++){
      if (pthread_create (&threads[i], 0,func_for_thread,&args[i])){
          fprintf (stderr, "cannot create thread #%d!\n",i);
          return 10;
        }
    }
  for (i = 0; i < nthreads; i++){
      if (pthread_join (threads[i], 0)) fprintf (stderr, "cannot wait thread #%d!\n", i);
    }
    
  //t_full = get_full_time () - t_full;
  //if (t_full == 0) t_full = 1; /* очень быстрый компьютер... */
  t_full=(clock()-t_full)/CLOCKS_PER_SEC;

  print_matrix(matrix,n);
  printf ("Obr_Matrix:\n");
  print_matrix(obr_matrix,n);
  
  printf("time=%ld\n",t_full);
 
  free (threads);
  free (args);
  free (matrix);
  free (obr_matrix);
  free(stolb);


  //printf ("Total full time = %ld, total threads time = %ld (%ld%%), per thread = %ld\n",
//				t_full, threads_total_time,(threads_total_time * 100) / t_full,threads_total_time / nthreads);

  return 0;
}

