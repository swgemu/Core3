/*
 * VendorDataComponent.h
 *
 *  Created on: 5/27/2012
 *      Author: kyle
 */

#ifndef VENDORDATACOMPONENT_H_
#define VENDORDATACOMPONENT_H_

#include "VendorDataComponent.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/components/DataObjectComponent.h"
#include "server/zone/objects/auction/AuctionItem.h"
#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/Zone.h"

class VendorDataComponent : public DataObjectComponent {
protected:
	uint64 ownerId;
	uint64 vendorId;

	ManagedReference<TangibleObject*> vendor;

	Reference<Task*> vendorCheckTask;

	String location;
	bool initialized;
	bool vendorSearchEnabled;
	bool disabled;
	bool registered;

	Time lastSuccessfulUpdate;

	int maintAmount;

	Time lastXpAward;
	int awardUsageXP;

	String UID;

public:
	/// 5 minutes
	static const int USEXPINTERVAL = 1;//60 * 5;
	// 60 Minutes
	static const int VENDORCHECKINTERVAL = 1;//60 * 5;

public:
	VendorDataComponent();

	virtual ~VendorDataComponent() {
		if(vendorCheckTask != NULL)
			vendorCheckTask->cancel();
	}

	void initializeTransientMembers();

	void notifyObjectDestroyingFromDatabase();

	void sendVendorUpdateMail(bool isEmpty);

	void sendVendorDestroyMail();

	void runVendorUpdate();

	void setOwnerId(uint64 id) {
		ownerId = id;
	}

	uint64 getOwnerId() {
		return ownerId;
	}

	void updateUID() {

		if(vendor == NULL)
			return;

		UID = vendor->getZone()->getZoneName() + ".";

		String region = vendor->getZone()->getZoneName();
		ManagedReference<CityRegion*> cityRegion = vendor->getCityRegion();
		if(cityRegion != NULL)
			region = cityRegion->getRegionName();

		UID += region + "." + vendor->getDisplayedName() + "#";
		UID += String::valueOf(vendor->getPositionX()) + "," + String::valueOf(vendor->getPositionY());
	}

	String getUID() {
		return UID;
	}

	bool isVendorData() {
		return true;
	}
	inline void setVendor(TangibleObject* objRef) {
		vendor = objRef;
		vendorId = objRef->getObjectID();
	}

	inline void setInitialized(bool val) {
		initialized = val;
		updateUID();
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


	inline TangibleObject* getVendor() {
		return vendor;
	}

	virtual inline String getLocation() {
		return location;
	}

	inline void setLocation(const String& loc) {
		location = loc;
	}

	inline int getOwnershipRightsOf(CreatureObject* player) {
		if (!initialized)
			return 2; // mark not initalized

		if (player->getObjectID() == ownerId) // Player owns this vendor
			return 0;
		else if (ownerId != 0) // someone else owns the vendor and its not a bazaar
			return 1;
		else
			return 2; // the vendor hasn't been initalized yet or it belongs to no one (bazaar)
	}

	inline bool isVendorOwner(CreatureObject* player) {
		return player->getObjectID() == ownerId;
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

	inline void awardUseXP() {
		if(time(0) - lastXpAward.getTime() > USEXPINTERVAL) {
			awardUsageXP++;
			lastXpAward.updateToCurrentTime();
		}
	}

	private:
		void addSerializableVariables();
};


#endif /* VENDORDATACOMPONENT_H_ */
