#include <iostream>
#include <format>
#include <fstream>
#include "asmfile.h"
#include "ultra_asm.h"

//https://stackoverflow.com/a/12774387/20913909
static bool file_exists(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

std::string read_file(std::string path)
{
	if (file_exists(path) == false) return std::format("{}", kPrefix + kDoesntExit);
	std::ifstream file(path);
	std::string string_buffer((std::istreambuf_iterator<char>(file)),
	std::istreambuf_iterator<char>());
	file.close();
	return string_buffer;
}

bool exists(std::string string, std::string to_find)
{
	if (string.find(to_find) == std::string::npos) return false;
	return true;
}

int count_bit(int number)
{
	int counter = 0;
	while (number != 0)
	{
		number = number >> 1;
		counter++;
	}
	return counter;
}

void message(uint_fast8_t type, std::string message)
{
	uint_fast8_t message_bit = MessageFlags & type;
	if ((message_bit) != 0) std::cout << std::format("\n{}{}", message_types[count_bit(message_bit)-1], message);
}

std::string only_filename(std::string filepath)
{
	return filepath.substr(filepath.find_last_of('\\')+1, filepath.size());
}

//ultra_asm.exe main.asm output.nes -l -w
//l: generate list
//w: show warnings
int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout << std::format("\nUsage: {} main.asm output.nes -l -w\nl: generate listing\n-w: show warnings\n", only_filename(argv[0]));
		return -1;
	}
	std::string cmd_input;
	for (uint_fast8_t i = 1; i < argc; i++) cmd_input += argv[i];
	//check for flags
	if (exists(cmd_input, "-w")) MessageFlags += kWarning;

	//start with main
	asmfile main(argv[1]);
	if (main.data == std::format("{}", kPrefix + kDoesntExit))
	{
		message(kError, std::format("Can't find main file: {}\n", argv[1]));
	}
}
