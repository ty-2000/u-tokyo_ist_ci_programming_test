#include<bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

struct Number {

	string base;
	string power;

	Number() {

		base = format("{:0<32}", 0);
		power = format("{:0>2}", 0);
	}
	Number(string base, string power) : base{ base }, power{ power } {}
	Number(int n) {

		int base_int = 0;

		if (n > 0)	base_int = log10(n);


		this->base = format("{:0<32}", n);
		this->power = format("{:0>2}", base_int);
	}

	Number operator * (const Number& val) {

		cpp_int x_base(this->base);
		int x_power = stoi(this->power);

		cpp_int y_base(val.base);
		int y_power = stoi(val.power);

		cpp_int res_base = x_base * y_base;
		int res_power = x_power + y_power;

		if (res_base.str().size() > 63)	res_power++;

		return Number(res_base.str().substr(0, 32), format("{:0>2}", res_power));
	}

	Number operator + (const Number& val) {

		cpp_int x_base(this->base);
		int x_power = stoi(this->power);

		cpp_int y_base(val.base);
		int y_power = stoi(val.power);

		int res_power = 0;
		cpp_int res_base = 0;

		if (x_power <= y_power) {

			int dif = y_power - x_power;
			for (int i = 0; i < dif; i++)	x_base /= 10;

			res_power = y_power;
		}
		else if (x_power > y_power) {

			int dif = x_power - y_power;
			for (int i = 0; i < dif; i++)	y_base /= 10;

			res_power = x_power;
		}

		res_base = x_base + y_base;
		if (res_base.str().size() > 32) {

			res_base /= 10;
			res_power++;
		}

		return Number(res_base.str(), format("{:0>2}", res_power));
	}

	bool operator == (const Number& val) {

		return (this->base == val.base && this->power == val.power);
	}

	bool operator < (const Number& val) {

		if (this->power == val.power) {

			return this->base < val.base;
		}
		else if (this->base.at(0) == '0') 	return true;
		else if (val.base.at(0) == '0') 	return false;

		return stoi(this->power) < stoi(val.power);
	}
};

Number sqrt(const Number& val);

Number abs(Number& a, Number& b);

Number divideBy10(const Number& val);

int main() {

	cout << "problem 8" << endl;

	Number phi = Number(1) + sqrt(Number(5));
	phi = phi * Number(5);
	phi = divideBy10(phi);

	vector<Number> G(141);
	vector<Number> F(141);

	G.at(1) = divideBy10(Number(5) + sqrt(Number(5)));
	for (int i = 2; i <= 140; i++) {

		G.at(i) = G.at(i - 1) * phi;
	}

	F.at(1) = Number(1);
	F.at(2) = Number(1);

	for (int i = 3; i <= 140; i++) {

		F.at(i) = F.at(i - 1) + F.at(i - 2);
	}

	Number max_different = Number(0);
	int idx = 0;

	for (int i = 1; i <= 140; i++) {

		Number dif = abs(F.at(i), G.at(i));

		if (max_different < dif)	max_different = dif;	idx = i;
	}

	cout << idx << " : " << max_different.base << " " << max_different.power << endl;
}

Number sqrt(const Number& val) {

	Number ret = Number(0);

	for (int i = 0; i < 32; i++) {

		while (ret.base.at(i) < '9' + 1 && ret * ret < val) {

			ret.base.at(i)++;
		}

		ret.base.at(i)--;
	}

	return ret;
}

Number abs(Number& a, Number& b) {

	cpp_int large = 0;
	cpp_int small = 0;

	int ret_power = 0;

	if (a < b) {

		large.assign(b.base);
		small.assign(a.base);

		ret_power = stoi(b.power);

		for (int i = 0; i < (stoi(b.power) - stoi(a.power)); i++) {

			small /= 10;
		}
	}
	else if (b < a) {

		large.assign(a.base);
		small.assign(b.base);

		ret_power = stoi(a.power);

		for (int i = 0; i < (stoi(a.power) - stoi(b.power)); i++) {

			small /= 10;
		}
	}
	else {

		return Number(0);
	}

	cpp_int ret_base = large - small;

	while (ret_base.str().size() < 32) {

		ret_base *= 10;
		ret_power--;
	}

	return Number(ret_base.str(), format("{:0>2}", ret_power));
}

Number divideBy10(const Number& val) {

	Number ret = val;

	int val_power = stoi(val.power);

	ret.power = format("{:0>2}", val_power - 1);

	return ret;
}