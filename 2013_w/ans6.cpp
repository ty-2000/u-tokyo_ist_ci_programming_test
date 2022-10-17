#include<bits/stdc++.h>
using namespace std;

void solve(string logical_equation);

void solve_sub(vector<vector<char> >& answers, string& rpn_equation, unordered_map<char, bool>& vals, unordered_map<char, bool>::iterator itr);

bool solveEquation_RPN(string& rpn_equation, unordered_map<char, bool>& vals);

string convertToRPN(string logical_equation);

set<char> getValuables(string equation);

int main() {

	string eq;

	cin >> eq;

	solve(eq);
}

void solve(string logical_equation) {

	// �ϐ��̎擾
	set<char> vals = getValuables(logical_equation);

	// �t�|�[�����h�L�@�ɕϊ�
	string rpn_equation = convertToRPN(logical_equation);

	// 0,0,...,0 ����
	unordered_map<char, bool> values;
	for (auto& e : vals) {

		values.insert({ e, 0 });
	}

	vector<vector<char> > answers_rev;

	solve_sub(answers_rev, rpn_equation, values, values.begin());

	for (int i = 0; i < (int)answers_rev.size(); ++i) {

		if (i)	cout << "&";
		
		cout << "(";

		int j = 0;
		for (auto& val : vals) {

			if (j)	cout << "+";

			if (answers_rev.at(i).at(j))	cout << "!";

			cout << val;

			++j;
		}

		cout << ")";
	}
}

void solve_sub(vector<vector<char> >& answers, string& rpn_equation, unordered_map<char, bool>& vals, unordered_map<char, bool>::iterator itr) {

	if (itr == vals.end()) {

		if (!solveEquation_RPN(rpn_equation, vals)) {

			vector<char> ans;
			for (auto& p : vals) {

				ans.push_back(p.second);
			}

			answers.push_back(ans);
		}
	}
	else {

		vals[itr->first] = 0;
		solve_sub(answers, rpn_equation, vals, ++itr);	--itr;

		vals[itr->first] = 1;
		solve_sub(answers, rpn_equation, vals, ++itr);	--itr;

		vals[itr->first] = 0;
	}

	return;
}

bool solveEquation_RPN(string& rpn_equation, unordered_map<char, bool>& vals) {

	stack<char> st;

	for (auto& e : rpn_equation) {

		if (e == '+') {

			char val1 = st.top();	st.pop();
			char val2 = st.top();	st.pop();

			st.push((val1 || val2));
		}
		else if (e == '&') {

			char val1 = st.top();	st.pop();
			char val2 = st.top();	st.pop();

			st.push((val1 && val2));
		}
		else if (e == '!') {

			char val1 = st.top();	st.pop();

			st.push((!val1));
		}
		else {

			st.push(vals[e]);
		}
	}

	return st.top();
}

string convertToRPN(string logical_equation) {

	logical_equation.push_back('%');

	unordered_map<char, int> priority = {
		{'%', -100},
		{'!', 4},
		{'&', 3},
		{'+', 2}
	};

	string ret = "";

	// to stack operator character
	stack<char> st;

	for (auto& e : logical_equation) {

		if (e == '+' || e == '&' || e == '!' || e == '%') {

			while (!st.empty() && priority[st.top()] >= priority[e]) {

				ret.push_back(st.top());
				st.pop();
			}

			st.push(e);
		}
		else if (e == '(') {

			st.push('(');
		}
		else if (e == ')') {

			while (st.top() != '(') {

				ret.push_back(st.top());
				st.pop();
			}

			st.pop();
		}
		else {

			ret.push_back(e);
		}
	}

	return ret;
}

set<char> getValuables(string equation) {

	set<char> vals;

	for (auto& e : equation) {

		if ('a' <= e && e <= 'z') {

			vals.insert(e);
		}
	}

	return vals;
}