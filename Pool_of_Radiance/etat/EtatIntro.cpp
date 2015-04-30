#include "EtatIntro.h"
#include "../queue/Message.h"

EtatIntro::EtatIntro() : sequence(LOADING), oAffichage(Affichage::getInstance()), imagesIntro(0)
{}

bool EtatIntro::init()
{
	return ( oLoading.init() && chargerImage() );
}

bool EtatIntro::chargerImage()
{
	switch (sequence) {
	case LOADING:
		imagesIntro = 0;
		oLoading.addTexte(0, 0, 24, cVERT_CLAIR);
		oTimer.start();
		break;

	case SSI:
	case POOL:
	case CREDITS:
		imagesIntro = oAffichage.loadImageAsSurface("data/images/TITLE_DAX.png", 0, 0, 255);
		break;
	}

	if (imagesIntro != 0 || sequence == LOADING)
		return true;
	else
		return false;
}

void EtatIntro::handleEvent( TInfoTouches& infTouches )
{
	if (infTouches.bEnter)
		switch (sequence) {
		case LOADING:
			break;

		case SSI:
			sequence = POOL;
			chargerImage();
			break;

		case POOL:
			sequence = CREDITS;
			chargerImage();
			break;

		case CREDITS:
			oPileMessage.pushMessage( Message(OBJ_ETAT_INTRO, OBJ_JEU, GM_INTRO_FINI) );
			break;

		}
}

void EtatIntro::draw()
{
	SDL_Rect src;
	SDL_Rect dst;

	dst.x = 0; dst.y = 0;
	src.x = 0; src.y = 0;
	src.w = 320; src.h = 200;

	switch(sequence) {
	case LOADING:
		oLoading.draw();

		if (oTimer.get_ticks() >= LOADING_TIME) {
			sequence = SSI;
			oTimer.stop();
			chargerImage();
		}
		break;

	case SSI:
		src.x = 0; src.y = 0;
		oAffichage.applySurface(dst.x, dst.y, imagesIntro, src);
		break;

	case POOL:
		src.x = 320; src.y = 0;
		oAffichage.applySurface(dst.x, dst.y, imagesIntro, src);
		break;

	case CREDITS:
		src.x = 640; src.y = 0;
		oAffichage.applySurface(dst.x, dst.y, imagesIntro, src);
		break;
	}
}

void EtatIntro::verifierMessages() {}

void EtatIntro::release()
{
	if (imagesIntro != 0)
		SDL_FreeSurface(imagesIntro);
}

EtatIntro::~EtatIntro()
{}
