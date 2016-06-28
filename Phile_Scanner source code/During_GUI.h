#pragma once
#include <string>
#include <ctime>
#include <nana\gui.hpp>
#include <nana\gui\widgets\button.hpp>
#include <nana\gui\widgets\label.hpp>
#include <nana\gui\widgets\progress.hpp>
#include <nana\gui\widgets\textbox.hpp>

using namespace std;
using namespace nana;

class During_GUI {
public:
	class Time {
	public:
		int minutes; int seconds;
		Time() { minutes = 0; seconds = 0; }
		Time(int min, int sec) {
			minutes = min; seconds = sec;
		}
	};
	During_GUI();
	void build();
	bool is_running;
	Time duration; Time time_left; 
	int scanners_triggered;
	listbox file_listings;
	progress progress_bar;
	button cancel;
	label files_scanned; label time_remaining; label suspect_files;
};