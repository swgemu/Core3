/*
 * VendorMaintSuiCallback.h
 *
 *  Created on: Feb 5, 2012
 *      Author: Kyle
 */

#ifndef VENDORMAINTCALLBACK_H_
#define VENDORMAINTCALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"

class VendorMaintSuiCallback : public SuiCallback {

public:
	VendorMaintSuiCallback(ZoneServer* serv) : SuiCallback(serv) {

	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!sui->isInputBox() || creature == NULL || cancelPressed || args->size() <= 0) {
			return;
		}

		try {
			int value = Integer::valueOf(args->get(0).toString());

			ManagedReference<SceneObject*> vendor = sui->getUsingObject().get();

			if(vendor == NULL)
				return;

			DataObjectComponentReference* data = vendor->getDataObjectComponent();
			if(data == NULL || data->get() == NULL || !data->get()->isVendorData()) {
				return;
			}

			VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());
			if(vendorData == NULL) {
				return;
			}

			if(sui->getWindowType() == SuiWindowType::STRUCTURE_VENDOR_PAY) {
				vendorData->handlePayMaintanence(value);
			} else {
				vendorData->handleWithdrawMaintanence(value);
			}


		} catch(Exception& e) {

		}
	}
};

#endif /* VENDORMAINTCALLBACK_H_ */
