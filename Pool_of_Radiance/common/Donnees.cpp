#include <iostream>
#include <vector>
#include <list>
#include "Donnees.h"
#include "Global.h"
#include "Util.h"
#include "../tinyXML/TinyXMLHelper.h"

using std::string;
using std::cout;
using std::vector;
using std::list;
using std::endl;

// Initialisation du singleton � NULL
Donnees* Donnees::singleton = 0;

Donnees::Donnees(): doc(FILE_OSRIC_RULES), hRoot(0), fileLoaded(false), loadError(false)
{
	init();
}

void Donnees::init() {
	if ( loadFile() )
	{
		loadRaces();
		loadGenders();
		loadClasses();
		loadAlignments();
	}
}

bool Donnees::loadFile()
{
	if ( !(fileLoaded || loadError) ) {
		if ( doc.LoadFile() )
		{
			TiXmlHandle   hDoc(&doc);
			TiXmlElement* pElem;

			pElem = hDoc.FirstChildElement().Element();
			hRoot = TiXmlHandle(pElem);

			fileLoaded = true;
		} else {
			loadError  = true;
			fileLoaded = false;
		}
	}

	return fileLoaded;
}

void Donnees::loadRaces()
{
	TiXmlNode* node;
	int id;
	string name;

	if ( !fileLoaded )
		return;

	node = hRoot.FirstChild( "lstRaces" ).FirstChild().ToNode();

	while (node != 0)
	{
		id   = oHelper.getAttributeIntValue(node, "id");
		name = oHelper.getAttributeValue   (node, "name");

		if (name.length() != 0)
		{
			NodeRace nodeRace;

			switch (id) {
			case DWARF   : nodeRace.val = DWARF    ; break;
			case ELF     : nodeRace.val = ELF      ; break;
			case GNOME   : nodeRace.val = GNOME    ; break;
			case HALF_ELF: nodeRace.val = HALF_ELF ; break;
			case HALFLING: nodeRace.val = HALFLING ; break;
			case HUMAN   : nodeRace.val = HUMAN    ; break;
			default      : nodeRace.val = RACE_NONE; break;
			}

			nodeRace.nom = name;
			vctRaces.push_back(nodeRace);
		}
		node = node->NextSiblingElement();
	}
}

void Donnees::loadGenders()
{
	TiXmlNode* node;
	int id;
	string name;

	if ( !fileLoaded )
		return;

	node = hRoot.FirstChild( "lstGenders" ).FirstChild().ToNode();

	while (node != 0)
	{
		id   = oHelper.getAttributeIntValue(node, "id");
		name = oHelper.getAttributeValue   (node, "name");

		if (name.length() != 0)
		{
			NodeGender nodeGender;

			switch (id) {
			case MALE    : nodeGender.val = MALE       ; break;
			case FEMALE  : nodeGender.val = FEMALE     ; break;
			default      : nodeGender.val = GENDER_NONE; break;
			}

			nodeGender.nom = name;
			vctGenders.push_back(nodeGender);
		}

		node = node->NextSiblingElement();
	}
}

void Donnees::loadAlignments()
{
	TiXmlNode* node;
	int id;
	string name;

	if ( !fileLoaded )
		return;

	node = hRoot.FirstChild( "lstAlignments" ).FirstChild().ToNode();

	while (node != 0)
	{
		id   = oHelper.getAttributeIntValue(node, "id");
		name = oHelper.getAttributeValue   (node, "name");

		if (name.length() != 0)
		{
			NodeAlignment nodeAlignment;

			switch (id) {
			case LAW_GOOD       : nodeAlignment.val = LAW_GOOD       ; break;
			case LAW_NEUTRAL    : nodeAlignment.val = LAW_NEUTRAL    ; break;
			case LAW_EVIL       : nodeAlignment.val = LAW_EVIL       ; break;
			case NEUTRAL_GOOD   : nodeAlignment.val = NEUTRAL_GOOD   ; break;
			case TRUE_NEUTRAL   : nodeAlignment.val = TRUE_NEUTRAL   ; break;
			case NEUTRAL_EVIL   : nodeAlignment.val = NEUTRAL_EVIL   ; break;
			case CHAOTIC_GOOD   : nodeAlignment.val = CHAOTIC_GOOD   ; break;
			case CHAOTIC_NEUTRAL: nodeAlignment.val = CHAOTIC_NEUTRAL; break;
			case CHAOTIC_EVIL   : nodeAlignment.val = CHAOTIC_EVIL   ; break;
			default             : nodeAlignment.val = ALIGN_NONE     ; break;
			}

			nodeAlignment.nom = name;
			vctAlignments.push_back(nodeAlignment);
		}
		node = node->NextSiblingElement();
	}
}

