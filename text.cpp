#include "cli_gui.h"
#include "text.h"
#include "split.h"
#include <algorithm>

using std::cout;		using std::ifstream;		using std::sort;
using std::cin;			using std::vector;			using std::istream;
using std::string;		using std::pair;            using std::ofstream;

bool compareByInt(pair<string, int>& a, pair <string, int>& b) {
	return a.second > b.second;
}

Text parse(bool cli, istream& is) {
	// some initialization
	int line = 0;
	ifstream file;
	std::streambuf *backup = is.rdbuf();

	// if text is not from files
	if (cli) {
		bool invalid = true;
		string dir;
		do {
			line = headline();
			cout << "\n\n\n\n";
			if (dir == "") cout << "\n\n";
			else cout << "        You can't break this, "
				<< "I'm handling errors properly!\n\n";
			cout << "        Please insert the directory "
				<< "of a text file for analysis.\n";
			cout << "        The file should be pre-formatted "
				<< "like this:\n\n";
			cout << "             <Title>\n";
			cout << "             <Author>\n\n";
			cout << "             <text to analyze>\n\n";
			cout << "        or pipe an input stream before "
				<< "executing.\n";
			for (int i = line += 9 + 7; i<25 - 1; i++) cout << "\n";
			cout << "Directory: ";
			if (getline(is, dir)) {
				(file.open(dir.c_str(), ifstream::in));
				if (file) invalid = false;
                else {
                    cout << "file could not be opened\n";
//                    exit(69);
                }
            }
		} while (invalid);
		is.rdbuf(file.rdbuf());
		cout << "istream mapped to cin.\n";
	}

	// check how many paragraphs are there
	string paragraph; int no_of_pars = 0; vector<string> pars;
	while (getline(is, paragraph)) {
		if (paragraph != "") {
			++no_of_pars;
			pars.push_back(paragraph);
		}
	}

	// invalid format
	if (no_of_pars < 2) {
        is.rdbuf(backup);
        file.close();
        
		line = headline();
		cout << "\n\n\n\n\n\n\n                     Invalid format!"
			<< "\n                     Error: "
			<< "file has less than 2 lines."
			<< "\n\n                     Try again maybe?";
		for (int i = line + 11; i < 24; i++) cout << "\n";
		if (!cli) {
			//cout << "piped, quitting";
			exit(1);
		}
		cout << "Press Enter to try again.";
		is.ignore();
		return parse(cli, is);
	}

	// new text object, having all word pairs
	Text text(pars[0], pars[1]);
	text.paragraphs = no_of_pars - 2;

	// count words and split
	vector<string> words;		// word vector
	int no_of_sentences = 0;
	for (auto iter = pars.begin() + 2; iter != pars.end(); ++iter) {
		no_of_sentences += split(*iter, words);
	}
	text.sentences = no_of_sentences;
	text.words = words.size();

	// sorting word
	sort(words.begin(), words.end());

	// reusing variable paragraph for temp read word
	paragraph = "";
	int times_appeared = 0;
	for (auto iter = words.begin(); iter != words.end(); ++iter) {
		if (!iter->compare(paragraph)) {
			++times_appeared;
		}
		else {
			if (times_appeared != 0) text.wordMap.insert(pair<string, int>(paragraph, times_appeared));
			cout << "pushed in " << paragraph << " " << times_appeared << "\n";
			times_appeared = 1;
		}
		paragraph = *iter;
	}
	// the last one never got included, so we have to manually add it
	text.wordMap.insert(pair<string, int>(paragraph, times_appeared));
	cout << "pushed in " << paragraph << " " << times_appeared << "\n";

	cout << "pushed all in, size " << text.wordMap.size() << "\n";

	// return cin rdbuf
	if (cli) {
		is.rdbuf(backup);
		cout << "istream (cin) reverted.\n";
		file.close();
		cout << "Opened file closed.\n";
	}

	cout << "Parse successful.\n";
	return text;
}