#include "iostream"
#include <boost\thread.hpp>
#include "Process.h"

using namespace std;

#pragma once
class ThreadPool
{
public:
	ThreadPool();
	~ThreadPool();
	void Start(vector<Process> processPool);

private:
	boost::thread_group group;
};

