#include <iostream>
#include <vector>
#include <list>
#include <sstream>
#include "Donnees.h"
#include "Global.h"
#include "Util.h"
#include "XalanCHelper.h"

#include <xalanc/Include/PlatformDefinitions.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xalanc/XPath/XObject.hpp>
#include <xalanc/XPath/XPathEvaluator.hpp>
#include <xalanc/XPath/NodeRefList.hpp>
#include <xalanc/XalanDOM/XalanNamedNodeMap.hpp>

using std::string;
using std::cout;
using std::cerr;
using std::vector;
using std::list;
using std::endl;
using std::stringstream;

XALAN_CPP_NAMESPACE_USE
XERCES_CPP_NAMESPACE_USE

// Initialisation du singleton à NULL
Donnees* Donnees::singleton = 0;

Donnees::Donnees(): theLiaison(theDOMSupport), loadError(false)
{
	initXalanC();
	init();
}

void Donnees::initXalanC()
{
	try {
		const XalanDOMString theFileName(FILE_OSRIC_RULES.c_str());
		const LocalFileInputSource theInputSource(theFileName.c_str());

		theDOMSupport.setParserLiaison(&theLiaison);
		theDocument = theLiaison.parseXMLStream(theInputSource);
		thePrefixResolver = new XalanDocumentPrefixResolver(theDocument);

		XPathEvaluator theEvaluator;
		root = theEvaluator.selectSingleNode(theDOMSupport, theDocument, XalanDOMString("/").c_str(), *thePrefixResolver);

		XalanCHelper::setWorkingObjects(&theDOMSupport, root, thePrefixResolver);

		loadError = false;
	} catch (...) {
		loadError = true;
	}
}

void Donnees::init()
{
	if (isXMLloaded()) {
		loadRaces();
		loadGenders();
		loadClasses();
		loadAlignments();
	}
}

bool Donnees::isXMLloaded()
{
	return !loadError;
}

void Donnees::loadRaces()
{
	NodeRefList nodeList;
	XalanNode* node;
	int nbNodes;
	int id;
	string name;

	if ( !isXMLloaded() )
		return;

	nodeList = XalanCHelper::selectNodeList(nodeList, "//race[@name]");

	nbNodes = nodeList.getLength();
	for (int i=0; i < nbNodes; i++) {
		node = nodeList.item(i);

		name = XalanCHelper::getAttributeValue(node, "name");
		id   = XalanCHelper::getAttributeIntValue(node, "id");

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
	}
}

void Donnees::loadGenders()
{
	NodeRefList nodeList;
	XalanNode* node;
	int nbNodes;
	int id;
	string name;

	if ( !isXMLloaded() )
		return;

	nodeList = XalanCHelper::selectNodeList(nodeList, "//gender[@name]");

	nbNodes = nodeList.getLength();
	for (int i=0; i < nbNodes; i++) {
		node = nodeList.item(i);

		name = XalanCHelper::getAttributeValue(node, "name");
		id   = XalanCHelper::getAttributeIntValue(node, "id");

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
	}
}

void Donnees::loadAlignments()
{
	NodeRefList nodeList;
	XalanNode* node;
	int nbNodes;
	int id;
	string name;

	if ( !isXMLloaded() )
		return;

	nodeList = XalanCHelper::selectNodeList(nodeList, "//alignment[@name]");

	nbNodes = nodeList.getLength();
	for (int i=0; i < nbNodes; i++) {
		node = nodeList.item(i);

		name = XalanCHelper::getAttributeValue(node, "name");
		id   = XalanCHelper::getAttributeIntValue(node, "id");

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
	}
}

void Donnees::loadClasses()
{
	NodeRefList nodeList;
	XalanNode* node;
	int nbNodes;
	int id;
	string name;

	if ( !isXMLloaded() )
		return;

	nodeList = XalanCHelper::selectNodeList(nodeList, "//class[@name]");

	nbNodes = nodeList.getLength();
	for (int i=0; i < nbNodes; i++) {
		node = nodeList.item(i);

		name = XalanCHelper::getAttributeValue(node, "name");
		id   = XalanCHelper::getAttributeIntValue(node, "id");

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
	}
}

