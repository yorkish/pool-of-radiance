#include <iostream>
#include "Jeu.h"
#include "etat/EtatIntro.h"
#include "etat/EtatMenu.h"
#include "queue/Message.h"
#include "common/Donnees.h"

using std::cout;

Jeu::Jeu(): typeEtat(GAME_STATE_UNDEFINED), oPileMessage(PileMessage::getInstance())
{}

bool Jeu::init()
{
	pushEtat( new EtatIntro() );
	gbl_Memoire.push_back(InfoAlloc('N',__FILE__, __LINE__));
	typeEtat = INTRO;

	return true;
}

void Jeu::handleEvent( TInfoTouches& infoTouches )
{
	getEtatCourant()->handleEvent(infoTouches);
}

void Jeu::move() {}

void Jeu::draw()
{
	getEtatCourant()->draw();
}

void Jeu::verifierMessages() {
	Message unMessage = oPileMessage.getMessageCourant();

	if (unMessage.getDestinataire() == OBJ_JEU) {
		switch (unMessage.getTypeMessage()) {
		case GM_INTRO_FINI:
			popPushEtat( new EtatMenu() );
			gbl_Memoire.push_back(InfoAlloc('N',__FILE__, __LINE__));
			typeEtat = MENU;
			break;

		case GM_NOUVEAU_PERSONNAGE:
			lstCharacter.push_back( new Character() );
			gbl_Memoire.push_back(InfoAlloc('N',__FILE__, __LINE__));
			break;

		case GM_ANNULER_PERSONNAGE:
			delete lstCharacter.back();
			gbl_Memoire.push_back(InfoAlloc('D',__FILE__, __LINE__));
			lstCharacter.pop_back();
			break;

		case GM_QUITTER:
			typeEtat = EXIT_REQUESTED;
			break;

		default: break;
		}
		oPileMessage.popMessage();
	}

	if (lstCharacter.size() != 0)
		lstCharacter.back()->verifierMessages();

	getEtatCourant()->verifierMessages();
	saveGameManager.verifierMessages();
}

bool Jeu::exitRequested()
{
	return (typeEtat == EXIT_REQUESTED);
}

EtatJeu* Jeu::getEtatCourant()
{
	if (!Etats.empty())
		return Etats.top();
	else
		return 0;
}

void Jeu::pushEtat( EtatJeu* etat )
{
    // set current state
	Etats.push( etat );
	Etats.top()->init();
}

void Jeu::popEtat()
{
    if ( Etats.empty() )
    	return;

    Etats.top()->release();

    delete Etats.top();
	gbl_Memoire.push_back(InfoAlloc('D',__FILE__, __LINE__));

    Etats.pop();
}

void Jeu::popPushEtat( EtatJeu* etat )
{
    // set current state
	popEtat();
	pushEtat(etat);
}

Jeu::~Jeu()
{
	while(getEtatCourant() != 0)
		popEtat();
}
