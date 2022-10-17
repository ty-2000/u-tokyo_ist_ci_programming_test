#include<bits/stdc++.h>
#include <boost/algorithm/string/classification.hpp> // is_any_of
#include <boost/algorithm/string/split.hpp>

using namespace std;


vector<int> getInfectionNum(string filename);

int getS(vector<int>& data1, vector<int>& data2);

int getS_sub(vector<int>& x, vector<int>& y, int i);


int main() {

	int max_s = -100000000;

	vector<pair<int, int> > answers;

	for (int i = 1; i <= 47; ++i) {

		string filepath_i = format("data/data{:0>2}.txt", i);

		vector<int> data_1 = getInfectionNum(filepath_i);

		for (int j = i + 1; j <= 47; ++j) {

			string filepath_j = format("data/data{:0>2}.txt", j);

			vector<int> data_2 = getInfectionNum(filepath_j);

			int s = getS(data_1, data_2);

			if (max_s <= s) {

				if (max_s < s) {

					answers.clear();
				}

				answers.push_back({ i, j });
				max_s = s;
			}
		}
	}

	cout << "max_s: " << max_s << endl;

	for (auto& e : answers) {

		cout << e.first << " " << e.second << endl;
	}
}

int sum(vector<int>::iterator from, int size) {

	int sum = 0;

	for (int i = 0; i < size; ++i) {

		sum += *(from + i);
	}

	return sum;
}

int getS(vector<int>& data1, vector<int>& data2) {

	vector<int> x, y;

	if (data1.size() < data2.size()) {

		x = data2;
		y = data1;
	}
	else {

		x = data1;
		y = data2;
	}

	int max_i = (int)x.size() - (int)y.size();

	int s = 1 << 29;

	for (int i = 0; i <= max_i; ++i) {

		int s_tmp = getS_sub(x, y, i);

		s = min(s, s_tmp);
	}

	return s * (-1);
}

int getS_sub(vector<int>& x, vector<int>& y, int i) {

	int ret = 0;

	int n = y.size();

	for (int k = 0; k < n; ++k) {

		ret += (x.at(k + i) - y.at(k)) * (x.at(k + i) - y.at(k));
	}

	return ret;
}


vector<int> getInfectionNum(string filename) {

	ifstream ifs{ filename };

	string str;

	getline(ifs, str);

	std::vector<std::string> result_str;
	boost::algorithm::split(result_str, str, boost::is_any_of(":")); // ƒJƒ“ƒ}‚Å•ªŠ„

	vector<int> ret;

	for (auto& e : result_str) {

		ret.push_back(stoi(e));
	}

	return ret;
}
