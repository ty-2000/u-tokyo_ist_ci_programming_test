#include<bits/stdc++.h>
#include <boost/algorithm/string/classification.hpp> // is_any_of
#include <boost/algorithm/string/split.hpp>

using namespace std;


vector<int> getInfectionNum(string filename);

vector<double> convertToLog(vector<int>& data);

double getA(vector<int>& data);

double getA(vector<double>& data, int from, int to) {

	int n = data.size();

	double sum_x = 0.0;
	double sum_i = 0.0;
	double sum_ix = 0.0;
	double sum_i2 = 0.0;

	for (int i = from; i <= to; ++i) {

		sum_x += data.at(i);

		sum_i += i;

		sum_ix += (i * data.at(i));

		sum_i2 += (i * i);
	}

	double a = (n * sum_ix - sum_i * sum_x) / (n * sum_i2 - sum_i * sum_i);

	return a;
}

double getK(vector<int>& data);



int main() {

	vector<int> data = getInfectionNum("infections2.txt");

	vector<double> data_d = convertToLog(data);

	double max_a = 0;
	vector<int> answers;

	for (int s = 0; s < data_d.size() - 30; ++s) {

		double a = getA(data_d, s, s + 30);

		if (max_a <= a) {

			if (max_a < a) {

				answers.clear();
			}

			answers.push_back(s);

			max_a = a;
		}
	}

	cout << "exp(" <<  max_a << ")" << endl;

	for (auto& e : answers) {

		cout << " " << e << endl;
	}
}

int sum(vector<int>::iterator from, int size) {

	int sum = 0;

	for (int i = 0; i < size; ++i) {

		sum += *(from + i);
	}

	return sum;
}

vector<double> convertToLog(vector<int>& data) {

	vector<double> ret(data.size());

	for (int i = 0; i < (int)data.size(); ++i) {

		ret.at(i) = log((double)data.at(i));
	}

	return ret;
}

double getA(vector<int>& data) {

	int n = data.size();

	double sum_x = 0.0;
	double sum_i = 0.0;
	double sum_ix = 0.0;
	double sum_i2 = 0.0;

	for (int i = 0; i < n; ++i) {

		sum_x += data.at(i);

		sum_i += i;

		sum_ix += (i * data.at(i));

		sum_i2 += (i * i);
	}

	double a = (n * sum_ix - sum_i * sum_x) / (n * sum_i2 - sum_i * sum_i);

	return a;
}

double getK(vector<int>& data) {

	int n = data.size();

	double sum_x = 0.0;
	double sum_i = 0.0;
	double sum_ix = 0.0;
	double sum_i2 = 0.0;

	for (int i = 0; i < n; ++i) {

		sum_x += data.at(i);

		sum_i += i;

		sum_ix += (i * data.at(i));

		sum_i2 += (i * i);
	}

	double k = (sum_i2 * sum_x - sum_ix * sum_i) / (n * sum_i2 - sum_i * sum_i);

	return k;
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
