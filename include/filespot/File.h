#ifndef FST_FILE_H_
#define FST_FILE_H_

#include <fstream>
#include <string>


namespace filespot
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


#endif // FST_FILE_H_
