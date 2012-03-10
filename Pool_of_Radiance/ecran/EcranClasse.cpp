#include "EcranClasse.h"
#include "EcranUtil.h"
#include "../queue/Message.h"
#include "../common/Donnees.h"

using std::vector;

EcranClasse::EcranClasse(): posCourante(0)
{
	oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_RACE, OBJ_PERSONNAGE_EN_CREATION, GM_OBTENIR_CLASSES_PERMISES) );
}

bool EcranClasse::init()
{
	if (oListeTexte.init())
		return true;
	else
		return false;
}

void EcranClasse::handleEvent( TInfoTouches& infTouches )
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
		oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_CLASSE, OBJ_ETAT_MENU, GM_MENU_ALIGNMENT) );
		oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_CLASSE, OBJ_PERSONNAGE_EN_CREATION, GM_CLASSE_CHOISIE, &vctClasse[posCourante]) );
	}
}

void EcranClasse::draw()
{
	if (!oListeTexte.isEmpty()) {
		dessinerCadre();

		//Le texte
		oListeTexte.draw();
	}
}

void EcranClasse::verifierMessages()
{
	vector<NodeClasse>* temp;
	Message unMessage = oPileMessage.getMessageCourant();

	if (unMessage.getDestinataire() == OBJ_ECRAN_MENU_CLASSE) {
		switch (unMessage.getTypeMessage()) {
		case GM_LISTE_CLASSES_PERMISES:
			temp = static_cast<vector<NodeClasse>*> (unMessage.getContenu());
			vctClasse = *temp;
			MAX_POS = vctClasse.size();
			delete temp;
			gbl_Memoire.push_back(InfoAlloc('D',__FILE__, __LINE__));

			updateScreen();
			break;

		default: break;
		}

		oPileMessage.popMessage();
	}
}

void EcranClasse::updateScreen()
{
	oListeTexte.reset();
	oListeTexte.addTexte("pick class", 1, 2, cMAGENTA_CLAIR);

	for (int i=0, ligne=3; i < MAX_POS; i++, ligne++) {
		if (posCourante == i)
			oListeTexte.addTexte(vctClasse[i].nom, 3, ligne, cBLANC);
		else
			oListeTexte.addTexte(vctClasse[i].nom, 3, ligne, cVERT_CLAIR);
	}

	oListeTexte.addTexte("exit", 1, 24, cVERT_CLAIR, cBLANC);
}

void EcranClasse::release()
{
	oListeTexte.reset();
}

EcranClasse::~EcranClasse()
{
	vctClasse.clear();
}
