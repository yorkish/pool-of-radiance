#include "EcranAlignment.h"
#include "EcranUtil.h"
#include "../queue/Message.h"
#include "../common/Donnees.h"

using std::vector;

EcranAlignment::EcranAlignment(Renderer &renderer): Ecran(renderer), posCourante(0)
{
	vctAlignment = Donnees::getInstance().getAlignments();
	MAX_POS = vctAlignment.size();
}

bool EcranAlignment::init()
{
	if (oListeTexte->init()) {
		updateScreen();
		return true;
	} else
		return false;
}

void EcranAlignment::handleEvent( TInfoTouches& infTouches )
{
	switch (infTouches.caractere) {
	case SDLK_e:
		oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_CLASSE, OBJ_ETAT_MENU, GM_REVENIR_MENU_PRINCIPAL) );
		oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_CLASSE, OBJ_JEU, GM_ANNULER_PERSONNAGE) );
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
		oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_CLASSE, OBJ_ETAT_MENU, GM_MENU_CHARACTER) );
		oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_CLASSE, OBJ_PERSONNAGE_EN_CREATION, GM_ALIGNMENT_CHOISI, &vctAlignment[posCourante]) );
	}
}

void EcranAlignment::draw()
{
	if (!oListeTexte->isEmpty()) {
		dessinerCadre(renderer);

		//Le texte
		oListeTexte->draw();
	}
}

void EcranAlignment::updateScreen()
{
	oListeTexte.reset();
	oListeTexte->addTexte("pick alignment", 1, 2, Couleur::brightMagenta);

	for (int i=0, ligne=3; i < MAX_POS; i++, ligne++) {
		if (posCourante == i)
			oListeTexte->addTexte(vctAlignment[i].nom, 3, ligne, Couleur::white);
		else
			oListeTexte->addTexte(vctAlignment[i].nom, 3, ligne, Couleur::brightGreen);
	}

	oListeTexte->addTexte("exit", 1, 24, Couleur::brightGreen, Couleur::white);
}

void EcranAlignment::verifierMessages() {}

void EcranAlignment::release()
{
	oListeTexte->reset();
}

EcranAlignment::~EcranAlignment()
{
	vctAlignment.clear();
}
