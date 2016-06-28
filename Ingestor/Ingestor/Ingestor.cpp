// Ingestor.cpp : main project file.
// Just an example of how to use the MD5 hashing with native Windows CLR
// CLR utilizes the .NET Framework!

#include "stdafx.h"
#include <fstream>
//for converting
#include <msclr/marshal_cppstd.h>
//vectors and sorting them
#include <vector>
#include <algorithm>
#include <string>
//for outputing to a file
#include <fstream>

//temp
#include <iostream>

using namespace System;
using namespace System::Security::Cryptography;
using namespace System::Security;
using namespace System::Text;
using namespace System::IO;


array<System::Byte> ^FileToByteArray(System::String ^_FileName) {
	//reference http://www.digitalcoding.com/Code-Snippets/CPP-CLI/C-CLI-Code-Snippet-Convert-file-to-byte-array.html
	array<System::Byte> ^_Buffer = nullptr;
	try {
		// Open file for reading
		System::IO::FileStream ^_FileStream = gcnew System::IO::FileStream(_FileName, System::IO::FileMode::Open, System::IO::FileAccess::Read);
		
		// attach filestream to binary reader
		System::IO::BinaryReader ^_BinaryReader = gcnew System::IO::BinaryReader(_FileStream);

		// get total byte length of the file
		System::IO::FileInfo ^_FileInfo = gcnew System::IO::FileInfo(_FileName);
		System::Int64 _TotalBytes = _FileInfo->Length;

		// read entire file into buffer
		_Buffer = _BinaryReader->ReadBytes(safe_cast<Int32>(_TotalBytes));
		
		// close file reader
		_FileStream->Close();
		delete _FileStream;
		_BinaryReader->Close();
	}

	catch (Exception ^_Exception)
	{
		// Error
		Console::WriteLine("Exception caught in process: {0}", _Exception->ToString());
	}
	return _Buffer;
}

String^ getMD5String_file(String^ filePath)
{
	array<Byte>^ byteArray = FileToByteArray(filePath);
	MD5CryptoServiceProvider^ md5provider = gcnew MD5CryptoServiceProvider();
	array<Byte>^ byteArrayHash = md5provider->ComputeHash(byteArray);
	return BitConverter::ToString(byteArrayHash);
}

String^ getSHA1String_file(String^ filePath)
{
	array<Byte>^ byteArray = FileToByteArray(filePath);
	SHA1CryptoServiceProvider^ sha1provider = gcnew SHA1CryptoServiceProvider();
	array<Byte>^ byteArrayHash = sha1provider->ComputeHash(byteArray);
	return BitConverter::ToString(byteArrayHash);
}

String^ getSHA3String_file(String^ filePath)
{
	array<Byte>^ byteArray = FileToByteArray(filePath);
	SHA384^ sha3provider = SHA384::Create();
	array<Byte>^ byteArrayHash = sha3provider->ComputeHash(byteArray);
	return BitConverter::ToString(byteArrayHash);
}

int main(array<String^> ^args)
{
	//initialize hash vectors
	std::vector<std::string> MD5Vector;
	std::vector<std::string> SHA1Vector;
	std::vector<std::string> SHA3Vector;

	//for converting from String^ to std::string
	msclr::interop::marshal_context context;

	bool cont = true; String^ answer = "y";
	Console::WriteLine("-------------==========Image Ingestor=========-----------------------------------------");
	while (cont) {
		Console::Clear();
		Console::WriteLine("In order to hash a folder of files you must input the desired location of input below:");
		//list directory
		String^ folder = Console::ReadLine();
		array<String^>^ file = Directory::GetFiles(folder);
		Console::WriteLine("--== Files inside '{0}' ==--", folder);
		Console::WriteLine("Hashing...");
		for (int i = 0; i < file->Length; i++) {
			//make a call the the hashing funtions here

			// add to vector
			std::string md5 = context.marshal_as<std::string>(getMD5String_file(file[i]));
			std::string sha1 = context.marshal_as<std::string>(getSHA1String_file(file[i]));
			std::string sha3 = context.marshal_as<std::string>(getSHA3String_file(file[i]));

			md5.erase(remove(md5.begin(), md5.end(), '-'), md5.end());
			sha1.erase(remove(sha1.begin(), sha1.end(), '-'), sha1.end());
			sha3.erase(remove(sha3.begin(), sha3.end(), '-'), sha3.end());

			MD5Vector.push_back(md5);
			SHA1Vector.push_back(sha1 );
			SHA3Vector.push_back(sha3);
		}
		
		//sort vectors
		Console::WriteLine("Sorting MD5...");
		std::sort(MD5Vector.begin(), MD5Vector.end());

		Console::WriteLine("Sorting SHA1...");
		std::sort(SHA1Vector.begin(), SHA1Vector.end());

		Console::WriteLine("Sorting SHA3...");
		std::sort(SHA3Vector.begin(), SHA3Vector.end());

		//Write to file

		std::ofstream MD5File;
		std::ofstream SHA1File;
		std::ofstream SHA3File;
		
		Console::WriteLine("Done sorting");

		Console::WriteLine("Removing duplicates...");
		MD5Vector.erase(unique(MD5Vector.begin(), MD5Vector.end()), MD5Vector.end());
		SHA1Vector.erase(unique(SHA1Vector.begin(), SHA1Vector.end()), SHA1Vector.end());
		SHA3Vector.erase(unique(SHA3Vector.begin(), SHA3Vector.end()), SHA3Vector.end());

		Console::WriteLine("Writing data to file...");
		MD5File.open(context.marshal_as<std::string>(folder) + "//MD5_HashTable.txt");
		for (int g = 0; g < MD5Vector.size(); g++)
		{
			MD5File << MD5Vector.at(g) + "\n";
		}
		MD5File.close();
		

		SHA1File.open(context.marshal_as<std::string>(folder) + "//SHA1_HashTable.txt");
		for (int g = 0; g < SHA1Vector.size(); g++)
		{
			SHA1File << SHA1Vector.at(g) + "\n";
		}
		SHA1File.close();

		SHA3File.open(context.marshal_as<std::string>(folder) + "//SHA3_HashTable.txt");
		for (int g = 0; g < SHA3Vector.size(); g++)
		{
			SHA3File << SHA3Vector.at(g) + "\n";
		}
		SHA3File.close();

		MD5Vector.clear();
		SHA1Vector.clear();
		SHA3Vector.clear();

		Console::WriteLine("Do you wish to continue? Please type (y/n) below:");
		answer = Console::ReadLine();
		Console::WriteLine(answer);
		if (answer == "y" || answer == "Y" || answer == "yes" || answer == "Yes") { cont = true; }
		else { cont = false; }
	}
	return 0;
}