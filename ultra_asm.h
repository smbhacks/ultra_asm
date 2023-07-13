#pragma once
#include <iostream>
//const
#define bit0 0b1
#define bit1 0b10
#define bit2 0b100
#define bit3 0b1000
#define bit4 0b10000
#define bit5 0b100000
#define bit6 0b1000000
#define bit7 0b10000000
const uint_fast8_t kError = bit0;
const uint_fast8_t kWarning = bit1;
const std::string message_types[]
{
	"[ERROR] ",
	"[WARNING] "
};
const std::string kPrefix = "ua.";
const std::string kDoesntExit = "doesnt_exist";


//global vars
uint_fast8_t MessageFlags = kError;

//misc
std::string only_filename(std::string filepath);
void message(uint_fast8_t type, std::string message);
int count_bit(int number);
bool exists(std::string string, std::string to_find);
std::string read_file(std::string path);