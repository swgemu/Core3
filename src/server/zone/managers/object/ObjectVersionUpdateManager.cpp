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

void ObjectVersionUpdateManager::run() {
	/*ObjectDatabase* staticDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("sceneobjects", true);

	ObjectDatabaseIterator iterator(staticDatabase);

	uint32 serverObjectCRC;
	uint64 objectID;

	ObjectInputStream objectData(2000);

	info("starting database update", true);



	try {

		while (iterator.getNextKeyAndValue(objectID, &objectData)) {
			uint32 gameObjectType = 0;

			try {

				if (!Serializable::getVariable<uint32>("gameObjectType", &gameObjectType, &objectData)) {
					objectData.reset();
					continue;
				}
			} catch (...) {
				objectData.reset();
				continue;
			}

			//info("updating object", true);

			if (gameObjectType == SceneObject::PLAYERCREATURE) {
				uint32 accountID;
				Serializable::getVariable<uint32>("accountID", &accountID, &objectData);

				StringId stringId;
				Serializable::getVariable<StringId>("objectName", &stringId, &objectData);

				UnicodeString fullName = stringId.getCustomString();
				UnicodeTokenizer token(fullName);
				String firstName;
				token.getStringToken(firstName);

				String lastName;
				if (token.hasMoreTokens())
					token.getStringToken(lastName);

				byte raceId;
				Serializable::getVariable<byte>("raceId", &raceId, &objectData);

				String race = CCRaceStrs[raceId];

				try {
					StringBuffer query;
					query << "INSERT INTO `characters` (`character_oid`, `account_id`, `galaxy_id`, `firstname`, `surname`, `race`, `gender`, `template`)"
							<< " VALUES (" <<  objectID << "," << accountID <<  "," << 2 << ","
							<< "'" << firstName.escapeString() << "','" << lastName.escapeString() << "'," << raceId << "," <<  0 << ",'" << race.escapeString() << "')";

					ServerDatabase::instance()->executeStatement(query);
				} catch (Exception& e) {
					error(e.getMessage());
				} catch (...) {
					error("unreported exception caught while creating character");
				}
			}

			objectData.reset();
		}
	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
	}

	info("finished update", true);

	//ObjectDatabaseManager::instance()->commitLocalTransaction();*/
}
