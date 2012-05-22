#include <vector>
#include "SaveGameManager.h"
#include "queue/Message.h"

using namespace std;

SaveGameManager::SaveGameManager(): oPileMessage(PileMessage::getInstance())
{}

void SaveGameManager::verifierMessages()
{
	NomObjet destination;
	Message unMessage = oPileMessage.getMessageCourant();

	if (unMessage.getDestinataire() == OBJ_SAVE_GAME_MANAGER) {
		switch (unMessage.getTypeMessage()) {
		case GM_OBTENIR_LISTE_SAUVEGARDE:
			destination = unMessage.getSource();
			oPileMessage.popMessage();
			oPileMessage.pushMessage(Message(OBJ_SAVE_GAME_MANAGER,
			                                 destination,
			                                 GM_LISTE_SAUVEGARDE,
			                                 getLettresSauvegardes() ));
			break;

		case GM_CHARGER_PARTIE:
			oPileMessage.popMessage(); break;

		default: break;
		}
	}
}

void* SaveGameManager::getLettresSauvegardes()
{
	vector<char>* lstSauvegarde = new vector<char>;
	gbl_Memoire.push_back(InfoAlloc('N',__FILE__, __LINE__));

	lstSauvegarde->push_back('A');  lstSauvegarde->push_back('B');
	lstSauvegarde->push_back('C');  lstSauvegarde->push_back('D');
	lstSauvegarde->push_back('E');  lstSauvegarde->push_back('F');
	lstSauvegarde->push_back('G');  lstSauvegarde->push_back('H');
	lstSauvegarde->push_back('I');  lstSauvegarde->push_back('J');
	lstSauvegarde->push_back('K');

	return lstSauvegarde;
}

SaveGameManager::~SaveGameManager() {}
