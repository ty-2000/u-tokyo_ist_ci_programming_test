#include<bits/stdc++.h>
using namespace std;

typedef long long int llint;

int main() {

	vector<llint> fibonacci(51, 0);

	fibonacci.at(1) = 1;
	fibonacci.at(2) = 1;

	for (int i = 3; i < (int)fibonacci.size(); i++) {

		fibonacci.at(i) = fibonacci.at(i - 1) + fibonacci.at(i - 2);
	}

	cout << "f(10) = " << fibonacci.at(10) << endl;
	cout << "f(50) = " << fibonacci.at(50) << endl;
}