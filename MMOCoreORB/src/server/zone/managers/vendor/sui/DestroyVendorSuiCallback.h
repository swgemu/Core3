/*
 * DestroyVendorSuiCallback.h
 *
 *  Created on: Mar 25, 2011
 *      Author: polonel
 */

#ifndef DESTROYVENDORSUICALLBACK_H_
#define DESTROYVENDORSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sessions/vendor/CreateVendorSession.h"
#include "server/zone/managers/vendor/VendorManager.h"

class DestroyVendorSuiCallback : public SuiCallback {
public:
	DestroyVendorSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isMessageBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		ManagedReference<SceneObject*> object = suiBox->getUsingObject();

		if (!object->isVendor() || object == NULL)
			return;

		TangibleObject* vendor = cast<TangibleObject*>(object.get());

		Locker clocker(vendor, player);

		VendorManager::instance()->handleDestroyCallback(player, vendor);
	}
};

#endif /* DESTROYVENDORSUICALLBACK_H_ */
