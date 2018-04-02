#include "EcranRace.h"
#include "EcranUtil.h"
#include "../queue/Message.h"
#include "../common/Donnees.h"

using std::vector;

EcranRace::EcranRace(Renderer &renderer): Ecran(renderer), posCourante(0)
{
	vctRace = Donnees::getInstance().getRaces();
	MAX_POS = vctRace.size();
}

bool EcranRace::init()
{
	if (oListeTexte->init()) {
		updateScreen();
		return true;
	} else
		return false;
}

void EcranRace::handleEvent( TInfoTouches& infTouches )
{
	switch (infTouches.caractere) {
	case SDLK_e:
		oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_RACE, OBJ_ETAT_MENU, GM_REVENIR_MENU_PRINCIPAL) );
		oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_RACE, OBJ_JEU, GM_ANNULER_PERSONNAGE) );
		break;

		default: break;
	}

	if (infTouches.bHaut) {
		posCourante = ((posCourante - 1) < 0)        ? MAX_POS-1 : posCourante-1;
		updateScreen();
	} else if (infTouches.bBas) {
		posCourante = ((posCourante + 1) == MAX_POS) ? 0         : posCourante+1;
		updateScreen();
	} else if (infTouches.bEnter) {
		oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_RACE, OBJ_ETAT_MENU, GM_MENU_GENDER) );
		oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_RACE, OBJ_PERSONNAGE_EN_CREATION, GM_RACE_CHOISIE, &vctRace[posCourante]) );
	}
}

void EcranRace::draw()
{
	if (!oListeTexte->isEmpty()) {
		dessinerCadre(renderer);

		//Le texte
		oListeTexte->draw();
	}
}

void EcranRace::updateScreen()
{
	oListeTexte->reset();
	oListeTexte->addTexte("pick race", 1, 2, Couleur::brightMagenta);

	for (int i=0, ligne=3; i < MAX_POS; i++, ligne++) {
		if (posCourante == i)
			oListeTexte->addTexte(vctRace[i].nom, 3, ligne, Couleur::white);
		else
			oListeTexte->addTexte(vctRace[i].nom, 3, ligne, Couleur::brightGreen);
	}

	oListeTexte->addTexte("exit", 1, 24, Couleur::brightGreen, Couleur::white);
}

void EcranRace::verifierMessages() {}

void EcranRace::release()
{
	oListeTexte->reset();
}

EcranRace::~EcranRace()
{
	vctRace.clear();
}
