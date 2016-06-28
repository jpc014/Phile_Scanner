#pragma once
#include <string.h>
#include <nana\gui.hpp>
#include <nana\gui\widgets\button.hpp>
#include <nana\gui\widgets\label.hpp>
#include <nana\gui\widgets\textbox.hpp>
#include <nana\gui\filebox.hpp>//added this

using namespace nana;

class Log_GUI {
public:
	Log_GUI();
	void build();
	std::string get_suspect();
	std::string get_investigator();
	textbox investigator; textbox suspect;
	label investigator_label; label suspect_label;

	button go_to_log;
	button exit;
};