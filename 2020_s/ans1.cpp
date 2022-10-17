#include<bits/stdc++.h>
using namespace std;

void makeDic_charToBits(map<char, bitset<6> >& dic);

void readFile(vector<char> &data, string filename);

int main() {

	map<char, bitset<6> > dic;
	makeDic_charToBits(dic);

	vector<char> data;
	readFile(data, "data1.txt");

	string bits_row = "";

	int idx = 0;
	while (bits_row.size() <= 320 )
	{
		bits_row += dic.at(data.at(idx++)).to_string();
	}

	auto ans = bits_row.substr(310, 11);

	cout << ans << endl;
}

void makeDic_charToBits(map<char, bitset<6> >& dic) {

	int cnt = 0;
	for (char c = 'A'; c <= 'Z'; ++c) {

		dic.insert({ c, bitset<6>(cnt++) });
	}

	for (char c = 'a'; c <= 'z'; ++c) {

		dic.insert({ c, bitset<6>(cnt++) });
	}

	for (char c = '0'; c <= '9'; ++c) {

		dic.insert({ c, bitset<6>(cnt++) });
	}

	dic.insert({ '@', cnt++ });

	dic.insert({ '#', bitset<6>(cnt++) });
}

void readFile(vector<char> &data, string filename) {

	ifstream ifs{ filename };

	typedef istreambuf_iterator<char> iter_type;

	data.assign(iter_type{ ifs }, iter_type{});

	return;
}
