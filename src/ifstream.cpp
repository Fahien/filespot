#include <string>
#include <memory>
#include <algorithm>

#ifdef WIN32
# include <cstdlib>
# include <iostream>
#else // other systems
# include <libgen.h>
#endif

#include "spot/file/ifstream.h"


namespace spot::file
{


Ifstream::Ifstream( const char* name, std::ios::openmode mode )
:	Ifstream( std::string{ name }, mode )
{}

std::string dirname( const std::string& path )
{
	auto it = std::find( path.rbegin(), path.rend(), '/' );
	if ( it == std::rend( path ) )
	{
		return "."; // cwd
	}

	return path.substr( 0, it - std::rend( path ) );
}

Ifstream::Ifstream( const std::string& name, std::ios::openmode mode )
#ifdef ANDROID
:	file{ name }
,	stream{ file.get_content(), mode }
#else
:	std::ifstream( name, mode )
#endif
#ifdef WIN32
,	path{}
#else // other systems
,	path{ dirname( name ) }
#endif
{
#ifdef WIN32
	char buf[32];
	_splitpath_s( name.c_str(), nullptr, 0, buf, 32, nullptr, 0, nullptr, 0 );
	path = buf;
#endif

	// Stop eating new lines in binary mode
	if ( mode == std::ios::binary )
	{
		#ifdef ANDROID
		stream.unsetf(std::ios::skipws);
		#else
		unsetf( std::ios::skipws );
		#endif
	}
}


bool Ifstream::is_open() const
{
#ifdef ANDROID
	return true;
#else
	return std::ifstream::is_open();
#endif
}


bool Ifstream::is_eof() const
{
#ifdef ANDROID
	return stream.eof();
#else
	return eof();
#endif
}


std::string Ifstream::get_line()
{
#ifdef ANDROID
	const size_t size{ 128 };
	char buffer[size];
	stream.getline(buffer, size);
	std::string line{ buffer };
#else // other systems
	std::string line;
	std::getline( *this, line );
#endif
	return line;
}


std::vector<char> Ifstream::read( std::streamsize count )
{
#ifdef ANDROID
	std::vector<char> buffer;
	buffer.reserve( count );
	// Read the data
	const char* begin = file.get_content();
	const char* end   = begin + count;
	buffer.insert( buffer.end(), begin, end );
	return buffer;
#else // other systems
	std::vector<char> content( count );
	seekg( 0, std::ios_base::beg );
	std::ifstream::read( content.data(), count );
	return content;
#endif
}

} // namespace spot::file
