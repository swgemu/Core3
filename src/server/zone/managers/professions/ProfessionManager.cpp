/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "ProfessionManager.h"

#include "../../../db/ServerDatabase.h"

/*#include "../../objects/player/Player.h"
#include "../../objects/player/PlayerImplementation.h"*/

//#include "../skills/SkillManager.h
#include "../objectcontroller/ObjectController.h"
#include "../crafting/CraftingManager.h"
#include "../../ZoneServer.h"

//#include "../../objects/player/badges/Badge.h"
#include "../../objects/creature/professions/SkillBox.h"
#include "../../objects/creature/professions/FourByFourProfession.h"
#include "../../objects/creature/professions/OneByFourProfession.h"
#include "../../objects/creature/professions/PyramidProfession.h"
#include "../../objects/creature/professions/Skill.h"
#include "../../objects/player/PlayerCreature.h"
#include "../../objects/player/PlayerObject.h"
#include "../../objects/player/Races.h"

const int ProfessionManager::professionHams[7][9] = {
		{ 600, 300, 300, 800, 400, 300, 900, 400, 500 },
		{ 1000, 500, 400, 800, 350, 350, 500, 300, 300 },
		{ 500, 300, 300, 1000, 400, 400, 800, 400, 400 },
		{ 1000, 450, 300, 800, 450, 300, 600, 300, 300 },
		{ 600, 300, 300, 700, 300, 300, 1000, 500, 500 },
		{ 800, 300, 350, 800, 400, 400, 700, 350, 400 },
		{ 800, 350, 350, 800, 350, 350, 800, 350, 350 }
};

ProfessionManager::ProfessionManager()
	: Mutex("Profession Manager"), Logger("ProfessionManager") {

	objectController = NULL;

	skillBoxMap.setNullValue(NULL);
	certificationMap.setNullValue(NULL);

	setGlobalLogging(true);
	setLogging(false);
}

ProfessionManager::~ProfessionManager() {
}
/*
void ProfessionManager::loadDefaultSkills(PlayerImplementation* player) {
	// Load default skills..
	Skill* defaultAttackSkill = skillManager->getSkill("attack");
	Skill* throwGrenade = skillManager->getSkill("throwgrenade");

	if (defaultAttackSkill != NULL)
		player->creatureSkills.put(defaultAttackSkill->getNameCRC(), defaultAttackSkill);

	if (throwGrenade != NULL)
		player->creatureSkills.put(throwGrenade->getNameCRC(), throwGrenade);
}
*/

void ProfessionManager::setStartingProfession(const String& startingProfession, int raceID, PlayerCreature* player) {
	int prof;

	if (startingProfession == "crafting_artisan")
		prof = 0;
	else if (startingProfession == "combat_brawler")
		prof = 1;
	else if (startingProfession == "social_entertainer")
		prof = 2;
	else if (startingProfession == "combat_marksman")
		prof = 3;
	else if (startingProfession == "science_medic")
		prof = 4;
	else if (startingProfession == "outdoors_scout")
		prof = 5;
	else
		prof = 6;


	for (int i = 0; i < 9; ++i) {
		int newVal = player->getBaseHAM(i) + professionHams[prof][i];

		player->setBaseHAM(i, newVal, false);
		player->setHAM(i, newVal, false);
		player->setMaxHAM(i, newVal, false);
	}

	Profession* profObj = getProfession(startingProfession);

	if (profObj != NULL) {
		SkillBox* novice = profObj->getNoviceBox(); // TODO:remove master box learning
		trainSkillBox(novice, player, false);
		//awardSkillBox(novice, player, true, false);
	}

	String race = Races::getSpecies(raceID);

	//skillmods
	SkillBox* speciesBox = getSkillBox("species_" + race);

	if (speciesBox != NULL) {
		trainSkillBox(speciesBox, player, false);
	} else {
		error("speciesBox null for " + race);
	}

	trainSkillBox("social_language_basic_speak", player, false);
	trainSkillBox("social_language_basic_comprehend", player, false);
	//lang
	if (raceID != 0 && raceID != 10) {
		String langBox = String("social_language_");

		if (raceID == 6 || raceID == 16)
			langBox += "moncalamari";
		else
			langBox += Races::getSpecies(raceID);

		trainSkillBox(langBox, player, false);
		String langDiscreteBox = langBox + String("_speak");
		trainSkillBox(langDiscreteBox, player, false);
		langDiscreteBox = langBox + String("_comprehend");
		trainSkillBox(langDiscreteBox, player, false);
	}

	if (race == 2 || race == 12) {
		String langBox = String("social_language_lekku");
		trainSkillBox(langBox, player, false);
		String langDiscreteBox = langBox + String("_speak");
		trainSkillBox(langDiscreteBox, player, false);
		langDiscreteBox = langBox + String("_comprehend");
		trainSkillBox(langDiscreteBox, player, false);
	}

	PlayerObject* ghost = player->getPlayerObject();
	ghost->setLanguageID(getLangFromRace(raceID), false);

}

