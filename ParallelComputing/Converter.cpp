#include "iostream"
#include <stdio.h>
#include <string>
#include <map>
#include <boost\thread.hpp>
#include <boost\filesystem.hpp>
#include "Process.h"
#include "Concurrent.h"
#include "Files.h"

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

		if (strcmp(dialog, "create") == 0)
		{
			Io.CreateFiles(1000, 2000);
		}
		if (strcmp(dialog, "convert") == 0)
		{
			boost::thread_group group;
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
			for (auto& process : processPool)
			{
				group.create_thread(std::ref(process));
			}
			group.join_all();
			cout << "Output file is ready." << endl;
		}
		if (strcmp(dialog, "exit") == 0)
		{
			exitCond = true;
		}
	}
	return 0;
}