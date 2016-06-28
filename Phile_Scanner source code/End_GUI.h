#pragma once

#include <iostream>
#include <nana\gui.hpp>
#include <nana\gui\widgets\button.hpp>
#include <nana\gui\widgets\textbox.hpp>
#include <nana\gui\widgets\label.hpp>
#include <nana\gui\widgets\listbox.hpp>

using namespace nana;

class End_GUI {
public:
	class Time {
	public:
		int minutes; int seconds;
		Time() { minutes = 0; seconds = 0; }
		Time(int min, int sec) {
			minutes = min; seconds = sec;
		}
	};
	End_GUI();
	void build();
	char get_choice_of_export_volume();
protected:
	Time time_elapsed;
	listbox file_listings;
	label files_scanned; label time_remaining; label suspect_files;
	button go_to_log;
	button exit;
};