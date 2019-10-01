#include <iostream>
#include <vector>
#ifndef CONTEST_SLAU_H
#define CONTEST_SLAU_H


using std::cin;
using std::cout;
using std::vector;
class SLAU{
    int n;
    vector<double> A;
    vector<double> B;
    vector<double> C;
    vector<double> F;
public:
    SLAU(int x) : n(x){
        double buff;
       for(int i = 0; i < n - 1; i++) {
           cin >> buff;
           A.push_back(buff);
       }
        for(int i = 0; i < n - 1; i++) {
            cin >> buff;
            B.push_back(buff);
        }
        for(int i = 0; i < n - 1; i++) {
            cin >> buff;
            C.push_back(buff);
        }
        for(int i = 0; i < n - 1; i++) {
            cin >> buff;
            F.push_back(buff);
        }
    }
    SLAU(int x, const vector<double> &a, const vector<double> &b, const vector<double> &c, const vector<double> &f) : n(x), A(a), B(b), C(c), F(f) {}

    vector<double> run(double kappa1, double kappa2, double mu1, double mu2){
        vector<double> alfa(1, kappa1);
        vector<double> beta(1, mu1);
        for(int i = 0; i < n - 1; i++){
            alfa.push_back(-C[i] / (alfa[i] * A[i] + B[i]) );
            beta.push_back((F[i] - beta[i] * A[i]) / (alfa[i] * A[i] + B[i]) );
        }
        vector<double> ans(n);
        ans[n - 1] = (kappa2 * beta[n - 1] + mu2) / (1 - kappa2 * alfa[n - 1]);
        for(int i = n - 1; i >= 1; i--){
            ans[i - 1] = alfa[i - 1] * ans[i] + beta[i - 1];
        }
        return ans;
    }
};
#endif //CONTEST_SLAU_H