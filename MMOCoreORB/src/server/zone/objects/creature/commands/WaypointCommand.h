/*
	Copyright <SWGEmu>
	See file COPYING for copying conditions.
*/

#ifndef WAYPOINTCOMMAND_H_
#define WAYPOINTCOMMAND_H_

// #define WAYPOINT_DEBUG

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/Zone.h"

class WaypointCommand : public QueueCommand {
private:
	bool advancedWaypoints = ConfigManager::instance()->getBool("Core3.PlayerManager.AdvancedWaypoints", false);
	String advancedGroundUsage = "Usage: /waypoint X Y <name> or /waypoint <name> or /waypoint <zone> X Z Y";
	String advancedSpaceUsage = "Usage: /waypoint X Z Y <name> or /waypoint <name> or /waypoint <zone> X Z Y";
	String groundUsage = "Usage: /waypoint X Y";
	String spaceUsage = "Usage: /waypoint X Z Y";
	mutable bool isSpaceZone;

public:
	WaypointCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature)) {
			return INVALIDSTATE;
		}

		if (!checkInvalidLocomotions(creature)) {
			return INVALIDLOCOMOTION;
		}

		Zone* zone = creature->getZone();

		if (zone == nullptr) {
			return GENERALERROR;
		}

		auto ghost = creature->getPlayerObject();

		if (ghost == nullptr) {
			return GENERALERROR;
		}

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr) {
			return GENERALERROR;
		}

		isSpaceZone = zone->isSpaceZone();

		String waypointData = arguments.toString();
		String waypointName = "@ui:datapad_new_waypoint"; // New Waypoint
		String planet = zone->getZoneName();

		float x = creature->getPositionX();
		float y = creature->getPositionY();
		float z = (isSpaceZone) ? creature->getPositionZ() : 0.0f;

		ManagedReference<SceneObject*> rootParent = creature->getRootParent();

		if (rootParent != nullptr) {
			x = rootParent ->getPositionX();
			y = rootParent ->getPositionY();

			if (isSpaceZone) {
				z = rootParent->getPositionZ();
			}
		}

		ManagedReference<SceneObject*> targetObject = zoneServer->getObject(target).get();

		StringTokenizer tokenizer(waypointData);
		tokenizer.setDelimeter(" ");

		if (tokenizer.hasMoreTokens()) {
			String arg;
			tokenizer.getStringToken(arg);

			// First argument was alpha (zone name)
			// This is invalid if advanced waypoints are disabled
			if (!advancedWaypoints && isalpha(arg[0]) > 0) {
				sendSystemMessage(creature);
				return GENERALERROR;
			}

			if (tokenizer.hasMoreTokens()) {
				// The first argument is passed here as a required argument as it can be a planet name or position
				// If the argument is not a valid position value, this condition is false
				if (getValidPosition(creature, &tokenizer, &x, &arg)) {
					// Space zones:
					// /waypoint X Z Y
					if (isSpaceZone) {
						if (!checkHasMoreTokens(creature, &tokenizer, &z)) {
							return GENERALERROR;
						}
						if (!checkHasMoreTokens(creature, &tokenizer, &y)) {
							return GENERALERROR;
						}
					// Ground zones:
					// /waypoint X Y
					} else {
						if (!checkHasMoreTokens(creature, &tokenizer, &y)) {
							return GENERALERROR;
						}
					}

					// Allows the last argument to name the waypoint
					if (advancedWaypoints) {
						StringBuffer newWaypointName;

						while (tokenizer.hasMoreTokens()) {
							String name;
							tokenizer.getStringToken(name);
							newWaypointName << name << " ";
						}

						if (newWaypointName.length() > 0) {
							waypointName = newWaypointName.toString();
						}
					}
				} else {
					// A waypoint in the form of /waypoint planet X Z Y - Planetary Map
					if (advancedWaypoints) {
						planet = arg;

						// Not a valid planet name - malformed command
						if (zoneServer->getZone(planet) == nullptr) {
							sendSystemMessage(creature);
							return GENERALERROR;
						}

						if (!checkHasMoreTokens(creature, &tokenizer, &x)) {
							return GENERALERROR;
						}
						if (!checkHasMoreTokens(creature, &tokenizer, &z)) {
							return GENERALERROR;
						}
						if (!checkHasMoreTokens(creature, &tokenizer, &y)) {
							return GENERALERROR;
						}
					}
				}
			} else {
				// Allows for naming the waypoint if the first argument starts with
				// an alpha character and has no additional position arguments
				if (advancedWaypoints) {
					waypointName = arg;
				}
			}
		} else if (targetObject != nullptr) {
			Locker crosslocker(targetObject, creature);

			x = targetObject->getWorldPositionX();
			y = targetObject->getWorldPositionY();
			z = isSpaceZone ? targetObject->getWorldPositionZ() : z;
			waypointName = targetObject->getDisplayedName();
		}

