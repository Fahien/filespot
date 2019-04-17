#include "filespot/File.h"


using namespace filespot;


bool File::Exists(const std::string& name)
{
	std::ifstream ifs{ name };
	return ifs.good();
}


File::File(const std::string& name)
: mStream{ name }
{}
