/*
 * DestroyVendorSuiCallback.h
 *
 *  Created on: Mar 25, 2011
 *      Author: polonel
 */

#ifndef DESTROYVENDORSUICALLBACK_H_
#define DESTROYVENDORSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/vendor/VendorManager.h"

class DestroyVendorSuiCallback : public SuiCallback {
public:
	DestroyVendorSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isMessageBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		ManagedReference<SceneObject*> object = suiBox->getUsingObject().get();

		if (object == NULL || !object->isVendor())
			return;

		TangibleObject* vendor = cast<TangibleObject*>(object.get());

		if (vendor == NULL)
			return;

		Locker clocker(vendor, player);

		VendorManager::instance()->destroyVendor(vendor);
	}
};

#endif /* DESTROYVENDORSUICALLBACK_H_ */
