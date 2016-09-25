#include "iostream"
#include "Concurrent.h"
#include <boost\thread.hpp>
#include <boost\interprocess\sync\scoped_lock.hpp>



Concurrent::Concurrent(char* path) : path(path)
{
	fopen_s(&file, path, "w");
	control = 'a';
}


Concurrent::~Concurrent()
{
	fclose(file);
}

void Concurrent::Write(char* outStr, int amount, int offset)
{
	boost::interprocess::scoped_lock<boost::mutex> locked(lock);
	fseek(file, offset, SEEK_SET);
	fwrite(outStr, sizeof(char), amount, file);
	if (control != outStr[0])
		cout << "Output symbol: " << outStr[0] << " | amount: " << amount << "|" << endl;
	control = outStr[0];
}