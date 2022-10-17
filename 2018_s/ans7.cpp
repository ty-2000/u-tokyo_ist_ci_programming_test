#include<bits/stdc++.h>
#include <boost/algorithm/string/classification.hpp> // is_any_of
#include <boost/algorithm/string/split.hpp>

using namespace std;

struct CacheElement {

	int matrix_id;
	int i;
	int j;

	CacheElement* prev;
	CacheElement* next;

	CacheElement() {

		prev = this;
		next = this;
	}
	CacheElement(int matrix_id, int i, int j) : matrix_id{ matrix_id }, i{ i }, j{ j } {

		prev = this;
		next = this;
	}
};

class Cache {

	vector<vector<CacheElement*> > A;	// m x n
	vector<vector<CacheElement*> > B;	// n x m

	CacheElement* old_sentinel;
	CacheElement* new_sentinel;

	int max_size;
	int current_size;
	int cnt_miss;

public:

	Cache() {}
	Cache(int m, int n, int size) {

		max_size = size;
		old_sentinel = new CacheElement();
		new_sentinel = new CacheElement();

		old_sentinel->next = new_sentinel;
		new_sentinel->prev = old_sentinel;

		A.assign(m, vector<CacheElement*>(n, nullptr));
		B.assign(n, vector<CacheElement*>(m, nullptr));

		cnt_miss = 0;
	}

	~Cache() {

		CacheElement* p = old_sentinel;
		CacheElement* q = old_sentinel->next;

		while (p != q) {

			delete p;
			p = q;
			q = p->next;
		}

		delete p;
	}

	int getMissCount() { return cnt_miss; }

	void referTo(int matrix_id, int i, int j);

	void deleteOldest();

	// delete ref later
	void remove(CacheElement* ref);

	void insertToNewest(CacheElement* ref);
};


int main() {

	int m, n, s;
	cin >> m >> n >> s;

	vector<int> p_vec;
	for (int i = 1; i <= min(m, n); i++) {

		if (m % i == 0 && n % i == 0)	p_vec.push_back(i);
	}
	
	int min_miss_cnt = 1 << 29;
	int ans = -1;

	for (auto& p : p_vec) {

		Cache cache = Cache(m, n, s);

		for (int u = 0; u < m; u += p) {

			for (int v = 0; v < m; v += p) {

				for (int w = 0; w < n; w += p) {

					for (int i = u; i < u + p; i++) {

						for (int j = v; j < v + p; j++) {

							for (int k = w; k < w + p; k++) {

								cache.referTo(0, i, k);
								cache.referTo(1, k, j);
							}
						}
					}
				}
			}
		}
		int miss_cnt = cache.getMissCount();

		std::cout << p << " :" << miss_cnt << endl;

		if (miss_cnt < min_miss_cnt) {

			min_miss_cnt = miss_cnt;
			ans = p;
		}
	}
	
	std::cout << "ans : " << ans << ", miss count : ";
	std::cout << min_miss_cnt << endl;
}

void Cache::referTo(int matrix_id, int i, int j) {

	CacheElement* ref = (matrix_id == 0) ? A.at(i).at(j) : B.at(i).at(j);

	if (ref == nullptr) {	//miss

		++cnt_miss;

		CacheElement* ele = new CacheElement(matrix_id, i, j);

		if (matrix_id == 0) A.at(i).at(j) = ele;
		else if (matrix_id == 1)	B.at(i).at(j) = ele;

		insertToNewest(ele);
		current_size++;

		if (current_size > max_size) {

			deleteOldest();
			current_size--;
		}
	}
	else {	//hit

		remove(ref);

		insertToNewest(ref);
	}
}

void Cache::deleteOldest() {

	CacheElement* ref = old_sentinel->next;

	old_sentinel->next = old_sentinel->next->next;
	old_sentinel->next->prev = old_sentinel;

	if (ref->matrix_id == 0)	A.at(ref->i).at(ref->j) = nullptr;
	else    B.at(ref->i).at(ref->j) = nullptr;

	delete ref;

	return;
}

void Cache::remove(CacheElement* ref) {

	ref->prev->next = ref->next;
	ref->next->prev = ref->prev;
}

void Cache::insertToNewest(CacheElement* ref) {

	ref->prev = new_sentinel->prev;
	ref->prev->next = ref;

	ref->next = new_sentinel;
	new_sentinel->prev = ref;
}
