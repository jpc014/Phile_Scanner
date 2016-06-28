#include "Control.h"
#include <Math.h>
#include <Windows.h>
#include <nana\gui\widgets\scroll.hpp>
#include <nana\gui\widgets\textbox.hpp>
#include <nana\gui\widgets\label.hpp>
#include <nana\gui\widgets\combox.hpp>
#include <nana\gui\widgets\group.hpp>
#include <nana\gui\widgets\listbox.hpp>

using namespace nana;
using namespace std;
using namespace std::tr2::sys;

void trigger_during(const nana::arg_click& trigger) {
	bool checked_hashes = false; bool checked_drives = false;
	if (start_gui->get_hashes() > 0) checked_hashes = true;
	if (start_gui->get_num_volumes_checked() > 0) checked_drives = true;
	if (checked_drives && checked_hashes) {
		start_gui->scan_duration = stoi(start_gui->duration.value());
		frame->hide();
		frame->close();
		/*Calls Joe, Derek, Keebler, Vickers, and Matt's code to create nana threads and other respective tasks.
		Be sure to let me know immediately if the UI is not triggering or you wish to modify.
		*/
		during_gui->build();
	}
	else {
		msgbox current_prompt = msgbox(*frame, "Invalid Scan Parameters", nana::msgbox::button_t::ok);
		current_prompt.icon(nana::msgbox::icon_t::icon_information);
		current_prompt << "Invalid input for scan parameters. Please check a drive to scan and a hash to use." << endl;
		current_prompt();
	}
}

void default_settings(const nana::arg_click& trigger) {
	cout << "Recommended settings!" << endl;
	start_gui->duration.value("20");
	start_gui->md5.check(true);
	start_gui->sha1.check(true);
	for (int i = 0; i < start_gui->get_volumes().size(); i++)
		start_gui->volume_checkboxes[i].check(true);
	start_gui->duration.enabled(false);
	start_gui->extra_options->enabled(false);
	start_gui->extra_options->bgcolor(color::color(220, 220, 220));
};

void allow_custom_settings() {
	cout << "Enabled Custom Settings window!" << endl;
	start_gui->duration.value("20");
	start_gui->duration.enabled(true);
	start_gui->extra_options->enabled(true);
	start_gui->extra_options->bgcolor(color::color(255, 255, 255));
	for (int i = 0; i < start_gui->get_volumes().size(); i++)
		start_gui->volume_checkboxes[i].check(false);
	start_gui->md5.check(false);
	start_gui->sha1.check(false);
};

void Start_GUI::build() {
	frame = new form(API::make_center(800, 600), appearance(true, true, true, false, true, false, false));
	frame->caption(L"Phile_Scanner");
	API::window_icon(*frame, nana::paint::image("logo.ico"));

	recommended_custom = radio_group();
	checkbox recommended(*frame, rectangle{ 45,45,200,20 });
	checkbox custom(*frame, rectangle{ 45,80,200,20 });
	recommended.caption("Recommended Settings");
	custom.caption("Custom Settings");
	recommended.events().click(default_settings);
	custom.events().click(allow_custom_settings);
	recommended_custom.add(recommended);
	recommended_custom.add(custom);

	extra_options = new nested_form(*frame, rectangle{ 15,150,765,400 }, appearance(false, false, false, false, false, false, false));
	extra_options->bgcolor(color::color(255, 255, 255)); scroll<true>::scroll(extra_options->parent(), rectangle{ 0,0, 200,100 });
	label drives_label(*extra_options, rectangle{ 630, 10, 120, 25 }); drives_label.format(true); drives_label.caption("<bold size = 10>Selected Drives:</>");

	all_volume_letters = start_gui->get_volumes();
	num_volumes = all_volume_letters.size();

	for (int i = 0; i < num_volumes; i++) {
		name[0] = all_volume_letters.at(i);
		volume_checkboxes[i].create(*extra_options, rectangle{ 630 , i * 20 + 50, 100, 22 });
		volume_checkboxes[i].caption(name);
		volume_checkboxes[i].bgcolor(color::color(255, 255, 255));
		volume_checkboxes[i].show();
	}

	duration.create(*extra_options, rectangle{ 23,23,70,24 }); duration.value("20");
	label duration_label(*extra_options, rectangle{ 120,25,120,20 }); duration_label.format(true); duration_label.caption("<bold size=10>Duration(minutes)</>");
	label hashes(*extra_options, rectangle{ 35,80, 100, 22 }); hashes.format(true); hashes.caption("<bold size=12>Hashes</>");
	md5.create(*extra_options, rectangle{ 25, 110, 100, 22 }); md5.caption("MD5 Hash"); md5.bgcolor(color::color(255, 255, 255));
	sha1.create(*extra_options, rectangle{ 25, 140, 100, 22 }); sha1.caption("SHA1 Hash"); sha1.bgcolor(color::color(255, 255, 255));
	sha3.create(*extra_options, rectangle{ 25, 170, 100, 22 }); sha3.caption("SHA3 Hash"); sha3.bgcolor(color::color(255, 255, 255));
	start_scan.create(*frame, rectangle{ 680,560,100,30 });
	start_scan.events().click(trigger_during);
	start_scan.caption("Start Scan");
	extra_options->show();
	frame->show();
	nana::exec();
};

Start_GUI::Start_GUI() {
	ShowWindow(GetConsoleWindow(), SW_HIDE); //Is here for when we deploy to hide the console for testing.
}

vector<char> Start_GUI::get_volumes() {
	vector<char> volumes_vector = vector<char>();
	DWORD drive_buffer = 128;
	TCHAR lp_buffer[128];
	DWORD test = GetLogicalDriveStrings(drive_buffer, lp_buffer);

	for (int i = 0; i < 128; i += 4) {
		if (lp_buffer[i] == NULL) {
			break;
		}
		else {
			volumes_vector.push_back(lp_buffer[i]);
			//cout << "Added to volumes_vector: " << (char)lp_buffer[i] << endl;
		}
	}
	//cout << "Number of drives found: " << volumes_vector.size() << endl;
	return volumes_vector;
}

int Start_GUI::get_hashes() {
	return ((md5.checked()) ? 1 : 0) + ((sha1.checked()) ? 2 : 0) + ((sha3.checked()) ? 4 : 0);
};

const int Start_GUI::get_num_volumes_checked() {
	int num_drives_checked = 0;
	for (int i = 0; i < num_volumes; i++)
		if (volume_checkboxes[i].checked())
			num_drives_checked++;
	cout << num_drives_checked << endl;
	return num_drives_checked;
};

vector<char> Start_GUI::get_volumes_checked() {
	vector<char> volumes_checked;
	for (int i = 0; i < num_volumes; i++)
		if (volume_checkboxes[i].checked())
			volumes_checked.push_back(all_volume_letters[i]);
	return volumes_checked;
}

int Start_GUI::get_minutes_to_run() {
	return scan_duration;
}