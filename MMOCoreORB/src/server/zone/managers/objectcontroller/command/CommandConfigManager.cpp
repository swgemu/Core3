/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "CommandConfigManager.h"
#include "server/zone/objects/creature/commands/commands.h"
#include "server/zone/objects/creature/commands/effect/StateEffect.h"
#include "server/zone/objects/creature/commands/effect/DotEffect.h"
#include "server/zone/objects/creature/commands/effect/CommandEffect.h"

#include "server/zone/objects/creature/commands/pet/PetAttackCommand.h"
#include "server/zone/objects/creature/commands/pet/PetEmoteCommand.h"
#include "server/zone/objects/creature/commands/pet/PetFeedCommand.h"
#include "server/zone/objects/creature/commands/pet/PetFollowCommand.h"
#include "server/zone/objects/creature/commands/pet/PetFriendCommand.h"
#include "server/zone/objects/creature/commands/pet/PetGroupCommand.h"
#include "server/zone/objects/creature/commands/pet/PetGuardCommand.h"
#include "server/zone/objects/creature/commands/pet/PetRangedAttackCommand.h"
#include "server/zone/objects/creature/commands/pet/PetRechargeCommand.h"
#include "server/zone/objects/creature/commands/pet/PetRechargeOtherCommand.h"
#include "server/zone/objects/creature/commands/pet/PetRecoverCommand.h"
#include "server/zone/objects/creature/commands/pet/PetSpecialAttackCommand.h"
#include "server/zone/objects/creature/commands/pet/PetStayCommand.h"
#include "server/zone/objects/creature/commands/pet/PetStoreCommand.h"
#include "server/zone/objects/creature/commands/pet/PetTrickCommand.h"
#include "server/zone/objects/creature/commands/pet/PetTransferCommand.h"
#include "server/zone/objects/creature/commands/pet/PetRepairCommand.h"
#include "server/zone/objects/creature/commands/pet/PetThrowCommand.h"
#include "server/zone/objects/creature/commands/pet/PetHarvestCommand.h"
#include "server/zone/objects/creature/commands/pet/PetPatrolCommand.h"
#include "server/zone/objects/creature/commands/pet/PetClearPatrolPointsCommand.h"
#include "server/zone/objects/creature/commands/pet/PetGetPatrolPointCommand.h"

#include "server/zone/objects/creature/CreatureState.h"
#include "server/zone/objects/creature/CreaturePosture.h"
#include "server/zone/objects/creature/CreatureLocomotion.h"
#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableRow.h"

#include "server/zone/ZoneProcessServer.h"
#include "CommandList.h"

CommandList* CommandConfigManager::slashCommands = NULL;
ZoneProcessServer* CommandConfigManager::server = NULL;
int CommandConfigManager::ERROR_CODE = 0;

CommandConfigManager::CommandConfigManager(ZoneProcessServer* serv) {
	server = serv;

	init();

	setLogging(false);
	setLoggingName("CommandConfigManager");

	registerFunctions();
	registerGlobals();
	registerCommands();
}

CommandConfigManager::~CommandConfigManager() {
	server = NULL;

	if (slashCommands != NULL)
		delete slashCommands;

	slashCommands = NULL;

	ERROR_CODE = 0;
}

void CommandConfigManager::loadCommandData(const String& filename) {
	int num = 0;

	IffStream* metatable = TemplateManager::instance()->openIffFile(filename);

	if (metatable == NULL) {
		error("Could not load command table " + filename + ".");
		return;
	}

	DataTableIff tablesToLoad;
	tablesToLoad.readObject(metatable);

	delete metatable;

	for (int j = 0; j < tablesToLoad.getTotalRows(); ++j) {
		DataTableRow* tableRow = tablesToLoad.getRow(j);
		String tableName;
		tableRow->getValue(0, tableName);


		IffStream* iffStream = TemplateManager::instance()->openIffFile(tableName);

		if (iffStream == NULL) {
			error("Could not load commands from " + tableName + ".");
			return;
		} else
			info("opened " + tableName);

		DataTableIff dtiff;
		dtiff.readObject(iffStream);

		delete iffStream;

		for (int i = 0; i < dtiff.getTotalRows(); ++i) {
			DataTableRow* row = dtiff.getRow(i);
			QueueCommand* slashCommand;

			bool disabled; // check disabled first and don't load it

			String name;
			bool combat = false;
			int targetType;
			float maxRangeToTarget;
			String characterAbility;
			float defaultTime;
			int defaultPriority;
			uint64 stateMask = 0; // need to construct statemask
			bool state;
			bool position; // need to add positions one by one

			row->getValue(CommandConfigManager::COMMANDNAME, name);
			slashCommand = createCommand(name.trim().toLowerCase());

			if (slashCommand == NULL) {
				error("Could not create command " + name);
				continue;
			}

			if (!tableName.contains("space"))
				row->getValue(CommandConfigManager::ADDTOCOMBATQUEUE, combat);

			slashCommand->setAddToCombatQueue(combat);

			row->getValue(CommandConfigManager::TARGETTYPE, targetType);
			slashCommand->setTargetType(targetType);

			row->getValue(CommandConfigManager::MAXRANGETOTARGET, maxRangeToTarget);
			slashCommand->setMaxRange(maxRangeToTarget);

			row->getValue(CommandConfigManager::CHARACTERABILITY, characterAbility);
			slashCommand->setCharacterAbility(characterAbility);

			row->getValue(CommandConfigManager::DEFAULTTIME, defaultTime);
			slashCommand->setDefaultTime(defaultTime);

			row->getValue(CommandConfigManager::DEFAULTPRIORITY, defaultPriority);
			slashCommand->setDefaultPriority(defaultPriority);

			// build state mask
			row->getValue(CommandConfigManager::COVER, state);
			if (!state) stateMask |= CreatureState::COVER;
			row->getValue(CommandConfigManager::COMBAT, state);
			if (!state) stateMask |= CreatureState::COMBAT;
			row->getValue(CommandConfigManager::PEACE, state);
			if (!state) stateMask |= CreatureState::PEACE;
			row->getValue(CommandConfigManager::AIMING, state);
			if (!state) stateMask |= CreatureState::AIMING;
			row->getValue(CommandConfigManager::ALERT, state);
			if (!state) stateMask |= CreatureState::ALERT;
			row->getValue(CommandConfigManager::BERSERK, state);
			if (!state) stateMask |= CreatureState::BERSERK;
			row->getValue(CommandConfigManager::FEIGNDEATH, state);
			if (!state) stateMask |= CreatureState::FEIGNDEATH;
			row->getValue(CommandConfigManager::COMBATATTITUDEEVASIVE, state);
			if (!state) stateMask |= CreatureState::COMBATATTITUDEEVASIVE;
			row->getValue(CommandConfigManager::COMBATATTITUDENORMAL, state);
			if (!state) stateMask |= CreatureState::COMBATATTITUDENORMAL;
			row->getValue(CommandConfigManager::COMBATATTITUDEAGGRESSIVE, state);
			if (!state) stateMask |= CreatureState::COMBATATTITUDEAGGRESSIVE;
			row->getValue(CommandConfigManager::TUMBLING, state);
			if (!state) stateMask |= CreatureState::TUMBLING;
			row->getValue(CommandConfigManager::RALLIED, state);
			if (!state) stateMask |= CreatureState::RALLIED;
			row->getValue(CommandConfigManager::STUNNED, state);
			if (!state) stateMask |= CreatureState::STUNNED;
			row->getValue(CommandConfigManager::BLINDED, state);
			if (!state) stateMask |= CreatureState::BLINDED;
			row->getValue(CommandConfigManager::DIZZY, state);
			if (!state) stateMask |= CreatureState::DIZZY;
			row->getValue(CommandConfigManager::INTIMIDATED, state);
			if (!state) stateMask |= CreatureState::INTIMIDATED;
			row->getValue(CommandConfigManager::IMMOBILIZED, state);
			if (!state) stateMask |= CreatureState::IMMOBILIZED;
			row->getValue(CommandConfigManager::FROZEN, state);
			if (!state) stateMask |= CreatureState::FROZEN;
			row->getValue(CommandConfigManager::SWIMMING, state);
			if (!state) stateMask |= CreatureState::SWIMMING;
			row->getValue(CommandConfigManager::SITTINGONCHAIR, state);
			if (!state) stateMask |= CreatureState::SITTINGONCHAIR;
			row->getValue(CommandConfigManager::CRAFTING, state);
			if (!state) stateMask |= CreatureState::CRAFTING;
			row->getValue(CommandConfigManager::GLOWINGJEDI, state);
			if (!state) stateMask |= CreatureState::GLOWINGJEDI;
			row->getValue(CommandConfigManager::MASKSCENT, state);
			if (!state) stateMask |= CreatureState::MASKSCENT;
			row->getValue(CommandConfigManager::POISONED, state);
			if (!state) stateMask |= CreatureState::POISONED;
			row->getValue(CommandConfigManager::BLEEDING, state);
			if (!state) stateMask |= CreatureState::BLEEDING;
			row->getValue(CommandConfigManager::DISEASED, state);
			if (!state) stateMask |= CreatureState::DISEASED;
			row->getValue(CommandConfigManager::ONFIRE, state);
			if (!state) stateMask |= CreatureState::ONFIRE;
			row->getValue(CommandConfigManager::RIDINGMOUNT, state);
			if (!state) stateMask |= CreatureState::RIDINGMOUNT;
			row->getValue(CommandConfigManager::MOUNTEDCREATURE, state);
			if (!state) stateMask |= CreatureState::MOUNTEDCREATURE;
			row->getValue(CommandConfigManager::PILOTINGSHIP, state);
			if (!state) stateMask |= CreatureState::PILOTINGSHIP;
			row->getValue(CommandConfigManager::PILOTINGPOBSHIP, state);
			if (!state) stateMask |= CreatureState::PILOTINGPOBSHIP;
			row->getValue(CommandConfigManager::SHIPOPERATIONS, state);
			if (!state) stateMask |= CreatureState::SHIPOPERATIONS;
			row->getValue(CommandConfigManager::SHIPGUNNER, state);
			if (!state) stateMask |= CreatureState::SHIPGUNNER;
			row->getValue(CommandConfigManager::SHIPINTERIOR, state);
			if (!state) stateMask |= CreatureState::SHIPINTERIOR;

			slashCommand->setStateMask(stateMask);

			// add prohibited locomotions
			row->getValue(CommandConfigManager::STANDING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::STANDING);
			row->getValue(CommandConfigManager::SNEAKING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::SNEAKING);
			row->getValue(CommandConfigManager::WALKING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::WALKING);
			row->getValue(CommandConfigManager::RUNNING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::RUNNING);
			row->getValue(CommandConfigManager::KNEELING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::KNEELING);
			row->getValue(CommandConfigManager::CROUCHSNEAKING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::CROUCHSNEAKING);
			row->getValue(CommandConfigManager::CROUCHWALKING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::CROUCHWALKING);
			row->getValue(CommandConfigManager::PRONE, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::PRONE);
			row->getValue(CommandConfigManager::CRAWLING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::CRAWLING);
			row->getValue(CommandConfigManager::CLIMBINGSTATIONARY, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::CLIMBINGSTATIONARY);
			row->getValue(CommandConfigManager::CLIMBING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::CLIMBING);
			row->getValue(CommandConfigManager::HOVERING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::HOVERING);
			row->getValue(CommandConfigManager::FLYING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::FLYING);
			row->getValue(CommandConfigManager::LYINGDOWN, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::LYINGDOWN);
			row->getValue(CommandConfigManager::SITTING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::SITTING);
			row->getValue(CommandConfigManager::SKILLANIMATING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::SKILLANIMATING);
			row->getValue(CommandConfigManager::DRIVINGVEHICLE, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::DRIVINGVEHICLE);
			row->getValue(CommandConfigManager::RIDINGCREATURE, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::RIDINGCREATURE);
			row->getValue(CommandConfigManager::KNOCKEDDOWN, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::KNOCKEDDOWN);
			row->getValue(CommandConfigManager::INCAPACITATED, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::INCAPACITATED);
			row->getValue(CommandConfigManager::DEAD, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::DEAD);
			row->getValue(CommandConfigManager::BLOCKING, position);
			if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::BLOCKING);

			uint32 group;
			row->getValue(CommandConfigManager::COMMANDGROUP, group);

			slashCommand->setCommandGroup(group);

			num++;
		}
	}

	info("Loaded " + String::valueOf(num) + " commands from " + filename + ".");
}

QueueCommand* CommandConfigManager::createCommand(const String& name) {
	QueueCommand* command = NULL;

	command = commandFactory.createCommand(name, name, server);

	if (command == NULL)
		return command;

	slashCommands->put(command);

	info("created command " + name);

	return command;
}

void CommandConfigManager::registerSpecialCommands(CommandList* sCommands) {
	slashCommands = sCommands;
	QueueCommand* admin = new AdminCommand("admin", server);
	slashCommands->put(admin);
	// Fri Oct  7 17:09:26 PDT 2011 - Karl Bunch <karlbunch@karlbunch.com>
	// Turns out this isn't in the base datatables/command/command_tables_shared.iff file
	// Meanwhile the client sends this to the server as part of the /logout command sequence
	QueueCommand* slashCommand = createCommand(String("logout").toLowerCase());

	if (slashCommand == NULL) {
		error("Could not create command /logout");
	}

	createCommand(String("mildPoison").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("strongPoison").toLowerCase())->setCommandGroup(0xe1c9a54a);

	createCommand(String("mediumPoison").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("mediumDisease").toLowerCase())->setCommandGroup(0xe1c9a54a);

	createCommand(String("mildDisease").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("strongDisease").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("turretFire").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("turretFireManual").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("minefieldAttack").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("creatureRangedAttack").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("defaultDroidAttack").toLowerCase())->setCommandGroup(0xe1c9a54a);

	//Pet commands
	createCommand(String("petAttack").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petEmote").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petFeed").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petFollow").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petFriend").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petGroup").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petGuard").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petRangedAttack").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petRecharge").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petRechargeOther").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petRecover").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petSpecialAttack").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petStay").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petStore").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petTransfer").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petTrick").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petRepair").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petThrow").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petHarvest").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petPatrol").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petClearPatrolPoints").toLowerCase())->setCommandGroup(0xe1c9a54a);
	createCommand(String("petGetPatrolPoint").toLowerCase())->setCommandGroup(0xe1c9a54a);
}

void CommandConfigManager::registerFunctions() {
	//lua generic
	lua_register(getLuaState(), "RunSlashCommandsFile", runSlashCommandsFile);
	lua_register(getLuaState(), "AddCommand", addCommand);
	lua_register(getLuaState(), "hashCode", hashCode);
}

