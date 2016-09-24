/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GRANTBADGECOMMAND_H_
#define GRANTBADGECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GrantBadgeCommand : public QueueCommand {
public:

	GrantBadgeCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (arguments.isEmpty() && target == 0) {
			creature->sendSystemMessage("Syntax: /grantBadge [-area [range]] [badge id]");
			return GENERALERROR;
		}

		ManagedReference<SceneObject*> targetObject = server->getZoneServer()->getObject(target);
		StringTokenizer args(arguments.toString());

		bool area = false;
		bool multiple = false;
		float range = 64;
		float badgeId = 0;
		float endBadge = 0;

		if (args.hasMoreTokens()) {

			String arg;
			args.getStringToken(arg);
			bool validOption = false;

			if (arg.charAt(0) == '-') {
				if (arg.toLowerCase() == "-help" || arg.toLowerCase() == "-h") {
					creature->sendSystemMessage("Syntax: /grantBadge [badge id]");
					creature->sendSystemMessage("Syntax: /grantBadge [-area [range]] [badge id]");
					creature->sendSystemMessage("Syntax: /grantBadge [-multiple] [start badge] [end badge]");
					return GENERALERROR;
				} else if (arg.toLowerCase() == "-area" || arg.toLowerCase() == "-a") {
					validOption = true;
					area = true;

					if (!args.hasMoreTokens()) {
						creature->sendSystemMessage("Syntax: /grantBadge [-area [range]] [badge id]");
						return GENERALERROR;
					}

					badgeId = args.getFloatToken();

					if (args.hasMoreTokens()) {
						range = badgeId;
						badgeId = args.getFloatToken();

						if (range <= 0 || range > 192) {
							creature->sendSystemMessage("Invalid range, must be between 1 and 192.");
							return INVALIDPARAMETERS;
						}
					}
				} else if (arg.toLowerCase() == "-multiple" || arg.toLowerCase() == "-m") {
					validOption = true;
					multiple = true;

					if (!args.hasMoreTokens()) {
						creature->sendSystemMessage("Syntax: /grantBadge [-multiple] [start badge] [end badge]");
						return GENERALERROR;
					}

					badgeId = args.getFloatToken();

					if (!args.hasMoreTokens()) {
						creature->sendSystemMessage("Syntax: /grantBadge [-multiple] [start badge] [end badge]");
						return GENERALERROR;
					}

					endBadge = args.getFloatToken();

					if (endBadge <= 0 || endBadge < badgeId) {
						creature->sendSystemMessage("End badge must be greater than 0 and greater than the start badge.");
						return INVALIDPARAMETERS;
					}


				}

				if (!validOption) {
					creature->sendSystemMessage("Invalid option " + arg);
					return INVALIDPARAMETERS;
				}
			} else {
				badgeId = Integer::valueOf(arg);
			}
		}

		if (area) {
			SortedVector<QuadTreeEntry*> closeObjects;
			Zone* zone = creature->getZone();

			if (creature->getCloseObjects() == NULL) {
#ifdef COV_DEBUG
				creature->info("Null closeobjects vector in GrantBadgeCommand::doQueueCommand", true);
#endif
				zone->getInRangeObjects(creature->getPositionX(), creature->getPositionY(), range, &closeObjects, true);
			}
			else {
				CloseObjectsVector* closeVector = (CloseObjectsVector*) creature->getCloseObjects();
				closeVector->safeCopyTo(closeObjects);
			}

			int numGranted = 0;

			for (int i = 0; i < closeObjects.size(); i++) {
				SceneObject* targetObject = cast<SceneObject*>(closeObjects.get(i));
				if (targetObject != NULL && targetObject->isPlayerCreature()) {
					ManagedReference<CreatureObject*> player = cast<CreatureObject*>(targetObject);

					if (player != NULL && player != creature) {
						Locker crossLocker(player, creature);
						server->getPlayerManager()->awardBadge(player->getPlayerObject(), badgeId);
						numGranted++;
					}
				}
			}
			creature->sendSystemMessage("Granted badge " + String::valueOf(badgeId) + " to " + String::valueOf(numGranted) + " players found within " + String::valueOf(range) + "m.");
			return SUCCESS;

		} else {
			if (targetObject == NULL || !targetObject->isPlayerCreature()) {
					creature->sendSystemMessage("Invalid target.");
					return INVALIDTARGET;
			} else {
				ManagedReference<CreatureObject*> player = cast<CreatureObject*>(targetObject.get());

				if (player != NULL) {
					Locker crossLocker(player, creature);

					if (multiple) {
						for (int i = (int)badgeId; i <= endBadge; i++)
							server->getPlayerManager()->awardBadge(player->getPlayerObject(), i);
						creature->sendSystemMessage("Granted badges from " + String::valueOf(badgeId) + " to " + String::valueOf(endBadge) + " to " + player->getDisplayedName() + ".");
					} else {
						server->getPlayerManager()->awardBadge(player->getPlayerObject(), badgeId);
						creature->sendSystemMessage("Granted badge " + String::valueOf(badgeId) + " to " + player->getDisplayedName() + ".");
						return SUCCESS;
					}
				}
			}
		}

		return SUCCESS;
	}

};

#endif //GRANTBADGECOMMAND_H_
