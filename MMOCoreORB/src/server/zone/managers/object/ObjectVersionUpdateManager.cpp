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

int ObjectVersionUpdateManager::updateToVersion2() {
	ObjectDatabase* database = ObjectDatabaseManager::instance()->loadObjectDatabase("sceneobjects", true);

	ObjectDatabaseIterator iterator(database);

	ObjectInputStream objectData(2000);
	uint64 objectID = 0;

	info("starting database update", true);

	String craftingComponents = "object/tangible/crafting/crafting_components_container.iff";
	uint32 hashCode = craftingComponents.hashCode();

	bool newVar = false;
	bool oldVar = false;

	ObjectOutputStream newVarData;
	TypeInfo<bool>::toBinaryStream(&newVar, &newVarData);

	try {

		while (iterator.getNextKeyAndValue(objectID, &objectData)) {
			uint32 serverObjectCRC = 0;

			try {
				if (!Serializable::getVariable<uint32>("SceneObject.serverObjectCRC", &serverObjectCRC, &objectData)) {
					objectData.clear();
					serverObjectCRC = 0;
					continue;
				}
			} catch (...) {
				objectData.clear();
				serverObjectCRC = 0;
				continue;
			}

			if (serverObjectCRC == hashCode) {
				info("adding variable to 0x" + String::hexvalueOf((int64)objectID), true);

				ObjectOutputStream* updatedObjectData = Serializable::addVariable("SceneObject.sendToClient", &objectData, &newVarData);

				/*info("old data", true);
				info(objectData.toStringData(), true);
				info("new data", true);
				info(updatedObjectData->toStringData(), true);

				delete updatedObjectData;*/

				database->putData(objectID, updatedObjectData, NULL);
			}


			objectData.clear();
		}
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	ObjectDatabaseManager::instance()->updateCurrentVersion(2);

	info("finished database update", true);

	return 0;
}

int ObjectVersionUpdateManager::run() {
	int version = ObjectDatabaseManager::instance()->getCurrentVersion();

	if (version <= 1) {
		return updateToVersion2();
	}

	if (version < 1)
		info("updating database to version " + String::valueOf(++version), true);
	else {
		info("database on latest version", true);
		return 1;
	}

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
}
