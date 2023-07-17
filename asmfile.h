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
	enum literal_opcode {
		cADC, cAND, cASL, cBCC, cBCS, cBEQ, cBIT, cBMI, 
		cBNE, cBPL, cBRK, cBVC, cBVS, cCLC, cCLD, cCLI, 
		cCLV, cCMP, cCPX, cCPY, cDEC, cDEX, cDEY, cEOR, 
		cINC, cINX, cINY, cJMP, cJSR, cLDA, cLDX, cLDY, 
		cLSR, cNOP, cORA, cPHA, cPHP, cPLA, cPLP, cROL, 
		cROR, cRTI, cRTS, cSBC, cSEC, cSED, cSEI, cSTA, 
		cSTX, cSTY, cTAX, cTAY, cTSX, cTXA, cTXS, cTYA
	};
	uint8_t implied_opcode[56] = {
		0, 0, 0x0A, 0, 0, 0, 0, 0,
		0, 0, 0x00, 0, 0, 0x18, 0xD8, 0x58,
		0xB8, 0, 0, 0, 0, 0xCA, 0x88, 0,
		0, 0xE8, 0xC8, 0, 0, 0, 0, 0,
		0x4A, 0xEA, 0, 0x48, 0x08, 0x68, 0x28, 0x2A,
		0x6A, 0x40, 0x60, 0, 0x38, 0xF8, 0x78, 0,
		0, 0, 0xAA, 0xA8, 0xBA, 0x8A, 0x9A, 0x98
	};

	//method
	uint_fast32_t end_of_line(uint_fast32_t pos, std::string this_line);
	bool has_opcode(std::string line, std::string opcode);
	bool handle_opcode(std::vector<uint8_t>& compiled_bytes, uint_fast32_t pos, uint8_t opcode);
	void convert_string_uppercase(std::string& string);
};