#include<bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

struct Number {

	string base;
	string power;

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

		return Number(res_base.str(), format("{0:>2}", res_power));
	}

	bool operator < (const Number& val) {

		if (this->power == val.power) {

			cpp_int t(this->base);
			cpp_int v(val.base);

			return t < v;
		}

		return (stoi(this->power) < stoi(val.power));
	}
};

Number sqrt(const Number& val);

Number divideBy10(const Number& val);

int main() {

	cout << "problem 7" << endl;

	Number phi = Number(1) + sqrt(Number(5));
	phi = phi * Number(5);
	phi = divideBy10(phi);

	Number g = divideBy10(Number(5) + sqrt(Number(5)));

	int cnt = 1;
	while (cnt <= 140) {

		g = g * phi;
		cnt++;
	}

	cout << g.base << " " << g.power << endl;
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

Number divideBy10(const Number& val) {

	Number ret = val;

	int val_power = stoi(val.power);

	ret.power = format("{:0>2}", val_power - 1);

	return ret;
}