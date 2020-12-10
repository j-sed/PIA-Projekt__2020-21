#include <iostream>
#include "sit.hpp"
#include "ulozVysledky.hpp"

using namespace std;

int main(int argc, char** argv) {
	
	sit msh(0.0, 1.0, 0.5, 200);
		
	//vector<data> w, wNew; // vektor pro nezname
	//w.resize(msh.n);
    //wNew.resize(msh.n);
    vector<resic> v, Fv; // vektor pro nezname
    v.resize(msh.n);
    Fv.resize(msh.n);
	//pocatecni podminka
	
	double p_pom;
	
	for(int i = 0; i < msh.n; i++){
		if(msh.x[i] < msh.prepBod){
			p_pom = 1.0;
			v[i].h = 1.1;
			v[i].hu = 0.0;
			
		}else{
			p_pom = 0.1;
			v[i].h = 0.01;
			v[i].hu = 0.0;
			
		}
		Fv[i].h = 0.0;
		Fv[i].hu =0.0;
	}
	
	double iter = 0.0, finalIter = 150, dt, eps = 0.8;
	
	while(iter < finalIter){
		
		//odhad casoveho kroku
		
		dt = 1e16;
        for (int i = 0; i < msh.n; ++i) {
            dt = min(dt, eps*msh.h/v[i].sigma(v[i]));
        }
        cout << dt << endl;
        //cout << v[0].sigma(v[0]) << endl;
		//aktulni cas vypoctu

		iter += 1;
		
		//Neumannovy okrajove podminky

		//vNew[0] = v[1];		//levy okrajovy bod
		//vNew[msh.n-1] = v[msh.n-2]; // pravy okrajovy bod
		Fv[0] = v[0].HLL(v[0],v[0]);
		Fv[msh.n-1] = v[msh.n-1].HLL(v[msh.n-1],v[msh.n-1]);
		//Projedeme vsechny VNITRNI body site a vypocitame hodnoty v nove casove vrstve pomoci Laxova Fredrichsova schematu

		for(int i = 0; i < msh.n-2; i++){
			Fv[i+1] = v[i+1].HLL(v[i],v[i+1]);
		}

		//prekopirovani nove nactenych hodnot do stareho scheatu
		for(int i = 0; i < msh.n-1; i++){
            v[i] = v[i] - dt/msh.h*(Fv[i+1]-Fv[i]);
		}
        for (int i = 0; i < msh.n-1; ++i) {
            //v[i] = vNew[i];
        }
        ulozVysledky(msh, v);
	}
	
	return 0;
}
