//Darryl Idle
#include "Control.h"

Thread_Handler *thread_handler;
form *frame;
Start_GUI *start_gui;
End_GUI *end_gui;
During_GUI *during_gui;
Log_GUI *log_gui;
vector<string> recent_scanned_files;
int num_file_scanned = 0;
int num_file_added = 0;

int main() {
	thread_handler = new Thread_Handler();
	during_gui = new During_GUI();
	end_gui = new End_GUI;
	log_gui = new Log_GUI;
	start_gui = new Start_GUI;
	cout << "Constructed Pointers" << endl;
	start_gui->build();
	return 0;
}