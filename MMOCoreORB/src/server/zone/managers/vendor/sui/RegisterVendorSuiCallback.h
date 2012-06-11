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

		ManagedReference<SceneObject*> object = suiBox->getUsingObject();

		if (!object->isVendor() || object == NULL)
			return;

		TangibleObject* vendor = cast<TangibleObject*>(object.get());

		SuiListBox* suiListBox = cast<SuiListBox*>( suiBox);

		int index = Integer::valueOf(args->get(0).toString());

		String planetMapCategoryName = suiListBox->getMenuItemName(index).subString(25);

		VendorManager::instance()->handleRegisterVendorCallback(player, vendor, planetMapCategoryName);
	}
};

#endif /* REGISTERVENDORSUICALLBACK_H_ */
