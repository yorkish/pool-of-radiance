#include "EcranCharacter.h"
#include <string>
#include <iostream>
#include "../common/Util.h"

using std::string;
using std::cout; using std::endl;

EcranCharacter::EcranCharacter() :
	        TETES_PAR_RANGEES(PORTRAIT_MAX_TETES / 2),
			CORPS_PAR_RANGEES(PORTRAIT_MAX_CORPS / 2),
			oAffichage(Affichage::getInstance()),
			spritesTetes(0), spritesCorps(0), statusEcran(GENERATION)
{}

bool EcranCharacter::init()
{
	if (oListeTexte.init()) {
		spritesTetes = oAffichage.loadImageAsSurface("data/images/HEAD_DAX.png", 0, 0, 255);
		spritesCorps = oAffichage.loadImageAsSurface("data/images/BODY_DAX.png", 0, 0, 255);

		oPileMessage.pushMessage( Message(OBJ_ECRAN_CHARACTER, OBJ_PERSONNAGE_EN_CREATION, GM_GENERER_PERSONNAGE) );

		if (spritesTetes != 0 && spritesCorps != 0)
			return true;
	}

	return false;
}

void EcranCharacter::handleEvent( TInfoTouches& infTouches )
{
	CharacterInfo* info;

	switch (statusEcran) {

	case GENERATION:
		switch (infTouches.caractere) {
		case SDLK_y:
			statusEcran = CHOISIR_NOM;
			updateScreen();
			break;

		case SDLK_n:
			oPileMessage.pushMessage( Message(OBJ_ECRAN_CHARACTER, OBJ_PERSONNAGE_EN_CREATION, GM_GENERER_PERSONNAGE) );
			break;

		case SDLK_e:
			oPileMessage.pushMessage( Message(OBJ_ECRAN_CHARACTER, OBJ_ETAT_MENU, GM_REVENIR_MENU_PRINCIPAL) );
			oPileMessage.pushMessage( Message(OBJ_ECRAN_CHARACTER, OBJ_JEU, GM_ANNULER_PERSONNAGE) );
			break;

		default: break;
		}
		break;

	case CHOISIR_NOM:
		if (infTouches.caractere != '\0')
			character.name += infTouches.caractere;
		else if (infTouches.bEspace)
			character.name += ' ';
		else if (infTouches.bRetourArriere)
			character.name = character.name.substr(0, character.name.length() - 1);

		if (infTouches.bEnter)
			statusEcran = CHOISIR_PORTRAIT;

		updateScreen();
		break;

	case CHOISIR_PORTRAIT:
		switch (infTouches.caractere) {
		case SDLK_h:
			if (++character.portrait.indTete == PORTRAIT_MAX_TETES) character.portrait.indTete = 0;
			break;

		case SDLK_b:
			if (++character.portrait.indCorps == PORTRAIT_MAX_CORPS) character.portrait.indCorps = 0;
			break;

		case SDLK_k:
			statusEcran = EXITING;
			info  = new CharacterInfo;
			gbl_Memoire.push_back(InfoAlloc('N',__FILE__, __LINE__));
			*info = character;
			oPileMessage.pushMessage( Message(OBJ_ECRAN_MENU_GENDER, OBJ_ETAT_MENU, GM_MENU_CHARACTER_ICON) );
			oPileMessage.pushMessage( Message(OBJ_ECRAN_CHARACTER, OBJ_PERSONNAGE_EN_CREATION, GM_PERSONNAGE_CHOISI, info) );
			break;

		case SDLK_e:
			oPileMessage.pushMessage( Message(OBJ_ECRAN_CHARACTER, OBJ_ETAT_MENU, GM_REVENIR_MENU_PRINCIPAL) );
			oPileMessage.pushMessage( Message(OBJ_ECRAN_CHARACTER, OBJ_JEU, GM_ANNULER_PERSONNAGE) );
			break;

		default: break;
		}
		break;

	case EXITING:
		break;

	}
}

