/*
 * PlayerManagerCommand.h
 *
 *  Created on: 2/28/2012
 *      Author: Kyle
 */

#ifndef PLAYERMANAGERCOMMAND_H_
#define PLAYERMANAGERCOMMAND_H_

#include "engine/engine.h"
#include "server/zone/managers/player/PlayerManager.h"

#include "server/zone/managers/collision/PathFinderManager.h"

class PlayerManagerCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (!creature->isPlayerCreature())
			return 1;

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(creature);
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (ghost == NULL || ghost->getAdminLevel() < 15) {
			return 1;
		}

		ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();

		if (playerManager == NULL) {
			creature->sendSystemMessage("playerManager not found");
			return 0;
		}

		//Parse the weather command.
		StringTokenizer tokenizer(arguments.toString());
		if (!tokenizer.hasMoreTokens()) {
			sendSyntax(player);
			return 1;
		}

		String command;
		tokenizer.getStringToken(command);
		command = command.toLowerCase();

		if (command == "path") {
			Vector3 pos = creature->getWorldPosition();
			Sphere sphere(pos, 125);
			Vector3 result;
			PathFinderManager::instance()->getSpawnPointInArea(sphere, creature->getZone(), result);
		} else if (command == "dumpcov") {
			uint64_t oid = creature->getObjectID();
			if (tokenizer.hasMoreTokens())
				oid = tokenizer.getLongToken();

			ManagedReference<SceneObject*> targetObject = player->getZoneServer()->getObject(oid);
			if (targetObject == NULL) {
				player->sendSystemMessage("Unable to look up character");
				return 1;
			}

			Locker locker(targetObject, player);

			CloseObjectsVector* vec = (CloseObjectsVector*)targetObject->getCloseObjects();
			if (vec == NULL) {
				player->sendSystemMessage("Object does not have a close object vector");
				return 1;
			}
			SortedVector<QuadTreeEntry*> closeObjects;
			vec->safeCopyTo(closeObjects);
			locker.release();

			StringBuffer resp;
			for (int i=0; i<vec->size(); i++) {
				ManagedReference<SceneObject *> obj = vec->get(i).castTo<SceneObject *>();
				resp << i << ": ";
				if (obj == NULL) {
					resp << "NULL Object" << endl;
				} else {
					Reference<SceneObject*> parent = obj->getParent().get();
					resp << obj->getObjectID() << ":" << obj->getObjectTemplate()->getTemplateFileName();
					if (parent == NULL)
						resp << " Parent: NULL";
					else
						resp << " Parent: " << parent->getObjectID();
					resp << obj->getWorldPosition().toString() << endl << "Addr: " <<  (uint64)obj.get();
					resp << " PrevX: " << obj->getPreviousPositionX() << " PrevY: " << obj->getPreviousPositionY() << endl;
				}
			}
			ChatManager* chatManager = player->getZoneServer()->getChatManager();
			chatManager->sendMail("System", "Dump COV" , resp.toString(), player->getFirstName());
			player->sendSystemMessage(resp.toString());
			return 0;
		} else if (command == "bench") {
			Reference<CreatureObject*> creo = player;
			int iterations = 100;
			if (tokenizer.hasMoreTokens())
				iterations = tokenizer.getIntToken();

			for (int i=0; i<iterations; i++) {
				Core::getTaskManager()->scheduleTask([creo]{
					Locker locker(creo);
					creo->executeObjectControllerAction(STRING_HASHCODE("createcreature"), 0, "gorax");
					creo->executeObjectControllerAction(STRING_HASHCODE("createcreature"), 0, "nightsister_elder");
					creo->executeObjectControllerAction(STRING_HASHCODE("createcreature"), 0, "death_watch_wraith");

				}, "spawnCreatureBenchmark", i*100);
			}
		} else if (command == "listjedi") {
			player->sendSystemMessage("Please wait. This may take a while.");

			Core::getTaskManager()->executeTask([=] () {
				playerManager->sendAdminJediList(player);
			}, "ListJediLambda");

			return 0;

		} else if (command == "listfrs") {
			player->sendSystemMessage("Please wait. This may take a while.");

			Core::getTaskManager()->executeTask([=] () {
				playerManager->sendAdminFRSList(player);
			}, "ListFrsLambda");

			return 0;

		} else if (command == "listadmins") {
			player->sendSystemMessage("Please wait. This may take a while.");

			Core::getTaskManager()->executeTask([=] () {
				playerManager->sendAdminList(player);
			}, "ListAdminsLambda");

			return 0;

		} else if (command == "setxpmodifier") {
			if (!tokenizer.hasMoreTokens()) {
				sendSyntax(player);
				return 1;
			}

			float multiplier = tokenizer.getFloatToken();

			playerManager->setExperienceMultiplier(multiplier);

			StringBuffer message;
			message << "Experience now increased by " << multiplier << "x";

			player->sendSystemMessage(message.toString());

		} else {
			sendSyntax(player);
			return 1;
		}

		return 0;

	}

	static void sendSyntax(CreatureObject* player) {
		if (player != NULL) {
			player->sendSystemMessage("Syntax: /server playermanager [setxpmodifier] [value]");
			player->sendSystemMessage("Syntax: /server playermanager [listjedi]");
			player->sendSystemMessage("Syntax: /server playermanager [list_frsjedi]");
			player->sendSystemMessage("Syntax: /server playermanager [listadmins]");
		}
	}
};

#endif /* PLAYERMANAGERCOMMAND_H_ */
