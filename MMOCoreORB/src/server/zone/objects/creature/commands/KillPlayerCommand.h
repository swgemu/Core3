/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef KILLPLAYERCOMMAND_H_
#define KILLPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/player/PlayerManager.h"

class KillPlayerCommand : public QueueCommand {
public:

	KillPlayerCommand(const String& name, ZoneProcessServer* server)
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
		if (arguments.isEmpty() && target == 0) {
			creature->sendSystemMessage("Syntax: /killPlayer [player name] [-area [range]] -wounds [<health> [action] [mind]]");
			return GENERALERROR;
		}

		ManagedReference<CreatureObject*> targetPlayer = NULL;
		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();

		if (targetObject != NULL) {
			if (targetObject->isPlayerCreature() || targetObject->isPet())
				targetPlayer = cast<CreatureObject*>(targetObject.get());
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
		bool wounds = false;
		bool damage = false;
		float range = 64;

		while (args.hasMoreTokens()) {

			String arg;
			args.getStringToken(arg);
			bool validOption = false;

			//If first argument is player name, break loop and kill player
			ManagedReference<CreatureObject*>findPlayer = playerManager->getPlayer(arg);
			if (findPlayer != NULL) {
				targetPlayer = findPlayer;
				break;
			}

			//Command Options
			if (arg.charAt(0) == '-') {
				//Help Syntax
				if (arg.toLowerCase() == "-help" || arg == "-H") {
					validOption = true;
					creature->sendSystemMessage("Syntax: /kill [-area [range]] [-wounds] [<health> [action] [mind]]");
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

				//Make command apply wounds as well as damage
				if (arg.toLowerCase() == "-wounds" || arg == "-w") {
					validOption = true;
					wounds = true;
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

					damage = true;
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
				creature->info("Null closeobjects vector in KillPlayerCommand::doQueueCommand", true);
				zone->getInRangeObjects(creature->getPositionX(), creature->getPositionY(), range, &closeObjects, true);
			}
			else {
				CloseObjectsVector* closeVector = (CloseObjectsVector*) creature->getCloseObjects();
				closeVector->safeCopyTo(closeObjects);
			}

			int count = 0;

			//Deal area damage if specified
			if (damage) {
				for (int i = 0; i < closeObjects.size(); i++) {
					SceneObject* targetObject = cast<SceneObject*>(closeObjects.get(i).get());
					if (targetObject->isPlayerCreature() || targetObject->isPet()) {
						targetPlayer = cast<CreatureObject*>(targetObject);

						Locker locker(targetPlayer, creature);
						//Deal damage if target is in range and is a player or pet
						if (creature->isInRange(targetPlayer, range) && (targetPlayer->isPlayerCreature() || targetPlayer->isPet()) && targetPlayer != creature) {
							targetPlayer->inflictDamage(creature, 0, healthDamage, true, true);
							targetPlayer->inflictDamage(creature, 3, actionDamage, true, true);
							targetPlayer->inflictDamage(creature, 6, mindDamage, true, true);

							if( wounds ){
								targetPlayer->addWounds( 0, healthDamage, true );
								targetPlayer->addWounds( 1, healthDamage, true );
								targetPlayer->addWounds( 2, healthDamage, true );
								targetPlayer->addWounds( 3, actionDamage, true );
								targetPlayer->addWounds( 4, actionDamage, true );
								targetPlayer->addWounds( 5, actionDamage, true );
								targetPlayer->addWounds( 6, mindDamage, true );
								targetPlayer->addWounds( 7, mindDamage, true );
								targetPlayer->addWounds( 8, mindDamage, true );
							}

							if (targetPlayer->isPlayerCreature())
								targetPlayer->sendSystemMessage("You have been damaged!");

							++count;
						}
					}
				}
				creature->sendSystemMessage(String::valueOf(count) + " players damaged.");
				return SUCCESS;
			}

			//Kill players in area
			else {
				for (int i = 0; i < closeObjects.size(); i++) {
					SceneObject* targetObject = cast<SceneObject*>(closeObjects.get(i).get());
					if (targetObject->isPlayerCreature() || targetObject->isPet()) {
						targetPlayer = cast<CreatureObject*>(targetObject);

						if (targetPlayer->isPlayerCreature() && targetPlayer != creature) {
							Locker locker (targetPlayer, creature);

							playerManager->killPlayer(creature, targetPlayer, 1);

							++count;
						} else if (targetPlayer->isPet()) {
							AiAgent* pet = cast<AiAgent*>(targetPlayer.get());

							if (pet != NULL) {
								Locker locker(pet, creature);

								PetManager* petManager = server->getZoneServer()->getPetManager();
								petManager->killPet(creature, pet);

								++count;
							}
						}
					}
				}
				creature->sendSystemMessage(String::valueOf(count) + " players and/or pets killed.");
				return SUCCESS;
			}
		}

		//Deal damage to single target
		else if (damage) {
			if (targetPlayer != NULL) {
				if (targetPlayer->isPlayerCreature() || targetPlayer->isPet()) {
					Locker locker(targetPlayer, creature);

					targetPlayer->inflictDamage(creature, 0, healthDamage, true, true);
					targetPlayer->inflictDamage(creature, 3, actionDamage, true, true);
					targetPlayer->inflictDamage(creature, 6, mindDamage, true, true);

					if( wounds ){
						targetPlayer->addWounds( 0, healthDamage, true );
						targetPlayer->addWounds( 1, healthDamage, true );
						targetPlayer->addWounds( 2, healthDamage, true );
						targetPlayer->addWounds( 3, actionDamage, true );
						targetPlayer->addWounds( 4, actionDamage, true );
						targetPlayer->addWounds( 5, actionDamage, true );
						targetPlayer->addWounds( 6, mindDamage, true );
						targetPlayer->addWounds( 7, mindDamage, true );
						targetPlayer->addWounds( 8, mindDamage, true );
					}

					if (targetPlayer->isPlayerCreature())
						creature->sendSystemMessage(targetPlayer->getFirstName() + " damaged.");
					else
						creature->sendSystemMessage(targetPlayer->getDisplayedName() + " damaged.");

					return SUCCESS;
				}
			}
			else {
				creature->sendSystemMessage("Invalid target.");
				return INVALIDTARGET;
			}
		}

		//Kill single target
		else {
			if (targetPlayer != NULL) {
				if (targetPlayer->isPlayerCreature()) {
					Locker locker(targetPlayer, creature);

					playerManager->killPlayer(creature, targetPlayer, 1);
				} else if (targetPlayer->isPet()) {
					Locker locker(targetPlayer, creature);

					targetPlayer->notifyObjectDestructionObservers(creature, 0);
				}
			}
			else {
				creature->sendSystemMessage("Invalid target.");
				return INVALIDTARGET;
			}
		}

		return SUCCESS;
	}

};

#endif //KILLPLAYERCOMMAND_H_
