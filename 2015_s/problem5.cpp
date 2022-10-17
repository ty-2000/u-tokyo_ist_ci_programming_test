#include<bits/stdc++.h>
using namespace std;

vector<pair<string, string> > getSimilerPair(vector<string>& data);

bool is_similer(string str1, string str2);

vector<string> readFile(string fileName);

int main() {

	auto data = readFile("program.txt");

	auto ans = getSimilerPair(data);

	cout << "Num : " << ans.size() << endl;

	for (auto& ans_ele : ans) {

		cout << ans_ele.first << "\n" << ans_ele.second << "\n" << endl;
	}
}

vector<pair<string, string> > getSimilerPair(vector<string>& data) {

	vector<pair<string, string> > ret;

	for (int i = 0; i < (int)data.size(); i++) {

		for (int j = i + 1; j < (int)data.size(); j++) {

			if (is_similer(data.at(i), data.at(j))) {

				ret.push_back({ data.at(i), data.at(j) });
			}
		}
	}

	return ret;
}

bool is_similer(string str1, string str2) {

	if (str1.size() < str2.size()) {

		while (str1.size() < str2.size()){

			str1 += " ";
		}
	}
	else {

		while (str1.size() > str2.size()) {

			str2 += " ";
		}
	}

	int cnt_dif = 0;
	for (int i = 0; i < (int)str1.size(); i++) {

		if (str1.at(i) != str2.at(i))	cnt_dif++;

		if (cnt_dif >= 5)	return false;
	}

	return true;
}


vector<string> readFile(string fileName) {

	vector<string> data;

	ifstream ifs{ fileName };

	string line;
	while (getline(ifs, line)) {

		data.push_back(line);
	}

	return data;
}
