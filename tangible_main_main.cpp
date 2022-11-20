#include <string>
#include <vector>
#include <APL/Main.h>

int main(int argc, char **argv)
{
	std::vector<std::wstring> args(argv + 1, argv + argc);
	APL::Main::main(args);
}

