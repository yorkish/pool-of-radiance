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

		bool onEnter();
		bool chargerImage();
		void update( TInfoTouches& keysInfo );
        void render();
        void checkMessages();
        bool onExit();

        bool finished();

    	virtual std::string getStateID() const {
    		return "INTRO_STATE";
    	}

		virtual ~EtatIntro();

	private:

		enum IntroSequence { LOADING, SSI, POOL, CREDITS };
		IntroSequence sequence;

		std::unique_ptr<ListeTexte> loading;
		Timer      oTimer;

		SDL_Texture* imagesIntro;
};
