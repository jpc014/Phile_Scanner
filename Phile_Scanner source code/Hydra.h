#pragma once
#include "pathItem.h"

class Hydra {
public:
	struct node_thing {
		node_thing* next;
		node_thing* previous;
		pathItem content;
	};
	Hydra(int preffered_comb_size, const int num_drives);
	pathItem remove_node();
	int add_node(int drive, pathItem fileLoc);
	bool is_empty();
	int iterate();
private:
	int comb_size, num_heads, size;
	node_thing current_node;
	node_thing *heads;
};