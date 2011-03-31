/*
 * VendorManager.h
 *
 *  Created on: Mar 23, 2011
 *      Author: polonel
 */

#ifndef VENDORMANAGER_H_
#define VENDORMANAGER_H_

#include "engine/engine.h"
#include "VendorSelectionNode.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/auction/Vendor.h"

class VendorManager : public Singleton<VendorManager>, public Logger {
protected:

	VendorSelectionNode rootNode;

public:
	VendorManager();

	void loadLuaVendors();

	void handleDisplayStatus(PlayerCreature* player, Vendor* vendor);

	void sendDestoryTo(PlayerCreature* player, Vendor* vendor);

	void sendRenameVendorTo(PlayerCreature* player, TangibleObject* vendor);

	void handleDestoryCallback(PlayerCreature* player, Vendor* vendor);

	void handleRegisterVendor(PlayerCreature* player, Vendor* vendor);

	void handleRenameVendor(TangibleObject* vendor, String& name);

	VendorSelectionNode* getRootNode() {
		return &rootNode;
	}

};

#endif /* VENDORMANAGER_H_ */
