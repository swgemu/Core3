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
#include "SkillModManager.h"
#include "PerformanceManager.h"
#include "imagedesign/ImageDesignManager.h"
#include "server/zone/objects/creature/variables/Skill.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/badges/Badge.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableRow.h"
#include "server/zone/managers/crafting/schematicmap/SchematicMap.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage4.h"

SkillManager::SkillManager()
		: Logger("SkillManager") {

	rootNode = new Skill();

	performanceManager = new PerformanceManager();

	loadClientData();
}

SkillManager::~SkillManager() {
}

void SkillManager::loadClientData() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/skill/skills.iff");

	if (iffStream == NULL) {
		error("Could not load skills.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	delete iffStream;

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);

		Reference<Skill*> skill = new Skill();
		skill->parseDataTableRow(row);

		Skill* parent = skillMap.get(skill->getParentName());

		if (parent == NULL)
			parent = rootNode;

		parent->addChild(skill);

		if (skillMap.put(skill->getSkillName(), skill) != NULL) {
			error("overwriting skill name");

			assert(0 && "skill name hashcode error");
		}

		//Load the abilities of the skill into the ability map.
		Vector<String> commands = skill->commands;

		for (int i = 0; i < commands.size(); ++i) {
			String command = commands.get(i);

			if (!abilityMap.containsKey(command)) {
				abilityMap.put(command, new Ability(command));
			}
		}
	}

	//If the admin ability isn't in the ability map, then we want to add it manually.
	if (!abilityMap.containsKey("admin"))
		abilityMap.put("admin", new Ability("admin"));

	loadXpLimits();

	info("Successfully loaded " + String::valueOf(skillMap.size()) + " skills and " + String::valueOf(abilityMap.size()) + " abilities.", true);
}

void SkillManager::loadXpLimits() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/skill/xp_limits.iff");

	if (iffStream == NULL) {
		error("Could not load skills.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	delete iffStream;

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);

		String type;
		int value;
		row->getValue(0, type);
		row->getValue(1, value);
		defaultXpLimits.put(type, value);
		info(type + ": " + String::valueOf(value));
	}
}

void SkillManager::addAbility(PlayerObject* ghost, const String& abilityName, bool notifyClient) {
	Ability* ability = abilityMap.get(abilityName);

	if (ability != NULL)
		ghost->addAbility(ability, notifyClient);
}

void SkillManager::removeAbility(PlayerObject* ghost, const String& abilityName, bool notifyClient) {
	Ability* ability = abilityMap.get(abilityName);

	if (ability != NULL)
		ghost->removeAbility(ability, notifyClient);
}

void SkillManager::addAbilities(PlayerObject* ghost, Vector<String>& abilityNames, bool notifyClient) {
	Vector<Ability*> abilities;

	for (int i = 0; i < abilityNames.size(); ++i) {
		String abilityName = abilityNames.get(i);

		Ability* ability = abilityMap.get(abilityName);

		if (ability != NULL && !ghost->hasAbility(abilityName))
			abilities.add(ability);
	}

	ghost->addAbilities(abilities, notifyClient);
}

void SkillManager::removeAbilities(PlayerObject* ghost, Vector<String>& abilityNames, bool notifyClient) {
	Vector<Ability*> abilities;

	for (int i = 0; i < abilityNames.size(); ++i) {
		String abilityName = abilityNames.get(i);

		Ability* ability = abilityMap.get(abilityName);

		if (ability != NULL && ghost->hasAbility(abilityName))
			abilities.add(ability);
	}

	ghost->removeAbilities(abilities, notifyClient);
}

/*bool SkillManager::checkPrerequisiteSkill(const String& skillName, CreatureObject* creature) {
	return true;
}*/

