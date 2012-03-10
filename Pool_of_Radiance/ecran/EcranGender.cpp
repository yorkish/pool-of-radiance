#include "EcranGender.h"
#include "EcranUtil.h"
#include "../queue/Message.h"
#include "../common/Donnees.h"

using std::vector;

EcranGender::EcranGender(): posCourante(0)
{
	vctGender = Donnees::getInstance().getGenders();
	MAX_POS = vctGender.size();
}

bool EcranGender::init()
{
	if (oListeTexte.init()) {
		updateScreen();
		return true;
	} else
		return false;
}

void EcranGender::handleEvent( TInfoTouches& infTouches )
{
	switch (infTouches.caractere) {
	case SDLK_e:
		oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_GENDER, OBJ_ETAT_MENU, GM_REVENIR_MENU_PRINCIPAL) );
		oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_GENDER, OBJ_JEU, GM_ANNULER_PERSONNAGE) );
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
		oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_GENDER, OBJ_ETAT_MENU, GM_MENU_CLASSE) );
		oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_GENDER, OBJ_PERSONNAGE_EN_CREATION, GM_GENDER_CHOISI, &vctGender[posCourante]) );
	}
}

void EcranGender::draw()
{
	if (!oListeTexte.isEmpty()) {
		dessinerCadre();

		//Le texte
		oListeTexte.draw();
	}
}

void EcranGender::updateScreen()
{
	oListeTexte.reset();
	oListeTexte.addTexte("pick gender", 1, 2, cMAGENTA_CLAIR);

	for (int i=0, ligne=3; i < MAX_POS; i++, ligne++) {
		if (posCourante == i)
			oListeTexte.addTexte(vctGender[i].nom, 3, ligne, cBLANC);
		else
			oListeTexte.addTexte(vctGender[i].nom, 3, ligne, cVERT_CLAIR);
	}

	oListeTexte.addTexte("exit", 1, 24, cVERT_CLAIR, cBLANC);
}

void EcranGender::verifierMessages() {}

void EcranGender::release()
{
	oListeTexte.reset();
}

EcranGender::~EcranGender()
{
	vctGender.clear();
}
