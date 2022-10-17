#include<bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;

int main() {

	vector<cpp_int> fibonacci(141, 0);

	fibonacci.at(1) = 1;
	fibonacci.at(2) = 1;

	for (int i = 3; i < (int)fibonacci.size(); i++) {

		fibonacci.at(i) = fibonacci.at(i - 1) + fibonacci.at(i - 2);
	}

	cout << "f(140) = " << fibonacci.at(140) << endl;
}