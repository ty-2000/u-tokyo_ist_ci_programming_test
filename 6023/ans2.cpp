#include<bits/stdc++.h>
#include <boost/algorithm/string/classification.hpp> // is_any_of
#include <boost/algorithm/string/split.hpp>

using namespace std;

vector<int> getInfectionNum_unique(string filename);

int main() {

	int sum = 0;

	for (int i = 1; i <= 47; ++i) {

		string filepath = format( "data/data{:0>2}.txt", i );

		vector<int> ans = getInfectionNum_unique(filepath);

		sum += ans.at(ans.size() - 10);
	}

	cout << sum << endl;
}

vector<int> getInfectionNum_unique(string filename) {

	ifstream ifs{ filename };

	string str;

	getline(ifs, str);

	std::vector<std::string> result_str;
	boost::algorithm::split(result_str, str, boost::is_any_of(":")); // ƒJƒ“ƒ}‚Å•ªŠ„

	set<int> res;

	for (auto& e : result_str) {

		res.insert(stoi(e));
	}

	vector<int> ret;

	for (auto& e : res) {

		ret.push_back(e);
	}

	return ret;
}