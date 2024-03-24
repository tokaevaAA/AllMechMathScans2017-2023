#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <exception>
#include <stdexcept>
#include <algorithm>
#include <numeric>
#include <iterator>

template<class T>
std::ostream& operator<<(std::ostream& out,const std::vector<T>& values){
    std::copy(values.begin(),values.end(),std::ostream_iterator<T>(out," "));
    return out<<std::endl;
}

void UpdateX(std::vector<double>& x_iterated, const std::vector<double>& x_fixed, const std::vector<double>& H, const std::vector<double>& g_fixed, double rho){
    int n=x_iterated.size();
    for (int i=0; i<n; i=i+1){
        double adjustment=0.0;
        for (int j=0; j<n; j=j+1){
            adjustment+=H[i*n+j]*g_fixed[j];
        }
        x_iterated[i]=x_fixed[i]-rho*adjustment;
    }
}

void UpdateH(std::vector<double>& H, const std::vector<double>& xi, const std::vector<double>& g_fixed, double lambda){
    int n=xi.size();
    for (int i=0; i<n; i=i+1){
        for (int j=0; j<n; j=j+1){
            H[i*n+j]+=lambda*xi[i]*g_fixed[j];
        }
    }
}

class Function{
private:
    int m_dimension;
public:
    Function(int dimension):m_dimension(dimension) {}
    double CalculateValue(const std::vector<double>& arguments){
        if (arguments.size()!=m_dimension){
            throw std::runtime_error("dimensions don't match");
        }
        return 100.0*(arguments[0]*arguments[0]-arguments[1])*(arguments[0]*arguments[0]-arguments[1])+(arguments[0]-1.0)*(arguments[0]-1.0);
    }
    void CalculateSubdifferential(std::vector<double>& result, const std::vector<double>& point){
        result[0]=400.0*(point[0]*point[0]-point[1])*point[0]+2.0*(point[0]-1.0);
        result[1]=-200.0*(point[0]*point[0]-point[1]);
    }
};

void Uryasev(int dimension, const std::vector<double>& initial_point, double epsilon=1e-15){
    Function f(dimension);
    std::vector<double> x_fixed(initial_point), x_iterated(dimension),g_fixed(dimension),g_iterated(dimension), xi(dimension);
    f.CalculateSubdifferential(g_fixed,x_fixed);
    //Notation: H[i][j]:=H[i*dimension+j];
    std::vector<double> H(dimension*dimension);
    for(int i=0; i<dimension; i=i+1){
        H[i*dimension+i]=1.0;
    }
    constexpr int max_step=1000;
    for (int step=0; step<max_step; step=step+1){
        constexpr int max_inner_step=1000;
        double rho=0.5;
        for (int inner_step=0; inner_step<max_inner_step; inner_step=inner_step+1){
            //x_iterated=x_fixed-rho*H*g_fixed
            UpdateX(x_iterated,x_fixed,H,g_fixed,rho);
            f.CalculateSubdifferential(g_iterated, x_iterated);
            //norm=|g_iterated|
            double norm=sqrt(std::inner_product(g_iterated.begin(), g_iterated.end(), g_iterated.begin(), 0.0));
            constexpr double exit_condition=1e-6;
            if (norm<exit_condition){
                return; //we are at the minimum
            }
            //xi=g_iterated/|g_iterated|
            std::transform(g_iterated.begin(), g_iterated.end(), xi.begin(), [norm](auto& elem){return elem/norm;});
            double lambda=1.0/(1.0+inner_step);
            //H+=lambda*xi*g_fixed^T
            UpdateH(H,xi,g_fixed,lambda);
            if (f.CalculateValue(x_iterated)<=f.CalculateValue(x_fixed)-epsilon){
                std::copy(x_iterated.begin(),x_iterated.end(),x_fixed.begin());
                std::copy(g_iterated.begin(),g_iterated.end(),g_fixed.begin());
                break;
            }
        }
        std::cout<<"Step :"<<step<<", point: "<<x_fixed;
    }
}

int main(){
    Uryasev(2,{2.0,2.0});
    return 0;
}
