/*
 * DeleteCharactersTask.h
 *
 *  Created on: Jul 3, 2012
 *      Author: swgemu
 */

#ifndef DELETECHARACTERSTASK_H_
#define DELETECHARACTERSTASK_H_

#include "server/zone/ZoneServer.h"
#include "server/zone/ZoneClientSession.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/transaction/TransactionLog.h"

class DeleteCharactersTask : public Task, public Logger {
	SortedVector<uint64> deletedCharacters;
#ifdef WITH_SWGREALMS_API
	String currentPurgeBatchID;
#endif

public:
	DeleteCharactersTask() : Task(), Logger("DeleteCharactersTask"), deletedCharacters(250, 250) {
		deletedCharacters.setNoDuplicateInsertPlan();

		setCustomTaskQueue("slowQueue");
	}

	void run() {
		ZoneServer* server = ServerCore::getZoneServer();

		if (server == nullptr)
			return;

		info("Running delete characters task.", true);

		int galaxyid = server->getGalaxyID();

#ifndef WITH_SWGREALMS_API
		try {
			Reference<ResultSet*> result = ServerDatabase::instance()->executeQuery("SELECT character_oid FROM deleted_characters WHERE db_deleted = 0 AND galaxy_id = " + String::valueOf(galaxyid) + " LIMIT 250");

			while (result->next()) {
				uint64 oid = result->getUnsignedLong(0);

				deletedCharacters.put(oid);

				ManagedReference<CreatureObject*> obj = server->getObject(oid).castTo<CreatureObject*>();

				if (obj == nullptr || !obj->isPlayerCreature())
					continue;

				Locker _lock(obj.get());

				ManagedReference<ZoneClientSession*> client = obj->getClient();

				if (client != nullptr)
					client->disconnect();

				if (obj->getPersistenceLevel() > 0) {
					TransactionLog trx(TrxCode::CHARACTERDELETE, nullptr, obj);

					// Force a synchronous export because the objects will be deleted before we can export them!
					trx.addRelatedObject(obj);
					trx.setExportRelatedObjects(true);
					trx.exportRelated();
				}

				obj->destroyObjectFromWorld(false); //Don't need to send destroy to the player - they are being disconnected.
				obj->destroyPlayerCreatureFromDatabase(true);
			}
		} catch (Exception& e) {
			error(e.getMessage());
		}
#else // WITH_SWGREALMS_API
		auto swgRealmsAPI = SWGRealmsAPI::instance();
		String errorMessage;
		Vector<uint64> deletedOIDs;

		if (!swgRealmsAPI->beginPurgeBatchBlocking(galaxyid, 250, deletedOIDs, currentPurgeBatchID, errorMessage)) {
			error("Failed to begin purge batch: " + errorMessage);
			return;
		}

		try {
			for (int i = 0; i < deletedOIDs.size(); ++i) {
				uint64 oid = deletedOIDs.get(i);

				deletedCharacters.put(oid);

				ManagedReference<CreatureObject*> obj = server->getObject(oid).castTo<CreatureObject*>();

				if (obj == nullptr || !obj->isPlayerCreature())
					continue;

				Locker _lock(obj.get());

				ManagedReference<ZoneClientSession*> client = obj->getClient();

				if (client != nullptr)
					client->disconnect();

				if (obj->getPersistenceLevel() > 0) {
					TransactionLog trx(TrxCode::CHARACTERDELETE, nullptr, obj);

					// Force a synchronous export because the objects will be deleted before we can export them!
					trx.addRelatedObject(obj);
					trx.setExportRelatedObjects(true);
					trx.exportRelated();
				}

				obj->destroyObjectFromWorld(false); //Don't need to send destroy to the player - they are being disconnected.
				obj->destroyPlayerCreatureFromDatabase(true);
			}
		} catch (Exception& e) {
			error(e.getMessage());
		}
#endif // WITH_SWGREALMS_API
	}

	void updateDeletedCharacters() {
		ZoneServer* server = ServerCore::getZoneServer();

		if (server == nullptr)
			return;

		int galaxyid = server->getGalaxyID();

		int size = deletedCharacters.size();

		if (size <= 0) {
			info("No characters to delete.");
			return;
		}

		info("Attempting to delete " + String::valueOf(size) + " characters from database.", true);

		PlayerManager* playerManager = server->getPlayerManager();

#ifndef WITH_SWGREALMS_API
		StringBuffer query;
		query << "UPDATE deleted_characters SET db_deleted = 1 WHERE galaxy_id = " << galaxyid << " AND (";

		for (int i = 0; i < size; ++i) {
			uint64 oid = deletedCharacters.get(i);

			query << " character_oid = " << oid;

			if (i < size - 1)
				query << " OR";
		}

		query << ")";

		try {
			ServerDatabase::instance()->executeQuery(query.toString());
		} catch (Exception& e) {
			error(e.getMessage());
		}
#else // WITH_SWGREALMS_API
		auto swgRealmsAPI = SWGRealmsAPI::instance();
		String errorMessage;

		if (!swgRealmsAPI->commitPurgeBatchBlocking(galaxyid, currentPurgeBatchID, errorMessage)) {
			error("Failed to commit purge batch: " + errorMessage);
		}

		currentPurgeBatchID = "";
#endif // WITH_SWGREALMS_API

		for (int i = 0; i < size; ++i) {
			uint64 oid = deletedCharacters.get(i);
			playerManager->removePlayer(oid);
		}

		//Clear the vector now that its updated the database.
		deletedCharacters.removeAll(250, 250);
	}
};

#endif /* DELETECHARACTERSTASK_H_ */
