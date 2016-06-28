#include "Reporter.h"
#include "Control.h"

void trigger_reporter() {
	//changed********************************************************************************************************************
	//open a filebox that allows a user to select where they would like to place the report that is generated
	filebox fb(true);
	fb.add_filter("Text File", "*.txt");
	fb.add_filter("All Files", "*.*");
	string file;
	if (fb())	//When user clickes 'OK'
	{
		char c;
		file = fb.file();
		for (int i = 0; i < file.size(); i++) {
			c = file.at(i);
			if (c == '\\') {
				file[i] = '/';
			}
		}
		file = file + "\0";
		cout << "\n" + file << endl;
	}
	Reporter reporter = Reporter();
	/*Calls Juan and Jennifer's code to export the report. Be sure to let me know immediately if the UI is not triggering or you wish to modify.*/
	if (!reporter.writeReport(log_gui->get_suspect(), log_gui->get_investigator(), file)) {//The location is default! Sorry I haven't gotten the text input yet.
		cout << "invalid location" << endl;
	}
	//end changed****************************************************************************************************************
};

void Log_GUI::build() {
	frame = new form(API::make_center(425, 250), appearance(true, true, true, false, true, false, false));
	frame->caption(L"Log Export");
	API::window_icon(*frame, nana::paint::image("logo.ico"));
	investigator.create(*frame, rectangle{ 155, 23, 120, 25 }); investigator.multi_lines(false);
	investigator_label.create(*frame, rectangle{ 25, 23, 120, 25 }); investigator_label.format(true); investigator_label.caption("<bold size=10>Investigator Name:</>");

	suspect.create(*frame, rectangle{ 155, 70, 120, 25 }); suspect.multi_lines(false);
	suspect_label.create(*frame, rectangle{ 25, 70, 120, 25 }); suspect_label.format(true); suspect_label.caption("<bold size=10>Suspect Name:</>");
	go_to_log.create(*frame, rectangle{ 200, 210, 100, 30 }, true);
	go_to_log.caption("Create Report");
	go_to_log.events().click(trigger_reporter);
	exit.create(*frame, rectangle{ 305, 210, 100, 30 }, true);
	exit.events().click(API::exit);
	exit.caption("Exit");
	frame->show();
};

Log_GUI::Log_GUI() { };

std::string Log_GUI::get_suspect() {
	string sus = "";
	suspect.getline(0, sus);
	return sus;
};

std::string Log_GUI::get_investigator() {
	string s = "";
	investigator.getline(0, s);
	return s;
};