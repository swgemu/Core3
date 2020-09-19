/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef JEDIMINDTRICKCOMMAND_H_
#define JEDIMINDTRICKCOMMAND_H_

//#include "server/zone/objects/creature/commands/JediQueueCommand.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "ForcePowersQueueCommand.h"

class JediMindTrickCommand : public ForcePowersQueueCommand {
public:

	JediMindTrickCommand(const String& name, ZoneProcessServer* server)
		: ForcePowersQueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (isWearingArmor(creature)) {
			return NOJEDIARMOR;
		}

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		Creature* targetCreature = cast<Creature*>(targetObject.get());

		if (targetObject == nullptr){ //|| !targetObject->isCreatureObject()) {
			creature->sendSystemMessage("Target object nullptr");
			return INVALIDTARGET;
		}

		if (targetObject->isCreature()) {
			//creature->sendSystemMessage("@error_message:target_not_npc");
			creature->sendSystemMessage("Target not npc");
			return false;
		}

		if (targetObject->getDistanceTo(creature) > 32.f){
			creature->sendSystemMessage("@error_message:target_out_of_range");
			return false;
		}

		int res = doCombatAction(creature, target);

		if (res == SUCCESS) {

//
			ManagedReference<CreatureObject*> creatureTarget = nullptr;
			ManagedReference<PlayerObject*> ghost = nullptr;
			ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

			StringTokenizer args(arguments.toString());

			if (args.hasMoreTokens()) {
				String character;
				args.getStringToken(character);

				creatureTarget = playerManager->getPlayer(character);

			} else {

				creatureTarget = server->getZoneServer()->getObject(target).castTo<CreatureObject*>();

			}

			if (creatureTarget == nullptr)
				return false;

			ghost = creatureTarget->getPlayerObject();

			Locker clocker(creatureTarget, creature);

			creatureTarget->removeDefender(creature);
			creatureTarget->notifyObservers(ObserverEventType::DEFENDERDROPPED);
			creatureTarget->getThreatMap()->clearAggro(creature);

			creature->doCombatAnimation(creatureTarget, STRING_HASHCODE("mind_trick_1"), 1, 0);
			creature->sendSystemMessage("@jedi_spam:mind_trick_success");

			if (ghost != nullptr && creatureTarget->isPlayerCreature()) {
				//creature->sendSystemMessage("Player Ghost not found");
				//return false;
				creature->clearQueueActions();
				CombatManager::instance()->attemptPeace(creatureTarget);
			}
//

			
			//ManagedReference<Creature*> creatureTarget = targetObject.castTo<Creature*>();
			//if (creatureTarget != nullptr) {


			//if (creatureTarget->isPlayerCreature()) {
			//	creature->clearQueueActions();
			////	CombatManager::instance()->attemptPeace(creatureTarget);
			//}

			creature->clearQueueActions();
			CombatManager::instance()->attemptPeace(creature);

			return SUCCESS;
			//} else {
				//creature->sendSystemMessage("@error_message:targetting_error");
				//creature->sendSystemMessage("else error 1");
				//return false;
			//}
		} else {
			//creature->sendSystemMessage("@jedi_spam:mind_trick_fail");
			//creature->sendSystemMessage("else error2");
			return false;
		}
		return res;
	}

};

#endif //JEDIMINDTRICKCOMMAND_H_
