#pragma once

//============= include section   ===========================================

#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include "FileReader.h"

//=============   class file reader   =======================================

class FileReader
{

public:

	// c'tor
	FileReader();
	// func to read the current level
	void readPragraph(std::ifstream& file, std::vector<std::unique_ptr<std::string>>& m_level, int i);
	// read one line from the text file, use also to check the high score
	std::string readLine(std::ifstream& file, bool& run);
	// d'tor
	~FileReader();
};

