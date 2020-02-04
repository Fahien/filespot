#pragma once

#include <fstream>
#include <string>


namespace spot::file
{


class File
{
  public:
	static bool exists( const std::string& name );

	File( const std::string& name );

	std::ifstream& get_stream() { return stream; }

	bool is_open() const { return stream.is_open(); }

  private:
	std::ifstream stream;
};

} // namespace spot::file
