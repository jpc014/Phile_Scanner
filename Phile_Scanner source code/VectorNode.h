#pragma once

#include <iostream>
#include <vector>
#include "Globals.h"

using namespace std;

class VectorNode {
public:
	vector<pathItem> files;
	char drive_letter;
	VectorNode(char drive) {
		drive_letter = drive;
	};
};