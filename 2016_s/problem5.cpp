#include<bits/stdc++.h>

using namespace std;

string decimalToRoman(int num);

int main() {

	int n;
	cin >> n;

	string ans = decimalToRoman(n);

	cout << ans << endl;
}


string decimalToRoman(int num) {

	vector<pair<int, string> > romanStrList{
		{1000, "M"},
		{900, "CM"},
		{500, "D"},
		{400, "CD"},
		{100, "C"},
		{90, "XC"},
		{50, "L"},
		{40, "XL"},
		{10, "X"},
		{9, "IX"},
		{5, "V"},
		{4, "IV"},
		{1, "I"},
	};

	string ans = "";

	for (int i = 0; i < romanStrList.size(); i++) {

		int digit = num / romanStrList.at(i).first;

		for (int j = 0; j < digit; j++)	ans = ans + romanStrList.at(i).second;

		num %= romanStrList.at(i).first;
	}

	return ans;
}
