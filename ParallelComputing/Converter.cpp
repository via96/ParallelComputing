#include "iostream"
#include <stdio.h>
#include <string>
#include <map>
#include <boost\thread.hpp>
#include <boost\filesystem.hpp>
#include "Process.h"
#include "Concurrent.h"
#include "Files.h"
#include "ThreadPool.h"

using namespace std;

map<char, pair<int, int>> library;

int main()
{
	char dialog[101];
	bool exitCond = false;
	Files Io;
	while (!exitCond)
	{
		cout << ">>> ";
		cin.getline(dialog, 100);
		if (strcmp(dialog, "help") == 0)
		{
			cout << "create - create starter file kit\nconvert - start converting process" << endl;
		}
		if (strcmp(dialog, "create") == 0)
		{
			Io.CreateFiles(1000, 2000);
		}
		if (strcmp(dialog, "convert") == 0)
		{
			ThreadPool group;
			library = Io.LoadFiles();
			Concurrent outFile("out.txt");
			vector<Process> processPool;
			int iter = 0;
			int offset = 0;
			for (auto it = library.begin(); it != library.end(); ++it, ++iter)
			{
				Process proc(it->first, it->second, &outFile);
				processPool.emplace_back(proc);
			}
			group.Start(processPool);
			cout << "Output file is ready." << endl;
		}
		if (strcmp(dialog, "exit") == 0)
		{
			exitCond = true;
		}
	}
	return 0;
}