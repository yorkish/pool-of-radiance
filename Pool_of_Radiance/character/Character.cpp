#include "Character.h"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include "../common/Donnees.h"
#include "../roll/Roll.h"
#include "../common/Util.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;

Character::Character(): oPileMessage(PileMessage::getInstance())
{
	BaseCommonValues baseValues = Donnees::getInstance().getBaseCommonValues();

	//info
	info.name = "";
	info.portrait.indTete = 0;
	info.portrait.indCorps = 0;

	info.coins = {0, 0, 0, 0, 0, 0};
	info.coins.coinsPerPounds = baseValues.coinsPerPounds;

	info.AC     = baseValues.AC;

	info.encumbrance     = 0;
	info.MAX_ENCUMBRANCE = baseValues.maxEncumbrance;

	info.damage     = baseValues.damage;
	info.minDamage  = baseValues.damage;
	info.experience = 0;
	info.level[0]   = -1;
	info.level[1]   = -1;
	info.level[2]   = -1;
	info.status.val = OKAY;
	info.status.nom = Donnees::getInstance().getnomStatus(info.status.val);
}

void Character::setRace(NodeRace& nodeRace)
{
	oRace.setRace(nodeRace);

	info.race         = nodeRace;
	info.movementRate = oRace.getMovementRate();
	info.icon.size    = oRace.getIconSize();
}

void Character::setGender(NodeGender& nodeGender)
{
	info.gender = nodeGender;
}

void Character::setClasse(NodeClasse& nodeClasse)
{
	const string MAX = "MAX";
	vector<NodeClasse> vctCharClasses;
	vector<NodeClasse>::iterator iter;
	int i;

	info.classe = nodeClasse;

	vctCharClasses = Donnees::getInstance().getCharacterClasses(info.classe.val);

	for(iter = vctCharClasses.begin(), i = 0; iter != vctCharClasses.end(); iter++, i++) {
		oTabClasses[i].setClasse(oRace.getRace(), (*iter).val);
		info.level[i] = oTabClasses[i].getLevel();
	}

	MAX_CLASSES = vctCharClasses.size();
	selectTHAC_Table();
}

void Character::setAlignment(NodeAlignment& nodeAlignment)
{
	info.alignment = nodeAlignment;
}

void Character::selectTHAC_Table()
{
	posClasseTHAC = 0;

	if (MAX_CLASSES > 1) {
		Class_e classeTHAC;
		classeTHAC = Donnees::getInstance().getMClassRestriction( info.classe.val, oRace.getMClassRestiction() );

		for(int i = 0; i < MAX_CLASSES; i++)
			if (oTabClasses[i].getClasse() == classeTHAC)
				posClasseTHAC = i;
	}

	info.THAC0 = oTabClasses[posClasseTHAC].getTHAC0(0);
}

void Character::generateCharacter()
{
	info.name = "";

	rollAbilities();
	bonusPerAbilities();
	rollStartingAge();
	rollStartingGold();
	rollHitPoints();
	calculateEncumbrance();
}

void Character::rollAbilities()
{
	Condition condition;
	AbilitiesTable table = oRace.getAbilitiesTable();

	for(int i = 0; i < MAX_CLASSES; i++){
		condition = oTabClasses[i].getConditionPercentage();
		if (condition.score != -1)
			break;
	}

	do {
		info.STR = table.rolls.throwDice() + table.STR.bonus;
		info.DEX = table.rolls.throwDice() + table.DEX.bonus;
		info.CON = table.rolls.throwDice() + table.CON.bonus;
		info.INT = table.rolls.throwDice() + table.INT.bonus;
		info.WIS = table.rolls.throwDice() + table.WIS.bonus;
		info.CHA = table.rolls.throwDice() + table.CHA.bonus;
	} while ( !validateAbilities(table) );

	// Doit-on calculer un pourcentage pour la force ?
	info.strPercentage = 0;
	if ( condition.score != -1 && info.STR == table.STR.condition.score ) {
		Roll roll;
		roll.appendRoll(table.STR.condition.then);

		info.strPercentage = roll.throwDice();
		if (info.strPercentage == condition.score) {
			info.STR += condition.then;
			info.strPercentage = 0;
		}
	}
}

bool Character::validateAbilities(const AbilitiesTable& table)
{
	bool valid;

	if      (info.STR < table.STR.min || info.STR > table.STR.max)
		valid = false;
	else if (info.DEX < table.DEX.min || info.DEX > table.DEX.max)
		valid = false;
	else if (info.CON < table.CON.min || info.CON > table.CON.max)
		valid = false;
	else if (info.INT < table.INT.min || info.INT > table.INT.max)
		valid = false;
	else if (info.WIS < table.WIS.min || info.WIS > table.WIS.max)
		valid = false;
	else if (info.CHA < table.CHA.min || info.CHA > table.CHA.max)
		valid = false;
	else
		valid = true;

	return valid;
}

