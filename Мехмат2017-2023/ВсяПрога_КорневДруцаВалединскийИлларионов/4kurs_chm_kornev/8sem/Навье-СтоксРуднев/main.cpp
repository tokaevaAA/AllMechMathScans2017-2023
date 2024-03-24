#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class StocksSolver
{
public:
    
    void fillInitialData()
    {
        nu = 1.0/100;
        k = 1;
        r = 1;
        c = 1;
        G = 10;
    }
    
    double q(double x, double y)
    {
        return sin(M_PI*x) * sin(M_PI*y);
    }
    
    double omega0(double x, double y)
    {
        return 0;
    }
    
    double T0(double x, double y)
    {
        return 0;
    }
    
    double psi0(double x, double y)
    {
        return 0;
    }
    
    StocksSolver(int xCount, int yCount, int timeCount)
    {
        Mx = xCount;
        My = yCount;
        N = timeCount;
        maxSize = Mx; //for common dtor
        
        hx = 1.0/Mx;
        hy = 1.0/My;
        tau = 1.0/N;

        fillInitialData();
        
        T = new double *[(Mx+1)];
        T_next = new double *[(Mx+1)];
        omega = new double *[(Mx+1)];
        omega_next = new double *[(Mx+1)];
        psi = new double *[(Mx+1)];
        f = new double *[(Mx+1)];
        C = new double *[(Mx+1)];
        d = new double *[(Mx+1)];

        for(int i = 0; i < Mx+1; ++i)
        {
            T[i] = new double[My+1];
            T_next[i] = new double[My+1];
            omega[i] = new double[My+1];
            omega_next[i] = new double[My+1];
            psi[i] = new double[My+1];
            f[i] = new double[My+1];
            C[i] = new double[My+1];
            d[i] = new double[My+1];
        }
    }
    
    void fillInitialConvData()
    {
        nu = 1;
        k = 1;
        r = 1;
        c = 1;
        G = 1;
    }
    
    StocksSolver(int size, int timeCount)
    {
        maxSize = size;
        N = timeCount;
        tau = 1.0/N;

        fillInitialConvData();
        
        T = new double *[(maxSize+1)];
        T_next = new double *[(maxSize+1)];
        omega = new double *[(maxSize+1)];
        omega_next = new double *[(maxSize+1)];
        psi = new double *[(maxSize+1)];
        f = new double *[(maxSize+1)];
        C = new double *[(maxSize+1)];
        d = new double *[(maxSize+1)];

        for(int i = 0; i < maxSize+1; ++i)
        {
            T[i] = new double[maxSize+1];
            T_next[i] = new double[maxSize+1];
            omega[i] = new double[maxSize+1];
            omega_next[i] = new double[maxSize+1];
            psi[i] = new double[maxSize+1];
            f[i] = new double[maxSize+1];
            C[i] = new double[maxSize+1];
            d[i] = new double[maxSize+1];
        }
    }
    
    virtual ~StocksSolver()
    {
        for(int i = 0; i < maxSize+1; ++i)
        {
            delete [] T[i];
            delete [] T_next[i];
            delete [] omega[i];
            delete [] omega_next[i];
            delete [] psi[i];
            delete [] f[i];
            delete [] C[i];
            delete [] d[i];
        }

        delete []T;
        delete []T_next;
        delete []omega;
        delete []omega_next;
        delete []psi;
        delete []f;
        delete []C;
        delete []d;
    }
    //basic loop
    void gifLoop()
    {
        FILE* foutT;
        FILE* foutOmega;
        FILE* foutPsi;

        char bufferT[32];
        char bufferOmega[32];
        char bufferPsi[32];
        
        snprintf(bufferT, sizeof(char) * 32, "./data/T/T%i.txt", 0);
        snprintf(bufferOmega, sizeof(char) * 32, "./data/Omega/Omega%i.txt", 0);
        snprintf(bufferPsi, sizeof(char) * 32, "./data/Psi/Psi%i.txt", 0);

        foutT = fopen(bufferT, "w");
        foutOmega = fopen(bufferOmega, "w");
        foutPsi = fopen(bufferPsi, "w");
        
        for (int i = 0; i < Mx+1; ++i)
        {
            for (int j = 0; j < My+1; ++j)
            {
                T[i][j] = T0(i*hx, j*hy);
                omega[i][j] = omega0(i*hx, j*hy);
                psi[i][j] = psi0(i*hx, j*hy);

                fprintf(foutT, "%.16lf ", T[i][j]);
                fprintf(foutOmega, "%.16lf ", omega[i][j]);
                fprintf(foutPsi, "%.16lf ", psi[i][j]);
            }
            fprintf(foutT, "\n");
            fprintf(foutOmega, "\n");
            fprintf(foutPsi, "\n");
        }
        
        fclose(foutT);
        fclose(foutOmega);
        fclose(foutPsi);

        for (int n = 1; n <= N; ++n)
        {
            cout<<n<<endl;
            generateDataForT();
            calculateNextWithData(T_next, k);

            generateDataForOmega();
            calculateNextWithData(omega_next, nu);

            generateDataForPsi();
            calculateNextPsi();

            snprintf(bufferT, sizeof(char) * 32, "./data/T/T%i.txt", n);
            snprintf(bufferOmega, sizeof(char) * 32, "./data/Omega/Omega%i.txt", n);
            snprintf(bufferPsi, sizeof(char) * 32, "./data/Psi/Psi%i.txt", n);

            foutT = fopen(bufferT, "w");
            foutOmega = fopen(bufferOmega, "w");
            foutPsi = fopen(bufferPsi, "w");
            
            for (int i = 0; i < Mx+1; ++i)
            {
                for (int j = 0; j < My+1; ++j)
                {
                    fprintf(foutT, "%.16lf ", T_next[i][j]);
                    fprintf(foutOmega, "%.16lf ", omega_next[i][j]);
                    fprintf(foutPsi, "%.16lf ", psi[i][j]);
                }
                fprintf(foutT, "\n");
                fprintf(foutOmega, "\n");
                fprintf(foutPsi, "\n");
            }
            
            fclose(foutT);
            fclose(foutOmega);
            fclose(foutPsi);

            swap(T, T_next);
            swap(omega, omega_next);
        }
    }
    
    void generateDataForT()
    {
        for (int i = 0; i < Mx+1; ++i)
            for (int j = 0; j < My+1; ++j)
                f[i][j] = 0;

        for (int i = 1; i < Mx; ++i)
            for (int j = 1; j < My; ++j)
                f[i][j] = 1.0/tau * T[i][j] - (T[i+1][j]-T[i-1][j])/(2*hx) * (psi[i][j+1]-psi[i][j-1])/(2*hy)
                                            + (T[i][j+1]-T[i][j-1])/(2*hy) * (psi[i+1][j]-psi[i-1][j])/(2*hx)
                                            + q(i*hx, j*hy)/(r*c);
    }
    
    void generateDataForOmega()
    {
        for (int i = 0; i < Mx+1; ++i)
            for (int j = 0; j < My+1; ++j)
                f[i][j] = 0;

        for (int i = 1; i < Mx; ++i)
            for (int j = 1; j < My; ++j)
                f[i][j] = 1.0/tau * omega[i][j] - (omega[i+1][j]-omega[i-1][j])/(2*hx) * (psi[i][j+1]-psi[i][j])/(2*hy)
                                                + (omega[i][j+1]-omega[i][j-1])/(2*hy) * (psi[i+1][j]-psi[i-1][j])/(2*hx)
                                                + G * (T_next[i+1][j]-T_next[i-1][j])/(2*hx);
    }
    
    void generateDataForPsi()
    {
        for (int i = 0; i < Mx+1; ++i)
            for (int j = 0; j < My+1; ++j)
                f[i][j] = -omega_next[i][j];
    }
    
    //2.1
    double omega0Null(double x, double y)
    {
        return sin(M_PI*x) * sin(M_PI*y);
    }
        
    double T0Null(double x, double y)
    {
        return sin(M_PI*x) * sin(M_PI*y);
    }
    
    double psi0Null(double x, double y)
    {
        return sin(M_PI*x) * sin(M_PI*y);
    }
    
    double answerNullFunctionWithCoef(double x, double y, double t, double coef)
    {
        return exp(-2*coef*M_PI*M_PI*t)*sin(M_PI*x)*sin(M_PI*y);
    }
    
    double answerNullFunction(double x, double y, double t, double coef)
    {
        return -exp(-2*coef*M_PI*M_PI*t)*sin(M_PI*x)*sin(M_PI*y)/(2.0*M_PI*M_PI);
    }
    
    void nullLoop()
    {
        for (int i = 0; i < Mx+1; ++i)
        {
            for (int j = 0; j < My+1; ++j)
            {
                T[i][j] = T0Null(i*hx, j*hy);
                omega[i][j] = omega0Null(i*hx, j*hy);
                psi[i][j] = psi0Null(i*hx, j*hy);
            }
        }
        
        double maxT = 0, maxOmega = 0, maxPsi = 0;
        double minT = 0, minOmega = 0, minPsi = 0;
        
        for (int n = 1; n <= N; ++n)
        {
            cout<<n<<endl;
            generateNullDataForT();
            calculateNextWithData(T_next, k);

            generateNullDataForOmega();
            calculateNextWithData(omega_next, nu);

            generateDataForPsi();
            calculateNextPsi();
            
            double curMaxT = 0, curMaxOmega = 0, curMaxPsi = 0;
            double curMinT = 0, curMinOmega = 0, curMinPsi = 0;
            
            for (int i = 0; i < Mx+1; ++i)
            {
                for (int j = 0; j < My+1; ++j)
                {
                    if (T_next[i][j] > curMaxT)
                        curMaxT = T_next[i][j];
                    if (T_next[i][j] < curMinT)
                        curMinT = T_next[i][j];
                    
                    if (omega_next[i][j] > curMaxOmega)
                        curMaxOmega = omega_next[i][j];
                    if (omega_next[i][j] < curMinOmega)
                        curMinOmega = omega_next[i][j];
                    
                    if (psi[i][j] > curMaxPsi)
                        curMaxPsi = psi[i][j];
                    if (psi[i][j] < curMinPsi)
                        curMinPsi = psi[i][j];
                }
            }
            
            if (curMaxT > maxT)
                maxT = curMaxT;
            if (curMinT < minT)
                minT = curMinT;
            
            if (curMaxOmega > maxOmega)
                maxOmega = curMaxOmega;
            if (curMinOmega < minOmega)
                minOmega = curMinOmega;
            
            if (curMaxPsi > maxPsi)
                maxPsi = curMaxPsi;
            if (curMinPsi < minPsi)
                minPsi = curMinPsi;
            
            swap(T, T_next);
            swap(omega, omega_next);
        }
        
        double maxRealT = 0, maxRealOmega = 0, maxRealPsi = 0;
        double minRealT = 0, minRealOmega = 0, minRealPsi = 0;
        
        for (int n = 1; n <= N; ++n)
        {
            for (int i = 0; i < Mx+1; ++i)
            {
                for (int j = 0; j < My+1; ++j)
                {
                    if (answerNullFunctionWithCoef(i*hx, j*hy, n*tau, k) > maxRealT)
                        maxRealT = answerNullFunctionWithCoef(i*hx, j*hy, n*tau, k);
                    if (answerNullFunctionWithCoef(i*hx, j*hy, n*tau, k) < minRealT)
                        minRealT = answerNullFunctionWithCoef(i*hx, j*hy, n*tau, k);
                    
                    if (answerNullFunctionWithCoef(i*hx, j*hy, n*tau, nu) > maxRealOmega)
                        maxRealOmega = answerNullFunctionWithCoef(i*hx, j*hy, n*tau, nu);
                    if (answerNullFunctionWithCoef(i*hx, j*hy, n*tau, nu) < minRealOmega)
                        minRealOmega = answerNullFunctionWithCoef(i*hx, j*hy, n*tau, nu);
                    
                    if (answerNullFunction(i*hx, j*hy, n*tau, nu) > maxRealPsi)
                        maxRealPsi = answerNullFunction(i*hx, j*hy, n*tau, nu);
                    if (answerNullFunction(i*hx, j*hy, n*tau, nu) < minRealPsi)
                        minRealPsi = answerNullFunction(i*hx, j*hy, n*tau, nu);
                }
            }
        }
        
        printf("Scheme T amplitude: %.16lf, Real T amplitude: %.16lf\n", maxT - minT, maxRealT - minRealT);
        printf("Error: %.16lf\n", fabs((maxT - minT) - (maxRealT - minRealT)));

        printf("Scheme Omega amplitude: %.16lf, Real Omega amplitude: %.16lf\n", maxOmega - minOmega, maxRealOmega - minRealOmega);
        printf("Error: %.16lf\n", fabs((maxOmega - minOmega) - (maxRealOmega - minRealOmega)));

        printf("Scheme Psi amplitude: %.16lf, Real Psi amplitude: %.16lf\n", maxPsi - minPsi, maxRealPsi - minRealPsi);
        printf("Error: %.16lf\n", fabs((maxPsi - minPsi) - (maxRealPsi - minRealPsi)));
    }
    
    void generateNullDataForT()
    {
        for (int i = 0; i < Mx+1; ++i)
            for (int j = 0; j < My+1; ++j)
                f[i][j] = 1.0/tau * T[i][j];
    }
       
    void generateNullDataForOmega()
    {
        for (int i = 0; i < Mx+1; ++i)
            for (int j = 0; j < My+1; ++j)
                f[i][j] = 1.0/tau * omega[i][j];
    }
    
    //2.2
    double omegaReal(double x, double y, double t)
    {
        return exp(sin(t)) * sin(2*M_PI*x) * sin(2*M_PI*y);
    }
        
    double TReal(double x, double y, double t)
    {
        return (1 - exp(-t)) * sin(2*M_PI*x) * sin(2*M_PI*y);
    }
    
    double psiReal(double x, double y, double t)
    {
        return -1 / (8*M_PI*M_PI) * exp(sin(t)) * sin(2*M_PI*x) * sin(2*M_PI*y);
    }
    
    double omega0Conv(double x, double y)
    {
        return omegaReal(x, y, 0);
    }
        
    double T0Conv(double x, double y)
    {
        return TReal(x, y, 0);
    }
    
    double psi0Conv(double x, double y)
    {
        return psiReal(x, y, 0);
    }
    
    double f1(double x, double y, double t)
    {
        return (cos(t) + 8*M_PI*M_PI) * exp(sin(t)) * sin(2*M_PI*x) * sin(2*M_PI*y) - 2*M_PI*(1 - exp(-t)) * cos(2*M_PI*x) * sin(2*M_PI*y);
    }
    
    double f2(double x, double y, double t)
    {
        return (exp(-t) + 8*M_PI*M_PI*(1 - exp(-t))) * sin(2*M_PI*x) * sin(2*M_PI*y);
    }
    
    void convLoop()
    {
        FILE *foutDifT, *foutDifOmega, *foutDifPsi, *foutDif;
        foutDifT = fopen("difT.txt", "w");
        foutDifOmega = fopen("difOmega.txt", "w");
        foutDifPsi = fopen("difPsi.txt", "w");
        foutDif = fopen("difScheme.txt", "w");

        for (int iter = 10; iter <= maxSize; iter+=10)
        {
            cout<<iter<<endl;
            Mx = iter;
            My = iter;
            hx = 1.0/iter;
            hy = 1.0/iter;
            
            for (int i = 0; i < Mx+1; ++i)
            {
                for (int j = 0; j < My+1; ++j)
                {
                    T[i][j] = T0Conv(i*hx, j*hy);
                    omega[i][j] = omega0Conv(i*hx, j*hy);
                    psi[i][j] = psi0Conv(i*hx, j*hy);
                }
            }
                        
            for (time = 1; time <= N; ++time)
            {
                generateConvDataForT();
                calculateNextWithData(T_next, k);

                generateConvDataForOmega();
                calculateNextWithData(omega_next, nu);

                generateDataForPsi();
                calculateNextPsi();
                
                swap(T, T_next);
                swap(omega, omega_next);
            }
                        
            double maxDifT = 0, maxDifOmega = 0, maxDifPsi = 0;
            
            for (int i = 0; i < Mx+1; ++i)
            {
                for (int j = 0; j < My+1; ++j)
                {
                    double difT = fabs(T[i][j] - TReal(i*hx, j*hy, N*tau));
                    double difOmega = fabs(omega[i][j] - omegaReal(i*hx, j*hy, N*tau));
                    double difPsi = fabs(psi[i][j] - psiReal(i*hx, j*hy, N*tau));
                    
                    if (difT > maxDifT)
                        maxDifT = difT;
                    
                    if (difOmega > maxDifOmega)
                        maxDifOmega = difOmega;
                    
                    if (difPsi > maxDifPsi)
                        maxDifPsi = difPsi;
                }
            }
            
            fprintf(foutDifT, "%.16lf\n", maxDifT/(tau+hx*hx+hy*hy));
            fprintf(foutDifOmega, "%.16lf\n", maxDifOmega/(tau+hx*hx+hy*hy));
            fprintf(foutDifPsi, "%.16lf\n", maxDifPsi/(tau+hx*hx+hy*hy));
            fprintf(foutDif, "%.16lf\n", (maxDifT + maxDifOmega + maxDifOmega)/(tau+hx*hx+hy*hy));
            
            printf("T: %.16lf\n", maxDifT/(tau+hx*hx+hy*hy));
            printf("Omega: %.16lf\n", maxDifOmega/(tau+hx*hx+hy*hy));
            printf("Psi: %.16lf\n", maxDifPsi/(tau+hx*hx+hy*hy));
            printf("Sceme: %.16lf\n", (maxDifT + maxDifOmega + maxDifOmega)/(tau+hx*hx+hy*hy));
        }
        
        fclose(foutDifT);
        fclose(foutDifOmega);
        fclose(foutDifPsi);
    }
    
    void generateConvDataForT()
    {
        for (int i = 0; i < Mx+1; ++i)
            for (int j = 0; j < My+1; ++j)
                f[i][j] = 0;

        for (int i = 1; i < Mx; ++i)
            for (int j = 1; j < My; ++j)
                f[i][j] = 1.0/tau * T[i][j] - (T[i+1][j]-T[i-1][j])/(2*hx) * (psi[i][j+1]-psi[i][j-1])/(2*hy)
                                            + (T[i][j+1]-T[i][j-1])/(2*hy) * (psi[i+1][j]-psi[i-1][j])/(2*hx)
                                            + q(i*hx, j*hy)/(r*c) + f2(i*hx, j*hy, time*tau);
    }
    
    void generateConvDataForOmega()
    {
        for (int i = 0; i < Mx+1; ++i)
            for (int j = 0; j < My+1; ++j)
                f[i][j] = 0;

        for (int i = 1; i < Mx; ++i)
            for (int j = 1; j < My; ++j)
                f[i][j] = 1.0/tau * omega[i][j] - (omega[i+1][j]-omega[i-1][j])/(2*hx) * (psi[i][j+1]-psi[i][j-1])/(2*hy)
                                                + (omega[i][j+1]-omega[i][j-1])/(2*hy) * (psi[i+1][j]-psi[i-1][j])/(2*hx)
                                                + G * (T_next[i+1][j]-T_next[i-1][j])/(2*hx) + f1(i*hx, j*hy, time*tau);
    }
    
    void calculateNextWithData(double **u_next, double a)
    {
        f2c();

        for (int i = 1; i < Mx; ++i)
            for (int j = 1; j < My; ++j)
                C[i][j] = C[i][j]/(a * (lambda(i, hx) + lambda(j, hy)) + 1.0/tau);

        for (int i = 0; i < Mx+1; ++i)
            for (int j = 0; j < My+1; ++j)
                u_next[i][j] = c2f(i*hx, j*hy);
    }
    
    void calculateNextPsi()
    {
        f2c();
        
        for (int i = 1; i < Mx; ++i)
            for (int j = 1; j < My; ++j)
                C[i][j] = C[i][j]/(lambda(i, hx) + lambda(j, hy));

        for (int i = 0; i < Mx+1; ++i)
            for (int j = 0; j < My+1; ++j)
                psi[i][j] = c2f(i*hx, j*hy);
    }

    double lambda(int m, double h)
    {
        return 4/(h*h) * sin(M_PI*m*h/2) * sin(M_PI*m*h/2);
    }

    void f2c()
    {
        double norm;

        for (int m = 0; m < Mx+1; ++m)
            for (int l = 0; l < My+1; ++l)
                C[m][l] = 0;
        
        for (int m = 1; m < Mx; ++m)
        {
            for (int l = 1; l < My; ++l)
            {
                d[m][l] = 0;
                norm = 0;

                for (int j = 1; j < My; ++j)
                {
                    d[m][l] += f[m][j] * sin(M_PI*l*j*hy) * hy;
                    norm += sin(M_PI*l*j*hy) * sin(M_PI*l*j*hy) * hy;
                }
                d[m][l] /= norm;
            }
        }

        for (int m = 1; m < Mx; ++m)
        {
            for (int l = 1; l < My; ++l)
            {
                C[m][l] = 0;
                norm = 0;

                for (int i = 1; i < Mx; ++i)
                {
                    C[m][l] += d[i][l] * sin(M_PI*m*i*hx) * hx;
                    norm += sin(M_PI*m*i*hx) * sin(M_PI*m*i*hx) * hx;
                }
                C[m][l] /= norm;
            }
        }
    }

    double c2f(double x, double y)
    {
        double func = 0;

        for (int m = 1; m < Mx; ++m)
            for (int l = 1; l < My; ++l)
                func += C[m][l] * sin(M_PI*m*x) * sin(M_PI*l*y);
        
        return func;
    }
    
private:
    int Mx, My, N, maxSize;
    double hx, hy, tau, nu, k, r, c, G;
    int time;
    
    double **T;
    double **T_next;
    double **omega;
    double **omega_next;
    double **psi;
    double **f;
    double **C;
    double **d;
};

int main()
{
    int Mx, My, N;
    printf("Enter x count of steps: ");
    scanf("%d", &Mx);
    printf("Enter y count of steps: ");
    scanf("%d", &My);
    printf("Enter time: ");
    scanf("%d", &N);
   
    StocksSolver stocksSolver(Mx, My, N);
    stocksSolver.gifLoop();
    
    return 0;
}

