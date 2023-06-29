/*
 * PlayerManagerCommand.h
 *
 *  Created on: 2/28/2012
 *      Author: Kyle
 */

#ifndef PLAYERMANAGERCOMMAND_H_
#define PLAYERMANAGERCOMMAND_H_

#include "engine/engine.h"
#include "server/zone/ZoneServer.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/player/PlayerManager.h"

#include "server/zone/managers/collision/PathFinderManager.h"

class PlayerManagerCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (!creature->isPlayerCreature())
			return 1;

		ManagedReference<CreatureObject*> player = cast<CreatureObject*>(creature);
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (ghost == nullptr || ghost->getAdminLevel() < 15) {
			return 1;
		}

		ManagedReference<PlayerManager*> playerManager = player->getZoneServer()->getPlayerManager();

		if (playerManager == nullptr) {
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
			bool showAll = false;
			uint64 oid = creature->getObjectID();

			if (tokenizer.hasMoreTokens()) {
				String arg;
				tokenizer.getStringToken(arg);

				if (arg == "all")
					showAll = true;
				else
					oid = Long::valueOf(arg);
			}

			if (tokenizer.hasMoreTokens())
				showAll = true;

			auto resp = dumpCOV(player->getZoneServer(), oid, showAll);
			ChatManager* chatManager = player->getZoneServer()->getChatManager();
			chatManager->sendMail("System", "Dump COV" , resp, player->getFirstName());
			player->sendSystemMessage(resp);
#ifdef NDEBUG
			Logger::console.info(true) << "\033[32;40m" << __FILE__ << ":" << __LINE__ << " dumpcov results:\n" << resp << "\033[0m";
#endif
			return 0;
		} else if (command == "bench") {
			Reference<CreatureObject*> creo = player;
			int iterations = 40;

			if (tokenizer.hasMoreTokens())
				iterations = tokenizer.getIntToken();

			for (int i = 0; i < iterations; i++) {
				Core::getTaskManager()->scheduleTask([creo] {
					Locker locker(creo);

					creo->executeObjectControllerAction(STRING_HASHCODE("createcreature"), 0, "gorax");
					creo->executeObjectControllerAction(STRING_HASHCODE("createcreature"), 0, "nightsister_elder");
					creo->executeObjectControllerAction(STRING_HASHCODE("createcreature"), 0, "death_watch_wraith");
					creo->executeObjectControllerAction(STRING_HASHCODE("createcreature"), 0, "dark_jedi_knight");
				}, "spawnCreatureBenchmark", i * 200);
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
		if (player != nullptr) {
			player->sendSystemMessage("Syntax: /server playermanager [setxpmodifier] [value]");
			player->sendSystemMessage("Syntax: /server playermanager [listjedi]");
			player->sendSystemMessage("Syntax: /server playermanager [list_frsjedi]");
			player->sendSystemMessage("Syntax: /server playermanager [listadmins]");
		}
	}

	static String dumpCOV(ZoneServer* zoneServer, uint64 oid, bool showAll) {
		StringBuffer resp;

		if (zoneServer == nullptr) {
			resp << "oid: " << oid << " zoneServer == nullptr";
			return resp.toString();
		}

		auto targetObject = zoneServer->getObject(oid);

		if (targetObject == nullptr) {
			resp << "oid: " << oid << " getObject() failed.";
			return resp.toString();
		}

		Locker locker(targetObject);

		auto vec = (CloseObjectsVector*)targetObject->getCloseObjects();

		if (vec == nullptr) {
			resp << "oid: " << oid << " does not have a close objects vector.";
			return resp.toString();
		}

		SortedVector<QuadTreeEntry*> closeObjects;
		vec->safeCopyTo(closeObjects);
		vec = nullptr;
		locker.release();

		resp << "Total COV objects: " << closeObjects.size() << " for " << targetObject->getDisplayedName() << " (" << targetObject->getObjectID() << ")";
		resp << endl;
		resp << endl;

		auto ourPosition = targetObject->getWorldPosition();

		VectorMap<float, SceneObject*> sortedObjects;
		sortedObjects.setAllowDuplicateInsertPlan();

		for (int i = 0; i < closeObjects.size(); ++i) {
			auto obj = static_cast<SceneObject*>(closeObjects.getUnsafe(i));
			auto distance = ourPosition.distanceTo(obj->getWorldPosition());
			sortedObjects.put(distance, obj);
		}

		for (int i = 0; i < sortedObjects.size(); ++i) {
			auto obj = sortedObjects.get(i);

			if (obj == nullptr) {
				resp << i << ": " << "nullptr Object" << endl;
				continue;
			}

			if (!showAll && !obj->isPlayerCreature() && !obj->isVehicleObject() && !obj->isMount())
				continue;

			resp << i << ": ";

			auto parent = obj->getParent().get();

			resp << obj->getObjectID() << ": " << obj->getDisplayedName() << " (" << obj->getObjectTemplate()->getTemplateFileName() << ")";

			if (parent == nullptr)
				resp << " Parent: <none>";
			else
				resp << " Parent: " << parent->getObjectID();

			resp << " Receivers: " << CloseObjectsVector::receiverFlagsToString(obj->getReceiverFlags());
			resp << endl;
			resp << "    @ " << obj->getWorldPosition().toString() << " " << ourPosition.distanceTo(obj->getWorldPosition()) << "m";

			float delta = obj->getWorldPosition().distanceTo(obj->getPreviousPosition());

			if (delta != 0.0f)
				resp << " previous: " << obj->getPreviousPosition().toString() << " delta: " << delta;

			resp << endl;
		}

		auto parent = targetObject->getParent().get();

		if (parent != nullptr) {
			resp << endl << ">> Parent " << dumpCOV(zoneServer, parent->getObjectID(), showAll);

			// Compare and report differences with parent
			Locker locker(parent);

			auto vec = (CloseObjectsVector*)parent->getCloseObjects();

			if (vec != nullptr) {
				SortedVector<QuadTreeEntry*> parentCloseObjects;
				vec->safeCopyTo(parentCloseObjects);
				vec = nullptr;
				locker.release();

				VectorMap<uint64, uint8> diff;

				for (int i = 0; i < closeObjects.size(); ++i) {
					auto obj = static_cast<SceneObject*>(closeObjects.getUnsafe(i));

					if (obj == nullptr)
						continue;

					diff.put(obj->getObjectID(), 1);
				}

				for (int i = 0; i < parentCloseObjects.size(); ++i) {
					auto obj = static_cast<SceneObject*>(parentCloseObjects.getUnsafe(i));

					if (obj == nullptr)
						continue;

					uint8 flags = 0;
					int found = diff.find(obj->getObjectID());

					if (found != -1)
						flags = diff.elementAt(found).getValue();

					diff.put(obj->getObjectID(), flags | 2);
				}

				resp << endl << ">> COV Differences found:";

				int count_diff = 0;

				for (int i = 0; i < diff.size(); ++i) {
					auto element = diff.elementAt(i);
					auto oid = element.getKey();
					auto flags = element.getValue();

					// Skip if in both lists
					if (flags == 3)
						continue;

					count_diff++;

					resp << endl << "    ";

					if (flags == 1) {
						resp << "Child Only: ";
					} else if(flags == 2) {
						resp << "Parent Only: ";
					}
					auto obj = zoneServer->getObject(oid);

					if (obj == nullptr) {
						resp << oid << ": getObject() failed";
					} else {
						resp << obj->getObjectID() << ": " << obj->getDisplayedName() << " (" << obj->getObjectTemplate()->getTemplateFileName() << ")";
						resp << " @ " << obj->getWorldPosition().toString() << " " << ourPosition.distanceTo(obj->getWorldPosition()) << "m";
					}
				}

				if (count_diff == 0)
					resp << " NONE";

				resp << endl;
			}
		}

		return resp.toString();
	}
};

#endif /* PLAYERMANAGERCOMMAND_H_ */
