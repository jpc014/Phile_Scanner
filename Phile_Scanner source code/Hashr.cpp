#include "Hashr.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <iostream>
#include <filesystem>
#include "Control.h"
#include "md5.h"
#include "sha1.h"
#include "sha3.h"

using namespace std;

pathItem hashItem;
int hashTypes;
string hashTarget;
string hashValue;
string targetData;
ifstream dataReader;
long length;
unordered_map<string, string> md5Table;
unordered_map<string, string> sha1Table;
unordered_map<string, string> sha3Table;
char* storage;
bool suspect = false;

Hashr::Hashr(int hashes) {
	hashTypes = hashes;
}

void Hashr::hashr_init() {
	switch (thread_handler->hasher->hashTypes) {
	case 1:
		dataReader.open("MD5_HashTable.txt");
		while (std::getline(dataReader, hashValue)) {
			md5Table[hashValue] = hashValue;
			//cout << "Populated the MD5T with: " << hashValue << endl;
		}
		dataReader.close();
		break;
	case 2:
		dataReader.open("SHA1_HashTable.txt");
		while (std::getline(dataReader, hashValue)) {
			sha1Table[hashValue] = hashValue;
			//cout << "Populated the SHA1T with: " << hashValue << endl;
		}
		dataReader.close();
		break;
	case 3:
		dataReader.open("MD5_HashTable.txt");
		while (std::getline(dataReader, hashValue)) {
			md5Table[hashValue] = hashValue;
			//cout << "Populated the MD5T with: " << hashValue << endl;
		}
		dataReader.close();
		dataReader.open("DSHA1_HashTable.txt");
		while (std::getline(dataReader, hashValue)) {
			sha1Table[hashValue] = hashValue;
			//cout << "Populated the SHA1T with: " << hashValue << endl;
		}
		dataReader.close();
		break;
	case 4:
		dataReader.open("SHA3_HashTable.txt");
		while (std::getline(dataReader, hashValue)) {
			sha3Table[hashValue] = hashValue;
			//cout << "Populated the SH3T with: " << hashValue << endl;
		}
		dataReader.close();
		break;
	case 5:
		dataReader.open("MD5_HashTable.txt");
		while (std::getline(dataReader, hashValue)) {
			md5Table[hashValue] = hashValue;
			//cout << "Populated the MD5T with: " << hashValue << endl;
		}
		dataReader.close();
		dataReader.open("SHA3_HashTable.txt");
		while (std::getline(dataReader, hashValue)) {
			sha3Table[hashValue] = hashValue;
			//cout << "Populated the SH3T with: " << hashValue << endl;
		}
		dataReader.close();
		break;
	case 6:
		dataReader.open("SHA1_HashTable.txt");
		while (std::getline(dataReader, hashValue)) {
			sha1Table[hashValue] = hashValue;
			//cout << "Populated the SHA1T with: " << hashValue << endl;
		}
		dataReader.close();
		dataReader.open("SHA3_HashTable.txt");
		while (std::getline(dataReader, hashValue)) {
			sha3Table[hashValue] = hashValue;
			//cout << "Populated the SH3T with: " << hashValue << endl;
		}
		dataReader.close();
		break;
	case 7:
		dataReader.open("MD5_HashTable.txt");
		while (std::getline(dataReader, hashValue)) {
			md5Table[hashValue] = hashValue;
			//cout << "Populated the MD5T with: " << hashValue << endl;
		}
		dataReader.close();
		dataReader.open("SHA1_HashTable.txt");
		while (std::getline(dataReader, hashValue)) {
			sha1Table[hashValue] = hashValue;
			//cout << "Populated the SHA1T with: " << hashValue << endl;
		}
		dataReader.close();
		dataReader.open("SHA3_HashTable.txt");
		while (std::getline(dataReader, hashValue)) {
			sha3Table[hashValue] = hashValue;
			//cout << "Populated the SH3T with: " << hashValue << endl;
		}
		dataReader.close();
		break;
	}
}
string Hashr::getData(string files) {
	if (files != "") {
		dataReader.open(files, std::ios::binary | std::ios::in); //opens files as binary
		dataReader.seekg(0, std::ios::end); // moves curser to the end
		length = dataReader.tellg(); // gets position of the end
		dataReader.seekg(0, std::ios::beg); // moves cursor to beginning
		storage = new char[length]; // creates char array the length of the file
		dataReader.read((char*)storage, length);// stores the bits into storage
		dataReader.close(); //closes file
		std::string data(storage, length);
		return data;
	}
	return "";
}

