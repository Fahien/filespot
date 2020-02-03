#pragma once

#include <fstream>
#include <string>


namespace spot::file
{


class File
{
  public:
	static bool Exists(const std::string& name);

	File(const std::string& name);

	std::ifstream& GetStream() { return mStream; }

	bool IsOpen() const { return mStream.is_open(); }

  private:
	std::ifstream mStream;
};

}
