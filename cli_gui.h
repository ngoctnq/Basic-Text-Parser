#ifndef CLI_GUI_GUARD_H
#define CLI_GUI_GUARD_H

#include <iostream>
#include "text.h"
#include <map>

int headline();
void introScreen(const Text&, bool, std::istream&);
void barChart(std::istream&, bool, std::string, std::map<std::string, int>&, bool);

#endif