string Donnees::getnomStatus(Status_e status)
{
	stringstream xpath;

	if ( !isXMLloaded() )
		return "";

	xpath << "//status[@id = " << status << "]/@name";
	return XalanCHelper::getStrResult(xpath);
}

BaseCommonValues Donnees::getBaseCommonValues()
{
	BaseCommonValues baseValues;

	if ( !isXMLloaded() )
		return baseValues;

	baseValues.maxEncumbrance = XalanCHelper::getIntResult("//characterCommon/baseValues/maxEncumbrance/text()");
	baseValues.AC             = XalanCHelper::getIntResult("//characterCommon/baseValues/AC/text()");
	baseValues.coinsPerPounds = XalanCHelper::getIntResult("//characterCommon/baseValues/coinsPerPounds/text()");

	// Base damage
	baseValues.damage.setX( XalanCHelper::getStrResult("//characterCommon/baseValues/damage/text()") );
	baseValues.damage.setY("0");
	baseValues.damage.setOperateur('+');

	return baseValues;
}

AbilitiesTable Donnees::getAbilitiesTable(Race_e race)
{
	NodeRefList nodeList;
	XalanNode* node;
	stringstream xpath;
	AbilitiesTable table;
	RollOperation rollOp;
	int nbNodes;
	int id;
	int min;
	int max;
	int bonus;
	int repetitions;

	if ( !isXMLloaded() )
		return table;

	//On va chercher les lancers de dés pour les habilités
	node = XalanCHelper::selectSingleNode("//lstAbilities/rolls/roll[1]");

	if (node != 0) {
		rollOp.setX( XalanCHelper::getAttributeValue(node, "x") );
		rollOp.setY( XalanCHelper::getAttributeValue(node, "y") );
		rollOp.setOperateur( XalanCHelper::getAttributeValue(node, "oper") );

		repetitions = XalanCHelper::getAttributeIntValue(node, "repeats");
		for(int i = 0; i < repetitions; i++)
			table.rolls.appendRoll(rollOp);

		node = XalanCHelper::NextSibling(node);
		if (node != 0) {
			rollOp.setX( XalanCHelper::getAttributeValue(node, "x") );
			rollOp.setY( XalanCHelper::getAttributeValue(node, "y") );
			rollOp.setOperateur( XalanCHelper::getAttributeValue(node, "oper") );
			table.rolls.appendRoll(rollOp);
		}
	}

	//On va chercher la condition rattachée au lancer du dé STR
	xpath << "//lstAbilities/Ability[@id=" << STRENGTH << "]";
	node = XalanCHelper::selectSingleNode(xpath);

	if (node != 0) {
		node = XalanCHelper::FirstChild(node);
		table.STR.condition.score = XalanCHelper::getAttributeIntValue(node, "score");

		node = XalanCHelper::FirstChild(node);
		table.STR.condition.then.setX( XalanCHelper::getAttributeValue(node, "x") );
		table.STR.condition.then.setY( XalanCHelper::getAttributeValue(node, "y") );
		table.STR.condition.then.setOperateur( XalanCHelper::getAttributeValue(node, "oper") );
	}

	//On va chercher les habilitées de la race
	xpath.str(""); xpath << "//race[@id='" << race << "']/ability";
	nodeList = XalanCHelper::selectNodeList(nodeList, xpath);

	nbNodes = nodeList.getLength();
	for (int i=0; i < nbNodes; i++) {
		node = nodeList.item(i);

		id    = XalanCHelper::getAttributeIntValue(node, "refId");
		min   = XalanCHelper::getAttributeIntValue(node, "min");
		max   = XalanCHelper::getAttributeIntValue(node, "max");
		bonus = XalanCHelper::getAttributeIntValue(node, "bonus");

		switch (id) {
		case STRENGTH:     table.STR.min = min; table.STR.max = max; table.STR.bonus = bonus; break;
		case DEXTERITY:    table.DEX.min = min; table.DEX.max = max; table.DEX.bonus = bonus; break;
		case CONSTITUTION: table.CON.min = min; table.CON.max = max; table.CON.bonus = bonus; break;
		case INTELLIGENCE: table.INT.min = min; table.INT.max = max; table.INT.bonus = bonus; break;
		case WISDOM:       table.WIS.min = min; table.WIS.max = max; table.WIS.bonus = bonus; break;
		case CHARISMA:     table.CHA.min = min; table.CHA.max = max; table.CHA.bonus = bonus; break;
		}
	}

	return table;
}

