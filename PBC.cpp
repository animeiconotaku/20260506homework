#include "PBC.h"

int PBC_set(int n, int m){
	if(m > n-1){
		return 0;
	}
	else if(m < 0){
		return n-1;
	}
	else{
		return m;
	}
}