bool SkillManager::awardSkill(const String& skillName, CreatureObject* creature, bool notifyClient, bool awardRequiredSkills, bool noXpRequired) {
	Skill* skill = skillMap.get(skillName);

	if (skill == NULL)
		return false;

	Locker locker(creature);

	//Check for required skills.
	Vector<String>* requiredSkills = skill->getSkillsRequired();
	for (int i = 0; i < requiredSkills->size(); ++i) {
		String requiredSkillName = requiredSkills->get(i);
		Skill* requiredSkill = skillMap.get(requiredSkillName);

		if (requiredSkill == NULL)
			continue;

		if (awardRequiredSkills)
			awardSkill(requiredSkillName, creature, notifyClient, awardRequiredSkills, noXpRequired);

		if (!creature->hasSkill(requiredSkillName))
			return false;
	}

	if (!canLearnSkill(skillName, creature, noXpRequired)) {
		return false;
	}

	//If they already have the skill, then return true.
	if (creature->hasSkill(skillName))
		return true;

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	if (ghost != NULL) {
		//Withdraw skill points.
		ghost->addSkillPoints(-skill->getSkillPointsRequired());

		//Witdraw experience.
		if (!noXpRequired) {
			ghost->addExperience(skill->getXpType(), -skill->getXpCost(), true);
		}

		creature->addSkill(skill, notifyClient);

		//Add skill modifiers
		VectorMap<String, int>* skillModifiers = skill->getSkillModifiers();

		for (int i = 0; i < skillModifiers->size(); ++i) {
			VectorMapEntry<String, int>* entry = &skillModifiers->elementAt(i);
			creature->addSkillMod(SkillModManager::SKILLBOX, entry->getKey(), entry->getValue(), notifyClient);

		}

		//Add abilities
		Vector<String>* abilityNames = skill->getAbilities();
		addAbilities(ghost, *abilityNames, notifyClient);

		//Add draft schematic groups
		Vector<String>* schematicsGranted = skill->getSchematicsGranted();
		SchematicMap::instance()->addSchematics(ghost, *schematicsGranted, notifyClient);

		//Update maximum experience.
		updateXpLimits(ghost);


		// Update Force Power Max and Regen.
		ghost->setForcePowerMax(creature->getSkillMod("jedi_force_power_max"), true);
		ghost->setForcePowerRegen(creature->getSkillMod("jedi_force_power_regen"));

		if (skillName.contains("master")) {
			uint32 badge = Badge::getID(skillName);

			if (badge == -1 && skillName == "crafting_shipwright_master") {
				badge = Badge::getID("crafting_shipwright");
			}

			if (badge != -1) {
				ManagedReference<PlayerManager*> playerManager = creature->getZoneServer()->getPlayerManager();

				if (playerManager != NULL) {
					playerManager->awardBadge(ghost, badge);
				}
			}
		}
	}

	/// Update client with new values for things like Terrain Negotiation
	CreatureObjectDeltaMessage4* msg4 = new CreatureObjectDeltaMessage4(creature);
	msg4->updateAccelerationMultiplierBase();
	msg4->updateAccelerationMultiplierMod();
	msg4->updateSpeedMultiplierBase();
	msg4->updateSpeedMultiplierMod();
	msg4->updateRunSpeed();
	msg4->updateTerrainNegotiation();
	msg4->close();
	creature->sendMessage(msg4);

	SkillModManager::instance()->verifySkillBoxSkillMods(creature);

	return true;
}

