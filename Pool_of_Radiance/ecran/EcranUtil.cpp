#include "EcranUtil.h"
#include "../common/Affichage.h"

EcranUtil::EcranUtil(): oAffichage(Affichage::getInstance()), tuileMenu(0) {}

bool EcranUtil::init()
{
	if (tuileMenu == 0)
		tuileMenu = oAffichage.loadImageAsSurface("data/images/common.png", 0, 0, 0);

	return (tuileMenu != 0);
}

void EcranUtil::dessinerCadre(Couleur couleurFond)
{
	int x,y;
	SDL_Rect src;

	if ( init() ) {
		oAffichage.wipeScreen(couleurFond);

		src.w = 8; src.h = 8;

		//Les 4 coins
		src.x = 0; src.y = 0;
		oAffichage.applySurface(  0,   0, tuileMenu, src);
		oAffichage.applySurface(312,   0, tuileMenu, src);
		oAffichage.applySurface(  0, 184, tuileMenu, src);
		oAffichage.applySurface(312, 184, tuileMenu, src);

		//Les lignes verticales
		src.x = 8; src.y = 0;
		for (y=8; y < 184; y += 8) {
			oAffichage.applySurface(0  , y, tuileMenu, src);
			oAffichage.applySurface(312, y, tuileMenu, src);
		}

		//Les lignes horizontales
		src.x = 16; src.y = 0;
		for (x=8; x < 312; x += 8) {
			oAffichage.applySurface(x,   0, tuileMenu, src);
			oAffichage.applySurface(x, 184, tuileMenu, src);
		}
	}
}

void EcranUtil::dessinerCadreEtPortrait()
{
	int x,y;
	SDL_Rect src;

	dessinerCadre();

	src.w = 8; src.h = 8;

	//Les 3 coins supplémentaires
	src.x = 0; src.y = 0;
	oAffichage.applySurface(216,  0, tuileMenu, src);
	oAffichage.applySurface(216, 96, tuileMenu, src);
	oAffichage.applySurface(312, 96, tuileMenu, src);

	//La ligne verticale
	src.x = 8; src.y = 0;
	for (y=8; y < 96; y += 8)
		oAffichage.applySurface(216, y, tuileMenu, src);

	//La ligne horizontale
	src.x = 16; src.y = 0;
	for (x=224; x < 312; x += 8)
		oAffichage.applySurface(x, 96, tuileMenu, src);
}

EcranUtil::~EcranUtil()
{
	if (tuileMenu != 0)
		SDL_FreeSurface(tuileMenu);
}
