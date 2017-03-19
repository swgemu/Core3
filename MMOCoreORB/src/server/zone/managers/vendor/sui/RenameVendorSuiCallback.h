/*
 * RenameVendorSuiCallback.h
 *
 *  Created on: Mar 27, 2011
 *      Author: polonel
 */

#ifndef RENAMEVENDORSUICALLBACK_H_
#define RENAMEVENDORSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/vendor/VendorManager.h"

class RenameVendorSuiCallback : public SuiCallback {
public:
	RenameVendorSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isInputBox())
			return;

		if (args->size() < 1)
			return;

		if (cancelPressed) {
			return;
		}

		String name = args->get(0).toString();

		ManagedReference<SceneObject*> strong = suiBox->getUsingObject().get();

		if (strong == NULL)
			return;

		TangibleObject* vendor = cast<TangibleObject*>(strong.get());

		if (vendor == NULL)
			return;

		VendorManager::instance()->handleRenameVendor(player, vendor, name);
	}
};

#endif /* RENAMEVENDORSUICALLBACK_H_ */
