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

	bool operator < (const Pixel& p) {

		return ((r * r + g * g + b * b) < p.r * p.r + p.g * p.g + p.b * p.b);
	}
};


vector<Pixel> select_k_pixels(vector<Pixel>& image, int k);

int get_width(vector<Pixel>& image);


int main() {

	int k = 4;

	vector<Pixel> image;
	string fileName = "image1.txt";
	ifstream ifs{ fileName };

	int i = 0;
	while (!ifs.eof()) {

		int r, g, b;
		ifs >> r >> g >> b;

		image.push_back(Pixel(i++, r, g, b));
	}

	auto ansers = select_k_pixels(image, k);

	for (auto& ans : ansers) {

		cout << "index : " << ans.idx << "\n";
		cout << "(r, g, b) = (" << ans.r << ", " << ans.g << ", " << ans.b << ")\n";
	}

	return 0;
}

vector<Pixel> select_k_pixels(vector<Pixel>& image, int k) {

	int n = image.size();

	sort(image.begin(), image.end());

	vector<Pixel> ret;
	for (int i = 0; i < k; i++) {

		ret.push_back(image.at(n * i / k));
	}

	return ret;
}


int get_width(vector<Pixel>& image) {

	int width = 0;

	int n = image.size();

	for (int i = 0; i < n; i++) {

		// ”’‚È‚ç’[‚ÌŒó•â
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
