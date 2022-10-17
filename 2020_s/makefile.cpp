#include<bits/stdc++.h>
using namespace std;

void makeFile(vector<char>& binarydata, string output_filename);

int main() {

	vector<char> data = {
		0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x00,0x06, 0x05, 0x48
	};

	makeFile(data, "data2a.bin");
}

void makeFile(vector<char>& binarydata, string output_filename) {

	ofstream ofs{ output_filename , ios_base::binary};

	for (auto& e : binarydata) {

		ofs << e;
	}

	return;
}
