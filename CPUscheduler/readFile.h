#ifndef READFILE_H
#define READFILE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "process.h"

class readFile
{
public:
	std::vector<Process> readInputFile(char* fileName);
};

#endif // READFILE_H

