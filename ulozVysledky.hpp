#pragma once
#include <fstream>
#include <vector>
#include "sit.hpp"
#include "data.hpp"

using namespace std;

void ulozVysledky(sit &g){
	ofstream vystup;
	
	vystup.open("Vysledky.txt");
	
	vystup<< "# x " << endl;
	vystup<< "-------------------------------------------" << endl;
	
	for(int i=0; i < g.n; i++){
		vystup<< g.x[i] << endl;		
 	}
 	
 	vystup.close(); 	
}



void ulozVysledky(sit &g, vector<data> &w){
	ofstream vystup;
	vystup.open("Vysledky.txt");
	
	vystup<< "# x \t h \t u " << endl;
	vystup<< "-------------------------------------------" << endl;
	
	for(int i=0; i < g.n; i++){
		vystup<< g.x[i] << "\t" << w[i].h << "\t" << w[i].u() << endl;		
 	}
 	
 	vystup.close(); 	
}