Condition Donnees::getConditionPercentage(Class_e classe)
{
	XalanNode* node;
	Condition condition = {-1, -1};
	stringstream xpath;

	if ( !isXMLloaded() )
		return condition;

	//On trouve la bonne classe
	xpath << "//class[@id='" << classe << "']/if[@AbilityId='" << STRENGTH << "']";
	node = XalanCHelper::selectSingleNode(xpath);

	if (node != 0) {
		condition.score = XalanCHelper::getAttributeIntValue(node, "percentage");
		condition.then  = XalanCHelper::getAttributeIntValue(node, "bonus");
	}

	return condition;
}

void Donnees::getBonusPerAbilities(CharacterInfo& character)
{
	XalanNode* node;
	stringstream xpath;

	if ( !isXMLloaded() )
		return;

	// Bonus reliés à la force
	if (character.STR == 18 && character.strPercentage != 0)
		xpath << "//strengthTable/strength[@score = " << character.STR << " and @min <= "<< character.strPercentage << " and @max >= " << character.strPercentage << "]";
	else
		xpath << "//strengthTable/strength[@score = " << character.STR << "]";

	cout << "****" << endl;
	cout << xpath.str();

	node = XalanCHelper::selectSingleNode(xpath);
	character.bonus.toHit       = XalanCHelper::getAttributeIntValue(node, "toHit");
	character.bonus.toDamage    = XalanCHelper::getAttributeIntValue(node, "toDamage");
	character.bonus.encumbrance = XalanCHelper::getAttributeIntValue(node, "encumbrance");

	cout << "character.bonus.toHit       = " << character.bonus.toHit << endl;
	cout << "character.bonus.toDamage    = " << character.bonus.toDamage << endl;
	cout << "character.bonus.encumbrance = " << character.bonus.encumbrance << endl;

	cout << "****" << endl;

	// Bonus reliées à la dextérité
	xpath.str(""); xpath << "//dexterityTable/dexterity[@score = " << character.DEX << "]";
	node = XalanCHelper::selectSingleNode(xpath);
	character.bonus.toHitMissile = XalanCHelper::getAttributeIntValue(node, "missileToHit");
	character.bonus.AC           = XalanCHelper::getAttributeIntValue(node, "AC");

	// Bonus reliées à la constitution
	xpath.str(""); xpath << "//constitutionTable/constitution[@score = " << character.CON << "]/class";
	node = XalanCHelper::selectSingleNode(xpath);

	if (node != 0) {
		//Il faut y aller par classes

		vector<NodeClasse> vctCharClasses;
		vector<NodeClasse>::iterator iter;
		int temp = 0;

		character.bonus.HPperDie = 0;
		vctCharClasses = getCharacterClasses(character.classe.val);

		for(iter = vctCharClasses.begin(); iter != vctCharClasses.end(); iter++) {
			xpath.str(""); xpath << "//constitutionTable/constitution[@score = " << character.CON << "]/class[@refId = " << (*iter).val << "]";
			node = XalanCHelper::selectSingleNode(xpath);

			temp = XalanCHelper::getAttributeIntValue(node,"HPperDie");
			if (temp > character.bonus.HPperDie)
				character.bonus.HPperDie = temp;
		}
	}
	else {
		xpath.str(""); xpath << "//constitutionTable/constitution[@score = " << character.CON << "]";
		node = XalanCHelper::selectSingleNode(xpath);
		character.bonus.HPperDie = XalanCHelper::getAttributeIntValue(node, "HPperDie");
	}
}

