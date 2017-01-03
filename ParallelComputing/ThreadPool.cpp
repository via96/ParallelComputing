#include "iostream"
#include "ThreadPool.h"
#include <boost\thread.hpp>
#include "Process.h"

using namespace std;

ThreadPool::ThreadPool()
{
}


ThreadPool::~ThreadPool()
{
}

void ThreadPool::Start(vector<Process> processPool)
{
	for (auto& process : processPool)
	{
		group.create_thread(std::ref(process));
	}
	group.join_all();
}