void Character::bonusPerAbilities()
{
	BaseCommonValues baseValues = Donnees::getInstance().getBaseCommonValues();
	info.AC              = baseValues.AC;
	info.MAX_ENCUMBRANCE = baseValues.maxEncumbrance;
	info.damage          = baseValues.damage;
	info.minDamage       = baseValues.damage;

	Donnees::getInstance().getBonusPerAbilities(info);

	info.MAX_ENCUMBRANCE += info.bonus.encumbrance;
	info.AC              += info.bonus.AC;
	info.THAC0           = oTabClasses[posClasseTHAC].getTHAC0(info.bonus.toHit);

	info.minDamage.addToY(info.bonus.toDamage);
	info.damage.addToY   (info.bonus.toDamage);
}

void Character::rollStartingAge()
{
	Roll rolls;

	for (int i = 0; i < MAX_CLASSES; i++)
		rolls.appendRoll( oTabClasses[i].getRollStartingAge() );

	if (MAX_CLASSES != 1)
		rolls.appendRoll( Donnees::getInstance().getStartingAge(oRace.getRace(), info.classe.val) );

	info.age = rolls.throwDice();
}

void Character::rollStartingGold()
{
	Roll rolls;

	for (int i = 0; i < MAX_CLASSES; i++)
		rolls.appendRoll( oTabClasses[i].getRollStartingGold() );

	if (MAX_CLASSES != 1)
		rolls.appendRoll( RollOperation("MAX", "0", '+') );

	info.coins.gold = rolls.throwDice();
}

void Character::rollHitPoints()
{
	Roll rolls;

	for (int i = 0; i < MAX_CLASSES; i++) {
		rolls.appendRoll( oTabClasses[i].rollHitPoints(info.bonus.HPperDie) );
		rolls.appendRoll( RollOperation("RES", Util::toStr(MAX_CLASSES), '/') );
	}

	info.HP     = rolls.throwDice();
	info.MAX_HP = info.HP;
}

void Character::calculateEncumbrance()
{
	int totalCoins = 0;
	double weight  = 0;

	totalCoins += info.coins.platinum;
	totalCoins += info.coins.gold;
	totalCoins += info.coins.electrum;
	totalCoins += info.coins.silver;
	totalCoins += info.coins.copper;

	weight = totalCoins / info.coins.coinsPerPounds;

	info.encumbrance = (int) floor(weight);
}

void Character::verifierMessages()
{
	NodeRace*      nodeRace  ; NodeGender*    nodeGender;
	NodeClasse*    nodeClasse; NodeAlignment* nodeAlignment;
	CharacterInfo* infoTemp  ;
	TypeMessage typeMessage;
	NomObjet destinataire;

	Message unMessage = oPileMessage.getMessageCourant();
	vector<NodeClasse>* temp;

	if (unMessage.getDestinataire() == OBJ_PERSONNAGE_EN_CREATION) {
		typeMessage = unMessage.getTypeMessage();

		switch (typeMessage) {

		case GM_RACE_CHOISIE:
			nodeRace = (NodeRace*) (unMessage.getContenu());
			setRace(*nodeRace);
			oPileMessage.popMessage();
			break;

		case GM_GENDER_CHOISI:
			nodeGender = (NodeGender*) (unMessage.getContenu());
			setGender(*nodeGender);
			oPileMessage.popMessage();
			break;

		case GM_CLASSE_CHOISIE:
			nodeClasse = (NodeClasse*) (unMessage.getContenu());
			setClasse(*nodeClasse);
			oPileMessage.popMessage();
			break;

		case GM_ALIGNMENT_CHOISI:
			nodeAlignment = (NodeAlignment*) (unMessage.getContenu());
			setAlignment(*nodeAlignment);
			oPileMessage.popMessage();
			break;

		case GM_OBTENIR_CLASSES_PERMISES:
			temp = new vector<NodeClasse>;
			gbl_Memoire.push_back(InfoAlloc('N',__FILE__, __LINE__));
			*temp = oRace.getAllowedClasses();
			oPileMessage.popMessage();
			oPileMessage.pushMessage( Message(OBJ_PERSONNAGE, OBJ_ECRAN_MENU_CLASSE, GM_LISTE_CLASSES_PERMISES, temp) );
			break;

		case GM_GENERER_PERSONNAGE:
			destinataire = unMessage.getSource();
			generateCharacter();
			oPileMessage.popMessage();
			oPileMessage.pushMessage( Message(OBJ_PERSONNAGE, destinataire, GM_INFO_CHARACTER, &info) );
			break;

		case GM_PERSONNAGE_CHOISI:
			infoTemp = (CharacterInfo*) (unMessage.getContenu());
			info     = *infoTemp;
			delete infoTemp;
			gbl_Memoire.push_back(InfoAlloc('D',__FILE__, __LINE__));
			oPileMessage.popMessage();
			break;

		case GM_INFO_CHARACTER:
			destinataire = unMessage.getSource();
			oPileMessage.popMessage();
			oPileMessage.pushMessage( Message(OBJ_PERSONNAGE, destinataire, GM_INFO_CHARACTER, &info) );
			break;

		default: break;
		}
	}
}

Character::~Character() {}
