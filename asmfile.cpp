#include "asmfile.h"
#include "ultra_asm.h"
#include <iostream>
#include <fstream>
#include <format>
#include <cstring>

//public--------------------------------
asmfile::asmfile(std::string path)
{
	data = read_file(path);
}

std::vector<uint8_t> asmfile::compile()
{
	std::vector<uint8_t> compiled_bytes;
	uint_fast32_t pos = 0;
	uint_fast32_t end = 0;
	do
	{
		//skip empty lines (this part of the code works)
		while (data[pos] == '\n') pos++;
		if (pos >= data.size()) break;

		//this doesnt
		std::string this_line = data.substr(pos, data.find('\n', pos) == std::string::npos ? std::string::npos : data.find('\n', pos) - pos);
		std::string this_line_uppercase = this_line;
		convert_string_uppercase(this_line_uppercase);
		std::uint_fast8_t opcode_name_id = UINT8_MAX;
		for (uint_fast8_t i = 0; i < 56; i++)
		{
			if (has_opcode(this_line_uppercase, opcode_names[i]))
			{
				opcode_name_id = i;
				break;
			}
		}
		if (opcode_name_id != UINT8_MAX) message(kWarning, std::format("Found opcode: {}", opcode_names[opcode_name_id]));

		if (this_line.find_first_of(':') < this_line.size())
		{
			pos += this_line.find_first_of(':') + 1;
			continue;
		}
		pos = data.find('\n', pos + 1);
	} while (pos < data.size());

	return compiled_bytes;
}

//private-------------------------------

bool asmfile::has_opcode(std::string line, std::string opcode)
{
	return line.find(opcode) != std::string::npos ? true : false;
}

void asmfile::convert_string_uppercase(std::string& string)
{
	for (uint_fast32_t i = 0; i < string.size(); i++) string[i] = toupper(string[i]);
}
