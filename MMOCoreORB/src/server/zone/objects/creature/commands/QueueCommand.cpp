/*
 * QueueCommand.cpp
 *
 *  Created on: 22/05/2010
 *      Author: victor
 */

#include "QueueCommand.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/frs/FrsManager.h"

QueueCommand::QueueCommand(const String& skillname, ZoneProcessServer* serv) : Logger() {
	server = serv;

	name = skillname;
	nameCRC = skillname.hashCode();

	maxRangeToTarget = 0;

	commandGroup = 0;

	stateMask = 0;
	targetType = 0;
	disabled = false;
	addToQueue = false;
	admin = false;

	defaultTime = 0.f;
	cooldown = 0;
	defaultPriority = NORMAL;

	setLogging(false);
	setGlobalLogging(true);
	setLoggingName("QueueCommand " + skillname);
}

/*
 * Sets the invalid locomotion for this command.
 * Parses the string from LUA's. Format: "4,12,13,"
 */
void QueueCommand::setInvalidLocomotions(const String& lStr) {
	StringTokenizer tokenizer(lStr);
	tokenizer.setDelimeter(",");

	String token = "";
	while (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(token);

		if(!token.isEmpty())
			invalidLocomotion.add(Integer::valueOf(token));
	}
}


/*
 * Checks each invalid locomotion with the player's current locomotion
 */
bool QueueCommand::checkInvalidLocomotions(CreatureObject* creature) const {
	for (int i = 0; i < invalidLocomotion.size(); ++i) {
		if (invalidLocomotion.get(i) == creature->getLocomotion())
			return false;
	}

	return true;
}

/*
*	Checks cell access for the player creature if the target is in a cell
*/
bool QueueCommand::playerEntryCheck(CreatureObject* creature, TangibleObject* target) const {
	if (creature == nullptr || target == nullptr) {
		return false;
	}

	uint64 creoParentID = creature->getParentID();
	uint64 tarParentID = target->getParentID();

	if (!creature->isPlayerCreature() || tarParentID == 0) {
		return true;
	}

	if (creoParentID != tarParentID) {
		Reference<CellObject*> targetCell = target->getParent().get().castTo<CellObject*>();

		if (targetCell != nullptr) {
			ManagedReference<SceneObject*> parentSceneObject = targetCell->getParent().get();

			if (parentSceneObject != nullptr) {
				BuildingObject* buildingObject = parentSceneObject->asBuildingObject();

				if (buildingObject != nullptr && !buildingObject->isAllowedEntry(creature)) {
					return false;
				}
			}

			const ContainerPermissions* perms = targetCell->getContainerPermissions();

			// This portion of the check is specific for locked dungeons doors since they do not inherit perms from parent
			if (!perms->hasInheritPermissionsFromParent() && (creature->getRootParent() == target->getRootParent())) {
				if (!targetCell->checkContainerPermission(creature, ContainerPermissions::WALKIN)) {
					return false;
				}
			}
		}
	}
	return true;
}

void QueueCommand::onStateFail(CreatureObject* creature, uint32 actioncntr) const {
	if (!addToQueue)
		return;

	uint64 states = stateMask & creature->getStateBitmask();

	uint64 state = 1;
	int num = 0;

	while (num < 34) {
		if (states & state) {

			creature->clearQueueAction(actioncntr, 0, 5, num);
			return;

		}

		state *= 2;
		++num;
	}

	creature->error("unknown invalid state in onStateFail");
}

void QueueCommand::onLocomotionFail(CreatureObject* creature, uint32 actioncntr) const {
	if (!checkInvalidLocomotions(creature))
		creature->clearQueueAction(actioncntr, 0, 1, creature->getLocomotion());
}

/*
 * Unsuccessful command completion alerts the player of the invalid state
 */
void QueueCommand::onFail(uint32 actioncntr, CreatureObject* creature, uint32 errorNumber) const {
	StringIdChatParameter prm;
	switch (errorNumber) {
	case INVALIDSYNTAX:
		creature->sendSystemMessage(getSyntax());
		if (addToQueue)
			creature->clearQueueAction(actioncntr);
		break;
	case INVALIDSTATE:
		onStateFail(creature, actioncntr);
		break;
	case INVALIDLOCOMOTION:
		onLocomotionFail(creature, actioncntr);
		break;
	case INVALIDTARGET:
		if (addToQueue)
			creature->clearQueueAction(actioncntr, 0, 3, 0);
		break;
	case INVALIDWEAPON: { // this only gets returned from combat commands
		ManagedReference<WeaponObject*> weapon = creature->getWeapon();
		int attackType = -1;

		if (weapon != nullptr) {
			attackType = weapon->getAttackType();
		}

		switch (attackType) {
		case SharedWeaponObjectTemplate::RANGEDATTACK:
			creature->sendSystemMessage("@cbt_spam:no_attack_ranged_single");
			break;
		case SharedWeaponObjectTemplate::MELEEATTACK:
			creature->sendSystemMessage("@cbt_spam:no_attack_melee_single");
			break;
		default:
			creature->sendSystemMessage("@cbt_spam:no_attack_wrong_weapon"); // Can't be done with this weapon
			break;
		}

		if (addToQueue)
			creature->clearQueueAction(actioncntr);
		break;
	}
	case TOOFAR:
		if (addToQueue)
			creature->clearQueueAction(actioncntr, 0, 4, 0);
		break;

	case NOJEDIARMOR:
		creature->sendSystemMessage("@jedi_spam:not_with_armor"); // You cannot use Force powers or lightsaber abilities while wearing armor.
		if (addToQueue)
			creature->clearQueueAction(actioncntr);

		break;

	case NOSTACKJEDIBUFF:
		creature->sendSystemMessage("@jedi_spam:force_buff_present"); // You are already have a similar Force enhancement active.
		if (addToQueue)
			creature->clearQueueAction(actioncntr);

		break;

	case ALREADYAFFECTEDJEDIPOWER:
			creature->sendSystemMessage("@jedi_spam:power_already_active"); // This target is already affected by that power.
			if (addToQueue)
				creature->clearQueueAction(actioncntr);

			break;

	case NOPRONE:
		if (addToQueue)
			creature->clearQueueAction(actioncntr, 0, 1, 7);

		break;

	case NOKNEELING:
		if (addToQueue)
			creature->clearQueueAction(actioncntr, 0, 1, 4);

		break;
	case INSUFFICIENTPERMISSION:
		creature->sendSystemMessage("@error_message:insufficient_permissions"); //You do not have sufficient permissions to perform the requested action.

		if (addToQueue)
			creature->clearQueueAction(actioncntr);
		break;
	case TOOCLOSE:
		prm.setStringId("combat_effects", "prone_ranged_too_close");
		creature->sendSystemMessage(prm);

		if (addToQueue)
			creature->clearQueueAction(actioncntr);
		break;
	case INSUFFICIENTHAM:
		prm.setStringId("cbt_spam", "pool_drain_fail_single");
		creature->sendSystemMessage(prm);

		if (addToQueue)
			creature->clearQueueAction(actioncntr);
		break;
	default:
		if (addToQueue)
			creature->clearQueueAction(actioncntr);
		break;
	}
}

