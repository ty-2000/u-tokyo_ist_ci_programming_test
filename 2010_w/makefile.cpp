#include<bits/stdc++.h>
using namespace std;

void makefile_a() {

	ofstream ofs{ "a.txt" };

	vector<int> data(1000);
	for (int i = 0; i < 1000; i++)	data.at(i) = i;

	for (int i = 0; i < 1000; i++) {

		string x = to_string(data.at(i % 1000));
		string y = to_string(data.at((i + 1) % 1000));

		string str = x + "->";
		str += y;

		ofs << str << endl;
	}
}

int main() {

	makefile_a();
}