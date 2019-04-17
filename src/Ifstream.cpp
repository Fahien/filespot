#include <string>
#include <memory>
#ifdef WIN32
# include <cstdlib>
# include <iostream>
#else // other systems
# include <libgen.h>
#endif

#include "filespot/Ifstream.h"


using namespace filespot;


Ifstream::Ifstream(const char* name, std::ios::openmode mode)
:	Ifstream(std::string{ name }, mode)
{}


Ifstream::Ifstream(const std::string& name, std::ios::openmode mode)
#ifdef ANDROID
:	mFile{ name }
,	mStream{ mFile.GetContent(), mode }
#else
:	std::ifstream(name, mode)
#endif
#ifdef WIN32
,	mPath{}
#else // other systems
,	mPath{ dirname(const_cast<char*>(name.data())) }
#endif
{
#ifdef WIN32
	char path[32];
	_splitpath_s(name.c_str(), nullptr, 0, path, 32, nullptr, 0, nullptr, 0);
	mPath = path;
#endif

	// Stop eating new lines in binary mode
	if (mode == std::ios::binary)
	{
		#ifdef ANDROID
		mStream.unsetf(std::ios::skipws);
		#else
		unsetf(std::ios::skipws);
		#endif
	}
}


bool Ifstream::IsOpen() const
{
#ifdef ANDROID
	return true;
#else
	return is_open();
#endif
}


bool Ifstream::IsEof() const
{
#ifdef ANDROID
	return mStream.eof();
#else
	return eof();
#endif
}


std::string Ifstream::GetLine()
{
#ifdef ANDROID
	const size_t size{ 128 };
	char buffer[size];
	mStream.getline(buffer, size);
	std::string line{ buffer };
#else // other systems
	std::string line;
	std::getline(*this, line);
#endif
	return line;
}


std::vector<char> Ifstream::Read(std::streamsize count)
{
#ifdef ANDROID
	std::vector<char> buffer;
	buffer.reserve(count);
	// Read the data
	const char* begin = mFile.GetContent();
	const char* end   = begin + count;
	buffer.insert(buffer.end(), begin, end);
	return buffer;
#else // other systems
	auto content = std::unique_ptr<char[]>(new char[count]);
	seekg(0, std::ios_base::beg);
	read(content.get(), count);
	return std::vector<char>{ content.get(), content.get() + count };
#endif
}
