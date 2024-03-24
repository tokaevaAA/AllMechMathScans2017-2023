#include<iostream>
#include<fstream>
#include<glpk.h>

void push(int* ia, int* ja, double* arr, int i, int j, double value, int& next){
    ia[next]=i;
    ja[next]=j;
    arr[next]=value;
    ++next;
}

int main(int argc, char** argv){
    if (argc!=3){std::cout<<"Usage: ./a.out q=10000 b=0.9"<<std::endl; return 0;}
    glp_prob* lp_solver;
    glp_smcp solver_params;
    
    int q=atoi(argv[1]); // 10000 num of generated (y1,y2,y3)
    double beta=atof(argv[2]);
    double R=0.011;
    int* ia = (int*)malloc(((q+4)*(q+4)+1)*sizeof(int)); //masssiv for i-index of nonzero elements in matrix a
    int* ja = (int*)malloc(((q+4)*(q+4)+1)*sizeof(int)); //masssiv for j-index of nonzero elements in matrix a
    double* arr=(double*)malloc(((q+4)*(q+4)+1)*sizeof(double)); //massiv for values of nonzero elements in matrix a
    
    lp_solver=glp_create_prob();
    glp_set_prob_name(lp_solver, "Problem P1P2 linear solver");
    glp_set_obj_dir(lp_solver,GLP_MIN); //we want to minimize the functional
    
    //add rows means add linear constraints
    glp_add_rows(lp_solver, q+2); //we have q+2 constraints; (u,x,aplha)
    for (int i=1; i<=q; i=i+1){
        glp_set_row_bnds(lp_solver, i, GLP_LO, 0.0, 0.0); //xTy_k+alpha+uk >=0  lhs<=...<infinity
    }
    glp_set_row_bnds(lp_solver, q+1, GLP_FX, 1.0, 1.0); //x1+x2+x3=1
    glp_set_row_bnds(lp_solver, q+2, GLP_LO, R, R); //xTm>=R
    
    
    
    //add cols means add variables u,x,alpha
    glp_add_cols(lp_solver, q+3+1); //u,x,alpha
    for (int i=1; i<=q; i=i+1){
        glp_set_col_bnds(lp_solver, i, GLP_LO, 0.0, 0.0); //u_k>=0
    }
    for (int i=1; i<=3; i=i+1){
        glp_set_col_bnds(lp_solver, q+i, GLP_LO, 0.0, 0.0); //x_i>=0
    }
    glp_set_col_bnds(lp_solver, q+3+1, GLP_FR, 0.0, 0.0); //x_i>=0
    
    
    
    //fill coef of target functional
    for (int i=1; i<=q; i=i+1){
        glp_set_obj_coef(lp_solver, i, 1/((double)(q)*(1-beta))); //coef of u_k in functional are 1/(q(1-beta))
    }
    for (int i=1; i<=3; i=i+1){
        glp_set_obj_coef(lp_solver, q+i, 0.0); //coef of x_i in functional are 0
    }
    glp_set_obj_coef(lp_solver, q+3+1, 1.0); //coef of alpha in functional
    
    int next=1; //numeration of nonzero elements is from 1 (not from 0)
    std::ifstream in("Generatedy1y2y3.txt");
    for (int i=1; i<=q; i=i+1){
        double y1,y2,y3;
        in>>y1>>y2>>y3;
        push(ia,ja,arr,i,q+1,y1,next); //coef y1 for x1 in xTy_k+alpha+uk >=0
        push(ia,ja,arr,i,q+2,y2,next); //coef y2 for x2 in xTy_k+alpha+uk >=0
        push(ia,ja,arr,i,q+3,y3,next); //coef y3 for x3 in xTy_k+alpha+uk >=0
        push(ia,ja,arr,i,q+4,1.0,next); //coef 1 for alpha in xTy_k+alpha+uk >=0
        push(ia,ja,arr,i,i,1.0,next); //coef 1 for uk in xTy_k+alpha+uk >=0
    }
    push(ia,ja,arr,q+1,q+1,1,next);
    push(ia,ja,arr,q+1,q+2,1,next);
    push(ia,ja,arr,q+1,q+3,1,next);
    
    double m1=0.01000111;
    double m2=0.0043532;
    double m3=0.0137058;
    
    push(ia,ja,arr,q+2,q+1,m1,next);
    push(ia,ja,arr,q+2,q+2,m2,next);
    push(ia,ja,arr,q+2,q+3,m3,next);
    
    glp_load_matrix(lp_solver, next-1, ia, ja, arr);
    
    solver_params.msg_lev=GLP_MSG_ALL;
    solver_params.meth=GLP_PRIMAL; //we solve normal, not inverse problem
    glp_init_smcp(&solver_params);
    glp_simplex(lp_solver, &solver_params);
    
    double cvar=glp_get_obj_val(lp_solver);
    double var=glp_get_col_prim(lp_solver, q+3+1);
    
    double x1=glp_get_col_prim(lp_solver, q+1);
    double x2=glp_get_col_prim(lp_solver, q+2);
    double x3=glp_get_col_prim(lp_solver, q+3);
    
    std::cout<<beta<<"-beta-CVAR="<<cvar<<std::endl;
    std::cout<<beta<<"-beta-VAR="<<var<<std::endl;
    std::cout<<"x1="<<x1<<std::endl;
    std::cout<<"x2="<<x2<<std::endl;
    std::cout<<"x2="<<x3<<std::endl;
    std::cout<<beta<<' '<<q<<' '<<x1<<' '<<x2<<' '<<x3<<' '<<var<<' '<<cvar<<std::endl;
    
    glp_delete_prob(lp_solver);
    
    free(ia);
    free(ja);
    free(arr);
    
    return 0;
}
