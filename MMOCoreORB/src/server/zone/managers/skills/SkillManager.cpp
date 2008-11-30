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

#include "SkillManager.h"
#include "../player/ProfessionManager.h"

#include "../../objects/player/professions/SkillBox.h"

#include "../../objects/player/Player.h"
#include "../../objects/player/PlayerImplementation.h"

#include "ScriptAttacksManager.h"
#include "../../ZoneProcessServerImplementation.h"

#include "performance/PerformanceManager.h"
#include "imagedesign/CustomizationManager.h"

SkillManager::SkillManager(ProfessionManager* profManager) {
	professionManager = profManager;
	scr = new ScriptAttacksManager(profManager->getZoneProcessServer());

	bool load = scr->loadSkillsFile(&combatActions);

	performanceManager = new PerformanceManager();
	customizationManager = new CustomizationManager();
}

SkillManager::~SkillManager() {
	delete performanceManager;
	delete customizationManager;

	delete scr;

	combatActions.resetIterator();

	while (combatActions.hasNext())
		delete combatActions.getNextValue();
}

void SkillManager::loadSkillBox(SkillBox* skillBox, PlayerImplementation* player, bool loadRequirements, bool updateClient) {
	if (player == NULL || skillBox == NULL)
		return;

	if (player->skillBoxes.containsKey(skillBox->getName()))
		return;

	SkillBox* skillBoxReq = NULL;

	player->addSkillBox(skillBox, updateClient);
	player->addSkillPoints(skillBox->getSkillPointsRequired());

	if (skillBox->getSkillXpType().length() > 1)
		player->addXp(skillBox->getSkillXpType(), skillBox->getSkillXpCost(), updateClient);

	loadSkillCommands(skillBox, player, updateClient);
	loadSkillCertifications(skillBox, player, updateClient);
	loadSkillMods(skillBox, player, updateClient);
	loadDraftSchematics(skillBox, player, updateClient);

	if (!loadRequirements)
		return;

	for (int i = 0; i < skillBox->requiredSkills.size(); i++) {
		skillBoxReq = skillBox->requiredSkills.get(i);
		loadSkillBox(skillBoxReq, player, true);
	}
}

void SkillManager::loadSkillCommands(SkillBox* skillBox, PlayerImplementation* player, bool updateClient) {
	if (player == NULL || skillBox == NULL)
		return;

	player->addSkills(skillBox->skillCommands, updateClient);
}

void SkillManager::loadSkillCertifications(SkillBox* skillBox, PlayerImplementation* player, bool updateClient) {
	if (player == NULL || skillBox == NULL)
		return;

	player->addCertifications(skillBox->skillCertifications, updateClient);
}

void SkillManager::loadSkillMods(SkillBox* skillBox, PlayerImplementation* player, bool updateClient) {
	if (player == NULL || skillBox == NULL)
		return;

	skillBox->skillMods.resetIterator();

	while (skillBox->skillMods.hasNext()) {
		String skillMod;
		int value = 0;

		skillBox->skillMods.getNextKeyAndValue(skillMod, value);
		player->addSkillMod(skillMod, value, updateClient);
	}
}

void SkillManager::loadDraftSchematics(SkillBox* skillBox, PlayerImplementation* player, bool updateClient) {
	if (player == NULL || skillBox == NULL)
		return;

	for (int i = 0; i < skillBox->getGrantedSchematicListSize(); i++) {

		String schematicGroupName = "";
		skillBox->getGrantedSchematic(schematicGroupName, i);
		player->addDraftSchematicsFromGroupName(schematicGroupName);
	}

	if (updateClient)
		player->sendDraftSchematics();
}

void SkillManager::removeSkillBox(SkillBox* skillBox, PlayerImplementation* player, bool updateClient) {
	if (!player->skillBoxes.containsKey(skillBox->getName()))
		return;

	player->removeSkillBox(skillBox, updateClient);
	player->removeSkillPoints(skillBox->getSkillPointsRequired());

	if (skillBox->getSkillXpType().length() > 1)
		player->addXp(skillBox->getSkillXpType(), -skillBox->getSkillXpCost(), updateClient);

	removeSkillCommands(skillBox, player, false);
	removeSkillCertifications(skillBox, player, updateClient);
	removeSkillMods(skillBox, player, updateClient);
	removeGrantedDraftSchematics(skillBox, player, updateClient);
}

void SkillManager::removeSkillCommands(SkillBox* skillBox, PlayerImplementation* player, bool updateClient) {
	if (player == NULL || skillBox == NULL)
		return;

	player->removeSkills(skillBox->skillCommands, updateClient);
}

void SkillManager::removeSkillCertifications(SkillBox* skillBox, PlayerImplementation* player, bool updateClient) {
	if (player == NULL || skillBox == NULL)
		return;

	player->removeCertifications(skillBox->skillCertifications, updateClient);
}

void SkillManager::removeSkillMods(SkillBox* skillBox, PlayerImplementation* player, bool updateClient) {
	if (player == NULL || skillBox == NULL)
		return;

	skillBox->skillMods.resetIterator();

	while (skillBox->skillMods.hasNext()) {
		String skillMod;
		int value = 0;

		skillBox->skillMods.getNextKeyAndValue(skillMod, value);

		player->addSkillMod(skillMod, -value, updateClient);
	}
}

void SkillManager::removeGrantedDraftSchematics(SkillBox* skillBox, PlayerImplementation* player, bool updateClient) {
	if (player == NULL || skillBox == NULL)
		return;

	for (int i = 0; i < skillBox->getGrantedSchematicListSize(); i++) {

		String schematicGroupName = "";
		skillBox->getGrantedSchematic(schematicGroupName, i);
		player->subtractDraftSchematicsFromGroupName(schematicGroupName);
	}

	if (updateClient)
		player->sendDraftSchematics();
}

void SkillManager::loadSkills(CreatureObject* creature) {
}

Skill* SkillManager::getSkill(const String& name) {
	return combatActions.getSkill(name);
}

Performance* SkillManager::getDance(const String& name) {
	if (performanceManager == NULL)
		return NULL;

	return performanceManager->getDance(name);
}

Performance* SkillManager::getSong(const String& name, int instrumentType) {
	if (performanceManager == NULL)
		return NULL;

	return performanceManager->getSong(name, instrumentType);
}

CustomizationData* SkillManager::getCustomizationData(const String& speciesGender, const String& customizationName) {
	if (customizationManager == NULL)
		return NULL;

	return customizationManager->getCustomizationData(speciesGender, customizationName);
}
