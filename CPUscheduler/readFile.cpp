#include "readFile.h"


using namespace std;

std::vector<Process> readFile::readInputFile(char* fileName)
{
	vector<Process> process;	// vector that holds all the processes from the input file

	// read file
	ifstream file;
	string line;
	stringstream ss;
	file.open(fileName);

	// open file
	if (file.is_open())
	{
		int tempPid, tempAT, tempBT, tempP;		// temp values to hold variables

		// while there is more input
		while (getline(file, line))
		{
			ss << line;	
			ss >> tempPid >> tempAT >> tempBT >> tempP;
			
			// set up temp for single process from input file
			Process temp(tempPid, tempAT, tempBT, tempP);
			process.push_back(temp);		// add to processlist
			ss.clear();						// keep going until end of file
		}
	}
	else 
	{
		// error opening file
		cout << "File not found.." << endl;
		exit(0);		// end program?
		//return;		// end program?
	}

	file.close();
	// return the filled vector of processes
	return process;
}
