/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef AUCTIONQUERYHEADERSRESPONSEMESSAGE_H_
#define AUCTIONQUERYHEADERSRESPONSEMESSAGE_H_

#include "engine/service/proto/BaseMessage.h"
#include "server/zone/objects/auction/AuctionItem.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/ZoneServer.h"

class AuctionQueryHeadersResponseMessage : public BaseMessage {

	Vector<ManagedReference<AuctionItem*> > itemList;

	SortedVector<String> locationList;

	ManagedReference<CreatureObject*> player;

public:
	AuctionQueryHeadersResponseMessage(int screen, int counter, CreatureObject* player) : BaseMessage() {
		insertShort(0x08);
		insertInt(0xFA500E52);  // opcode

		insertInt(counter);
		insertInt(screen); // Vendor screen number

		setCompression(true);

		this->player = player;

		locationList.setNoDuplicateInsertPlan();
	}

	void addItemToList(AuctionItem* ai) {
		locationList.put(ai->getVendorUID());
		locationList.put(ai->getOwnerName());

		if(ai->isAuction() && ai->getStatus() == AuctionItem::FORSALE)
			locationList.put("");
		else
			locationList.put(ai->getBidderName());

		itemList.add(ai);
	}

	void dumpLocationList() {
		int llSize = locationList.size();

		insertInt(llSize);

		for (int i = 0; i < locationList.size(); i++) {
			insertAscii(locationList.get(i));
		}
	}

	void dumpItemNameList() {
		int ilSize = itemList.size();

		insertInt(ilSize);

		for (int i = 0; i < itemList.size(); i++) {
			AuctionItem* il = itemList.get(i);

	    	UnicodeString name = il->getItemName();
	    	insertUnicode(name); //name
		}
	}

	void dumpItemInfoList() {
		int ilSize = itemList.size();

		insertInt(ilSize);

		for (int i = 0; i < itemList.size(); i++) {
			AuctionItem* il = itemList.get(i);

			int accessFee = 0;
			ManagedReference<SceneObject*> vendor = player->getZoneServer()->getObject(il->getVendorID());
			if(vendor != NULL) {
				ManagedReference<SceneObject*> parent = vendor->getRootParent();
				if(parent != NULL && parent->isBuildingObject()) {
					BuildingObject* building = cast<BuildingObject*>(parent.get());
					if(building != NULL)
						accessFee = building->getAccessFee();
				}
			}

			insertLong(il->getAuctionedItemObjectID()); //item id
			insertByte(i);  // List item String number

			insertInt(il->getPrice()); //item cost.

			Time expireTime;
			uint32 expire = il->getExpireTime() - expireTime.getMiliTime() / 1000;

			insertInt(expire);

	    	if (il->isAuction())
	    		insertByte(0);
	    	else
	    		insertByte(1);

	    	insertShort(locationList.find(il->getVendorUID()));

	    	insertLong(il->getOwnerID()); // seller ID

	    	insertShort(locationList.find(il->getOwnerName()));

	    	if(il->isAuction() && il->getStatus() == AuctionItem::FORSALE) {
	    		insertLong(0);
	    		insertShort(locationList.find(""));
	    	} else {
	    		insertLong(il->getBuyerID()); // buyer ID
	    		insertShort(locationList.find(il->getBidderName()));
	    	}

	    	insertInt(il->getProxy()); // my proxy not implemented yet
	    	insertInt(il->getPrice()); // my bid default to price

	    	insertInt(il->getItemType());

	    	//insertInt(il->getAuctionOptions()); // autionOptions 0x400 = Premium, 0x800 = withdraw
	    	int additionalValues = 0;

	    	if (il->getOwnerID() == player->getObjectID() &&
	    			(il->getStatus() == AuctionItem::FORSALE || il->getStatus() == AuctionItem::OFFERED)) {
	    		additionalValues |= 0x800;
	    	}

	    	insertInt(il->getAuctionOptions() | additionalValues);
	    	//insertInt(10);

	    	insertInt(accessFee);
		}
	}

	void createMessage(int offset = 0, bool continues = false) {
		dumpLocationList();

		dumpItemNameList();

		dumpItemInfoList();

		insertShort(offset); // Item list start offset

		insertByte(continues); // more to come?
	}

	inline int getListSize() {
		return itemList.size();
	}

};

#endif /*AUCTIONQUERYHEADERSRESPONSEMESSAGE_H_*/
