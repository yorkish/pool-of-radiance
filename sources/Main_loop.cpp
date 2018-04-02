#include "Main_loop.h"

#include <iostream>

#include "common/Global.h"
#include "clavier/Evenement.h"
#include "Jeu.h"
#include "common/Timer.h"
#include "common/Donnees.h"
#include "common/Renderer.h"

using std::cout;
using std::endl;

Main_loop::Main_loop() {}

uint8_t Main_loop::start()
{
	raiicap<Renderer> rendererCap;
	Renderer renderer(rendererCap);

	Jeu oJeu(renderer);
	Timer fps;
	TInfoTouches infoTouches;
	uint8_t returnCode = EXIT_SUCCESS;

	cout << "renderer init attempt..." << endl;
	if (renderer.initRenderer())
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
						renderer.toggleFullScreen();
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

				renderer.preRender();

				oJeu.draw();

				renderer.postRender();

				renderer.sleep(fps.get_ticks());

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

Main_loop::~Main_loop() {}
