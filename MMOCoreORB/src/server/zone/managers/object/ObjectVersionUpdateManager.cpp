/*
 * ObjectVersionUpdateManager.cpp
 *
 *  Created on: Oct 28, 2010
 *      Author: oru
 */

#include "ObjectVersionUpdateManager.h"
#include "ObjectManager.h"
#include "server/zone/objects/player/Races.h"
#include "server/db/ServerDatabase.h"

ObjectVersionUpdateManager::ObjectVersionUpdateManager() : Logger("ObjectVersionUpdateManager") {
	luaInstance = new Lua();
	luaInstance->init();
}


int ObjectVersionUpdateManager::run() {
	int version = ObjectDatabaseManager::instance()->getCurrentVersion();

	info("database on latest version", true);
	return 1;
/*

	ObjectDatabase* database = ObjectDatabaseManager::instance()->loadObjectDatabase("sceneobjects", true);

	ObjectDatabaseIterator iterator(database);

	ObjectInputStream objectData(2000);
	uint64 objectID = 0;

	info("starting database update", true);

	try {

		while (iterator.getNextKeyAndValue(objectID, &objectData)) {
			bool municipalZone = false;

			try {
				if (!Serializable::getVariable<bool>("ActiveArea.municipalZone", &municipalZone, &objectData)) {
					objectData.clear();
					continue;
				}
			} catch (...) {
				objectData.clear();
				continue;
			}

			//info("updating object", true);

			if (municipalZone) {
				database->deleteData(objectID);

				info("deleting municipal zone 0x" + String::hexvalueOf((int64)objectID), true);
			}

			objectData.clear();
		}
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	ObjectDatabaseManager::instance()->updateCurrentVersion(version);

	info("finished database update", true);

	return 0;
	*/
}
