#pragma once
#define kappa 1.4
#define g 9.81
#include <cmath>

//trida data
class data{
	public:
		
		//definice vnitrnich promennych
		
		double h, hU; 		// vektor neznamych
		
		data F();			//metoda vracejici slozky toku pocitane z vnitrnich promenych tridy
		
		double u();			//metoda vracejici hodnotu rychlosti
				
		data operator + (const data& B);
		data operator - (const data& B);
};

data data::F(){
	data pom;
	
	pom.h 	= hU;
	pom.hU 	= hU * u() + 0.5*tiha*h*h;
		
	return pom;		
}


double data::u(){
	return hU / h;
}

data data::operator+ (const data& B){
	data A;
	A.h = h		+ B.h;
	A.hU = hU 	+ B.hU;
		
	return A;
} 


data data::operator- (const data& B){
	data A;
	A.h = h		- B.h;
	A.hU = hU 	- B.hU;
	
	return A;
}

inline data operator* (const double& k, const data& B){
	data A;
	
	A.h 	= k * B.h;
	A.hU 	= k * B.hU;
	
	return A;	
}


inline data operator* (const data& B, const double& k){
	data A;
	
	A.h 	= k * B.h;
	A.hU 	= k * B.hU;
		
	return A;	
}

