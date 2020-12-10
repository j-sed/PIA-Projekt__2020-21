#pragma once
#include <fstream>
#include <vector>
#include "sit.hpp"
#include "resic.h"

using namespace std;

void ulozVysledky(sit &msh){
	ofstream vystup;
	
	vystup.open("Vysledky.txt");
	
	vystup<< "# x " << endl;
	vystup<< "-------------------------------------------" << endl;
	
	for(int i=0; i < msh.n; i++){
		vystup<< msh.x[i] << endl;
 	}
 	
 	vystup.close(); 	
}



void ulozVysledky(sit &msh, vector<resic> &w){
	ofstream vystup;
	vystup.open("Vysledky.txt",std::ios::app);
	
	//vystup<< "# x \t h \t u " << endl;
	//vystup<< "-------------------------------------------" << endl;
	
	for(int i=0; i < msh.n; i++){
		vystup<< msh.x[i] << "\t" << w[i].h << "\t" << w[i].hu/w[i].h << endl;
 	}
 	
 	vystup.close(); 	
}



