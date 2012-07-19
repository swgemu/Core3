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

	Locker locker(_this.get());
	Locker vlocker(vendorItems);

	int result = vendorItems->put(item);

	if(result == -1)
		return ItemSoldMessage::UNKNOWNERROR;

	allItems.put(item->getAuctionedItemObjectID(), item);

	if(vendorItems->size() == 1 && player != NULL)
		sendVendorUpdateMail(vendor, false);

	return ItemSoldMessage::SUCCESS;
}

int AuctionsMapImplementation::addBazaarItem(CreatureObject* player, const String& planet, const String& region, SceneObject* vendor, AuctionItem* item) {

	if(allItems.contains(item->getAuctionedItemObjectID()))
		return ItemSoldMessage::ALREADYFORSALE;

	if(!bazaarItemsForSale.contains(vendor->getObjectID()) && !bazaarItemsForSale.createTerminalListing(planet, region, vendor))
		return ItemSoldMessage::VENDORNOTWORKING;

	Reference<TerminalItemList*> bazaarItems = bazaarItemsForSale.get(vendor->getObjectID());

	if(bazaarItems == NULL)
		return ItemSoldMessage::INVALIDAUCTIONER;

	Locker locker(_this.get());
	Locker blocker(bazaarItems);
	int result = bazaarItems->put(item);

	if(result == -1)
		return ItemSoldMessage::UNKNOWNERROR;

	allItems.put(item->getAuctionedItemObjectID(), item);
//	int count = bazaarCount.get(item->getOwnerID()) + 1;
//	bazaarCount.put(item->getOwnerID(), count);

	return ItemSoldMessage::SUCCESS;
}

int AuctionsMapImplementation::removeItem(SceneObject* vendor, AuctionItem* item) {

	if(vendor == NULL)
		return ItemSoldMessage::VENDORNOTWORKING;

	if(vendor->isBazaarTerminal())
		return removeBazaarItem(vendor, item);

	return removeVendorItem(vendor, item);
}

int AuctionsMapImplementation::removeVendorItem(SceneObject* vendor, AuctionItem* item) {

	Reference<TerminalItemList*> vendorItems = vendorItemsForSale.get(vendor->getObjectID());

	if(vendorItems == NULL)
		return ItemSoldMessage::VENDORNOTWORKING;

	if(!vendorItems->contains(item))
		return ItemSoldMessage::INVALIDITEM;

	Locker locker(_this.get());
	Locker vlocker(vendorItems);

	if(vendorItems->removeElement(item)) {

		allItems.drop(item->getAuctionedItemObjectID());

		if(vendorItems->size() == 0)
			sendVendorUpdateMail(vendor, true);

		return ItemSoldMessage::SUCCESS;
	}

	logger.error("unable to remove vendor item");
	return ItemSoldMessage::UNKNOWNERROR;
}

int AuctionsMapImplementation::removeBazaarItem(SceneObject* vendor,  AuctionItem* item) {

	Reference<TerminalItemList*> bazaarItems = bazaarItemsForSale.get(vendor->getObjectID());

	if(bazaarItems == NULL)
		return ItemSoldMessage::VENDORNOTWORKING;

	if(!bazaarItems->contains(item))
		return ItemSoldMessage::INVALIDITEM;

	Locker locker(_this.get());
	Locker blocker(bazaarItems);

	if(bazaarItems->removeElement(item)) {

		allItems.drop(item->getAuctionedItemObjectID());

		return ItemSoldMessage::SUCCESS;
	}

	logger.error("unable to remove bazaar item");
	return ItemSoldMessage::UNKNOWNERROR;
}

TerminalListVector AuctionsMapImplementation::getVendorTerminalData(const String& planet, const String& region, SceneObject* vendor) {
	return vendorItemsForSale.getTerminalData(planet, region, vendor);
}

TerminalListVector AuctionsMapImplementation::getBazaarTerminalData(const String& planet, const String& region, SceneObject* vendor) {
	return bazaarItemsForSale.getTerminalData(planet, region, vendor);
}

int AuctionsMapImplementation::getVendorItemCount(SceneObject* vendor) {

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

	if(vendor->isBazaarTerminal()) {
		logger.error("null zone in AuctionsMapImplementation::deleteTerminalItems");
		return;
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

	ChatManager* cman = vendor->getZoneServer()->getChatManager();
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

	if (vendor == NULL)
		return;

	vendorItemsForSale.updateTerminalSearch(vendor, enabled);
}
