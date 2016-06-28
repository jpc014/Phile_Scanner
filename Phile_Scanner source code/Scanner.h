#pragma once
#include "Control.h"
#include "pathItem.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

using namespace std;
using namespace std::tr2::sys;

#define MAX_SIZE 5000000
#define MIN_SIZE 5000

class Scanner
{
private:
	path startDirectory;
	pathItem currentItem;
public:
	Scanner(char sDir);
	bool isDesiredFileType(const path &pathToCheck);
	string getFileLastAccessed(string file_location);
	void begin_scan();
	string get_drive_letter();
	recursive_directory_iterator iterator;
	int totalScanned;
};