#include <bits/stdc++.h>


namespace sts {
	using namespace std;

	// Trim from the start (in place)
	void ltrim(std::string &s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
					return !std::isspace(ch);
					}));
	}

	// Trim from the end (in place)
	void rtrim(std::string &s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
					return !std::isspace(ch);
					}).base(), s.end());
	}
	vector<string> split_string(string& str, char delim) {
		vector<string> res;
		stringstream ss(str);
		string s;
		while (getline(ss, s, delim)) {
			res.push_back(s);
		}
		return res;
	} 
}