void EcranCharacter::draw()
{
	if (!oListeTexte.isEmpty()) {
		dessinerCadreEtPortrait();

		// Le texte
		oListeTexte.draw();

		// Le Portrait
		afficherPortrait();
	}
}

void EcranCharacter::afficherPortrait()
{
	SDL_Rect src;

	//La tête
	src.w = 88; src.h = 40;
	src.x = src.w * (character.portrait.indTete % TETES_PAR_RANGEES);
	src.y = src.h * (character.portrait.indTete / TETES_PAR_RANGEES);
	oAffichage.applySurface(224, 8, spritesTetes, src);

	//Le corps
	src.w = 88; src.h = 48;
	src.x = src.w * (character.portrait.indCorps % CORPS_PAR_RANGEES);
	src.y = src.h * (character.portrait.indCorps / CORPS_PAR_RANGEES);
	oAffichage.applySurface(224, 48, spritesCorps, src);
}

void EcranCharacter::updateScreen()
{
	string temp;
	oListeTexte.reset();

	temp = character.gender.nom + " " + character.race.nom + " age " + Util::toStr(character.age);
	oListeTexte.addTexte(temp, 1, 3, cBLANC);

	oListeTexte.addTexte(character.alignment.nom, 1, 4, cBLANC);
	oListeTexte.addTexte(character.classe.nom   , 1, 5, cBLANC);

	updateAbilities();
	updateCoins();
	updateLevels();

	oListeTexte.addTexte("exp", 17, 15, cBLANC);
	oListeTexte.addTexte(Util::toStr(character.experience), 21, 15, cBLANC);

	oListeTexte.addTexte("ac", 1, 17, cBLANC);
	oListeTexte.addTexte(Util::toStr(character.AC), 4, 17, cVERT_CLAIR);

	oListeTexte.addTexte("thac0",  9, 17, cBLANC);
	oListeTexte.addTexte(Util::toStr(character.THAC0), 15, 17, cVERT_CLAIR);

	oListeTexte.addTexte("encumbrance", 22, 17, cBLANC);
	oListeTexte.addTexte(Util::toStr(character.encumbrance), 34, 17, cVERT_CLAIR);

	updateHP();

	oListeTexte.addTexte("damage",  8, 18, cBLANC);
	oListeTexte.addTexte(character.damage.getStringRep(), 15, 18, cVERT_CLAIR);

	oListeTexte.addTexte("movement", 25, 18, cBLANC);
	oListeTexte.addTexte(Util::toStr(character.movementRate), 34, 18, cVERT_CLAIR);

	updateStatus();

	switch (statusEcran) {
	case GENERATION:
		oListeTexte.addTexte("keep this character?", 0, 24, cMAGENTA_CLAIR);
		oListeTexte.addTexte("yes" , 21, 24, cVERT_CLAIR, cBLANC);
		oListeTexte.addTexte("no"  , 25, 24, cVERT_CLAIR, cBLANC);
		oListeTexte.addTexte("exit", 28, 24, cVERT_CLAIR, cBLANC);
		break;

	case CHOISIR_NOM:
		oListeTexte.addTexte("character name:  ",  0, 24, cMAGENTA_CLAIR);
		oListeTexte.addTexte(character.name     , 16, 24, cBLANC);
		break;

	case CHOISIR_PORTRAIT:
		oListeTexte.addTexte("head",  0 , 24, cVERT_CLAIR, cBLANC);
		oListeTexte.addTexte("body",  5 , 24, cVERT_CLAIR, cBLANC);
		oListeTexte.addTexte("keep",  10, 24, cVERT_CLAIR, cBLANC);
		oListeTexte.addTexte("exit",  15, 24, cVERT_CLAIR, cBLANC);

	case EXITING:
		break;
	}
}

