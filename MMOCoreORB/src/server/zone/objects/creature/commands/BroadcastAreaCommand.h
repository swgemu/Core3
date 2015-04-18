/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BROADCASTAREACOMMAND_H_
#define BROADCASTAREACOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"

class BroadcastAreaCommand : public QueueCommand {
public:

	BroadcastAreaCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		//Check privileges
		if (ghost == NULL || !ghost->isPrivileged())
			return INSUFFICIENTPERMISSION;

		StringTokenizer args(arguments.toString());

		//Explain syntax
		if (!args.hasMoreTokens()) {
			creature->sendSystemMessage("Syntax: /broadcastArea [range] [-event | -rebel | -imperial] <message>");
			return INVALIDPARAMETERS;
		}

		ChatManager* chatManager = server->getZoneServer()->getChatManager();

		//The first argument is the message type, which displays different versions of a broadcast, or the range of the broadcast
		String messageType;
		args.getStringToken(messageType);

		//Default range of broadcast
		float range = 64;

		//Test for range if first argument's character is a number
		if (Character::isDigit(messageType.charAt(0))) {
			try {
				//Test if value is integer
				for (int i = 0; i < messageType.length(); i++) {
					if (!Character::isDigit(messageType.charAt(i)))
						throw Exception("Invalid broadcast range.");
				}

				range = Integer::valueOf(messageType);
				if (range <= 5 || range > 5000) {
					throw Exception("Range must be between 5 and 5000.");
				}
				args.getStringToken(messageType);
			}
			catch (Exception e) {
				creature->sendSystemMessage(e.getMessage());
				return INVALIDPARAMETERS;
			}
		}

		//Get nearby objects from player
		SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
		Zone* zone = creature->getZone();

		if (creature->getCloseObjects() == NULL) {
			creature->info("Null closeobjects vector in BroadcastAreaCommand::doQueueCommand", true);
			zone->getInRangeObjects(creature->getPositionX(), creature->getPositionY(), range, &closeObjects, true);
		}
		else {
			CloseObjectsVector* closeVector = (CloseObjectsVector*) creature->getCloseObjects();
			closeVector->safeCopyTo(closeObjects);
		}

		//Command Options
		if (messageType.charAt(0) == '-') {
			//Help syntax
			if (messageType.toLowerCase() == "-help" || messageType == "-H") {
				creature->sendSystemMessage("Syntax: /broadcastArea [range] [-event | -imperial | -rebel] <message>");
				return GENERALERROR;
			}

			//Creates an event broadcast
			if (messageType.toLowerCase() == "-event" || messageType == "-e") {
				String type = " \\#FFA500[Event]\\#FFFFFF ";
				String message;

				if (!args.hasMoreTokens()) {
					creature->sendSystemMessage("You must include a message!");
					return GENERALERROR;
				}

				while (args.hasMoreTokens()) {
					String messageParts;
					args.getStringToken(messageParts);
					message = message + messageParts + " ";
				}

				//Broadcast to all nearby players
				for (int i = 0; i < closeObjects.size(); i++) {
					SceneObject* targetObject = cast<SceneObject*>(closeObjects.get(i).get());

					if (targetObject->isPlayerCreature() && creature->isInRange(targetObject, range)) {
						CreatureObject* targetPlayer = cast<CreatureObject*>(targetObject);
						targetPlayer->sendSystemMessage(type + message);
					}
				}
				return SUCCESS;
			}

			//Creates an Imperial-only broadcast
			else if (messageType.toLowerCase() == "-imperial" || messageType == "-i") {
				String type = " \\#0000FF[Imperial]\\#FFFFFF ";
				String message;
				String faction = "imperial";

				if (!args.hasMoreTokens()) {
					creature->sendSystemMessage("You must include a message!");
					return GENERALERROR;
				}

				while (args.hasMoreTokens()) {
					String messageParts;
					args.getStringToken(messageParts);
					message = message + messageParts + " ";
				}

				//Broadcast to all nearby imperial players and staff
				for (int i = 0; i < closeObjects.size(); i++) {
					SceneObject* targetObject = cast<SceneObject*>(closeObjects.get(i).get());

					if (targetObject->isPlayerCreature() && creature->isInRange(targetObject, range)) {
						CreatureObject* targetPlayer = cast<CreatureObject*>(targetObject);

						if (targetPlayer->getFaction() == faction.hashCode() || targetPlayer->getPlayerObject()->isPrivileged())
							targetPlayer->sendSystemMessage(type + message);
					}
				}
				return SUCCESS;
			}

			//Creates a Rebel-only broadcast
			else if (messageType.toLowerCase() == "-rebel" || messageType == "-r") {
				String type = " \\#800000[Rebel]\\#FFFFFF ";
				String message;
				String faction = "rebel";

				if (!args.hasMoreTokens()) {
					creature->sendSystemMessage("You must include a message!");
					return GENERALERROR;
				}

				while (args.hasMoreTokens()) {
					String messageParts;
					args.getStringToken(messageParts);
					message = message + messageParts + " ";
				}

				//Broadcast to all nearby rebel players and staff
				for (int i = 0; i < closeObjects.size(); i++) {
					SceneObject* targetObject = cast<SceneObject*>(closeObjects.get(i).get());

					if (targetObject->isPlayerCreature() && creature->isInRange(targetObject, range)) {
						CreatureObject* targetPlayer = cast<CreatureObject*>(targetObject);

						if (targetPlayer->getFaction() == faction.hashCode() || targetPlayer->getPlayerObject()->isPrivileged())
							targetPlayer->sendSystemMessage(type + message);
					}
				}
				return SUCCESS;
			}
			else {
				creature->sendSystemMessage("Invalid option " + messageType);
				return INVALIDPARAMETERS;
			}
		}

		//If no message type is specified, the rest of the arguments are broadcast as a string
		String message = messageType + " ";
		while (args.hasMoreTokens()) {
			String messageParts;
			args.getStringToken(messageParts);
			message = message + messageParts + " ";
		}

		//Broadcast to all nearby players
		for (int i = 0; i < closeObjects.size(); i++) {
			SceneObject* targetObject = cast<SceneObject*>(closeObjects.get(i).get());

			if (targetObject->isPlayerCreature() && creature->isInRange(targetObject, range)) {
					CreatureObject* targetPlayer = cast<CreatureObject*>(targetObject);
					targetPlayer->sendSystemMessage(message);
				}
			}
		return SUCCESS;
	}

};

#endif //BROADCASTAREACOMMAND_H_