void QueueCommand::onComplete(uint32 actioncntr, CreatureObject* player, float commandDuration) const {
	if (!player->isPlayerCreature())
		return;

	if (addToQueue) {
		player->clearQueueAction(actioncntr, commandDuration);
	}
}

int QueueCommand::doCommonMedicalCommandChecks(CreatureObject* creature) const {
	if (!checkStateMask(creature))
		return INVALIDSTATE;

	if (!checkInvalidLocomotions(creature))
		return INVALIDLOCOMOTION;

	if (creature->isProne() || creature->isMeditating() || creature->isSwimming()) {
		creature->sendSystemMessage("@error_message:wrong_state"); //You cannot complete that action while in your current state.
		return GENERALERROR;
	}

	if (creature->isRidingMount()) {
		creature->sendSystemMessage("@error_message:survey_on_mount"); //You cannot perform that action while mounted on a creature or driving a vehicle.
		return GENERALERROR;
	}

	return SUCCESS;
}

bool QueueCommand::checkForArenaDuel(CreatureObject* target) const {
	FrsManager* frsManager = server->getZoneServer()->getFrsManager();

	if (frsManager == nullptr)
		return false;

	if (!frsManager->isFrsEnabled())
		return false;

	return frsManager->isPlayerFightingInArena(target->getObjectID());
}

void QueueCommand::checkForTef(CreatureObject* creature, CreatureObject* target) const {
	if (!creature->isPlayerCreature() || creature == target) {
		return;
	}

	PlayerObject* ghost = creature->getPlayerObject().get();

	if (ghost == nullptr) {
		return;
	}

	if (target->isPlayerCreature()) {
		PlayerObject* targetGhost = target->getPlayerObject().get();

		if (targetGhost != nullptr && !CombatManager::instance()->areInDuel(creature, target) && target->getFactionStatus() == FactionStatus::OVERT && targetGhost->hasPvpTef()) {
			ghost->updateLastGcwPvpCombatActionTimestamp();
		}

	} else if (target->isPet()) {
		ManagedReference<CreatureObject*> owner = target->getLinkedCreature().get();

		if (owner != nullptr && owner->isPlayerCreature()) {
			PlayerObject* ownerGhost = owner->getPlayerObject().get();

			if (ownerGhost != nullptr && !CombatManager::instance()->areInDuel(creature, owner) && owner->getFactionStatus() == FactionStatus::OVERT && ownerGhost->hasPvpTef()) {
				ghost->updateLastGcwPvpCombatActionTimestamp();
			}
		}
	}
}

bool QueueCommand::checkCooldown(CreatureObject* creo) const {
	if (cooldown == 0) {
		return true;
	}

	if (creo == nullptr) {
		error() << "checkCooldown() creature is nullptr";
		return true;
	}

	// Provide sane default but should have been set in setCooldown()
	auto cooldownKey = cooldownName.isEmpty() ? "command_" + name : cooldownName;

	if (creo->checkCooldownRecovery(cooldownKey)) {
		creo->addCooldown(cooldownKey, cooldown);
		return true;
	}

	uint32 remain = 0;
	auto cooldownTime = creo->getCooldownTime(cooldownKey);

	if (cooldownTime != nullptr) {
		Time now;
		remain = now.miliDifference(*cooldownTime) / 1000;
	}

	String logMsg;

	if (!cooldownString.isEmpty()) {
		if (cooldownString.charAt(0) == '@') {
			StringIdChatParameter stringIdMsg(cooldownString);
			stringIdMsg.setDI(remain);
			logMsg = stringIdMsg.toString();
			creo->sendSystemMessage(stringIdMsg);
		} else {
			logMsg = cooldownString.replaceFirst("%DI", String::valueOf(remain));
			creo->sendSystemMessage(logMsg);
		}
	} else {
		StringBuffer buf;

		buf << "You can't do /" << name << " again yet, please wait";

		if (remain > 0) {
			buf << " " << remain << (remain == 1 ? " second" : " seconds");
		}

		buf << " before trying again.";
		logMsg = buf.toString();
		creo->sendSystemMessage(logMsg);
	}

	creo->info(admin) << "checkCooldown /" << name << ": remain=" << remain << "; msg=\"" << logMsg << "\"";

	return false;
}
