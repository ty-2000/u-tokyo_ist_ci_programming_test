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
		{999, "IM"},	//	if(M) skip
		{995, "VM"},	//
		{990, "XM"},	//
		{950, "LM"},	//
		{900, "CM"},	
		{500, "D"},
		{499, "ID"},	//	if(D) skip
		{495, "VD"},	//
		{490, "XD"},	//
		{450, "LD"},	//
		{400, "CD"},	
		{100, "C"},
		{99, "IC"},	//	if(C) skip
		{95, "VC"},	//
		{90, "XC"},	
		{50, "L"},
		{49, "IL"},	//	if(L) skip
		{45, "VL"},	//
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

		if (i == 0 && digit)	i += 4;
		else if (i == 6 && digit)	i += 4;
		else if (i == 12 && digit)	i += 2;
		else if (i == 16 && digit)	i += 2;
	}

	return ans;
}
