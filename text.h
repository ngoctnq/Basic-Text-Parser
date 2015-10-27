#ifndef TEXT_GUARD_H
#define TEXT_GUARD_H
#include <string>
#include <map>
#include <utility>
#include <fstream>

class Text {
public:
	// title of the processed text
	std::string title;
	// author of the processed text
	std::string author;
	// number of paragraphs
	int paragraphs;
	//number of sentences
	int sentences;
	// number of words
	int words;
	// map of words and number of times it is used
	std::map<std::string, int> wordMap;
	// custom constructor, taking title and author as parameters
	Text(std::string title_, std::string author_) : title(title_), author(author_) {}
};

bool compareByInt(std::pair<std::string, int>&, std::pair<std::string, int>&);

Text parse(bool, std::istream&);

#endif