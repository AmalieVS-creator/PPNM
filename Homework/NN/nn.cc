#include "nn.h"
#include <cmath>
#include <cstdlib>

// constructor
ann::ann(int n_)
{
    n = n_;
    p.resize(3*n);

    for (int i = 0; i < n; i++)
    {
        p[3*i+0] = 2.0 * rand()/RAND_MAX - 1.0;
        p[3*i+1] = 0.5 + rand()/RAND_MAX;
        p[3*i+2] = 2.0 * rand()/RAND_MAX - 1.0;
    }

    f = [](double x)
    {
        return std::exp(-x*x);
    };
}

// network output
double ann::response(double x)
{
    double sum = 0;

    for (int i = 0; i < n; i++)
    {
        double a = p[3*i+0];
        double b = p[3*i+1];
        double w = p[3*i+2];


        double z = (x - a)/b;
        sum += w * std::exp(-z*z);
    }

    return sum;
}

// training
void ann::train(const pp::vector& x, const pp::vector& y)
{
    double lr = 0.001;

    for (int iter = 0; iter < 10000; iter++)
    {
        pp::vector grad(3*n);
        for (int i = 0; i < 3*n; i++)
            grad[i] = 0;

        for (int k = 0; k < x.size(); k++)
        {
            double xx = x[k];
            double yy = y[k];

            double F = response(xx);
            double err = F - yy;

            for (int i = 0; i < n; i++)
            {
                double a = p[3*i+0];
                double b = p[3*i+1];
                double w = p[3*i+2];

                if (b < 0.05) b = 0.05;

                double z = (xx - a)/b;
                double fz = std::exp(-z*z);
                double df = -2*z*fz;

                grad[3*i+2] += 2*err*fz;
                grad[3*i+0] += 2*err*w*df*(-1.0/b);
                grad[3*i+1] += 2*err*w*df*(-(xx-a)/(b*b));
            }
        }

        for (int i = 0; i < 3*n; i++)
            p[i] -= lr * grad[i];
    }
}

double ann::derivative(double x)
{
    double sum = 0;

    for(int i=0;i<n;i++)
    {
        double a = p[3*i];
        double b = p[3*i+1];
        double w = p[3*i+2];

        double z = (x-a)/b;

        double fp = std::exp(-z*z)*(1-2*z*z);

        sum += w*fp/b;
    }

    return sum;
}

double ann::second_derivative(double x)
{
    double sum = 0;

    for(int i=0;i<n;i++)
    {
        double a = p[3*i];
        double b = p[3*i+1];
        double w = p[3*i+2];

        double z = (x-a)/b;

        double fpp = std::exp(-z*z)*(4*z*z*z-6*z);

        sum += w*fpp/(b*b);
    }

    return sum;
}

double ann::antiderivative(double x)
{
    double sum = 0;

    for(int i=0;i<n;i++)
    {
        double a = p[3*i];
        double b = p[3*i+1];
        double w = p[3*i+2];

        double z = (x-a)/b;

        sum += -0.5*w*b*std::exp(-z*z);
    }

    return sum;
}