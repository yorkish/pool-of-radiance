#include "MainLoop.h"
#include "common/Global.h"
#include "common/Affichage.h"
#include "clavier/Evenement.h"
#include "Jeu.h"
#include "common/Timer.h"
#include "common/Donnees.h"

#include <iostream>

using std::cout;
using std::endl;

MainLoop::MainLoop()
{
}

uint8_t MainLoop::start()
{
	Affichage& affichage = Affichage::getInstance();
	Jeu oJeu;
	Timer fps;
	TInfoTouches infoTouches;
	uint8_t returnCode = EXIT_SUCCESS;

	cout << "renderer init attempt..." << endl;
	if (affichage.initRenderer())
	{
		cout << "game init attempt..." << endl;
		if (oJeu.init())
		{
			cout << "main loop entered..." << endl;

			while (true)
			{
				fps.start();

				if (oEvenement.verifierEvent())
				{
					if (oEvenement.estToggleFullScreen())
					{
						affichage.toggleFullScreen();
					}
					else
						if (oEvenement.estQuitter())
						{
							break;
						}

					infoTouches = oEvenement.lireClavier();

					oJeu.handleEvent(infoTouches);
					oJeu.move();
				}

				oJeu.verifierMessages();

				affichage.preRender();

				oJeu.draw();

				affichage.postRender();

				affichage.introduireDelai(fps.get_ticks());

				if (oJeu.exitRequested())
				{
					break;
				}
			}
		}
		else
		{
			cout << "Game init failure - " << SDL_GetError() << endl;
			returnCode = EXIT_FAILURE;
		}
	}
	else
	{
		cout << "Renderer init failure - " << SDL_GetError() << endl;
		returnCode = EXIT_FAILURE;
	}

	SDL_ShowCursor(SDL_ENABLE);

	return returnCode;
}

MainLoop::~MainLoop()
{
}
