#include <cmath>
#include "SLAU.h"

#ifndef CONTEST_HEATEQUATION_H
#define CONTEST_HEATEQUATION_H

class Equation{
    double T;
    double L;
protected:
    virtual double Ux1(double t) = 0;
    virtual double Ux2(double t) = 0;
    virtual double V(double x) = 0;
    virtual double f(double x, double t) = 0;
public:
    Equation(double X, double T): T(T), L(X){};
    double **Explicit_solve(int N, int M){
        double h = L / (N - 1);
        double tau = T / (M - 1);
        auto **y = new double *[N];
        for(int i = 0; i < N; i++) y[i] = new double [N];
        for(int i = 0; i < N; i++){
            y[0][i] =     Ux1(tau * i * (M - 1));
            y[N - 1][i] = Ux2( tau * i * (M - 1));
            y[i][0] =     V(i * h * (N - 1));
        }
        for(int j = 0; j < M; j++) {
            for (int i = 1; i < N - 1; i++) {
                y[i][j + 1] = y[i][j] + tau / (h * h) * (y[i + 1][j] - 2 * y[i][j] + y[i - 1][j]) + tau * i * h;
            }
        }
        return y;
    }
    double **Multi_solve(int N, int M, double o){
        double h = L / (N - 1);
        double tau = T / (M - 1);
        auto **y = new double *[N];
        for(int i = 0; i < N; i++) y[i] = new double [M];
        for(int i = 0; i < N; i++){
            y[i][0] = V(i * h);
        }
        for(int j = 0; j < M; j++){
            y[0][j] =     Ux1(tau * j);
            y[N - 1][j] = Ux2( tau * j);
        }
        vector<double> A(N - 2,  2 * tau * o / (h * h));
        vector<double> B(N - 2,  1 + 4 * tau * o / (h * h));
        vector<double> F;
        for(int j = 0; j < M - 1; j++){ // step j + 1
            for(int i = 0; i < N; i++){
                F.push_back(y[i][j] + tau * f(h * i, (j + 0.5) * tau) + tau * o/(h * h) * (y[i - 1][j]) - 2 * y[i][j] + y[i + 1][j]);
            }
            vector<double> layer = SLAU(N, A, B, A, F).run(0, 0, y[0][j], y[N - 1][j]);

        }
        return y;
    }
};
#endif //CONTEST_HEATEQUATION_H