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
	/*ObjectDatabase* staticDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("playerstructures", true);

	ObjectDatabaseIterator iterator(staticDatabase);

	uint32 serverObjectCRC;
	uint64 objectID;

	ObjectInputStream objectData(2000);

	try {

		while (iterator.getNextKeyAndValue(objectID, &objectData)) {
			uint32 gameObjectType = 0;

			if (!Serializable::getVariable<uint32>("gameObjectType", &gameObjectType, &objectData)) {
				objectData.reset();
				continue;
			}

			if (gameObjectType == 4104) {
				info("bank found", true);

				ObjectManager::instance()->commitDestroyObjectToDB(objectID);
			}

			objectData.reset();
		}
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}*/
}