bool ProfessionManager::checkPrerequisites(SkillBox* skillBox, PlayerCreature* player) {
	SkillBoxList* playerSkillBoxList = player->getSkillBoxList();

	if (playerSkillBoxList->contains(skillBox)) {
		System::out << "player contains skillbox " << endl;
		return false;
	}

	if ((player->getSkillPoints() + skillBox->skillPointsRequired) > 250) {
		System::out << "too many skill points " << player->getSkillPoints() << endl;
		return false;
	}

	for (int i = 0; i < skillBox->requiredSkills.size(); i++) {
		SkillBox* sBox = skillBox->requiredSkills.get(i);

		if (!playerSkillBoxList->contains(sBox)) {
			System::out << "required skill not found " << endl;
			return false;
		}
	}

	return true;
}

void ProfessionManager::awardSkillMods(SkillBox* skillBox, PlayerCreature* player, bool updateClient) {
	PlayerObject* playerObject = (PlayerObject*) player->getSlottedObject("ghost");

	for (int i = 0; i < skillBox->skillMods.size(); ++i) {
		String skillMod = skillBox->skillMods.elementAt(i).getKey();
		int value = skillBox->skillMods.elementAt(i).getValue();

		player->addSkillMod(skillMod, value, updateClient);
	}
}

void ProfessionManager::awardDraftSchematics(SkillBox* skillBox, PlayerCreature* player, bool updateClient) {
	PlayerObject* playerObject = (PlayerObject*) player->getSlottedObject("ghost");

	ManagedReference<CraftingManager* > craftingManager = player->getZoneServer()->getCraftingManager();
	if(craftingManager == NULL)
		return;

	Vector<String> schematicgroups;

	for (int i = 0; i < skillBox->skillSchematicsGranted.size(); ++i) {
		String schematicgroup = skillBox->skillSchematicsGranted.get(i);

		schematicgroups.add(schematicgroup);
	}

	craftingManager->awardSchematicGroup(playerObject, schematicgroups, updateClient);
}

void ProfessionManager::removeSkillMods(SkillBox* skillBox, PlayerCreature* player, bool updateClient) {
	PlayerObject* playerObject = (PlayerObject*) player->getSlottedObject("ghost");

	for (int i = 0; i < skillBox->skillMods.size(); ++i) {
		String skillMod = skillBox->skillMods.elementAt(i).getKey();
		int value = skillBox->skillMods.elementAt(i).getValue();

		player->addSkillMod(skillMod, -value, updateClient);
	}
}

void ProfessionManager::removeDraftSchematics(SkillBox* skillBox, PlayerCreature* player, bool updateClient) {
	PlayerObject* playerObject = (PlayerObject*) player->getSlottedObject("ghost");

	ManagedReference<CraftingManager* > craftingManager = player->getZoneServer()->getCraftingManager();
	if(craftingManager == NULL)
		return;

	Vector<String> schematicgroups;

	for (int i = 0; i < skillBox->skillSchematicsGranted.size(); ++i) {
		String schematicgroup = skillBox->skillSchematicsGranted.get(i);

		schematicgroups.add(schematicgroup);
	}

	craftingManager->removeSchematicGroup(playerObject, schematicgroups, updateClient);
}

void ProfessionManager::awardSkillBox(SkillBox* skillBox, PlayerCreature* player, bool awardRequired, bool updateClient) {
	if (player == NULL || skillBox == NULL)
		return;

	SkillBoxList* playerSkillBoxList = player->getSkillBoxList();

	if (playerSkillBoxList->contains(skillBox))
		return;

	SkillBox* skillBoxReq = NULL;

	PlayerObject* playerObject = (PlayerObject*) player->getSlottedObject("ghost");

	player->addSkillBox(skillBox, updateClient);
	player->addSkillPoints(skillBox->getSkillPointsRequired());

	playerObject->addSkills(skillBox->skillCommands, updateClient);
	playerObject->addSkills(skillBox->skillCertifications, updateClient);

	awardSkillMods(skillBox, player, updateClient);
	awardDraftSchematics(skillBox, player, updateClient);

	if (!awardRequired)
		return;

	for (int i = 0; i < skillBox->requiredSkills.size(); i++) {
		skillBoxReq = skillBox->requiredSkills.get(i);
		awardSkillBox(skillBoxReq, player, true, false);
	}
}

