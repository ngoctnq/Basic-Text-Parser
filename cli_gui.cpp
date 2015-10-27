#include "text.h"
#include "cli_gui.h"
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <sstream>

using std::cout;			using std::cin;			using std::istream;
using std::string;			using std::map;			using std::vector;
using std::pair;			using std::setw;		using std::ostringstream;

const static long sleepTime = 500;
const static char cor1 = 0xC9;
const static char cor2 = 187;
//const static char cor3 = 188; // will never get used
const static char cor4 = 200;
const static char horz = 205;
const static char vert = 186;
const static char barc = 0xDC;
const static char sepc = 0xB3;

#ifdef _WIN32
const int ROWS = 25;
#else
const int ROWS = 24;
#endif

// int headline(): print out the headline
int headline() {
	// free endlines whooooo
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	cout << "TEXT ANALYSIS - CSC-121-01 FINAL PROJECT\n";
	cout << "NGOC NGO QUANG TRAN 2015\n";
	if (ROWS == 25) cout << "\n";
	return 2;
}

// formatting barchart lines
string print(string s, int n, int max) {
	string ret = "";
	ret += vert; ret += " ";
	if (s.size() > 11) {
		ret += s.substr(0, 8);
		ret += "...";
	}
	else {
		ret += s;
		ret += string(11 - s.size(), ' ');
	}

	ostringstream os;
	os << " " << setw(3) << n << setw(0);
	ret += os.str();

	ret += sepc;
	int no = (double)n / (double)max * 60.0;
	ret += string(no, barc);
	ret += string(60 - no, ' ');

	ret += " "; ret += vert;
	return ret;
}

void endText(istream& is, bool cli) {
	if (cli) is.ignore();
	else for (int i = 3; i > 0; --i) {
		cout << i << "...";
		cout.flush();
		std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
	}
}

void introScreen(const Text& text, bool cli, istream& is) {
//	int line = headline();

	cout << "\n\nMETADATA:\n";

	cout << "\nTitle:\n";
	auto length = text.title.size();
	if (length > 80) {
		for (int i = 0; i<77; ++i) cout << text.title[i];
		cout << "...\n";
	}
	else cout << text.title << "\n\n";

	cout << "\nAuthor:\n";
	length = text.author.size();
	if (length > 80) {
		for (int i = 0; i<77; ++i) cout << text.author[i];
		cout << "...\n";
	}
	else cout << text.author << "\n\n";

	cout << "\nStatistics:\n\n";
	cout << "\tParagraphs:\t" << text.paragraphs << "\n";
	cout << "\tSentences:\t" << text.sentences << "\n";
	cout << "\tWords:\t\t" << text.words;
	cout << "\n\n\n\n\n";
	if (cli) cout << "Press Enter to continue...";
	else cout << "Next page coming in...";
	endText(is, cli);
	cout << "\n";
}

void barChart(istream& is, bool cli, string title, map<string, int>& map, bool end) {
	cout << "map size " << map.size() << "\n";
	vector<pair<string, int> > vec(map.begin(), map.end());
	cout << "vector created, size " << vec.size() << "\n";
	sort(vec.begin(), vec.end(), compareByInt);
	cout << "vector sorted." << "\n";
	bool shortaf = false;
	if (vec.size() < ROWS - 4) shortaf = true;

	// title
	cout << cor1 << horz;
	if (title.length() > 76) cout << title.substr(0, 73) << "...";
	else {
		cout << string((76 - title.length()) / 2, horz) << title
			<< string(76-title.length()-(76 - title.length()) / 2, horz);
	}
	cout << horz << cor2;

	// spaceeeee
	cout << vert << string(78, ' ') << vert;

	if (shortaf) for (size_t i = 0; i < (ROWS - 4 - vec.size()) / 2; ++i)
		cout << vert << string(78, ' ') << vert;

	int max = vec.begin()->second;
	if (shortaf) for (vector<pair<string, int> >::const_iterator iter = vec.begin(); iter != vec.end(); ++iter)
		cout << print(iter->first, iter->second, max);
	else {
		int count = 0;
		for (vector<pair<string, int> >::const_iterator iter = vec.begin(); count < ROWS - 4; ++count, ++iter)
			cout << print(iter->first, iter->second, max);
	}

	if (shortaf) for (auto i = (ROWS - 4 - vec.size()) / 2 + vec.size(); i < ROWS - 4; ++i)
		cout << vert << string(78, ' ') << vert;

	// more spaceeeee
	cout << vert << string(78, ' ') << vert;

	// ending
	if (cli) {
		string text = (end) ? "Press Enter to Quit..." : "Press Enter to Continue...";
		cout << cor4 << horz;
		cout << string((76 - text.length()) / 2, horz) << text
			<< string(76 - text.length() - (76 - text.length()) / 2, horz);
		cout << horz;
	}
	else {
		string text = (end) ? "Quitting..." : "Continuing...";
		cout << cor4 << horz;
		cout << string(77 - text.length() - ((end) ? 12 : 0), horz) << text;
	}
	endText(is, cli);
}