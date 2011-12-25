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
#include "server/ServerCore.h"

namespace server {
namespace zone {
namespace managers {
namespace stringid {

class StringIdManager : public Logger, public Singleton<StringIdManager>, public Object {
	ObjectDatabaseManager* databaseManager;

	LocalDatabase* stringsDatabase;

protected:
	void populateDatabase();

public:
	StringIdManager();

	~StringIdManager();

	UnicodeString getStringId(uint32 crc);
};

}
}
}
}

using namespace server::zone::managers::stringid;

#endif /* STRINGIDMANAGER_H_ */
