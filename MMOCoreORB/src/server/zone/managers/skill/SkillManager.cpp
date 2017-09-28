/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
 */

#include "SkillManager.h"
#include "SkillModManager.h"
#include "PerformanceManager.h"
#include "server/zone/objects/creature/variables/Skill.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/badges/Badge.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/jedi/JediManager.h"
#include "templates/manager/TemplateManager.h"
#include "templates/datatables/DataTableIff.h"
#include "templates/datatables/DataTableRow.h"
#include "server/zone/managers/crafting/schematicmap/SchematicMap.h"
#include "server/zone/packets/creature/CreatureObjectDeltaMessage4.h"
#include "server/zone/managers/mission/MissionManager.h"

SkillManager::SkillManager()
: Logger("SkillManager") {

	rootNode = new Skill();

	performanceManager = new PerformanceManager();

	apprenticeshipEnabled = false;
}

SkillManager::~SkillManager() {
	delete performanceManager;
}

int SkillManager::includeFile(lua_State* L) {
	String filename = Lua::getStringParameter(L);
	Lua::runFile("scripts/skills/" + filename, L);

	return 0;
}

int SkillManager::addSkill(lua_State* L) {
	LuaObject obj(L);
	SkillManager::instance()->loadSkill(&obj);
	obj.pop();

	return 0;
}

