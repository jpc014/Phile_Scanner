#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <wchar.h>
#include <filesystem>
#include <vector>


using namespace std;
using namespace std::tr2::sys;

class pathItem {
public:
	pathItem() {};
	pathItem(string loc, string accessed) { address = path(loc.c_str()); lastAccessed = accessed; }
	path address;
	string lastAccessed;
	bool hashed;
};