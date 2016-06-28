#include <string>
#include <fstream>
#include "Control.h"
#include "Globals.h"

#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <wchar.h>
#include <vector>
using namespace std;

#pragma once

class Reporter {
public:
	bool writeReport(std::string suspectName, std::string investigatorName, std::string location);

	std::string getSystemTimeDate();

};