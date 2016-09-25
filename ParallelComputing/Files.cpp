#include "iostream"
#include <string>
#include <boost/filesystem.hpp>
#include <map>
#include "Files.h"

using namespace std;

Files::Files()
{
}


Files::~Files()
{
}

map<char, pair<int, int>> Files::LoadFiles()
{
	int curSize;
	//FILE* file;
	int offset = 0;
	map<char, pair<int, int>> input;
	boost::filesystem::directory_iterator end_itr;
	for (boost::filesystem::directory_iterator itr("in"); itr != end_itr; itr++)
	{
		if (boost::filesystem::is_regular_file(itr->path()))
		{
			string inputPath = itr->path().string();
			if (inputPath != "")
			{
				boost::filesystem::ifstream file(inputPath);
				string text = "";
				long long int length = 0;
				file.seekg(0, boost::filesystem::ifstream::end);
				length = file.tellg();
				file.seekg(0, boost::filesystem::ifstream::beg);
				char* inputTextBuffer = new char[length];
				file.read(inputTextBuffer, length);
				string inputText(inputTextBuffer);
				input[inputTextBuffer[0]] = { offset, length };
				offset += length;
				file.close();
			}
		}
	}
	return input;
}



void Files::CreateFiles(int sizeMin, int sizeMax)
{
	srand(time(0));
	boost::filesystem::create_directory("in");
	for (char c = 'a'; c <= 'z'; c++)
	{
		string fileName({ c });
		fileName += ".txt";
		boost::filesystem::ofstream file("in\\" + fileName);
		int size = rand() % (sizeMax - sizeMin) + sizeMin;
		for (int i = 0; i < size; i++)
			file << c;
		file.close();
		cout << "Create file " << fileName << endl;
	}
	cout << "Files creation completed!" << endl;
}