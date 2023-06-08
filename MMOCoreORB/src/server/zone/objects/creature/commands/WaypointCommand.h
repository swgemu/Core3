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
    String groundUsage = "Usage: /waypoint X Y <name> or /waypoint <name> or /waypoint <zone> X Z Y";
	String spaceUsage = "Usage: /waypoint X Z Y <name> or /waypoint <name> or /waypoint <zone> X Z Y";
    mutable bool isSpaceZone;

public:
    WaypointCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {}

    int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
        if (!checkStateMask(creature))
            return INVALIDSTATE;

        if (!checkInvalidLocomotions(creature))
            return INVALIDLOCOMOTION;

        Zone* zone = creature->getZone();

        if (zone == nullptr) {
            zone = creature->getSpaceZone();

            if (zone == nullptr) {
                return GENERALERROR;
            }
        }

        bool advancedWaypoints = ConfigManager::instance()->getBool("Core3.PlayerManager.AdvancedWaypoints", false);

		isSpaceZone = zone->isSpaceZone();
        String waypointData = arguments.toString();

        String waypointName = "@ui:datapad_new_waypoint"; // New Waypoint
        String planet = zone->getZoneName();
        float x = creature->getPositionX();
        float y = creature->getPositionY();
        float z = (isSpaceZone) ? creature->getPositionZ() : 0.0f;

        ManagedReference<SceneObject*> parentObject = creature->getParent().get();

        if (parentObject != nullptr) {
            if (parentObject->isCellObject()) {
                ManagedReference<SceneObject*> grandParentObject = parentObject->getParent().get();

                if (grandParentObject != nullptr) {
                    x = grandParentObject->getPositionX();
                    y = grandParentObject->getPositionY();
                }
            }
        }

        ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target).get();

        StringTokenizer tokenizer(waypointData);
        tokenizer.setDelimeter(" ");

        if (tokenizer.hasMoreTokens()) {
            String arg;
            tokenizer.getStringToken(arg);

            // A waypoint in the form of /waypoint <name>
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
                        if (server->getZoneServer()->getZone(planet) == nullptr) {
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
			z = (zone->isSpaceZone()) ? targetObject->getWorldPositionZ() : z;
			waypointName = targetObject->getDisplayedName();
		}

#ifdef WAYPOINT_DEBUG
		printf("waypoint name: %s\n", waypointName.toCharArray());
        printf("x: %f, z: %f, y: %f\n\n", x, z, y);
#endif

        x = (x < -8192) ? -8192 : x;
        x = (x > 8192) ? 8192 : x;

        y = (y < -8192) ? -8192 : y;
        y = (y > 8192) ? 8192 : y;

        z = (z < -8192) ? -8192 : z;
        z = (z > 8192) ? 8192 : z;

        Reference<PlayerObject*> playerObject = creature->getSlottedObject("ghost").castTo<PlayerObject*>();

        ManagedReference<WaypointObject*> obj = server->getZoneServer()->createObject(0xc456e788, 1).castTo<WaypointObject*>();

        Locker locker(obj);

        obj->setPlanetCRC(planet.hashCode());
        obj->setPosition(x, z, y);
        obj->setCustomObjectName(waypointName, false);
        obj->setActive(true);

		// Should the second argument be true, and waypoints with the same name thus remove their old version?
        playerObject->addWaypoint(obj, false, true);

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
            printf("Arg: %s\n", arg.toCharArray());
        }
        if (requiredArg != nullptr) {
            printf("Passed arg: %s\n", requiredArg->toCharArray());
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
            printf("Returned position: %f\n", *position);
#endif
        } else {
			// Required arg has the possibility of being a planet name
			// so only send system message when it's not null and numerical
			if (requiredArg != nullptr && isalpha(requiredArg->toCharArray()[0]) == 0) {
				sendSystemMessage(creature);
			} else if (requiredArg == nullptr) {
				sendSystemMessage(creature);
			}
        }

        return isValid;
    }

	void sendSystemMessage(CreatureObject* creature) const {
        creature->sendSystemMessage((isSpaceZone) ? spaceUsage : groundUsage);
	}
};

#endif // WAYPOINTCOMMAND_H_
