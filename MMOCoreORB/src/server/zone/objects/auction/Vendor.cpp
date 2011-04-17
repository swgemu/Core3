/*
 * Vendor.cpp
 *
 *  Created on: Mar 15, 2011
 *      Author: polonel
 */

#include "Vendor.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/chat/ChatManager.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/player/PlayerCreature.h"

Vendor::Vendor() {
	ownerID = 0;
	location = "";
	vendorType = 0;
	vendorRef = NULL;
	initialized = false;
	vendorSearchEnabled = true;
	disabled = false;
	registered = false;
	itemWarningLevel = 0x00;
	vendorCheckTask = NULL;
	nextCheckTime = 0;

	vendorItems.setNullValue(NULL);
	vendorItems.setNoDuplicateInsertPlan();

	addSerializableVariables();
}

Vendor::Vendor(const Vendor& v) : Object(), Serializable() {
	vendorItems = v.vendorItems;
	ownerID = v.ownerID;
	location = v.location;
	vendorType = v.vendorType;
	initialized = v.initialized;
	vendorSearchEnabled = v.vendorSearchEnabled;
	disabled = v.disabled;
	registered = v.registered;
	itemWarningLevel = v.itemWarningLevel;
	nextCheckTime = v.nextCheckTime;

	addSerializableVariables();

}

void Vendor::runVendorCheck() {
	if (vendorCheckTask != NULL) {
		vendorCheckTask->reschedule(1000);
	} else {
		vendorCheckTask = new VendorCheckTask(vendorRef);
		vendorCheckTask->schedule(1000); // trigger
	}
}

void Vendor::sendVendorUpdateMail(bool isEmpty) {
	//Send the mail to the vendor owner
	ManagedReference<SceneObject*> strongOwnerRef = vendorRef->getZoneServer()->getObject(ownerID);

	if (!strongOwnerRef->isPlayerCreature())
		return;

	PlayerCreature* owner = (PlayerCreature*) strongOwnerRef.get();
	ChatManager* cman = owner->getZoneServer()->getChatManager();

	String sender = vendorRef->getObjectName()->getDisplayedName();
	UnicodeString subject("@auction:vendor_status_subject");

	if (cman == NULL || owner == NULL)
		return;

	Locker playerLocker(owner);


	if (isEmpty) {
		StringIdChatParameter body("@auction:vendor_status_empty");
		body.setTO(vendorRef->getObjectName()->getDisplayedName());
		cman->sendMail(sender, subject, body, owner->getFirstName());
	} else {
		StringIdChatParameter body("@auction:vendor_status_normal");
		body.setTO(vendorRef->getObjectName()->getDisplayedName());
		cman->sendMail(sender, subject, body, owner->getFirstName());
	}

}

void Vendor::sendVendorDestroyMail() {
	ManagedReference<SceneObject*> strongOwnerRef = vendorRef->getZoneServer()->getObject(ownerID);

	if (!strongOwnerRef->isPlayerCreature())
		return;

	PlayerCreature* owner = (PlayerCreature*) strongOwnerRef.get();
	ChatManager* cman = owner->getZoneServer()->getChatManager();

	String sender = vendorRef->getObjectName()->getDisplayedName();
	UnicodeString subject("@auction:vendor_status_subject");

	if (cman == NULL || owner == NULL)
		return;

	Locker playerLocker(owner);

	StringIdChatParameter body("@auction:vendor_status_deleted");
	body.setTO(vendorRef->getObjectName()->getDisplayedName());
	cman->sendMail(sender, subject, body, owner->getFirstName());

}
