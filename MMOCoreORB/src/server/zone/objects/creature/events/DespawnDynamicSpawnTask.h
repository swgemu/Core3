
#ifndef DESPAWNDYNAMICSPAWNTASK_H_
#define DESPAWNDYNAMICSPAWNTASK_H_

#include "server/zone/objects/scene/SceneObject.h"

class DespawnDynamicSpawnTask : public Task {
	ManagedReference<SceneObject*> spawn;

public:
	DespawnDynamicSpawnTask(SceneObject* sceno) {
		spawn = sceno;
	}

	void run() {
		Locker locker(spawn);

		Zone* zone = spawn->getZone();

		if (zone == NULL)
			return;

		spawn->destroyObjectFromWorld(true);

	}
};


#endif /* DESPAWNDYNAMICSPAWNTASK_H_ */
