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
#include "server/zone/objects/auction/Vendor.h"
#include "server/zone/objects/tangible/terminal/vendor/VendorTerminal.h"
#include "server/zone/objects/creature/vendor/VendorCreature.h"

class DestroyVendorSuiCallback : public SuiCallback {
public:
	DestroyVendorSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(PlayerCreature* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isMessageBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		ManagedReference<SceneObject*> sceno = suiBox->getUsingObject();

		if (!sceno->isVendor())
			return;

		Vendor* vendor = NULL;

		if (sceno->isTerminal()) {
			VendorTerminal* vendorTerminal = dynamic_cast<VendorTerminal*>(sceno.get());
			vendor = vendorTerminal->getVendor();
		} else if (sceno->isCreatureObject()) {
			VendorCreature* vendorCreature = dynamic_cast<VendorCreature*>(sceno.get());
			vendor = vendorCreature->getVendor();
		}

		if (vendor == NULL)
			return;

		VendorManager::instance()->handleDestoryCallback(player, vendor);
	}
};

#endif /* DESTROYVENDORSUICALLBACK_H_ */
