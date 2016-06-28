#pragma once
#include <nana\gui.hpp>
#include <nana\gui\widgets\button.hpp>
#include <nana\gui\widgets\textbox.hpp>
#include <nana\gui\widgets\combox.hpp>
#include <nana\gui\widgets\spinbox.hpp>
#include <nana\gui\widgets\checkbox.hpp>
#include <nana\gui\widgets\group.hpp>
#include <nana\gui\widgets\listbox.hpp>

using namespace nana;
using namespace std;

class Start_GUI {
public:
	Start_GUI();
	void build();
	int get_minutes_to_run();
	vector<char> get_volumes(); //null when done is not pressed
	vector<char> all_volume_letters; // all found drives
	checkbox volume_checkboxes[26];
	vector<char> get_volumes_checked();
	const int get_num_volumes_checked();
	int get_hashes(); //000 = none, 100 = MD5, 010 = SHA1, 001 = SHA3
	int scan_duration;
	int num_volumes;
	string name = " :/";
	spinbox duration;
	button start_scan;
	nested_form* extra_options;
	radio_group recommended_custom;
	checkbox md5; checkbox sha1; checkbox sha3;
};