void Hashr::hash_next(pathItem path) {
	//string retrieved = thread_handler->hidra->hydra_next().address.string();
	//std::lock_guard<std::shared_timed_mutex> guard(thread_handler->m);
	//pathItem node_to_hash = thread_handler->hidra->remove_node();
	string retrieved = path.address.string();
	const char* to_hash = retrieved.c_str();
	//cout << "Grabbed data from: " << retrieved.c_str() << endl;
	switch (hashTypes) {
	case 1:
		md5Hash(to_hash, path.address); //hashes and checks data in storage against hash map
		break;
	case 2:
		sha1Hash(to_hash, path.address); //hashes and checks data in storage against hash map
		break;
	case 3:
		md5Hash(to_hash, path.address); //hashes and checks data in storage against hash map
		sha1Hash(to_hash, path.address); //hashes and checks data in storage against hash map
		break;
	case 4:
		sha3Hash(to_hash, path.address); //hashes and checks data in storage against hash map
		break;
	case 5:
		md5Hash(to_hash, path.address); //hashes and checks data in storage against hash map
		sha3Hash(to_hash, path.address); //hashes and checks data in storage against hash map
		break;
	case 6:
		sha1Hash(to_hash, path.address); //hashes and checks data in storage against hash map
		sha3Hash(to_hash, path.address); //hashes and checks data in storage against hash map
		break;
	case 7:
		md5Hash(to_hash, path.address); //hashes and checks data in storage against hash map
		sha1Hash(to_hash, path.address); //hashes and checks data in storage against hash map
		sha3Hash(to_hash, path.address); //hashes and checks data in storage against hash map
		break;
	}
	num_processed++;
	//recent_scanned_files.push_back(retrieved);
	if (suspect) {
		pathItem push; push.address = retrieved; push.lastAccessed = path.lastAccessed;
		suspect_files_found.push_back(push);
		cout << "Suspect file: " << push.address << endl;
		num_file_scanned++;
		suspect = false;
	}
	during_gui->file_listings.insert(during_gui->file_listings.at(0), retrieved);
	//guard.unlock();
	//guard.release();
}

void Hashr::md5Hash(const char* file, path hash_item) {
	MD5 hash = MD5(file, 32);
	hashValue = hash.getHash();
	ofstream fout; fout.open("C:/Users/darry/Desktop/MD5_HashTable.txt", ofstream::app);
	fout << hashValue << endl;
	fout.close();
	//cout << "MD5: " << hashValue << endl;
	//cout << "MD5HashTable value: " << md5Table[hashValue] << endl;
	if (md5Table[hashValue] == hashValue) {
		suspect = true;
	}
}

void Hashr::sha1Hash(const char* file, path hash_item) {
	SHA1 hash = SHA1(file, 32);
	hashValue = hash.getHash();
	ofstream fout; fout.open("C:/Users/darry/Desktop/SHA1_HashTable.txt", ofstream::app);
	fout << hashValue << endl;
	fout.close();
	//cout << "SHA1: "<< hashValue << endl;
	if (sha1Table[hashValue] == hashValue) {
		suspect = true;
	}
}

void Hashr::sha3Hash(const char* file, path hash_item) {
	SHA3 hash = SHA3(file, 32);
	hashValue = hash.getHash();
	//ofstream fout; fout.open("C:/Users/darry/Desktop/SHA3_HashTable.txt", ofstream::app);
	//fout << hashValue << endl;
	//fout.close();
	//cout << hashValue << endl;
	if (sha3Table[hashValue] == hashValue) {
		suspect = true;
	}
}