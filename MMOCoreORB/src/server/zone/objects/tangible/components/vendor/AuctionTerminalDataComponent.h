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

		if(parent != NULL) {
			auctionManager = parent->getZoneServer()->getAuctionManager();
			if(uid.isEmpty())
				updateUID();
		}
	}

	void updateUID() {

		if(auctionManager == NULL || parent == NULL || parent->getZone() == NULL)
			return;

		String olduid = uid;

		uid = parent->getZone()->getZoneName() + ".";

		String region = "@planet_n:" + parent->getZone()->getZoneName();
		ManagedReference<CityRegion*> cityRegion = parent->getCityRegion();
		if(cityRegion != NULL)
			region = cityRegion->getRegionName();

		uid += region + "." + parent->getDisplayedName() + ".";
		uid += String::valueOf(parent->getObjectID()) + "#";
		uid += String::valueOf(((int)parent->getWorldPositionX())) + "," + String::valueOf(((int)parent->getWorldPositionY()));

		if(olduid != uid)
			auctionManager->updateVendorUID(parent, olduid, uid);
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
