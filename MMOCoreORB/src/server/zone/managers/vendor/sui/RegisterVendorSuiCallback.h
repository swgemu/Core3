/*
 * RegisterVendorSuiCallback.h
 *
 *  Created on: May 1, 2011
 *      Author: polonel
 */

#ifndef REGISTERVENDORSUICALLBACK_H_
#define REGISTERVENDORSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/objects/auction/Vendor.h"
#include "server/zone/objects/tangible/terminal/vendor/VendorTerminal.h"
#include "server/zone/objects/creature/vendor/VendorCreature.h"

class RegisterVendorSuiCallback : public SuiCallback {
public:
	RegisterVendorSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		ManagedReference<SceneObject*> sceno = suiBox->getUsingObject();

		if (!sceno->isVendor())
			return;

		Vendor* vendor = NULL;

		if (sceno->isTerminal()) {
			VendorTerminal* vendorTerminal = dynamic_cast<VendorTerminal*>(sceno.get());

			if (vendorTerminal != NULL)
				vendor = vendorTerminal->getVendor();

		} else if (sceno->isCreatureObject()) {
			VendorCreature* vendorCreature = dynamic_cast<VendorCreature*>(sceno.get());

			if (vendorCreature != NULL)
				vendor = vendorCreature->getVendor();
		}

		if (vendor == NULL)
			return;

		SuiListBox* suiListBox = (SuiListBox*) suiBox;

		int index = Integer::valueOf(args->get(0).toString());

		String planetMapCategoryName = suiListBox->getMenuItemName(index).subString(25);

		VendorManager::instance()->handleRegisterVendorCallback(player, vendor, planetMapCategoryName);
	}
};

#endif /* REGISTERVENDORSUICALLBACK_H_ */
