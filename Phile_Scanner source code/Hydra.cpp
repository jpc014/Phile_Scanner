#pragma once
#include "Hydra.h"

using namespace std;

Hydra::Hydra(int preffered_comb_size, const int num_drives) {
	size = 0;
	comb_size = preffered_comb_size;
	num_heads = num_drives;
	heads = new node_thing[num_drives];
	for (int i = 0; i<num_heads-1; i++)
		heads[i].next = &heads[i + 1];
	for (int i = 1; i<num_heads; i++)
		heads[i].previous = &heads[i - 1];
	heads[0].previous = &heads[num_drives - 1];
	heads[num_drives - 1].next = &heads[0];
	current_node = heads[0];
	for(int i = 0; i < 6; i++)
		add_node(0, pathItem("D:/File.jpg", ""));
}

bool Hydra::is_empty() {
	return size == 0;
}

//returns new size
int Hydra::add_node(int drive, pathItem fileLoc) {
	node_thing new_node;
	new_node.content = fileLoc;
	new_node.next = heads[drive].next;
	new_node.previous = &heads[drive];
	heads[drive].next = &new_node;
	new_node.next->previous = &new_node;
	size++;
	return ++size;
}

//returns comb used
int Hydra::iterate() {
	for (int i = 0; i<(size>10) ? comb_size : 1; i++)
		current_node = *current_node.next;
	return (size>10) ? comb_size : 1;
}

pathItem Hydra::remove_node() {
	if (is_empty()) return pathItem("C:/", "");
	node_thing tmp = current_node;
	while (tmp.content.address.string() == "") { tmp = *tmp.next; }
	size--;
	tmp.previous->next = tmp.next;
	tmp.next->previous = tmp.previous;
	current_node = *tmp.next;
	Hydra::iterate();
	return tmp.content;
}