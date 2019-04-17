#include <cstdlib>
#include <cassert>
#include <filespot/Ifstream.h>
#include <filespot/File.h>

namespace fst = filespot;


void testIfstream()
{
	fst::Ifstream is{ "test/test.txt" };

	assert(is.IsOpen());
	assert(is.GetLine() == "test content");
}


void testFile()
{
	assert(fst::File::Exists("test/test.txt"));

	fst::File f{ "test/test.txt" };
	assert(f.IsOpen());
}


int main()
{
	testIfstream();
	testFile();

	return EXIT_SUCCESS;
}
