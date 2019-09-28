#include "ScreenPlayTask.h"
#include "server/zone/managers/director/DirectorManager.h"

void ScreenPlayTask::run() {
	ZoneServer* zoneServer = ServerCore::getZoneServer();

	if (zoneServer == nullptr || zoneServer->isServerShuttingDown())
		return;

	if (zoneServer->isServerLoading()) {
		schedule(10000);

		return;
	}

	ManagedReference<SceneObject*> obj = this->obj.get();

	if (obj != nullptr) {
		Locker locker(obj);

		DirectorManager::instance()->activateEvent(this);
	} else {
		DirectorManager::instance()->activateEvent(this);
	}

	setTaskName(String("ScreenPlayTask " + screenPlay + ":" + taskKey + ":" + args).toCharArray());
}
