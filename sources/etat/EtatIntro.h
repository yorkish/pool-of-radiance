#pragma once

#include "EtatJeu.h"
#include "../common/Affichage.h"
#include "../texte/ListeTexte.h"
#include "../common/Timer.h"

class EtatIntro : public EtatJeu
{
	public:
		EtatIntro();

		bool init();
		bool chargerImage();
		void handleEvent( TInfoTouches& infTouches );
        void draw();
        void verifierMessages();
        void release();

        bool finished();

		virtual ~EtatIntro();

	private:

		enum IntroSequence { LOADING, SSI, POOL, CREDITS };
		IntroSequence sequence;

		Affichage& oAffichage;
		ListeTexte oLoading;
		Timer      oTimer;

		SDL_Surface* imagesIntro;
};
