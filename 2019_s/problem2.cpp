#include<bits/stdc++.h>
using namespace std;

struct Pixel {

	int idx;

	int r;
	int g;
	int b;

	Pixel() {};
	Pixel(int idx, int r, int g, int b) : idx{ idx }, r{ r }, g{ g }, b{ b } {}

	bool is_white() {

		return (r == 255 && g == 255 && b == 255);
	}
};

int get_width(vector<Pixel>& image);

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

	int width = get_width(image);

	cout << width << endl;

	return 0;
}


int get_width(vector<Pixel>& image) {

	int width = 0;

	int n = image.size();

	for (int i = 0; i < n; i++) {

		// ???Ȃ??[?̌???
		if (image.at(i).is_white()) {

			width = i + 1;
			int j = i;
			while (true) {

				if (!image.at(j).is_white())	break;

				j += width;
				if (n <= j)	return width;
			}
		}
	}
	return width;
}
