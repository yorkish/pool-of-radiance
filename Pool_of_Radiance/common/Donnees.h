#pragma once
#include <vector>
#include <string>
#include "Global.h"

#include <xalanc/XalanSourceTree/XalanSourceTreeInit.hpp>
#include <xalanc/XalanSourceTree/XalanSourceTreeDOMSupport.hpp>
#include <xalanc/XalanSourceTree/XalanSourceTreeParserLiaison.hpp>
#include <xalanc/DOMSupport/XalanDocumentPrefixResolver.hpp>

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
		std::vector<RollOperation> getStartingAge(Race_e race, Class_e classe);
		std::vector<RollOperation> getStartingGold(Class_e classe);
		RollOperation              getHpRoll(Class_e classe, int level, int bonusPerDie);
		Class_e                    getMClassRestriction(Class_e classe, MClassRestiction_e mClassRestriction);

	private:
		Donnees();

		void initXalanC();
		void init();

		bool isXMLloaded();
		void loadRaces();
		void loadGenders();
		void loadClasses();
		void loadAlignments();
		std::vector<NodeClasse> getClasses();

		~Donnees();

		static Donnees* singleton;

		xalanc_1_10::XalanSourceTreeInit			theSourceTreeInit;
		xalanc_1_10::XalanSourceTreeDOMSupport		theDOMSupport;
		xalanc_1_10::XalanSourceTreeParserLiaison	theLiaison;
		xalanc_1_10::XalanDocument*					theDocument;
		xalanc_1_10::XalanDocumentPrefixResolver*	thePrefixResolver;
		xalanc_1_10::XalanNode* 					root;

		bool loadError;

		std::vector<NodeRace>      vctRaces;
		std::vector<NodeGender>    vctGenders;
		std::vector<NodeAlignment> vctAlignments;
		std::vector<NodeClasse>    vctClasses;
};
