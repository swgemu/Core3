/*
 * DeleteCharactersTask.h
 *
 *  Created on: Jul 3, 2012
 *      Author: swgemu
 */

#ifndef DELETECHARACTERSTASK_H_
#define DELETECHARACTERSTASK_H_

#include "engine/engine.h"

#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneClientSession.h"
#include "server/zone/managers/statistics/StatisticsManager.h"
class DeleteCharactersTask : public Task, public Logger {
	SortedVector<uint64> deletedCharacters;

public:
	DeleteCharactersTask() : Task(), Logger("DeleteCharactersTask"), deletedCharacters(250, 250) {
		deletedCharacters.setNoDuplicateInsertPlan();
	}

	void run() {
		ZoneServer* server = ServerCore::getZoneServer();

		if (server == NULL) {
			StatisticsManager::instance()->IncrementCharacterStat(StatisticsManager::TASKERRORS);
			return;
		}

		info("Running delete characters task. ", true);

		int galaxyid = server->getGalaxyID();

		try {

			StatisticsManager::instance()->IncrementCharacterStat(StatisticsManager::TASKRUN);

			Reference<ResultSet*> result = ServerDatabase::instance()->executeQuery("SELECT character_oid FROM deleted_characters WHERE db_deleted = 0 AND galaxy_id = " + String::valueOf(galaxyid) + " LIMIT 250");

			while (result->next()) {
				uint64 oid = result->getUnsignedLong(0);

				deletedCharacters.put(oid);

				ManagedReference<SceneObject*> obj = server->getObject(oid);

				if (obj == NULL || !obj->isPlayerCreature()) {
					info("ERROR: error deleting character it's null or not a player" + String::valueOf(oid),true);
					StatisticsManager::instance()->IncrementCharacterStat(StatisticsManager::TASKERRORS);
					continue;
				}

				Locker _lock(obj.get());

				ManagedReference<ZoneClientSession*> client = obj->getClient();

				if (client != NULL)
					client->disconnect();

				obj->destroyObjectFromWorld(false); //Don't need to send destroy to the player - they are being disconnected.
				StatisticsManager::instance()->IncrementCharacterStat(StatisticsManager::CHARACTERDESTROYEDFROMWORLD);

				obj->destroyPlayerCreatureFromDatabase(true);
				StatisticsManager::instance()->IncrementCharacterStat(StatisticsManager::CHARACTERDESTROYEDFROMDATABASE);
			}
		} catch (Exception& e) {
			error(e.getMessage());
			StatisticsManager::instance()->IncrementCharacterStat(StatisticsManager::TASKEXCEPTIONS);
		}
	}

	void updateDeletedCharacters() {
		StatisticsManager::instance()->IncrementCharacterStat(StatisticsManager::CHARACTUREUPDATES);
		StringBuffer query;

		query << "UPDATE deleted_characters SET db_deleted = 1 WHERE";

		int size = deletedCharacters.size();

		if (size <= 0) {
			return;
		}

		for (int i = 0; i < size; ++i) {

			uint64 oid = deletedCharacters.get(i);

			query << " character_oid = " << oid;

			if (i < size - 1)
				query << " OR";
		}

		try {

			ServerDatabase::instance()->executeQuery(query.toString());

		} catch (Exception& e) {
			error(e.getMessage());
		}

		//Clear the vector now that its updated the database.
		deletedCharacters.removeAll(250, 250);
	}
};

#endif /* DELETECHARACTERSTASK_H_ */