bool SkillManager::surrenderSkill(const String& skillName, CreatureObject* creature, bool notifyClient) {
	Skill* skill = skillMap.get(skillName);

	if (skill == NULL)
		return false;

	Locker locker(creature);

	//If they already have the skill, then return true.
	if (!creature->hasSkill(skillName))
		return true;

	SkillList* skillList = creature->getSkillList();

	for (int i = 0; i < skillList->size(); ++i) {
		Skill* checkSkill = skillList->get(i);

		if (checkSkill->isRequiredSkillOf(skill))
			return false;
	}

	creature->removeSkill(skill, notifyClient);

	//Remove skill modifiers
	VectorMap<String, int>* skillModifiers = skill->getSkillModifiers();

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	for (int i = 0; i < skillModifiers->size(); ++i) {
		VectorMapEntry<String, int>* entry = &skillModifiers->elementAt(i);
		creature->removeSkillMod(SkillModManager::SKILLBOX, entry->getKey(), entry->getValue(), notifyClient);

	}

	if (ghost != NULL) {
		//Give the player the used skill points back.
		ghost->addSkillPoints(skill->getSkillPointsRequired());

		//Remove abilities
		Vector<String>* abilityNames = skill->getAbilities();
		removeAbilities(ghost, *abilityNames, notifyClient);

		//Remove draft schematic groups
		Vector<String>* schematicsGranted = skill->getSchematicsGranted();
		SchematicMap::instance()->removeSchematics(ghost, *schematicsGranted, notifyClient);

		//Update maximum experience.
		updateXpLimits(ghost);

		/// Update Force Power Max and Regen
		ghost->setForcePowerMax(creature->getSkillMod("jedi_force_power_max"), true);
		ghost->setForcePowerRegen(creature->getSkillMod("jedi_force_power_regen"));

	}

	/// Update client with new values for things like Terrain Negotiation
	CreatureObjectDeltaMessage4* msg4 = new CreatureObjectDeltaMessage4(creature);
	msg4->updateAccelerationMultiplierBase();
	msg4->updateAccelerationMultiplierMod();
	msg4->updateSpeedMultiplierBase();
	msg4->updateSpeedMultiplierMod();
	msg4->updateRunSpeed();
	msg4->updateTerrainNegotiation();
	msg4->close();
	creature->sendMessage(msg4);

	SkillModManager::instance()->verifySkillBoxSkillMods(creature);

	return true;
}

void SkillManager::surrenderAllSkills(CreatureObject* creature, bool notifyClient) {
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	SkillList* skillList = creature->getSkillList();

	while (skillList->size() > 0) {
		Skill* skill = skillList->get(0);

		creature->removeSkill(skill, notifyClient);

		//Remove skill modifiers
		VectorMap<String, int>* skillModifiers = skill->getSkillModifiers();

		for (int i = 0; i < skillModifiers->size(); ++i) {
			VectorMapEntry<String, int>* entry = &skillModifiers->elementAt(i);
			creature->removeSkillMod(SkillModManager::SKILLBOX, entry->getKey(), entry->getValue(), notifyClient);

		}

		SkillModManager::instance()->verifySkillBoxSkillMods(creature);

		if (ghost != NULL) {
			//Give the player the used skill points back.
			ghost->addSkillPoints(skill->getSkillPointsRequired());

			//Remove abilities
			Vector<String>* abilityNames = skill->getAbilities();
			removeAbilities(ghost, *abilityNames, notifyClient);

			//Remove draft schematic groups
			Vector<String>* schematicsGranted = skill->getSchematicsGranted();
			SchematicMap::instance()->removeSchematics(ghost, *schematicsGranted, notifyClient);

			/// update force
			ghost->setForcePowerMax(creature->getSkillMod("jedi_force_power_max"), true);
			ghost->setForcePowerRegen(creature->getSkillMod("jedi_force_power_regen"));
		}
	}
}

void SkillManager::awardDraftSchematics(Skill* skill, PlayerObject* ghost, bool notifyClient) {
	if (ghost != NULL) {
		//Add draft schematic groups
		Vector<String>* schematicsGranted = skill->getSchematicsGranted();
		SchematicMap::instance()->addSchematics(ghost, *schematicsGranted, notifyClient);
	}
}

