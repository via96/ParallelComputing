#include "iostream"
#include "Concurrent.h"
using namespace std;

#pragma once
class Process
{
public:
	Process(char fileSign, pair<int, int> fileOptions, Concurrent* fileOut);
	~Process();
	void run();
	void init(char fileSign, pair<int, int> fileOptions, Concurrent* fileOut);
	char* GetResult();
	void operator()();
	bool GetFlowStatus();

private:
	Concurrent* outFile;
	bool flowIsBusy;
	char sign;
	int offset;
	int amount;
	char path[8];
	char* letter;
	char* outputStr;
	char* ToUpCase(char* a, int cnt);
};

