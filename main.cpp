#include <iostream>
#include "sit.hpp"
#include "ulozVysledky.hpp"

using namespace std;

int main(int argc, char** argv) {
	
	sit msh(0.0, 1.0, 0.5, 200);
		
	//vector<data> w, wNew; // vektor pro nezname
	//w.resize(msh.n);
    //wNew.resize(msh.n);
    vector<resic> v, vNew; // vektor pro nezname
    v.resize(msh.n);
    vNew.resize(msh.n);
	//pocatecni podminka
	
	double p_pom;
	
	for(int i = 0; i < msh.n; i++){
		if(msh.x[i] < msh.prepBod){
			p_pom = 1.0;
			v[i].h = 1.0;
			v[i].hu = 0.001;
			
		}else{
			p_pom = 0.1;
			v[i].h = 0.01;
			v[i].hu = 0.001;
			
		}
	}
	
	double cas = 0.0, konecnyCas = 150, dt, eps = 0.93;
	
	while(cas < konecnyCas){
		
		//odhad casoveho kroku
		
		dt = 1e16;
        for (int i = 0; i < msh.n-1; ++i) {
            dt = min(dt, 0.8*msh.h/v[i].sigma(v[i]));
        }
        cout << dt << endl;
		//aktulni cas vypoctu

		cas += 1;
		
		//Neumannovy okrajove podminky

		//vNew[0] = v[1];		//levy okrajovy bod
		//vNew[msh.n-1] = v[msh.n-2]; // pravy okrajovy bod
		v[0].F() = v[0].HLL(v[1],v[1]);
		v[msh.n-1].F() = v[msh.n-1].HLL(v[msh.n-1],v[msh.n-1]);
		//Projedeme vsechny VNITRNI body site a vypocitame hodnoty v nove casove vrstve pomoci Laxova Fredrichsova schematu

		for(int i = 0; i < msh.n-2; i++){
			v[i+1].F() = v[i+1].HLL(v[i],v[i+1]);
		}

		//prekopirovani nove nactenych hodnot do stareho scheatu
		for(int i = 0; i < msh.n-2; i++){
            vNew[i] = v[i] - dt/msh.h*(v[i+1].F()-v[i].F());
		}
        for (int i = 0; i < msh.n-2; ++i) {
            v[i] = vNew[i];
        }
						
	}
	
	ulozVysledky(msh, v);
	
	return 0;
}
