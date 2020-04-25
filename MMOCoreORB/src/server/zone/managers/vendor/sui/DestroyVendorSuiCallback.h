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
#include "server/zone/objects/transaction/TransactionLog.h"

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

		if (object == nullptr || !object->isVendor())
			return;

		TangibleObject* vendor = cast<TangibleObject*>(object.get());

		if (vendor == nullptr)
			return;

		Locker clocker(vendor, player);

		TransactionLog trx(player, vendor, TrxCode::VENDORLIFECYCLE);

		if (trx.isVerbose()) {
			// Force a synchronous export because the object will be deleted before we can export it!
			trx.addRelatedObject(object, true);
			trx.setExportRelatedObjects(true);
			trx.exportRelated();
		}

		VendorManager::instance()->destroyVendor(vendor);
	}
};

#endif /* DESTROYVENDORSUICALLBACK_H_ */
