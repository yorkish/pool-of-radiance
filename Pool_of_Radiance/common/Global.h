#pragma once

#include <string>
#include <SDL/SDL.h>
#include <vector>
#include "../roll/Roll.h"
#include "../roll/RollOperation.h"

class InfoAlloc {
	public:
		InfoAlloc(char type, std::string source, int line) {
			this->type = type; this->source = source; this->line = line;
		};

		InfoAlloc(const InfoAlloc& object) {
			type = object.type; source = object.source; line = object.line;
		}

		~InfoAlloc() {};

		int line;  std::string source;  char type;
};

extern std::vector<InfoAlloc> gbl_Memoire;

//Les attributs de notre �cran
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 400;
const int SCREEN_BPP = 32;

//Les attributs de notre surface de travail
const int TRAVAIL_WIDTH = 320;
const int TRAVAIL_HEIGHT = 200;

const int FRAMES_PER_SECOND = 40;
const int DELAIS_MS = 1000 / FRAMES_PER_SECOND;

const int LOADING_TIME = 2000;

const int MAX_SAVED_GAMES = 11;

const int PORTRAIT_MAX_TETES = 14;
const int PORTRAIT_MAX_CORPS = 12;

const std::string FILE_WINDOW_SETTING = "data/settings/window.txt";
const std::string FILE_OSRIC_RULES    = "data/rules/osricRules.xml";

enum GameState { INTRO, MENU, VIEWPORT, MAP, EXIT_REQUESTED };

enum TypeDirection { DIR_N, DIR_S, DIR_O, DIR_E };

enum Race_e {DWARF, ELF, GNOME, HALF_ELF, HALFLING, HUMAN, RACE_NONE};

enum Gender_e {MALE, FEMALE, GENDER_NONE};

enum Class_e {	CLERIC, FIGHTER, MAGIC_USER, PALADIN, RANGER, THIEF,
				CLERIC_FIGHTER, CLERIC_MAGIC_USER, CLERIC_RANGER, CLERIC_FIGHTER_MAGIC_USER,
				FIGHTER_MAGIC_USER, FIGHTER_THIEF, FIGHTER_MAGIC_USER_THIEF,
				MAGIC_USER_THIEF,
				CLASSE_NONE};

enum Alignment_e {LAW_GOOD, LAW_NEUTRAL, LAW_EVIL, NEUTRAL_GOOD, TRUE_NEUTRAL, NEUTRAL_EVIL, CHAOTIC_GOOD, CHAOTIC_NEUTRAL, CHAOTIC_EVIL, ALIGN_NONE};

enum Ability_e {STRENGTH, DEXTERITY, CONSTITUTION, INTELLIGENCE, WISDOM, CHARISMA};

enum MClassRestiction_e { LESS_RETRICTIVE, MOST_RETRICTIVE };

enum Status_e { OKAY, UNCONSCIOUS, DYING, DEAD, STONED, FLED, GONE };

enum Size_e { SIZE_SMALL, SIZE_LARGE };

enum Couleur {cNOIR       , cBLEU         , cVERT      , cCYAN        ,
	          cROUGE      , cMAGENTA      , cBRUN      , cGRIS_CLAIR  ,
	          cGRIS_FONCE , cBLEU_CLAIR   , cVERT_CLAIR, cCYAN_CLAIR  ,
	          cROUGE_CLAIR, cMAGENTA_CLAIR, cJAUNE     , cBLANC       ,
	          cMEME_COULEUR                                            };

