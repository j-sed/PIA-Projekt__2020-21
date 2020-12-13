#include <iostream>
#include <string>
#include "sit.hpp"
#include "ulozVysledky.hpp"
#include "data.hpp"

using namespace std;

int main(int argc, char* const argv[]) {
    // Defaultni hodnoty site
    double pocBod = 0.0;
    double koncBod = 1.0;
    double prep = 0.5;
    double num = 200;
    if (argc > 1 || argc == 4){
        double pocBod = *argv[1];
        double koncBod = *argv[2];
        double prep = *argv[3];
        double num = *argv[4];
    }
    sit msh(pocBod, koncBod, prep, num);
    sit gr = msh;

    /* HLL */
    vector<resic> v, Fv; // vektor pro nezname a Flux
    v.resize(msh.n);
    Fv.resize(msh.n);

    /*Lax-Friedrichs*/
    vector<data> w, wNew; // vektor pro nezname
    w.resize(gr.n);
    wNew.resize(gr.n);
    double p_pom;


	//pocatecni podminka
	for(int i = 0; i < msh.n; i++){
		if(msh.x[i] < msh.prepBod){
            /*HLL*/
			v[i].h = 1.1;
			v[i].hu = 0.0;
            /*Lax-Friedrichs*/
            p_pom = 1.0;
            w[i].h = 1.0;
            w[i].hU = 0.0;
			
		}else{
		    /*HLL*/
			v[i].h = 0.01;
			v[i].hu = 0.0;
            /*Lax-Friedrichs*/
            p_pom = 0.1;
            w[i].h = 0.01;
            w[i].hU = 0.0;
			
		}
		Fv[i].h = 0.0;
		Fv[i].hu =0.0;
	}

	double iter = 0.0, finalIter = 150, dt, eps = 0.8,casCelkem = 0.0;
	
	while(iter < finalIter){
		
		// Odhad casoveho kroku
		dt = 1e16;
        for (int i = 0; i < msh.n; ++i) {
            dt = min(dt, eps*msh.h/v[i].sigma(v[i]));
        }
        // Vypis casoveho kroku pro danou iteraci
        cout << "casovy krok: "<< dt  << " pro iteraci: " << iter+1 << endl;
        casCelkem += dt;

        // Debug
        if (std::string("-d") == argv[1] || std::string("-d") == argv[argc-1] ){
            cout << v[0].sigma(v[0]) << endl;
            cout << Fv[0].h << " " << Fv[0].hu << endl;
        }

		iter += 1;
		// Napocitani hodnoty toku v krajnich bodech
		Fv[0] = v[0].HLL(v[0],v[0]);
		Fv[msh.n-1] = v[msh.n-1].HLL(v[msh.n-1],v[msh.n-1]);
        // Napocitani toku v cele domene
		for(int i = 0; i < msh.n-2; i++){
			Fv[i+1] = v[i+1].HLL(v[i],v[i+1]);
		}
		// Vypocet vektoru v
		for(int i = 0; i < msh.n-1; i++){
            v[i] = v[i] - dt/msh.h*(Fv[i+1]-Fv[i]);
		}
		// Pripojeni vysledku na konec souboru pro zaznamu dat ze vsech iteracnich kroku
        ulozVysledkyKumulativne(msh, v);
	}
    if (std::string("-d") == argv[1] || std::string("-d") == argv[argc-1] ){
        cout << "Celkovy cas simulace: " << casCelkem << endl;
    }

	double cas = 0.0, konecnyCas = casCelkem;
    eps = 0.93;

    while(cas < konecnyCas){

        //odhad casoveho kroku

        dt = 0.0001;

        //aktulni cas vypoctu

        cas += dt;

        //Neumannovy okrajove podminky

        wNew[0] = w[1];		//levy okrajovy bod
        wNew[gr.n-1] = w[gr.n-2]; // pravy okrajovy bod

        //Projedeme vsechny VNITRNI body site a vypocitame hodnoty v nove casove vrstve pomoci Laxova Fredrichsova schematu

        for(int i = 1; i < gr.n-1; i++){
            wNew[i] = w[i] - (w[i+1].F() - w[i-1].F() ) * (dt / (2.0 * gr.h ))+ 0.5 * eps * (w[i+1] - 2.0 * w[i] + w[i-1] );
        }

        //prekopirovani nove nactenych hodnot do stareho scheatu
        for(int i = 0; i < gr.n; i++){
            w[i] = wNew[i];
        }

        //ulozVysledkyKumulativne(gr, w);

    }
    ulozVysledky(gr, w);
	return 0;
}
