#include "iostream"
#include <map>
#include <string>
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>

using namespace std;

#pragma once
class Files
{
public:
	Files();
	~Files();
	map<char, pair<int, int>> LoadFiles();
	void CreateFiles(int sizeMin = 2000000, int sizeMax = 10000000);
};