#ifdef WAYPOINT_DEBUG
		info(true) << "waypoint name: " << waypointName.toCharArray();
		info(true) << "X: " << x << ", Z: " << z << ", Y: " << y;
#endif

		x = (x < -8192) ? -8192 : x;
		x = (x > 8192) ? 8192 : x;

		y = (y < -8192) ? -8192 : y;
		y = (y > 8192) ? 8192 : y;

		z = (z < -8192) ? -8192 : z;
		z = (z > 8192) ? 8192 : z;

		ManagedReference<WaypointObject*> waypoint = zoneServer->createObject(0xc456e788, 1).castTo<WaypointObject*>();

		if (waypoint == nullptr) {
			return GENERALERROR;
		}

		Locker locker(waypoint, creature);

		waypoint->setPlanetCRC(planet.hashCode());
		waypoint->setPosition(x, z, y);
		waypoint->setCustomObjectName(waypointName, false);

		if (isSpaceZone) {
			waypoint->setColor(WaypointObject::COLOR_SPACE);
		}

		waypoint->setActive(true);

		// Should the second argument be true, and waypoints with the same name thus remove their old version?
		ghost->addWaypoint(waypoint, false, true);

		return SUCCESS;
	}

	bool checkHasMoreTokens(CreatureObject* creature, StringTokenizer* tokenizer, float* position) const {
		if (tokenizer->hasMoreTokens()) {
			if (!getValidPosition(creature, tokenizer, position)) {
				return false;
			}
		} else {
			sendSystemMessage(creature);
			return false;
		}

		return true;
	}

	bool getValidPosition(CreatureObject* creature, StringTokenizer* tokenizer, float* position, String* requiredArg = nullptr) const {
		String arg;

		if (requiredArg == nullptr) {
			tokenizer->getStringToken(arg);
		}

#ifdef WAYPOINT_DEBUG
		if (!arg.isEmpty()) {
			info(true) << "Arg: " << arg.toCharArray();
		}
		if (requiredArg != nullptr) {
			info(true) << "Passed arg: " << requiredArg->toCharArray();
		}
#endif

		bool isValid = false;
	
		if (requiredArg != nullptr) {
			if (isalpha(requiredArg->toCharArray()[0]) == 0) {
				*position = atof(requiredArg->toCharArray());
				isValid = true;
			}
		} else {
			if (isalpha(arg[0]) == 0) {
				*position = atof(arg.toCharArray());
				isValid = true;
			}
		}

		if (isValid) {
#ifdef WAYPOINT_DEBUG
			info(true) << "Returned position: " << *position;
#endif
		} else {
			if (advancedWaypoints) {
				// Only necessary if requiredArg is null since it is allowed to be alpha
				if (requiredArg == nullptr) {
					sendSystemMessage(creature);
				}
			} else {
				sendSystemMessage(creature);
			}
		}

		return isValid;
	}

	void sendSystemMessage(CreatureObject* creature) const {
		if (advancedWaypoints) {
			creature->sendSystemMessage((isSpaceZone) ? advancedSpaceUsage : advancedGroundUsage);
		} else {
			creature->sendSystemMessage((isSpaceZone) ? spaceUsage : groundUsage);
		}
	}
};

#endif // WAYPOINTCOMMAND_H_
