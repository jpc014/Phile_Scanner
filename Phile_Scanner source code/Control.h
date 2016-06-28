#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include "Start_GUI.h"
#include "During_GUI.h"
#include "End_GUI.h"
#include "Log_GUI.h"
#include "Thread_Handler.h"
#include "Scanner.h"
#include "Globals.h"

static const int MD5_HASH = 3;
static const int SHA1_HASH = 2;
static const int SHA3_HASH = 1;
extern int num_file_scanned;
extern int num_file_added;
extern vector<string> recent_scanned_files;

extern Thread_Handler *thread_handler;
extern form *frame;
extern Start_GUI *start_gui;
extern End_GUI *end_gui;
extern During_GUI *during_gui;
extern Log_GUI *log_gui;