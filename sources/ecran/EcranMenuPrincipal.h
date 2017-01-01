#pragma once
#include <vector>
#include "Ecran.h"
#include "../common/Affichage.h"
#include "../texte/ListeTexte.h"
#include "EcranUtil.h"

class EcranMenuPrincipal: public Ecran, public EcranUtil
{
	public:
		EcranMenuPrincipal();

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

		ListeTexte oListeTexte;
		std::vector<char> lstSauvegarde;
};

