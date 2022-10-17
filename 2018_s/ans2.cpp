#include<bits/stdc++.h>
#include <boost/algorithm/string/classification.hpp> // is_any_of
#include <boost/algorithm/string/split.hpp>

using namespace std;

vector<vector<int> > readFileAsMatrix(string fileName);

int main(){

	vector<vector<int> > matrix = readFileAsMatrix("mat1.txt");

	for (auto& row : matrix) {

		for (auto& val : row) {

			cout << val << " ";
		}
		cout << "\n";
	}
}

vector<vector<int> > readFileAsMatrix(string fileName) {

	// read file
	string str = "";
	ifstream ifs{ fileName };

	getline(ifs, str);

	// split by piriod
	vector<string> matrix;
	boost::algorithm::split(matrix, str, boost::is_any_of("."));

	// split by comma
	vector<string> rows;
	boost::algorithm::split(rows, matrix.at(0), boost::is_any_of(","));

	vector<vector<int> > mat(rows.size());

	for (int i = 0; i < (int)rows.size(); i++) {

		string row = rows.at(i);
		stringstream ss{ row };

		while (!ss.eof())
		{
			int val;
			ss >> val;

			mat.at(i).push_back(val);
		}
	}

	return mat;
}
