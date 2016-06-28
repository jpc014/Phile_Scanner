#pragma once
#include <nana\system\platform.hpp>
#include <nana\threads\pool.hpp>
#include "Hashr.h"
#include <shared_mutex>

using namespace std;
using namespace nana;
using namespace nana::system;

class Thread_Handler {
public:
	Thread_Handler();
	threads::pool scanner_spool; 
	threads::pool hasher_thread; 
	threads::pool ui_thread;
	threads::pool spool;
	mutex m;
	Hashr* hasher;
	int scanners_triggered;
};