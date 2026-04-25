#include <iostream>
#include <cmath>
#include <fstream>
#include "system.h"
using namespace std;


int main(){
	//cout << "input simulation size" << endl;

	/*
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
	*/
	int N_size = 32;
	double temp = 300.0;
	int Cyc = 4000000;
	int Jack_w = -1;
	int Jack_n = Cyc/Jack_w;
	


	ofstream par_txt("par.txt");
	par_txt << "simulation_size " << N_size*N_size << endl;
	//par_txt << "magnetic_field " << H  << "T" << endl;
	par_txt << "Temperature " << temp << "K" << endl;
	par_txt << "simulation_cycle " << Cyc << endl;
	par_txt.close();

	//ofstream debug_data("debug.dat");
	//ofstream debug_system("system.dat");

	for(int h_i=0; h_i < 100; h_i++){

	}
	double H = 1.0;
	double h_eff = H*mu_avog;
	double J_interact = 0.0;

	objSystem simulation_system(H,J_interact,temp,N_size);

	vector<double> energy_step(Cyc,-1.0);

	for(int i = 0; i < Cyc; i++){
		simulation_system.gibbs_sampling();
		energy_step.at(i) = simulation_system.calculationEnergy();
	}

	double res_ave = 0.0;

	ofstream result("energy.dat");
	for(int i = 0; i < Cyc; i++){
		result << i << " " << energy_step.at(i) << endl;
		res_ave += energy_step.at(i);
	}

	res_ave /= static_cast<double>(Cyc);

	cout << res_ave << endl;

	vector<int> test_value(12,-1);
	test_value.at(0) = 10000;
	test_value.at(1) = 20000;
	test_value.at(2) = 40000;
	test_value.at(3) = 50000;
	test_value.at(4) = 80000;
	test_value.at(5) = 100000;
	test_value.at(6) = 200000;
	test_value.at(7) = 400000;
	test_value.at(8) = 500000;
	test_value.at(9) = 800000;
	test_value.at(10) = 1000000;
	test_value.at(11) = 2000000;

	ofstream jack_txt("jack.dat");

	for(int k = 0; k < 12; k++){
		Jack_w = test_value.at(k);
		int Jack_n = Cyc/Jack_w;
		vector<double> Jack_w_array(Jack_w,-1.0);
		vector<double> Jack_n_array(Jack_n,-1.0);
		for(int i = 0; i < Jack_n; i++){
			for(int j = 0; j < Jack_w;j++){
				Jack_w_array.at(j) = energy_step.at(i*Jack_w+j);
			}
			double Jack_ave = 0.0;
			for(int j = 0; j < Jack_w;j++){
				Jack_ave += Jack_w_array.at(j);
			}
			Jack_ave /= static_cast<double>(Jack_w);
			//cout << Jack_ave << endl;
			Jack_n_array.at(i) = Jack_ave;
		}
		double Jack = -1.0;
		double Jack_keisu = 1/(static_cast<double>(Jack_n)*static_cast<double>(Jack_n-1));
		double Jack_sum = 0.0;
	
		for(int l=0;l<Jack_n;l++){
			//jack_txt << l << " " <<Jack_n_array.at(l) << endl;
			//cout << pow((Jack_n_array.at(l)-res_ave),2.0) << endl;
			Jack_sum += pow((Jack_n_array.at(l)-res_ave),2.0);
		}
		//cout << Jack_sum << endl;
		Jack = sqrt(Jack_keisu*Jack_sum);
		cout << Jack_w << " " <<Jack << endl;
		jack_txt << Jack_w << " " <<Jack << endl;
		//debug_data << H << " " << res_ave << endl;
	}
	
	result.close();
	jack_txt.close();

	//debug_data.close();
	//debug_system.close();

	return 0;
}
