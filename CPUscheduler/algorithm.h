#ifndef ALGORITHM_H
#define ALGORITHM_H

// holds fcfs, srtf, rr, and pp algorithms and the display function

#include <iostream>
#include <vector>

#include "process.h"


using namespace std;

class Algorithm
{
public:
	void FCFS(vector<Process>);
	void SRTF(vector<Process> process);
	void RR(vector<Process> process, int quantum);
	void PP(vector<Process> process);
	void displayOutput(vector<Process> process, string name);
};

#endif // !ALGORITHM_H


