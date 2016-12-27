/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BROADCASTPLANETCOMMAND_H_
#define BROADCASTPLANETCOMMAND_H_

#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/player/PlayerMap.h"

class BroadcastPlanetCommand : public QueueCommand {
public:

	BroadcastPlanetCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		StringTokenizer args(arguments.toString());

		//Explain syntax
		if (!args.hasMoreTokens()) {
			creature->sendSystemMessage("Syntax: /broadcastPlanet [-event | -imperial | -rebel] <message>");
			return INVALIDPARAMETERS;
		}

		ChatManager* chatManager = server->getZoneServer()->getChatManager();
		Locker chatManagerLocker(chatManager);

		PlayerMap* playerMap = chatManager->getPlayerMap();
		playerMap->resetIterator(false);

		//The first argument is the message type, which displays different versions of a broadcast
		String messageType;
		args.getStringToken(messageType);

		//Command Options
		if (messageType.charAt(0) == '-') {
			//Help syntax
			if (messageType.toLowerCase() == "-help" || messageType == "-H") {
				creature->sendSystemMessage("Syntax: /broadcastPlanet [-event | -imperial | -rebel] <message>");
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

				while (playerMap->hasNext(false)) {
					ManagedReference<CreatureObject*> playerObject = playerMap->getNextValue(false);

					if (creature->getPlanetCRC() == playerObject->getPlanetCRC()) {
						playerObject->sendSystemMessage(type + message);
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

				while (playerMap->hasNext(false)) {
					ManagedReference<CreatureObject*> playerObject = playerMap->getNextValue(false);

					if (creature->getPlanetCRC() == playerObject->getPlanetCRC()) {
						if (playerObject->getFaction() == faction.hashCode() || playerObject->getPlayerObject()->hasGodMode())
							playerObject->sendSystemMessage(type + message);
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

				while (playerMap->hasNext(false)) {
					ManagedReference<CreatureObject*> playerObject = playerMap->getNextValue(false);

					if (creature->getPlanetCRC() == playerObject->getPlanetCRC()) {
						if (playerObject->getFaction() == faction.hashCode() || playerObject->getPlayerObject()->hasGodMode())
							playerObject->sendSystemMessage(type + message);
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

		while (playerMap->hasNext(false)) {
			ManagedReference<CreatureObject*> playerObject = playerMap->getNextValue(false);

			if (creature->getPlanetCRC() == playerObject->getPlanetCRC()) {
				playerObject->sendSystemMessage(message);
			}
		}
		return SUCCESS;
	}

};

#endif //BROADCASTPLANETCOMMAND_H_
