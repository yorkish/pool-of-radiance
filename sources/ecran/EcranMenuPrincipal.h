#pragma once
#include <vector>

#include "../common/Renderer.h"
#include "Ecran.h"
#include "../texte/ListeTexte.h"
#include "EcranUtil.h"

class EcranMenuPrincipal: public Ecran, public EcranUtil
{
	public:
		EcranMenuPrincipal(Renderer &renderer);

		bool init();
		bool chargerImage();
		void handleEvent( TInfoTouches& infTouches );
        void draw();
        void verifierMessages();
        void release();

		~EcranMenuPrincipal();

	private:
		void switchPosition();
		void ajouterLettresSauvegardes();

		enum PositionMenuPrincipal { MAIN_MENU, LOAD, EXIT, EXITING};
		PositionMenuPrincipal posMenu;

		std::vector<char> lstSauvegarde;
};

