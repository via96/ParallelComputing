#include "iostream"
#include "Process.h"
#include <string>
#include "Concurrent.h"
#include <boost\thread.hpp>
#include <boost\filesystem.hpp>

using namespace std;

Process::Process(char fileSign, pair<int, int> fileOptions, Concurrent* fileOut)
{
	
	path[0] = 'i';
	path[1] = 'n';
	path[2] = '\\';
	path[3] = fileSign;
	path[4] = '.';
	path[5] = 't';
	path[6] = 'x';
	path[7] = 't';
	outFile = fileOut;
	flowIsBusy = false;
	sign = fileSign;
	offset = fileOptions.first;
	amount = fileOptions.second;
	
}

Process::~Process()
{

}

void Process::run()
{
	outputStr = ToUpCase(letter, amount);
	outFile->Write(outputStr, amount, offset);
}

void Process::init(char fileSign, pair<int, int> fileOptions, Concurrent* fileOut)
{
	outFile = fileOut;
	flowIsBusy = false;
	sign = fileSign;
	offset = fileOptions.first;
	amount = fileOptions.second;
}

char * Process::GetResult()
{
	return outputStr;
}

void Process::operator()()
{
	if (boost::filesystem::is_regular_file(path))
	{
		boost::filesystem::ifstream file(path);
		string text = "";
		long long int length = 0;
		file.seekg(0, boost::filesystem::ifstream::end);
		length = file.tellg();
		file.seekg(0, boost::filesystem::ifstream::beg);
		char* inputTextBuffer = new char[length];
		file.read(inputTextBuffer, length);
		letter = inputTextBuffer;
		file.close();
	}
	run();
	outFile->Write(outputStr, amount, offset);
}

bool Process::GetFlowStatus()
{
	return flowIsBusy;
}


char* Process::ToUpCase(char* a, int cnt)
{
	for (int i = 0; i < cnt; ++i)
		if (a[i] >= 'a' && a[i] <= 'z')
			a[i] -= 32;
	return a;
}