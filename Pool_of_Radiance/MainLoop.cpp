#include "MainLoop.h"
#include "common/Global.h"
#include "common/Affichage.h"
#include "clavier/Evenement.h"
#include "Jeu.h"
#include "common/Timer.h"
#include "common/Donnees.h"

MainLoop::MainLoop()
{
}

bool MainLoop::start()
{
	Affichage& affichage = Affichage::getInstance();
	Jeu oJeu;
	Timer fps;
	int ticks;
	TInfoTouches infoTouches;

	if (!affichage.initRenderer())
	{
		return true;
	}

	if (!oJeu.init())
	{
		return true;
	}

	while (true)
	{
		fps.start();

		if (oEvenement.verifierEvent())
		{
			if (oEvenement.estToggleFullScreen())
			{
				affichage.toggleFullScreen();
			}
			else if (oEvenement.estQuitter())
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

		affichage.preRender();

		ticks = fps.get_ticks();
		if (ticks < DELAIS_MS)
		{
			affichage.introduireDelai(DELAIS_MS - ticks);
		}

		if (oJeu.exitRequested())
		{
			break;
		}
	}

	return false;
}

MainLoop::~MainLoop()
{
}
