/*
 * ObjectVersionUpdateManager.cpp
 *
 *  Created on: Oct 28, 2010
 *      Author: oru
 */

#include "ObjectVersionUpdateManager.h"
#include "ObjectManager.h"

ObjectVersionUpdateManager::ObjectVersionUpdateManager() : Logger("ObjectVersionUpdateManager") {
	luaInstance = new Lua();
	luaInstance->init();
}

void ObjectVersionUpdateManager::run() {
	/*ObjectDatabase* staticDatabase = ObjectDatabaseManager::instance()->loadDatabase("guilds", true);

	ObjectDatabaseIterator iterator(staticDatabase);

	uint32 serverObjectCRC;
	uint64 objectID;

	ObjectInputStream objectData(2000);

	while (iterator.getNextKeyAndValue(objectID, &objectData)) {
		String guildAbbrev;

		if (!Serializable::getVariable<String>("guildAbbrev", &guildAbbrev, &objectData)) {
			objectData.reset();
			continue;
		}

		if (guildAbbrev == "cRus4") {
			info("guild found");

			ObjectManager::instance()->commitDestroyObjectToDB(objectID);
		}

		objectData.reset();
	}

	ObjectDatabaseManager::instance()->commitLocalTransaction();*/
}
