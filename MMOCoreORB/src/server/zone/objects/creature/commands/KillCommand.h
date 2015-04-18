/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef KILLCOMMAND_H_
#define KILLCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/creature/CreatureManager.h"

class KillCommand : public QueueCommand {
public:

	KillCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

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
				creature->info("Null closeobjects vector in KillCommand::doQueueCommand", true);
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
					//Deal damage if target is an attackable creature, in range, and not a player or pet
					if (targetCreature->isAttackableBy(creature) && creature->isInRange(targetObject, range) && !targetObject->isPlayerCreature() && !targetObject->isPet()) {
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
			//Deal damage if target is not a player or pet
			if (targetCreature != NULL) {
				if (!targetCreature->isPlayerCreature() && !targetObject->isPet()) {
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
