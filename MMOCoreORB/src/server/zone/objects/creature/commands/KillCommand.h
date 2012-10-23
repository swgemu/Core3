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

#ifndef KILLCOMMAND_H_
#define KILLCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/creature/CreatureManager.h"

class KillCommand : public QueueCommand {
public:

	KillCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		//Check privileges
		if (ghost == NULL || !ghost->isPrivileged())
			return INSUFFICIENTPERMISSION;

		//Explain syntax
		if (arguments.isEmpty() && creature->getTargetID() == 0) {
			creature->sendSystemMessage("Syntax: /kill [-area [range]] [<health> [action] [mind]]");
			return GENERALERROR;
		}

		ManagedReference<CreatureObject*> targetCreature = NULL;
		ManagedReference<TangibleObject*> targetLair = NULL;
		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		if (targetObject != NULL) {
			if (targetObject->isCreatureObject())
				targetCreature = cast<CreatureObject*>(targetObject.get());
			else if (targetObject->isTangibleObject())
				targetLair = cast<TangibleObject*>(targetObject.get());
			else {
				creature->sendSystemMessage("Invalid target.");
				return INVALIDTARGET;
			}
		}

		StringTokenizer args(arguments.toString());

		//Initialize default damage amount
		int healthDamage = 9999999;
		int actionDamage = healthDamage;
		int mindDamage = healthDamage;

		//Initialize components used to kill nearby creatures
		bool area = false;
		float range = 64;

		while (args.hasMoreTokens()) {

			String arg;
			args.getStringToken(arg);
			bool validOption = false;

			//Command Options
			if (arg.charAt(0) == '-') {
				//Help Syntax
				if (arg.toLowerCase() == "-help" || arg == "-H") {
					validOption = true;
					creature->sendSystemMessage("Syntax: /kill [-area [range]] [<health> [action] [mind]]");
					return GENERALERROR;
				}

				//Make command area affect with optional range
				if (arg.toLowerCase() == "-area" || arg == "-a") {
					validOption = true;
					area = true;

					if (args.hasMoreTokens()) {
						range = args.getFloatToken();
						if (range <= 0) {
							creature->sendSystemMessage("Invalid range.");
							return INVALIDPARAMETERS;
						}
					}
				}

				if (!validOption) {
					creature->sendSystemMessage("Invalid option " + arg);
					return INVALIDPARAMETERS;
				}
			}

			else {
				//Override default damage amount
				try {
					//Test if value is integer
					for (int i = 0; i < arg.length(); i++) {
						if (!Character::isDigit(arg.charAt(i)))
							throw Exception("Invalid damage amount.");
					}

					healthDamage = Integer::valueOf(arg);
					actionDamage = healthDamage;
					mindDamage = healthDamage;

					if (args.hasMoreTokens()) {
						args.getStringToken(arg);
						//Test if value is integer
						for (int i = 0; i < arg.length(); i++) {
							if (!Character::isDigit(arg.charAt(i)))
								throw Exception("Invalid action damage amount.");
						}

						actionDamage = Integer::valueOf(arg);
						mindDamage = 0;

						if (args.hasMoreTokens()) {
							args.getStringToken(arg);
							//Test if value is integer
							for (int i = 0; i < arg.length(); i++) {
								if (!Character::isDigit(arg.charAt(i)))
									throw Exception("Invalid mind damage amount.");
							}

							mindDamage = Integer::valueOf(arg);

							if (args.hasMoreTokens())
								throw Exception("Too many arguments.");
						}
					}
				}
				catch (Exception e) {
					creature->sendSystemMessage(e.getMessage());
					return INVALIDPARAMETERS;
				}
			}
		}

		//Deal area damage if specified
		if (area) {
			//Retrieve nearby objects
			SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;
			Zone* zone = creature->getZone();

			if (creature->getCloseObjects() == NULL) {
				zone->getInRangeObjects(creature->getPositionX(), creature->getPositionY(), range, &closeObjects, true);
			}
			else {
				CloseObjectsVector* closeVector = (CloseObjectsVector*) creature->getCloseObjects();
				closeVector->safeCopyTo(closeObjects);
			}

			for (int i = 0; i < closeObjects.size(); i++) {
				SceneObject* targetObject = cast<SceneObject*>(closeObjects.get(i).get());
				if (targetObject->isCreatureObject()) {
					targetCreature = cast<CreatureObject*>(targetObject);

					Locker locker(targetCreature, creature);
					//Deal damage if target is an attackable creature, in range, and not a player
					if (targetCreature->isAttackableBy(creature) && creature->isInRange(targetObject, range) && !targetObject->isPlayerCreature()) {
						targetCreature->inflictDamage(creature, 0, healthDamage, true, true);
						targetCreature->inflictDamage(creature, 3, actionDamage, true, true);
						targetCreature->inflictDamage(creature, 6, mindDamage, true, true);
					}
				}
			}
			return SUCCESS;
		}

		//Deal damage to selected target
		else {
			//Deal damage if target is not a player
			if (targetCreature != NULL) {
				if (!targetCreature->isPlayerCreature()) {
					Locker locker(targetCreature, creature);

					targetCreature->inflictDamage(creature, 0, healthDamage, true, true);
					targetCreature->inflictDamage(creature, 3, actionDamage, true, true);
					targetCreature->inflictDamage(creature, 6, mindDamage, true, true);
					return SUCCESS;
				}
			}
			//Deal damage if target is a lair
			else if (targetLair != NULL) {
				Locker locker(targetLair, creature);

				targetLair->inflictDamage(creature, 0, healthDamage, true, true);
				return SUCCESS;
			}
		}

		return SUCCESS;
	}

};

#endif //KILLCOMMAND_H_
