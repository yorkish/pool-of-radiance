#pragma once

#include "Ecran.h"
#include "EcranUtil.h"
#include "../texte/ListeTexte.h"

class EcranCharacterIcon: public Ecran, public EcranUtil
{
	public:
		EcranCharacterIcon(Renderer &renderer);

		bool init();
		void handleEvent( TInfoTouches& infTouches );
		void draw();
		void verifierMessages();
		void release();

		~EcranCharacterIcon();

	private:
		void updateScreen();
		void setStartingColors();
		void traiterTouchesChangementCouleurs();

		enum StatusEcran { MAIN,
						   PARTS,   CHOOSE_HEAD,    CHOOSE_WEAPON,

						   COLOR_1, WEAPON_COLOR_1, BODY_COLOR_1,  HAIR_COLOR,
						            SHIELD_COLOR_1, ARM_COLOR_1,   LEG_COLOR_1,

						   COLOR_2, WEAPON_COLOR_2, BODY_COLOR_2,  FACE_COLOR,
						            SHIELD_COLOR_2, ARM_COLOR_2,   LEG_COLOR_2,
						   SIZE,
						   EXITING };

		CharacterInfo character;

		StatusEcran statusEcran;
		Couleur couleurOriginale;
};

