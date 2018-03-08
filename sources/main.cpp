#define SDL_main main

#include <time.h>
#include <iostream>
#include <vector>
#include <string>
#include "common/Global.h"
#include "MainLoop.h"

using std::cout;
using std::endl;
using std::vector;
using std::string;

vector<InfoAlloc> _gblMemory;

void showMemorySequence()
{
	int nbNew = 0, nbDel = 0;
	int nbNewText = 0, nbDelText = 0;

	if (_gblMemory.size() == 0) return;

	for (InfoAlloc info : _gblMemory)
	{
		if (info.type == 'A') nbNewText++;
		if (info.type == 'R') nbDelText++;
		if (info.type == 'N') nbNew++;
		if (info.type == 'D') nbDel++;
	}

	if ((nbNew != nbDel) || (nbNewText != nbDelText))
	{
		for (InfoAlloc info : _gblMemory)
		{

			if (info.type == 'A' || info.type == 'R') cout << "    ";

			cout << "(" << info.type << ") " << info.source << ":" << info.line
					<< endl;
		}

		if (nbNew != nbDel)
		{
			cout << endl << "Memory Leak!!!!" << endl;
			cout << "News: " << nbNew << ", " << "Deletes: " << nbDel << endl;
		}

		if (nbNewText != nbDelText)
		{
			cout << endl << "TEXT Memory Leak!!!!" << endl;
			cout << "News: " << nbNewText << ", " << "Deletes: " << nbDelText
					<< endl;
		}
	}

	_gblMemory.clear();
}

int main(int argc, char** argv)
{
	uint8_t returnCode = false;
	MainLoop oMainLoop;

	// Hack needed on a Windows system
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	// Init the seed for random numbers
	srand((unsigned) time(NULL));

	returnCode = oMainLoop.start();

	showMemorySequence();

	return returnCode;
}