bool ProfessionManager::trainSkillBox(SkillBox* skillBox, PlayerCreature* player, bool updateClient) {
	if (!checkPrerequisites(skillBox, player))
		return false;

	//System::out << "trying to teach 2" << skillBox->getName() << endl;


	//skillManager->loadSkillBox(skillBox, player, false, updateClient);
	awardSkillBox(skillBox, player, false, updateClient);

	if (skillBox->isMasterBox()) {
		player->awardBadge(Badge::getID(skillBox->getName()));
	}

	/*if (skillBox->getName().compareTo("combat_smuggler_underworld_01") == 0) {

		String socialLanguage = "social_language_";
		String language = "language_";

		for (int i = 1; i < 10 ; i++) {

			String skillName;
			String languageName;

			if (i == 6) {
				skillName = String(socialLanguage + "moncalamari_comprehend");
				languageName = String(language + "moncalamari_comprehend");
			} else {
				skillName = String(socialLanguage + Races::getRace(i) + "_comprehend");
				languageName = String(language + Races::getRace(i) + "_comprehend");
			}

			if (player->getSkill(skillName) == NULL) {
				player->addSkillMod(languageName, 100, true);
			}

		}

		if (player->getSkill(socialLanguage + "lekku_comprehend") == NULL)
			player->addSkillMod(language + "lekku_comprehend", 100, updateClient);
	}*/

	//player->setPlayerLevel(updateClient);

	return true;
}

bool ProfessionManager::trainSkillBox(const String& skillBox, PlayerCreature* player, bool updateClient) {
	SkillBox* sBox = skillBoxMap.get(skillBox);

	if (sBox != NULL)
		return trainSkillBox(sBox, player, updateClient);
	else {
		return false;
	}
}

/*bool ProfessionManager::loseJediSkillBox(PlayerImplementation* player, bool updateClient) {
	SortedVector<SkillBox*> removable;
	for (int i = 0; i < player->skillBoxesToSave.size(); i++) {
		if (player->skillBoxesToSave.get(i)->getName().indexOf("force_discipline_") >= 0)
			removable.add(player->skillBoxesToSave.get(i));
	}
	// this gives us a good approximation, but sometimes required skills make it into skillBoxesToSave. We must check for those.

	// it is safe to only loop through the removable stuff since the only required skills for jedi skills are jedi skills
	SortedVector<SkillBox*> required;
	for (int i = 0; i < removable.size(); i++)
		for (int j = 0; j < removable.size(); j++)
			if (removable.get(i)->requiredSkills.contains(removable.get(j)))
				required.add(removable.get(j));

	for (int i = 0; i < required.size(); i++)
		removable.drop(required.get(i));

	if (System::random(2) == 2) {
		int r = System::random(removable.size() - 1);
		if (r < removable.size() && removable.size() > 0)
			surrenderSkillBox(removable.get(r), player, updateClient);
	}
	return true;
}
*/

bool ProfessionManager::checkRequisitesToSurrender(SkillBox* skillBox, PlayerCreature* player) {
	SkillBoxList* playerSkillBoxList = player->getSkillBoxList();

	if (!playerSkillBoxList->contains(skillBox)) {
		System::out << "player doesnt contain skill box to surrender" << endl;
		return false;
	}

	if (skillBox->isMasterBox())
		return true;

	Vector<SkillBox*>* children = skillBox->getChildren();

	System::out << "trying to check children..." << endl;

	for (int i = 0; i < children->size(); ++i) {
		SkillBox* box = children->get(i);

		System::out << "checking child box " << box->getName() << endl;

		if (playerSkillBoxList->contains(box))
			return false;
	}

	return true;
}

