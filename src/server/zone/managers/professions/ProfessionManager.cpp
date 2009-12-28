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
#include "../../ZoneServer.h"

//#include "../../objects/player/badges/Badge.h"
#include "../../objects/creature/professions/SkillBox.h"
#include "../../objects/creature/professions/FourByFourProfession.h"
#include "../../objects/creature/professions/OneByFourProfession.h"
#include "../../objects/creature/professions/PyramidProfession.h"


ProfessionManager::ProfessionManager(ObjectController* controller)
	: Mutex("Profession Manager"), Logger("ProfessionManager") {

	objectController = controller;
	//server = serv;
	//skillManager = new SkillManager(this);

	skillBoxMap.setNullValue(NULL);
	certificationMap.setNullValue(NULL);

	setGlobalLogging(true);
	setLogging(false);

	loadProfessionsFromDatabase();
}

ProfessionManager::~ProfessionManager() {
	for (int i = 0; i < skillBoxMap.size(); ++i)
		delete skillBoxMap.get(i);

	for (int i = 0; i < certificationMap.size(); ++i)
		delete certificationMap.get(i);

	professionMap.resetIterator();

	while (professionMap.hasNext())
		delete professionMap.getNextValue();
}

/*void ProfessionManager::loadProfessions(PlayerImplementation* player) {
	SkillBox* skillBox;
	String box;

	StringBuffer query;
	query << "SELECT professions FROM characters WHERE character_id = " << player->characterID;

	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

	if (!result->next()) {
		StringBuffer msg;
		msg << "unknown character ID" << player->characterID;

		throw Exception(msg.toString());
	}

	String professions = result->getString(0);

	delete result;

	String decodedData;
	BinaryData decodedProfession(professions);
	decodedProfession.decode(decodedData);

	if (decodedData.length() == 0)
		return;

	uint16* data = (uint16*)decodedData.toCharArray();
	uint16 size = *data;
	data++;

	for (int i = 0; i < size; i++) {
		uint16 idx = *data;

		skillBox = skillBoxMap.get(idx);
		if (skillBox == NULL) {
			StringBuffer msg;
			msg << "Invalid SkillBox when loading professions for character:" << player->characterID;

			throw Exception(msg.toString());
		}

		skillManager->loadSkillBox(skillBox, player, true);
		player->skillBoxesToSave.put(skillBox);

		data++;
	}

	loadDefaultSkills(player);
}

void ProfessionManager::loadDefaultSkills(PlayerImplementation* player) {
	// Load default skills..
	Skill* defaultAttackSkill = skillManager->getSkill("attack");
	Skill* throwGrenade = skillManager->getSkill("throwgrenade");

	if (defaultAttackSkill != NULL)
		player->creatureSkills.put(defaultAttackSkill->getNameCRC(), defaultAttackSkill);

	if (throwGrenade != NULL)
		player->creatureSkills.put(throwGrenade->getNameCRC(), throwGrenade);
}

void ProfessionManager::saveProfessions(PlayerImplementation* player) {
	int size = player->skillBoxesToSave.size();

	if (size > 40) {
		StringBuffer msg;
		msg << "SkillBoxes overflow when saving professions for character:" << player->characterID;

		for (int i = 0; i < size; i++) {
			SkillBox* sBox = player->skillBoxesToSave.get(i);
			System::out << i << ": " << sBox->getName() << "\n";
		}

		throw Exception(msg.toString());
	}

	uint16* data = new uint16[size + 1];
	data[0] = (uint16)size;

	for (int i = 0; i < size; i++) {
		SkillBox* sBox = player->skillBoxesToSave.get(i);
	 	int pos = skillBoxMap.find(sBox->getName());
		data[i+1] = (uint16)pos;
	}

	String professionData((char*)data, (size + 1) * 2);

	String encodedData;
	BinaryData profession(professionData);
	profession.encode(encodedData);

	StringBuffer query;
	query << "UPDATE characters SET "
          << "professions ='" << encodedData.subString(0, encodedData.length() - 1)
          << "' WHERE character_id=" << player->characterID << ";";

	ServerDatabase::instance()->executeStatement(query.toString());

	delete [] data;
}

bool ProfessionManager::trainSkillBox(SkillBox* skillBox, PlayerImplementation* player, bool updateClient) {
	if (player->skillBoxes.containsKey(skillBox->getName()))
		return false;

	if ((player->skillPoints + skillBox->skillPointsRequired) > 250)
		return false;

	for (int i = 0; i < skillBox->requiredSkills.size(); i++) {
		SkillBox* sBox = skillBox->requiredSkills.get(i);
		if (!player->skillBoxes.containsKey(sBox->getName()))
			return false;
	}

	for (int i = 0; i < skillBox->requiredSkills.size(); i++)
		player->skillBoxesToSave.drop(skillBox->requiredSkills.get(i));

	player->skillBoxesToSave.put(skillBox);

	skillManager->loadSkillBox(skillBox, player, false, updateClient);

	if (skillBox->isMasterBox()) {
		player->awardBadge(Badge::getID(skillBox->getName()));
	}

	if (skillBox->getName().compareTo("combat_smuggler_underworld_01") == 0) {

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
			player->addSkillMod(language + "lekku_comprehend", 100, true);
	}

	player->setPlayerLevel(updateClient);

	return true;
}

bool ProfessionManager::trainSkillBox(const String& skillBox, PlayerImplementation* player, bool updateClient) {
	SkillBox* sBox = skillBoxMap.get(skillBox);

	if (sBox != NULL)
		return trainSkillBox(sBox, player, updateClient);
	else
		return false;
}

bool ProfessionManager::loseJediSkillBox(PlayerImplementation* player, bool updateClient) {
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

bool ProfessionManager::surrenderSkillBox(SkillBox* skillBox, PlayerImplementation* player, bool updateClient) {
	if (!player->skillBoxesToSave.contains(skillBox)) {
		return false;
	} else {
		skillManager->removeSkillBox(skillBox, player, updateClient);

		player->skillBoxesToSave.drop(skillBox);

		for (int i = 0; i < skillBox->requiredSkills.size(); i++) {
			SkillBox* sBox = skillBox->requiredSkills.get(i);
			player->skillBoxesToSave.put(sBox);
		}

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

		player->setPlayerLevel(updateClient);

		return true;
	}
}

bool ProfessionManager::surrenderSkillBox(const String& skillBox, PlayerImplementation* player, bool updateClient) {
	SkillBox* sBox = skillBoxMap.get(skillBox);

	if (sBox != NULL) {
		return surrenderSkillBox(sBox, player, updateClient);
	}

	return false;
}

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

SkillBox* ProfessionManager::loadSkillBox(ResultSet* result, Profession* profession) {
	SkillBox* skillBox = new SkillBox(result->getString(1), result->getInt(0), profession);

	String skillParent = result->getString(2);

	if (skillParent.length() > 1) {
		SkillBox* parent = skillBoxMap.get(skillParent);
		if (parent != NULL) {
			skillBox->setParent(parent);
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

