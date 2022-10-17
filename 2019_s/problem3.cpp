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

bool less_idx(const Pixel& p, const Pixel& q) {

	return (p.idx < q.idx);
}

Pixel select_middle(vector<Pixel>& image);

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

	Pixel ans = select_middle(image);

	cout << "index : " << ans.idx << "\n";
	cout << "(r, g, b) = (" << ans.r << ", " << ans.g << ", " << ans.b << ")\n";

	sort(image.begin(), image.end(), less_idx);

	for (auto& e : image)	cout << e.idx << "\n";

	return 0;
}

Pixel select_middle(vector<Pixel>& image) {

	sort(image.begin(), image.end());

	return image.at((image.size() / 2));
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
