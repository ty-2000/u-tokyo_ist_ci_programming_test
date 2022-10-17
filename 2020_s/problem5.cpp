
#include<boost/multiprecision/cpp_int.hpp>
#include<bits/stdc++.h>

using namespace std;
using namespace boost::multiprecision;

cpp_int const e("551263368336670859257571");
cpp_int const n("3858843578360632069557337");

void decrypt(string input_filename, int d);

vector<char> decrypt_sub(cpp_int c, int d);

int main() {

	const int d = 7;

	decrypt("data5.txt", d);
}

void decrypt(string input_filename, int d) {

	ifstream ifs{ input_filename };

	while (!ifs.eof()) {

		string c_str;
		ifs >> c_str;

		cpp_int c(c_str);

		vector<char> b = decrypt_sub(c, d);

		for (auto& e : b)	cout << e;
	}

	return;
}

vector<char> decrypt_sub(cpp_int c, int d) {

	cpp_int m_tmp("1");

	for (int i = 0; i < d; ++i) {

		m_tmp = (m_tmp * c) % n;
	}

	unsigned int m = static_cast<unsigned int>(m_tmp);

	vector<char> b(4);

	for (int i = 3; i >= 0; --i) {

		b.at(i) = 0xff & m;

		m = m >> 8;
	}

	return b;
}