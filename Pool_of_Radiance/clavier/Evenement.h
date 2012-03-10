#pragma once

#include <SDL/SDL.h>
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
		void PrintKeyInfo( SDL_KeyboardEvent *key );
		void PrintModifiers( SDLMod mod );

		SDL_Event event;

		bool bQuitter;
		bool bToggleFullScreen;

} oEvenement;
