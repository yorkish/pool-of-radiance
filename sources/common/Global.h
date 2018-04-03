#pragma once

#include <string>
#include <SDL2/SDL.h>
#include <vector>
#include "../roll/Roll.h"
#include "../roll/RollOperation.h"
#include "Cleanup.h"

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

extern std::vector<InfoAlloc> _gblMemory;

const int LOADING_TIME = 2000;

const int MAX_SAVED_GAMES = 11;

const int PORTRAIT_MAX_TETES = 14;
const int PORTRAIT_MAX_CORPS = 12;

const std::string FILE_WINDOW_SETTING = "data/settings/window.txt";
const std::string FILE_OSRIC_RULES    = "data/rules/osricRules.xml";

enum GameState { INTRO, MENU, VIEWPORT, MAP, EXIT_REQUESTED, GAME_STATE_UNDEFINED };

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

enum class Couleur : Uint32 {black = 0x000000FF,    blue = 0x0000AAFF,          green = 0x00AA00FF,       cyan = 0x00AAAAFF,
							 red = 0xAA0000FF,      magenta = 0xAA00AAFF,       brown = 0xAA5500FF,       lightGray = 0xAAAAAAFF,
							 darkGray = 0x555555FF, brightBlue = 0x5555FFFF,    brightGreen = 0x55FF55FF, brightCyan = 0x55FFFFFF,
							 lightRed = 0xFF5555FF, brightMagenta = 0xFF55FFFF, yellow = 0xFFFF55FF,      white = 0xFFFFFFFF,
							 sameColor = 0x0F0F0F0F /* this color will never be rendered */};

//// Overload the Couleur++ operator
//inline Couleur& operator++(Couleur& eDOW, int)
//{
//	const int i = static_cast<int>(eDOW)+1;
//	eDOW = static_cast<Couleur>((i) % 16);
//	return eDOW;
//}
//
//// Overload the Couleur-- operator
//inline Couleur& operator--(Couleur& type, int)
//{
//	const int i = static_cast<int>(type) - 1;
//
//	type = static_cast<Couleur> ((i < 0) ? 15 : i);
//
//	return type;
//}

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

//// Overload the Couleur-- operator
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
