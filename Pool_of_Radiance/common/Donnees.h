#pragma once
#include <vector>
#include <string>
#include "Global.h"
#include "../tinyXML/tinyxml.h"
#include "../tinyXML/TinyXMLHelper.h"

class Donnees
{
	public:
		static Donnees& getInstance();

		std::vector<NodeRace>      getRaces();
		std::vector<NodeGender>    getGenders();
		std::vector<NodeAlignment> getAlignments();
		std::vector<NodeClasse>    getAllowedClasses(Race_e race);
		std::string                getnomStatus(Status_e status);
		BaseCommonValues           getBaseCommonValues();
		AbilitiesTable             getAbilitiesTable(Race_e race);
		Condition                  getConditionPercentage(Class_e classe);
		void                       getBonusPerAbilities(CharacterInfo& character);
		RaceInfo                   getRaceInfo(Race_e race);
		std::vector<NodeClasse>    getCharacterClasses(Class_e classe);
		THAC_GenerationTable       getTHACInfo(Class_e classe, int level);
		RollOperation              getStartingAge(Race_e race, Class_e classe);
		std::vector<RollOperation> getStartingGold(Class_e classe);
		RollOperation              getHpRoll(Class_e classe, int level, int bonusPerDie);
		Class_e                    getMClassRestriction(Class_e classe, MClassRestiction_e mClassRestriction);

	private:
		Donnees();

		void init();
		bool loadFile();
		void loadRaces();
		void loadGenders();
		void loadClasses();
		void loadAlignments();
		std::vector<NodeClasse> getClasses();

		~Donnees();

		static Donnees* singleton;
		TinyXMLHelper oHelper;

		TiXmlDocument   doc;
		TiXmlHandle     hRoot;

		bool fileLoaded;
		bool loadError;

		std::vector<NodeRace>      vctRaces;
		std::vector<NodeGender>    vctGenders;
		std::vector<NodeAlignment> vctAlignments;
		std::vector<NodeClasse>    vctClasses;
		std::vector<NodeClasse>    vctClassesPermises;
};
