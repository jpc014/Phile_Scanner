//#pragma once
#include "Control.h"
#include <thread>

using namespace std;
using namespace nana::system;

void trigger_end(const nana::arg_click  &trigger) {
	msgbox current_prompt = msgbox(trigger.window_handle, "Warning! Scan still in progress!", nana::msgbox::button_t::yes_no);
	current_prompt.icon(nana::msgbox::icon_t::icon_warning);
	current_prompt << "Are you sure you want to stop the scan with the progress currently?" << endl;
	current_prompt << "Doing so will result in possible loss of potiential suspect files.";
	current_prompt << endl;
	current_prompt << "Press yes if you are sure you want to go straight to log.";
	if (current_prompt() != current_prompt.pick_no) {
		frame->hide();
		frame->close();
		during_gui->is_running = false;
		end_gui->build();
	}
};

void scan_time_out() {
	during_gui->is_running = false;
	msgbox current_prompt = msgbox(*frame, "Scan Completed", nana::msgbox::button_t::ok);
	current_prompt.icon(nana::msgbox::icon_t::icon_information);
	current_prompt << "The scan on the targetted drives has finished. Please click ok to continue to results screen." << endl;
	current_prompt << endl;
	if (current_prompt() == current_prompt.pick_ok) {
		//end_gui->build();
		//frame->show();
		//frame->umake_event(frame->events().expose(scan_time_out));
		end_gui->build();
		end_gui = new End_GUI();
		end_gui->build();
	}
	frame->show();
}

void update_counts() {
	while (during_gui->is_running) {
		nana::system::sleep(17);
		if (thread_handler->scanners_triggered <= 0) {
			frame->events().destroy(scan_time_out);
			frame->close();
			frame->show();
			//end_gui->build();
		}else{
			during_gui->files_scanned.caption("<size=10>Files Scanned: </><bold size=10>" + to_string(num_file_added) + "</>");
			during_gui->suspect_files.caption("<size=10>Suspected Files: </><bold size=10>" + to_string(num_file_scanned) + "</>");
			/*for (int i = recent_scanned_files.size() - 10; i < recent_scanned_files.size(); i++) {
			if (!recent_scanned_files[i].empty() && during_gui->is_running) {
			during_gui->file_listings.insert(during_gui->file_listings.at(0), recent_scanned_files[i]);
			}
			}*/
			during_gui->file_listings.hide();
			during_gui->file_listings.show();
		}
	}
}

void update_ui() {
	while (during_gui->is_running && during_gui->time_left.minutes + during_gui->time_left.seconds > 0) {
		nana::system::sleep(1000);
		during_gui->time_left.seconds -= 1;
		if (during_gui->time_left.seconds <= 0 && during_gui->time_left.minutes > 0) {
			during_gui->time_left.minutes -= 1;
			during_gui->time_left.seconds = 59;
		}
		double total_time = during_gui->duration.minutes*60;
		double current_time = total_time - (during_gui->time_left.minutes*60 + during_gui->time_left.seconds);
		double time_ratio = (double)current_time / (double)total_time;
		during_gui->progress_bar.value(time_ratio*620.0);
		during_gui->time_remaining.caption("<size=10>Time Remaining: </><bold size=10>" + to_string(during_gui->time_left.minutes) + " minutes " + to_string(during_gui->time_left.seconds) + " seconds" + "</>");
	}
	if (during_gui->is_running) {
		//Ended scan through time constraint force to End_GUI
		frame->events().destroy(scan_time_out);
		frame->close();
	}
};

void trigger_new_scanner() {
	vector<char> drives = start_gui->get_volumes_checked();
	//for (int i = 0; i < drives.size(); i++)
		//cout << "Drive: " << drives[i] << endl;
	cout << "Triggered Scanners: " << thread_handler->scanners_triggered << endl;
	Scanner scan = Scanner(drives[thread_handler->scanners_triggered]);
	++thread_handler->scanners_triggered;
	//nana::system::sleep(2000);
	scan.begin_scan();
	cout << "Finished scanning " << scan.get_drive_letter();
	thread_handler->scanners_triggered--;
};

void trigger_hasher() {
	//cout << "During GUI run state: " << during_gui->is_running << " and triggered scans is: " << thread_handler->scanners_triggered << endl;
	while (during_gui->is_running && thread_handler->scanners_triggered >= 0) {
		//cout << "Hashing thread still running." << endl;
		//if (!thread_handler->hidra->is_empty() && thread_handler->scanners_done_with_hydra) {
			//thread_handler->hasher->hash_next();
		//}
	}
	cout << "Done with Hasher" << endl;
};

void During_GUI::build() {
	frame = new form(API::make_center(800, 450), appearance(true, true, true, false, true, true, false));
	frame->caption(L"During Phase..");
	API::window_icon(*frame, nana::paint::image("logo.ico"));
	files_scanned.create(*frame, rectangle{ 55, 45, 400, 25 }); files_scanned.format(true); files_scanned.caption("<size=10>Files Scanned: </><bold size=10>0</>");
	time_remaining.create(*frame, rectangle{ 55,75,400,25 }); time_remaining.format(true); time_remaining.caption("<size=10>Time Remaining: </><bold size=10>"+to_string(start_gui->scan_duration)+"</> </><bold size=10>minutes </></><bold size=10>00</></><bold size=10> seconds</>");
	suspect_files.create(*frame, rectangle{ 55,105,400,25 }); suspect_files.format(true); suspect_files.caption("<size=10>Suspected Files: </><bold size=10>0</>");
	file_listings.create(*frame, rectangle{15, 150, 765, 250});
	file_listings.append_header("Recently Processed"); file_listings.auto_width(true);
	cancel.create(*frame, rectangle{ 680,410,100,30 });
	cancel.caption("Abort");
	cancel.events().click(trigger_end);
	duration = Time(start_gui->get_minutes_to_run(), 0);
	time_left = Time(duration.minutes-1, 60);
	progress_bar.create(*frame, rectangle{ 45,411,620,20 });
	progress_bar.amount(620);
	frame->show();
	cout << "Scan was set to run for: " << duration.minutes << " minutes." << endl; is_running = true;
	//thread creation example------------------------ you will need to do a pool push for each thread needed.
	during_gui->file_listings.focused();
	thread_handler->hasher = new Hashr(start_gui->get_hashes());
	thread_handler->hasher->hashr_init();
	//thread_handler->scanners_triggered += start_gui->get_num_volumes_checked();
	int num_triggered = 0;
	while (num_triggered < start_gui->get_num_volumes_checked()) {
		if (thread_handler->scanners_triggered >= num_triggered) {
			cout << "Creating a new Scanner on drive: " << start_gui->get_volumes_checked()[num_triggered] << endl;
			thread_handler->scanner_spool.push(trigger_new_scanner);
			num_triggered++;
		}
	}
	thread_handler->ui_thread.push(update_ui);
	thread_handler->ui_thread.push(update_counts);
	//thread_handler->hasher_thread.push(trigger_hasher);
};

During_GUI::During_GUI() {
	scanners_triggered = 0;
};