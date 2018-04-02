#include "EcranCharacter.h"
#include <string>
#include <iostream>
#include "../common/Util.h"

using std::string;
using std::cout; using std::endl;

EcranCharacter::EcranCharacter(Renderer &renderer) :
			Ecran(renderer),
	        TETES_PAR_RANGEES(PORTRAIT_MAX_TETES / 2),
			CORPS_PAR_RANGEES(PORTRAIT_MAX_CORPS / 2),
			spritesTetes(0),
			spritesCorps(0),
			statusEcran(GENERATION)
{}

bool EcranCharacter::init()
{
	if (oListeTexte->init()) {
		spritesTetes = renderer.loadImage("assets/HEAD_DAX.png");
		spritesCorps = renderer.loadImage("assets/BODY_DAX.png");

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
			_gblMemory.push_back(InfoAlloc('N',__FILE__, __LINE__));
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
	if (!oListeTexte->isEmpty()) {
		dessinerCadreEtPortrait(renderer);

		// Le texte
		oListeTexte->draw();

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
	renderer.applyTexture(224, 8, spritesTetes, src);

	//Le corps
	src.w = 88; src.h = 48;
	src.x = src.w * (character.portrait.indCorps % CORPS_PAR_RANGEES);
	src.y = src.h * (character.portrait.indCorps / CORPS_PAR_RANGEES);
	renderer.applyTexture(224, 48, spritesCorps, src);
}

void EcranCharacter::updateScreen()
{
	string temp;
	oListeTexte->reset();

	temp = character.gender.nom + " " + character.race.nom + " age " + Util::toStr(character.age);
	oListeTexte->addTexte(temp, 1, 3, Couleur::white);

	oListeTexte->addTexte(character.alignment.nom, 1, 4, Couleur::white);
	oListeTexte->addTexte(character.classe.nom   , 1, 5, Couleur::white);

	updateAbilities();
	updateCoins();
	updateLevels();

	oListeTexte->addTexte("exp", 17, 15, Couleur::white);
	oListeTexte->addTexte(Util::toStr(character.experience), 21, 15, Couleur::white);

	oListeTexte->addTexte("ac", 1, 17, Couleur::white);
	oListeTexte->addTexte(Util::toStr(character.AC), 4, 17, Couleur::brightGreen);

	oListeTexte->addTexte("thac0",  9, 17, Couleur::white);
	oListeTexte->addTexte(Util::toStr(character.THAC0), 15, 17, Couleur::brightGreen);

	oListeTexte->addTexte("encumbrance", 22, 17, Couleur::white);
	oListeTexte->addTexte(Util::toStr(character.encumbrance), 34, 17, Couleur::brightGreen);

	updateHP();

	oListeTexte->addTexte("damage",  8, 18, Couleur::white);
	oListeTexte->addTexte(character.damage.getStringRep(), 15, 18, Couleur::brightGreen);

	oListeTexte->addTexte("movement", 25, 18, Couleur::white);
	oListeTexte->addTexte(Util::toStr(character.movementRate), 34, 18, Couleur::brightGreen);

	updateStatus();

	switch (statusEcran) {
	case GENERATION:
		oListeTexte->addTexte("keep this character?", 0, 24, Couleur::brightMagenta);
		oListeTexte->addTexte("yes" , 21, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("no"  , 25, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("exit", 28, 24, Couleur::brightGreen, Couleur::white);
		break;

	case CHOISIR_NOM:
		oListeTexte->addTexte("character name:  ",  0, 24, Couleur::brightMagenta);
		oListeTexte->addTexte(character.name     , 16, 24, Couleur::white);
		break;

	case CHOISIR_PORTRAIT:
		oListeTexte->addTexte("head",  0 , 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("body",  5 , 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("keep",  10, 24, Couleur::brightGreen, Couleur::white);
		oListeTexte->addTexte("exit",  15, 24, Couleur::brightGreen, Couleur::white);
		break;

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

	oListeTexte->addTexte(temp, 1, 7, Couleur::brightGreen);

	temp = "dex " + Util::toStr(character.DEX, 2);
	oListeTexte->addTexte(temp, 1, 8, Couleur::brightGreen);

	temp = "con " + Util::toStr(character.CON, 2);
	oListeTexte->addTexte(temp, 1, 9, Couleur::brightGreen);

	temp = "int " + Util::toStr(character.INT, 2);
	oListeTexte->addTexte(temp, 1, 10, Couleur::brightGreen);

	temp = "wis " + Util::toStr(character.WIS, 2);
	oListeTexte->addTexte(temp, 1, 11, Couleur::brightGreen);

	temp = "cha " + Util::toStr(character.CHA, 2);
	oListeTexte->addTexte(temp, 1, 12, Couleur::brightGreen);
}

void EcranCharacter::updateCoins()
{
	int ligne = 7;
	string coins;

	if (character.coins.platinum != 0) {
		coins = Util::toStr(character.coins.platinum);
		oListeTexte->addTexte("platinum " + coins, 12, ligne++ , Couleur::brightGreen);
	}

	if (character.coins.gold != 0) {
		coins = Util::toStr(character.coins.gold);
		oListeTexte->addTexte("gold " + coins, 16, ligne++ , Couleur::brightGreen);
	}
	if (character.coins.electrum != 0) {
		coins = Util::toStr(character.coins.electrum);
		oListeTexte->addTexte("electrum " + coins, 12, ligne++ , Couleur::brightGreen);
	}

	if (character.coins.silver != 0) {
		coins = Util::toStr(character.coins.silver);
		oListeTexte->addTexte("silver " + coins, 14, ligne++ , Couleur::brightGreen);
	}

	if (character.coins.copper != 0) {
		coins = Util::toStr(character.coins.copper);
		oListeTexte->addTexte("copper " + coins, 14, ligne, Couleur::brightGreen);
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

	oListeTexte->addTexte("level " + level, 1, 15, Couleur::white);
}

void EcranCharacter::updateHP()
{
	Couleur couleur;

	oListeTexte->addTexte("hp", 1, 18, Couleur::white);

	if (character.HP == character.MAX_HP)
		couleur = Couleur::brightGreen;
	else if(character.HP >= 0)
		couleur = Couleur::yellow;
	else
		couleur = Couleur::lightRed;

	oListeTexte->addTexte(Util::toStr(character.HP), 4, 18, couleur);
}

void EcranCharacter::updateStatus()
{
	Couleur couleur;

	oListeTexte->addTexte("status", 1 , 22, Couleur::white);

	switch (character.status.val) {
	case OKAY:
		couleur = Couleur::brightGreen;
		break;

	case UNCONSCIOUS:
	case FLED:
	case STONED:
		couleur = Couleur::yellow;
		break;

	case DYING:
	case DEAD:
	case GONE:
		couleur = Couleur::lightRed;
	}

	oListeTexte->addTexte(character.status.nom, 8, 22, couleur);
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
	oListeTexte->reset();
	cleanup(spritesCorps);
	cleanup(spritesTetes);
}

EcranCharacter::~EcranCharacter() {}
