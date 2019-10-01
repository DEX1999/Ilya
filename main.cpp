#include <bits/stdc++.h>
#include "HeatEquation.h"
#include "SLAU.h"
using namespace std;

class Task : public Equation{
protected:
    double Ux1(double t){
        return 0;
    }
    double Ux2(double t){
        return 0;
    }
    double V(double x){
        return sin(M_PI * x / 2);
    }
    double f(double x, double t){
        return x;
    }
public:
    Task(double x, double t) : Equation(1, 1){};
};

int main(){
    vector<double> f;
    int t = 1;
    for(int i = 1; i < 9; i++){
        f.push_back(pow((i - 1), t) + (t + 2) * pow(i, t) + pow((i + 1), t));
    }
    SLAU E(10, vector<double>(10, 1), vector<double>(10, 3),vector<double>(10, 1), vector<double>(10, 15));
    vector<double> ans = E.run(0, 0, 3, 3);
    for(auto i: ans){
        cout << i << " ";
    }
}