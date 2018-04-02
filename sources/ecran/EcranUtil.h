#pragma once
#include "../common/Global.h"
#include "../common/Renderer.h"

class EcranUtil {
	public:
		EcranUtil();
		void dessinerCadre(Renderer &renderer, Couleur couleurFond = Couleur::black);
		void dessinerCadreEtPortrait(Renderer &renderer);

		~EcranUtil();

	private:
		bool init(Renderer &renderer);

		SDL_Texture* tuileMenu;
};
