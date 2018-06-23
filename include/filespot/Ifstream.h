#ifndef FST_IFSTREAM_H_
#define FST_IFSTREAM_H_

#include <fstream>

#ifdef ANDROID
# include <sstream>
# include "filespot/AssetManager.h"
#endif

namespace filespot
{

class Ifstream : public std::ifstream
{
public:
	Ifstream(const char* name);
	Ifstream(const std::string& name);
	
	bool IsOpen() const;
	bool IsEof() const;
	
	const std::string& GetPath() const { return mPath; }
	std::string GetLine();

private:
#ifdef ANDROID
	Asset mFile;
	std::stringstream mStream;
#endif
	std::string mPath;
};

}

#endif // SST_IFSTREAM_H
