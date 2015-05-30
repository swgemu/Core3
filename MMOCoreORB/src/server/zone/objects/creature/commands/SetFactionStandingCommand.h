/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SETFACTIONSTANDINGCOMMAND_H_
#define SETFACTIONSTANDINGCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/faction/FactionManager.h"

class SetFactionStandingCommand : public QueueCommand {
public:

	SetFactionStandingCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	void sendInvalidParameterMessage(CreatureObject* creature) const {
		creature->sendSystemMessage("Invalid parameter. Format is /setFactionStanding <player> <faction name> <value>");
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		//make sure that the target is a player
		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(target);

		if (obj == NULL || !obj->isPlayerCreature() ) {
			sendInvalidParameterMessage(creature);
			return INVALIDTARGET;
		}

		CreatureObject* targetCreature = cast<CreatureObject*>( obj.get());

		if ( targetCreature == NULL ) {
			sendInvalidParameterMessage(creature);
			return GENERALERROR;
		}

		Locker _locker(targetCreature, creature);

		UnicodeTokenizer tokenizer(arguments);
		tokenizer.setDelimeter(" ");

		// try to get the faction
		if (!tokenizer.hasMoreTokens()) {
			sendInvalidParameterMessage(creature);
			return INVALIDPARAMETERS;
		}

		String faction;
		tokenizer.getStringToken(faction);

		// check for valid rebel/imperial faction specification
		if (!FactionManager::instance()->isFaction(faction)) {
			sendInvalidParameterMessage(creature);
			return INVALIDPARAMETERS;
		}

		// get the amount of faction points
		if (!tokenizer.hasMoreTokens())
		{
			sendInvalidParameterMessage(creature);
			return INVALIDPARAMETERS;
		}

		int factionValue = -1;

		try {
			factionValue = tokenizer.getIntToken();
		} catch ( Exception& err ) {
			error("error parsing faction value in setfactionstandingcommand");
		}

		PlayerObject* targetPlayer = targetCreature->getPlayerObject();

		if ( targetPlayer == NULL )
			return GENERALERROR;

		int intCurrentFaction = targetPlayer->getFactionStanding(faction);
		int factionDif = intCurrentFaction - factionValue;

		if ( factionValue >= -5000 && factionValue <= 100000 && factionDif != 0) {
			if ( factionValue > intCurrentFaction)
				targetPlayer->increaseFactionStanding(faction,factionValue-intCurrentFaction);
			else
				targetPlayer->decreaseFactionStanding(faction, intCurrentFaction - factionValue);

			creature->sendSystemMessage(faction + " faction standing set to " + String::valueOf(factionValue) + " for " + targetCreature->getFirstName());

		} else {
			if ( factionDif == 0 )
				creature->sendSystemMessage("No faction change");
			else
				creature->sendSystemMessage("Invalid faction amount.  Must be between -5000 and 100k");
		}
		return SUCCESS;
	}

};

#endif //SETFACTIONSTANDINGCOMMAND_H_
