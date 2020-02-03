#pragma once

#include <fstream>
#include <vector>

#ifdef ANDROID
# include <sstream>
# include "filespot/Asset.h"
#endif

namespace spot::file
{

class Ifstream : public std::ifstream
{
public:
	Ifstream(const char* name, std::ios::openmode mode = std::ios::in);
	Ifstream(const std::string& name, std::ios::openmode mode = std::ios::in);
	
	bool IsOpen() const;
	bool IsEof() const;
	
	const std::string& GetPath() const { return mPath; }
	std::string GetLine();

	std::vector<char> Read(std::streamsize count);

#ifdef ANDROID
	Asset&             GetAsset()  { return mFile; }
	std::stringstream& GetStream() { return mStream; }
#endif

private:
#ifdef ANDROID
	Asset mFile;
	std::stringstream mStream;
#endif
	std::string mPath;
};

}

#ifdef ANDROID
template <typename T>
filespot::Ifstream& operator>>(filespot::Ifstream& is, T& obj)
{
	is.GetStream() >> obj;
	return is;
}
#endif
