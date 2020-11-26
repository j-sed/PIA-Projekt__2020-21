# pragma once

#include <vector>

using namespace std;

class sit{
	public:
	vector<double>x; 	// x-ove sourdnice bodu vypocetni site
	double h;			//krok site
	double pocBod;		//souradnice pocatecni bod
	double koncBod;		//souradnice koncovy bod
	double prepBod;		//souradnice prepazky (na pocatku)
	int n;				//pocet bodu site
	
	// vytvorit konstruktor
	sit(double _pocBod, double _koncBod, double _prepBod, int _n);
};

sit::sit(double _pocBod, double _koncBod, double _prepBod, int _n){
	pocBod = _pocBod;
	koncBod = _koncBod;
	prepBod = _prepBod;
	n = _n;
	h = (koncBod - pocBod) / (n-1);
	
	x.resize(n);
	
	for(int i = 0; i < n; i++){
		x[i] = pocBod + i * h;
	}
}
