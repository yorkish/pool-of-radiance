#pragma once
#include "Ecran.h"
#include "EcranUtil.h"
#include "../texte/ListeTexte.h"


class EcranCharacter: public Ecran, public EcranUtil {
	public:
		EcranCharacter(Renderer &renderer);

		bool init();
		void handleEvent( TInfoTouches& infTouches );
		void draw();
		void verifierMessages();
		void release();

		~EcranCharacter();

	private:
		void afficherPortrait();
		void updateScreen();
		void updateAbilities();
		void updateCoins();
		void updateLevels();
		void updateHP();
		void updateStatus();

		enum StatusEcran { GENERATION, CHOISIR_NOM, CHOISIR_PORTRAIT, EXITING};

		const int TETES_PAR_RANGEES;
		const int CORPS_PAR_RANGEES;

		CharacterInfo character;

		SDL_Texture* spritesTetes;
		SDL_Texture* spritesCorps;

		StatusEcran statusEcran;
};

