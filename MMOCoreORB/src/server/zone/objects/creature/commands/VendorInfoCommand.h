/*
 * VendorInfoCommand.h
 *
 *  Created on: Apr 6, 2011
 *      Author: polonel
 */

#ifndef VENDORINFOCOMMAND_H_
#define VENDORINFOCOMMAND_H_

#include "engine/engine.h"
#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/managers/auction/AuctionManager.h"
#include "server/zone/managers/auction/AuctionsMap.h"

class VendorInfoCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (!creature->isPlayerCreature() && !creature->getPlayerObject()->isPrivileged())
			return 1;

		ManagedReference<CreatureObject*> targetObject;

		if (!arguments.isEmpty()) {
			ManagedReference<PlayerManager*> playerManager = creature->getZoneServer()->getPlayerManager();

			targetObject = playerManager->getPlayer(arguments.toString());
		} else {
			targetObject = creature->getZoneServer()->getObject(creature->getTargetID()).castTo<CreatureObject*>();
		}

		if (targetObject == NULL || !targetObject->isPlayerCreature()) {
			targetObject = creature;
		}

		Locker locker(targetObject, creature);

		PlayerObject* ghost = targetObject->getPlayerObject();

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, 0);

		box->setPromptTitle("Vendor Info");

		StringBuffer promptText;

		promptText << "Player Name:\t" << targetObject->getFirstName() << endl;
		promptText << "ObjectID:\t" << targetObject->getObjectID() << endl;
		promptText << "Max number of vendors:\t" << targetObject->getSkillMod("manage_vendor") << endl << endl;
		promptText << "Vendors:" << endl;

		SortedVector<unsigned long long>* ownedVendors = ghost->getOwnedVendors();
		for (int i = 0; i < ownedVendors->size(); i++) {
			ManagedReference<SceneObject*> vendor = creature->getZoneServer()->getObject(ownedVendors->elementAt(i));

			int num = i + 1;
			promptText << endl << String::valueOf(num) << ". ";

			if (vendor == NULL) {
				promptText << "NULL Vendor" << endl << endl;
				continue;
			}

			promptText << "VendorID:\t" << vendor->getObjectID() << endl;

			DataObjectComponentReference* data = vendor->getDataObjectComponent();
			if(data == NULL || data->get() == NULL || !data->get()->isVendorData()) {
				promptText << "    NULL Data Component" << endl << endl;
				continue;
			}

			VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());
			if(vendorData == NULL) {
				promptText << "    NULL Vendor Data Component" << endl << endl;
				continue;
			}

			bool init = false;
			if (vendorData->isInitialized())
				init = true;

			promptText << "    Initialized?\t" << (init ? "Yes" : "No");
			promptText << endl;

			promptText << "    Parent:\t";

			ManagedReference<SceneObject*> parent = vendor->getParent().get();
			if (parent == NULL)
				promptText << "NULL" << endl;
			else
				promptText << parent->getObjectID() << endl;

			promptText << "    Zone:\t";

			Zone* zone = vendor->getZone();
			if (zone == NULL) {
				promptText << "NULL" << endl;
			} else {
				promptText << zone->getZoneName() << endl;
				promptText << "    World Position:\t" << vendor->getWorldPositionX() << ", " << vendor->getWorldPositionY() << endl;
			}

		}

		box->setPromptText(promptText.toString());

		creature->sendMessage(box->generateMessage());

		return 0;
	}

};

#endif /* VENDORINFOCOMMAND_H_ */
