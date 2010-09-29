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

class StringIdManager : public Logger, public Singleton<StringIdManager> {
	ObjectDatabaseManager* databaseManager;

	ObjectDatabase* stringsDatabase;

protected:
	void populateDatabase() {
		ResultSet* result = NULL;
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
				ObjectOutputStream data;
				value.toBinaryStream(&data);

				stringsDatabase->putData((uint64)full.hashCode(), &data, NULL);
			}

			delete result;
		} catch (Exception& e) {
			error(e.getMessage());
		} catch (...) {
			error("unreported exception caught in StringIdManager::populateDatabase()");
		}

	}

public:
	StringIdManager() : Logger("StringIdManager") {
		databaseManager = ObjectDatabaseManager::instance();
		bool fill = databaseManager->getDatabaseID("strings") == 0xFFFF;

		stringsDatabase = databaseManager->loadDatabase("strings", true);

		if (fill)
			populateDatabase();

		ObjectDatabaseManager::instance()->commitLocalTransaction();
	}

	~StringIdManager() {}

	String getStringId(uint32 crc) {
		ObjectInputStream data;
		String str = "";
		if (stringsDatabase->getData(crc, &data) == 0)
			str.parseFromBinaryStream(&data);

		return str;
	}
};

}
}
}
}

#endif /* STRINGIDMANAGER_H_ */
