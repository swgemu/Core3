/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef WAYPOINTCOMMAND_H_
#define WAYPOINTCOMMAND_H_


#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/Zone.h"


#include "server/zone/managers/object/ObjectManager.h"

class WaypointCommand : public QueueCommand {
public:

	WaypointCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		Zone* zone = creature->getZone();

		if (zone == NULL)
			return GENERALERROR;

		int counter = 0;
		String dummy;

		String usageError = "Usage: /waypoint X Y <name> or /waypoint <name>";

		String waypointData = arguments.toString();

		String waypointName = "New Waypoint";
		String planet = zone->getZoneName();
		float x = creature->getPositionX();
		float y = creature->getPositionY();
		float z = 0.0f;

		ManagedReference<SceneObject*> parentObject = creature->getParent();

		if (parentObject != NULL) {
			if (parentObject->isCellObject()) {
				ManagedReference<SceneObject*> grandParentObject = parentObject->getParent();

				if (grandParentObject != NULL) {
					x = grandParentObject->getPositionX();
					y = grandParentObject->getPositionY();
				}
			}
		}

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target).get();

		if (targetObject != NULL) {
			Locker crosslocker(targetObject, creature);

			x = targetObject->getWorldPositionX();
			y = targetObject->getWorldPositionY();
			waypointName = targetObject->getDisplayedName();
		}

		StringTokenizer tokenizer(waypointData);
		tokenizer.setDelimeter(" ");

		if (tokenizer.hasMoreTokens()) {

			String arg1;
			tokenizer.getStringToken(arg1);

			if (tokenizer.hasMoreTokens()) {
				if (isalpha(arg1[0]) == 0) {
					//A waypoint in the form of /waypoint X Y <name>
					x = atof(arg1.toCharArray());

					if (tokenizer.hasMoreTokens()) {
						String temp;
						tokenizer.getStringToken(temp);
						if (isalpha(temp[0]) == 0) {
							y = atof(temp.toCharArray());
						} else {
							creature->sendSystemMessage(usageError);
							return GENERALERROR;
						}
					}

					StringBuffer newWaypointName;

					while (tokenizer.hasMoreTokens()) {
						String name;
						tokenizer.getStringToken(name);
						newWaypointName << name << " ";
					}

					/*if (!newWaypointName.isEmpty())
							 newWaypointName.deleteRange(0, 1);*/// ????

					waypointName = newWaypointName.toString();
				} else {
					//A waypoint in the form of /waypoint planet X Z Y - Planetary Map
					planet = arg1;

					if (server->getZoneServer()->getZone(planet) == NULL) { //Not a valid planet name - malformed command
						creature->sendSystemMessage(usageError);
						return GENERALERROR;
					}

					if (tokenizer.hasMoreTokens()) {
						String temp;
						tokenizer.getStringToken(temp);

						if (!Character::isLetterOrDigit(temp.charAt(0))) {
							x = Float::valueOf(temp);
						} else {
							creature->sendSystemMessage(usageError);
							return GENERALERROR;
						}
					}

					if (tokenizer.hasMoreTokens()) {
						String temp;
						tokenizer.getStringToken(temp);

						if (!Character::isLetterOrDigit(temp.charAt(0))) {
							z = Float::valueOf(temp);
						} else {
							creature->sendSystemMessage(usageError);
							return GENERALERROR;
						}
					}

					if (tokenizer.hasMoreTokens()) {
						String temp;
						tokenizer.getStringToken(temp);

						if (!Character::isLetterOrDigit(temp.charAt(0))) {
							y = Float::valueOf(temp);
						} else {
							creature->sendSystemMessage(usageError);
							return GENERALERROR;
						}
					}
				}
			} else {
				//A waypoint in the form of /waypoint <name>
				waypointName = arg1;
			}
		}

		x = (x < -8192) ? -8192 : x;
		x = (x > 8192) ? 8192 : x;

		y = (y < -8192) ? -8192 : y;
		y = (y > 8192) ? 8192 : y;

		Reference<PlayerObject*> playerObject =  creature->getSlottedObject("ghost").castTo<PlayerObject*>();

		ManagedReference<WaypointObject*> obj = server->getZoneServer()->createObject(0xc456e788, 1).castTo<WaypointObject*>();
		obj->setPlanetCRC(planet.hashCode());
		obj->setPosition(x, z, y);
		obj->setCustomObjectName(waypointName, false);
		obj->setActive(true);

		playerObject->addWaypoint(obj, false, true); // Should second argument be true, and waypoints with the same name thus remove their old version?

		return SUCCESS;
	}

};

#endif //WAYPOINTCOMMAND_H_


