/*
 * AuctionsMap.cpp
 *
 *  Created on: 6/3/2012
 *      Author: kyle
 */

#include "engine/engine.h"

#include "AuctionsMap.h"
#include "AuctionTerminalMap.h"
#include "server/zone/objects/auction/AuctionItem.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/ZoneServer.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/packets/auction/ItemSoldMessage.h"

int AuctionsMapImplementation::addItem(CreatureObject* player, SceneObject* vendor, AuctionItem* item) {
	if(vendor == NULL || vendor->getZone() == NULL)
		return ItemSoldMessage::VENDORNOTWORKING;

	String planet = vendor->getZone()->getZoneName();

	String region = "@planet_n:" + vendor->getZone()->getZoneName();
	ManagedReference<CityRegion*> cityRegion = vendor->getCityRegion();
	if(cityRegion != NULL)
		region = cityRegion->getRegionName();

	if(vendor->isBazaarTerminal())
		return addBazaarItem(player, planet, region, vendor, item);

	return addVendorItem(player, planet, region, vendor, item);
}

int AuctionsMapImplementation::addVendorItem(CreatureObject* player, const String& planet, const String& region, SceneObject* vendor, AuctionItem* item) {
	Locker locker(_this.get());

	if(allItems.contains(item->getAuctionedItemObjectID()))
		return ItemSoldMessage::ALREADYFORSALE;

	if(!vendorItemsForSale.contains(vendor->getObjectID()) && !vendorItemsForSale.createTerminalListing(planet, region, vendor))
		return ItemSoldMessage::VENDORNOTWORKING;

	Reference<TerminalItemList*> vendorItems = vendorItemsForSale.get(vendor->getObjectID());
	if(vendorItems->isEmpty()) {

		VendorDataComponent* vendorData = NULL;
		DataObjectComponentReference* data = vendor->getDataObjectComponent();
		if(data != NULL && data->get() != NULL && data->get()->isVendorData()) {
			vendorData = cast<VendorDataComponent*>(data->get());
			if(vendorData == NULL)
				return ItemSoldMessage::VENDORNOTWORKING;

			vendorItems->setSearchable(vendorData->isVendorSearchEnabled());
		}
	}

	if(vendorItems == NULL)
		return ItemSoldMessage::INVALIDAUCTIONER;

	//Locker vlocker(vendorItems);

	int result = vendorItems->put(item);

	if(result == -1)
		return ItemSoldMessage::UNKNOWNERROR;

	allItems.put(item->getAuctionedItemObjectID(), item);

	if(vendorItems->size() == 1 && player != NULL)
		sendVendorUpdateMail(vendor, false);

	return ItemSoldMessage::SUCCESS;
}

int AuctionsMapImplementation::addBazaarItem(CreatureObject* player, const String& planet, const String& region, SceneObject* vendor, AuctionItem* item) {
	Locker locker(_this.get());

	if(allItems.contains(item->getAuctionedItemObjectID()))
		return ItemSoldMessage::ALREADYFORSALE;

	if(!bazaarItemsForSale.contains(vendor->getObjectID()) && !bazaarItemsForSale.createTerminalListing(planet, region, vendor))
		return ItemSoldMessage::VENDORNOTWORKING;

	Reference<TerminalItemList*> bazaarItems = bazaarItemsForSale.get(vendor->getObjectID());

	if(bazaarItems == NULL)
		return ItemSoldMessage::INVALIDAUCTIONER;

	//Locker blocker(bazaarItems);
	int result = bazaarItems->put(item);

	if(result == -1)
		return ItemSoldMessage::UNKNOWNERROR;

	allItems.put(item->getAuctionedItemObjectID(), item);
	return ItemSoldMessage::SUCCESS;
}

void AuctionsMapImplementation::deleteItem(SceneObject* vendor, AuctionItem* item) {

	Locker locker(_this.get());

	if(vendor != NULL) {
		if(vendor->isBazaarTerminal())
			removeBazaarItem(vendor, item);
		else
			removeVendorItem(vendor, item);
	}

	allItems.drop(item->getAuctionedItemObjectID());
	ObjectManager::instance()->destroyObjectFromDatabase(item->_getObjectID());
}

void AuctionsMapImplementation::removeVendorItem(SceneObject* vendor, AuctionItem* item) {
	Locker locker(_this.get());
		
	Reference<TerminalItemList*> vendorItems = vendorItemsForSale.get(vendor->getObjectID());

	if(vendorItems == NULL)
		return;

	if(!vendorItems->contains(item))
		return;

	//Locker vlocker(vendorItems);

	if(vendorItems->removeElement(item)) {

		if(vendorItems->size() == 0)
			sendVendorUpdateMail(vendor, true);

		return;
	}

	logger.error("unable to remove vendor item");
}

void AuctionsMapImplementation::removeBazaarItem(SceneObject* vendor,  AuctionItem* item) {
	Locker locker(_this.get());
		
	Reference<TerminalItemList*> bazaarItems = bazaarItemsForSale.get(vendor->getObjectID());

	if(bazaarItems == NULL)
		return;

	if(!bazaarItems->contains(item))
		return;

	//Locker blocker(bazaarItems);

	if(!bazaarItems->removeElement(item))
		logger.error("unable to remove bazaar item");

}

TerminalListVector AuctionsMapImplementation::getVendorTerminalData(const String& planet, const String& region, SceneObject* vendor) {
	Locker locker(_this.get());
	
	return vendorItemsForSale.getTerminalData(planet, region, vendor);
}

TerminalListVector AuctionsMapImplementation::getBazaarTerminalData(const String& planet, const String& region, SceneObject* vendor) {
	Locker locker(_this.get());
	
	return bazaarItemsForSale.getTerminalData(planet, region, vendor);
}

