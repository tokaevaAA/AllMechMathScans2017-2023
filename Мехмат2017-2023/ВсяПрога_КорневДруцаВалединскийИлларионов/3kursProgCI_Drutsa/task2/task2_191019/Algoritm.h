#ifndef ALGORITM_H
#define ALGORITM_H


void to_3diag_vid_Tij(double* a, int n, int i, int j,int k);
void to_3diag_vid(double* a, int n);
void matrix_mult(int n, double* a, double* b, double* c);
void count_L_LM_U(double* a, int n,  double lamda);
int indicate_peremena_znaka(double a, double b);
int signum(double x);
int get_chislo_peremen_znaka(double* a, int n,  double lamda );
double norma_matrix(double* a, int n);
int find_sobstv_znach_nomer_k(double* matrix, int n, double norma, int k,  double eps , int needed_amount,double* sobstv_chisla);
void algoritm(double* a, int n, double* sobstv_chisla, double eps);

#endif
