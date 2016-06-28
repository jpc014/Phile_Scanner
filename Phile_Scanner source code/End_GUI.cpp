
#include "Control.h"

void create_report_log() {
	frame->hide();
	frame->close();
	log_gui->build();
};

void End_GUI::build() {
	frame = new form(API::make_center(800, 450), appearance(true, true, true, false, true, true, false));
	frame->caption(L"Scan Results");
	API::window_icon(*frame, nana::paint::image("logo.ico"));
	files_scanned.create(*frame, rectangle{ 55, 45, 400, 25 }); files_scanned.format(true); files_scanned.caption("<size=10>Files Scanned: </><bold size=10>"+to_string(num_file_added)+"</>");
	int minutes_ran = during_gui->duration.minutes - during_gui->time_left.minutes-1;
	int seconds_ran = 60-during_gui->time_left.seconds;
	time_remaining.create(*frame, rectangle{ 55,75,400,25 }); time_remaining.format(true); time_remaining.caption("<size=10>Time Elapsed: </><bold size=10>"+to_string(minutes_ran)+"</> </><bold size=10>minutes </></><bold size=10>"+to_string(seconds_ran)+"</></><bold size=10> seconds</>");
	suspect_files.create(*frame, rectangle{ 55,105,400,25 }); suspect_files.format(true); suspect_files.caption("<size=10>Suspected Files: </><bold size=10>"+to_string(suspect_files_found.size())+"</>");
	file_listings.create(*frame, rectangle{ 15, 150, 765, 250 });
	file_listings.append_header("Found Files");
	file_listings.enabled(true);
	for (int i = 0; i < suspect_files_found.size(); i++) {
		file_listings.insert(file_listings.at(0), suspect_files_found[i].address);
	}
	exit.create(*frame, rectangle{ 680,410,100,30 });
	exit.caption("Go to Log");
	exit.events().click(create_report_log);
	frame->show();
};

End_GUI::End_GUI() { };
