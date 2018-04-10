#include <iostream>

#include "readFile.h"
#include "algorithm.h"
#include "queue.h"
#include "process.h"

using namespace std;

// unix prompt format, first argument is file name, second is algorithm, thrid is quantum size
// myscheduler	 test-input-file-name	 0		4
			
char* inputFile;				// file name
readFile r;						// readInputFile is member function of class readFile
vector<Process> inputProcess;	// vector to hold all processes
Algorithm a;					// FCFS(), RR(), etc is member function of class algorithm

int main(int argc, char* argv[])
{
	if (argc)
	{
		// FCFS
		if (atoi(argv[2]) == 0)
		{
			inputFile = argv[1];
			inputProcess = r.readInputFile(inputFile);
			a.FCFS(inputProcess);
		}

		// SRTF
		else if (atoi(argv[2]) == 1)
		{
			inputFile = argv[1];
			inputProcess = r.readInputFile(inputFile);
			a.SRTF(inputProcess);
		}

		// RR with a valid quantum number
		else if (atoi(argv[2]) == 2 && atoi(argv[3]) > 1)
		{
			inputFile = argv[1];
			int quantum = atoi(argv[3]);
			inputProcess = r.readInputFile(inputFile);
			a.RR(inputProcess, quantum);
		}

		// PP
		else if (atoi(argv[2]) == 3)
		{
			inputFile = argv[1];
			inputProcess = r.readInputFile(inputFile);
			a.PP(inputProcess);
		}
	}
	system("pause");
}

