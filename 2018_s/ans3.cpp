#include<bits/stdc++.h>
#include <boost/algorithm/string/classification.hpp> // is_any_of
#include <boost/algorithm/string/split.hpp>

using namespace std;

int calculateTrace(vector<vector<int> >& A, vector<vector<int> >& B);

vector<vector<int> > readFileAsMatrix(string fileName);

int main() {

	vector<vector<int> > A = readFileAsMatrix("mat1.txt");
	vector<vector<int> > B = readFileAsMatrix("mat2.txt");

	auto ans = calculateTrace(A, B);

	cout << ans << endl;
}

int calculateTrace(vector<vector<int> >& A, vector<vector<int> >& B) {

	if (A.at(0).size() != B.size())	return -1;
	if (A.size() != B.at(0).size())	return -1;

	int m = A.size();
	int n = A.at(0).size();

	int trace = 0;

	for (int i = 0; i < m; i++) {

		for (int j = 0; j < n; j++) {

			trace += A.at(i).at(j) * B.at(j).at(i);
		}
	}

	return trace;
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
