#include <cstdlib>
#include <cassert>
#include <filespot/Ifstream.h>

namespace fst = filespot;


int main()
{
	fst::Ifstream is{ "test/test.txt" };

	assert(is.IsOpen());
	assert(is.GetLine() == "test content");

	char buffer[7] = { 0 };
	is.Read(buffer, 6);
	assert(std::string{ buffer } == "second");

	return EXIT_SUCCESS;
}
