/*
 * StringIdManager.h
 *
 *  Created on: Sep 21, 2010
 *      Author: dannuic
 */

#ifndef STRINGIDMANAGER_H_
#define STRINGIDMANAGER_H_

#include "engine/log/Logger.h"
#include "engine/util/Singleton.h"
#include "server/zone/objects/scene/variables/StringId.h"
#include "system/lang/Object.h"
#include "system/lang/UnicodeString.h"
#include "system/platform.h"

namespace engine {
namespace db {
class LocalDatabase;
class ObjectDatabaseManager;
}  // namespace db
}  // namespace engine

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

	UnicodeString getStringId(const StringId& id);
};

}
}
}
}

using namespace server::zone::managers::stringid;

#endif /* STRINGIDMANAGER_H_ */
