#include <iostream>
#include <fstream>
#include "system.h"
using namespace std;


int main(){
	cout << "input simulation size" << endl;

	int N_size;
	try {
		cin >> N_size;
	} catch (...) {
		return 1;
	}
	cout << "input magnetic field(T)" << endl;
	double H;
	try {
		cin >> H;
	} catch (...) {
		return 1;
	}
	cout << "input temperature(K)" << endl;
	double temp;
	try {
		cin >> temp;
	} catch (...) {
		return 1;
	}
	cout << "input simulation cycle" << endl;
	int Cyc;
	try {
		cin >> Cyc;
	} catch (...) {
		return 1;
	}

	ofstream par_txt("par.txt");
	par_txt << "simulation_size " << N_size*N_size << endl;
	par_txt << "magnetic_field " << H  << "T" << endl;
	par_txt << "Temperature " << temp << "K" << endl;
	par_txt << "simulation_cycle " << Cyc << endl;
	par_txt.close();

	double h_eff = H*mu_avog;
	double Jinteract = 0.0;//相互作用の係数. 今回は無視するので0.

	objSystem simulation_system(H,Jinteract,temp,N_size);

	vector<double> energy_step(Cyc,-1.0);
	for(int i = 0; i < Cyc; i++){
		simulation_system.gibbs_sampling();
		energy_step.at(i) = simulation_system.calculationEnergy();
	}

	ofstream result("energy.dat");
	for(int i = 0; i < Cyc; i++){
		result << i << " " << energy_step.at(i) << endl;
	}

	result.close();



	return 0;
}
