#include <cstdlib>
#include <cassert>
#include <spot/file/ifstream.h>
#include <spot/file/file.h>

namespace fl = spot::file;


void testIfstream()
{
	fl::Ifstream is{ "test/test.txt" };

	assert(is.is_open());
	assert(is.get_line() == "test content");
}


void testFile()
{
	assert(fl::File::exists("test/test.txt"));

	fl::File f{ "test/test.txt" };
	assert( f.is_open() );
}


int main()
{
	testIfstream();
	testFile();

	return EXIT_SUCCESS;
}