void Donnees::loadClasses()
{
	TiXmlNode* node;
	int id;
	string name;

	if ( !fileLoaded )
		return;

	node = hRoot.FirstChild( "lstClasses" ).FirstChild().ToNode();

	while (node != 0)
	{
		id   = oHelper.getAttributeIntValue(node, "id");
		name = oHelper.getAttributeValue   (node, "name");

		if (name.length() != 0)
		{
			NodeClasse nodeClasse;

			switch (id) {
			case CLERIC    : nodeClasse.val = CLERIC    ; break;
			case FIGHTER   : nodeClasse.val = FIGHTER   ; break;
			case MAGIC_USER: nodeClasse.val = MAGIC_USER; break;
			case PALADIN   : nodeClasse.val = PALADIN   ; break;
			case RANGER    : nodeClasse.val = RANGER    ; break;
			case THIEF     : nodeClasse.val = THIEF     ; break;

			case CLERIC_FIGHTER           : nodeClasse.val = CLERIC_FIGHTER           ; break;
			case CLERIC_MAGIC_USER        : nodeClasse.val = CLERIC_MAGIC_USER        ; break;
			case CLERIC_RANGER            : nodeClasse.val = CLERIC_RANGER            ; break;
			case CLERIC_FIGHTER_MAGIC_USER: nodeClasse.val = CLERIC_FIGHTER_MAGIC_USER; break;
			case FIGHTER_MAGIC_USER       : nodeClasse.val = FIGHTER_MAGIC_USER       ; break;
			case FIGHTER_THIEF            : nodeClasse.val = FIGHTER_THIEF            ; break;
			case FIGHTER_MAGIC_USER_THIEF : nodeClasse.val = FIGHTER_MAGIC_USER_THIEF ; break;
			case MAGIC_USER_THIEF         : nodeClasse.val = MAGIC_USER_THIEF         ; break;

			default: nodeClasse.val = CLASSE_NONE     ; break;
			}

			nodeClasse.nom = name;
			vctClasses.push_back(nodeClasse);
		}
		node = node->NextSiblingElement();
	}
}

vector<NodeRace> Donnees::getRaces()
{
	return vctRaces;
}

vector<NodeGender> Donnees::getGenders()
{
	return vctGenders;
}

vector<NodeClasse> Donnees::getClasses()
{
	return vctClasses;
}

vector<NodeAlignment> Donnees::getAlignments()
{
	return vctAlignments;
}

string Donnees::getnomStatus(Status_e status)
{
	TiXmlNode* node;

	if ( !fileLoaded )
		return "";

	node = oHelper.findChildNodeById(hRoot.FirstChild( "lstStatus" ).ToNode(), "id", status);
	return oHelper.getAttributeValue(node, "name");
}

BaseCommonValues Donnees::getBaseCommonValues()
{
	BaseCommonValues baseValues;
	TiXmlNode* node;

	if ( !fileLoaded )
		return baseValues;

	node = hRoot.FirstChild( "characterCommon" ).FirstChild("baseValues").ToNode();

	baseValues.AC             = oHelper.getTextValueInt(node->FirstChild("AC"));
	baseValues.maxEncumbrance = oHelper.getTextValueInt(node->FirstChild("maxEncumbrance"));

	baseValues.damage.setX( oHelper.getTextValue(node->FirstChild("damage")) );
	baseValues.damage.setY("0");
	baseValues.damage.setOperateur('+');

	baseValues.coinsPerPounds = oHelper.getTextValueInt(node->FirstChild("coinsPerPounds"));

	return baseValues;
}