void EcranCharacter::updateAbilities()
{
	string temp;

	temp = "str " + Util::toStr(character.STR, 2);
	if (character.strPercentage > 0)
		temp += "(" + Util::toStr(character.strPercentage, 2, true) + ")";
	oListeTexte.addTexte(temp, 1, 7, cVERT_CLAIR);

	temp = "dex " + Util::toStr(character.DEX, 2);
	oListeTexte.addTexte(temp, 1, 8, cVERT_CLAIR);

	temp = "con " + Util::toStr(character.CON, 2);
	oListeTexte.addTexte(temp, 1, 9, cVERT_CLAIR);

	temp = "int " + Util::toStr(character.INT, 2);
	oListeTexte.addTexte(temp, 1, 10, cVERT_CLAIR);

	temp = "wis " + Util::toStr(character.WIS, 2);
	oListeTexte.addTexte(temp, 1, 11, cVERT_CLAIR);

	temp = "cha " + Util::toStr(character.CHA, 2);
	oListeTexte.addTexte(temp, 1, 12, cVERT_CLAIR);
}

void EcranCharacter::updateCoins()
{
	int ligne = 7;
	string coins;

	if (character.coins.platinum != 0) {
		coins = Util::toStr(character.coins.platinum);
		oListeTexte.addTexte("platinum " + coins, 12, ligne++ , cVERT_CLAIR);
	}

	if (character.coins.gold != 0) {
		coins = Util::toStr(character.coins.gold);
		oListeTexte.addTexte("gold " + coins, 16, ligne++ , cVERT_CLAIR);
	}
	if (character.coins.electrum != 0) {
		coins = Util::toStr(character.coins.electrum);
		oListeTexte.addTexte("electrum " + coins, 12, ligne++ , cVERT_CLAIR);
	}

	if (character.coins.silver != 0) {
		coins = Util::toStr(character.coins.silver);
		oListeTexte.addTexte("silver " + coins, 14, ligne++ , cVERT_CLAIR);
	}

	if (character.coins.copper != 0) {
		coins = Util::toStr(character.coins.copper);
		oListeTexte.addTexte("copper " + coins, 14, ligne, cVERT_CLAIR);
	}
}

void EcranCharacter::updateLevels()
{
	const int MAX_CLASSES = 3;

	string level;
	string temp;
	int i = 0;

	level = Util::toStr(character.level[i++]);

	while (character.level[i] != -1 && i < MAX_CLASSES) {
		temp = Util::toStr(character.level[i++]);
		level += "/" + temp;
	}

	oListeTexte.addTexte("level " + level, 1, 15, cBLANC);
}

void EcranCharacter::updateHP()
{
	Couleur couleur;

	oListeTexte.addTexte("hp", 1, 18, cBLANC);

	if (character.HP == character.MAX_HP)
		couleur = cVERT_CLAIR;
	else if(character.HP >= 0)
		couleur = cJAUNE;
	else
		couleur = cROUGE_CLAIR;

	oListeTexte.addTexte(Util::toStr(character.HP), 4, 18, couleur);
}

void EcranCharacter::updateStatus()
{
	Couleur couleur;

	oListeTexte.addTexte("status", 1 , 22, cBLANC);

	switch (character.status.val) {
	case OKAY:
		couleur = cVERT_CLAIR;
		break;

	case UNCONSCIOUS:
	case FLED:
	case STONED:
		couleur = cJAUNE;
		break;

	case DYING:
	case DEAD:
	case GONE:
		couleur = cROUGE_CLAIR;
	}

	oListeTexte.addTexte(character.status.nom, 8, 22, couleur);
}

void EcranCharacter::verifierMessages()
{
	Message unMessage = oPileMessage.getMessageCourant();

	if (unMessage.getDestinataire() == OBJ_ECRAN_CHARACTER) {
		switch (unMessage.getTypeMessage()) {

		case GM_INFO_CHARACTER:
			character = *((CharacterInfo*) unMessage.getContenu());
			oPileMessage.popMessage();
			updateScreen();
			break;

		default: break;
		}
	}
}

void EcranCharacter::release()
{
	oListeTexte.reset();
}

EcranCharacter::~EcranCharacter() {}
