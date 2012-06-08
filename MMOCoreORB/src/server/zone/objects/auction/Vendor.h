/*
 * Vendor.h
 *
 *  Created on: Mar 15, 2011
 *      Author: polonel
 */

#ifndef VENDOR_H_
#define VENDOR_H_

#include "engine/core/Core.h"
#include "server/zone/objects/auction/AuctionItem.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/auction/events/VendorCheckTask.h"

namespace server {
namespace zone {
namespace objects {
namespace auction {

class Vendor : public Serializable {
protected:
	VectorMap<unsigned long long, ManagedReference<AuctionItem*> > vendorItems;

	ManagedWeakReference<SceneObject*> vendorRef;

	Reference<VendorCheckTask*> vendorCheckTask;
	Time nextCheckTime;

	unsigned long long ownerID;
	String location;
	byte vendorType;
	bool initialized;
	bool vendorSearchEnabled;
	bool disabled;
	bool registered;
	byte itemWarningLevel;

	inline void addSerializableVariables() {
		addSerializableVariable("vendorItems", &vendorItems);
		addSerializableVariable("ownerID", &ownerID);
		addSerializableVariable("location", &location);
		addSerializableVariable("vendorType", &vendorType);
		addSerializableVariable("initialized", &initialized);
		addSerializableVariable("vendorSearchEnabled", &vendorSearchEnabled);
		addSerializableVariable("disabled", &disabled);
		addSerializableVariable("registered", &registered);
		addSerializableVariable("itemWarningLevel", &itemWarningLevel);
		addSerializableVariable("nextCheckTime", &nextCheckTime);

	}

public:
	static const byte VENDORTERMINAL = 0x01;
	static const byte BAZAARTERMINAL = 0x02;
	static const byte NPCVENDOR = 0x03;

	static const int CHECKINTERVAL = 1; // days

	Vendor();

	Vendor(const Vendor& v);
	Vendor& operator=(const Vendor& v) {
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

		return *this;
	}

	~Vendor() {
		vendorRef = NULL;
		clearEvents();
	}

	void sendVendorUpdateMail(bool isEmpty);
	void sendVendorDestroyMail();
	void runVendorCheck();

	inline void clearEvents() {
		if (vendorCheckTask != NULL) {
			if (vendorCheckTask->isScheduled())
				vendorCheckTask->cancel();
			vendorCheckTask = NULL;
		}
	}

	inline void rescheduleEvent() {
		if (vendorCheckTask != NULL || isBazaarTerminal() || vendorItems.size() > 0)
			return;

		if (nextCheckTime.isPast()) {
			vendorCheckTask = new VendorCheckTask(vendorRef.get());
			vendorCheckTask->schedule(1000);
		} else {
			vendorCheckTask = new VendorCheckTask(vendorRef.get());
			vendorCheckTask->schedule(nextCheckTime);
		}
	}

	inline void setNextCheckTime(Time time) {
		nextCheckTime = time;
	}

	inline void setVendor(SceneObject* objRef) {
		vendorRef = objRef;
	}

	inline void addVendorItem(AuctionItem* item) {
		if (vendorItems.size() == 0 && !isBazaarTerminal())
			sendVendorUpdateMail(false);

		vendorItems.put(item->getAuctionedItemObjectID(), item);
	}

	inline bool containsVendorItem(unsigned long long itemID) {
		return vendorItems.contains(itemID);
	}

	inline void dropVendorItem(unsigned long long itemID) {
		vendorItems.drop(itemID);

		if (vendorItems.size() <= 0 && !isBazaarTerminal()) {
			if (vendorCheckTask != NULL)
				vendorCheckTask->reschedule(1000);
			else {
				vendorCheckTask = new VendorCheckTask(vendorRef.get());
				vendorCheckTask->schedule(1000);
			}
		}

	}

	inline void dropVendorItem(AuctionItem* item) {
		vendorItems.drop(item->getAuctionedItemObjectID());

		if (vendorItems.size() <= 0 && !isBazaarTerminal()) {
			if (vendorCheckTask != NULL)
				vendorCheckTask->reschedule(1000);
			else {
				vendorCheckTask = new VendorCheckTask(vendorRef.get());
				vendorCheckTask->schedule(1000);
			}
		}
	}

	inline void setOwnerID(unsigned long long objID) {
		ownerID = objID;
	}

	inline void setInitialized(bool val) {
		initialized = val;
	}

	inline void setVendorSearchEnabled(bool enabled) {
		vendorSearchEnabled = enabled;
	}

	inline void setDisabled(bool isDisabled) {
		disabled = isDisabled;
	}

	inline void setRegistered(bool reg) {
		registered = reg;
	}

	inline void setItemWarningLevel(byte lvl) {
		itemWarningLevel = lvl;
	}

	inline ManagedWeakReference<SceneObject*> getVendor() {
		return vendorRef;
	}

	inline int getMaxPrice() {
		if (vendorType == BAZAARTERMINAL)
			return 20000;
		else
			return 99999999;
	}

	inline unsigned long long getOwnerID() {
		return ownerID;
	}

	virtual inline String getLocation() {
		return location;
	}

	inline void setLocation(const String& loc) {
		location = loc;
	}

	inline void setVendorType(byte type) {
		vendorType = type;
	}

	inline byte getItemWarningLevel() {
		return itemWarningLevel;
	}

	inline byte getVendorType() {
		return vendorType;
	}

	inline int getVendorItemCount() {
		return vendorItems.size();
	}

	inline int getOwnershipRightsOf(CreatureObject* player) {
		if (!initialized)
			return 2; // mark not initalized

		if (player->getObjectID() == ownerID) // Player owns this vendor
			return 0;
		else if (ownerID != 0) // someone else owns the vendor and its not a bazaar
			return 1;
		else
			return 2; // the vendor hasn't been initalized yet or it belongs to no one (bazaar)
	}

	inline VectorMap<unsigned long long, ManagedReference<AuctionItem*> >* getVendorItems() {
		return &vendorItems;
	}

	inline bool isVendorOwner(unsigned long long playerID) {
		return playerID == ownerID;
	}

	inline bool isVendorTerminal() {
		return vendorType == VENDORTERMINAL;
	}

	inline bool isBazaarTerminal() {
		return vendorType == BAZAARTERMINAL;
	}

	inline bool isNpcVendor() {
		return vendorType == NPCVENDOR;
	}

	inline bool isInitialized() {
		return initialized;
	}

	inline bool isVendorSearchEnabled() {
		return vendorSearchEnabled;
	}

	inline bool isDisabled() {
		return disabled;
	}

	inline bool isRegistered() {
		return registered;
	}

};

}
}
}
}

using namespace server::zone::objects::auction;

#endif /* VENDOR_H_ */
