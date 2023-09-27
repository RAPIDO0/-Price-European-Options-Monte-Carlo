#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <random>

struct optionParams
/*will contain all the parameters used in option prices*/
{
    double S; /*stick-underlying price*/
    double K; /*Strike price of the option*/
    double r; /*risk free rate of the market*/
    double v; /*volatilty of the underlying stock */
    double T; /*Maturity of the option*/
};

double montecarloCallPrice(const int nSim, const optionParams p)
{
    double drift = (p.r - 0.5 * p.v * p.v) * p.T;
    double diffusion = p.v * sqrt(p.T);

    double payoffSum = 0.0;

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);
    
    for(int i = 0; i < nSim; i++){
        double Z = distribution(generator);//Brownien motion 
        double SForward = p.S * exp(drift + diffusion * Z);//Forward underlying Price 

        payoffSum += std::max(SForward - p.K, 0.0);

    }

    return (payoffSum / nSim) * exp(-p.r * p.T);
}

double montecarloPutPrice(const int nSim, const optionParams p)
{
    double drift = (p.r - 0.5 * p.v * p.v) * p.T;
    double diffusion = p.v * sqrt(p.T);

    double payoffSum = 0.0;

    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, 1.0);
    
    for(int i = 0; i < nSim; i++){
        double Z = distribution(generator);//Brownien motion 
        double SForward = p.S * exp(drift + diffusion * Z);//Forward underlying Price 

        payoffSum += std::max(p.K - SForward, 0.0);

    }

    return (payoffSum / nSim) * exp(-p.r * p.T);
}


int main()
{
    int nSim = 1000000;
    optionParams params;
    params.S = 100.0;
    params.K = 100.0;
    params.r = 0.05;
    params.v = 0.2;
    params.T = 1.0;

    double montecarloCallPrice_ = montecarloCallPrice(nSim, params);
    double montecarloPutPrice_ = montecarloPutPrice(nSim, params);

    std::cout << "\n Monte Carlo Call Price " << montecarloCallPrice_;
    std::cout << "\n Monte Carlo Put Price " << montecarloPutPrice_;
    std::cout << std::endl;
    return 0;
}