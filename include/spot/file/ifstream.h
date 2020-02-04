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
	Ifstream( const char* name, std::ios::openmode mode = std::ios::in );
	Ifstream( const std::string& name, std::ios::openmode mode = std::ios::in );
	
	bool is_open() const;
	bool is_eof() const;
	
	const std::string& get_path() const { return path; }
	std::string get_line();

	std::vector<char> read( std::streamsize count );

#ifdef ANDROID
	Asset&             get_asset()  { return file; }
	std::stringstream& get_stream() { return stream; }
#endif

private:
#ifdef ANDROID
	Asset file;
	std::stringstream stream;
#endif
	std::string path;
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
