#ifndef ARGS_H
#define ARGS_H

typedef struct _ARGS
{
  double* matrix;      
  double* obr_matrix;
  double* stolb;      
  int n;                
  int thread_num;       
  int total_threads;
  int* has_obr_matrix;
  double* t_full_astr; 
  double  norma; 
  
} ARGS;

#endif
