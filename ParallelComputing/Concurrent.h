#include "iostream"
#include <stdio.h>
#include <boost\thread.hpp>

using namespace std;

#pragma once
class Concurrent
{
public:
	Concurrent(char* path);
	~Concurrent();
	void Write(char* outStr, int amount, int offset);

private:
	string path;
	FILE* file;
	boost::mutex lock;
	char control;
};

