#include "EcranCharacterIcon.h"

EcranCharacterIcon::EcranCharacterIcon(Renderer &renderer): Ecran(renderer), statusEcran(MAIN), couleurOriginale(Couleur::white)
{}

bool EcranCharacterIcon::init()
{
	if (oListeTexte->init()) {

		oPileMessage.pushMessage( Message(OBJ_ECRAN_CHARACTER_ICON, OBJ_PERSONNAGE_EN_CREATION, GM_INFO_CHARACTER) );
		return true;
	} else
		return false;
}

void EcranCharacterIcon::handleEvent( TInfoTouches& infTouches )
{
	switch (statusEcran) {

	case MAIN:
		switch (infTouches.caractere) {
		case SDLK_p: statusEcran = PARTS  ; break;
		case SDLK_1: statusEcran = COLOR_1; break;
		case SDLK_2: statusEcran = COLOR_2; break;
		case SDLK_s: statusEcran = SIZE   ; break;

		case SDLK_e:
			oPileMessage.pushMessage( Message(OBJ_ECRAN_CHARACTER_ICON, OBJ_ETAT_MENU, GM_REVENIR_MENU_PRINCIPAL) );
			oPileMessage.pushMessage( Message(OBJ_ECRAN_CHARACTER_ICON, OBJ_JEU, GM_ANNULER_PERSONNAGE) );
			break;

		default: break;
		}
		break;


	// Menu PARTS DÉBUT
	case PARTS:
		switch (infTouches.caractere) {
		case SDLK_h: statusEcran = CHOOSE_HEAD  ; break;
		case SDLK_w: statusEcran = CHOOSE_WEAPON; break;
		case SDLK_e: statusEcran = MAIN; break;
		default    : break;
		}
		break;

	case CHOOSE_HEAD:
		switch (infTouches.caractere) {
		case SDLK_n: break;
		case SDLK_p: break;
		case SDLK_k: statusEcran = PARTS; break;
		case SDLK_e: statusEcran = PARTS; break;
		default    : break;
		}
		break;

	case CHOOSE_WEAPON:
		switch (infTouches.caractere) {
		case SDLK_n: break;
		case SDLK_p: break;
		case SDLK_k: statusEcran = PARTS ; break;
		case SDLK_e: statusEcran = PARTS ; break;
		default    : break;
		}
		break;
	// Menu PARTS FIN


	// Menu COLOR_1 DÉBUT
	case COLOR_1:
		switch (infTouches.caractere) {
		case SDLK_w: statusEcran = WEAPON_COLOR_1; couleurOriginale = character.icon.weapon1; break;
		case SDLK_b: statusEcran = BODY_COLOR_1  ; couleurOriginale = character.icon.body1  ; break;
		case SDLK_h: statusEcran = HAIR_COLOR    ; couleurOriginale = character.icon.hair   ; break;
		case SDLK_s: statusEcran = SHIELD_COLOR_1; couleurOriginale = character.icon.shield1; break;
		case SDLK_a: statusEcran = ARM_COLOR_1   ; couleurOriginale = character.icon.arm1   ; break;
		case SDLK_l: statusEcran = LEG_COLOR_1   ; couleurOriginale = character.icon.leg1   ; break;
		case SDLK_e: statusEcran = MAIN          ; break;
		default    : break;
		}
		break;

	case WEAPON_COLOR_1:
		switch (infTouches.caractere) {
//		case SDLK_n: character.icon.weapon1++; break;
//		case SDLK_p: character.icon.weapon1--; break;
		case SDLK_k: statusEcran = COLOR_1   ; break;
		case SDLK_e: statusEcran = COLOR_1   ; character.icon.weapon1 = couleurOriginale; break;
		default    : break;
		}
		break;

	case BODY_COLOR_1:
		switch (infTouches.caractere) {
//		case SDLK_n: character.icon.body1++; break;
//		case SDLK_p: character.icon.body1--; break;
		case SDLK_k: statusEcran = COLOR_1 ; break;
		case SDLK_e: statusEcran = COLOR_1 ; character.icon.body1 = couleurOriginale; break;
		default    : break;
		}
		break;

	case HAIR_COLOR:
		switch (infTouches.caractere) {
//		case SDLK_n: character.icon.hair++; break;
//		case SDLK_p: character.icon.hair--; break;
		case SDLK_k: statusEcran = COLOR_1; break;
		case SDLK_e: statusEcran = COLOR_1; character.icon.hair = couleurOriginale; break;
		default    : break;
		}
		break;

	case SHIELD_COLOR_1:
		switch (infTouches.caractere) {
//		case SDLK_n: character.icon.shield1++; break;
//		case SDLK_p: character.icon.shield1--; break;
		case SDLK_k: statusEcran = COLOR_1   ; break;
		case SDLK_e: statusEcran = COLOR_1   ; character.icon.shield1 = couleurOriginale; break;
		default    : break;
		}
		break;

	case ARM_COLOR_1:
		switch (infTouches.caractere) {
//		case SDLK_n: character.icon.arm1++; break;
//		case SDLK_p: character.icon.arm1--; break;
		case SDLK_k: statusEcran = COLOR_1; break;
		case SDLK_e: statusEcran = COLOR_1; character.icon.arm1 = couleurOriginale; break;
		default    : break;
		}
		break;

	case LEG_COLOR_1:
		switch (infTouches.caractere) {
//		case SDLK_n: character.icon.leg1++; break;
//		case SDLK_p: character.icon.leg1--; break;
		case SDLK_k: statusEcran = COLOR_1; break;
		case SDLK_e: statusEcran = COLOR_1; character.icon.leg1 = couleurOriginale; break;
		default    : break;
		}
		break;
	// Menu COLOR_1 FIN


	// Menu COLOR_2 DÉBUT
	case COLOR_2:
		switch (infTouches.caractere) {
		case SDLK_w: statusEcran = WEAPON_COLOR_2; couleurOriginale = character.icon.weapon2; break;
		case SDLK_b: statusEcran = BODY_COLOR_2  ; couleurOriginale = character.icon.body2  ; break;
		case SDLK_f: statusEcran = FACE_COLOR    ; couleurOriginale = character.icon.face   ; break;
		case SDLK_s: statusEcran = SHIELD_COLOR_2; couleurOriginale = character.icon.shield2; break;
		case SDLK_a: statusEcran = ARM_COLOR_2   ; couleurOriginale = character.icon.arm2   ; break;
		case SDLK_l: statusEcran = LEG_COLOR_2   ; couleurOriginale = character.icon.leg2   ; break;
		case SDLK_e: statusEcran = MAIN          ; break;
		default    : break;
		}
		break;

	case WEAPON_COLOR_2:
		switch (infTouches.caractere) {
		case SDLK_n: break;
		case SDLK_p: break;
		case SDLK_k: statusEcran = COLOR_2       ; break;
		case SDLK_e: statusEcran = COLOR_2       ; break;
		default    : break;
		}
		break;

	case BODY_COLOR_2:
		switch (infTouches.caractere) {
		case SDLK_n: break;
		case SDLK_p: break;
		case SDLK_k: statusEcran = COLOR_2       ; break;
		case SDLK_e: statusEcran = COLOR_2       ; break;
		default    : break;
		}
		break;

	case FACE_COLOR:
		switch (infTouches.caractere) {
		case SDLK_n: break;
		case SDLK_p: break;
		case SDLK_k: statusEcran = COLOR_2       ; break;
		case SDLK_e: statusEcran = COLOR_2       ; break;
		default    : break;
		}
		break;

	case SHIELD_COLOR_2:
		switch (infTouches.caractere) {
		case SDLK_n: break;
		case SDLK_p: break;
		case SDLK_k: statusEcran = COLOR_2       ; break;
		case SDLK_e: statusEcran = COLOR_2       ; break;
		default    : break;
		}
	break;

	case ARM_COLOR_2:
		switch (infTouches.caractere) {
		case SDLK_n: break;
		case SDLK_p: break;
		case SDLK_k: statusEcran = COLOR_2       ; break;
		case SDLK_e: statusEcran = COLOR_2       ; break;
		default    : break;
		}
		break;

	case LEG_COLOR_2:
		switch (infTouches.caractere) {
		case SDLK_n: break;
		case SDLK_p: break;
		case SDLK_k: statusEcran = COLOR_2       ; break;
		case SDLK_e: statusEcran = COLOR_2       ; break;
		default    : break;
		}
		break;
		// Menu COLOR_2 FIN


	case SIZE:
		switch (infTouches.caractere) {
		case SDLK_l:
			if (character.icon.size == SIZE_SMALL)
				character.icon.size = SIZE_LARGE;
			break;

		case SDLK_s:
			if (character.icon.size == SIZE_LARGE)
				character.icon.size = SIZE_SMALL;
			break;

		case SDLK_k: statusEcran = MAIN; break;
		case SDLK_e: statusEcran = MAIN; break;
		default    : break;
		}
		break;

	case EXITING:
		break;

	}

	if (statusEcran != EXITING)
		updateScreen();
}

