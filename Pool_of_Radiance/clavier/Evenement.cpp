#include "Evenement.h"
#include <SDL/SDL_keyboard.h>
#include <iostream>
#include <string>

using std::cout; using std::endl;
using std::string;

Evenement::Evenement() : bQuitter(false), bToggleFullScreen(false)
{}

SDL_Event& Evenement::getEvent() { return event; }

bool Evenement::verifierEvent()
{
	if ( SDL_PollEvent(&event) )
		return traiterEvenementsGeneraux();
	else
		return false;
}

bool Evenement::traiterEvenementsGeneraux()
{
	bool evenementValide = true;
	bToggleFullScreen = false;

	//Cas g�n�raux
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
			case SDLK_F4 :
				if (event.key.keysym.mod & KMOD_ALT)
					bQuitter = true;
				break;

			case SDLK_ESCAPE :
				bQuitter = true;
				break;

			case SDLK_RETURN :
				if (event.key.keysym.mod & KMOD_CTRL)
					bToggleFullScreen = true;
				break;

			default : break;
		}
		break;

	case SDL_QUIT:
		bQuitter = true;
		break;

	default:
		evenementValide = false;
		break;
    }

	return evenementValide;
}

TInfoTouches Evenement::lireClavier()
{
	TInfoTouches infoTouches = { false, false, false, false, '\0', false , false, false};

	if (event.type == SDL_KEYDOWN) {

		Uint16 unicode = event.key.keysym.unicode;
		SDLKey touche  = event.key.keysym.sym;

		if( unicode >= SDLK_EXCLAIM && unicode < SDLK_DELETE ) {

			// 'A-Z' --> 'a-z'
			if (unicode >= 65 && unicode <= 90)
				infoTouches.caractere = (char) (unicode - 65 + 97);

			else if ( (unicode >= SDLK_a && unicode <= SDLK_z)   ||
					  (unicode >= SDLK_0 && unicode <= SDLK_9)    )
				infoTouches.caractere = (char) unicode;

			else {
				switch(unicode) {
				case SDLK_EXCLAIM    : case SDLK_AMPERSAND  :
				case SDLK_AT         : case SDLK_COLON      :
				case SDLK_COMMA      : case SDLK_EQUALS     :
				case SDLK_GREATER    : case SDLK_LESS       :
				case SDLK_LEFTPAREN  : case SDLK_HASH       :
				case SDLK_QUESTION   : case SDLK_QUOTE      :
				case SDLK_QUOTEDBL   : case SDLK_RIGHTPAREN :
				case SDLK_SEMICOLON  : case SDLK_MINUS      :
				case SDLK_KP_MINUS   : case SDLK_ASTERISK   :
				case SDLK_KP_MULTIPLY: case SDLK_PLUS       :
				case SDLK_KP_PLUS    : case SDLK_PERIOD     :
				case SDLK_KP_PERIOD  : case SDLK_SLASH      :
				case SDLK_KP_DIVIDE  :
					infoTouches.caractere = (char) unicode; break;

				default: break;
				}
			}

		} else {
			switch (touche) {
			case SDLK_KP1       : infoTouches.bBas           = true;
								  infoTouches.bGauche        = true; break;
			case SDLK_KP2       : infoTouches.bBas           = true; break;
			case SDLK_KP3       : infoTouches.bBas           = true;
								  infoTouches.bDroite        = true; break;
			case SDLK_KP4       : infoTouches.bGauche        = true; break;
			case SDLK_KP6       : infoTouches.bDroite        = true; break;
			case SDLK_KP7       : infoTouches.bHaut          = true;
								  infoTouches.bGauche        = true; break;
			case SDLK_KP8		: infoTouches.bHaut          = true; break;
			case SDLK_KP9		: infoTouches.bHaut          = true;
								  infoTouches.bDroite        = true; break;
			case SDLK_DOWN		: infoTouches.bBas           = true; break;
			case SDLK_LEFT		: infoTouches.bGauche        = true; break;
			case SDLK_RIGHT		: infoTouches.bDroite        = true; break;
			case SDLK_UP		: infoTouches.bHaut          = true; break;
			case SDLK_RETURN	:
			case SDLK_KP_ENTER	: infoTouches.bEnter         = true; break;
			case SDLK_SPACE		: infoTouches.bEspace        = true; break;
			case SDLK_BACKSPACE	: infoTouches.bRetourArriere = true; break;

			default: break;
			}
		}
	}

	return infoTouches;
}

bool Evenement::estQuitter() { return bQuitter; }

bool Evenement::estToggleFullScreen() { return bToggleFullScreen; }

Evenement::~Evenement() {}
