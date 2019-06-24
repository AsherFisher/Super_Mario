
//===============   include section   =============================================

#include "FileReader.h"
#include <sstream>

//--------------------  c'tor   -----------------------------------------------

FileReader::FileReader()
{
}

//--------------------------   read paragrph  ----------------------------------

void FileReader::readPragraph(std::ifstream& file, std::vector < std::unique_ptr<std::string>>& m_level, int i)
{
	std::string line;
	while (i > 0)    // read a full level
	{
		std::getline(file, line);
		m_level.push_back(std::make_unique <std::string>(line));
		i--;
	}
	return;
}

//--------------  read line   ---------------------------------------------------

std::string FileReader::readLine(std::ifstream& file, bool& run)
{
	std::string line;
	if (file.eof())
	{
		run = false;
		return line;
	}
	while (std::getline(file, line) && !line.size());

	return line;
}

//-------------------   d'tor  ----------------------------------------------

FileReader::~FileReader()
{
}
