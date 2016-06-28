#include "Reporter.h"

using namespace std;
using namespace std::tr2::sys;

// input: Suspect's Name, investigator's name, and a pointer to an output stream
// output: .txt file with all of the found files that met the criteria 
// need to do: fix last parameter(file data structure?)
bool Reporter::writeReport(std::string suspectName, std::string investigatorName, std::string location) {

	ofstream fout;

	//create output file at location specified
	fout.open(location);

	if (fout.fail()) {
		return false;
	}
	//write headings
	fout << "Investigator's Name: " + investigatorName << endl;
	fout << "Suspect's Name: " + suspectName << endl;
	fout << "Number of files scanned: " + std::to_string(num_file_added) << endl;
	fout << "Number of matches: " + std::to_string(num_file_scanned) << endl;
	fout << "Date: " + getSystemTimeDate() + "\n" << endl;

	//write body
	fout << "#\t\tDate last accessed\t\tAddress\n----------------------------------------------------------------------------------------------------------------" << endl;
	int i;

	for (i = 0; i < suspect_files_found.size(); i++) {
		fout << std::to_string(i + 1) + "\t|\t" + suspect_files_found.at(i).lastAccessed + "\t|\t" + suspect_files_found.at(i).address.string() << endl;
	}

	//close output file
	fout.close();

	return true;
}

// when called returns a string in the format: Month day, Year time (time is in 24 hour format)
std::string Reporter::getSystemTimeDate() {
	std::string month;
	char time[6];

	//get date
	SYSTEMTIME st = { 0 };

	GetLocalTime(&st);

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