bool ProfessionManager::surrenderSkillBox(SkillBox* skillBox, PlayerCreature* player, bool updateClient) {
	if (!checkRequisitesToSurrender(skillBox, player))
		return false;

	player->removeSkillBox(skillBox, updateClient);
	player->addSkillPoints(-skillBox->getSkillPointsRequired());

	PlayerObject* playerObject = (PlayerObject*) player->getSlottedObject("ghost");

	playerObject->removeSkills(skillBox->skillCommands, updateClient);
	playerObject->removeSkills(skillBox->skillCertifications, updateClient);

	removeSkillMods(skillBox, player, updateClient);
	removeDraftSchematics(skillBox, player, updateClient);


	/*

	if (skillBox->getName().compareTo("combat_smuggler_underworld_01") == 0) {
		//int race = Races::getRaceID(player->getRaceFileName());

		String socialLanguage = "social_language_";
		String language = "language_";

		for (int i = 1; i < 10 ; i++) {

			String skillName;
			String languageName;

			if (i == 6) {
				skillName = String(socialLanguage + "moncalamari_comprehend");
				languageName = String(language + "moncalamari_comprehend");
			} else {
				skillName = String(socialLanguage + Races::getRace(i) + "_comprehend");
				languageName = String(language + Races::getRace(i) + "_comprehend");
			}

			if (player->getSkill(skillName) == NULL) {
				player->removeSkillMod(languageName, true);
			}

		}

		if (player->getSkill(socialLanguage + "lekku_comprehend") == NULL)
			player->removeSkillMod(language + "lekku_comprehend", true);
	}

	player->setPlayerLevel(updateClient);*/

	return true;

}

bool ProfessionManager::surrenderSkillBox(const String& skillBox, PlayerCreature* player, bool updateClient) {
	SkillBox* sBox = skillBoxMap.get(skillBox);

	if (sBox != NULL) {
		return surrenderSkillBox(sBox, player, updateClient);
	}

	return false;
}
/*
void ProfessionManager::surrenderAll(PlayerImplementation* player) {
	while (player->skillBoxesToSave.size() > 0) {
		surrenderSkillBox(player->skillBoxesToSave.get(0), player, false);
	}

	player->sendTo(player->_this);
}*/

void ProfessionManager::loadProfessionsFromDatabase() {
	info("Loading professions...", true);

	lock();

	ResultSet* result;

	StringBuffer query;
	query << "SELECT * FROM skills";

	result = ServerDatabase::instance()->executeQuery(query);

	if (!result->next()) {
		StringBuffer msg;
		msg << "No Skills in Database";

		unlock();
		throw Exception(msg.toString());
	}

	while (result->next()) {
		bool isProfession = result->getInt(6);

		String name = String(result->getString(1));

		bool isSpecies = (name.indexOf("species_") != -1);
		bool isLanguage = (name.indexOf("social_language_") != -1);

		if (isProfession) {
			Profession* prof = loadProfession(result);
			if (prof != NULL)
				if (!professionMap.containsKey(prof->getName()))
					professionMap.put(prof->getName(), prof);
		} else if (isSpecies || isLanguage)
			loadSkillBox(result, NULL);

	}

	delete result;

	for (int i = 0; i < skillBoxMap.size(); i++) {
		SkillBox* sBox = skillBoxMap.get(i);

		for (int i = 0; i < sBox->skillRequirements.size(); i++) {
			String box = sBox->skillRequirements.get(i);

			SkillBox* requiredSkillBox = skillBoxMap.get(box);
			sBox->requiredSkills.add(requiredSkillBox);
		}
	}

	unlock();

	info("Loaded " + String::valueOf(professionMap.size()) + " professions", true);
	info("Loaded " + String::valueOf(skillBoxMap.size()) + " skill boxes", true);

}

