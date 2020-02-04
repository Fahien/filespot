#include "spot/file/file.h"


namespace spot::file
{


bool File::exists(const std::string& name)
{
	std::ifstream ifs{ name };
	return ifs.good();
}


File::File(const std::string& name)
: stream{ name }
{}

}
