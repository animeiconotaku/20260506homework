#include "system.h"
#include <random>
using namespace std;
random_device seed_gen;
mt19937_64 engine(seed_gen());
uniform_int_distribution<> spin_rand(0,1);

double objSystem::calculationEnergy(){
	double J = this->interactionJ;
	double h = this->magneticH; //係数はmol毎で桁落ちを防ぐ. 
	int N = this->systemSize;
	double E = 0.0;

	/*
	//interaction term(相互作用の項)
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			int sig_i = this->spinsArray.at(i).at(j).spinVector;

		}
	}
	*/

	//magnetic term(磁場の影響の項)
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			int sig_i = this->spinsArray.at(i).at(j).spinVector;
			E += -1.0 * h * static_cast<double>(sig_i);
		}
	}

	E /= static_cast<double>(N*N);//1原子あたりに修正. N_Aが係数としてかかっているので1molあたりになる. 
	return E;
}

objSystem::objSystem(double h, double j, double T, int N)
	:magneticH(h),interactionJ(j),systemSize(N),temperature(T){
		this->spinsArray.assign(N,vector<SpinStruct>(N));
		this->system_randomsetter();
}

void objSystem::system_randomsetter(){
	int N = this->systemSize;
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){
			int sp = spin_rand(engine);
			if(sp == 0){
				sp = -1;
			}
			this->spinsArray.at(i).at(j).spinVector = sp;
		}
	}
}

void objSystem::gibbs_sampling(){
    int N = this->systemSize;
    uniform_int_distribution<> point_rand(0,N-1);
    int i = point_rand(engine);
    int j = point_rand(engine);
    double E_plus = -99.0;
    double E_minus = -99.0;
    this->spinsArray.at((i)).at(j).spinVector = 1;
    E_plus = this->calculationEnergy();
    this->spinsArray.at((i)).at(j).spinVector = -1;
    E_minus = this->calculationEnergy();
    double RT = gas_const*(this->temperature); //mol毎のエネルギーを考えるのでボルツマン定数を気体定数にする. 
    double exp_plus = exp(-1.0*(E_plus/RT));
    double exp_minus = exp(-1.0*(E_minus/RT));
    uniform_real_distribution<> sampling_rand(0.0,exp_plus+exp_minus);
    double sampling_num = sampling_rand(engine);
    if(0.0 <= sampling_num && sampling_num <= exp_plus){
        this->spinsArray.at(i).at(j).spinVector = 1;
    }else {
		this->spinsArray.at(i).at(j).spinVector = -1;
	}
    return;
}