RaceInfo Donnees::getRaceInfo(Race_e race)
{
	const string MOST = "most";
	const string SMALL = "small";

	stringstream xpath;
	string valeur;
	RaceInfo raceInfo = { -1, LESS_RETRICTIVE, SIZE_LARGE };

	if ( !isXMLloaded() )
		return raceInfo;

	xpath << "//race[@id = " << race << "]/movementRate/text()";
	raceInfo.baseMovementRate = XalanCHelper::getIntResult(xpath);

	// Restriction Multi-classe
	xpath.str(""); xpath << "//race[@id = " << race << "]/multiClass/@restriction";
	valeur = XalanCHelper::getStrResult(xpath);
	Util::toLowerCase(valeur);

	if ( valeur.compare(MOST) == 0 )
		raceInfo.mClassRestriction = MOST_RETRICTIVE;
	else
		raceInfo.mClassRestriction = LESS_RETRICTIVE;

	// Icône
	xpath.str(""); xpath << "//race[@id = " << race << "]/icon/@size";
	valeur =  XalanCHelper::getStrResult(xpath);
	Util::toLowerCase(valeur);

	if ( valeur.compare(SMALL) == 0 )
		raceInfo.iconSize = SIZE_SMALL;
	else
		raceInfo.iconSize = SIZE_LARGE;

	return raceInfo;
}

vector<NodeClasse> Donnees::getAllowedClasses(Race_e race)
{
	NodeRefList nodeList;
	XalanNode* node;
	stringstream xpath;
	std::vector<NodeClasse> vctClassesPermises;
	int refid;
	int nbNodes;

	if ( !isXMLloaded() )
		return vctClassesPermises;

	//On va chercher la node de la race
	xpath << "//race[@id = " << race << "]/allowedClasses[@refId]";
	nodeList = XalanCHelper::selectNodeList(nodeList, xpath);

	nbNodes = nodeList.getLength();
	for (int i=0; i < nbNodes; i++) {
		node = nodeList.item(i);

		refid = XalanCHelper::getAttributeIntValue(node, "refId");
		vctClassesPermises.push_back(vctClasses[refid]);
	}

	return vctClassesPermises;
}

vector<NodeClasse> Donnees::getCharacterClasses(Class_e classe)
{
	stringstream xpath;
	XalanNode* node;
	vector<string> vctSousClasses;
	vector<string>::iterator iter;
	vector<NodeClasse> charClasses;
	string sousClasses;
	int x;

	//On va chercher les info pour la classe
	xpath << "//class[@id = " << classe << "]";
	node = XalanCHelper::selectSingleNode(xpath);

	//Est-ce un personnage multi-classe?
	vctSousClasses = Util::splitString(XalanCHelper::getAttributeValue(node, "subClasses"), ';');

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
	stringstream xpath;
	XalanNode* node;
	THAC_GenerationTable table = { {-1, -1, -1}, -1};

	if ( !isXMLloaded() )
		return table;

	//On va chercher les info sur la table THAC
	xpath << "//characterCommon/THAC_Table";
	node = XalanCHelper::selectSingleNode(xpath);

	table.baseTHAC.value   = XalanCHelper::getAttributeIntValue(node, "value");
	table.baseTHAC.repeats = XalanCHelper::getAttributeIntValue(node, "repeats");

	//On va chercher les infos sur la table THAC pour la classe
	xpath.str(""); xpath << "//class[@id =" << classe << "]/THAC/level[@levels = " << level << "]";
	node = XalanCHelper::selectSingleNode(xpath);

	table.baseTHAC.offset = XalanCHelper::getAttributeIntValue(node, "offset");
	table.THAC            = XalanCHelper::getAttributeIntValue(node, "value");

	return table;
}

