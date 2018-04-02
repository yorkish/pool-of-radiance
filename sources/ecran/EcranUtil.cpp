#include "EcranUtil.h"
#include "../common/Renderer.h"

EcranUtil::EcranUtil(): tuileMenu(0) {}

bool EcranUtil::init(Renderer &renderer)
{
	if (tuileMenu == 0)
		tuileMenu = renderer.loadImage("assets/common.png", 0, 0, 0);

	return (tuileMenu != 0);
}

void EcranUtil::dessinerCadre(Renderer &renderer, Couleur couleurFond)
{
	int x,y;
	SDL_Rect src;

	if ( init(renderer) ) {
		renderer.wipeScreen(couleurFond);

		src.w = 8; src.h = 8;

		//Les 4 coins
		src.x = 0; src.y = 0;
		renderer.applyTexture(  0,   0, tuileMenu, src);
		renderer.applyTexture(312,   0, tuileMenu, src);
		renderer.applyTexture(  0, 184, tuileMenu, src);
		renderer.applyTexture(312, 184, tuileMenu, src);

		//Les lignes verticales
		src.x = 8; src.y = 0;
		for (y=8; y < 184; y += 8) {
			renderer.applyTexture(0  , y, tuileMenu, src);
			renderer.applyTexture(312, y, tuileMenu, src);
		}

		//Les lignes horizontales
		src.x = 16; src.y = 0;
		for (x=8; x < 312; x += 8) {
			renderer.applyTexture(x,   0, tuileMenu, src);
			renderer.applyTexture(x, 184, tuileMenu, src);
		}
	}
}

void EcranUtil::dessinerCadreEtPortrait(Renderer &renderer)
{
	int x,y;
	SDL_Rect src;

	dessinerCadre(renderer);

	src.w = 8; src.h = 8;

	//Les 3 coins supplémentaires
	src.x = 0; src.y = 0;
	renderer.applyTexture(216,  0, tuileMenu, src);
	renderer.applyTexture(216, 96, tuileMenu, src);
	renderer.applyTexture(312, 96, tuileMenu, src);

	//La ligne verticale
	src.x = 8; src.y = 0;
	for (y=8; y < 96; y += 8)
		renderer.applyTexture(216, y, tuileMenu, src);

	//La ligne horizontale
	src.x = 16; src.y = 0;
	for (x=224; x < 312; x += 8)
		renderer.applyTexture(x, 96, tuileMenu, src);
}

EcranUtil::~EcranUtil()
{
	cleanup(tuileMenu);
}
