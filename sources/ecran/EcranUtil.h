#pragma once
#include "../common/Global.h"
#include "../common/Affichage.h"

class EcranUtil {
	public:
		EcranUtil();
		void dessinerCadre(Couleur couleurFond = cNOIR);
		void dessinerCadreEtPortrait();

		~EcranUtil();

	private:
		bool init();

		Affichage&  oAffichage;
		SDL_Surface* tuileMenu;
};
