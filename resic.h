//
// Created by jsed on 21.11.20.
//

#ifndef PIA_PROJEKT__2020_21_RESIC_H
#define PIA_PROJEKT__2020_21_RESIC_H

#endif //PIA_PROJEKT__2020_21_RESIC_H
#include <vector>
#include <cmath>
#define g 9.81

using namespace std;

class resic{
public:
    /* Zakladni promenne tridy resic*/
    double h, hu;
    /* Funkce a vraci vektor s hodnotami u-a a u+a.*/
    vector<double> a();
    /* F napocitava Flux - bilance bybnosti*/
    resic F();
    /* Harten Lax-van Leer schema (HLL) schema aproximace*/
    resic HLL(resic &wl, resic &wr);

/* Operator overloading declaration*/
    resic operator+(const resic& _vect);
    resic operator-(const resic& _vect);
    friend resic operator*(const double& a, const resic& _vect);
    friend resic operator*(resic const& _vect, double const& a);
};