AbilitiesTable Donnees::getAbilitiesTable(Race_e race)
{
	AbilitiesTable table;
	RollOperation rollOp;
	TiXmlNode* node;
	int id;
	int min;
	int max;
	int bonus;
	int repetitions;

	if ( !fileLoaded )
		return table;

	//On va chercher les lancers de d�s pour les habilit�s
	node = hRoot.FirstChild( "lstAbilities" ).FirstChild("rolls").FirstChild().ToNode();
	if (node != 0) {
		rollOp.setX( oHelper.getAttributeValue(node, "x") );
		rollOp.setY( oHelper.getAttributeValue(node, "y") );
		rollOp.setOperateur( oHelper.getAttributeValue(node, "oper")[0] );
		repetitions = oHelper.getAttributeIntValue(node, "repeats");

		for(int i = 0; i < repetitions; i++)
			table.rolls.appendRoll(rollOp);

		node = node->NextSibling();
		if (node != 0) {
			rollOp.setX( oHelper.getAttributeValue(node, "x") );
			rollOp.setY( oHelper.getAttributeValue(node, "y") );
			rollOp.setOperateur( oHelper.getAttributeValue(node, "oper")[0] );
			table.rolls.appendRoll(rollOp);
		}
	}

	//On va chercher la condition rattach�e au lancer du d� STR
	node = oHelper.findChildNodeById(hRoot.FirstChild( "lstAbilities" ).ToNode(), "id", STRENGTH);
	if (node != 0) {
		node = node->FirstChild();
		table.STR.condition.score = oHelper.getAttributeIntValue(node, "score");

		node = node->FirstChild();
		table.STR.condition.then.setX( oHelper.getAttributeValue(node, "x") );
		table.STR.condition.then.setY( oHelper.getAttributeValue(node, "y") );
		table.STR.condition.then.setOperateur( oHelper.getAttributeValue(node, "oper")[0] );
	}

	//On va chercher la node de la race
	node = oHelper.findChildNodeById(hRoot.FirstChild( "lstRaces" ).ToNode(), "id", race);

	if (node != 0)
	{
		node = node->FirstChild("ability");
		while (node != 0) {
			id    = oHelper.getAttributeIntValue(node, "refid");
			min   = oHelper.getAttributeIntValue(node, "min");
			max   = oHelper.getAttributeIntValue(node, "max");
			bonus = oHelper.getAttributeIntValue(node, "bonus");

			switch (id) {
			case STRENGTH:     table.STR.min = min; table.STR.max = max; table.STR.bonus = bonus; break;
			case DEXTERITY:    table.DEX.min = min; table.DEX.max = max; table.DEX.bonus = bonus; break;
			case CONSTITUTION: table.CON.min = min; table.CON.max = max; table.CON.bonus = bonus; break;
			case INTELLIGENCE: table.INT.min = min; table.INT.max = max; table.INT.bonus = bonus; break;
			case WISDOM:       table.WIS.min = min; table.WIS.max = max; table.WIS.bonus = bonus; break;
			case CHARISMA:     table.CHA.min = min; table.CHA.max = max; table.CHA.bonus = bonus; break;
			}

			node = node->NextSibling("ability");
		}
	}

	return table;
}

Condition Donnees::getConditionPercentage(Class_e classe)
{
	TiXmlNode* node;
	Condition condition = {-1, -1};

	if ( !fileLoaded )
		return condition;

	//On trouve la bonne classe
	node = oHelper.findChildNodeById(hRoot.FirstChild( "lstClasses" ).ToNode(), "id", classe);
	node = oHelper.findChildNodeById(node, "if", "AbilityId", "0");

	if (node != 0) {
		condition.score = oHelper.getAttributeIntValue(node, "percentage");
		condition.then  = oHelper.getAttributeIntValue(node, "bonus");
	}

	return condition;
}

void Donnees::getBonusPerAbilities(CharacterInfo& character)
{
	TiXmlNode* node;

	if ( !fileLoaded )
		return;

	//Bonus reli�s � la force
	if (character.STR == 18 && character.strPercentage != 0) {
		node = oHelper.findChildNodeById(hRoot.FirstChild( "strengthTable" ).ToNode(), "score", character.STR);
		while ( character.strPercentage > oHelper.getAttributeIntValue(node, "percUnder") )
			node = node->NextSibling();
	} else
		node = oHelper.findChildNodeById(hRoot.FirstChild( "strengthTable" ).ToNode(), "score", character.STR);

	character.bonus.toHit       = oHelper.getAttributeIntValue(node, "toHit");
	character.bonus.toDamage    = oHelper.getAttributeIntValue(node, "toDamage");
	character.bonus.encumbrance = oHelper.getAttributeIntValue(node, "encumbrance");

	//Bonus reli�es � la dext�rit�
	node = oHelper.findChildNodeById(hRoot.FirstChild( "dexterityTable" ).ToNode(), "score", character.DEX);
	character.bonus.toHitMissile = oHelper.getAttributeIntValue(node, "missileToHit");
	character.bonus.AC           = oHelper.getAttributeIntValue(node, "AC");

	//Bonus reli�es � la constitution
	node = oHelper.findChildNodeById(hRoot.FirstChild( "constitutionTable" ).ToNode(), "score", character.CON);

	if (node->FirstChild() != 0) {
		//Il faut y aller par classes

		TiXmlNode* nodeTrouve;

		vector<NodeClasse> vctCharClasses;
		vector<NodeClasse>::iterator iter;
		int temp = 0;

		character.bonus.HPperDie = 0;
		vctCharClasses = getCharacterClasses(character.classe.val);

		for(iter = vctCharClasses.begin(); iter != vctCharClasses.end(); iter++) {
			nodeTrouve = oHelper.findChildNodeById(node, "refid", (*iter).val);
			temp = oHelper.getAttributeIntValue(nodeTrouve, "HPperDie");
			if (temp > character.bonus.HPperDie)
				character.bonus.HPperDie = temp;
		}
	}
	else
		character.bonus.HPperDie = oHelper.getAttributeIntValue(node, "HPperDie");
}

