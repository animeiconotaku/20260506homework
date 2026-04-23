#include <vector>
#include <random>
#include <cmath>
#include "spin.h"
#include "PBC.h"
#include "const.h"
using namespace std;


class objSystem{
	public:
		int systemSize;
		double temperature;
		double interactionJ;
		double magneticH;
		vector<vector<SpinStruct>> spinsArray;
		double calculationEnergy();
		objSystem(double h, double j, double T, int N);
		void system_randomsetter();
		void gibbs_sampling();
};