Profession* ProfessionManager::loadProfession(ResultSet* result) {
	String name = result->getString(1);
	Profession* profession = NULL;

	String skillGraphType = result->getString(3);

	if (skillGraphType.compareTo("fourByFour") == 0) {
		FourByFourProfession* fourByFourProfession = new FourByFourProfession(name);

		if (result->next())
			fourByFourProfession->setNoviceBox(loadSkillBox(result, (Profession*) fourByFourProfession));

		if (result->next())
			fourByFourProfession->setMasterBox(loadSkillBox(result, (Profession*) fourByFourProfession));

		if (!professionMap.containsKey(name))
			professionMap.put(name, fourByFourProfession);

		for (int i = 1; i <= 4; i++) {
			for (int j = 1; j <= 4; j++) {
				if (!result->next()) {
					StringBuffer msg;
					msg << "Missing SkillBoxes for " << name << " Profession";

					throw Exception(msg.toString());
				}

				SkillBox* skillBox = loadSkillBox(result, (Profession*) fourByFourProfession);
				fourByFourProfession->setBox(i, j, skillBox);
			}
		}

		profession = (Profession*) fourByFourProfession;
	} else if (skillGraphType.compareTo("oneByFour") == 0) {
		OneByFourProfession* oneByFourProfession = new OneByFourProfession(name);

		if (result->next())
			oneByFourProfession->setNoviceBox(loadSkillBox(result, (Profession*)oneByFourProfession));

		if (result->next())
			oneByFourProfession->setMasterBox(loadSkillBox(result, (Profession*)oneByFourProfession));

		if (!professionMap.containsKey(name))
			professionMap.put(name, oneByFourProfession);

		for (int i = 1; i <= 4; i++) {
			if (!result->next()) {
					StringBuffer msg;
					msg << "Missing SkillBoxes for " << name << " Profession";

					throw Exception(msg.toString());
			}

			SkillBox* skillBox = loadSkillBox(result, (Profession*)oneByFourProfession);
			oneByFourProfession->setBox(i, skillBox);
		}

		profession = (Profession*)oneByFourProfession;
	} else if (skillGraphType.compareTo("pyramid") == 0) {
		PyramidProfession* pyramidProfession = new PyramidProfession(name);

		if (result->next())
			pyramidProfession->setNoviceBox(loadSkillBox(result, (Profession*)pyramidProfession));

		if (result->next())
			pyramidProfession->setMasterBox(loadSkillBox(result, (Profession*)pyramidProfession));

		if (!professionMap.containsKey(name))
			professionMap.put(name, pyramidProfession);

		for (int i = 1; i <= 10; i++) {
			if (!result->next()) {
					StringBuffer msg;
					msg << "Missing SkillBoxes for " << name << " Profession";

					throw Exception(msg.toString());
			}

			SkillBox* skillBox = loadSkillBox(result, (Profession*)pyramidProfession);
			pyramidProfession->setBox(i, skillBox);
		}

		profession = (Profession*)pyramidProfession;
	}
	return profession;
}

SkillBox* ProfessionManager::loadBox(const String& name, Profession* profession) {
	SkillBox* box = NULL;

	StringBuffer query;
	query << "SELECT * FROM skills WHERE skill_name = '" << name << "'";

	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

	if (!result->next()) {
		StringBuffer msg;
		msg << "Skill " << name << " not found in database";

		throw Exception(msg.toString());
	}

	bool isProfession = result->getInt(6);

	if (!isProfession)
		box = loadSkillBox(result, profession);

	delete result;

	return box;
}

SkillBox* ProfessionManager::loadSkillBox(ResultSet* result, Profession* profession) {
	String name = result->getString(1);

	if (skillBoxMap.contains(name))
		return skillBoxMap.get(name);

	SkillBox* skillBox = new SkillBox(name, result->getInt(0), profession);

	String skillParent = result->getString(2);

	if (skillParent.length() > 1) {
		SkillBox* parent = skillBoxMap.get(skillParent);

		if (parent == NULL) {
			Profession* profession = professionMap.get(skillParent);

			if (profession != NULL) {
				parent = profession->getNoviceBox();
			}
		}

		if (parent != NULL) {
			info(skillParent + " found");

			skillBox->setParent(parent);
			parent->addChild(skillBox);
		} else {
			info("parent not found " + skillParent);
		}
	}

	skillBox->setSkillGodOnly(result->getInt(4));
	skillBox->setSkillIsTitle(result->getInt(5));
	skillBox->setSkillIsHidden(result->getInt(7));
	skillBox->setSkillMoneyRequired(result->getInt(8));
	skillBox->setSkillPointsRequired(result->getInt(9));

	String skillRequirements = result->getString(11);
	loadSkillRequirements(skillBox, skillRequirements);

	String skillPreclusions = result->getString(12);
	loadSkillPreclusions(skillBox, skillPreclusions);

	skillBox->setSkillXpType(result->getString(13));
	skillBox->setSkillXpCost(result->getInt(14));
	skillBox->setSkillXpCap(result->getInt(15));

	String skillSpeciesRequired = result->getString(19);
	loadSkillSpeciesRequired(skillBox, skillSpeciesRequired);

	skillBox->setSkillJediStateRequired(result->getString(20));

	String skillCommands = result->getString(22);
	loadSkillCommands(skillBox, skillCommands);

	String skillMods = result->getString(23);
	loadSkillMods(skillBox, skillMods);

	String grantedDraftSchematics = result->getString(24);
	loadDraftSchematics(skillBox, grantedDraftSchematics);

	skillBox->setSkillIsSearchable(result->getInt(26));

	skillBoxMap.put(skillBox->getName(), skillBox);

	return skillBox;
}

