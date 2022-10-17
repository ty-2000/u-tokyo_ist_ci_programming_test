#include<bits/stdc++.h>
using namespace std;

vector<int> searchInteger(string &text);

int main() {

	string fileName_1 = "c1.txt";
	string fileName_2 = "c2.txt";

	ifstream ifs_1{ fileName_1 };
	ifstream ifs_2{ fileName_2 };

	string text1, text2;

	getline(ifs_1, text1);
	getline(ifs_2, text2);

	auto ans_1 = searchInteger(text1);
	auto ans_2 = searchInteger(text2);

	cout << "c1.txt に含まれる置換指定文字列の数 : " << ans_1.size() << "\n";
	cout << "c2.txt に含まれる置換指定文字列の数 : " << ans_2.size() << endl;
}

vector<int> searchInteger(string &text) {

	vector<int> ret;

	for (auto itr = text.begin(); itr != text.end(); itr++) {

		if ('0' <= *itr && *itr <= '9') {

			ret.push_back(itr - text.begin());

			itr += 2;
		}
	}

	return ret;
}
