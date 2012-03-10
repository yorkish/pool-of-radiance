#include "EtatMenu.h"
#include "../ecran/EcranMenuPrincipal.h"
#include "../ecran/EcranRace.h"
#include "../ecran/EcranGender.h"
#include "../ecran/EcranClasse.h"
#include "../ecran/EcranAlignment.h"
#include "../ecran/EcranCharacter.h"
#include "../ecran/EcranCharacterIcon.h"
#include "../queue/Message.h"

EtatMenu::EtatMenu() {}

bool EtatMenu::init()
{
	popPushMenu( new EcranMenuPrincipal() );
	gbl_Memoire.push_back(InfoAlloc('N',__FILE__, __LINE__));
	return true;
}

void EtatMenu::handleEvent( TInfoTouches& infoTouches )
{
	getMenuCourant()->handleEvent(infoTouches);
}

void EtatMenu::draw()
{
	getMenuCourant()->draw();
}

void EtatMenu::verifierMessages()
{
	Message unMessage = oPileMessage.getMessageCourant();
	TypeMessage typeMessage;

	if (unMessage.getDestinataire() == OBJ_ETAT_MENU) {
		typeMessage = unMessage.getTypeMessage();
		oPileMessage.popMessage();

		switch (typeMessage) {

		case GM_MENU_RACE:
			popPushMenu( new EcranRace() );
			gbl_Memoire.push_back(InfoAlloc('N',__FILE__, __LINE__));
			break;

		case GM_MENU_GENDER:
			popPushMenu( new EcranGender() );
			gbl_Memoire.push_back(InfoAlloc('N',__FILE__, __LINE__));
			break;

		case GM_MENU_CLASSE:
			popPushMenu( new EcranClasse() );
			gbl_Memoire.push_back(InfoAlloc('N',__FILE__, __LINE__));
			break;

		case GM_MENU_ALIGNMENT:
			popPushMenu( new EcranAlignment() );
			gbl_Memoire.push_back(InfoAlloc('N',__FILE__, __LINE__));
			break;

		case GM_MENU_CHARACTER:
			popPushMenu( new EcranCharacter() );
			gbl_Memoire.push_back(InfoAlloc('N',__FILE__, __LINE__));
			break;

		case GM_MENU_CHARACTER_ICON:
			popPushMenu( new EcranCharacterIcon() );
			gbl_Memoire.push_back(InfoAlloc('N',__FILE__, __LINE__));
			break;

		case GM_REVENIR_MENU_PRINCIPAL:
			popPushMenu( new EcranMenuPrincipal() );
			gbl_Memoire.push_back(InfoAlloc('N',__FILE__, __LINE__));
			break;

		default: break;
		}
	}

	getMenuCourant()->verifierMessages();
}

void EtatMenu::release()
{
	while ( getMenuCourant() != 0)
		popMenu();
}

Ecran* EtatMenu::getMenuCourant()
{
	if (!Ecrans.empty())
		return Ecrans.top();
	else
		return 0;
}

void EtatMenu::pushMenu( Ecran* ecran )
{
    // set current state
	Ecrans.push( ecran );
	Ecrans.top()->init();
}

void EtatMenu::popMenu()
{
    if ( Ecrans.empty() )
    	return;

    Ecrans.top()->release();

    delete Ecrans.top();
	gbl_Memoire.push_back(InfoAlloc('D',__FILE__, __LINE__));

    Ecrans.pop();
}

void EtatMenu::popPushMenu( Ecran* ecran )
{
    // set current state
	popMenu();
	pushMenu(ecran);
}

EtatMenu::~EtatMenu()
{
	while(getMenuCourant() != 0)
		popMenu();
}
