#include<bits/stdc++.h>
#include <boost/algorithm/string/classification.hpp> // is_any_of
#include <boost/algorithm/string/split.hpp>

using namespace std;

vector<double> getAve(vector<int>& infectonNum);

vector<int> getInfectionNum(string filename);


int main() {

	vector<int> num_infection = getInfectionNum("infections.txt");

	vector<double> ave = getAve(num_infection);

	for (auto& e : ave) {

		cout << e << endl;
	}

	cout << "max: " << setprecision(10) << *max_element(ave.begin() + 3, ave.end()) << endl;

	cout << "min: " << setprecision(10) << *min_element(ave.begin() + 3, ave.end()) << endl;

	double sum = 0.0;
	for (auto& e : ave) {

		sum += e;
	}

	cout << "sum:" << setprecision(10) << sum << endl;
}

int sum(vector<int>::iterator from, int size) {

	int sum = 0;

	for (int i = 0; i < size; ++i) {

		sum += *(from + i);
	}

	return sum;
}

vector<double> getAve(vector<int>& infectonNum) {

	vector<double> ave(infectonNum.size() - 3);

	for (int i = 3; i < ave.size(); ++i) {

		ave.at(i) = (double)sum(infectonNum.begin() + i - 3, 7) / 7;
	}

	return ave;
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
