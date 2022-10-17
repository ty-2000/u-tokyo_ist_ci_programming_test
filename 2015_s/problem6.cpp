#include<bits/stdc++.h>
using namespace std;

vector<pair<string, string> > getSimilerPair(vector<string>& data);

bool is_similer(string str1, string str2);

int getEditDistance(string str1, string str2);

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

	if (4 > getEditDistance(str1, str2)) {

		return true;
	}

	return false;
}

int getEditDistance(string str1, string str2) {

	const int INF = 1 << 29;

	str1 = " " + str1;
	str2 = " " + str2;

	vector<vector<int> > dp(str1.size(), vector<int>(str2.size(), INF));

	for (int i = 0; i < str1.size(); i++)	dp.at(i).at(0) = i;
	for (int j = 0; j < str2.size(); j++)	dp.at(0).at(j) = j;

	for (int i = 1; i < (int)str1.size(); i++) {

		for (int j = 1; j < (int)str2.size(); j++) {

			if (str1.at(i) == str2.at(j)) {

				dp.at(i).at(j) = min({
					dp.at(i - 1).at(j - 1),
					dp.at(i).at(j - 1) + 1,
					dp.at(i - 1).at(j) + 1
				});
			}
			else {

				dp.at(i).at(j) = min({
					dp.at(i - 1).at(j - 1) + 1,
					dp.at(i).at(j - 1) + 1,
					dp.at(i - 1).at(j) + 1
				});
			}
		}
	}

	return dp.at(str1.size() - 1).at(str2.size() - 1);
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