RaceInfo Donnees::getRaceInfo(Race_e race)
{
	TiXmlNode* node;
	string valeur;
	RaceInfo raceInfo = { -1, LESS_RETRICTIVE, LARGE };

	if ( !fileLoaded )
		return raceInfo;

	//On va chercher la node de la race
	node = oHelper.findChildNodeById(hRoot.FirstChild( "lstRaces" ).ToNode(), "id", race);

	if (node != 0) {
		raceInfo.baseMovementRate = oHelper.getTextValueInt(node->FirstChild("movementRate"));

		// Restriction Multi-classe
		valeur = oHelper.getAttributeValue(node->FirstChild("multiClass"), "restriction");
		Util::toLowerCase(valeur);

		if ( valeur.compare("most") == 0 )
			raceInfo.mClassRestriction = MOST_RETRICTIVE;
		else
			raceInfo.mClassRestriction = LESS_RETRICTIVE;

		// Ic�ne
		valeur = oHelper.getAttributeValue(node->FirstChild("icon"), "size");
		Util::toLowerCase(valeur);

		if ( valeur.compare("small") == 0 )
			raceInfo.iconSize = SMALL;
		else
			raceInfo.iconSize = LARGE;
	}

	return raceInfo;
}

vector<NodeClasse> Donnees::getAllowedClasses(Race_e race)
{
	TiXmlNode*    node;
	int refid;

	if (vctClassesPermises.size() != 0)
		vctClassesPermises.clear();

	if ( !fileLoaded )
		return vctClassesPermises;

	//On va chercher la node de la race
	node = oHelper.findChildNodeById(hRoot.FirstChild( "lstRaces" ).ToNode(), "id", race);

	if (node != 0)
	{
		node = node->FirstChild("allowedClasses");

		while (node != 0)
		{
			refid = -1;

			refid = oHelper.getAttributeIntValue(node, "refid");
			vctClassesPermises.push_back(vctClasses[refid]);

			node = node->NextSibling("allowedClasses");
		}
	}

	return vctClassesPermises;
}

vector<NodeClasse> Donnees::getCharacterClasses(Class_e classe)
{
	TiXmlNode* node;
	vector<string> vctSousClasses;
	vector<string>::iterator iter;
	vector<NodeClasse> charClasses;
	string sousClasses;
	int x;

	//On va chercher les info sur la table THAC pour la classe
	node = oHelper.findChildNodeById(hRoot.FirstChild( "lstClasses" ).ToNode(), "id", classe);

	sousClasses = oHelper.getAttributeValue(node, "subClasses");
	vctSousClasses = Util::splitString(sousClasses, ';');

	//Est-ce un personnage multi-classe?
	if (vctSousClasses.size() != 0 ) {
		for(iter = vctSousClasses.begin(); iter != vctSousClasses.end(); iter++) {
			x = atoi( (*iter).c_str() );
			charClasses.push_back(vctClasses[x]);
		}
	} else
		charClasses.push_back(vctClasses[classe]);

	return charClasses;
}

