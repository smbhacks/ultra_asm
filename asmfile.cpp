#include "asmfile.h"
#include "ultra_asm.h"
#include <iostream>
#include <fstream>

asmfile::asmfile(std::string path)
{
	data = read_file(path);
}