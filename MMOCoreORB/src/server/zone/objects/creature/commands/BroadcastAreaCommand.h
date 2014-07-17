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

#ifndef BROADCASTAREACOMMAND_H_
#define BROADCASTAREACOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"

class BroadcastAreaCommand : public QueueCommand {
public:

	BroadcastAreaCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

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
