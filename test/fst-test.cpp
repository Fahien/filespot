#include <cstdlib>
#include <cassert>
#include <filespot/Ifstream.h>

namespace fst = filespot;


int main()
{
	fst::Ifstream is{ "test/test.txt" };

	assert(is.IsOpen());
	assert(is.GetLine() == "test content");

	return EXIT_SUCCESS;
}
