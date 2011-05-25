/*
 * StringIdManager.h
 *
 *  Created on: Sep 21, 2010
 *      Author: dannuic
 */

#ifndef STRINGIDMANAGER_H_
#define STRINGIDMANAGER_H_

#include "engine/engine.h"
#include "server/db/ServerDatabase.h"

namespace server {
namespace zone {
namespace managers {
namespace stringid {

class StringIdManager : public Logger, public Singleton<StringIdManager>, public Object {
	ObjectDatabaseManager* databaseManager;

	LocalDatabase* stringsDatabase;

protected:
	void populateDatabase() {
		Reference<ResultSet*> result = NULL;

		String query = "SELECT stringFile, name, value FROM client_strings;";

		try {
			result = ServerDatabase::instance()->executeQuery(query);

			while (result->next()) {
				String file = result->getString(0);
				String name = result->getString(1);
				String value = result->getString(2);

				file = file.replaceFirst("string/en/","");
				file = file.replaceFirst(".stf","");

				String full = "@" + file + ":" + name;
				ObjectOutputStream* data = new ObjectOutputStream();
				value.toBinaryStream(data);

				uint64 longKey = (uint64)full.hashCode();

				ObjectOutputStream* key = new ObjectOutputStream();
				TypeInfo<uint64>::toBinaryStream(&longKey, key);

				stringsDatabase->putData(key, data);
			}
		} catch (Exception& e) {
			error(e.getMessage());
		}
	}

public:
	StringIdManager() : Logger("StringIdManager") {
		databaseManager = ObjectDatabaseManager::instance();
		bool fill = databaseManager->getDatabaseID("strings") == 0xFFFF;

		stringsDatabase = databaseManager->loadLocalDatabase("strings", true);

		if (fill)
			populateDatabase();

		ObjectDatabaseManager::instance()->commitLocalTransaction();
	}

	~StringIdManager() {}

	String getStringId(uint32 crc) {
		ObjectInputStream data;
		String str = "";

		uint64 longKey = (uint64) crc;
		ObjectOutputStream key;
		TypeInfo<uint64>::toBinaryStream(&longKey, &key);

		if (stringsDatabase->getData(&key, &data) == 0)
			str.parseFromBinaryStream(&data);

		return str;
	}
};

}
}
}
}

using namespace server::zone::managers::stringid;

#endif /* STRINGIDMANAGER_H_ */
