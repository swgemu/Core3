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
#include "server/zone/objects/player/PlayerCreature.h"

class Vendor : public Serializable {
protected:
	VectorMap<unsigned long long, ManagedReference<AuctionItem*> > vendorItems;

	ManagedWeakReference<SceneObject*> vendorRef;

	unsigned long long ownerID;
	String location;
	byte vendorType;
	bool initialized;
	bool vendorSearchEnabled;
	bool disabled;
	bool registered;

	inline void addSerializableVariables() {
		addSerializableVariable("vendorItems", &vendorItems);
		addSerializableVariable("ownerID", &ownerID);
		addSerializableVariable("location", &location);
		addSerializableVariable("vendorType", &vendorType);
		addSerializableVariable("initialized", &initialized);
		addSerializableVariable("vendorSearchEnabled", &vendorSearchEnabled);
		addSerializableVariable("disabled", &disabled);
		addSerializableVariable("registered", &registered);
	}

public:
	static const byte VENDORTERMINAL = 0x01;
	static const byte BAZAARTERMINAL = 0x02;
	static const byte NPCVENDOR = 0x03;

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

		return *this;
	}

	~Vendor() {
		vendorRef = NULL;
	}

	inline void setVendor(SceneObject* objRef) {
		vendorRef = objRef;
	}

	inline void addVendorItem(AuctionItem* item) {
		vendorItems.put(item->getAuctionedItemObjectID(), item);
	}

	inline bool containsVendorItem(unsigned long long itemID) {
		return vendorItems.contains(itemID);
	}

	inline void dropVendorItem(unsigned long long itemID) {
		vendorItems.drop(itemID);
	}

	inline void dropVendorItem(AuctionItem* item) {
		vendorItems.drop(item->getAuctionedItemObjectID());
	}

	inline void setOwnerID(unsigned long long objID) {
		ownerID = objID;
	}

	inline void setInitialized (bool val) {
		initialized = val;
	}

	inline void setVendorSearchEnabled (bool enabled) {
		vendorSearchEnabled = enabled;
	}

	inline void setDisabled (bool isDisabled) {
		disabled = isDisabled;
	}

	inline void setRegistered (bool reg) {
		registered = reg;
	}

	inline SceneObject* getVendor() {
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

	inline byte getVendorType() {
		return vendorType;
	}

	inline int getVendorItemCount() {
		return vendorItems.size();
	}

	inline int getOwnershipRightsOf(PlayerCreature* player) {
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

#endif /* VENDOR_H_ */
