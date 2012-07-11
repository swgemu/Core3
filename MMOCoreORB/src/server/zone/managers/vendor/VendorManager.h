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
#include "server/zone/managers/name/NameManager.h"
#include "VendorOutfitManager.h"

namespace server {
namespace zone {
namespace managers {
namespace vendor {

class VendorManager : public Singleton<VendorManager>, public Mutex, public Logger, public Object {
protected:
	Reference<VendorSelectionNode*> rootNode;

	ManagedReference<ZoneProcessServer*> server;
	Reference<NameManager*> nameManager;

public:

	VendorManager();

	~VendorManager() {

	}

	void initialize(ZoneProcessServer* zserv);

	void loadLuaVendors();

	inline void loadVendorOutfits() {
		VendorOutfitManager::instance()->initialize();
	}

	bool isValidVendorName(const String& name);

	void handleDisplayStatus(CreatureObject* player, TangibleObject* vendor);

	void promptDestroyVendor(CreatureObject* player, TangibleObject* vendor);

	void promptRenameVendorTo(CreatureObject* player, TangibleObject* vendor);

	void handleDestroyCallback(CreatureObject* player, TangibleObject* vendor);

	void destroyVendor(SceneObject* vendor);

	void sendRegisterVendorTo(CreatureObject* player, TangibleObject* vendor);

	void handleRegisterVendorCallback(CreatureObject* player, TangibleObject* vendor, const String& planetMapCategoryName);

	void handleUnregisterVendor(CreatureObject* player, TangibleObject* vendor);

	void handleRenameVendor(CreatureObject* player, TangibleObject* vendor, String& name);

	void randomizeCustomization(TangibleObject* vendor);

	inline VendorSelectionNode* getRootNode() {
		return rootNode;
	}
};

}
}
}
}

using namespace server::zone::managers::vendor;

#endif /* VENDORMANAGER_H_ */
