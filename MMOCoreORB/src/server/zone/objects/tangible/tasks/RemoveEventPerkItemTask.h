
#ifndef REMOVEEVENTPERKITEMTASK_H_
#define REMOVEEVENTPERKITEMTASK_H_

#include "server/zone/objects/tangible/TangibleObject.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace tasks {

class RemoveEventPerkItemTask : public Task {
	ManagedReference<TangibleObject*> tano;

public:
	RemoveEventPerkItemTask(TangibleObject* obj) {
		 tano = obj;
	}

	void run() {
		if (tano == NULL) {
			return;
		}

		Locker locker(tano);

		if (tano->getServerObjectCRC() == 0x46BD798B) { // Jukebox
			Jukebox* jbox = cast<Jukebox*>(tano.get());
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
