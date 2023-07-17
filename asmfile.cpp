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
		while (data[pos] == '\n' && pos < data.size()-1) pos++;
		if (pos >= data.size()) break;

		std::string this_line = data.substr(pos, data.find('\n', pos) == std::string::npos ? std::string::npos : data.find('\n', pos) - pos);
		std::string this_line_uppercase = this_line;
		convert_string_uppercase(this_line_uppercase);
		std::uint_fast8_t opcode_name_id = UINT8_MAX;
		for (uint_fast8_t i = 0; i < 56; i++)
		{
			if (has_opcode(this_line_uppercase, opcode_names[i]))
			{
				opcode_name_id = i;
				//   *--- set pos here and handle this opcode
				//LDA 
				handle_opcode(compiled_bytes, this_line_uppercase.find(opcode_names[i])+3, i);
				break;
			}
		}
		if (opcode_name_id != UINT8_MAX) message(kWarning, std::format("Found opcode: {}", opcode_names[opcode_name_id]));

		pos = end_of_line(pos, this_line);
	} while (pos < data.size());

	return compiled_bytes;
}

//private-------------------------------

bool asmfile::has_opcode(std::string line, std::string opcode)
{
	int pos = line.find(opcode);
	return line.find(opcode) < line.size() ? true : false;
}

void asmfile::convert_string_uppercase(std::string& string)
{
	for (uint_fast32_t i = 0; i < string.size(); i++) string[i] = toupper(string[i]);
}

uint_fast32_t asmfile::end_of_line(uint_fast32_t pos, std::string this_line)
{
	if (this_line.find(':') < this_line.size())
	{
		pos += this_line.find(':') + 1;
	}
	else pos = data.find('\n', pos + 1);
	return pos;
}

bool asmfile::handle_opcode(std::vector<uint8_t>& compiled_bytes, uint_fast32_t pos, uint8_t opcode)
{
	while (data[pos] == ' ' && pos < data.size() - 1)
	{
		pos++;
		if (data[pos] == '\n' || data[pos] == ':') return false; //case where there is nothing after opcode
	}
	if (pos >= data.size()) return false; //case where there is no value and out of bounds

	switch (opcode)
	{
	case cADC:
	case cAND:
	case cBCC:
	case cBCS:
	case cBEQ:
	case cBIT:
	case cBMI:
	case cBNE:
	case cBPL:
	case cBVC:
	case cBVS:
	case cCMP:
	case cCPX:
	case cCPY:
	case cDEC:
	case cEOR:
	case cINC:
	case cINX:
	case cINY:
	case cJMP:
	case cJSR:
	case cLDA:
	case cLDX:
	case cLDY:
	case cLSR:
	case cORA:
	case cROL:
	case cROR:
	case cSBC:
	case cSTA:
	case cSTX:
	case cSTY:
		break;

		//These are definitely implied
	case cBRK:
	case cCLC:
	case cCLD:
	case cCLI:
	case cCLV:
	case cDEX:
	case cDEY:
	case cNOP:
	case cPHA:
	case cPHP:
	case cPLA:
	case cPLP:
	case cRTI:
	case cRTS:
	case cSEC:
	case cSED:
	case cSEI:
	case cTAX:
	case cTAY:
	case cTSX:
	case cTXA:
	case cTXS:
	case cTYA:
		compiled_bytes.push_back(implied_opcode[opcode]);
		break;
	}
}
