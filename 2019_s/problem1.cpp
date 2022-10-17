#include<bits/stdc++.h>
using namespace std;

struct Pixel {
	
	int idx;

	int r;
	int g;
	int b;

	Pixel() {};
	Pixel(int idx, int r, int g, int b) : idx{ idx }, r{ r }, g{ g }, b{ b } {}


};

int main() {

	vector<Pixel> image;

	string fileName = "image1.txt";
	ifstream ifs{ fileName };

	int i = 0;
	while (!ifs.eof()) {

		int r, g, b;
		ifs >> r >> g >> b;

		image.push_back(Pixel(i++, r, g, b));
	}

	cout << image.size() << endl;

	return 0;
}