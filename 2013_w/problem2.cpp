#include<bits/stdc++.h>

using namespace std;

void solve();

vector<vector<int> > getAns(string formula);

// 再帰ですべてのパターン試す
void getAns_sub(string& postfixFormula, vector<vector<int> > &ans, vector<char> &valuables, vector<int> &vals, int idx);

// 変数取得
vector<char> getValuables(string formula);

bool solveLogicalFormula(string postfixFormula, unordered_map<char, bool> dict);

string infixToPostfix(string formula);

vector<string> split(string text, char splitter);


int main() {

	solve();
}

void solve() {

	string formula;
	getline(cin, formula);

	vector<char> valuables = getValuables(formula);

	vector<vector<int> > ansers = getAns(formula);

	for (auto& e : ansers) {

		for (int i = 0; i < e.size(); i++) {

			string str = (e.at(i)) ? "true" : "false";

			cout << valuables.at(i) << "=" << str << " ";
		}
		cout << endl;
	}

	return;
}

vector<vector<int> > getAns(string formula) {

	string postfixFormula = infixToPostfix(formula);

	vector<vector<int> > ans;

	vector<char> valuables = getValuables(formula);

	vector<int> values(valuables.size(), 0);

	getAns_sub(postfixFormula, ans, valuables, values, 0);

	return ans;
}

void getAns_sub(string& postfixFormula, vector<vector<int> >& ans, vector<char>& valuables, vector<int>& vals, int idx){

	if (idx == vals.size()) {

		unordered_map<char, bool> d;
		for (int i = 0; i < valuables.size(); i++)	d.insert({ valuables.at(i), vals.at(i) });

		if (solveLogicalFormula(postfixFormula, d))	ans.push_back(vals);
	}
	else {

		vals.at(idx) = 0;
		getAns_sub(postfixFormula, ans, valuables, vals, idx + 1);

		vals.at(idx) = 1;
		getAns_sub(postfixFormula, ans, valuables, vals, idx + 1);

		vals.at(idx) = 0;
	}
	return;
}

vector<char> getValuables(string formula) {

	set<char> vals;

	for (auto itr = formula.begin(); itr != formula.end(); itr++) {

		if ('a' <= *itr && *itr <= 'z') {

			vals.insert(*itr);
		}
	}

	vector<char> ret(vals.begin(), vals.end());

	return ret;
}

bool solveLogicalFormula(string postfixFormula, unordered_map<char, bool> dict) {

	stack<bool> st;

	for (auto itr = postfixFormula.begin(); itr != postfixFormula.end(); itr++) {

		if ('a' <= *itr && *itr <= 'z') {

			st.push(dict[*itr]);
		}
		else {

			if (*itr == '+') {

				bool a = st.top();	st.pop();
				bool b = st.top();	st.pop();

				st.push(a | b);
			}
			else if (*itr == '&') {

				bool a = st.top();	st.pop();
				bool b = st.top();	st.pop();

				st.push(a && b);
			}
		}
	}

	return st.top();
}

string infixToPostfix(string formula) {


	unordered_map<char, int> priority = {
		{'(', 1},
		{'+', 2},
		{'&', 3},
		{')', 4},
	};

	string ans = "";

	stack<char> st;

	for (auto itr = formula.begin(); itr != formula.end(); itr++) {

		if ('a' <= *itr && *itr <= 'z') {

			ans = ans + *itr;
		}
		else {

			while (!st.empty() && priority[st.top()] >= priority[*itr])
			{
				ans = ans + st.top();
				st.pop();
			}

			st.push(*itr);
		}
	}

	while (!st.empty())
	{
		ans = ans + st.top();
		st.pop();
	}

	return ans;
}


vector<string> split(string text, char splitter) {

	text = text + splitter;

	vector<string> ret;
	string buf = "";

	for (auto itr = text.begin(); itr != text.end(); itr++) {

		if (*itr == splitter) {

			if (buf.size() > 0) {

				ret.push_back(buf);

				buf.clear();
			}
			else {

				continue;
			}
		}
		else {

			buf = buf + *itr;
		}
	}

	return ret;
}
