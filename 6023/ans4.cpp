#include<bits/stdc++.h>
#include <boost/algorithm/string/classification.hpp> // is_any_of
#include <boost/algorithm/string/split.hpp>

using namespace std;

vector<int> getDif(vector<int>& nums);

vector<int> getInfectionNum(string filename);

vector<pair<int, int> > getMaxRange(vector<int>& diff);

int main() {

	vector<int> num_infection = getInfectionNum("infections.txt");

	vector<int> diff = getDif(num_infection);

	auto ans = getMaxRange(diff);

	for (auto& e : ans) {

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

vector<pair<int, int> > getMaxRange(vector<int>& diff) {

	int max_val = 0;

	vector< pair<int, int> > max_range = { {0, 1 << 29} };

	for (int window_size = (int) diff.size(); window_size > 0; --window_size) {

		for (int from = 0; from <= (int)diff.size() - window_size; ++from) {

			int sum_tmp = sum(diff.begin() + from, window_size);

			if (sum_tmp >= max_val) {

				if (max_range.at(0).second > window_size) {

					max_range.clear();
				}

				max_val = sum_tmp;

				max_range.push_back({ from, window_size });
			}
		}
	}

	cout << max_val << endl;

	return max_range;
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
