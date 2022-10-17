#include<bits/stdc++.h>
using namespace std;

struct Node {

	int val;

	char c;

	Node* parent;
	Node* left;
	Node* right;

	Node() {
		val = -1;
		c = 0;
		parent = this;
		left = this;
		right = this;
	}

	bool operator < (const Node& v) {

		if (this->val == v.val) {

			return this->c < v.c;
		}

		return this->val < v.val;
	}
};

map<char, string> assignCode(map<char, int>& dict);

void dfs_assignCode(Node* current, string code, map<char, string>& dict);

void countCharacter(map<char, int>& dict, vector<char>& text);

void readFileAsBinary(string file_name, vector<char>& data);

int main() {

	vector<char> data;
	readFileAsBinary("q21.txt", data);

	map<char, int> dict;

	countCharacter(dict, data);

	auto code_dict = assignCode(dict);

	unsigned long long  cnt_char = 0;
	unsigned long long sum = 0;

	for (auto& e : dict) {

		int length = code_dict[e.first].size();

		sum += length * e.second;
		cnt_char += e.second;
	}

	double ans = (double)sum / (double)cnt_char;

	cout << ans << endl;
}

map<char, string> assignCode(map<char, int>& dict) {

	// make tree
	vector<Node*> tree_partial;

	for (auto& e : dict) {

		Node* v = new Node();

		v->c = e.first;
		v->val = e.second;

		tree_partial.push_back(v);
	}

	while (tree_partial.size() > 1)
	{
		stable_sort(tree_partial.rbegin(), tree_partial.rend());

		Node* r = tree_partial.back();
		tree_partial.pop_back();

		Node* l = tree_partial.back();
		tree_partial.pop_back();

		Node* p = new Node();
		p->c = 255;
		p->val = l->val + r->val;
		p->left = l;
		p->right = r;

		tree_partial.push_back(p);
	}

	// assign code
	map<char, string> code;

	dfs_assignCode(tree_partial.at(0), "", code);

	return code;
}

void dfs_assignCode(Node* current, string code, map<char, string>& dict) {

	if (current->left == current) {

		dict.insert({ current->c, code });
		return;
	}
	else {

		dfs_assignCode(current->left, code + "0", dict);
		dfs_assignCode(current->right, code + "1", dict);
	}

	delete current;

	return;
}

void countCharacter(map<char, int>& dict, vector<char>& data) {

	for (auto& e : data) {

		dict[e] ++;
	}

	return;
}

void readFileAsBinary(string file_name, vector<char>& data) {

	typedef istreambuf_iterator<char> itr_type;
	ifstream ifs{ file_name, ios_base::binary };

	data.assign(itr_type{ ifs }, itr_type{});
}
