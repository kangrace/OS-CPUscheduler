#include "process.h"

Process::Process(int pid, float arrivalTime, float burstTime, float priority)
{
	this->pid = pid;
	this->arrivalTime = arrivalTime;
	this->burstTime = burstTime;
	this->priority = priority;
};

Process::Process(int pid, float arrivalTime, float burstTime, float priority,
	float finishTime, float waitTime, float turnaround, float response, int contextSwitch)
{
	this->pid = pid;
	this->arrivalTime = arrivalTime;
	this->burstTime = burstTime;
	this->priority = priority;
	this->finishTime = finishTime;
	this->waitTime = waitTime;
	this->responseTime = response;
	this->contextSwitch = contextSwitch;
}


bool operator<(Process const & lhs, Process const & rhs)
{

	return lhs.remainingTime < rhs.remainingTime;
}



