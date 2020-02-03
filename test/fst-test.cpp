#include <cstdlib>
#include <cassert>
#include <spot/file/ifstream.h>
#include <spot/file/file.h>

namespace fl = spot::file;


void testIfstream()
{
	fl::Ifstream is{ "test/test.txt" };

	assert(is.IsOpen());
	assert(is.GetLine() == "test content");
}


void testFile()
{
	assert(fl::File::Exists("test/test.txt"));

	fl::File f{ "test/test.txt" };
	assert(f.IsOpen());
}


int main()
{
	testIfstream();
	testFile();

	return EXIT_SUCCESS;
}
