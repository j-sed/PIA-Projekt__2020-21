#include <iostream>
#include "sit.hpp"
#include "ulozVysledky.hpp"

using namespace std;

int main(int argc, char** argv) {
	
	sit g(1.0, 2.0, 1.3, 200);
		
	vector<data> w, wNew; // vektor pro nezname
	w.resize(g.n);
	wNew.resize(g.n);
	
	//pocatecni podminka
	
	double p_pom;
	
	for(int i = 0; i < g.n; i++){
		if(g.x[i] < g.prepBod){
			p_pom = 1.0;
			w[i].h = 1.0;
			w[i].hU = 0.0;
			
		}else{
			p_pom = 0.1;
			w[i].h = 0.01;
			w[i].hU = 0.0;
			
		}
	}
	
	double cas = 0.0, konecnyCas = 0.5, dt, eps = 0.93;
	
	while(cas < konecnyCas){
		
		//odhad casoveho kroku
		
		dt = 0.0001;
		
		//aktulni cas vypoctu
		
		cas += dt;
		
		//Neumannovy okrajove podminky
		
		wNew[0] = w[1];		//levy okrajovy bod
		wNew[g.n-1] = w[g.n-2]; // pravy okrajovy bod
		
		//Projedeme vsechny VNITRNI body site a vypocitame hodnoty v nove casove vrstve pomoci Laxova Fredrichsova schematu
		
		for(int i = 1; i < g.n-1; i++){
			wNew[i] = w[i] - (w[i+1].F() - w[i-1].F() ) * (dt / (2.0 * g.h ))+ 0.5 * eps * (w[i+1] - 2.0 * w[i] + w[i-1] );
		}
		
		//prekopirovani nove nactenych hodnot do stareho scheatu
		for(int i = 0; i < g.n; i++){
			w[i] = wNew[i];				
		}
						
	}
	
	ulozVysledky(g, w);
	
	return 0;
}
