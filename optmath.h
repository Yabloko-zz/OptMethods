#ifndef OPTMATH_H
#define OPTMATH_H

#include <math.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solver1d //заготовка для наследования
{
public:
    int stepCounter;
    int MaxSteps;
    vector<float> delta_x;
    vector<float> delta_fx;
    float (*f)(float );
    float eps;
    float a0, b0;

    Solver1d(float a0_,float b0_,float eps_, int MS_, float (*f_)(float))
    {
        a0=a0_;
        b0=b0_;
        eps=eps_;
        f=f_;
        MaxSteps=MS_;
        stepCounter = 0;
    }

    virtual float Solve()
    {
        cout << "default" << endl;
        return 0.0;
    }
};

class BisectionSolve : public Solver1d
{
public:
    float delta;
    virtual float Solve();

    BisectionSolve(float d, float eps_, float a_, float b_, float (*f_)(float ), int MaxSteps_) : Solver1d(a_,b_,eps_,MaxSteps_,f_)
    {
        delta = d;
    }

};

class GoldenRatio : public Solver1d
{

public:
    float delta;
    virtual float Solve();

    GoldenRatio(float d, float eps_, float a_, float b_, float (*f_)(float ), int MaxSteps_) : Solver1d(a_,b_,eps_,MaxSteps_,f_)
    {
        delta = d;
    }
};

class NewtonMethod1d_extr : public Solver1d
{
public:
    int stepCounter;
    int MaxSteps;
    vector<float> delta_x;
    vector<float> delta_fx;
    float (*F)(float );
    float (*dF)(float );
    float (*ddF)(float );
    float x0;
    float eps;

    virtual float Solve();

    NewtonMethod1d_extr(float eps_, float x0_, float (*F_)(float ),float (*dF_)(float ),float (*ddF_)(float ),int MaxSteps_) : Solver1d(0,0,eps_,MaxSteps_,F_)
    {
        eps = eps_; x0 = x0_; F = F_; dF = dF_; ddF = ddF_;
        MaxSteps = MaxSteps_;
        stepCounter = 0;
    }
};

class NewtonMethod1d_zero
{
public:
    int stepCounter;
    int MaxSteps;
    vector<float> delta_x;
    vector<float> delta_fx;
    float (*F)(float );
    float (*dF)(float );
    //float (*ddF)(float );
    float x0;
    float eps;

    virtual float Solve(float trueX);

    NewtonMethod1d_zero(float eps_, float x0_, float (*F_)(float ),float (*dF_)(float ), int MaxSteps_)
    {
        eps = eps_; x0 = x0_; F = F_; dF = dF_; //ddF = ddF_;
        MaxSteps = MaxSteps_;
        stepCounter = 0;
    }

};

class FibMethod : public Solver1d
{
public:

    FibMethod(float a0_, float b0_, float eps_, int MS_, float (*f_)(float)) : Solver1d(a0_,b0_,eps_,MS_,f_)
    {}
    float fib(float n)
    {
        if (n <= 0)
                return 0.0;
            else if (n == 1)
                return 1.0;
            else
                return fib(n - 1) + n;
    }

    virtual float Solve();
};

class Loman : public Solver1d
{
public:
    int stepCounter;

    double GetPointIntersection(double Lx, double Rx, double L, float (*f)(float ))
    {
        return (f(Lx) - f(Rx))/(2*L) + (Lx + Rx)/2;
    }

    float GetLipschitzConst(float a, float b, float (*f)(float ))
    {
        float tmpL, L = 0;
        float h = fabs(b - a)/10000;
        for(float cur = a + h; cur <= b; cur += h)
        {
            tmpL = fabs( f(cur) - f(cur - h) ) / h;
            if(tmpL > L) { L = tmpL; }
        }
        return L;
    }

    Loman(float a0_, float b0_, float eps_, int MS_, float (*f_)(float )) : Solver1d(a0_,b0_,eps_,MS_,f_)
    {}

    virtual float Solve();

};

class Strongin : public Solver1d
{
public:
    vector <float> u;
    float nu;
    float mk;
    float dk;
    float Li_(float ui1, float ui2)
    {
        return (abs(f(ui2)-f(ui1)))/(ui2-ui1);
    }

    float Rk_(int i)
    {   
       return ( dk*(u[i]-u[i-1]) + (f(u[i]) - f(u[i-1]))*
               (f(u[i]) - f(u[i-1]))/(dk * (u[i]-u[i-1])) - 2*(f(u[i])) - 2*(f(u[i-1])));
    }

    Strongin(float a0_, float b0_, float eps_, int MS_, float (*f_)(float ), float nu_) : Solver1d(a0_,b0_,eps_,MS_,f_)
    {
        nu = nu_;
    }

    virtual float Solve();
};
#endif // OPTMATH_H