std::vector<RollOperation> Donnees::getStartingAge(Race_e race, Class_e classe)
{
	stringstream xpath;
	NodeRefList nodeList;
	XalanNode* node;
	vector<RollOperation> vctRolls;
	RollOperation rollOperation;
	int nbNodes;

	if ( !isXMLloaded() )
		return vctRolls;

	//On va chercher la node de la race et la node de l'age reliée à la classe
	xpath << "//race[@id = " << race << "]/startingAge[@classId = " << classe << "]/roll";
	nodeList = XalanCHelper::selectNodeList(nodeList, xpath);

	nbNodes = nodeList.getLength();
	for (int i=0; i < nbNodes; i++) {
		node = nodeList.item(i);

		rollOperation.setX( XalanCHelper::getAttributeValue(node, "x") );
		rollOperation.setY( XalanCHelper::getAttributeValue(node, "y") );
		rollOperation.setOperateur( XalanCHelper::getAttributeValue(node, "oper") );
		vctRolls.push_back(rollOperation);
	}

	return vctRolls;
}

std::vector<RollOperation> Donnees::getStartingGold(Class_e classe)
{
	stringstream xpath;
	NodeRefList nodeList;
	XalanNode* node;
	vector<RollOperation> vctRolls;
	RollOperation rollOperation;
	int nbNodes;

	if ( !isXMLloaded() )
		return vctRolls;

	//On va chercher la node de la race et la node de l'age reliée à la classe
	xpath << "//class[@id =" << classe << "]/startingGold/roll";
	nodeList = XalanCHelper::selectNodeList(nodeList, xpath);

	nbNodes = nodeList.getLength();
	for (int i=0; i < nbNodes; i++) {
		node = nodeList.item(i);

		rollOperation.setX( XalanCHelper::getAttributeValue(node, "x") );
		rollOperation.setY( XalanCHelper::getAttributeValue(node, "y") );
		rollOperation.setOperateur( XalanCHelper::getAttributeValue(node, "oper") );
		vctRolls.push_back(rollOperation);
	}

	return vctRolls;
}

RollOperation Donnees::getHpRoll(Class_e classe, int level, int bonusPerDie)
{
	stringstream xpath;
	XalanNode* node;
	RollOperation rollOperation;

	if ( !isXMLloaded() )
		return rollOperation;

	xpath << "//class[@id =" << classe << "]/levels/level[@level = " << level << "]";
	node = XalanCHelper::selectSingleNode(xpath);

	rollOperation.setX( XalanCHelper::getAttributeValue(node, "hp") );
	rollOperation.setY( "0" );
	rollOperation.setOperateur( '+' );
	rollOperation.setBonusPerDie(bonusPerDie);

	return rollOperation;
}

// TODO
Class_e Donnees::getMClassRestriction(Class_e classe, MClassRestiction_e mClassRestriction)
{
	stringstream xpath;
	XalanNode* node;
	string restriction;
	int pos = 0;

	if ( !isXMLloaded() )
		return CLASSE_NONE;

	if (mClassRestriction == MOST_RETRICTIVE)
		restriction = "most";
	else
		restriction = "less";

	xpath << "//class[@id =" << classe << "]/THAC[@mcRestriction = '" << restriction << "']";
	node = XalanCHelper::selectSingleNode(xpath);
	pos  = XalanCHelper::getAttributeIntValue(node, "classId");

	return vctClasses[pos].val;
}

vector<NodeRace> Donnees::getRaces() { return vctRaces; }
vector<NodeGender> Donnees::getGenders() { return vctGenders; }
vector<NodeClasse> Donnees::getClasses() { return vctClasses; }
vector<NodeAlignment> Donnees::getAlignments() { return vctAlignments; }

Donnees& Donnees::getInstance()
{
	if (singleton == 0) {
		XMLPlatformUtils::Initialize();
		XPathEvaluator::initialize();

		singleton = new Donnees();
	}

	return *singleton;
}

Donnees::~Donnees()
{
	if (singleton != 0) {
		delete thePrefixResolver;

		XPathEvaluator::terminate();
		XMLPlatformUtils::Terminate();

		delete singleton;
	}
}
