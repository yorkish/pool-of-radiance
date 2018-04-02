#include "EtatIntro.h"
#include "../queue/Message.h"

EtatIntro::EtatIntro(Renderer &renderer) : EtatJeu(renderer), sequence(LOADING), loading(std::make_unique<ListeTexte>(renderer)), imagesIntro(0)
{
}

bool EtatIntro::init()
{
	return ( loading->init() && chargerImage() );
}

bool EtatIntro::chargerImage()
{
	switch (sequence) {
	case LOADING:
		imagesIntro = 0;
		loading->addTexte(0, 0, 24, Couleur::brightGreen);
		oTimer.start();
		break;

	case SSI:
	case POOL:
	case CREDITS:
		imagesIntro = renderer.loadImage("assets/TITLE_DAX.png");
		break;
	}

	if (imagesIntro != 0 || sequence == LOADING)
		return true;
	else
		return false;
}

void EtatIntro::handleEvent( TInfoTouches& infTouches )
{
	if (infTouches.bEnter){
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
		loading->draw();

		if (oTimer.get_ticks() >= LOADING_TIME) {
			sequence = SSI;
			oTimer.stop();
			chargerImage();
		}
		break;

	case SSI:
		src.x = 0; src.y = 0;
		renderer.applyTexture(dst.x, dst.y, imagesIntro, src);
		break;

	case POOL:
		src.x = 320; src.y = 0;
		renderer.applyTexture(dst.x, dst.y, imagesIntro, src);
		break;

	case CREDITS:
		src.x = 640; src.y = 0;
		renderer.applyTexture(dst.x, dst.y, imagesIntro, src);
		break;
	}
}

void EtatIntro::verifierMessages() {}

void EtatIntro::release()
{
	loading->release();
	cleanup(imagesIntro);
}

EtatIntro::~EtatIntro()
{}
