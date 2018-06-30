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

	auto buffer = is.Read(6);
	buffer.push_back('\0');
	assert(std::string{ buffer.data() } == "second");
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
