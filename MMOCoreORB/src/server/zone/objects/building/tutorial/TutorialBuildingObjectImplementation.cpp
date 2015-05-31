/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "server/zone/objects/building/tutorial/TutorialBuildingObject.h"
#include "events/UnloadBuildingTask.h"
#include "server/zone/objects/cell/CellObject.h"

void TutorialBuildingObjectImplementation::enqueueUnloadEvent() {
	unloadTask = new UnloadBuildingTask(_this.getReferenceUnsafeStaticCast());
	unloadTask->schedule(1000);
}

void TutorialBuildingObjectImplementation::notifyRemoveFromZone() {
	/*for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		Vector<ManagedReference<SceneObject*> > terminalsToSave;

		while (cell->getContainerObjectsSize() > 0) {
			ManagedReference<SceneObject*> obj = cell->getContainerObject(0);

			//obj->removeFromZone();
			obj->destroyObjectFromWorld(true);

			//cell->removeObject(obj);

			if (!obj->isPlayerCreature())
				terminalsToSave.add(obj);
		}

		for (int j = 0; j < terminalsToSave.size(); ++j) {
			SceneObject* obj = terminalsToSave.get(j);

			cell->transferObject(obj, -1, false);
		}
	}*/

	TangibleObjectImplementation::notifyRemoveFromZone();
}

