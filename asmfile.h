#pragma once
#include <iostream>
#include <vector>

class asmfile
{
public:
	//var
	std::string data;

	//method
	asmfile(std::string path);
	std::vector<uint8_t> compile();

private:
	//var
	const std::string opcode_names[56] = {
		"ADC", "AND", "ASL", "BCC", "BCS", "BEQ", "BIT", "BMI",
		"BNE", "BPL", "BRK", "BVC", "BVS", "CLC", "CLD", "CLI",
		"CLV", "CMP", "CPX", "CPY", "DEC", "DEX", "DEY", "EOR",
		"INC", "INX", "INY", "JMP", "JSR", "LDA", "LDX", "LDY",
		"LSR", "NOP", "ORA", "PHA", "PHP", "PLA", "PLP", "ROL",
		"ROR", "RTI", "RTS", "SBC", "SEC", "SED", "SEI", "STA",
		"STX", "STY", "TAX", "TAY", "TSX", "TXA", "TXS", "TYA"
	};

	//method
	bool has_opcode(std::string line, std::string opcode);
	void convert_string_uppercase(std::string& string);
};