#include <cctype>
#include <string>
#include <vector>
#include <iterator>
#include "split.h"

using std::vector;
using std::string;

#ifndef _MSC_VER
using std::isspace;
#endif

string tolower(string s) {
	string ret;
	for (std::size_t i = 0; i < s.size(); ++i) ret += std::tolower(s[i]);
	return ret;
}

// return the number of sentences and split all the words to the given vector
int split(const string& s, vector<string>& vec)
{
	int count = 0;

	vector<string> ret;
	typedef string::size_type string_size;
	string_size i = 0;

	// invariant: we have processed characters `['original value of `i', `i)'
	while (i != s.size()) {
		// ignore leading blanks
		// invariant: characters in range `['original `i', current `i)' are all spaces
		while (i != s.size() && !isalnum(s[i])) {
			if (s[i] =='!' || s[i] == '?' || s[i] == '.') ++count;
			++i;
		}

		// find end of next word
		string_size j = i;
		// invariant: none of the characters in range `['original `j', current `j)' is a space
		while (j != s.size() && isalnum(s[j]))
			++j;

		// if we found some nonwhitespace characters
		if (i != j) {
			// copy from `s' starting at `i' and taking `j' `\-' `i' chars
			vec.push_back(tolower(s.substr(i, j - i)));
			i = j;
		}

	}

	return count;
}