const SDL_Color COUL_NOIR          = {0x00, 0x00, 0x00, 0}; // Default Palette:  0
const SDL_Color COUL_BLEU          = {0x00, 0x00, 0xAA, 0}; // Default Palette:  1
const SDL_Color COUL_VERT          = {0x00, 0xAA, 0x00, 0}; // Default Palette:  2
const SDL_Color COUL_CYAN          = {0x00, 0xAA, 0xAA, 0}; // Default Palette:  3
const SDL_Color COUL_ROUGE         = {0xAA, 0x00, 0x00, 0}; // Default Palette:  4
const SDL_Color COUL_MAGENTA       = {0xAA, 0x00, 0xAA, 0}; // Default Palette:  5
const SDL_Color COUL_BRUN          = {0xAA, 0x55, 0x00, 0}; // Default Palette:  6
const SDL_Color COUL_GRIS_CLAIR    = {0xAA, 0xAA, 0xAA, 0}; // Default Palette:  7
const SDL_Color COUL_GRIS_FONCE    = {0x55, 0x55, 0x55, 0}; // Default Palette:  8
const SDL_Color COUL_BLEU_CLAIR    = {0x55, 0x55, 0xFF, 0}; // Default Palette:  9
const SDL_Color COUL_VERT_CLAIR    = {0x55, 0xFF, 0x55, 0}; // Default Palette: 10
const SDL_Color COUL_CYAN_CLAIR    = {0x55, 0xFF, 0xFF, 0}; // Default Palette: 11
const SDL_Color COUL_ROUGE_CLAIR   = {0xFF, 0x55, 0x55, 0}; // Default Palette: 12
const SDL_Color COUL_MAGENTA_CLAIR = {0xFF, 0x55, 0xFF, 0}; // Default Palette: 13
const SDL_Color COUL_JAUNE         = {0xFF, 0xFF, 0x55, 0}; // Default Palette: 14
const SDL_Color COUL_BLANC         = {0xFF, 0xFF, 0xFF, 0}; // Default Palette: 15

// Overload the Couleur++ operator
inline Couleur& operator++(Couleur& eDOW, int)
{
	const int i = static_cast<int>(eDOW)+1;
	eDOW = static_cast<Couleur>((i) % 16);
	return eDOW;
}

// Overload the Couleur-- operator
inline Couleur& operator--(Couleur& type, int)
{
	const int i = static_cast<int>(type) - 1;

	type = static_cast<Couleur> ((i < 0) ? 15 : i);

/*
	if (i < 0) // Check whether to cycle to last item if number goes below 0
		type = static_cast<Couleur>(15);
	else // Else set it to current number -1
		type = static_cast<Couleur>((i) % 16);
*/
	return type;

}

struct TInfoTouches
{
	bool   bHaut  , bBas;
	bool   bGauche, bDroite;
	char   caractere;
	bool   bEnter;
	bool   bRetourArriere;
	bool   bEspace;
};

struct NodeRace
{
	std::string nom;
	Race_e      val;
};

struct NodeGender
{
	std::string nom;
	Gender_e    val;
};

struct NodeClasse
{
	std::string nom;
	Class_e     val;
};

struct NodeAlignment
{
	std::string nom;
	Alignment_e val;
};

struct NodeStatus
{
	std::string nom;
	Status_e    val;
};

struct Condition
{
	int score;
	int then;
};

struct ConditionRoll
{
	int score;
	RollOperation then;
};

struct BaseCommonValues
{
	int AC;
	int maxEncumbrance;
	RollOperation damage;
	int coinsPerPounds;
};

struct RaceInfo
{
	int baseMovementRate;
	MClassRestiction_e mClassRestriction;
	Size_e iconSize;
};

struct THAC_GenerationTable
{
	struct {int value, repeats, offset;} baseTHAC;
	int THAC;
};

struct AbilitiesTable
{
	Roll rolls;
	struct { int min, max, bonus; ConditionRoll condition;} STR;
	struct { int min, max, bonus;} DEX;
	struct { int min, max, bonus;} CON;
	struct { int min, max, bonus;} INT;
	struct { int min, max, bonus;} WIS;
	struct { int min, max, bonus;} CHA;
};

struct Coins
{
	int copper;
	int silver;
	int electrum;
	int gold;
	int platinum;
	int coinsPerPounds;
};

struct CharacterInfo
{
	std::string name;

	NodeRace      race;
	NodeGender    gender;
	NodeClasse    classe;
	NodeAlignment alignment;
	NodeStatus    status;

	int age;

	int STR, DEX, CON, INT, WIS, CHA;
	int strPercentage;

	Coins coins;

	int level[3];
	int experience;

	int AC;
	int THAC0;

	int encumbrance, MAX_ENCUMBRANCE;

	int HP, MAX_HP;

	RollOperation damage, minDamage;

	int movementRate;

	struct {
		int toHit;
		int toHitMissile;
		int toDamage;
		int encumbrance;
		int AC;
		int HPperDie;
	} bonus;

	struct {
		int indTete;
		int indCorps;
	} portrait;

	struct {
		Size_e size;
		Couleur weapon1, weapon2;
		Couleur body1  , body2;
		Couleur hair   , face;
		Couleur shield1, shield2;
		Couleur arm1   , arm2;
		Couleur leg1   , leg2;
	} icon;

};
