
#ifndef PETFIXSUICALLBACK_H_
#define PETFIXSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/tangible/deed/pet/PetDeed.h"

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

class PetFixSuiCallback : public SuiCallback {
	ManagedWeakReference<PetControlDevice*> controlDevice;

public:
	PetFixSuiCallback(ZoneServer* server, PetControlDevice* device)
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
		ManagedReference<PetDeed*> deed = pet->getPetDeed();
		Locker lock(pet, player);

		if (otherPressed) {
			deed->adjustPetLevel(player,pet);
		}
		else {
			deed->adjustPetStats(player,pet);
		}

		device->sendAttributeListTo(player);
	}
};

#endif /* PETFIXSUICALLBACK_H_ */
