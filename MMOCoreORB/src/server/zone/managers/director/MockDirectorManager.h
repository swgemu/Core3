/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef MOCKDIRECTORMANAGER_H_
#define MOCKDIRECTORMANAGER_H_

#include "DirectorManager.h"

namespace server {
namespace zone {
namespace managers {
namespace director {

class MockDirectorManager : public DirectorManager {
public:
	MOCK_METHOD0(getLuaInstance, Lua*());
};

}
}
}
}

using namespace server::zone::managers::director;

#endif /* MOCKDIRECTORMANAGER_H_ */
