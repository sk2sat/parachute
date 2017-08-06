#include <iostream>
#include <cmath>
#include <sksat/math/vector.hpp>

using sksat::math::vector;

bool open_flg = false;

const double S			= 3.14 * 0.5 * 0.5;
const double Cd			= 1.33;
const double rho		= 1.293;
const double m			= 1.;
const double g			= 9.8;
const double open_t		= 1.0;
const double dt			= 0.001;
const double t_limit	= 30.;

inline vector<> func(vector<> x){
	vector<> ret(x.get_y(), 0.0);
	double v = x.get_y();
	double D = 0.5 * rho * v * v * S * Cd;
	if(open_flg){
		ret.set_y(D/m - g);
	}else{
		ret.set_y(-g);
	}
	return ret;
}

int main(int argc, char **argv){
	vector<> x(70, 0);
	vector<> k1, k2, k3, k4;
	double t = 0.;

	for(auto i=0;t<t_limit;++i){
//		x += dt * func(x);

		k1 = func(x);
		k2 = func(x + dt / 2. * k1);
		k3 = func(x + dt / 2. * k2);
		k4 = func(x + dt * k3);
		x = x + dt / 6. * (k1 + 2.*k2 + 2.*k3 + k4);

		std::cout<<t
		<<" "<<x.get_x()
		<<" "<<x.get_y()
		<<std::endl;

		t = i * dt;
		if(t>open_t) open_flg = true;
		if(x.get_x() < 0) break;
	}

	return 0;
}
