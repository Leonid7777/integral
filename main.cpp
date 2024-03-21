#include <iostream>
#include <cmath>


double f1(double x)
{
  return std::sin(1 / x);
}

double
f(double a, double b, double I, double eps)
{
    double x = (b + a) / 2;
    double val_1 = (x - a) * (f1(x) + f1(a)) / 2;
    double val_2 = (b - x) * (f1(x) + f1(b)) / 2;

    double arr = std::abs(val_1 + val_2 - I);


    if(arr >= eps) {
        #pragma omp task
        {
            val_1 = f(a, x, val_1, eps / 2);
        }

        #pragma omp task
        {
            val_2 = f(x, b, val_2, eps / 2);
        }
    }
    
    return val_1 + val_2;
}

int
main()
{
    double a, b, eps;
    std::cin >> a >> b >> eps;

    #pragma omp parallel
    {
        #pragma omp master
            std::cout << f(a, b, (b - a) * (f1(b) + f1(a)) / 2, eps) << std::endl;
    } 

    return 0;
}