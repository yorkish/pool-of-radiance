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

vector<InfoAlloc> gbl_Memoire;

void montrerSequenceMemoire();

int main(int argc, char** argv) 
{
	bool bErreur = false;
	MainLoop oMainLoop;

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	//initialise le générateur de nombres aléatoires
	srand( (unsigned) time(NULL) );

	bErreur = oMainLoop.start();

	SDL_ShowCursor(SDL_ENABLE);

	montrerSequenceMemoire();

	return (!bErreur) ? EXIT_SUCCESS : EXIT_FAILURE;
}

void montrerSequenceMemoire()
{
	vector<InfoAlloc>::iterator iter;
	int nbNew     = 0, nbDel     = 0;
	int nbNewText = 0, nbDelText = 0;

	if(gbl_Memoire.size() == 0)
    	return;

    for(iter = gbl_Memoire.begin(); iter != gbl_Memoire.end(); iter++) {
    	if ((*iter).type == 'A') nbNewText++;
    	if ((*iter).type == 'R') nbDelText++;
    	if ((*iter).type == 'N') nbNew++;
    	if ((*iter).type == 'D') nbDel++;
    }

    if ((nbNew != nbDel) || (nbNewText != nbDelText)) {
        for(iter = gbl_Memoire.begin(); iter != gbl_Memoire.end(); iter++) {

        	if ((*iter).type == 'A' || (*iter).type == 'R')
        		cout << "    ";

        	cout << "(" << (*iter).type << ") " << (*iter).source << ":" << (*iter).line << endl;
        }

		if (nbNew != nbDel) {
			cout << endl << "Memory Leak!!!!" << endl;
			cout << "News: " << nbNew << ", " << "Deletes: " << nbDel << endl;
		}

		if (nbNewText != nbDelText) {
			cout << endl << "TEXT Memory Leak!!!!" << endl;
			cout << "News: " << nbNewText << ", " << "Deletes: " << nbDelText << endl;
		}
    }

    gbl_Memoire.clear();
};
