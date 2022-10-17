#include<bits/stdc++.h>
#include<format>
using namespace std;

struct Pixel {

	int idx;

	int r;
	int g;
	int b;


	Pixel() {

		idx = -1; r = 0; g = 0; b = 0;
	}
	Pixel(int idx, int r, int g, int b) : idx{ idx }, r{ r }, g{ g }, b{ b } {}

	int get_distance_from(const Pixel& p) {

		return (abs(p.r - r) + abs(p.g - g) + abs(p.b - b));
	}

	bool is_white() {

		return (r == 255 && g == 255 && b == 255);
	}

	bool operator < (const Pixel& p) {

		return ((r * r + g * g + b * b) < p.r * p.r + p.g * p.g + p.b * p.b);
	}

	void show() {

		cout << idx << " " << r << " " << g << " " << b << "\n";
	}
};

bool idxOrder(const Pixel& p, const Pixel& q) {

	return p.idx < q.idx;
}

int getDistance(const Pixel& p, const Pixel& q) {
	return (abs(p.r - q.r) + abs(p.g - q.g) + abs(p.b - q.b));
}

vector<char> int_to_bytes(int num);

void make_imagefile(string input, string output);

vector<Pixel> reduceColor(vector<Pixel>& image, int k);

vector<Pixel> select_k_pixels(vector<Pixel>& image, int k);

vector<vector<Pixel> > classify(vector<Pixel>& image, vector<Pixel> reps_pixels);

Pixel choose_reps(vector<Pixel>& cluster);

Pixel select_nearest(Pixel& p, vector<Pixel>& pixels);

int get_width(vector<Pixel>& image);


int main() {

	make_imagefile("image3.txt", "image.tif");
}

vector<char> int_to_bytes(int num) {

	vector<char> ret(4);
	for (int i = 3; i >= 0; i--) {

		ret.at(i) = num & 255;

		num = num >> 8;
 	}

	return ret;
}

void make_imagefile(string input, string output) {

	vector<Pixel> image;

	ifstream ifs{ input };
	int i = 0;
	while (!ifs.eof()) {

		int r, g, b;
		ifs >> r >> g >> b;

		image.push_back(Pixel(i++, r, g, b));
	}

	int width;
	int height;
	int size;

	width = get_width(image);
	height = width;
	size = width * height * 3;

	vector<char> w(4);
	vector<char> h(4);
	vector<char> s(4);

	w = int_to_bytes(width);
	h = int_to_bytes(height);
	s = int_to_bytes(size);

	vector<char> initInfo = {
		  77,  77,   0,  42,   0,   0,   0,   8,   0,   7,   1,   0,   0,   4,   0,   0,
		   0,   1,w[0],w[1],w[2],w[3],   1,   1,   0,   4,   0,   0,   0,   1,h[0],h[1],
		h[2],h[3],   1,   2,   0,   3,   0,   0,   0,   3,   0,   0,   0,  98,   1,   6,
		   0,   3,   0,   0,   0,   1,   0,   2,   0,   0,   1,  17,   0,   4,   0,   0,
		   0,   1,   0,   0,   0, 104,   1,  21,   0,   3,   0,   0,   0,   1,   0,   3,
		   0,   0,   1,  23,   0,   4,   0,   0,   0,   1,s[0],s[1],s[2],s[3],   0,   0,
		   0,   0,   0,   8,   0,   8,   0,   8
	};

	image = reduceColor(image, 2);

	vector<char> data;
	for (auto& p : image) {

		char r_byte = p.r & 255;
		char g_byte = p.g & 255;
		char b_byte = p.b & 255;

		data.push_back(r_byte);
		data.push_back(g_byte);
		data.push_back(b_byte);
	}

	ofstream ofs{ output, ios_base::binary };

	for (auto& e : initInfo)	ofs << e;
	for (auto& e : data)	ofs << e;

	return;
}


vector<Pixel> reduceColor(vector<Pixel>& image, int k) {

	vector<Pixel> reps_pixels = select_k_pixels(image, k);

	vector<vector<Pixel> > clusters = classify(image, reps_pixels);

	for (int i = 0; i < 10; i++) {

		for (int cluster_id = 0; cluster_id < k; cluster_id++) {

			reps_pixels.at(cluster_id) = choose_reps(clusters.at(cluster_id));
		}

		clusters = classify(image, reps_pixels);
	}

	for (int i = 0; i < (int)clusters.size(); i++) {

		vector<Pixel> cluster = clusters.at(i);

		for (auto& p : cluster) {

			image.at(p.idx) = reps_pixels.at(i);
		}
	}

	return image;
}

vector<vector<Pixel> > classify(vector<Pixel>& image, vector<Pixel> reps_pixels) {

	sort(reps_pixels.begin(), reps_pixels.end(), idxOrder);

	// clusters
	vector<vector<Pixel> > clusters(reps_pixels.size());
	for (int i = 0; i < (int)reps_pixels.size(); i++) {

		clusters.at(i).push_back(reps_pixels.at(i));
	}


	// index of representative pixels
	unordered_set<int> reps_idx;
	for (auto& e : reps_pixels)	reps_idx.insert(e.idx);

	for (auto& p : image) {

		if (reps_idx.find(p.idx) != reps_idx.end())	continue;	// represantative pixel

		int min_dist = 1 << 29;
		int cluster_id = -1;

		int i = 0;
		for (auto& q : reps_pixels) {

			int d = getDistance(p, q);

			if (d <= min_dist) {

				min_dist = d;
				cluster_id = i;
			}
			++i;
		}

		clusters.at(cluster_id).push_back(p);
	}

	return clusters;
}

Pixel choose_reps(vector<Pixel>& cluster) {

	int n = cluster.size();

	// calc center
	int r_ave = 0;
	int g_ave = 0;
	int b_ave = 0;

	for (auto& p : cluster) {

		r_ave += p.r;
		g_ave += p.g;
		b_ave += p.b;
	}

	r_ave /= n;
	g_ave /= n;
	b_ave /= n;

	Pixel center = Pixel(-1, r_ave, g_ave, b_ave);

	Pixel reps = select_nearest(center, cluster);

	return reps;
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

Pixel select_nearest(Pixel& p, vector<Pixel>& pixels) {

	sort(pixels.begin(), pixels.end(), idxOrder);

	int min_dist = 1 << 29;
	Pixel nearest = pixels.at(0);

	for (auto& q : pixels) {

		int d = getDistance(p, q);

		if (d <= min_dist) {

			min_dist = d;
			nearest = q;
		}
	}

	return nearest;
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