void ProfessionManager::loadSkillRequirements(SkillBox* skillBox, String& skillRequirements) {
	if (skillRequirements.length() > 1) {
		StringTokenizer tokenizer(skillRequirements);
		tokenizer.setDelimeter(",");

		while (tokenizer.hasMoreTokens()) {
			String skill;
			tokenizer.getStringToken(skill);

			skillBox->addRequirementSkill(skill);
		}
	}
}

void ProfessionManager::loadSkillPreclusions(SkillBox* skillBox, String& skillPreclusions) {
	if (skillPreclusions.length() > 1) {
		StringTokenizer tokenizer(skillPreclusions);
		tokenizer.setDelimeter(",");

		while (tokenizer.hasMoreTokens()) {
			String skill;
			tokenizer.getStringToken(skill);

			skillBox->addPreclusionSkill(skill);
		}
	}
}

void ProfessionManager::loadSkillSpeciesRequired(SkillBox* skillBox, String& skillSpeciesRequired) {
	if (skillSpeciesRequired.length() > 1) {
		StringTokenizer tokenizer(skillSpeciesRequired);
		tokenizer.setDelimeter(",");

		while (tokenizer.hasMoreTokens()) {
			String race;
			tokenizer.getStringToken(race);

			skillBox->addRequiredSpecies(race);
		}
	}
}

void ProfessionManager::loadSkillCommands(SkillBox* skillBox, String& skillCommands) {
	if (skillCommands.length() > 1) {
		StringTokenizer tokenizer(skillCommands);
		tokenizer.setDelimeter(",");

		while (tokenizer.hasMoreTokens()) {
			String command;
			tokenizer.getStringToken(command);

			command = command.toLowerCase();

			int idx = command.indexOf("cert_");
			if (idx != -1) {
				Certification* cert = certificationMap.get(command);

				if (cert == NULL) {
					cert = new Certification(command);

					certificationMap.put(command, cert);
				}

				skillBox->skillCertifications.add(cert);
			} else {
				QueueCommand* skill = objectController->getQueueCommand(command);

				if (skill != NULL)
					skillBox->addSkillCommand(skill);
			}
		}
	}
}

void ProfessionManager::loadSkillMods(SkillBox* skillBox, String& skillMods) {
	if (skillMods.length() > 1) {
		StringTokenizer tokenizer(skillMods);
		tokenizer.setDelimeter(",");

		while (tokenizer.hasMoreTokens()) {
			String skillMod;
			tokenizer.getStringToken(skillMod);

			int index = skillMod.indexOf("=");
			String skillModName = skillMod.subString(0, index);
			int value = Integer::valueOf(skillMod.subString(index + 1, skillMod.length()));

			skillBox->addSkillMod(skillModName, value);
		}
	}
}

void ProfessionManager::loadDraftSchematics(SkillBox* skillBox, String& grantedDraftSchematics) {
	if (grantedDraftSchematics.length() > 1) {
		StringTokenizer tokenizer(grantedDraftSchematics);
		tokenizer.setDelimeter(",");

		while (tokenizer.hasMoreTokens()) {
			String draftSchematic;
			tokenizer.getStringToken(draftSchematic);

			skillBox->addGrantedSchematic(draftSchematic);
		}
	}
}

Skill* ProfessionManager::getSkill(const String& name) {
	Skill* skill = certificationMap.get(name);

	if (skill == NULL)
		skill = objectController->getQueueCommand(name);

	return skill;
}

uint8 ProfessionManager::getLangFromRace(int race) {

	switch(race) {
	case 0:
	case 10:
		return 0x01;
		break;
	case 1:
	case 11:
		return 0x03;
		break;
	case 2:
	case 12:
		return 0x07;
		break;
	case 3:
	case 13:
		return 0x06;
		break;
	case 4:
	case 14:
		return 0x08;
		break;
	case 5:
	case 15:
		return 0x02;
		break;
	case 6:
	case 16:
		return 0x04;
		break;
	case 7:
	case 17:
		return 0x05;
		break;
	case 8:
	case 18:
		return 0x0B;
		break;
	case 9:
	case 19:
		return 0x0A;
		break;
	default:
		return 1;
	}

	return 1;
}
