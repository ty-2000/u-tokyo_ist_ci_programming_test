#include<bits/stdc++.h>
#include <boost/algorithm/string/classification.hpp> // is_any_of
#include <boost/algorithm/string/split.hpp>

using namespace std;

vector<int> getDif(vector<int>& nums);

vector<int> getInfectionNum(string filename);


int main() {

	vector<int> num_infection = getInfectionNum("infections.txt");

	vector<int> diff = getDif(num_infection);

	ofstream ofs{ "diff.txt" };

	for (auto& e : diff) {

		if (e >= 0)	ofs << '+';

		ofs << e;
	}

	ofs.close();

	ifstream ifs{ "diff.txt" };

	string str;
	getline(ifs, str);

	cout << str.size() << endl;
}

vector<int> getDif(vector<int>& nums) {

	vector<int> ret(nums.size());

	for (int i = 0; i < (int)nums.size(); ++i) {

		if (i) {

			ret.at(i) = nums.at(i) - nums.at(i - 1);
		}
		else {

			ret.at(0) = nums.at(0);
		}
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
