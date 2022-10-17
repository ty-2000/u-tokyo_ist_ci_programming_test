#include<bits/stdc++.h>
#include <boost/algorithm/string/classification.hpp> // is_any_of
#include <boost/algorithm/string/split.hpp>

using namespace std;

int main() {

	string logical_eq;
	cin >> logical_eq;

	std::vector<std::string> result;
	boost::algorithm::split(result, logical_eq, boost::is_any_of("+"));

	for (auto& str : result) {

		cout << str << endl;
	}
}