void SkillManager::updateXpLimits(PlayerObject* ghost) {
	if (ghost == NULL || !ghost->isPlayerObject()) {
		return;
	}

	VectorMap<String, int>* xpTypeCapList = ghost->getXpTypeCapList();

	//Clear all xp limits to the default limits.
	for (int i = 0; i < defaultXpLimits.size(); ++i) {
		String xpType = defaultXpLimits.elementAt(i).getKey();
		int xpLimit = defaultXpLimits.elementAt(i).getValue();

		if (xpTypeCapList->contains(xpType)) {
			xpTypeCapList->get(xpType) = xpLimit;
		} else {
			xpTypeCapList->put(xpType, xpLimit);
		}
	}

	//Iterate over the player skills and update xp limits accordingly.
	CreatureObject* player = cast<CreatureObject*>(ghost->getParentRecursively(SceneObjectType::PLAYERCREATURE));

	if(player == NULL)
		return;

	SkillList* playerSkillBoxList = player->getSkillList();

	for(int i = 0; i < playerSkillBoxList->size(); ++i) {
		Skill* skillBox = playerSkillBoxList->get(i);
		if (xpTypeCapList->contains(skillBox->getXpType()) && (xpTypeCapList->get(skillBox->getXpType()) < skillBox->getXpCap())) {
			xpTypeCapList->get(skillBox->getXpType()) = skillBox->getXpCap();
		}
	}

	//Iterate over the player xp types and cap all xp types to the limits.
	DeltaVectorMap<String, int>* experienceList = ghost->getExperienceList();

	for (int i = 0; i < experienceList->size(); ++i) {
		String xpType = experienceList->getKeyAt(i);
		if (experienceList->get(xpType) > xpTypeCapList->get(xpType)) {
			ghost->addExperience(xpType, xpTypeCapList->get(xpType) - experienceList->get(xpType), true);
		}
	}
}

bool SkillManager::canLearnSkill(const String& skillName, CreatureObject* creature, bool noXpRequired) {
	Skill* skill = skillMap.get(skillName);

	if (skill == NULL) {
		return false;
	}

	//If they already have the skill, then return false.
	if (creature->hasSkill(skillName)) {
		return false;
	}

	if (!fullfillsSkillPrerequisites(skillName, creature)) {
		return false;
	}

	ManagedReference<PlayerObject* > ghost = creature->getPlayerObject();
	if (ghost != NULL) {
		//Check if player has enough xp to learn the skill.
		if (!noXpRequired) {
			if (ghost->getExperience(skill->getXpType()) < skill->getXpCost()) {
				return false;
			}
		}

		//Check if player has enough skill points to learn the skill.
		if (ghost->getSkillPoints() < skill->getSkillPointsRequired()) {
			return false;
		}
	} else {
		//Could not retrieve player object.
		return false;
	}


	return true;
}

bool SkillManager::fullfillsSkillPrerequisitesAndXp(const String& skillName, CreatureObject* creature) {
	if (!fullfillsSkillPrerequisites(skillName, creature)) {
		return false;
	}

	Skill* skill = skillMap.get(skillName);

	if (skill == NULL) {
		return false;
	}

	ManagedReference<PlayerObject* > ghost = creature->getPlayerObject();
	if (ghost != NULL) {
		//Check if player has enough xp to learn the skill.
		if (skill->getXpCost() > 0 && ghost->getExperience(skill->getXpType()) < skill->getXpCost()) {
			return false;
		}
	}

	return true;
}

bool SkillManager::fullfillsSkillPrerequisites(const String& skillName, CreatureObject* creature) {
	Skill* skill = skillMap.get(skillName);

	if (skill == NULL) {
		return false;
	}

	//Check for required skills.
	Vector<String>* requiredSkills = skill->getSkillsRequired();
	for (int i = 0; i < requiredSkills->size(); ++i) {
		String requiredSkillName = requiredSkills->get(i);
		Skill* requiredSkill = skillMap.get(requiredSkillName);

		if (requiredSkill == NULL) {
			continue;
		}

		if (!creature->hasSkill(requiredSkillName)) {
			return false;
		}
	}

	return true;
}
