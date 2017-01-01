#define SDL_main main

#include <SDL2/SDL.h>
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
	bool bErreur = false;
	MainLoop oMainLoop;

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	// Init the seed for random numbers
	srand((unsigned) time(NULL));

	bErreur = oMainLoop.start();

	SDL_ShowCursor(SDL_ENABLE);

	showMemorySequence();

	return (!bErreur) ? EXIT_SUCCESS : EXIT_FAILURE;
}
