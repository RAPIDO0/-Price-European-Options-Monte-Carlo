#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <random>

struct optionParams
/*will contain all the parameters used in option prices*/
{
    double S; /*underlying price*/
    double K; /*Strike price of the option*/
    double r; /*risk free rate of the market*/
    double v; /*volatilty of the underlying stock */
    double T; /*Maturity of the option*/
};

double montecarloCallPrice(const int nSim, const optionParams p)
{
    double drift = (p.r - 0.5 * p.v * p.v) * p.T;
    double diffusion = p.v * sqrt(p.T);



}