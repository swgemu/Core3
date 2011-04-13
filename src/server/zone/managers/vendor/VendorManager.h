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
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/auction/Vendor.h"
#include "VendorOutfitManager.h"

#include "server/zone/managers/player/PlayerManager.h"


namespace server {
namespace zone {
namespace managers {
namespace vendor {

class VendorManager : public Singleton<VendorManager>, public Logger {
protected:
	VendorSelectionNode rootNode;
	VectorMap<uint64, Vendor*> vendorMap;

public:

	VendorManager();

	~VendorManager() {
		if (!vendorMap.isEmpty()) {
			vendorMap.removeAll();
		}

	}

	void initialize();

	void loadLuaVendors();

	inline void loadVendorOutfits() {
		VendorOutfitManager::instance()->initialize();
	}

	bool isValidVendorName(const String& name);

	void handleDisplayStatus(PlayerCreature* player, Vendor* vendor);

	void sendDestoryTo(PlayerCreature* player, Vendor* vendor);

	void sendRenameVendorTo(PlayerCreature* player, TangibleObject* vendor);

	void handleDestoryCallback(PlayerCreature* player, Vendor* vendor);

	void handleRegisterVendor(PlayerCreature* player, Vendor* vendor);

	void handleRenameVendor(PlayerCreature* player, TangibleObject* vendor, String& name);

	void handleAwardVendorLookXP(PlayerCreature* player, Vendor* vendor);

	void randomizeCustomization(CreatureObject* vendor);

	inline VendorSelectionNode* getRootNode() {
		return &rootNode;
	}

	inline void addVendor(uint64 objectID, Vendor* vendor) {
		if (!vendor->isBazaarTerminal())
			vendorMap.put(objectID, vendor);
	}

	inline void dropVendor(uint64 objectID) {
		vendorMap.drop(objectID);
	}

	inline void dropVendor(int idx) {
		vendorMap.drop(idx);
	}

	inline Vendor* getVendor(int idx) {
		return vendorMap.get(idx);
	}

	inline Vendor* getVendor(uint64 objectID) {
		return vendorMap.get(objectID);
	}

	inline int getVendorMapSize() {
		return vendorMap.size();
	}

};

}
}
}
}

using namespace server::zone::managers::vendor;

#endif /* VENDORMANAGER_H_ */
