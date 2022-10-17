#include<bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

struct Number {

	string base;
	string power;

	Number(string base, string power) : base{ base }, power{ power } {}

	Number operator * (const Number& val) {

		cpp_int x_base(this->base);
		int x_power = stoi(this->power);

		cpp_int y_base(val.base);
		int y_power = stoi(val.power);

		cpp_int res_base = x_base * y_base;
		int res_power = x_power + y_power;

		if (res_base.str().size() > 63)	res_power++;

		return Number(res_base.str().substr(0, 32), format("{:02}", res_power));
	}
};

int main() {

	string a_base, a_pow, b_base, b_pow;

	cin >> a_base >> a_pow >> b_base >> b_pow;

	Number a = Number(a_base, a_pow);
	Number b = Number(b_base, b_pow);

	Number ans = a * b;

	cout << ans.base << " " << ans.power << endl;
}