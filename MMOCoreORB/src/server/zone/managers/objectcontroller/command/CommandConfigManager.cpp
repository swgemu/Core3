/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#include "CommandConfigManager.h"

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"

#include "server/zone/objects/intangible/PetControlDevice.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/Creature.h"

#include "server/zone/objects/player/sessions/crafting/CraftingSession.h"

#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/group/GroupManager.h"

#include "server/zone/objects/group/GroupObject.h"

#include "server/zone/packets/object/CombatSpam.h"
#include "server/zone/packets/object/CombatAction.h"

#include "server/zone/objects/creature/commands/AdminCommand.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"
#include "server/zone/objects/creature/commands/SquadLeaderCommand.h"
#include "server/zone/objects/creature/commands/ForceHealQueueCommand.h"
#include "server/zone/objects/creature/commands/JediQueueCommand.h"
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

#include "server/zone/objects/creature/commands/JediQueueCommand.h"

#include "templates/datatables/DataTableIff.h"
#include "templates/datatables/DataTableRow.h"
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
	setGlobalLong("FEIGNDEATH_STATE", CreatureState::FEIGNDEATH);
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
	setGlobalInt("NO_ATTRIBUTE", CombatManager::NONE);
	setGlobalInt("HEALTH_ATTRIBUTE", CombatManager::HEALTH);
	setGlobalInt("ACTION_ATTRIBUTE", CombatManager::ACTION);
	setGlobalInt("MIND_ATTRIBUTE", CombatManager::MIND);
	setGlobalInt("RANDOM_ATTRIBUTE", CombatManager::RANDOM);

	setGlobalInt("HEALTH", CreatureAttribute::HEALTH);
	setGlobalInt("ACTION", CreatureAttribute::ACTION);
	setGlobalInt("MIND", CreatureAttribute::MIND);
	setGlobalInt("ATTACK_POOL", CreatureAttribute::UNKNOWN);

	// weapons
	setGlobalInt("ANYWEAPON", SharedWeaponObjectTemplate::ANYWEAPON);
	setGlobalInt("THROWNWEAPON", SharedWeaponObjectTemplate::THROWNWEAPON);
	setGlobalInt("HEAVYWEAPON", SharedWeaponObjectTemplate::HEAVYWEAPON);
	setGlobalInt("MINEWEAPON", SharedWeaponObjectTemplate::MINEWEAPON);
	setGlobalInt("SPECIALHEAVYWEAPON", SharedWeaponObjectTemplate::SPECIALHEAVYWEAPON);
	setGlobalInt("UNARMEDWEAPON", SharedWeaponObjectTemplate::UNARMEDWEAPON);
	setGlobalInt("ONEHANDMELEEWEAPON", SharedWeaponObjectTemplate::ONEHANDMELEEWEAPON);
	setGlobalInt("TWOHANDMELEEWEAPON", SharedWeaponObjectTemplate::TWOHANDMELEEWEAPON);
	setGlobalInt("POLEARMWEAPON", SharedWeaponObjectTemplate::POLEARMWEAPON);
	setGlobalInt("PISTOLWEAPON", SharedWeaponObjectTemplate::PISTOLWEAPON);
	setGlobalInt("CARBINEWEAPON", SharedWeaponObjectTemplate::CARBINEWEAPON);
	setGlobalInt("RIFLEWEAPON", SharedWeaponObjectTemplate::RIFLEWEAPON);
	setGlobalInt("GRENADEWEAPON", SharedWeaponObjectTemplate::GRENADEWEAPON);
	setGlobalInt("LIGHTNINGRIFLEWEAPON", SharedWeaponObjectTemplate::LIGHTNINGRIFLEWEAPON);
	setGlobalInt("ONEHANDJEDIWEAPON", SharedWeaponObjectTemplate::ONEHANDJEDIWEAPON);
	setGlobalInt("TWOHANDJEDIWEAPON", SharedWeaponObjectTemplate::TWOHANDJEDIWEAPON);
	setGlobalInt("POLEARMJEDIWEAPON", SharedWeaponObjectTemplate::POLEARMJEDIWEAPON);
	setGlobalInt("MELEEWEAPON", SharedWeaponObjectTemplate::MELEEWEAPON);
	setGlobalInt("RANGEDWEAPON", SharedWeaponObjectTemplate::RANGEDWEAPON);
	setGlobalInt("JEDIWEAPON", SharedWeaponObjectTemplate::JEDIWEAPON);

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
	setGlobalInt("ATTACKER_FORCE_STANDING", CommandEffect::ATTACKER_FORCE_STAND);
	setGlobalInt("ATTACKER_FORCE_CROUCH", CommandEffect::ATTACKER_FORCE_CROUCH);
	setGlobalInt("ATTACKER_FORCE_PRONE", CommandEffect::ATTACKER_FORCE_PRONE);

	// trails
	setGlobalInt("NOTRAIL", CombatManager::NOTRAIL);
	setGlobalInt("LEFTFOOTTRAIL", CombatManager::LEFTFOOTTRAIL);
	setGlobalInt("RIGHTFOOTTRAIL", CombatManager::RIGHTFOOTTRAIL);
	setGlobalInt("LEFTHANDTRAIL", CombatManager::LEFTHANDTRAIL);
	setGlobalInt("RIGHTHANDTRAIL", CombatManager::RIGHTHANDTRAIL);
	setGlobalInt("WEAPONTRAIL", CombatManager::WEAPONTRAIL);
	setGlobalInt("DEFAULTTRAIL", CombatManager::DEFAULTTRAIL);

	// damage types
	setGlobalInt("KINETIC_DAMAGE", SharedWeaponObjectTemplate::KINETIC);
	setGlobalInt("ENERGY_DAMAGE", SharedWeaponObjectTemplate::ENERGY);
	setGlobalInt("BLAST_DAMAGE", SharedWeaponObjectTemplate::BLAST);
	setGlobalInt("STUN_DAMAGE", SharedWeaponObjectTemplate::STUN);
	setGlobalInt("LIGHTSABER_DAMAGE", SharedWeaponObjectTemplate::LIGHTSABER);
	setGlobalInt("HEAT_DAMAGE", SharedWeaponObjectTemplate::HEAT);
	setGlobalInt("COLD_DAMAGE", SharedWeaponObjectTemplate::COLD);
	setGlobalInt("ACID_DAMAGE", SharedWeaponObjectTemplate::ACID);
	setGlobalInt("ELECTRICITY_DAMAGE", SharedWeaponObjectTemplate::ELECTRICITY);
    
	// JediQueueCommand buff types
	setGlobalInt("BASE_BUFF", JediQueueCommand::BASE_BUFF);
	setGlobalInt("SINGLE_USE_BUFF", JediQueueCommand::SINGLE_USE_BUFF);
    
	// force heal targets
	setGlobalInt("FORCE_HEAL_TARGET_SELF", ForceHealQueueCommand::TARGET_SELF);
	setGlobalInt("FORCE_HEAL_TARGET_OTHER", ForceHealQueueCommand::TARGET_OTHER);

	//animation generation types
	setGlobalInt("GENERATE_NONE", CombatQueueCommand::GENERATE_NONE);
	setGlobalInt("GENERATE_RANGED", CombatQueueCommand::GENERATE_RANGED);
	setGlobalInt("GENERATE_INTENSITY", CombatQueueCommand::GENERATE_INTENSITY);
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
		if (varName == "forceAttack") {
			combatCommand->setForceAttack((bool)lua_toboolean(L, -1));
			command.pop();
		} else if (varName == "damageMultiplier")
			combatCommand->setDamageMultiplier(Lua::getFloatParameter(L));
		else if (varName == "accuracyBonus")
			combatCommand->setAccuracyBonus(Lua::getIntParameter(L));
		else if (varName == "speedMultiplier")
			combatCommand->setSpeedMultiplier(Lua::getFloatParameter(L));
		else if (varName == "minDamage")
			combatCommand->setMinDamage(Lua::getFloatParameter(L));
		else if (varName == "maxDamage")
			combatCommand->setMaxDamage(Lua::getFloatParameter(L));
		else if (varName == "damageType")
			combatCommand->setDamageType(Lua::getIntParameter(L));
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
		else if (varName == "visMod")
			combatCommand->setVisMod(Lua::getIntParameter(L));
		else if (varName == "coneRange")
			combatCommand->setConeRange(Lua::getIntParameter(L));
		else if (varName == "range")
			combatCommand->setRange(Lua::getIntParameter(L));
		else if (varName == "accuracySkillMod")
			combatCommand->setAccuracySkillMod(Lua::getStringParameter(L));
		else if (varName == "areaAction") {
			combatCommand->setAreaAction((bool)lua_toboolean(L, -1));
			command.pop();
		} else if (varName == "splashDamage") {
			combatCommand->setSplashDamage((bool)lua_toboolean(L, -1));
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
		else if (varName == "animation")
			combatCommand->setAnimationString(Lua::getStringParameter(L));
		else if (varName == "animType")
			combatCommand->setAnimType(Lua::getUnsignedIntParameter(L));
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
		else if(varName == "buffClass")
			jediCommand->setBuffClass(Lua::getIntParameter(L));
		else if(varName == "visMod")
			jediCommand->setVisMod(Lua::getIntParameter(L));
		else if (varName == "duration")
			jediCommand->setDuration(Lua::getIntParameter(L));
		else if (varName == "animationCRC")
			jediCommand->setAnimationCRC(Lua::getIntParameter(L));
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
			else if (varName == "attributesToHeal")
				healCommand->setAttributesToHeal(Lua::getUnsignedIntParameter(L));
			else if (varName == "woundAttributesToHeal")
				healCommand->setWoundAttributesToHeal(Lua::getUnsignedIntParameter(L));
			else if (varName == "forceCostMultiplier")
				healCommand->setForceCostMultiplier(Lua::getFloatParameter(L));
			else if (varName == "range")
				healCommand->setRange(Lua::getIntParameter(L));
			else if (varName == "healBleedingCost")
				healCommand->setHealBleedingCost(Lua::getUnsignedIntParameter(L));
			else if (varName == "healFireCost")
				healCommand->setHealFireCost(Lua::getUnsignedIntParameter(L));
			else if (varName == "healDiseaseCost")
				healCommand->setHealDiseaseCost(Lua::getUnsignedIntParameter(L));
			else if (varName == "healPoisonCost")
				healCommand->setHealPoisonCost(Lua::getUnsignedIntParameter(L));
			else if (varName == "healBattleFatigue")
				healCommand->setHealBattleFatigue(Lua::getUnsignedIntParameter(L));
			else if (varName == "healStateCost")
				healCommand->setHealStateCost(Lua::getUnsignedIntParameter(L));
			else if (varName == "statesToHeal")
				healCommand->setStatesToHeal(Lua::getUnsignedIntParameter(L));
			else if (varName == "bleedHealIterations")
				healCommand->setBleedHealIterations(Lua::getUnsignedIntParameter(L));
			else if (varName == "poisonHealIterations")
				healCommand->setPoisonHealIterations(Lua::getUnsignedIntParameter(L));
			else if (varName == "diseaseHealIterations")
				healCommand->setDiseaseHealIterations(Lua::getUnsignedIntParameter(L));
			else if (varName == "fireHealIterations")
				healCommand->setFireHealIterations(Lua::getUnsignedIntParameter(L));
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
	registerCommands2();
	registerCommands3();
	registerCommands4();

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
