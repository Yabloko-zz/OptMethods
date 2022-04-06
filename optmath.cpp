#include "optmath.h"
#include <time.h>
#include <random>

float BisectionSolve::Solve()
{
    float result;
    float a = a0;
    float b = b0;
    // = 0;

    while(abs(f(a)-f(b)) > eps || abs(b-a) > eps)
    {
        delta = abs(b-a)/10000;

        float x1 = (a + b - delta)/2;
        float x2 = (a + b + delta)/2;

        cout << f(x1) << " ? " << f(x2) <<endl;

        if(f(x1) > f(x2))
        {
            a = x1;
        }
        else
        {
            b = x2;
        }

        delta_x.push_back(abs(a-b));
        delta_fx.push_back(abs(f(a)-f(b)));
        stepCounter++;
    }
    result = (a + b)/2;
    return result;
}

float GoldenRatio::Solve()
{
    float a = a0;
    float b = b0;
    float result;
    while(abs(f(a)-f(b)) > eps || abs(b-a) > eps)
    {
        //float x1 = (a + b - delta)/2;
        //float x2 = (a + b + delta)/2;

        //delta = (b-a)/4;

        float x1 = a + (3-sqrt(5))*(b-a)/2;
        float x2 = a + (sqrt(5)-1)*(b-a)/2;

        if(f(x1) > f(x2))
        {

            a = x1;
            //b = b;
        }
        else
        {
            //a = a;
            b = x2;
        }
        delta_x.push_back(abs(a-b));
        delta_fx.push_back(abs(f(a)-f(b)));
        stepCounter++;
    }
    result = (a + b)/2;
    return result;
}

float NewtonMethod1d_extr::Solve()
{
    float x1 = x0 - dF(x0)/ddF(x0);
    while(abs(x0-x1) > eps)
    {
        x0 = x1;
        x1 = x0 - dF(x0)/ddF(x0);

        delta_x.push_back(abs(x0-x1));
        delta_fx.push_back(abs(F(x0)-F(x1)));
        stepCounter++;
    }

    return x1;
}

float NewtonMethod1d_zero::Solve(float trueX)
{
    float x1 = x0 - F(x0)/dF(x0);
    while(abs(x0-x1) > eps && stepCounter <= MaxSteps)
    {
        x0 = x1;
        x1 = x0 - F(x0)/dF(x0);

        delta_x.push_back(abs(x1-trueX));
        delta_fx.push_back(abs(F(x0)-F(x1)));
        stepCounter++;
    }
    return x1;
}

float FibMethod::Solve()
{
    int n = MaxSteps;
    float a, b;
    a=a0;
    b=b0;
    int k = 1;

    float lk = a + fib(n-k) / fib(n-k+1) * (b-a);
    float mk = a + fib(n-k+1) / fib(n-k+1) * (b-a);

    while((abs(f(a)-f(b)) > eps || abs(b-a) > eps) && k <= n)
    {
        if(f(lk)>f(mk))
        {
            a = lk;
            lk = mk;
            mk = a + fib(n-k-1)/fib(n-k) * (b-a);
            if(k==n-2)
            {
                mk = lk+eps;
                if(f(lk)==f(mk))
                {
                    a = lk;
                }
                else
                {
                    b = mk;
                }
            }
        }

        else if(f(lk)<=f(mk))
        {
            b = mk;
            mk = lk;
            lk = a + fib(n-k-2)/fib(n-k) * (b-a);
            if(k==n-2)
            {
                mk = lk+eps;
                if(f(lk)==f(mk))
                {
                    a = lk;
                }
                else
                {
                    b = mk;
                }
            }
        }
        delta_x.push_back(abs(a-b));
        delta_fx.push_back(abs(f(a)-f(b)));
        stepCounter++;

        k++;
    }

    return (a+b)/2;
}

float Loman::Solve()
{
    float a = a0;
    float b = b0;
    float PIx, PILx, PIRx;
    float L = GetLipschitzConst(a0, b0, f);
    int k = 0;

    while((abs(f(a)-f(b)) > eps || abs(b-a) > eps) && k <= MaxSteps)
    {
        PIx = GetPointIntersection(a, b, L,f);
        PILx = GetPointIntersection(a, PIx, L,f);
        PIRx = GetPointIntersection(PIx, b, L,f);

        if(f(PILx) <= f(PIRx))
        {
            a = PIx;
        }
        else
        {
            b = PIx;
        }

        delta_x.push_back(abs(a-b));
        delta_fx.push_back(abs(f(a)-f(b)));
        stepCounter++;
    }

    return (a+b)/2;
}

float Strongin::Solve()
{
    srand(time(NULL));
    u.push_back(a0);
    u.push_back(b0);

    //float xi = (a0+b0)/2;

    float xt1 = a0;
    float xt2 = b0;
    float Lk = std::numeric_limits<float>::lowest();
    float dk;
    while(abs(xt2-xt1) > eps && stepCounter < MaxSteps && abs(f(xt2)-f(xt1)) > eps)
    {
        //mk = rand()

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(101, 1000);
        mk = float(distr(gen))/100;
        std::sort(u.begin(), u.end());
        for(int i = 1; i < u.size(); i++)
        {
            float nli = Li_(u[i-1],u[i]);
            if(nli > Lk)
                Lk = nli;
        }

        if(Lk > 0)
            dk=mk;//dk = mk*Lk; //pick mk randomly each time and mk > 1
        else
            dk=nu; //nu is fixed
        int s;
        float Rks = std::numeric_limits<float>::lowest();
        for(int i = 1; i < u.size(); i++)
        {
            float Rki = Rk_(i);
            if(Rks < Rki)
            {
                Rks = Rki;
                s = i;
            }
        }
        float ustar = (u[s]+u[s-1])/2 - (f(u[s])-f(u[s-1]))/(2*dk);
        u.push_back(ustar);
        xt2 = u[s];
        xt1 = u[s-1];

        delta_x.push_back(abs(xt2-xt1));
        delta_fx.push_back(abs(f(xt2)-f(xt1)));
        stepCounter++;
        std::cout << "strongin step num: " << stepCounter<<std::endl;

    }
    return (xt2-xt1)/2;
}
