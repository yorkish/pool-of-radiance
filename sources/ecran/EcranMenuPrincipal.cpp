#include "EcranMenuPrincipal.h"
#include "EcranUtil.h"
#include "../queue/Message.h"
#include <iostream>

using namespace std;

EcranMenuPrincipal::EcranMenuPrincipal(Renderer &renderer): Ecran(renderer), posMenu(MAIN_MENU)
{}

bool EcranMenuPrincipal::init() {
	if (oListeTexte->init()) {
		switchPosition();
		return true;
	} else
		return false;
}

void EcranMenuPrincipal::handleEvent( TInfoTouches& infTouches )
{
	if (posMenu == EXIT)
		switch (infTouches.caractere) {
		case SDLK_y:
			oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_PRINCIPAL, OBJ_JEU, GM_QUITTER) );
			posMenu = EXITING;
			break;

		case SDLK_n:
			posMenu = MAIN_MENU;
			break;

		default: break;
		}

	else if (posMenu == LOAD) {
		vector<char>::iterator iter = lstSauvegarde.begin();
		while (iter != lstSauvegarde.end()) {
			if (*iter == infTouches.caractere) {
				oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_PRINCIPAL, OBJ_SAVE_GAME_MANAGER, GM_CHARGER_PARTIE, &infTouches.caractere) );
			}
			iter++;
		}
		posMenu = MAIN_MENU;

	} else
		switch (infTouches.caractere) {
		case SDLK_c:
			if (posMenu == MAIN_MENU){
				oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_PRINCIPAL, OBJ_ETAT_MENU, GM_MENU_RACE) );
				oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_PRINCIPAL, OBJ_JEU, GM_NOUVEAU_PERSONNAGE) );
				posMenu = EXITING;
			}
			break;

		case SDLK_a:
			if (posMenu == MAIN_MENU)
				posMenu = EXIT;
			break;

		case SDLK_l:
			if (posMenu == MAIN_MENU) {
				oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_PRINCIPAL, OBJ_SAVE_GAME_MANAGER, GM_OBTENIR_LISTE_SAUVEGARDE) );
				posMenu = LOAD;
			}
			break;

		case SDLK_e:
			if (posMenu == MAIN_MENU)
				posMenu = EXIT;
			break;

		default: break;
		}

	if (posMenu != EXITING)
		switchPosition();
}

void EcranMenuPrincipal::draw()
{
	if (!oListeTexte->isEmpty()) {
		dessinerCadre(renderer);

		//Le texte
		oListeTexte->draw();
	}
}

void EcranMenuPrincipal::switchPosition()
{
	oListeTexte->reset();
	oListeTexte->addTexte("create new character"  , 2, 12, Couleur::brightGreen, Couleur::white);
	oListeTexte->addTexte("add character to party", 2, 13, Couleur::brightGreen, Couleur::white);
	oListeTexte->addTexte("load saved game"       , 2, 14, Couleur::brightGreen, Couleur::white);
	oListeTexte->addTexte("exit to os"            , 2, 15, Couleur::brightGreen, Couleur::white);

	switch (posMenu) {
	case MAIN_MENU:
		oListeTexte->addTexte("choose a function", 0, 24, Couleur::brightMagenta );
		break;

	case LOAD:
		//On attends de recevoir les lettres de sauvegardes
		break;

	case EXIT:
		oListeTexte->addTexte("quit to os", 0 , 24, Couleur::yellow);
		oListeTexte->addTexte("yes"       , 11, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("no"        , 15, 24, Couleur::brightGreen, Couleur::white);
		break;

	default:
		break;
	}
}

void EcranMenuPrincipal::ajouterLettresSauvegardes()
{
	int x = 17;

	if (lstSauvegarde.size() != 0) {
		oListeTexte->addTexte("load which game: ",  0, 24, Couleur::brightMagenta );

		vector<char>::iterator iter = lstSauvegarde.begin();
		while (iter != lstSauvegarde.end()) {
			oListeTexte->addTexte( string(1, *iter), x, 24, Couleur::white   );
			x += 2;
			iter++;
		}
	}
}

void EcranMenuPrincipal::verifierMessages()
{
	vector<char>* temp;
	Message unMessage = oPileMessage.getMessageCourant();

	if (unMessage.getDestinataire() == OBJ_ECRAN_MENU_PRINCIPAL) {
		switch (unMessage.getTypeMessage()) {
		case GM_LISTE_SAUVEGARDE:
			temp = static_cast<vector<char>*> (unMessage.getContenu());
			lstSauvegarde = *temp;
			ajouterLettresSauvegardes();
			delete temp;
			_gblMemory.push_back(InfoAlloc('D',__FILE__, __LINE__));
			break;

		default: break;
		}

		oPileMessage.popMessage();
	}
}

void EcranMenuPrincipal::release()
{
	oListeTexte->reset();
}

EcranMenuPrincipal::~EcranMenuPrincipal() {}
