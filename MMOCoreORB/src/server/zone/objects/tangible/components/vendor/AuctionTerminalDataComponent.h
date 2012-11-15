/*
 * AuctionTerminalDataComponent.h
 *
 *  Created on: 5/27/2012
 *      Author: kyle
 */

#ifndef AUCTIONTERMINALDATACOMPONENT_H_
#define AUCTIONTERMINALDATACOMPONENT_H_

#include "server/zone/objects/scene/components/DataObjectComponent.h"
#include "server/zone/managers/auction/AuctionManager.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/Zone.h"

class AuctionTerminalDataComponent : public DataObjectComponent {
protected:

	ManagedReference<AuctionManager*> auctionManager;
	String uid;

public:
	AuctionTerminalDataComponent() {
		uid = "";
		addSerializableVariables();
	}

	virtual ~AuctionTerminalDataComponent() {

	}

	void initializeTransientMembers() {

		if(parent.get() != NULL) {
			auctionManager = parent.get()->getZoneServer()->getAuctionManager();
			if(uid.isEmpty())
				updateUID();
		}
	}

	void updateUID() {

		if(auctionManager == NULL || parent.get() == NULL || parent.get()->getZone() == NULL)
			return;

		String olduid = uid;

		uid = parent.get()->getZone()->getZoneName() + ".";

		String region = "@planet_n:" + parent.get()->getZone()->getZoneName();
		ManagedReference<CityRegion*> cityRegion = parent.get()->getCityRegion();
		if(cityRegion != NULL)
			region = cityRegion->getRegionName();

		uid += region + "." + parent.get()->getDisplayedName() + ".";
		uid += String::valueOf(parent.get()->getObjectID()) + "#";
		uid += String::valueOf(((int)parent.get()->getWorldPositionX())) + "," + String::valueOf(((int)parent.get()->getWorldPositionY()));

		if(olduid != uid)
			auctionManager->updateVendorUID(parent.get(), olduid, uid);
	}

	String getUID() {
		return uid;
	}

	bool isAuctionTerminalData() {
		return true;
	}

private:
	void addSerializableVariables() {
		addSerializableVariable("uid", &uid);
	}
};


#endif /* AUCTIONTERMINALDATACOMPONENT_H_ */
