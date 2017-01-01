#pragma once
#include "../common/Global.h"

enum NomObjet {	OBJ_JEU,                  OBJ_ETAT_INTRO,           OBJ_ETAT_MENU,
				OBJ_ECRAN_MENU_PRINCIPAL, OBJ_ECRAN_MENU_RACE,      OBJ_ECRAN_MENU_GENDER,
				OBJ_ECRAN_MENU_CLASSE,    OBJ_ECRAN_MENU_ALIGNMENT, OBJ_ECRAN_CHARACTER,
				OBJ_ECRAN_CHARACTER_ICON, OBJ_SAVE_GAME_MANAGER,    OBJ_PERSONNAGE_EN_CREATION,
				OBJ_PERSONNAGE,           OBJ_ALL,                  OBJ_NONE };

enum TypeMessage {	GM_INTRO_FINI              , GM_MENU_RACE,
					GM_MENU_GENDER             , GM_MENU_CLASSE,
					GM_MENU_ALIGNMENT          , GM_MENU_CHARACTER,
					GM_MENU_CHARACTER_ICON     ,
					GM_REVENIR_MENU_PRINCIPAL  , GM_QUITTER,
					GM_NOUVEAU_PERSONNAGE      , GM_ANNULER_PERSONNAGE,
					GM_RACE_CHOISIE            , GM_GENDER_CHOISI,
					GM_CLASSE_CHOISIE          , GM_ALIGNMENT_CHOISI,
					GM_OBTENIR_LISTE_SAUVEGARDE, GM_LISTE_SAUVEGARDE,
					GM_CHARGER_PARTIE          , GM_OBTENIR_CLASSES_PERMISES,
					GM_LISTE_CLASSES_PERMISES  , GM_GENERER_PERSONNAGE,
					GM_INFO_CHARACTER          , GM_PERSONNAGE_CHOISI,
                    GM_NONE};

class Message {
	public:
		Message(NomObjet source, NomObjet destinataire, TypeMessage typeMessage);
		Message(NomObjet source, NomObjet destinataire, TypeMessage typeMessage, void* contenu);

		NomObjet     getSource();
		NomObjet     getDestinataire();
		TypeMessage  getTypeMessage();
		void*        getContenu();

		~Message();

	private:
		NomObjet     source;
		NomObjet     destinataire;
		TypeMessage  typeMessage;
		void*        contenu;
};