void CommandConfigManager::registerGlobals() {
	//states
	setGlobalLong("INVALID_STATE", CreatureState::INVALID);
	setGlobalLong("COVER_STATE", CreatureState::COVER);
	setGlobalLong("COMBAT_STATE", CreatureState::COMBAT);
	setGlobalLong("PEACE_STATE", CreatureState::PEACE);
	setGlobalLong("AIMING_STATE", CreatureState::AIMING);
	setGlobalLong("ALERT_STATE", CreatureState::ALERT);
	setGlobalLong("BERSERK_STATE", CreatureState::BERSERK);
	setGlobalLong("FEIGNDEATH_STATE", CreatureState::FEIGNDEATH);
	setGlobalLong("COMBATATTITUDEEVASIVE_STATE", CreatureState::COMBATATTITUDEEVASIVE);
	setGlobalLong("COMBATATTITUDENORMAL_STATE", CreatureState::COMBATATTITUDENORMAL);
	setGlobalLong("COMBATATTITUDEAGGRESSIVE_STATE", CreatureState::COMBATATTITUDEAGGRESSIVE);
	setGlobalLong("TUMBLING_STATE", CreatureState::TUMBLING);
	setGlobalLong("RALLIED_STATE", CreatureState::RALLIED);
	setGlobalLong("STUNNED_STATE", CreatureState::STUNNED);
	setGlobalLong("BLINDED_STATE", CreatureState::BLINDED);
	setGlobalLong("DIZZY_STATE", CreatureState::DIZZY);
	setGlobalLong("INTIMIDATED_STATE", CreatureState::INTIMIDATED);
	setGlobalLong("IMMOBILIZED_STATE", CreatureState::IMMOBILIZED);
	setGlobalLong("FROZEN_STATE", CreatureState::FROZEN);
	setGlobalLong("SWIMMING_STATE", CreatureState::SWIMMING);
	setGlobalLong("SITTINGONCHAIR_STATE", CreatureState::SITTINGONCHAIR);
	setGlobalLong("CRAFTING_STATE", CreatureState::CRAFTING);
	setGlobalLong("GLOWINGJEDI_STATE", CreatureState::GLOWINGJEDI);
	setGlobalLong("MASKSCENT_STATE", CreatureState::MASKSCENT);
	setGlobalLong("POISONED", CreatureState::POISONED);
	setGlobalLong("BLEEDING", CreatureState::BLEEDING);
	setGlobalLong("DISEASED", CreatureState::DISEASED);
	setGlobalLong("ONFIRE", CreatureState::ONFIRE);
	setGlobalLong("RIDINGMOUNT_STATE", CreatureState::RIDINGMOUNT);
	setGlobalLong("MOUNTEDCREATURE_STATE", CreatureState::MOUNTEDCREATURE);
	setGlobalLong("PILOTINGSHIP_STATE", CreatureState::PILOTINGSHIP);
	setGlobalLong("PILOTINGPOBSHIP_STATE", CreatureState::PILOTINGPOBSHIP);
	setGlobalLong("SHIPOPERATIONS_STATE", CreatureState::SHIPOPERATIONS);
	setGlobalLong("SHIPGUNNER_STATE", CreatureState::SHIPGUNNER);
	setGlobalLong("SHIPINTERIOR_STATE", CreatureState::SHIPINTERIOR);

	// locomotion
	setGlobalInt("INVALID_LOCOMOTION", CreatureLocomotion::INVALID);
	setGlobalInt("STANDING_LOCOMOTION", CreatureLocomotion::STANDING);
	setGlobalInt("SNEAKING_LOCOMOTION", CreatureLocomotion::SNEAKING);
	setGlobalInt("WALKING_LOCOMOTION", CreatureLocomotion::WALKING);
	setGlobalInt("RUNNING_LOCOMOTION", CreatureLocomotion::RUNNING);
	setGlobalInt("KNEELING_LOCOMOTION", CreatureLocomotion::KNEELING);
	setGlobalInt("CROUCHSNEAKING_LOCOMOTION", CreatureLocomotion::CROUCHSNEAKING);
	setGlobalInt("CROUCHWALKING_LOCOMOTION", CreatureLocomotion::CROUCHWALKING);
	setGlobalInt("PRONE_LOCOMOTION", CreatureLocomotion::PRONE);
	setGlobalInt("CRAWLING_LOCOMOTION", CreatureLocomotion::CRAWLING);
	setGlobalInt("CLIMBINGSTATIONARY_LOCOMOTION", CreatureLocomotion::CLIMBINGSTATIONARY);
	setGlobalInt("CLIMBING_LOCOMOTION", CreatureLocomotion::CLIMBING);
	setGlobalInt("HOVERING_LOCOMOTION", CreatureLocomotion::HOVERING);
	setGlobalInt("FLYING_LOCOMOTION", CreatureLocomotion::FLYING);
	setGlobalInt("LYINGDOWN_LOCOMOTION", CreatureLocomotion::LYINGDOWN);
	setGlobalInt("SITTING_LOCOMOTION", CreatureLocomotion::SITTING);
	setGlobalInt("SKILLANIMATING_LOCOMOTION", CreatureLocomotion::SKILLANIMATING);
	setGlobalInt("DRIVINGVEHICLE_LOCOMOTION", CreatureLocomotion::DRIVINGVEHICLE);
	setGlobalInt("RIDINGCREATURE_LOCOMOTION", CreatureLocomotion::RIDINGCREATURE);
	setGlobalInt("KNOCKEDDOWN_LOCOMOTION", CreatureLocomotion::KNOCKEDDOWN);
	setGlobalInt("INCAPACITATED_LOCOMOTION", CreatureLocomotion::INCAPACITATED);
	setGlobalInt("DEAD_LOCOMOTION", CreatureLocomotion::DEAD);
	setGlobalInt("BLOCKING_LOCOMOTION", CreatureLocomotion::BLOCKING);

	// attributes
	setGlobalInt("HEALTH_ATTRIBUTE", CombatManager::HEALTH);
	setGlobalInt("ACTION_ATTRIBUTE", CombatManager::ACTION);
	setGlobalInt("MIND_ATTRIBUTE", CombatManager::MIND);
	setGlobalInt("RANDOM_ATTRIBUTE", CombatManager::RANDOM);

	setGlobalInt("HEALTH", CreatureAttribute::HEALTH);
	setGlobalInt("ACTION", CreatureAttribute::ACTION);
	setGlobalInt("MIND", CreatureAttribute::MIND);

	// weapons
	setGlobalInt("ANYWEAPON", CombatManager::ANYWEAPON);
	setGlobalInt("THROWNWEAPON", CombatManager::THROWNWEAPON);
	setGlobalInt("HEAVYWEAPON", CombatManager::HEAVYWEAPON);
	setGlobalInt("MINEWEAPON", CombatManager::MINEWEAPON);
	setGlobalInt("SPECIALHEAVYWEAPON", CombatManager::SPECIALHEAVYWEAPON);
	setGlobalInt("UNARMEDWEAPON", CombatManager::UNARMEDWEAPON);
	setGlobalInt("ONEHANDMELEEWEAPON", CombatManager::ONEHANDMELEEWEAPON);
	setGlobalInt("TWOHANDMELEEWEAPON", CombatManager::TWOHANDMELEEWEAPON);
	setGlobalInt("POLEARMWEAPON", CombatManager::POLEARMWEAPON);
	setGlobalInt("PISTOLWEAPON", CombatManager::PISTOLWEAPON);
	setGlobalInt("CARBINEWEAPON", CombatManager::CARBINEWEAPON);
	setGlobalInt("RIFLEWEAPON", CombatManager::RIFLEWEAPON);
	setGlobalInt("GRENADEWEAPON", CombatManager::GRENADEWEAPON);
	setGlobalInt("LIGHTNINGRIFLEWEAPON", CombatManager::LIGHTNINGRIFLEWEAPON);
	setGlobalInt("ONEHANDJEDIWEAPON", CombatManager::ONEHANDJEDIWEAPON);
	setGlobalInt("TWOHANDJEDIWEAPON", CombatManager::TWOHANDJEDIWEAPON);
	setGlobalInt("POLEARMJEDIWEAPON", CombatManager::POLEARMJEDIWEAPON);
	setGlobalInt("MELEEWEAPON", CombatManager::MELEEWEAPON);
	setGlobalInt("RANGEDWEAPON", CombatManager::RANGEDWEAPON);
	setGlobalInt("JEDIWEAPON", CombatManager::JEDIWEAPON);

	// effects
	setGlobalInt("INVALID_EFFECT", CommandEffect::INVALID);
	setGlobalInt("BLIND_EFFECT", CommandEffect::BLIND);
	setGlobalInt("DIZZY_EFFECT", CommandEffect::DIZZY);
	setGlobalInt("INTIMIDATE_EFFECT", CommandEffect::INTIMIDATE);
	setGlobalInt("STUN_EFFECT", CommandEffect::STUN);
	setGlobalInt("KNOCKDOWN_EFFECT", CommandEffect::KNOCKDOWN);
	setGlobalInt("POSTUREUP_EFFECT", CommandEffect::POSTUREUP);
	setGlobalInt("POSTUREDOWN_EFFECT", CommandEffect::POSTUREDOWN);
	setGlobalInt("NEXTATTACKDELAY_EFFECT", CommandEffect::NEXTATTACKDELAY);
	setGlobalInt("HEALTHDEGRADE_EFFECT", CommandEffect::HEALTHDEGRADE);
	setGlobalInt("ACTIONDEGRADE_EFFECT", CommandEffect::ACTIONDEGRADE);
	setGlobalInt("MINDDEGRADE_EFFECT", CommandEffect::MINDDEGRADE);
	setGlobalInt("REMOVE_COVER_EFFECT", CommandEffect::REMOVECOVER);
	setGlobalInt("FORCECHOKE", CommandEffect::FORCECHOKE);

	// trails
	setGlobalInt("NOTRAIL", CombatManager::NOTRAIL);
	setGlobalInt("LEFTFOOTTRAIL", CombatManager::LEFTFOOTTRAIL);
	setGlobalInt("RIGHTFOOTTRAIL", CombatManager::RIGHTFOOTTRAIL);
	setGlobalInt("LEFTHANDTRAIL", CombatManager::LEFTHANDTRAIL);
	setGlobalInt("RIGHTHANDTRAIL", CombatManager::RIGHTHANDTRAIL);
	setGlobalInt("WEAPONTRAIL", CombatManager::WEAPONTRAIL);
	setGlobalInt("DEFAULTTRAIL", CombatManager::DEFAULTTRAIL);

	// attack types
	setGlobalInt("WEAPONATTACK", CombatManager::WEAPONATTACK);
	setGlobalInt("FORCEATTACK", CombatManager::FORCEATTACK);

	// force heal targets
	setGlobalInt("FORCE_HEAL_TARGET_SELF", ForceHealQueueCommand::TARGET_SELF);
	setGlobalInt("FORCE_HEAL_TARGET_OTHER", ForceHealQueueCommand::TARGET_OTHER);
}

int CommandConfigManager::runSlashCommandsFile(lua_State* L) {
	String filename;

	filename = getStringParameter(L);

	bool res = runFile("scripts/commands/" + filename, L);

	if (!res)
		ERROR_CODE = GENERAL_ERROR;

	return 0;
}

void CommandConfigManager::parseOptions(LuaObject &slashcommand, QueueCommand* command) {
	lua_State* L = slashcommand.getLuaState();

	if (!slashcommand.isValidTable())
		return;

	lua_pushnil(L);
	while (lua_next(L, -2) != 0) {
		// 'key' is at index -2 and 'value' at index -1
		if (lua_type(L, -2) == LUA_TSTRING) {
			String varName = lua_tolstring(L, -2, 0);
			parseVariableData(varName, slashcommand, command);
		} else
			lua_pop(L, 1);
	}
}

void CommandConfigManager::parseVariableData(String varName, LuaObject &command, QueueCommand* slashCommand) {
	lua_State* L = command.getLuaState();

	// overwrite data from command_table
	if (varName == "name") // just ignore name, it's only used to grab the object from the table
		command.pop();
	else if (varName == "invalidStateMask")
		slashCommand->setStateMask(Lua::getUnsignedLongParameter(L));
	else if (varName == "invalidLocomotions")
		slashCommand->setInvalidLocomotions(Lua::getStringParameter(L));
	else if (varName == "targetType")
		slashCommand->setTargetType(Lua::getIntParameter(L));
	else if (varName == "disabled") {
		slashCommand->setDisabled((bool)lua_toboolean(L, -1));
		command.pop();
	} else if (varName == "maxRangeToTarget")
		slashCommand->setMaxRange(Lua::getIntParameter(L));
	else if (varName == "addToCombatQueue") {
		slashCommand->setAddToCombatQueue((bool)lua_toboolean(L, -1));
		command.pop();
	} else if (varName == "characterAbility")
		slashCommand->setCharacterAbility(Lua::getStringParameter(L));
	else if (varName == "defaultPriority")
		slashCommand->setDefaultPriority(Lua::getStringParameter(L));
	else if (varName == "defaultTime")
		slashCommand->setDefaultTime(Lua::getFloatParameter(L));
	else if (varName == "skillMods") {
		LuaObject skillMods(L);

		for (int i = 1; i <= skillMods.getTableSize(); ++i) {
			LuaObject skillEntry = skillMods.getObjectAt(i);
			slashCommand->addSkillMod(skillEntry.getStringAt(1), skillEntry.getIntAt(2));
			skillEntry.pop();
		}
		skillMods.pop();

	} else if (slashCommand->isCombatCommand()) { // define combat variables (for combat commands)
		CombatQueueCommand* combatCommand = cast<CombatQueueCommand*>(slashCommand);
		if (varName == "attackType")
			combatCommand->setAttackType(Lua::getIntParameter(L));
		else if (varName == "damageMultiplier")
			combatCommand->setDamageMultiplier(Lua::getFloatParameter(L));
		else if (varName == "accuracyBonus")
			combatCommand->setAccuracyBonus(Lua::getIntParameter(L));
		else if (varName == "speedMultiplier")
			combatCommand->setSpeedMultiplier(Lua::getFloatParameter(L));
		else if (varName == "damage")
			combatCommand->setDamage(Lua::getFloatParameter(L));
		else if (varName == "speed")
			combatCommand->setSpeed(Lua::getFloatParameter(L));
		else if (varName == "poolsToDamage")
			combatCommand->setPoolsToDamage(Lua::getIntParameter(L));
		else if (varName == "weaponType")
			combatCommand->setWeaponType(Lua::getIntParameter(L));
		else if (varName == "healthCostMultiplier")
			combatCommand->setHealthCostMultiplier(Lua::getFloatParameter(L));
		else if (varName == "actionCostMultiplier")
			combatCommand->setActionCostMultiplier(Lua::getFloatParameter(L));
		else if (varName == "mindCostMultiplier")
			combatCommand->setMindCostMultiplier(Lua::getFloatParameter(L));
		else if (varName == "forceCostMultiplier")
			combatCommand->setForceCostMultiplier(Lua::getFloatParameter(L));
		else if (varName == "forceCost")
			combatCommand->setForceCost(Lua::getFloatParameter(L));
		else if (varName == "range")
			combatCommand->setRange(Lua::getIntParameter(L));
		else if (varName == "accuracySkillMod")
			combatCommand->setAccuracySkillMod(Lua::getStringParameter(L));
		else if (varName == "areaAction") {
			combatCommand->setAreaAction((bool)lua_toboolean(L, -1));
			command.pop();
		} else if (varName == "coneAction") {
			combatCommand->setConeAction((bool)lua_toboolean(L, -1));
			command.pop();
		} else if (varName == "coneAngle")
			combatCommand->setConeAngle(Lua::getIntParameter(L));
		else if (varName == "areaRange")
			combatCommand->setAreaRange(Lua::getIntParameter(L));
		else if (varName == "combatSpam")
			combatCommand->setCombatSpam(Lua::getStringParameter(L));
		else if (varName == "animationCRC")
			combatCommand->setAnimationCRC(Lua::getUnsignedIntParameter(L));
		else if (varName == "effectString")
			combatCommand->setEffectString(Lua::getStringParameter(L));
		else if (varName == "trails")
			combatCommand->setTrails(Lua::getIntParameter(L));
		else if (varName == "stateEffects") {
			LuaObject states(L);

			for (int i = 1; i <= states.getTableSize(); ++i) {
				lua_rawgeti(L, -1, i);
				LuaObject state(L);
				combatCommand->addStateEffect(StateEffect(state));
				state.pop();
			}

			states.pop();
		} else if (varName == "dotEffects") {
			LuaObject dots(L);

			for (int i = 1; i <= dots.getTableSize(); ++i) {
				lua_rawgeti(L, -1, i);
				LuaObject dot(L);
				combatCommand->addDotEffect(DotEffect(dot));
				//System::out << "count " << combatCommand->getDotEffects()->size()<< endl;
				dot.pop();
			}

			dots.pop();
		} else if (combatCommand->isSquadLeaderCommand()) {
			SquadLeaderCommand* slCommand = cast<SquadLeaderCommand*>(combatCommand);
			if (varName == "action")
				slCommand->setAction(Lua::getStringParameter(L));
			else {
				Logger::console.error("unknown variable " + varName + " in squadleader command " + slashCommand->getQueueCommandName());
				command.pop();
			}
		} else {
			Logger::console.error("unknown variable " + varName + " in combat queue command " + slashCommand->getQueueCommandName());
			command.pop();
		}
	} else if (slashCommand->isJediQueueCommand()) {
		JediQueueCommand* jediCommand = cast<JediQueueCommand*>(slashCommand);
		if (varName == "forceCost")
			jediCommand->setForceCost(Lua::getIntParameter(L));
		else if (varName == "duration")
			jediCommand->setDuration(Lua::getIntParameter(L));
		else if (varName == "animationCRC")
			jediCommand->setAnimationCRC(Lua::getUnsignedIntParameter(L));
		else if (varName == "clientEffect")
			jediCommand->setClientEffect(Lua::getStringParameter(L));
		else if (varName == "speedMod")
			jediCommand->setSpeedMod(Lua::getFloatParameter(L));
		else if (jediCommand->isForceHealCommand()) {
			ForceHealQueueCommand* healCommand = cast<ForceHealQueueCommand*>(jediCommand);
			if (varName == "healAmount")
				healCommand->setHealAmount(Lua::getIntParameter(L));
			else if (varName == "healWoundAmount") 
				healCommand->setHealWoundAmount(Lua::getIntParameter(L));
			else if (varName == "healAttributes")
				healCommand->setHealAttributes(Lua::getUnsignedIntParameter(L));
			else if (varName == "healWoundAttributes")
				healCommand->setHealWoundAttributes(Lua::getUnsignedIntParameter(L));
			else if (varName == "forceCostDivisor")
				healCommand->setForceCostDivisor(Lua::getFloatParameter(L));
			else if (varName == "range")
				healCommand->setRange(Lua::getIntParameter(L));
			else if (varName == "healBleeding")
				healCommand->setHealBleeding(Lua::getUnsignedIntParameter(L));
			else if (varName == "healFire")
				healCommand->setHealFire(Lua::getUnsignedIntParameter(L));
			else if (varName == "healDisease")
				healCommand->setHealDisease(Lua::getUnsignedIntParameter(L));
			else if (varName == "healPoison")
				healCommand->setHealPoison(Lua::getUnsignedIntParameter(L));
			else if (varName == "healBattleFatigue")
				healCommand->setHealBattleFatigue(Lua::getUnsignedIntParameter(L));
			else if (varName == "healStates")
				healCommand->setHealStates(Lua::getUnsignedIntParameter(L));
			else if (varName == "speed")
				healCommand->setSpeed(Lua::getUnsignedIntParameter(L));
			else if (varName == "allowedTarget")
				healCommand->setAllowedTarget(Lua::getUnsignedIntParameter(L));
			else {
				Logger::console.error("unknown variable " + varName + " in force healing command " + slashCommand->getQueueCommandName());
				command.pop();
			}
		} else {
			Logger::console.error("unknown variable " + varName + " in jedi queue command " + slashCommand->getQueueCommandName());
			command.pop();
		}
	} else {
		Logger::console.error("unknown variable " + varName + " in command " + slashCommand->getQueueCommandName());
		command.pop();
	}
}

