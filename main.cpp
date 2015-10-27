//  for checking if cin is piped
#ifdef __unix__
#include "unistd.h"
#elif __APPLE__
#include "unistd.h"
#elif _WIN32
#include "io.h"
#else
#error OS not supported
#endif

// include statements
#include "stdio.h"
#include "cli_gui.h"
#include "text.h"
#include <vector>

using std::cin;				using std::cout;			using std::vector;

// check if CLI input or file input/piping
#ifdef _WIN32
bool cli = _isatty(_fileno(stdin));
#else
bool cli = isatty(fileno(stdin));
#endif

int main()
{
	vector<Text> vText;
	cout << "Vector created.\n";
	vText.push_back(parse(cli, cin));
	cout << "Text item pushed.\n";
	cout << vText[0].title << "-" << vText[0].author << "-" << vText[0].paragraphs << "-" << vText[0].sentences << "-" << vText[0].words;

	introScreen(vText[0], cli, cin);
	barChart(cin, cli, "Chart of most used words relatively", vText[0].wordMap, true);
	return 0;
}
