#include "EtatMenu.h"
#include "../ecran/EcranMenuPrincipal.h"
#include "../ecran/EcranRace.h"
#include "../ecran/EcranGender.h"
#include "../ecran/EcranClasse.h"
#include "../ecran/EcranAlignment.h"
#include "../ecran/EcranCharacter.h"
#include "../ecran/EcranCharacterIcon.h"
#include "../queue/Message.h"

EtatMenu::EtatMenu(Renderer &renderer) : EtatJeu(renderer) {}

bool EtatMenu::onEnter()
{
	popPushMenu( new EcranMenuPrincipal(renderer) );
	_gblMemory.push_back(InfoAlloc('N',__FILE__, __LINE__));
	return true;
}

void EtatMenu::update( TInfoTouches& keysInfo )
{
	getMenuCourant()->handleEvent(keysInfo);
}

void EtatMenu::render()
{
	getMenuCourant()->draw();
}

void EtatMenu::checkMessages()
{
	Message unMessage = oPileMessage.getMessageCourant();
	TypeMessage typeMessage;

	if (unMessage.getDestinataire() == OBJ_ETAT_MENU) {
		typeMessage = unMessage.getTypeMessage();
		oPileMessage.popMessage();

		switch (typeMessage) {

		case GM_MENU_RACE:
			popPushMenu( new EcranRace(renderer) );
			_gblMemory.push_back(InfoAlloc('N',__FILE__, __LINE__));
			break;

		case GM_MENU_GENDER:
			popPushMenu( new EcranGender(renderer) );
			_gblMemory.push_back(InfoAlloc('N',__FILE__, __LINE__));
			break;

		case GM_MENU_CLASSE:
			popPushMenu( new EcranClasse(renderer) );
			_gblMemory.push_back(InfoAlloc('N',__FILE__, __LINE__));
			break;

		case GM_MENU_ALIGNMENT:
			popPushMenu( new EcranAlignment(renderer) );
			_gblMemory.push_back(InfoAlloc('N',__FILE__, __LINE__));
			break;

		case GM_MENU_CHARACTER:
			popPushMenu( new EcranCharacter(renderer) );
			_gblMemory.push_back(InfoAlloc('N',__FILE__, __LINE__));
			break;

		case GM_MENU_CHARACTER_ICON:
			popPushMenu( new EcranCharacterIcon(renderer) );
			_gblMemory.push_back(InfoAlloc('N',__FILE__, __LINE__));
			break;

		case GM_REVENIR_MENU_PRINCIPAL:
			popPushMenu( new EcranMenuPrincipal(renderer) );
			_gblMemory.push_back(InfoAlloc('N',__FILE__, __LINE__));
			break;

		default: break;
		}
	}

	getMenuCourant()->verifierMessages();
}

bool EtatMenu::onExit()
{
	while ( getMenuCourant() != 0)
		popMenu();

	return true;
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
    _gblMemory.push_back(InfoAlloc('D',__FILE__, __LINE__));

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
