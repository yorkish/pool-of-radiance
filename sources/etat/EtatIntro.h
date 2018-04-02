#pragma once
#include <memory>
#include "../common/Renderer.h"
#include "EtatJeu.h"
#include "../texte/ListeTexte.h"
#include "../common/Timer.h"

class EtatIntro : public EtatJeu
{
	public:
		EtatIntro(Renderer &renderer);

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

		std::unique_ptr<ListeTexte> loading;
		Timer      oTimer;

		SDL_Texture* imagesIntro;
};