THAC_GenerationTable Donnees::getTHACInfo(Class_e classe, int level)
{
	TiXmlNode* node;
	THAC_GenerationTable table = { {-1, -1, -1}, -1};
	vector<string> vctSousClasses;
	string sousClasses;

	if ( !fileLoaded )
		return table;

	//On va chercher les info sur la table THAC
	node = hRoot.FirstChild( "characterCommon" ).FirstChild("THAC_Table").ToNode();

	table.baseTHAC.value   = oHelper.getAttributeIntValue(node, "value");
	table.baseTHAC.repeats = oHelper.getAttributeIntValue(node, "repeats");

	//On va chercher les infos sur la table THAC pour la classe
	node = oHelper.findChildNodeById(hRoot.FirstChild( "lstClasses" ).ToNode(), "id", classe);
	node = oHelper.findChildNodeById(node->FirstChild("THAC"), "levels", level);

	table.baseTHAC.offset = oHelper.getAttributeIntValue(node, "offset");
	table.THAC            = oHelper.getAttributeIntValue(node, "value");

	return table;
}

RollOperation Donnees::getStartingAge(Race_e race, Class_e classe)
{
	TiXmlNode* node;
	RollOperation rollOperation;

	if ( !fileLoaded )
		return rollOperation;

	//On va chercher la node de la race et la node de l'age reli�e � la classe
	node = oHelper.findChildNodeById(hRoot.FirstChild( "lstRaces" ).ToNode(), "id", race);
	node = oHelper.findChildNodeById(node, "startingAge", "classId", classe);

	// On suppose qu'il n'y a qu'une node � lire
	node = node->FirstChild();
	rollOperation.setX(oHelper.getAttributeValue(node, "x"));
	rollOperation.setY(oHelper.getAttributeValue(node, "y"));
	rollOperation.setOperateur(oHelper.getAttributeValue(node, "oper")[0]);

	return rollOperation;
}

std::vector<RollOperation> Donnees::getStartingGold(Class_e classe)
{
	TiXmlNode* node;
	vector<RollOperation> vctRolls;
	RollOperation rollOperation;

	if ( !fileLoaded )
		return vctRolls;

	//On va chercher la node de la race et la node de l'age reli�e � la classe
	node = oHelper.findChildNodeById(hRoot.FirstChild( "lstClasses" ).ToNode(), "id", classe);

	// On suppose qu'il y a, au plus, deux nodes � lire
	node = node->FirstChild("startingGold")->FirstChild();
	rollOperation.setX(oHelper.getAttributeValue(node, "x"));
	rollOperation.setY(oHelper.getAttributeValue(node, "y"));
	rollOperation.setOperateur(oHelper.getAttributeValue(node, "oper")[0]);
	vctRolls.push_back(rollOperation);

	node = node->NextSibling();
	if (node != 0) {
		rollOperation.setX(oHelper.getAttributeValue(node, "x"));
		rollOperation.setY(oHelper.getAttributeValue(node, "y"));
		rollOperation.setOperateur(oHelper.getAttributeValue(node, "oper")[0]);
		vctRolls.push_back(rollOperation);
	}

	return vctRolls;
}

RollOperation Donnees::getHpRoll(Class_e classe, int level, int bonusPerDie)
{
	TiXmlNode* node;
	RollOperation rollOperation;

	if ( !fileLoaded )
		return rollOperation;

	node = oHelper.findChildNodeById(hRoot.FirstChild( "lstClasses" ).ToNode(), "id", classe);
	node = oHelper.findChildNodeById(node->FirstChild("levels"), "level", level);

	if (node != 0) {
		rollOperation.setX( oHelper.getAttributeValue(node, "hp") );
		rollOperation.setY( "0" );
		rollOperation.setOperateur( '+' );
		rollOperation.setBonusPerDie(bonusPerDie);
	}

	return rollOperation;
}

Class_e Donnees::getMClassRestriction(Class_e classe, MClassRestiction_e mClassRestriction)
{
	TiXmlNode* node;
	string restriction;
	int pos;

	if ( !fileLoaded )
		return CLASSE_NONE;

	if (mClassRestriction == MOST_RETRICTIVE)
		restriction = "most";
	else
		restriction = "less";

	node = oHelper.findChildNodeById(hRoot.FirstChild( "lstClasses" ).ToNode(), "id", classe);
	node = oHelper.findChildNodeById(node, "THAC", "mcRestriction", restriction);
	pos  = oHelper.getAttributeIntValue(node, "classId");
	return vctClasses[pos].val;
}



Donnees& Donnees::getInstance()
{
	if (singleton == 0)
		singleton = new Donnees();

	return *singleton;
}

Donnees::~Donnees()
{
	if (singleton != 0)
		delete singleton;
}
