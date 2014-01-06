
#ifndef MOUNTGROWTHARRESTSUICALLBACK_H_
#define MOUNTGROWTHARRESTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/intangible/PetControlDevice.h"

namespace server {
namespace zone {
namespace objects {
namespace creature {
	class CreatureObject;
}
}
}
}

using namespace server::zone::objects::creature;

class MountGrowthArrestSuiCallback : public SuiCallback {
	ManagedWeakReference<PetControlDevice*> controlDevice;

public:
	MountGrowthArrestSuiCallback(ZoneServer* server, PetControlDevice* device)
		: SuiCallback(server) {

		controlDevice = device;
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		ManagedReference<PetControlDevice*> device = controlDevice.get();

		if (device == NULL || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		bool otherPressed = Bool::valueOf(args->get(0).toString());

		ManagedReference<TangibleObject*> controlledObject = device->getControlledObject();

		if (controlledObject == NULL || !controlledObject->isCreature())
			return;

		ManagedReference<Creature*> pet = cast<Creature*>(controlledObject.get());

		Locker lock(pet, player);

		if (otherPressed)
			device->growPet(player, true);
		else
			device->arrestGrowth();

	}
};

#endif /* MOUNTGROWTHARRESTSUICALLBACK_H_ */
