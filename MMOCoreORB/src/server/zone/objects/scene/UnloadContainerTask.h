
#ifndef UNLOADCONTAINERTASK_H_
#define UNLOADCONTAINERTASK_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/cell/CellObject.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace scene {

class UnloadContainerTask : public Task {
	ManagedWeakReference<SceneObject*> container;

	public:
		UnloadContainerTask(SceneObject* obj) {
			container = obj;
		}

		void run() {
			ManagedReference<SceneObject*> obj = container;

			if (obj == NULL)
				return;

			if (obj->getLastContainerAccess() < 900000) { // if accessed within the last 15 minutes, reschedule
				reschedule(1800000); // 30 minutes
				return;
			}

			if (obj->isCellObject()) {
				CellObject* cell = obj.castTo<CellObject*>();

				if (cell->hasForceLoadObject()) {
					reschedule(1800000); // 30 minutes
					return;
				}
			}

			obj->unloadContainerObjects();
		}
	};

   }
  }
 }
}

#endif /* UNLOADCONTAINERTASK_H_ */
