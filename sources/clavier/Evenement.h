#pragma once

#include <SDL2/SDL.h>
#include "../common/Global.h"

static class Evenement
{
	public:
		Evenement();

		SDL_Event& getEvent();
		
		bool verifierEvent();
		TInfoTouches lireClavier();
		
		bool estQuitter();
		bool estToggleFullScreen();

		~Evenement();

	private:
		bool traiterEvenementsGeneraux();

		SDL_Event event;

		bool bQuitter;
		bool bToggleFullScreen;

} oEvenement;
