#include<bits/stdc++.h>
#include <boost/algorithm/string/classification.hpp> // is_any_of
#include <boost/algorithm/string/split.hpp>

using namespace std;

vector<int> getInfectionNum(string filename);

int main() {

	vector<int> ans = getInfectionNum("infections.txt");

	for (auto& e : ans) {

		cout << e << "\n";
	}

	cout << ans.at(ans.size() - 10) << endl;
}

vector<int> getInfectionNum(string filename) {

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