void CommandConfigManager::parseAlternativeNames(String& alternativeNames, QueueCommand* slashCommand) {
	StringTokenizer tokenizer(alternativeNames);
	tokenizer.setDelimeter(",");

	String token = "";
	while (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(token);

		slashCommands->put(token, slashCommand);
	}
}

int CommandConfigManager::hashCode(lua_State* L) {
	const char* anim = lua_tostring(L, -1);

	lua_pushnumber(L, String(anim).hashCode());

	return 1;
}

int CommandConfigManager::addCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	// get object from map, then overwrite/fill in variables
	String name = slashcommand.getStringField("name");
	QueueCommand* command = slashCommands->getSlashCommand(name);
	if (command == NULL)
		return 0;

	parseOptions(slashcommand, command);

	return 1;
}

void CommandConfigManager::registerCommands() {
	commandFactory.registerCommand<ActionShot1Command>(String("actionShot1").toLowerCase());
	commandFactory.registerCommand<ActionShot2Command>(String("actionShot2").toLowerCase());
	commandFactory.registerCommand<ActivateCloneCommand>(String("activateClone").toLowerCase());
	commandFactory.registerCommand<ActivateQuestCommand>(String("activateQuest").toLowerCase());
	commandFactory.registerCommand<AddAllowedPlayerCommand>(String("addAllowedPlayer").toLowerCase());
	commandFactory.registerCommand<AddBannedPlayerCommand>(String("addBannedPlayer").toLowerCase());
	commandFactory.registerCommand<AddFriendCommand>(String("addFriend").toLowerCase());
	commandFactory.registerCommand<AddIgnoreCommand>(String("addIgnore").toLowerCase());
	commandFactory.registerCommand<AddMapLocationCommand>(String("addMapLocation").toLowerCase());
	commandFactory.registerCommand<AddPowerCommand>(String("addPower").toLowerCase());
	commandFactory.registerCommand<AdjustLotCountCommand>(String("adjustLotCount").toLowerCase());
	commandFactory.registerCommand<AiIgnoreCommand>(String("aiIgnore").toLowerCase());
	commandFactory.registerCommand<AimCommand>(String("aim").toLowerCase());
	commandFactory.registerCommand<AlertCommand>(String("alert").toLowerCase());
	commandFactory.registerCommand<AnimalAttackCommand>(String("animalAttack").toLowerCase());
	commandFactory.registerCommand<AnimalCalmCommand>(String("animalCalm").toLowerCase());
	commandFactory.registerCommand<AnimalScareCommand>(String("animalScare").toLowerCase());
	commandFactory.registerCommand<AnonCommand>(String("anon").toLowerCase());
	commandFactory.registerCommand<ApplyDiseaseCommand>(String("applyDisease").toLowerCase());
	commandFactory.registerCommand<ApplyPoisonCommand>(String("applyPoison").toLowerCase());
	commandFactory.registerCommand<ApplyPowerupCommand>(String("applyPowerup").toLowerCase());
	commandFactory.registerCommand<AreatrackCommand>(String("areatrack").toLowerCase());
	commandFactory.registerCommand<AssignDroidCommand>(String("assignDroid").toLowerCase());
	commandFactory.registerCommand<AssistCommand>(String("assist").toLowerCase());
	commandFactory.registerCommand<AssociateDroidControlDeviceWithShipCommand>(String("associateDroidControlDeviceWithShip").toLowerCase());
	commandFactory.registerCommand<AttackCommand>(String("attack").toLowerCase());
	commandFactory.registerCommand<AuctionCommand>(String("auction").toLowerCase());
	commandFactory.registerCommand<AuctionAcceptCommand>(String("auctionAccept").toLowerCase());
	commandFactory.registerCommand<AuctionBidCommand>(String("auctionBid").toLowerCase());
	commandFactory.registerCommand<AuctionCancelCommand>(String("auctionCancel").toLowerCase());
	commandFactory.registerCommand<AuctionCreateCommand>(String("auctionCreate").toLowerCase());
	commandFactory.registerCommand<AuctionQueryCommand>(String("auctionQuery").toLowerCase());
	commandFactory.registerCommand<AuctionRetrieveCommand>(String("auctionRetrieve").toLowerCase());
	commandFactory.registerCommand<AuctionsayCommand>(String("auctionsay").toLowerCase());
	commandFactory.registerCommand<AvoidIncapacitationCommand>(String("avoidIncapacitation").toLowerCase());
	commandFactory.registerCommand<BandFlourishCommand>(String("bandFlourish").toLowerCase());
	commandFactory.registerCommand<BattlefieldStatusCommand>(String("battlefieldStatus").toLowerCase());
	commandFactory.registerCommand<Berserk1Command>(String("berserk1").toLowerCase());
	commandFactory.registerCommand<Berserk2Command>(String("berserk2").toLowerCase());
	commandFactory.registerCommand<BetCommand>(String("bet").toLowerCase());
	commandFactory.registerCommand<BleedingShotCommand>(String("bleedingShot").toLowerCase());
	commandFactory.registerCommand<BlindAttackCommand>(String("blindAttack").toLowerCase());
	commandFactory.registerCommand<BoardShuttleCommand>(String("boardShuttle").toLowerCase());
	commandFactory.registerCommand<BodyShot1Command>(String("bodyShot1").toLowerCase());
	commandFactory.registerCommand<BodyShot2Command>(String("bodyShot2").toLowerCase());
	commandFactory.registerCommand<BodyShot3Command>(String("bodyShot3").toLowerCase());
	commandFactory.registerCommand<BoostmoraleCommand>(String("boostmorale").toLowerCase());
	commandFactory.registerCommand<BroadcastCommand>(String("broadcast").toLowerCase());
	commandFactory.registerCommand<BroadcastAreaCommand>(String("broadcastArea").toLowerCase());
	commandFactory.registerCommand<BroadcastGalaxyCommand>(String("broadcastGalaxy").toLowerCase());
	commandFactory.registerCommand<BroadcastPlanetCommand>(String("broadcastPlanet").toLowerCase());
	commandFactory.registerCommand<BurstRunCommand>(String("burstRun").toLowerCase());
	commandFactory.registerCommand<BurstShot1Command>(String("burstShot1").toLowerCase());
	commandFactory.registerCommand<BurstShot2Command>(String("burstShot2").toLowerCase());
	commandFactory.registerCommand<CancelCraftingSessionCommand>(String("cancelCraftingSession").toLowerCase());
	commandFactory.registerCommand<CenterOfBeingCommand>(String("centerOfBeing").toLowerCase());
	commandFactory.registerCommand<ChangeBandMusicCommand>(String("changeBandMusic").toLowerCase());
	commandFactory.registerCommand<ChangeDanceCommand>(String("changeDance").toLowerCase());
	commandFactory.registerCommand<ChangeMusicCommand>(String("changeMusic").toLowerCase());
	commandFactory.registerCommand<ChannelForceCommand>(String("channelForce").toLowerCase());
	commandFactory.registerCommand<ChargeShot1Command>(String("chargeShot1").toLowerCase());
	commandFactory.registerCommand<ChargeShot2Command>(String("chargeShot2").toLowerCase());
	commandFactory.registerCommand<CheckForceStatusCommand>(String("checkForceStatus").toLowerCase());
	commandFactory.registerCommand<CitybanCommand>(String("cityban").toLowerCase());
	commandFactory.registerCommand<CitypardonCommand>(String("citypardon").toLowerCase());
	commandFactory.registerCommand<ClaimVeteranRewardCommand>(String("claimVeteranReward").toLowerCase());
	commandFactory.registerCommand<ClearCompletedQuestCommand>(String("clearCompletedQuest").toLowerCase());
	commandFactory.registerCommand<ClearVeteranRewardCommand>(String("clearVeteranReward").toLowerCase());
	commandFactory.registerCommand<ClientQualifiedForSkillCommand>(String("clientQualifiedForSkill").toLowerCase());
	commandFactory.registerCommand<CloneCommand>(String("clone").toLowerCase());
	commandFactory.registerCommand<CloseContainerCommand>(String("closeContainer").toLowerCase());
	commandFactory.registerCommand<ColorlightsCommand>(String("colorlights").toLowerCase());
	commandFactory.registerCommand<CombatCommand>(String("combat").toLowerCase());
	commandFactory.registerCommand<CombatEscapeCommand>(String("combatEscape").toLowerCase());
	commandFactory.registerCommand<CombatModeCheckCommand>(String("combatModeCheck").toLowerCase());
	commandFactory.registerCommand<CombatSpamCommand>(String("combatSpam").toLowerCase());
	commandFactory.registerCommand<CombatTargetCommand>(String("combatTarget").toLowerCase());
	commandFactory.registerCommand<CompleteQuestCommand>(String("completeQuest").toLowerCase());
	commandFactory.registerCommand<ConcealCommand>(String("conceal").toLowerCase());
	commandFactory.registerCommand<ConcealShotCommand>(String("concealShot").toLowerCase());
	commandFactory.registerCommand<ConfusionShotCommand>(String("confusionShot").toLowerCase());
	commandFactory.registerCommand<ConsentCommand>(String("consent").toLowerCase());
	commandFactory.registerCommand<CorpseCommand>(String("corpse").toLowerCase());
	commandFactory.registerCommand<CoupDeGraceCommand>(String("coupDeGrace").toLowerCase());
	commandFactory.registerCommand<CraftCommand>(String("craft").toLowerCase());
	commandFactory.registerCommand<CreateCreatureCommand>(String("createCreature").toLowerCase());
	commandFactory.registerCommand<CreateManfSchematicCommand>(String("createManfSchematic").toLowerCase());
	commandFactory.registerCommand<CreateMissionElementCommand>(String("createMissionElement").toLowerCase());
	commandFactory.registerCommand<CreateNPCCommand>(String("createNPC").toLowerCase());
	commandFactory.registerCommand<CreatePrototypeCommand>(String("createPrototype").toLowerCase());
	commandFactory.registerCommand<CreateSpawningElementCommand>(String("createSpawningElement").toLowerCase());
	commandFactory.registerCommand<CreateSpawningElementWithDifficultyCommand>(String("createSpawningElementWithDifficulty").toLowerCase());
	commandFactory.registerCommand<CreatureAreaAttackCommand>(String("creatureAreaAttack").toLowerCase());
	commandFactory.registerCommand<CreatureAreaBleedingCommand>(String("creatureAreaBleeding").toLowerCase());
	commandFactory.registerCommand<CreatureAreaComboCommand>(String("creatureAreaCombo").toLowerCase());
	commandFactory.registerCommand<CreatureAreaDiseaseCommand>(String("creatureAreaDisease").toLowerCase());
	commandFactory.registerCommand<CreatureAreaKnockdownCommand>(String("creatureAreaKnockdown").toLowerCase());
	commandFactory.registerCommand<CreatureRangedAttackCommand>(String("creatureRangedAttack").toLowerCase());
	commandFactory.registerCommand<CreatureAreaPoisonCommand>(String("creatureAreaPoison").toLowerCase());
	commandFactory.registerCommand<CreditsCommand>(String("credits").toLowerCase());
	commandFactory.registerCommand<CripplingShotCommand>(String("cripplingShot").toLowerCase());
	commandFactory.registerCommand<CsAppendCommentCommand>(String("csAppendComment").toLowerCase());
	commandFactory.registerCommand<CsCancelTicketCommand>(String("csCancelTicket").toLowerCase());
	commandFactory.registerCommand<CsConnectPlayerCommand>(String("csConnectPlayer").toLowerCase());
	commandFactory.registerCommand<CsCreateTicketCommand>(String("csCreateTicket").toLowerCase());
	commandFactory.registerCommand<CsDisconnectPlayerCommand>(String("csDisconnectPlayer").toLowerCase());
	commandFactory.registerCommand<CsGetArticleCommand>(String("csGetArticle").toLowerCase());
	commandFactory.registerCommand<CsGetCommentsCommand>(String("csGetComments").toLowerCase());
	commandFactory.registerCommand<CsGetTicketsCommand>(String("csGetTickets").toLowerCase());
	commandFactory.registerCommand<CsRequestCategoriesCommand>(String("csRequestCategories").toLowerCase());
	commandFactory.registerCommand<CsSearchKnowledgeBaseCommand>(String("csSearchKnowledgeBase").toLowerCase());
	commandFactory.registerCommand<CuiConsentResponseCommand>(String("cuiConsentResponse").toLowerCase());
	commandFactory.registerCommand<CureDiseaseCommand>(String("cureDisease").toLowerCase());
	commandFactory.registerCommand<CurePoisonCommand>(String("curePoison").toLowerCase());
	commandFactory.registerCommand<CustomizeDroidCommand>(String("customizeDroid").toLowerCase());
	commandFactory.registerCommand<CustomizeVehicleCommand>(String("customizeVehicle").toLowerCase());
	commandFactory.registerCommand<DatabaseCommand>(String("database").toLowerCase());
	commandFactory.registerCommand<DazzleCommand>(String("dazzle").toLowerCase());
	commandFactory.registerCommand<DeactivateQuestCommand>(String("deactivateQuest").toLowerCase());
	commandFactory.registerCommand<DeathBlowCommand>(String("deathBlow").toLowerCase());
	commandFactory.registerCommand<DeathCountCommand>(String("deathCount").toLowerCase());
	commandFactory.registerCommand<DeclareOvertCommand>(String("declareOvert").toLowerCase());
	commandFactory.registerCommand<DeclareresidenceCommand>(String("declareresidence").toLowerCase());
	commandFactory.registerCommand<DeclineCommand>(String("decline").toLowerCase());
	commandFactory.registerCommand<DefaultAttackCommand>(String("defaultAttack").toLowerCase());
	commandFactory.registerCommand<DefaultDroidAttackCommand>(String("defaultDroidAttack").toLowerCase());
	commandFactory.registerCommand<DefuseMinefieldCommand>(String("defuseMinefield").toLowerCase());
	commandFactory.registerCommand<DelegateFactionPointsCommand>(String("delegateFactionPoints").toLowerCase());
	commandFactory.registerCommand<DenyServiceCommand>(String("denyService").toLowerCase());
	commandFactory.registerCommand<DeployTrapCommand>(String("deployTrap").toLowerCase());
	commandFactory.registerCommand<DestroyCommand>(String("destroy").toLowerCase());
	commandFactory.registerCommand<DestroystructureCommand>(String("destroystructure").toLowerCase());
	commandFactory.registerCommand<DetonateDroidCommand>(String("detonateDroid").toLowerCase());
	commandFactory.registerCommand<DiagnoseCommand>(String("diagnose").toLowerCase());
	commandFactory.registerCommand<DisarmingShot1Command>(String("disarmingShot1").toLowerCase());
	commandFactory.registerCommand<DisarmingShot2Command>(String("disarmingShot2").toLowerCase());
	commandFactory.registerCommand<DisbandCommand>(String("disband").toLowerCase());
	commandFactory.registerCommand<DismissGroupMemberCommand>(String("dismissGroupMember").toLowerCase());
	commandFactory.registerCommand<DismountCommand>(String("dismount").toLowerCase());
	commandFactory.registerCommand<DismountandstoreCommand>(String("dismountandstore").toLowerCase());
	commandFactory.registerCommand<DistractCommand>(String("distract").toLowerCase());
	commandFactory.registerCommand<DiveShotCommand>(String("diveShot").toLowerCase());
	commandFactory.registerCommand<DizzyAttackCommand>(String("dizzyAttack").toLowerCase());
	commandFactory.registerCommand<DoubleTapCommand>(String("doubleTap").toLowerCase());
	commandFactory.registerCommand<DragIncapacitatedPlayerCommand>(String("dragIncapacitatedPlayer").toLowerCase());
	commandFactory.registerCommand<DrainForceCommand>(String("drainForce").toLowerCase());
	commandFactory.registerCommand<DuelCommand>(String("duel").toLowerCase());
	commandFactory.registerCommand<DumpTargetInformationCommand>(String("dumpTargetInformation").toLowerCase());
	commandFactory.registerCommand<DumpZoneInformationCommand>(String("dumpZoneInformation").toLowerCase());
	commandFactory.registerCommand<EatCommand>(String("eat").toLowerCase());
	commandFactory.registerCommand<EditAppearanceCommand>(String("editAppearance").toLowerCase());
	commandFactory.registerCommand<EditBankCommand>(String("editBank").toLowerCase());
	commandFactory.registerCommand<EditBankAccountCommand>(String("editBankAccount").toLowerCase());
	commandFactory.registerCommand<EditStatsCommand>(String("editStats").toLowerCase());
	commandFactory.registerCommand<EmboldenpetsCommand>(String("emboldenpets").toLowerCase());
	commandFactory.registerCommand<EmptyMailTargetCommand>(String("emptyMailTarget").toLowerCase());
	commandFactory.registerCommand<EndDuelCommand>(String("endDuel").toLowerCase());
	commandFactory.registerCommand<EnragepetsCommand>(String("enragepets").toLowerCase());
	commandFactory.registerCommand<EquilibriumCommand>(String("equilibrium").toLowerCase());
	commandFactory.registerCommand<ExecuteKnowledgeBaseMessageCommand>(String("executeKnowledgeBaseMessage").toLowerCase());
	commandFactory.registerCommand<ExtinguishFireCommand>(String("extinguishFire").toLowerCase());
	commandFactory.registerCommand<ExtractObjectCommand>(String("extractObject").toLowerCase());
	commandFactory.registerCommand<EyeShotCommand>(String("eyeShot").toLowerCase());
	commandFactory.registerCommand<FactoryCrateSplitCommand>(String("factoryCrateSplit").toLowerCase());
	commandFactory.registerCommand<FanShotCommand>(String("fanShot").toLowerCase());
	commandFactory.registerCommand<FastBlastCommand>(String("fastBlast").toLowerCase());
	commandFactory.registerCommand<FeignDeathCommand>(String("feignDeath").toLowerCase());
	commandFactory.registerCommand<FindCommand>(String("find").toLowerCase());
	commandFactory.registerCommand<FindFriendCommand>(String("findFriend").toLowerCase());
	commandFactory.registerCommand<FindFriendCommand>(String("findFriend").toLowerCase());
	commandFactory.registerCommand<FindMyTrainerCommand>(String("findMyTrainer").toLowerCase());
	commandFactory.registerCommand<FindObjectCommand>(String("findObject").toLowerCase());
	commandFactory.registerCommand<FindPlayerCommand>(String("findPlayer").toLowerCase());
	commandFactory.registerCommand<FireAcidCone1Command>(String("fireAcidCone1").toLowerCase());
	commandFactory.registerCommand<FireAcidCone2Command>(String("fireAcidCone2").toLowerCase());
	commandFactory.registerCommand<FireAcidSingle1Command>(String("fireAcidSingle1").toLowerCase());
	commandFactory.registerCommand<FireAcidSingle2Command>(String("fireAcidSingle2").toLowerCase());
	commandFactory.registerCommand<FireHeavyWeaponCommand>(String("fireHeavyWeapon").toLowerCase());
	commandFactory.registerCommand<FirejetCommand>(String("firejet").toLowerCase());
	commandFactory.registerCommand<FireLightningCone1Command>(String("fireLightningCone1").toLowerCase());
	commandFactory.registerCommand<FireLightningCone2Command>(String("fireLightningCone2").toLowerCase());
	commandFactory.registerCommand<FireLightningSingle1Command>(String("fireLightningSingle1").toLowerCase());
	commandFactory.registerCommand<FireLightningSingle2Command>(String("fireLightningSingle2").toLowerCase());
	commandFactory.registerCommand<FirstAidCommand>(String("firstAid").toLowerCase());
	commandFactory.registerCommand<FishCommand>(String("fish").toLowerCase());
	commandFactory.registerCommand<FlameCone1Command>(String("flameCone1").toLowerCase());
	commandFactory.registerCommand<FlameCone2Command>(String("flameCone2").toLowerCase());
	commandFactory.registerCommand<FlameSingle1Command>(String("flameSingle1").toLowerCase());
	commandFactory.registerCommand<FlameSingle2Command>(String("flameSingle2").toLowerCase());
	commandFactory.registerCommand<FlashSpeederCommand>(String("flashSpeeder").toLowerCase());
	commandFactory.registerCommand<FlourishCommand>(String("flourish").toLowerCase());
	commandFactory.registerCommand<FlurryShot1Command>(String("flurryShot1").toLowerCase());
	commandFactory.registerCommand<FlurryShot2Command>(String("flurryShot2").toLowerCase());
	commandFactory.registerCommand<FlushingShot1Command>(String("flushingShot1").toLowerCase());
	commandFactory.registerCommand<FlushingShot2Command>(String("flushingShot2").toLowerCase());
	commandFactory.registerCommand<ForageCommand>(String("forage").toLowerCase());
	commandFactory.registerCommand<ForceAbsorb1Command>(String("forceAbsorb1").toLowerCase());
	commandFactory.registerCommand<ForceAbsorb2Command>(String("forceAbsorb2").toLowerCase());
	commandFactory.registerCommand<ForceArmor1Command>(String("forceArmor1").toLowerCase());
	commandFactory.registerCommand<ForceArmor2Command>(String("forceArmor2").toLowerCase());
	commandFactory.registerCommand<ForceChokeCommand>(String("forceChoke").toLowerCase());
	commandFactory.registerCommand<ForceCommandCommand>(String("forceCommand").toLowerCase());
	commandFactory.registerCommand<ForceCureDiseaseCommand>(String("forceCureDisease").toLowerCase());
	commandFactory.registerCommand<ForceCurePoisonCommand>(String("forceCurePoison").toLowerCase());
	commandFactory.registerCommand<ForceFeedback1Command>(String("forceFeedback1").toLowerCase());
	commandFactory.registerCommand<ForceFeedback2Command>(String("forceFeedback2").toLowerCase());
	commandFactory.registerCommand<ForceIntimidate1Command>(String("forceIntimidate1").toLowerCase());
	commandFactory.registerCommand<ForceIntimidate2Command>(String("forceIntimidate2").toLowerCase());
	commandFactory.registerCommand<ForceKnockdown1Command>(String("forceKnockdown1").toLowerCase());
	commandFactory.registerCommand<ForceKnockdown2Command>(String("forceKnockdown2").toLowerCase());
	commandFactory.registerCommand<ForceKnockdown3Command>(String("forceKnockdown3").toLowerCase());
	commandFactory.registerCommand<ForceLightningCone1Command>(String("forceLightningCone1").toLowerCase());
	commandFactory.registerCommand<ForceLightningCone2Command>(String("forceLightningCone2").toLowerCase());
	commandFactory.registerCommand<ForceLightningSingle1Command>(String("forceLightningSingle1").toLowerCase());
	commandFactory.registerCommand<ForceLightningSingle2Command>(String("forceLightningSingle2").toLowerCase());
	commandFactory.registerCommand<ForceMeditateCommand>(String("forceMeditate").toLowerCase());
	commandFactory.registerCommand<ForceOfWillCommand>(String("forceOfWill").toLowerCase());
	commandFactory.registerCommand<ForceProtectionCommand>(String("forceProtection").toLowerCase());
	commandFactory.registerCommand<ForceResistBleedingCommand>(String("forceResistBleeding").toLowerCase());
	commandFactory.registerCommand<ForceResistDiseaseCommand>(String("forceResistDisease").toLowerCase());
	commandFactory.registerCommand<ForceResistPoisonCommand>(String("forceResistPoison").toLowerCase());
	commandFactory.registerCommand<ForceResistStatesCommand>(String("forceResistStates").toLowerCase());
	commandFactory.registerCommand<ForceRun1Command>(String("forceRun1").toLowerCase());
	commandFactory.registerCommand<ForceRun2Command>(String("forceRun2").toLowerCase());
	commandFactory.registerCommand<ForceRun3Command>(String("forceRun3").toLowerCase());
	commandFactory.registerCommand<ForceShield1Command>(String("forceShield1").toLowerCase());
	commandFactory.registerCommand<ForceShield2Command>(String("forceShield2").toLowerCase());
	commandFactory.registerCommand<ForceSpeed1Command>(String("forceSpeed1").toLowerCase());
	commandFactory.registerCommand<ForceSpeed2Command>(String("forceSpeed2").toLowerCase());
	commandFactory.registerCommand<ForceThrow1Command>(String("forceThrow1").toLowerCase());
	commandFactory.registerCommand<ForceThrow2Command>(String("forceThrow2").toLowerCase());
	commandFactory.registerCommand<ForceWeaken1Command>(String("forceWeaken1").toLowerCase());
	commandFactory.registerCommand<ForceWeaken2Command>(String("forceWeaken2").toLowerCase());
	commandFactory.registerCommand<FormupCommand>(String("formup").toLowerCase());
	commandFactory.registerCommand<FreezePlayerCommand>(String("freezePlayer").toLowerCase());
	commandFactory.registerCommand<FullAutoArea1Command>(String("fullAutoArea1").toLowerCase());
	commandFactory.registerCommand<FullAutoArea2Command>(String("fullAutoArea2").toLowerCase());
	commandFactory.registerCommand<FullAutoSingle1Command>(String("fullAutoSingle1").toLowerCase());
	commandFactory.registerCommand<FullAutoSingle2Command>(String("fullAutoSingle2").toLowerCase());
	commandFactory.registerCommand<GroupChatCommand>(String("g").toLowerCase());
	commandFactory.registerCommand<GallopCommand>(String("gallop").toLowerCase());
	commandFactory.registerCommand<GallopStopCommand>(String("gallopStop").toLowerCase());
	commandFactory.registerCommand<GcCommand>(String("gc").toLowerCase());
	commandFactory.registerCommand<GcwStatusCommand>(String("gcwStatus").toLowerCase());
	commandFactory.registerCommand<GenerateCraftedItemCommand>(String("generateCraftedItem").toLowerCase());
	commandFactory.registerCommand<GetAccountInfoCommand>(String("getAccountInfo").toLowerCase());
	commandFactory.registerCommand<GetAttributesCommand>(String("getAttributes").toLowerCase());
	commandFactory.registerCommand<GetAttributesBatchCommand>(String("getAttributesBatch").toLowerCase());
	commandFactory.registerCommand<GetFriendListCommand>(String("getFriendList").toLowerCase());
	commandFactory.registerCommand<GetGameTimeCommand>(String("getGameTime").toLowerCase());
	commandFactory.registerCommand<GetIgnoreListCommand>(String("getIgnoreList").toLowerCase());
	commandFactory.registerCommand<GetMapLocationsCommand>(String("getMapLocations").toLowerCase());
	commandFactory.registerCommand<GetObjVarsCommand>(String("getObjVars").toLowerCase());
	commandFactory.registerCommand<GetPlayerIdCommand>(String("getPlayerId").toLowerCase());
	commandFactory.registerCommand<GetPrototypeCommand>(String("getPrototype").toLowerCase());
	commandFactory.registerCommand<GetRankCommand>(String("getRank").toLowerCase());
	commandFactory.registerCommand<GetSpawnDelaysCommand>(String("getSpawnDelays").toLowerCase());
	commandFactory.registerCommand<GetStationNameCommand>(String("getStationName").toLowerCase());
	commandFactory.registerCommand<GetVeteranRewardTimeCommand>(String("getVeteranRewardTime").toLowerCase());
	commandFactory.registerCommand<GetVeteranRewardTimeCsCommand>(String("getVeteranRewardTimeCs").toLowerCase());
	commandFactory.registerCommand<GiveItemCommand>(String("giveItem").toLowerCase());
	commandFactory.registerCommand<GiveMaintenanceToVendorCommand>(String("giveMaintenanceToVendor").toLowerCase());
	commandFactory.registerCommand<GivevendormaintCommand>(String("givevendormaint").toLowerCase());
	commandFactory.registerCommand<GmForceCommandCommand>(String("gmForceCommand").toLowerCase());
	commandFactory.registerCommand<GmCreateClassResourceCommand>(String("gmCreateClassResource").toLowerCase());
	commandFactory.registerCommand<GmCreateSpecificResourceCommand>(String("gmCreateSpecificResource").toLowerCase());
	commandFactory.registerCommand<GmForceRankCommand>(String("gmForceRank").toLowerCase());
	commandFactory.registerCommand<GmFsVillageCommand>(String("gmFsVillage").toLowerCase());
	commandFactory.registerCommand<GmJediStateCommand>(String("gmJediState").toLowerCase());
	commandFactory.registerCommand<GmReviveCommand>(String("gmRevive").toLowerCase());
	commandFactory.registerCommand<GotoCommand>(String("goto").toLowerCase());
	commandFactory.registerCommand<GrantBadgeCommand>(String("grantBadge").toLowerCase());
	commandFactory.registerCommand<GrantPadawanTrialsEligibilityCommand>(String("grantPadawanTrialsEligibility").toLowerCase());
	commandFactory.registerCommand<GrantSkillCommand>(String("grantSkill").toLowerCase());
	commandFactory.registerCommand<GrantTitleCommand>(String("grantTitle").toLowerCase());
	commandFactory.registerCommand<GrantZoningRightsCommand>(String("grantZoningRights").toLowerCase());
	commandFactory.registerCommand<GroupChatCommand>(String("groupChat").toLowerCase());
	commandFactory.registerCommand<GroupChatCommand>(String("groupSay").toLowerCase());
	commandFactory.registerCommand<GroupChatCommand>(String("gsay").toLowerCase());
	commandFactory.registerCommand<GroupChatCommand>(String("gtell").toLowerCase());
	commandFactory.registerCommand<GuildCommand>(String("guild").toLowerCase());
	commandFactory.registerCommand<GuildremoveCommand>(String("guildremove").toLowerCase());
	commandFactory.registerCommand<GuildCommand>(String("guildsay").toLowerCase());
	commandFactory.registerCommand<GuildstatusCommand>(String("guildstatus").toLowerCase());
	commandFactory.registerCommand<HarmfulCommand>(String("harmful").toLowerCase());
	commandFactory.registerCommand<HarmlessCommand>(String("harmless").toLowerCase());
	commandFactory.registerCommand<HarvestCorpseCommand>(String("harvestCorpse").toLowerCase());
	commandFactory.registerCommand<HarvesterActivateCommand>(String("harvesterActivate").toLowerCase());
	commandFactory.registerCommand<HarvesterDeactivateCommand>(String("harvesterDeactivate").toLowerCase());
	commandFactory.registerCommand<HarvesterDiscardHopperCommand>(String("harvesterDiscardHopper").toLowerCase());
	commandFactory.registerCommand<HarvesterGetResourceDataCommand>(String("harvesterGetResourceData").toLowerCase());
	commandFactory.registerCommand<HarvesterHarvestCommand>(String("harvesterHarvest").toLowerCase());
	commandFactory.registerCommand<HarvesterMakeCrateCommand>(String("harvesterMakeCrate").toLowerCase());
	commandFactory.registerCommand<HarvesterSelectResourceCommand>(String("harvesterSelectResource").toLowerCase());
	commandFactory.registerCommand<HarvesterTakeSurveyCommand>(String("harvesterTakeSurvey").toLowerCase());
	commandFactory.registerCommand<HasVeteranRewardCommand>(String("hasVeteranReward").toLowerCase());
	commandFactory.registerCommand<HaveconsentCommand>(String("haveconsent").toLowerCase());
	commandFactory.registerCommand<HeadShot1Command>(String("headShot1").toLowerCase());
	commandFactory.registerCommand<HeadShot2Command>(String("headShot2").toLowerCase());
	commandFactory.registerCommand<HeadShot3Command>(String("headShot3").toLowerCase());
	commandFactory.registerCommand<HealActionSelf1Command>(String("healActionSelf1").toLowerCase());
	commandFactory.registerCommand<HealActionSelf2Command>(String("healActionSelf2").toLowerCase());
	commandFactory.registerCommand<HealActionWoundOther1Command>(String("healActionWoundOther1").toLowerCase());
	commandFactory.registerCommand<HealActionWoundOther2Command>(String("healActionWoundOther2").toLowerCase());
	commandFactory.registerCommand<HealActionWoundSelf1Command>(String("healActionWoundSelf1").toLowerCase());
	commandFactory.registerCommand<HealActionWoundSelf2Command>(String("healActionWoundSelf2").toLowerCase());
	commandFactory.registerCommand<HealAllOther1Command>(String("healAllOther1").toLowerCase());
	commandFactory.registerCommand<HealAllOther2Command>(String("healAllOther2").toLowerCase());
	commandFactory.registerCommand<HealAllSelf1Command>(String("healAllSelf1").toLowerCase());
	commandFactory.registerCommand<HealAllSelf2Command>(String("healAllSelf2").toLowerCase());
	commandFactory.registerCommand<HealBattleFatigueOther1Command>(String("healBattleFatigueOther1").toLowerCase());
	commandFactory.registerCommand<HealBattleFatigueOther2Command>(String("healBattleFatigueOther2").toLowerCase());
	commandFactory.registerCommand<HealBattleFatigueSelf1Command>(String("healBattleFatigueSelf1").toLowerCase());
	commandFactory.registerCommand<HealBattleFatigueSelf2Command>(String("healBattleFatigueSelf2").toLowerCase());
	commandFactory.registerCommand<HealDamageCommand>(String("healDamage").toLowerCase());
	commandFactory.registerCommand<HealDroidDamageCommand>(String("healDroidDamage").toLowerCase());
	commandFactory.registerCommand<HealDroidWoundCommand>(String("healDroidWound").toLowerCase());
	commandFactory.registerCommand<HealEnhanceCommand>(String("healEnhance").toLowerCase());
	commandFactory.registerCommand<HealHealthSelf1Command>(String("healHealthSelf1").toLowerCase());
	commandFactory.registerCommand<HealHealthSelf2Command>(String("healHealthSelf2").toLowerCase());
	commandFactory.registerCommand<HealHealthWoundOther1Command>(String("healHealthWoundOther1").toLowerCase());
	commandFactory.registerCommand<HealHealthWoundOther2Command>(String("healHealthWoundOther2").toLowerCase());
	commandFactory.registerCommand<HealHealthWoundSelf1Command>(String("healHealthWoundSelf1").toLowerCase());
	commandFactory.registerCommand<HealHealthWoundSelf2Command>(String("healHealthWoundSelf2").toLowerCase());
	commandFactory.registerCommand<HealMindCommand>(String("healMind").toLowerCase());
	commandFactory.registerCommand<HealMindSelf1Command>(String("healMindSelf1").toLowerCase());
	commandFactory.registerCommand<HealMindSelf2Command>(String("healMindSelf2").toLowerCase());
	commandFactory.registerCommand<HealMindWoundOther1Command>(String("healMindWoundOther1").toLowerCase());
	commandFactory.registerCommand<HealMindWoundOther2Command>(String("healMindWoundOther2").toLowerCase());
	commandFactory.registerCommand<HealMindWoundSelf1Command>(String("healMindWoundSelf1").toLowerCase());
	commandFactory.registerCommand<HealMindWoundSelf2Command>(String("healMindWoundSelf2").toLowerCase());
	commandFactory.registerCommand<HealPetCommand>(String("healPet").toLowerCase());
	commandFactory.registerCommand<HealStateCommand>(String("healState").toLowerCase());
	commandFactory.registerCommand<HealStatesOtherCommand>(String("healStatesOther").toLowerCase());
	commandFactory.registerCommand<HealStatesSelfCommand>(String("healStatesSelf").toLowerCase());
	commandFactory.registerCommand<HealthShot1Command>(String("healthShot1").toLowerCase());
	commandFactory.registerCommand<HealthShot2Command>(String("healthShot2").toLowerCase());
	commandFactory.registerCommand<HealWoundCommand>(String("healWound").toLowerCase());
	commandFactory.registerCommand<HoloEmoteCommand>(String("holoEmote").toLowerCase());
	commandFactory.registerCommand<ImagedesignCommand>(String("imagedesign").toLowerCase());
	commandFactory.registerCommand<InitializeComponentCommand>(String("initializeComponent").toLowerCase());
	commandFactory.registerCommand<InnateCommand>(String("innate").toLowerCase());
	commandFactory.registerCommand<InsertItemIntoShipComponentSlotCommand>(String("insertItemIntoShipComponentSlot").toLowerCase());
	commandFactory.registerCommand<InstallMissionTerminalCommand>(String("installMissionTerminal").toLowerCase());
	commandFactory.registerCommand<InstallShipComponentCommand>(String("installShipComponent").toLowerCase());
	commandFactory.registerCommand<InsureCommand>(String("insure").toLowerCase());
	commandFactory.registerCommand<Intimidate1Command>(String("intimidate1").toLowerCase());
	commandFactory.registerCommand<Intimidate2Command>(String("intimidate2").toLowerCase());
	commandFactory.registerCommand<IntimidationAttackCommand>(String("intimidationAttack").toLowerCase());
	commandFactory.registerCommand<MildPoisonCommand>(String("mildPoison").toLowerCase());
	commandFactory.registerCommand<MediumPoisonCommand>(String("mediumPoison").toLowerCase());
	commandFactory.registerCommand<MediumDiseaseCommand>(String("mediumDisease").toLowerCase());
	commandFactory.registerCommand<StrongPoisonCommand>(String("strongPoison").toLowerCase());
	commandFactory.registerCommand<StrongDiseaseCommand>(String("strongDisease").toLowerCase());
	commandFactory.registerCommand<MildDiseaseCommand>(String("mildDisease").toLowerCase());
	commandFactory.registerCommand<InviteCommand>(String("invite").toLowerCase());
	commandFactory.registerCommand<InvulnerableCommand>(String("invulnerable").toLowerCase());
	commandFactory.registerCommand<ItemmovebackCommand>(String("itemmoveback").toLowerCase());
	commandFactory.registerCommand<ItemmovedownCommand>(String("itemmovedown").toLowerCase());
	commandFactory.registerCommand<ItemmoveforwardCommand>(String("itemmoveforward").toLowerCase());
	commandFactory.registerCommand<ItemmoveupCommand>(String("itemmoveup").toLowerCase());
	commandFactory.registerCommand<ItemrotateleftCommand>(String("itemrotateleft").toLowerCase());
	commandFactory.registerCommand<ItemrotaterightCommand>(String("itemrotateright").toLowerCase());
	commandFactory.registerCommand<JediMindTrickCommand>(String("jediMindTrick").toLowerCase());
	commandFactory.registerCommand<JoinCommand>(String("join").toLowerCase());
	commandFactory.registerCommand<JoinGameCommand>(String("joinGame").toLowerCase());
	commandFactory.registerCommand<KickCommand>(String("kick").toLowerCase());
	commandFactory.registerCommand<KillCommand>(String("kill").toLowerCase());
	commandFactory.registerCommand<KillPlayerCommand>(String("killPlayer").toLowerCase());
	commandFactory.registerCommand<KipUpShotCommand>(String("kipUpShot").toLowerCase());
	commandFactory.registerCommand<KneelCommand>(String("kneel").toLowerCase());
	commandFactory.registerCommand<KnockdownAttackCommand>(String("knockdownAttack").toLowerCase());
	commandFactory.registerCommand<KnockdownFireCommand>(String("knockdownFire").toLowerCase());
	commandFactory.registerCommand<LagCommand>(String("lag").toLowerCase());
	commandFactory.registerCommand<LastDitchCommand>(String("lastDitch").toLowerCase());
	commandFactory.registerCommand<LaunchFireworkCommand>(String("launchFirework").toLowerCase());
	commandFactory.registerCommand<LeaveGameCommand>(String("leaveGame").toLowerCase());
	commandFactory.registerCommand<LeaveGroupCommand>(String("leaveGroup").toLowerCase());
	commandFactory.registerCommand<LegShot1Command>(String("legShot1").toLowerCase());
	commandFactory.registerCommand<LegShot2Command>(String("legShot2").toLowerCase());
	commandFactory.registerCommand<LegShot3Command>(String("legShot3").toLowerCase());
	commandFactory.registerCommand<LfgCommand>(String("lfg").toLowerCase());
	commandFactory.registerCommand<ListActiveQuestsCommand>(String("listActiveQuests").toLowerCase());
	commandFactory.registerCommand<ListCompletedQuestsCommand>(String("listCompletedQuests").toLowerCase());
	commandFactory.registerCommand<ListenCommand>(String("listen").toLowerCase());
	commandFactory.registerCommand<ListGuildsCommand>(String("listGuilds").toLowerCase());
	commandFactory.registerCommand<LogoutCommand>(String("logout").toLowerCase());
	commandFactory.registerCommand<LogoutServerCommand>(String("logoutServer").toLowerCase());
	commandFactory.registerCommand<LootCommand>(String("loot").toLowerCase());
	commandFactory.registerCommand<LootPlayerCorpseCommand>(String("lootPlayerCorpse").toLowerCase());
	commandFactory.registerCommand<LowBlowCommand>(String("lowBlow").toLowerCase());
	commandFactory.registerCommand<MakeLeaderCommand>(String("makeLeader").toLowerCase());
	commandFactory.registerCommand<MakeMasterLooterCommand>(String("makeMasterLooter").toLowerCase());
	commandFactory.registerCommand<MakeSurveyCommand>(String("makeSurvey").toLowerCase());
	commandFactory.registerCommand<ManufactureCommand>(String("manufacture").toLowerCase());
	commandFactory.registerCommand<MaskscentCommand>(String("maskscent").toLowerCase());
	commandFactory.registerCommand<MaxCombatAbilityCommand>(String("maxCombatAbility").toLowerCase());
	commandFactory.registerCommand<MaxStatsCommand>(String("maxStats").toLowerCase());
	commandFactory.registerCommand<MedicalForageCommand>(String("medicalForage").toLowerCase());
	commandFactory.registerCommand<MeditateCommand>(String("meditate").toLowerCase());
	commandFactory.registerCommand<Melee1hBlindHit1Command>(String("melee1hBlindHit1").toLowerCase());
	commandFactory.registerCommand<Melee1hBlindHit2Command>(String("melee1hBlindHit2").toLowerCase());
	commandFactory.registerCommand<Melee1hBodyHit1Command>(String("melee1hBodyHit1").toLowerCase());
	commandFactory.registerCommand<Melee1hBodyHit2Command>(String("melee1hBodyHit2").toLowerCase());
	commandFactory.registerCommand<Melee1hBodyHit3Command>(String("melee1hBodyHit3").toLowerCase());
	commandFactory.registerCommand<Melee1hDizzyHit1Command>(String("melee1hDizzyHit1").toLowerCase());
	commandFactory.registerCommand<Melee1hDizzyHit2Command>(String("melee1hDizzyHit2").toLowerCase());
	commandFactory.registerCommand<Melee1hHealthHit1Command>(String("melee1hHealthHit1").toLowerCase());
	commandFactory.registerCommand<Melee1hHealthHit2Command>(String("melee1hHealthHit2").toLowerCase());
	commandFactory.registerCommand<Melee1hHit1Command>(String("melee1hHit1").toLowerCase());
	commandFactory.registerCommand<Melee1hHit2Command>(String("melee1hHit2").toLowerCase());
	commandFactory.registerCommand<Melee1hHit3Command>(String("melee1hHit3").toLowerCase());
	commandFactory.registerCommand<Melee1hLunge1Command>(String("melee1hLunge1").toLowerCase());
	commandFactory.registerCommand<Melee1hLunge2Command>(String("melee1hLunge2").toLowerCase());
	commandFactory.registerCommand<Melee1hScatterHit1Command>(String("melee1hScatterHit1").toLowerCase());
	commandFactory.registerCommand<Melee1hScatterHit2Command>(String("melee1hScatterHit2").toLowerCase());
	commandFactory.registerCommand<Melee1hSpinAttack1Command>(String("melee1hSpinAttack1").toLowerCase());
	commandFactory.registerCommand<Melee1hSpinAttack2Command>(String("melee1hSpinAttack2").toLowerCase());
	commandFactory.registerCommand<Melee2hArea1Command>(String("melee2hArea1").toLowerCase());
	commandFactory.registerCommand<Melee2hArea2Command>(String("melee2hArea2").toLowerCase());
	commandFactory.registerCommand<Melee2hArea3Command>(String("melee2hArea3").toLowerCase());
	commandFactory.registerCommand<Melee2hHeadHit1Command>(String("melee2hHeadHit1").toLowerCase());
	commandFactory.registerCommand<Melee2hHeadHit2Command>(String("melee2hHeadHit2").toLowerCase());
	commandFactory.registerCommand<Melee2hHeadHit3Command>(String("melee2hHeadHit3").toLowerCase());
	commandFactory.registerCommand<Melee2hHit1Command>(String("melee2hHit1").toLowerCase());
	commandFactory.registerCommand<Melee2hHit2Command>(String("melee2hHit2").toLowerCase());
	commandFactory.registerCommand<Melee2hHit3Command>(String("melee2hHit3").toLowerCase());
	commandFactory.registerCommand<Melee2hLunge1Command>(String("melee2hLunge1").toLowerCase());
	commandFactory.registerCommand<Melee2hLunge2Command>(String("melee2hLunge2").toLowerCase());
	commandFactory.registerCommand<Melee2hMindHit1Command>(String("melee2hMindHit1").toLowerCase());
	commandFactory.registerCommand<Melee2hMindHit2Command>(String("melee2hMindHit2").toLowerCase());
	commandFactory.registerCommand<Melee2hSpinAttack1Command>(String("melee2hSpinAttack1").toLowerCase());
	commandFactory.registerCommand<Melee2hSpinAttack2Command>(String("melee2hSpinAttack2").toLowerCase());
	commandFactory.registerCommand<Melee2hSweep1Command>(String("melee2hSweep1").toLowerCase());
	commandFactory.registerCommand<Melee2hSweep2Command>(String("melee2hSweep2").toLowerCase());
	commandFactory.registerCommand<MindBlast1Command>(String("mindBlast1").toLowerCase());
	commandFactory.registerCommand<MindBlast2Command>(String("mindBlast2").toLowerCase());
	commandFactory.registerCommand<MindShot1Command>(String("mindShot1").toLowerCase());
	commandFactory.registerCommand<MindShot2Command>(String("mindShot2").toLowerCase());
	commandFactory.registerCommand<MinefieldAttackCommand>(String("minefieldAttack").toLowerCase());
	commandFactory.registerCommand<MoneyCommand>(String("money").toLowerCase());
	commandFactory.registerCommand<MountCommand>(String("mount").toLowerCase());
	commandFactory.registerCommand<MoveFurnitureCommand>(String("moveFurniture").toLowerCase());
	commandFactory.registerCommand<MultiTargetPistolShotCommand>(String("multiTargetPistolShot").toLowerCase());
	commandFactory.registerCommand<MultiTargetShotCommand>(String("multiTargetShot").toLowerCase());
	commandFactory.registerCommand<NameStructureCommand>(String("nameStructure").toLowerCase());
	commandFactory.registerCommand<NewbiehelperCommand>(String("newbiehelper").toLowerCase());
	commandFactory.registerCommand<NewbieRequestStartingLocationsCommand>(String("newbieRequestStartingLocations").toLowerCase());
	commandFactory.registerCommand<NewbieSelectStartingLocationCommand>(String("newbieSelectStartingLocation").toLowerCase());
	commandFactory.registerCommand<NextCraftingStageCommand>(String("nextCraftingStage").toLowerCase());
	commandFactory.registerCommand<NpcCommand>(String("npc").toLowerCase());
	commandFactory.registerCommand<NpcConversationSelectCommand>(String("npcConversationSelect").toLowerCase());
	commandFactory.registerCommand<NpcConversationStartCommand>(String("npcConversationStart").toLowerCase());
	commandFactory.registerCommand<NpcConversationStopCommand>(String("npcConversationStop").toLowerCase());
	commandFactory.registerCommand<ObjectCommand>(String("Object").toLowerCase());
	commandFactory.registerCommand<ObjvarCommand>(String("objvar").toLowerCase());
	commandFactory.registerCommand<OpenContainerCommand>(String("openContainer").toLowerCase());
	commandFactory.registerCommand<OverChargeShot1Command>(String("overChargeShot1").toLowerCase());
	commandFactory.registerCommand<OverChargeShot2Command>(String("overChargeShot2").toLowerCase());
	commandFactory.registerCommand<OverrideActiveMonthsCommand>(String("overrideActiveMonths").toLowerCase());
	commandFactory.registerCommand<OverridePadawanTrialsEligibilityCommand>(String("overridePadawanTrialsEligibility").toLowerCase());
	commandFactory.registerCommand<PanicShotCommand>(String("panicShot").toLowerCase());
	commandFactory.registerCommand<PauseDanceCommand>(String("pauseDance").toLowerCase());
	commandFactory.registerCommand<PauseMusicCommand>(String("pauseMusic").toLowerCase());
	commandFactory.registerCommand<PaWithdrawCommand>(String("paWithdraw").toLowerCase());
	commandFactory.registerCommand<PaymaintenanceCommand>(String("paymaintenance").toLowerCase());
	commandFactory.registerCommand<PeaceCommand>(String("peace").toLowerCase());
	commandFactory.registerCommand<PermissionListModifyCommand>(String("permissionListModify").toLowerCase());
	commandFactory.registerCommand<PistolMeleeDefense1Command>(String("pistolMeleeDefense1").toLowerCase());
	commandFactory.registerCommand<PistolMeleeDefense2Command>(String("pistolMeleeDefense2").toLowerCase());
	commandFactory.registerCommand<PlaceBattlefieldStructureCommand>(String("placeBattlefieldStructure").toLowerCase());
	commandFactory.registerCommand<PlaceStructureCommand>(String("placeStructure").toLowerCase());
	commandFactory.registerCommand<PlaceStructureModeCommand>(String("placeStructureMode").toLowerCase());
	commandFactory.registerCommand<PlanetCommand>(String("planet").toLowerCase());
	commandFactory.registerCommand<PlanetsayCommand>(String("planetsay").toLowerCase());
	commandFactory.registerCommand<PlanetwarpCommand>(String("planetwarp").toLowerCase());
	commandFactory.registerCommand<PlanetwarpTargetCommand>(String("planetwarpTarget").toLowerCase());
	commandFactory.registerCommand<PointBlankArea1Command>(String("pointBlankArea1").toLowerCase());
	commandFactory.registerCommand<PointBlankArea2Command>(String("pointBlankArea2").toLowerCase());
	commandFactory.registerCommand<PointBlankSingle1Command>(String("pointBlankSingle1").toLowerCase());
	commandFactory.registerCommand<PointBlankSingle2Command>(String("pointBlankSingle2").toLowerCase());
	commandFactory.registerCommand<PolearmActionHit1Command>(String("polearmActionHit1").toLowerCase());
	commandFactory.registerCommand<PolearmActionHit2Command>(String("polearmActionHit2").toLowerCase());
	commandFactory.registerCommand<PolearmArea1Command>(String("polearmArea1").toLowerCase());
	commandFactory.registerCommand<PolearmArea2Command>(String("polearmArea2").toLowerCase());
	commandFactory.registerCommand<PolearmHit1Command>(String("polearmHit1").toLowerCase());
	commandFactory.registerCommand<PolearmHit2Command>(String("polearmHit2").toLowerCase());
	commandFactory.registerCommand<PolearmHit3Command>(String("polearmHit3").toLowerCase());
	commandFactory.registerCommand<PolearmLegHit1Command>(String("polearmLegHit1").toLowerCase());
	commandFactory.registerCommand<PolearmLegHit2Command>(String("polearmLegHit2").toLowerCase());
	commandFactory.registerCommand<PolearmLegHit3Command>(String("polearmLegHit3").toLowerCase());
	commandFactory.registerCommand<PolearmLunge1Command>(String("polearmLunge1").toLowerCase());
	commandFactory.registerCommand<PolearmLunge2Command>(String("polearmLunge2").toLowerCase());
	commandFactory.registerCommand<PolearmSpinAttack1Command>(String("polearmSpinAttack1").toLowerCase());
	commandFactory.registerCommand<PolearmSpinAttack2Command>(String("polearmSpinAttack2").toLowerCase());
	commandFactory.registerCommand<PolearmStun1Command>(String("polearmStun1").toLowerCase());
	commandFactory.registerCommand<PolearmStun2Command>(String("polearmStun2").toLowerCase());
	commandFactory.registerCommand<PolearmSweep1Command>(String("polearmSweep1").toLowerCase());
	commandFactory.registerCommand<PolearmSweep2Command>(String("polearmSweep2").toLowerCase());
	commandFactory.registerCommand<PostureDownAttackCommand>(String("postureDownAttack").toLowerCase());
	commandFactory.registerCommand<PostureUpAttackCommand>(String("postureUpAttack").toLowerCase());
	commandFactory.registerCommand<PowerBoostCommand>(String("powerBoost").toLowerCase());
	commandFactory.registerCommand<ProneCommand>(String("prone").toLowerCase());
	commandFactory.registerCommand<PurchaseReinforcementCommand>(String("purchaseReinforcement").toLowerCase());
	commandFactory.registerCommand<PurchaseTicketCommand>(String("purchaseTicket").toLowerCase());
	commandFactory.registerCommand<QuickHealCommand>(String("quickHeal").toLowerCase());
	commandFactory.registerCommand<RallyCommand>(String("rally").toLowerCase());
	commandFactory.registerCommand<ReconnectToTransferServerCommand>(String("reconnectToTransferServer").toLowerCase());
	commandFactory.registerCommand<RecruitSkillTrainerCommand>(String("recruitSkillTrainer").toLowerCase());
	commandFactory.registerCommand<RegainConsciousnessCommand>(String("regainConsciousness").toLowerCase());
	commandFactory.registerCommand<RegenerationCommand>(String("regeneration").toLowerCase());
	commandFactory.registerCommand<RegisterWithLocationCommand>(String("registerWithLocation").toLowerCase());
	commandFactory.registerCommand<ReloadCommand>(String("reload").toLowerCase());
	commandFactory.registerCommand<RemoteCommand>(String("remote").toLowerCase());
	commandFactory.registerCommand<RemoveAllowedPlayerCommand>(String("removeAllowedPlayer").toLowerCase());
	commandFactory.registerCommand<RemoveBannedPlayerCommand>(String("removeBannedPlayer").toLowerCase());
	commandFactory.registerCommand<RemoveFriendCommand>(String("removeFriend").toLowerCase());
	commandFactory.registerCommand<RemoveIgnoreCommand>(String("removeIgnore").toLowerCase());
	commandFactory.registerCommand<RepairBattlefieldStructureCommand>(String("repairBattlefieldStructure").toLowerCase());
	commandFactory.registerCommand<RepairShipComponentInSlotCommand>(String("repairShipComponentInSlot").toLowerCase());
	commandFactory.registerCommand<ReportCommand>(String("report").toLowerCase());
	commandFactory.registerCommand<RequestBadgesCommand>(String("requestBadges").toLowerCase());
	commandFactory.registerCommand<RequestBiographyCommand>(String("requestBiography").toLowerCase());
	commandFactory.registerCommand<RequestCharacterMatchCommand>(String("requestCharacterMatch").toLowerCase());
	commandFactory.registerCommand<RequestCharacterSheetInfoCommand>(String("requestCharacterSheetInfo").toLowerCase());
	commandFactory.registerCommand<RequestCoreSampleCommand>(String("requestCoreSample").toLowerCase());
	commandFactory.registerCommand<RequestCraftingSessionCommand>(String("requestCraftingSession").toLowerCase());
	commandFactory.registerCommand<RequestDraftSlotsCommand>(String("requestDraftSlots").toLowerCase());
	commandFactory.registerCommand<RequestDraftSlotsBatchCommand>(String("requestDraftSlotsBatch").toLowerCase());
	commandFactory.registerCommand<RequestManfSchematicSlotsCommand>(String("requestManfSchematicSlots").toLowerCase());
	commandFactory.registerCommand<RequestResourceWeightsCommand>(String("requestResourceWeights").toLowerCase());
	commandFactory.registerCommand<RequestResourceWeightsBatchCommand>(String("requestResourceWeightsBatch").toLowerCase());
	commandFactory.registerCommand<RequestSetStatMigrationDataCommand>(String("requestSetStatMigrationData").toLowerCase());
	commandFactory.registerCommand<RequestStatMigrationDataCommand>(String("requestStatMigrationData").toLowerCase());
	commandFactory.registerCommand<RequestStatMigrationStartCommand>(String("requestStatMigrationStart").toLowerCase());
	commandFactory.registerCommand<RequestStatMigrationStopCommand>(String("requestStatMigrationStop").toLowerCase());
	commandFactory.registerCommand<RequestStimpackCommand>(String("requestStimpack").toLowerCase());
	commandFactory.registerCommand<RequestSurveyCommand>(String("requestSurvey").toLowerCase());
	commandFactory.registerCommand<RequestWaypointAtPositionCommand>(String("requestWaypointAtPosition").toLowerCase());
	commandFactory.registerCommand<RescueCommand>(String("rescue").toLowerCase());
	commandFactory.registerCommand<ResendLoginMessageToAllCommand>(String("resendLoginMessageToAll").toLowerCase());
	commandFactory.registerCommand<ResetJediCommand>(String("resetJedi").toLowerCase());
	commandFactory.registerCommand<ResourceCommand>(String("resource").toLowerCase());
	commandFactory.registerCommand<ResourceContainerSplitCommand>(String("resourceContainerSplit").toLowerCase());
	commandFactory.registerCommand<ResourceContainerTransferCommand>(String("resourceContainerTransfer").toLowerCase());
	commandFactory.registerCommand<ResourceSetNameCommand>(String("resourceSetName").toLowerCase());
	commandFactory.registerCommand<ResSampleLoopCommand>(String("resSampleLoop").toLowerCase());
	commandFactory.registerCommand<RestartConversionCommand>(String("restartConversion").toLowerCase());
	commandFactory.registerCommand<RestartCraftingSessionCommand>(String("restartCraftingSession").toLowerCase());
	commandFactory.registerCommand<RetreatCommand>(String("retreat").toLowerCase());
	commandFactory.registerCommand<RevivePlayerCommand>(String("revivePlayer").toLowerCase());
	commandFactory.registerCommand<RevokeBadgeCommand>(String("revokeBadge").toLowerCase());
	commandFactory.registerCommand<RevokeSkillCommand>(String("revokeSkill").toLowerCase());
	commandFactory.registerCommand<RolePlayCommand>(String("rolePlay").toLowerCase());
	commandFactory.registerCommand<RollShotCommand>(String("rollShot").toLowerCase());
	commandFactory.registerCommand<RotateFurnitureCommand>(String("rotateFurniture").toLowerCase());
	commandFactory.registerCommand<Saber1hComboHit1Command>(String("saber1hComboHit1").toLowerCase());
	commandFactory.registerCommand<Saber1hComboHit2Command>(String("saber1hComboHit2").toLowerCase());
	commandFactory.registerCommand<Saber1hComboHit3Command>(String("saber1hComboHit3").toLowerCase());
	commandFactory.registerCommand<Saber1hFlurryCommand>(String("saber1hFlurry").toLowerCase());
	commandFactory.registerCommand<Saber1hFlurry2Command>(String("saber1hFlurry2").toLowerCase());
	commandFactory.registerCommand<Saber1hHeadHit1Command>(String("saber1hHeadHit1").toLowerCase());
	commandFactory.registerCommand<Saber1hHeadHit2Command>(String("saber1hHeadHit2").toLowerCase());
	commandFactory.registerCommand<Saber1hHeadHit3Command>(String("saber1hHeadHit3").toLowerCase());
	commandFactory.registerCommand<Saber1hHit1Command>(String("saber1hHit1").toLowerCase());
	commandFactory.registerCommand<Saber1hHit2Command>(String("saber1hHit2").toLowerCase());
	commandFactory.registerCommand<Saber1hHit3Command>(String("saber1hHit3").toLowerCase());
	commandFactory.registerCommand<Saber2hBodyHit1Command>(String("saber2hBodyHit1").toLowerCase());
	commandFactory.registerCommand<Saber2hBodyHit2Command>(String("saber2hBodyHit2").toLowerCase());
	commandFactory.registerCommand<Saber2hBodyHit3Command>(String("saber2hBodyHit3").toLowerCase());
	commandFactory.registerCommand<Saber2hFrenzyCommand>(String("saber2hFrenzy").toLowerCase());
	commandFactory.registerCommand<Saber2hHit1Command>(String("saber2hHit1").toLowerCase());
	commandFactory.registerCommand<Saber2hHit2Command>(String("saber2hHit2").toLowerCase());
	commandFactory.registerCommand<Saber2hHit3Command>(String("saber2hHit3").toLowerCase());
	commandFactory.registerCommand<Saber2hPhantomCommand>(String("saber2hPhantom").toLowerCase());
	commandFactory.registerCommand<Saber2hSweep1Command>(String("saber2hSweep1").toLowerCase());
	commandFactory.registerCommand<Saber2hSweep2Command>(String("saber2hSweep2").toLowerCase());
	commandFactory.registerCommand<Saber2hSweep3Command>(String("saber2hSweep3").toLowerCase());
	commandFactory.registerCommand<SaberPolearmDervishCommand>(String("saberPolearmDervish").toLowerCase());
	commandFactory.registerCommand<SaberPolearmDervish2Command>(String("saberPolearmDervish2").toLowerCase());
	commandFactory.registerCommand<SaberPolearmHit1Command>(String("saberPolearmHit1").toLowerCase());
	commandFactory.registerCommand<SaberPolearmHit2Command>(String("saberPolearmHit2").toLowerCase());
	commandFactory.registerCommand<SaberPolearmHit3Command>(String("saberPolearmHit3").toLowerCase());
	commandFactory.registerCommand<SaberPolearmLegHit1Command>(String("saberPolearmLegHit1").toLowerCase());
	commandFactory.registerCommand<SaberPolearmLegHit2Command>(String("saberPolearmLegHit2").toLowerCase());
	commandFactory.registerCommand<SaberPolearmLegHit3Command>(String("saberPolearmLegHit3").toLowerCase());
	commandFactory.registerCommand<SaberPolearmSpinAttack1Command>(String("saberPolearmSpinAttack1").toLowerCase());
	commandFactory.registerCommand<SaberPolearmSpinAttack2Command>(String("saberPolearmSpinAttack2").toLowerCase());
	commandFactory.registerCommand<SaberPolearmSpinAttack3Command>(String("saberPolearmSpinAttack3").toLowerCase());
	commandFactory.registerCommand<SaberSlash1Command>(String("saberSlash1").toLowerCase());
	commandFactory.registerCommand<SaberSlash2Command>(String("saberSlash2").toLowerCase());
	commandFactory.registerCommand<SaberThrow1Command>(String("saberThrow1").toLowerCase());
	commandFactory.registerCommand<SaberThrow2Command>(String("saberThrow2").toLowerCase());
	commandFactory.registerCommand<SaberThrow3Command>(String("saberThrow3").toLowerCase());
	commandFactory.registerCommand<SampleCommand>(String("sample").toLowerCase());
	commandFactory.registerCommand<SampleDNACommand>(String("sampleDNA").toLowerCase());
	commandFactory.registerCommand<ScatterShot1Command>(String("scatterShot1").toLowerCase());
	commandFactory.registerCommand<ScatterShot2Command>(String("scatterShot2").toLowerCase());
	commandFactory.registerCommand<ScriptCommand>(String("script").toLowerCase());
	commandFactory.registerCommand<SearchCorpseCommand>(String("searchCorpse").toLowerCase());
	commandFactory.registerCommand<SecretSpawnSpamCommand>(String("secretSpawnSpam").toLowerCase());
	commandFactory.registerCommand<SeGogglesCommand>(String("seGoggles").toLowerCase());
	commandFactory.registerCommand<SelectDraftSchematicCommand>(String("selectDraftSchematic").toLowerCase());
	commandFactory.registerCommand<ServerCommand>(String("server").toLowerCase());
	commandFactory.registerCommand<ServerDestroyObjectCommand>(String("serverDestroyObject").toLowerCase());
	commandFactory.registerCommand<ServerSysGroupCommand>(String("serverSysGroup").toLowerCase());
	commandFactory.registerCommand<SetBiographyAdminCommand>(String("setBiographyAdmin").toLowerCase());
	commandFactory.registerCommand<SetBiographyCommand>(String("setBiography").toLowerCase());
	commandFactory.registerCommand<SetBoostmoraleCommand>(String("setBoostmorale").toLowerCase());
	commandFactory.registerCommand<SetChargeCommand>(String("setCharge").toLowerCase());
	commandFactory.registerCommand<SetCurrentSkillTitleCommand>(String("setCurrentSkillTitle").toLowerCase());
	commandFactory.registerCommand<SetExperienceCommand>(String("setExperience").toLowerCase());
	commandFactory.registerCommand<SetFactionCommand>(String("setFaction").toLowerCase());
	commandFactory.registerCommand<SetFactionStandingCommand>(String("setFactionStanding").toLowerCase());
	commandFactory.registerCommand<SetFirstNameCommand>(String("setFirstName").toLowerCase());
	commandFactory.registerCommand<SetFormupCommand>(String("setFormup").toLowerCase());
	commandFactory.registerCommand<SetGodModeCommand>(String("setGodMode").toLowerCase());
	commandFactory.registerCommand<SetHueCommand>(String("setHue").toLowerCase());
	commandFactory.registerCommand<SetIntimidateCommand>(String("setIntimidate").toLowerCase());
	commandFactory.registerCommand<SetLastNameCommand>(String("setLastName").toLowerCase());
	commandFactory.registerCommand<SetLoginMessageCommand>(String("setLoginMessage").toLowerCase());
	commandFactory.registerCommand<SetLoginTitleCommand>(String("setLoginTitle").toLowerCase());
	commandFactory.registerCommand<SetMatchMakingCharacterIdCommand>(String("setMatchMakingCharacterId").toLowerCase());
	commandFactory.registerCommand<SetMatchMakingPersonalIdCommand>(String("setMatchMakingPersonalId").toLowerCase());
	commandFactory.registerCommand<SetMaximumSpawnTimeCommand>(String("setMaximumSpawnTime").toLowerCase());
	commandFactory.registerCommand<SetMinimumSpawnTimeCommand>(String("setMinimumSpawnTime").toLowerCase());
	commandFactory.registerCommand<SetMoodCommand>(String("setMood").toLowerCase());
	commandFactory.registerCommand<SetMoodInternalCommand>(String("setMoodInternal").toLowerCase());
	commandFactory.registerCommand<SetNameCommand>(String("setName").toLowerCase());
	commandFactory.registerCommand<SetNameCommand>(String("setName").toLowerCase());
	commandFactory.registerCommand<SetOwnerCommand>(String("setOwner").toLowerCase());
	commandFactory.registerCommand<SetPerformanceBuffTargetCommand>(String("setPerformanceBuffTarget").toLowerCase());
	commandFactory.registerCommand<SetpermissionCommand>(String("setpermission").toLowerCase());
	commandFactory.registerCommand<SetPlanetLimitCommand>(String("setPlanetLimit").toLowerCase());
	commandFactory.registerCommand<SetPlayerAppearanceCommand>(String("setPlayerAppearance").toLowerCase());
	commandFactory.registerCommand<SetPlayerStateCommand>(String("setPlayerState").toLowerCase());
	commandFactory.registerCommand<SetprivacyCommand>(String("setprivacy").toLowerCase());
	commandFactory.registerCommand<SetPublicStateCommand>(String("setPublicState").toLowerCase());
	commandFactory.registerCommand<SetRankCommand>(String("setRank").toLowerCase());
	commandFactory.registerCommand<SetRetreatCommand>(String("setRetreat").toLowerCase());
	commandFactory.registerCommand<SetSpeedCommand>(String("setSpeed").toLowerCase());
	commandFactory.registerCommand<SetSpokenLanguageCommand>(String("setSpokenLanguage").toLowerCase());
	commandFactory.registerCommand<SetSteadyaimCommand>(String("setSteadyaim").toLowerCase());
	commandFactory.registerCommand<SetTEFCommand>(String("setTEF").toLowerCase());
	commandFactory.registerCommand<SetVeteranRewardCommand>(String("setVeteranReward").toLowerCase());
	commandFactory.registerCommand<SetWarcryCommand>(String("setWarcry").toLowerCase());
	commandFactory.registerCommand<SetWaypointActiveStatusCommand>(String("setWaypointActiveStatus").toLowerCase());
	commandFactory.registerCommand<SetWaypointNameCommand>(String("setWaypointName").toLowerCase());
	commandFactory.registerCommand<ShowCouncilRankCommand>(String("showCouncilRank").toLowerCase());
	commandFactory.registerCommand<ShowDanceVisualsCommand>(String("showDanceVisuals").toLowerCase());
	commandFactory.registerCommand<ShowFactionInformationCommand>(String("showFactionInformation").toLowerCase());
	commandFactory.registerCommand<ShowMusicianVisualsCommand>(String("showMusicianVisuals").toLowerCase());
	commandFactory.registerCommand<ShowPvPRatingCommand>(String("showPvPRating").toLowerCase());
	commandFactory.registerCommand<ShowSpawnRegionCommand>(String("showSpawnRegion").toLowerCase());
	commandFactory.registerCommand<SitServerCommand>(String("sitServer").toLowerCase());
	commandFactory.registerCommand<SkillCommand>(String("skill").toLowerCase());
	commandFactory.registerCommand<SmokebombCommand>(String("smokebomb").toLowerCase());
	commandFactory.registerCommand<SniperShotCommand>(String("sniperShot").toLowerCase());
	commandFactory.registerCommand<SnoopCommand>(String("snoop").toLowerCase());
	commandFactory.registerCommand<SocialCommand>(String("social").toLowerCase());
	commandFactory.registerCommand<SocialInternalCommand>(String("socialInternal").toLowerCase());
	commandFactory.registerCommand<SpatialChatCommand>(String("spatialChat").toLowerCase());
	commandFactory.registerCommand<SpatialChatInternalCommand>(String("spatialChatInternal").toLowerCase());
	commandFactory.registerCommand<SpawnStatusCommand>(String("spawnStatus").toLowerCase());
	commandFactory.registerCommand<SplitCreditsWithGroupCommand>(String("splitCreditsWithGroup").toLowerCase());
	commandFactory.registerCommand<SpotlightCommand>(String("spotlight").toLowerCase());
	commandFactory.registerCommand<SprayShotCommand>(String("sprayShot").toLowerCase());
	commandFactory.registerCommand<StandCommand>(String("stand").toLowerCase());
	commandFactory.registerCommand<StartBandCommand>(String("startBand").toLowerCase());
	commandFactory.registerCommand<StartCitySpawnerCommand>(String("startCitySpawner").toLowerCase());
	commandFactory.registerCommand<StartDanceCommand>(String("startDance").toLowerCase());
	commandFactory.registerCommand<StartleShot1Command>(String("startleShot1").toLowerCase());
	commandFactory.registerCommand<StartleShot2Command>(String("startleShot2").toLowerCase());
	commandFactory.registerCommand<StartMusicCommand>(String("startMusic").toLowerCase());
	commandFactory.registerCommand<StartSpawnerCommand>(String("startSpawner").toLowerCase());
	commandFactory.registerCommand<StartTargetSpawnerCommand>(String("startTargetSpawner").toLowerCase());
	commandFactory.registerCommand<StartTraceLoggingCommand>(String("startTraceLogging").toLowerCase());
	commandFactory.registerCommand<StatCommand>(String("stat").toLowerCase());
	commandFactory.registerCommand<SteadyaimCommand>(String("steadyaim").toLowerCase());
	commandFactory.registerCommand<StopBandCommand>(String("stopBand").toLowerCase());
	commandFactory.registerCommand<StopBleedingCommand>(String("stopBleeding").toLowerCase());
	commandFactory.registerCommand<StopCitySpawnerCommand>(String("stopCitySpawner").toLowerCase());
	commandFactory.registerCommand<StopCraftingSessionCommand>(String("stopCraftingSession").toLowerCase());
	commandFactory.registerCommand<StopDanceCommand>(String("stopDance").toLowerCase());
	commandFactory.registerCommand<StoplisteningCommand>(String("stoplistening").toLowerCase());
	commandFactory.registerCommand<StopMusicCommand>(String("stopMusic").toLowerCase());
	commandFactory.registerCommand<StoppingShotCommand>(String("stoppingShot").toLowerCase());
	commandFactory.registerCommand<StopSpawnerCommand>(String("stopSpawner").toLowerCase());
	commandFactory.registerCommand<StopTargetSpawnerCommand>(String("stopTargetSpawner").toLowerCase());
	commandFactory.registerCommand<StopTraceLoggingCommand>(String("stopTraceLogging").toLowerCase());
	commandFactory.registerCommand<StopwatchingCommand>(String("stopwatching").toLowerCase());
	commandFactory.registerCommand<StrafeShot1Command>(String("strafeShot1").toLowerCase());
	commandFactory.registerCommand<StrafeShot2Command>(String("strafeShot2").toLowerCase());
	commandFactory.registerCommand<StructurestatusCommand>(String("structurestatus").toLowerCase());
	commandFactory.registerCommand<StunAttackCommand>(String("stunAttack").toLowerCase());
	commandFactory.registerCommand<SuppressionFire1Command>(String("suppressionFire1").toLowerCase());
	commandFactory.registerCommand<SuppressionFire2Command>(String("suppressionFire2").toLowerCase());
	commandFactory.registerCommand<SurpriseShotCommand>(String("surpriseShot").toLowerCase());
	commandFactory.registerCommand<SurrenderSkillCommand>(String("surrenderSkill").toLowerCase());
	commandFactory.registerCommand<SurveyCommand>(String("survey").toLowerCase());
	commandFactory.registerCommand<SynchronizedUiListenCommand>(String("synchronizedUiListen").toLowerCase());
	commandFactory.registerCommand<SynchronizedUiStopListeningCommand>(String("synchronizedUiStopListening").toLowerCase());
	commandFactory.registerCommand<SystemMessageCommand>(String("systemMessage").toLowerCase());
	commandFactory.registerCommand<TakeCoverCommand>(String("takeCover").toLowerCase());
	commandFactory.registerCommand<TameCommand>(String("tame").toLowerCase());
	commandFactory.registerCommand<TargetCommand>(String("target").toLowerCase());
	commandFactory.registerCommand<TauntCommand>(String("taunt").toLowerCase());
	commandFactory.registerCommand<TeachCommand>(String("teach").toLowerCase());
	commandFactory.registerCommand<TeleportCommand>(String("teleport").toLowerCase());
	commandFactory.registerCommand<TeleportTargetCommand>(String("teleportTarget").toLowerCase());
	commandFactory.registerCommand<TeleportToCommand>(String("teleportTo").toLowerCase());
	commandFactory.registerCommand<TellpetCommand>(String("tellpet").toLowerCase());
	commandFactory.registerCommand<TendDamageCommand>(String("tendDamage").toLowerCase());
	commandFactory.registerCommand<TendDamageToolCommand>(String("tendDamageTool").toLowerCase());
	commandFactory.registerCommand<TendWoundCommand>(String("tendWound").toLowerCase());
	commandFactory.registerCommand<TendWoundsToolCommand>(String("tendWoundsTool").toLowerCase());
	commandFactory.registerCommand<ThreatenShotCommand>(String("threatenShot").toLowerCase());
	commandFactory.registerCommand<ThrowGrenadeCommand>(String("throwGrenade").toLowerCase());
	commandFactory.registerCommand<ThrowTrapCommand>(String("throwTrap").toLowerCase());
	commandFactory.registerCommand<TipCommand>(String("tip").toLowerCase());
	commandFactory.registerCommand<ToggleAwayFromKeyBoardCommand>(String("toggleAwayFromKeyBoard").toLowerCase());
	commandFactory.registerCommand<ToggleDisplayingFactionRankCommand>(String("toggleDisplayingFactionRank").toLowerCase());
	commandFactory.registerCommand<TorsoShotCommand>(String("torsoShot").toLowerCase());
	commandFactory.registerCommand<TotalHealOtherCommand>(String("totalHealOther").toLowerCase());
	commandFactory.registerCommand<TotalHealSelfCommand>(String("totalHealSelf").toLowerCase());
	commandFactory.registerCommand<TransferForceCommand>(String("transferForce").toLowerCase());
	commandFactory.registerCommand<TransferItemCommand>(String("transferItem").toLowerCase());
	commandFactory.registerCommand<TransferItemArmorCommand>(String("transferItemArmor").toLowerCase());
	commandFactory.registerCommand<TransferItemMiscCommand>(String("transferItemMisc").toLowerCase());
	commandFactory.registerCommand<TransferItemWeaponCommand>(String("transferItemWeapon").toLowerCase());
	commandFactory.registerCommand<TransferstructureCommand>(String("transferstructure").toLowerCase());
	commandFactory.registerCommand<TumbleToKneelingCommand>(String("tumbleToKneeling").toLowerCase());
	commandFactory.registerCommand<TumbleToProneCommand>(String("tumbleToProne").toLowerCase());
	commandFactory.registerCommand<TumbleToStandingCommand>(String("tumbleToStanding").toLowerCase());
	commandFactory.registerCommand<TurretFireCommand>(String("turretFire").toLowerCase());
	commandFactory.registerCommand<TurretFireManualCommand>(String("turretFireManual").toLowerCase());
	commandFactory.registerCommand<UnarmedBlind1Command>(String("unarmedBlind1").toLowerCase());
	commandFactory.registerCommand<UnarmedBodyHit1Command>(String("unarmedBodyHit1").toLowerCase());
	commandFactory.registerCommand<UnarmedCombo1Command>(String("unarmedCombo1").toLowerCase());
	commandFactory.registerCommand<UnarmedCombo2Command>(String("unarmedCombo2").toLowerCase());
	commandFactory.registerCommand<UnarmedDizzy1Command>(String("unarmedDizzy1").toLowerCase());
	commandFactory.registerCommand<UnarmedHeadHit1Command>(String("unarmedHeadHit1").toLowerCase());
	commandFactory.registerCommand<UnarmedHit1Command>(String("unarmedHit1").toLowerCase());
	commandFactory.registerCommand<UnarmedHit2Command>(String("unarmedHit2").toLowerCase());
	commandFactory.registerCommand<UnarmedHit3Command>(String("unarmedHit3").toLowerCase());
	commandFactory.registerCommand<UnarmedKnockdown1Command>(String("unarmedKnockdown1").toLowerCase());
	commandFactory.registerCommand<UnarmedKnockdown2Command>(String("unarmedKnockdown2").toLowerCase());
	commandFactory.registerCommand<UnarmedLegHit1Command>(String("unarmedLegHit1").toLowerCase());
	commandFactory.registerCommand<UnarmedLunge1Command>(String("unarmedLunge1").toLowerCase());
	commandFactory.registerCommand<UnarmedLunge2Command>(String("unarmedLunge2").toLowerCase());
	commandFactory.registerCommand<UnarmedSpinAttack1Command>(String("unarmedSpinAttack1").toLowerCase());
	commandFactory.registerCommand<UnarmedSpinAttack2Command>(String("unarmedSpinAttack2").toLowerCase());
	commandFactory.registerCommand<UnarmedStun1Command>(String("unarmedStun1").toLowerCase());
	commandFactory.registerCommand<UnassociateDroidControlDeviceWithShipCommand>(String("unassociateDroidControlDeviceWithShip").toLowerCase());
	commandFactory.registerCommand<UnCityBanCommand>(String("unCityBan").toLowerCase());
	commandFactory.registerCommand<UnconsentCommand>(String("unconsent").toLowerCase());
	commandFactory.registerCommand<UnderHandShotCommand>(String("underHandShot").toLowerCase());
	commandFactory.registerCommand<UnfreezePlayerCommand>(String("unfreezePlayer").toLowerCase());
	commandFactory.registerCommand<UninstallShipComponentCommand>(String("uninstallShipComponent").toLowerCase());
	commandFactory.registerCommand<UninviteCommand>(String("uninvite").toLowerCase());
	commandFactory.registerCommand<UnsnoopCommand>(String("unsnoop").toLowerCase());
	commandFactory.registerCommand<UseReconDroneCommand>(String("useReconDrone").toLowerCase());
	commandFactory.registerCommand<UseSkillBuffCommand>(String("useSkillBuff").toLowerCase());
	commandFactory.registerCommand<VentriloquismCommand>(String("ventriloquism").toLowerCase());
	commandFactory.registerCommand<ToggleCombatTauntsCommand>(String("toggleCombatTaunts").toLowerCase());
	commandFactory.registerCommand<VertFurnitureCommand>(String("vertFurniture").toLowerCase());
	commandFactory.registerCommand<VitalizeCommand>(String("vitalize").toLowerCase());
	commandFactory.registerCommand<VolleyFireCommand>(String("volleyFire").toLowerCase());
	commandFactory.registerCommand<VolleyFireAttackCommand>(String("volleyFireAttack").toLowerCase());
	commandFactory.registerCommand<Warcry1Command>(String("warcry1").toLowerCase());
	commandFactory.registerCommand<Warcry2Command>(String("warcry2").toLowerCase());
	commandFactory.registerCommand<WarningShotCommand>(String("warningShot").toLowerCase());
	commandFactory.registerCommand<WatchCommand>(String("watch").toLowerCase());
	commandFactory.registerCommand<WildShot1Command>(String("wildShot1").toLowerCase());
	commandFactory.registerCommand<WildShot2Command>(String("wildShot2").toLowerCase());
	commandFactory.registerCommand<WipeItemsCommand>(String("wipeItems").toLowerCase());
	commandFactory.registerCommand<WookieeRoarCommand>(String("wookieeRoar").toLowerCase());
	commandFactory.registerCommand<CityInfoCommand>(String("cityInfo").toLowerCase());
	commandFactory.registerCommand<GroupLootCommand>(String("groupLoot").toLowerCase());
	commandFactory.registerCommand<OpenLotteryContainerCommand>(String("openLotteryContainer").toLowerCase());
	commandFactory.registerCommand<CloseLotteryContainerCommand>(String("closeLotteryContainer").toLowerCase());
	commandFactory.registerCommand<RequestQuestTimersAndCountersCommand>(String("requestQuestTimersAndCounters").toLowerCase());
	commandFactory.registerCommand<EjectCommand>(String("eject").toLowerCase());
	commandFactory.registerCommand<LaunchIntoSpaceCommand>(String("launchIntoSpace").toLowerCase());
	commandFactory.registerCommand<UnstickCommand>(String("unstick").toLowerCase());
	commandFactory.registerCommand<WaypointCommand>(String("waypoint").toLowerCase());
	commandFactory.registerCommand<CreateVendorCommand>(String("createVendor").toLowerCase());
	commandFactory.registerCommand<PilotShipCommand>(String("pilotShip").toLowerCase());
	commandFactory.registerCommand<UnpilotShipCommand>(String("unpilotShip").toLowerCase());
	commandFactory.registerCommand<LeaveStationCommand>(String("leaveStation").toLowerCase());
	commandFactory.registerCommand<OpenWingsCommand>(String("openWings").toLowerCase());
	commandFactory.registerCommand<CloseWingsCommand>(String("closeWings").toLowerCase());
	commandFactory.registerCommand<LaunchMissileCommand>(String("launchMissile").toLowerCase());
	commandFactory.registerCommand<LaunchCountermeasureCommand>(String("launchCountermeasure").toLowerCase());
	commandFactory.registerCommand<BoosterOnCommand>(String("boosterOn").toLowerCase());
	commandFactory.registerCommand<BoosterOffCommand>(String("boosterOff").toLowerCase());
	commandFactory.registerCommand<InspectCommand>(String("inspect").toLowerCase());
	commandFactory.registerCommand<DockCommand>(String("dock").toLowerCase());
	commandFactory.registerCommand<PumpreactorCommand>(String("pumpreactor").toLowerCase());
	commandFactory.registerCommand<IffscrambleCommand>(String("iffscramble").toLowerCase());
	commandFactory.registerCommand<DroidCommand>(String("droid").toLowerCase());
	commandFactory.registerCommand<LootAllCommand>(String("lootAll").toLowerCase());
	commandFactory.registerCommand<ServerAsteroidDataListenCommand>(String("serverAsteroidDataListen").toLowerCase());
	commandFactory.registerCommand<ServerAsteroidDataStopListeningCommand>(String("serverAsteroidDataStopListening").toLowerCase());
	commandFactory.registerCommand<DisableTargetCommand>(String("disableTarget").toLowerCase());
	commandFactory.registerCommand<DestroyTargetCommand>(String("destroyTarget").toLowerCase());
	commandFactory.registerCommand<SendFormObjectDataCommand>(String("sendFormObjectData").toLowerCase());
	commandFactory.registerCommand<WaypointCommand>(String("waypoint").toLowerCase());
	commandFactory.registerCommand<InspacerepairCommand>(String("inspacerepair").toLowerCase());
	commandFactory.registerCommand<LightEngineScrambleCommand>(String("lightEngineScramble").toLowerCase());
	commandFactory.registerCommand<HyperspaceCommand>(String("hyperspace").toLowerCase());
	commandFactory.registerCommand<AborthyperspaceCommand>(String("aborthyperspace").toLowerCase());
	commandFactory.registerCommand<EweaponsCommand>(String("eweapons").toLowerCase());
	commandFactory.registerCommand<EshieldsCommand>(String("eshields").toLowerCase());
	commandFactory.registerCommand<EthrustCommand>(String("ethrust").toLowerCase());
	commandFactory.registerCommand<VrepairCommand>(String("vrepair").toLowerCase());
	commandFactory.registerCommand<Bstrike1Command>(String("bstrike1").toLowerCase());
	commandFactory.registerCommand<Bstrike2Command>(String("bstrike2").toLowerCase());
	commandFactory.registerCommand<Bstrike3Command>(String("bstrike3").toLowerCase());
	commandFactory.registerCommand<Ptrap1Command>(String("ptrap1").toLowerCase());
	commandFactory.registerCommand<Ptrap2Command>(String("ptrap2").toLowerCase());
	commandFactory.registerCommand<Epulse1Command>(String("epulse1").toLowerCase());
	commandFactory.registerCommand<Epulse2Command>(String("epulse2").toLowerCase());
	commandFactory.registerCommand<Epulse3Command>(String("epulse3").toLowerCase());
	commandFactory.registerCommand<NblastCommand>(String("nblast").toLowerCase());
	commandFactory.registerCommand<VrepairotherCommand>(String("vrepairother").toLowerCase());
	commandFactory.registerCommand<UndockCommand>(String("undock").toLowerCase());
	commandFactory.registerCommand<Jstart1Command>(String("jstart1").toLowerCase());
	commandFactory.registerCommand<Jstart2Command>(String("jstart2").toLowerCase());
	commandFactory.registerCommand<Jstart3Command>(String("jstart3").toLowerCase());
	commandFactory.registerCommand<EscapePodCommand>(String("escapePod").toLowerCase());
	commandFactory.registerCommand<InspacereloadCommand>(String("inspacereload").toLowerCase());
	commandFactory.registerCommand<InspacerrCommand>(String("inspacerr").toLowerCase());
	commandFactory.registerCommand<RequestSpaceTrainerCommand>(String("requestSpaceTrainer").toLowerCase());

	//pet commands
	commandFactory.registerCommand<PetAttackCommand>(String("petAttack").toLowerCase());
	commandFactory.registerCommand<PetEmoteCommand>(String("petEmote").toLowerCase());
	commandFactory.registerCommand<PetFeedCommand>(String("petFeed").toLowerCase());
	commandFactory.registerCommand<PetFollowCommand>(String("petFollow").toLowerCase());
	commandFactory.registerCommand<PetFriendCommand>(String("petFriend").toLowerCase());
	commandFactory.registerCommand<PetGroupCommand>(String("petGroup").toLowerCase());
	commandFactory.registerCommand<PetGuardCommand>(String("petGuard").toLowerCase());
	commandFactory.registerCommand<PetRangedAttackCommand>(String("petRangedAttack").toLowerCase());
	commandFactory.registerCommand<PetRechargeCommand>(String("petRecharge").toLowerCase());
	commandFactory.registerCommand<PetRechargeOtherCommand>(String("petRechargeOther").toLowerCase());
	commandFactory.registerCommand<PetRecoverCommand>(String("petRecover").toLowerCase());
	commandFactory.registerCommand<PetSpecialAttackCommand>(String("petSpecialAttack").toLowerCase());
	commandFactory.registerCommand<PetStayCommand>(String("petStay").toLowerCase());
	commandFactory.registerCommand<PetStoreCommand>(String("petStore").toLowerCase());
	commandFactory.registerCommand<PetTransferCommand>(String("petTransfer").toLowerCase());
	commandFactory.registerCommand<PetTrickCommand>(String("petTrick").toLowerCase());
	commandFactory.registerCommand<PetRepairCommand>(String("petRepair").toLowerCase());
	commandFactory.registerCommand<PetThrowCommand>(String("petThrow").toLowerCase());
	commandFactory.registerCommand<PetHarvestCommand>(String("petHarvest").toLowerCase());
	commandFactory.registerCommand<PetPatrolCommand>(String("petPatrol").toLowerCase());
	commandFactory.registerCommand<PetClearPatrolPointsCommand>(String("petClearPatrolPoints").toLowerCase());
	commandFactory.registerCommand<PetGetPatrolPointCommand>(String("petGetPatrolPoint").toLowerCase());
}
