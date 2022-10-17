#include<bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;


int main() {

	string num1, num2;
	cin >> num1 >> num2;

	int top1 = 0;
	int top2 = 0;

	while (num1.at(top1) == '0')	++top1;
	while (num2.at(top2) == '0')	++top2;

	num1 = num1.substr(top1, (int)num1.size() - top1);
	num2 = num2.substr(top2, (int)num2.size() - top2);

	cpp_int a(num1);
	cpp_int b(num2);

	cpp_int ans = a + b;

	cout << ans << endl;
}