void SkillManager::loadLuaConfig() {
	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/skill_manager.lua");

	apprenticeshipEnabled = lua->getGlobalByte("apprenticeshipEnabled");

	delete lua;
	lua = NULL;
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

		Skill* parent = skillMap.get(skill->getParentName().hashCode());

		if (parent == NULL)
			parent = rootNode;

		parent->addChild(skill);

		if (skillMap.put(skill->getSkillName().hashCode(), skill) != NULL) {
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

	loadFromLua();

	//If the admin ability isn't in the ability map, then we want to add it manually.
	if (!abilityMap.containsKey("admin"))
		abilityMap.put("admin", new Ability("admin"));

	// These are not listed in skills.iff and need to be added manually
	if (!abilityMap.containsKey("startMusic+western"))
		abilityMap.put("startMusic+western", new Ability("startMusic+western"));
	if (!abilityMap.containsKey("startDance+theatrical"))
		abilityMap.put("startDance+theatrical", new Ability("startDance+theatrical"));
	if (!abilityMap.containsKey("startDance+theatrical2"))
		abilityMap.put("startDance+theatrical2", new Ability("startDance+theatrical2"));

	loadXpLimits();

	info("Successfully loaded " + String::valueOf(skillMap.size()) + " skills and " + String::valueOf(abilityMap.size()) + " abilities.", true);
}

void SkillManager::loadFromLua() {
	Lua* lua = new Lua();
	lua->init();
	lua_register(lua->getLuaState(), "includeFile", &includeFile);
	lua_register(lua->getLuaState(), "addSkill", &addSkill);

	lua->runFile("scripts/skills/serverobjects.lua");

	delete lua;
}

void SkillManager::loadSkill(LuaObject* luaSkill) {
	Reference<Skill*> skill = new Skill();
	skill->parseLuaObject(luaSkill);
	Skill* parent = skillMap.get(skill->getParentName().hashCode());

	if(parent == NULL) {
		parent = rootNode;
	}

	parent->addChild(skill);
	skillMap.put(skill->getSkillName().hashCode(), skill);

	Vector<String> commands = skill->commands;

	for(int i = 0; i < commands.size(); ++i) {
		String command = commands.get(i);

		if(!abilityMap.containsKey(command)) {
			abilityMap.put(command, new Ability(command));
		}
	}

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

void SkillManager::addAbilities(PlayerObject* ghost, const Vector<String>& abilityNames, bool notifyClient) {
	Vector<Ability*> abilities;

	for (int i = 0; i < abilityNames.size(); ++i) {
		const String& abilityName = abilityNames.get(i);

		Ability* ability = abilityMap.get(abilityName);

		if (ability != NULL && !ghost->hasAbility(abilityName))
			abilities.add(ability);
	}

	ghost->addAbilities(abilities, notifyClient);
}

void SkillManager::removeAbilities(PlayerObject* ghost, const Vector<String>& abilityNames, bool notifyClient) {
	Vector<Ability*> abilities;

	for (int i = 0; i < abilityNames.size(); ++i) {
		const String& abilityName = abilityNames.get(i);

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
	auto skill = skillMap.get(skillName.hashCode());

	if (skill == NULL)
		return false;

	Locker locker(creature);

	//Check for required skills.
	auto requiredSkills = skill->getSkillsRequired();
	for (int i = 0; i < requiredSkills->size(); ++i) {
		const String& requiredSkillName = requiredSkills->get(i);
		auto requiredSkill = skillMap.get(requiredSkillName.hashCode());

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
	if (creature->hasSkill(skill->getSkillName()))
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
		auto skillModifiers = skill->getSkillModifiers();

		for (int i = 0; i < skillModifiers->size(); ++i) {
			auto entry = &skillModifiers->elementAt(i);
			creature->addSkillMod(SkillModManager::SKILLBOX, entry->getKey(), entry->getValue(), notifyClient);

		}

		//Add abilities
		auto abilityNames = skill->getAbilities();
		addAbilities(ghost, *abilityNames, notifyClient);
		if (skill->isGodOnly()) {
			for (int i = 0; i < abilityNames->size(); ++i) {
				const String& ability = abilityNames->get(i);
				StringIdChatParameter params;
				params.setTU(ability);
				params.setStringId("ui", "skill_command_acquired_prose");

				creature->sendSystemMessage(params);
			}
		}

		//Add draft schematic groups
		auto schematicsGranted = skill->getSchematicsGranted();
		SchematicMap::instance()->addSchematics(ghost, *schematicsGranted, notifyClient);

		//Update maximum experience.
		updateXpLimits(ghost);


		// Update Force Power Max.
		ghost->setForcePowerMax(creature->getSkillMod("jedi_force_power_max"), true);

		ManagedReference<PlayerManager*> playerManager = creature->getZoneServer()->getPlayerManager();

		if (skillName.contains("master")) {
			if (playerManager != NULL) {
				const Badge* badge = BadgeList::instance()->get(skillName);

				if (badge == NULL && skillName == "crafting_shipwright_master") {
					badge = BadgeList::instance()->get("crafting_shipwright");
				}

				if (badge != NULL) {
					playerManager->awardBadge(ghost, badge);
				}
			}
		}

		SkillList* list = creature->getSkillList();

		int totalSkillPointsWasted = 250;

		for (int i = 0; i < list->size(); ++i) {
			Skill* skill = list->get(i);

			totalSkillPointsWasted -= skill->getSkillPointsRequired();
		}

		if (ghost->getSkillPoints() != totalSkillPointsWasted) {
			creature->error("skill points mismatch calculated: " + String::valueOf(totalSkillPointsWasted) + " found: " + String::valueOf(ghost->getSkillPoints()));
			ghost->setSkillPoints(totalSkillPointsWasted);
		}

		if (playerManager != NULL) {
			creature->setLevel(playerManager->calculatePlayerLevel(creature));
		}

		if (skill->getSkillName().contains("force_sensitive") && skill->getSkillName().contains("_04"))
			JediManager::instance()->onFSTreeCompleted(creature, skill->getSkillName());

		MissionManager* missionManager = creature->getZoneServer()->getMissionManager();

		if (skill->getSkillName() == "force_title_jedi_rank_02") {
			if (missionManager != NULL)
				missionManager->addPlayerToBountyList(creature->getObjectID(), ghost->calculateBhReward());
		} else if (skill->getSkillName().contains("force_discipline")) {
			if (missionManager != NULL)
				missionManager->updatePlayerBountyReward(creature->getObjectID(), ghost->calculateBhReward());
		} else if (skill->getSkillName().contains("squadleader")) {
			Reference<GroupObject*> group = creature->getGroup();

			if (group != NULL && group->getLeader() == creature) {
				Core::getTaskManager()->executeTask([group] () {
					Locker locker(group);

					group->removeGroupModifiers();
					group->addGroupModifiers();
				}, "UpdateGroupModsLambda");
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

void SkillManager::removeSkillRelatedMissions(CreatureObject* creature, Skill* skill) {
	if(skill->getSkillName().hashCode() == STRING_HASHCODE("combat_bountyhunter_investigation_03")) {
		ManagedReference<ZoneServer*> zoneServer = creature->getZoneServer();
		if(zoneServer != NULL) {
			ManagedReference<MissionManager*> missionManager = zoneServer->getMissionManager();
			if(missionManager != NULL) {
				missionManager->failPlayerBountyMission(creature->getObjectID());
			}
		}
	}
}

bool SkillManager::surrenderSkill(const String& skillName, CreatureObject* creature, bool notifyClient) {
	Skill* skill = skillMap.get(skillName.hashCode());

	if (skill == NULL)
		return false;

	Locker locker(creature);

	//If they have already surrendered the skill, then return true.
	if (!creature->hasSkill(skill->getSkillName()))
		return true;

	SkillList* skillList = creature->getSkillList();

	for (int i = 0; i < skillList->size(); ++i) {
		Skill* checkSkill = skillList->get(i);

		if (checkSkill->isRequiredSkillOf(skill))
			return false;
	}

	if (skillName.beginsWith("force_") && !(JediManager::instance()->canSurrenderSkill(creature, skillName)))
		return false;

	removeSkillRelatedMissions(creature, skill);

	creature->removeSkill(skill, notifyClient);

	//Remove skill modifiers
	auto skillModifiers = skill->getSkillModifiers();

	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	for (int i = 0; i < skillModifiers->size(); ++i) {
		auto entry = &skillModifiers->elementAt(i);
		creature->removeSkillMod(SkillModManager::SKILLBOX, entry->getKey(), entry->getValue(), notifyClient);

	}

	if (ghost != NULL) {
		//Give the player the used skill points back.
		ghost->addSkillPoints(skill->getSkillPointsRequired());

		//Remove abilities but only if the creature doesn't still have a skill that grants the
		//ability.  Some abilities are granted by multiple skills. For example Dazzle for dancers
		//and musicians.
		auto skillAbilities = skill->getAbilities();
		if (skillAbilities->size() > 0) {
			SortedVector<String> abilitiesLost;
			for (int i = 0; i < skillAbilities->size(); i++) {
				abilitiesLost.put(skillAbilities->get(i));
			}
			for (int i = 0; i < skillList->size(); i++) {
				Skill* remainingSkill = skillList->get(i);
				auto remainingAbilities = remainingSkill->getAbilities();
				for(int j = 0; j < remainingAbilities->size(); j++) {
					if (abilitiesLost.contains(remainingAbilities->get(j))) {
						abilitiesLost.drop(remainingAbilities->get(j));
						if (abilitiesLost.size() == 0) {
							break;
						}
					}
				}
			}
			if (abilitiesLost.size() > 0) {
				removeAbilities(ghost, abilitiesLost, notifyClient);
			}
		}

		//Remove draft schematic groups
		auto schematicsGranted = skill->getSchematicsGranted();
		SchematicMap::instance()->removeSchematics(ghost, *schematicsGranted, notifyClient);

		//Update maximum experience.
		updateXpLimits(ghost);

		/// Update Force Power Max
		ghost->setForcePowerMax(creature->getSkillMod("jedi_force_power_max"), true);

		SkillList* list = creature->getSkillList();

		int totalSkillPointsWasted = 250;

		for (int i = 0; i < list->size(); ++i) {
			Skill* skill = list->get(i);

			totalSkillPointsWasted -= skill->getSkillPointsRequired();
		}

		if (ghost->getSkillPoints() != totalSkillPointsWasted) {
			creature->error("skill points mismatch calculated: " + String::valueOf(totalSkillPointsWasted) + " found: " + String::valueOf(ghost->getSkillPoints()));
			ghost->setSkillPoints(totalSkillPointsWasted);
		}

		ManagedReference<PlayerManager*> playerManager = creature->getZoneServer()->getPlayerManager();
		if (playerManager != NULL) {
			creature->setLevel(playerManager->calculatePlayerLevel(creature));
		}

		MissionManager* missionManager = creature->getZoneServer()->getMissionManager();

		if (skill->getSkillName() == "force_title_jedi_rank_02") {
			if (missionManager != NULL)
				missionManager->removePlayerFromBountyList(creature->getObjectID());
		} else if (skill->getSkillName().contains("force_discipline")) {
			if (missionManager != NULL)
				missionManager->updatePlayerBountyReward(creature->getObjectID(), ghost->calculateBhReward());
		} else if (skill->getSkillName().contains("squadleader")) {
			Reference<GroupObject*> group = creature->getGroup();

			if (group != NULL && group->getLeader() == creature) {
				Core::getTaskManager()->executeTask([group] () {
					Locker locker(group);

					group->removeGroupModifiers();

					if (group->hasSquadLeader())
						group->addGroupModifiers();
				}, "UpdateGroupModsLambda2");
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

void SkillManager::surrenderAllSkills(CreatureObject* creature, bool notifyClient, bool removeForceProgression) {
	ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

	SkillList* skillList = creature->getSkillList();

	Vector<String> listOfNames;
	skillList->getStringList(listOfNames);
	SkillList copyOfList;

	copyOfList.loadFromNames(listOfNames);

	for (int i = 0; i < copyOfList.size(); i++) {
		Skill* skill = copyOfList.get(i);

		if (skill->getSkillPointsRequired() > 0) {
			if (!removeForceProgression and skill->getSkillName().contains("force_"))
				continue;

			removeSkillRelatedMissions(creature, skill);

			creature->removeSkill(skill, notifyClient);

			//Remove skill modifiers
			auto skillModifiers = skill->getSkillModifiers();

			for (int i = 0; i < skillModifiers->size(); ++i) {
				auto entry = &skillModifiers->elementAt(i);
				creature->removeSkillMod(SkillModManager::SKILLBOX, entry->getKey(), entry->getValue(), notifyClient);
			}

			if (ghost != NULL) {
				//Give the player the used skill points back.
				ghost->addSkillPoints(skill->getSkillPointsRequired());

				//Remove abilities
				auto abilityNames = skill->getAbilities();
				removeAbilities(ghost, *abilityNames, notifyClient);

				//Remove draft schematic groups
				auto schematicsGranted = skill->getSchematicsGranted();
				SchematicMap::instance()->removeSchematics(ghost, *schematicsGranted, notifyClient);
			}
		}
	}

	SkillModManager::instance()->verifySkillBoxSkillMods(creature);

	if (ghost != NULL) {
		//Update maximum experience.
		updateXpLimits(ghost);

		/// update force
		ghost->setForcePowerMax(creature->getSkillMod("jedi_force_power_max"), true);
	}

	ManagedReference<PlayerManager*> playerManager = creature->getZoneServer()->getPlayerManager();
	if (playerManager != NULL) {
		creature->setLevel(playerManager->calculatePlayerLevel(creature));
	}

	MissionManager* missionManager = creature->getZoneServer()->getMissionManager();
	if (missionManager != NULL)
		missionManager->removePlayerFromBountyList(creature->getObjectID());

	Reference<GroupObject*> group = creature->getGroup();

	if (group != NULL && group->getLeader() == creature) {
		Core::getTaskManager()->executeTask([group] () {
			Locker locker(group);

			group->removeGroupModifiers();
		}, "UpdateGroupModsLambda3");
	}
}

void SkillManager::awardDraftSchematics(Skill* skill, PlayerObject* ghost, bool notifyClient) {
	if (ghost != NULL) {
		//Add draft schematic groups
		auto schematicsGranted = skill->getSchematicsGranted();
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
	ManagedReference<CreatureObject*> player = ghost->getParentRecursively(SceneObjectType::PLAYERCREATURE).castTo<CreatureObject*>();

	if(player == NULL)
		return;

	SkillList* playerSkillBoxList = player->getSkillList();

	for(int i = 0; i < playerSkillBoxList->size(); ++i) {
		Skill* skillBox = playerSkillBoxList->get(i);

		if (skillBox == NULL)
			continue;

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
	Skill* skill = skillMap.get(skillName.hashCode());

	if (skill == NULL) {
		return false;
	}

	//If they already have the skill, then return false.
	if (creature->hasSkill(skillName)) {
		return false;
	}

	if (!fulfillsSkillPrerequisites(skillName, creature)) {
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

bool SkillManager::fulfillsSkillPrerequisitesAndXp(const String& skillName, CreatureObject* creature) {
	if (!fulfillsSkillPrerequisites(skillName, creature)) {
		return false;
	}

	Skill* skill = skillMap.get(skillName.hashCode());

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

bool SkillManager::fulfillsSkillPrerequisites(const String& skillName, CreatureObject* creature) {
	Skill* skill = skillMap.get(skillName.hashCode());

	if (skill == NULL) {
		return false;
	}

	if (skillName.contains("admin_") && !(creature->getPlayerObject()->getAdminLevel() > 0)) {
		return false;
	}

	auto requiredSpecies = skill->getSpeciesRequired();
	if (requiredSpecies->size() > 0) {
		bool foundSpecies = false;
		for (int i = 0; i < requiredSpecies->size(); i++) {
			if (creature->getSpeciesName() == requiredSpecies->get(i)) {
				foundSpecies = true;
				break;
			}
		}
		if (!foundSpecies) {
			return false;
		}
	}

	//Check for required skills.
	auto requiredSkills = skill->getSkillsRequired();
	for (int i = 0; i < requiredSkills->size(); ++i) {
		const String& requiredSkillName = requiredSkills->get(i);
		Skill* requiredSkill = skillMap.get(requiredSkillName.hashCode());

		if (requiredSkill == NULL) {
			continue;
		}

		if (!creature->hasSkill(requiredSkillName)) {
			return false;
		}
	}

	PlayerObject* ghost = creature->getPlayerObject();
	if (ghost == NULL || ghost->getJediState() < skill->getJediStateRequired()) {
		return false;
	}

	if (ghost->isPrivileged())
		return true;

	if (skillName.beginsWith("force_")) {
		return JediManager::instance()->canLearnSkill(creature, skillName);
	}

	return true;
}

int SkillManager::getForceSensitiveSkillCount(CreatureObject* creature, bool includeNoviceMasterBoxes) {
	SkillList* skills =  creature->getSkillList();
	int forceSensitiveSkillCount = 0;

	for (int i = 0; i < skills->size(); ++i) {
		const String& skillName = skills->get(i)->getSkillName();
		if (skillName.contains("force_sensitive") && (includeNoviceMasterBoxes || skillName.indexOf("0") != -1)) {
			forceSensitiveSkillCount++;
		}
	}

	return forceSensitiveSkillCount;
}

bool SkillManager::villageKnightPrereqsMet(CreatureObject* creature, const String& skillToDrop) {
	SkillList* skillList = creature->getSkillList();

	int fullTrees = 0;
	int totalJediPoints = 0;

	for (int i = 0; i < skillList->size(); ++i) {
		Skill* skill = skillList->get(i);

		String skillName = skill->getSkillName();
		if (skillName.contains("force_discipline_") &&
			(skillName.indexOf("0") != -1 || skillName.contains("novice") || skillName.contains("master") )) {
			totalJediPoints += skill->getSkillPointsRequired();

			if (skillName.indexOf("4") != -1) {
				fullTrees++;
			}
		}
	}

	if (!skillToDrop.isEmpty()) {
		Skill* skillBeingDropped = skillMap.get(skillToDrop.hashCode());

		if (skillToDrop.indexOf("4") != -1) {
			fullTrees--;
		}

		totalJediPoints -= skillBeingDropped->getSkillPointsRequired();
	}

	return fullTrees >= 2 && totalJediPoints >= 206;
}
