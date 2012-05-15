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
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/managers/player/PlayerManager.h"


namespace server {
namespace zone {
namespace managers {
namespace vendor {

class VendorManager : public Singleton<VendorManager>, public Mutex, public Logger, public Object {
protected:
	Reference<VendorSelectionNode*> rootNode;
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

	void handleDisplayStatus(CreatureObject* player, Vendor* vendor);

	void sendDestoryTo(CreatureObject* player, Vendor* vendor);

	void sendRenameVendorTo(CreatureObject* player, TangibleObject* vendor);

	void handleDestoryCallback(CreatureObject* player, Vendor* vendor);

	void sendRegisterVendorTo(CreatureObject* player, Vendor* vendor);

	void handleRegisterVendorCallback(CreatureObject* player, Vendor* vendor, const String& planetMapCategoryName);

	void handleUnregisterVendor(CreatureObject* player, Vendor* vendor);

	void handleRenameVendor(CreatureObject* player, TangibleObject* vendor, String& name);

	void handleAwardVendorLookXP(CreatureObject* player, Vendor* vendor);

	void randomizeCustomization(CreatureObject* vendor);

	inline VendorSelectionNode* getRootNode() {
		return rootNode;
	}

	inline void addVendor(uint64 objectID, Vendor* vendor) {
		if (!vendor->isBazaarTerminal()) {
			Locker locker(this);
			vendorMap.put(objectID, vendor);
		}
	}

	inline void dropVendor(uint64 objectID) {
		Locker locker(this);
		vendorMap.drop(objectID);
	}

	inline void dropVendor(int idx) {
		Locker locker(this);
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