void EcranCharacterIcon::draw()
{
	if (!oListeTexte->isEmpty()) {
		dessinerCadre(renderer, Couleur::darkGray);

		// Le texte
		oListeTexte->draw();
	}
}

void EcranCharacterIcon::updateScreen()
{
	oListeTexte->reset();

	oListeTexte->addTexte("old"           , 8, 6 , Couleur::white);
	oListeTexte->addTexte("ready   action", 3, 10, Couleur::white);
	oListeTexte->addTexte("new"           , 8, 12, Couleur::white);
	oListeTexte->addTexte("ready   action", 3, 16, Couleur::white);

	switch (statusEcran) {
	case MAIN:
		oListeTexte->addTexte("parts"  , 0 , 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("color-1", 6 , 24, Couleur::brightGreen, Couleur::sameColor, Couleur::white);
		oListeTexte->addTexte("color-2", 14, 24, Couleur::brightGreen, Couleur::sameColor, Couleur::white);
		oListeTexte->addTexte("size"   , 22, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("exit"   , 27, 24, Couleur::brightGreen, Couleur::white);
		break;

	case PARTS:
		oListeTexte->addTexte("head"  ,  0, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("weapon",  5, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("exit"  , 12, 24, Couleur::brightGreen, Couleur::white);
		break;

	case COLOR_1:
		oListeTexte->addTexte("weapon",  0, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("body"  ,  7, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("hair"  , 12, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("shield", 17, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("arm"   , 24, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("leg"   , 28, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("exit"  , 32, 24, Couleur::brightGreen, Couleur::white);
		break;

	case COLOR_2:
		oListeTexte->addTexte("weapon",  0, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("body"  ,  7, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("face"  , 12, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("shield", 17, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("arm"   , 24, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("leg"   , 28, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("exit"  , 32, 24, Couleur::brightGreen, Couleur::white);
		break;

	case CHOOSE_HEAD   :
	case CHOOSE_WEAPON :
	case WEAPON_COLOR_1:
	case BODY_COLOR_1  :
	case HAIR_COLOR    :
	case SHIELD_COLOR_1:
	case ARM_COLOR_1   :
	case LEG_COLOR_1   :
	case WEAPON_COLOR_2:
	case BODY_COLOR_2  :
	case FACE_COLOR    :
	case SHIELD_COLOR_2:
	case ARM_COLOR_2   :
	case LEG_COLOR_2   :
		oListeTexte->addTexte("next"    ,  0, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("previous",  5, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("keep"    , 14, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("exit"    , 19, 24, Couleur::brightGreen, Couleur::white);
		break;

	case SIZE:
		if (character.icon.size == SIZE_SMALL)
			oListeTexte->addTexte("large",  0, 24, Couleur::brightGreen, Couleur::white);
		else
			oListeTexte->addTexte("small",  0, 24, Couleur::brightGreen, Couleur::white);

		oListeTexte->addTexte("keep" ,  6, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("exit" , 11, 24, Couleur::brightGreen, Couleur::white);
		break;

	case EXITING:
		break;
	}
}

void EcranCharacterIcon::verifierMessages()
{
	Message unMessage = oPileMessage.getMessageCourant();

	if (unMessage.getDestinataire() == OBJ_ECRAN_CHARACTER_ICON) {
		switch (unMessage.getTypeMessage()) {

		case GM_INFO_CHARACTER:
			character = *((CharacterInfo*) unMessage.getContenu());
			oPileMessage.popMessage();
			setStartingColors();
			updateScreen();
			break;

		default: break;
		}
	}
}

void EcranCharacterIcon::setStartingColors()
{
	character.icon.weapon1 = Couleur::lightGray;
	character.icon.body1   = Couleur::blue;
	character.icon.hair    = Couleur::red;
	character.icon.shield1 = Couleur::brown;
	character.icon.arm1    = Couleur::green;
	character.icon.leg1    = Couleur::cyan;

	character.icon.weapon2 = Couleur::white;
	character.icon.body2   = Couleur::brightBlue;
	character.icon.face    = Couleur::lightRed;
	character.icon.shield2 = Couleur::yellow;
	character.icon.arm2    = Couleur::brightGreen;
	character.icon.leg2    = Couleur::brightCyan;
}

void EcranCharacterIcon::release()
{
	oListeTexte->reset();
}

EcranCharacterIcon::~EcranCharacterIcon() {}
