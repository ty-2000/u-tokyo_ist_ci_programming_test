#include<bits/stdc++.h>
using namespace std;

struct Pixel {

	int idx;

	int r;
	int g;
	int b;

	Pixel() {};
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
};

int getDistance(const Pixel& p, const Pixel& q) {
	return (abs(p.r - q.r) + abs(p.g - q.g) + abs(p.b - q.b));
}

vector<Pixel> get_reps_pixels(vector<Pixel>& image, int k);

vector<Pixel> select_k_pixels(vector<Pixel>& image, int k);

vector<vector<Pixel> > classify(vector<Pixel>& image, vector<Pixel> reps_pixels);

Pixel choose_reps(vector<Pixel>& cluster);

Pixel select_nearest(Pixel& p, vector<Pixel>& pixels);

int get_width(vector<Pixel>& image);


int main() {

	int k = 8;

	vector<Pixel> image;
	string fileName = "image3.txt";
	ifstream ifs{ fileName };

	int i = 0;
	while (!ifs.eof()) {

		int r, g, b;
		ifs >> r >> g >> b;

		image.push_back(Pixel(i++, r, g, b));
	}

	auto ansers = get_reps_pixels(image, k);

	cout << "problem5:" << endl;

	for (auto& ans : ansers) {

		cout << "index : " << ans.idx << "\n";
		cout << "(r, g, b) = (" << ans.r << ", " << ans.g << ", " << ans.b << ")\n";
	}

	return 0;
}

vector<Pixel> get_reps_pixels(vector<Pixel>& image, int k) {

	vector<Pixel> reps_pixels = select_k_pixels(image, k);

	for (int i = 0; i < 10; i++) {

		vector<vector<Pixel> > clusters = classify(image, reps_pixels);

		for (int cluster_id = 0; cluster_id < k; cluster_id++) {

			reps_pixels.at(cluster_id) = choose_reps(clusters.at(cluster_id));
		}
	}

	return reps_pixels;
}

vector<vector<Pixel> > classify(vector<Pixel>& image, vector<Pixel> reps_pixels) {

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
