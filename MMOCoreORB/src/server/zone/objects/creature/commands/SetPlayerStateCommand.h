/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETPLAYERSTATECOMMAND_H_
#define SETPLAYERSTATECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class SetPlayerStateCommand : public QueueCommand {
public:

	SetPlayerStateCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		UnicodeTokenizer tok(arguments);
		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(target);

		CreatureObject* targetCreature = creature;

		if (obj == NULL || !obj->isPlayerCreature()) {
			if (!tok.hasMoreTokens())
				return INVALIDSYNTAX;

			String targetName;
			tok.getStringToken(targetName);
			obj = server->getPlayerManager()->getPlayer(targetName);

			//The command issuer is the target if they have not specified a target or name.
			if (obj != NULL && obj->isPlayerCreature())
				targetCreature = obj.castTo<CreatureObject*>();
		} else {
			targetCreature = obj.castTo<CreatureObject*>();
		}

		if (!tok.hasMoreTokens())
			return INVALIDSYNTAX;

		String state;
		tok.getStringToken(state);

		uint64 stateID = CreatureState::instance()->getState(state);

		Locker _clock(targetCreature, creature);

		String actionName;

		if (targetCreature->hasState(stateID)) {
			targetCreature->clearState(stateID, true);
			actionName = "cleared";
		} else {
			targetCreature->setState(stateID, true);
			actionName = "set";
		}

		creature->sendSystemMessage("You have " + actionName + " " + targetCreature->getDisplayedName() + "'s '" + state + "' state.");

		return SUCCESS;
	}

	String getSyntax() const {
		return String("/setPlayerState [target|name] {state}");
	}

};

#endif //SETPLAYERSTATECOMMAND_H_
