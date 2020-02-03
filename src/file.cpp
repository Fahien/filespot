#include "spot/file/file.h"


namespace spot::file
{


bool File::Exists(const std::string& name)
{
	std::ifstream ifs{ name };
	return ifs.good();
}


File::File(const std::string& name)
: mStream{ name }
{}

}
