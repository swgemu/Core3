
#ifndef REMOVEEVENTPERKITEMTASK_H_
#define REMOVEEVENTPERKITEMTASK_H_

#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/tangible/eventperk/Jukebox.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace tasks {

class RemoveEventPerkItemTask : public Task {
	ManagedWeakReference<TangibleObject*> tano;

public:
	RemoveEventPerkItemTask(TangibleObject* obj) {
		 tano = obj;
	}

	void run() {
		Reference<TangibleObject*> tano = this->tano.get();

		if (tano == NULL) {
			return;
		}

		Locker locker(tano);

		if (tano->getServerObjectCRC() == 0x46BD798B) { // Jukebox
			Jukebox* jbox = tano.castTo<Jukebox*>();

			if (jbox != NULL)
				jbox->stopPlaying();
		}

		tano->destroyObjectFromWorld(true);
		tano->destroyObjectFromDatabase();
	}
};

}
}
}
}
}

using namespace server::zone::objects::tangible::tasks;

#endif /* REMOVEEVENTPERKITEMTASK_H_ */
