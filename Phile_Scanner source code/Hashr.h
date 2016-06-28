#pragma once
#include <string>
#include <fstream>
#include <unordered_map>
#include <iostream>
#include "Hydra.h"
#include <filesystem>

using namespace std;

//hashNext() will call getData with the file path from hydra_next, grab the data from the file, then 
//use that to call the different hash methods nessessary which will all hash the toggle suspect to TRUE 
//if they collide with the data in the tables, hashNext then returns that bool after all hashes finish
//and sets suspect to FALSE for the next pass

class Hashr {
public:
	Hashr(int hashes);
	Hashr() {}; 
	void hash_next(pathItem path);
	void hashr_init();
	void md5Hash(const char* file, path hash_item);
	void sha1Hash(const char* file, path hash_item);
	void sha3Hash(const char* file, path hash_item);
	int hashTypes; int num_processed; bool suspect; bool done_with_hydra;
private:
	Hydra * hydraPoint;
	ifstream dataReader;
	long length;
	pathItem hashItem;
	string hashTarget;
	string hashValue;
	string targetData;
	unordered_map<string, string> md5Table;
	unordered_map<string, string> sha1Table;
	unordered_map<string, string> sha3Table;
	char* storage;
	
	string getData(string file);
};
