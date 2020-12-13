//
// Created by jsed on 21.11.20.
//

#include "resic.h"

array<double, 2> resic::a() {
    double u = hu/h;
    double a = sqrt(g*h);
    array<double, 2> vect{u-a,u+a};
    return vect;
}

resic resic::F() {
    resic temp;
    double u = hu/h;
    temp.h = hu;
    temp.hu = hu*u+0.5*g*h*h;
    return temp;
}

resic resic::HLL(resic &wl, resic &wr) {
    resic Fl = wl.F();
    resic Fr = wr.F();
    vector<double> eigl;
    vector<double> eigr;
    eigl.assign(wl.a().begin(),wl.a().end());
    eigr.assign(wr.a().begin(),wr.a().end());
    double sl = min(eigl[0],eigr[0]);
    double sr = min(eigl[1],eigr[1]);
    double diffS = 1.0/(sr-sl);
    if (0.0 <= sl) {
        return Fl;
    }
    else if (0.0 < sr){
        return (sr*Fl - sl*Fr + sl*sr*(wr-wl))*diffS;
    }
    else {
        return Fr;
    }
}

/* Operators overloading definition*/
resic resic::operator+(const resic &_vect) {
    resic temp;
    temp.h = h      + _vect.h ;
    temp.hu = hu    + _vect.hu;
    return temp;
}

resic resic::operator-(const resic &_vect) {
    resic temp;
    temp.h = h      - _vect.h;
    temp.hu = hu    - _vect.hu;
    return temp;
}

resic operator*(const double &a, const resic& _vect) {
    resic temp;
    temp.h =  a * _vect.h;
    temp.hu = a * _vect.hu;
    return temp;
}

resic operator*(resic const&_vect,double const&a) {
    resic temp;
    temp.h =  a       * _vect.h;
    temp.hu = a       * _vect.hu;
    return temp;
}

double resic::sigma(resic &w) {
    array<double, 2> eig = w.a();
    return max(abs(eig[0]),abs(eig[1]));
}

