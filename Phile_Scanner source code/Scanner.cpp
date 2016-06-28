#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <wchar.h>
#include <vector>
#include "Scanner.h"
#include "Globals.h"
#include <thread>

#define MAX_SIZE 5000000
#define MIN_SIZE 5000

using namespace std;
using namespace std::tr2::sys;

// Scanner Constructor
Scanner::Scanner(char sDir)
{
	string thisisstring = " :/";
	thisisstring[0] = sDir;
	startDirectory = path(thisisstring);
	totalScanned = 0;
	iterator = recursive_directory_iterator{startDirectory};
	cout << "PATH: " << thisisstring << endl;
}

string Scanner::get_drive_letter() {
	return startDirectory.string();
}

// Checks for target file parameters
bool Scanner::isDesiredFileType(const path &pathToCheck){
	if (!pathToCheck.extension().compare(".jpg"))
		if ((MIN_SIZE <= file_size(pathToCheck) && file_size(pathToCheck) <= MAX_SIZE))
			return true;
	return false;
}

string Scanner::getFileLastAccessed(string file_location) {

	FILETIME AccessTime, LocalTime;
	HANDLE hFile;
	SYSTEMTIME st;
	std::string month;
	char time[6];

	hFile = CreateFile(file_location.c_str(), 0, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL);

	// error checking
	if (hFile == INVALID_HANDLE_VALUE){
		printf("Could not open file, error %ul\n", GetLastError());
		return "";
	}

	if (!GetFileTime(hFile, NULL, &AccessTime, NULL)){
		printf("Something wrong!\n");
		return "";
	}

	FileTimeToLocalFileTime(&AccessTime, &LocalTime);

	FileTimeToSystemTime(&LocalTime, &st);

	switch (st.wMonth) {
		case 1: month = "January"; break;
		case 2: month = "Febuary"; break;
		case 3: month = "March"; break;
		case 4: month = "April"; break;
		case 5: month = "May"; break;
		case 6: month = "June"; break;
		case 7: month = "July"; break;
		case 8: month = "August"; break;
		case 9: month = "September"; break;
		case 10: month = "October"; break;
		case 11: month = "November"; break;
		case 12: month = "December"; break;
	}
	// format time
	sprintf_s(time, "%02d:%02d", st.wHour, st.wMinute);
	return month + " " + std::to_string(st.wDay) + ", " + std::to_string(st.wYear) + " " + time;
}

// Iterates through the files
void Scanner::begin_scan(){
	for (recursive_directory_iterator iterator{ startDirectory }, end; iterator != end && during_gui->is_running; ++iterator) {
		if (isDesiredFileType(iterator->path())){
			// pass off to hydra
			cout << iterator->path() << endl;
			currentItem.address = iterator->path(); 
			currentItem.lastAccessed = getFileLastAccessed(iterator->path().string());
			std::lock_guard<std::mutex> guard(thread_handler->m);
			thread_handler->hasher->hash_next(currentItem);
			//thread_handler->hidra->add_node(0, currentItem);
		}
		num_file_added++;
		++totalScanned;
	}
}
//reeeeeeeeeeee