int AuctionsMapImplementation::getVendorItemCount(SceneObject* vendor) {
	Locker locker(_this.get());
	
	if(vendor == NULL) {
		logger.error("null vendor in AuctionsMapImplementation::getVendorItemCount");
		return 0;
	}

	Reference<TerminalItemList*> vendorItems = vendorItemsForSale.get(vendor->getObjectID());

	if(vendorItems == NULL)
		return 0;

	return vendorItems->size();
}

void AuctionsMapImplementation::deleteTerminalItems(SceneObject* vendor) {
	Locker locker(_this.get());
	
	if(vendor->isBazaarTerminal()) {
		return;
	}

	Locker locker(_this.get());

	Reference<TerminalItemList*> vendorItems = vendorItemsForSale.get(vendor->getObjectID());

	if(vendorItems != NULL) {
		for(int i = 0; i < vendorItems->size(); ++i) {
			ManagedReference<AuctionItem*> item = vendorItems->get(i);
			if(item != NULL)
				allItems.drop(item->getAuctionedItemObjectID());
		}
	}

	vendorItemsForSale.dropTerminalListing(vendor);
}

void AuctionsMapImplementation::sendVendorUpdateMail(SceneObject* vendor, bool isEmpty) {
	//Send the mail to the vendor owner
	if (vendor == NULL || !vendor->isVendor())
		return;

	VendorDataComponent* vendorData = NULL;
	DataObjectComponentReference* data = vendor->getDataObjectComponent();
	if(data != NULL && data->get() != NULL && data->get()->isVendorData())
		vendorData = cast<VendorDataComponent*>(data->get());

	if(vendorData == NULL)
		return;

	ManagedReference<ChatManager*> cman = vendor->getZoneServer()->getChatManager();
	ManagedReference<CreatureObject*> owner = cast<CreatureObject*>(vendor->getZoneServer()->getObject(vendorData->getOwnerId()));

	String sender = vendor->getDisplayedName();
	UnicodeString subject("@auction:vendor_status_subject");

	if (cman == NULL || owner == NULL)
		return;

	if (isEmpty) {
		StringIdChatParameter body("@auction:vendor_status_empty");
		body.setTO(vendor->getDisplayedName());
		cman->sendMail(sender, subject, body, owner->getFirstName());
		vendorData->setEmpty();
		VendorManager::instance()->handleUnregisterVendor(owner, cast<TangibleObject*>(vendor));
	} else {
		StringIdChatParameter body("@auction:vendor_status_normal");
		body.setTO(vendor->getDisplayedName());
		cman->sendMail(sender, subject, body, owner->getFirstName());
	}

}

void AuctionsMapImplementation::updateUID(SceneObject* vendor, const String& oldUID, const String& newUID) {
	Locker locker(_this.get());
	
	if (vendor == NULL) {
		logger.error("NULL vendor while updating UID  Vendor Is Bazaar: " + String::valueOf(vendor->isBazaarTerminal()));
		return;
	}

	if (vendor->getZone() == NULL) {
		logger.error("NULL zone while updating UID  Vendor Is Bazaar: " + String::valueOf(vendor->isBazaarTerminal()));
		return;
	}

	String planet = vendor->getZone()->getZoneName();

	String region = "@planet_n:" + vendor->getZone()->getZoneName();
	ManagedReference<CityRegion*> cityRegion = vendor->getCityRegion();
	if(cityRegion != NULL)
		region = cityRegion->getRegionName();

	if(vendor->isVendor())
		vendorItemsForSale.updateTerminalUID(planet, region, vendor, newUID);
	else
		bazaarItemsForSale.updateTerminalUID(planet, region, vendor, newUID);
}

void AuctionsMapImplementation::updateVendorSearch(SceneObject* vendor, bool enabled) {
	Locker locker(_this.get());
	
	if (vendor == NULL)
		return;

	vendorItemsForSale.updateTerminalSearch(vendor, enabled);
}

int AuctionsMapImplementation::getCommodityCount(CreatureObject* player) {

	Locker locker(&commoditiesLimit);

	if(!commoditiesLimit.contains(player->getObjectID()))
		return 0;

	Vector<ManagedWeakReference<AuctionItem*> >* items = &commoditiesLimit.get(player->getObjectID());

	for(int i = items->size() -1; i >= 0; --i) {
		ManagedReference<AuctionItem*> item = items->get(i);
		if(item == NULL || item->getOwnerID() != player->getObjectID() ||
				item->getStatus() == AuctionItem::RETRIEVED) {
			items->remove(i);
		}
	}

	return items->size();
}

void AuctionsMapImplementation::addToCommodityLimit(AuctionItem* item) {

	Locker locker(&commoditiesLimit);

	if(!commoditiesLimit.contains(item->getOwnerID())) {
		Vector<ManagedWeakReference<AuctionItem*> > newItems;
		commoditiesLimit.put(item->getOwnerID(), newItems);
	}

	Vector<ManagedWeakReference<AuctionItem*> >* items = &commoditiesLimit.get(item->getOwnerID());
	if(items != NULL)
		items->add(item);

}

void AuctionsMapImplementation::removeFromCommodityLimit(AuctionItem* item) {

	Locker locker(&commoditiesLimit);

	if(!commoditiesLimit.contains(item->getOwnerID()))
		return;

	Vector<ManagedWeakReference<AuctionItem*> >* items = &commoditiesLimit.get(item->getOwnerID());
	if(items != NULL)
		items->removeElement(item);

	if(items->isEmpty())
		commoditiesLimit.drop(item->getOwnerID());
}

