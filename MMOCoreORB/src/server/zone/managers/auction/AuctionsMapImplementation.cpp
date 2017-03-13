/*
 * AuctionsMap.cpp
 *
 *  Created on: 6/3/2012
 *      Author: kyle
 */

#include "server/zone/managers/auction/AuctionsMap.h"
#include "server/zone/objects/auction/AuctionItem.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/packets/auction/ItemSoldMessage.h"

int AuctionsMapImplementation::addItem(CreatureObject* player, SceneObject* vendor, AuctionItem* item) {
	if(vendor == NULL || vendor->getZone() == NULL)
		return ItemSoldMessage::VENDORNOTWORKING;

	String planet = vendor->getZone()->getZoneName();

	String region = "@planet_n:" + vendor->getZone()->getZoneName();
	ManagedReference<CityRegion*> cityRegion = vendor->getCityRegion().get();
	if(cityRegion != NULL)
		region = cityRegion->getRegionName();

	if(vendor->isBazaarTerminal())
		return addBazaarItem(player, planet, region, vendor, item);

	return addVendorItem(player, planet, region, vendor, item);
}

int AuctionsMapImplementation::addVendorItem(CreatureObject* player, const String& planet, const String& region, SceneObject* vendor, AuctionItem* item) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

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

	return ItemSoldMessage::SUCCESS;
}

int AuctionsMapImplementation::addBazaarItem(CreatureObject* player, const String& planet, const String& region, SceneObject* vendor, AuctionItem* item) {
	Locker locker(_this.getReferenceUnsafeStaticCast());

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

	Locker locker(_this.getReferenceUnsafeStaticCast());

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
	Locker locker(_this.getReferenceUnsafeStaticCast());
		
	Reference<TerminalItemList*> vendorItems = vendorItemsForSale.get(vendor->getObjectID());

	if(vendorItems == NULL)
		return;

	//Locker vlocker(vendorItems);

	if(vendorItems->drop(item))
		return;

	logger.error("unable to remove vendor item");
}

void AuctionsMapImplementation::removeBazaarItem(SceneObject* vendor,  AuctionItem* item) {
	Locker locker(_this.getReferenceUnsafeStaticCast());
		
	Reference<TerminalItemList*> bazaarItems = bazaarItemsForSale.get(vendor->getObjectID());

	if(bazaarItems == NULL)
		return;

	//Locker blocker(bazaarItems);

	if(!bazaarItems->drop(item))
		logger.error("unable to remove bazaar item");

}

TerminalListVector AuctionsMapImplementation::getVendorTerminalData(const String& planet, const String& region, SceneObject* vendor) {
	Locker locker(_this.getReferenceUnsafeStaticCast());
	
	return vendorItemsForSale.getTerminalData(planet, region, vendor);
}

TerminalListVector AuctionsMapImplementation::getBazaarTerminalData(const String& planet, const String& region, SceneObject* vendor) {
	Locker locker(_this.getReferenceUnsafeStaticCast());
	
	return bazaarItemsForSale.getTerminalData(planet, region, vendor);
}
int AuctionsMapImplementation::getPlayerItemCount(CreatureObject* player) {
	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == NULL)
		return 0;

	SortedVector<unsigned long long>* ownedVendors = ghost->getOwnedVendors();
	int total = 0;

	for (int i = 0; i < ownedVendors->size(); i++) {
		ManagedReference<SceneObject*> vendor = player->getZoneServer()->getObject(ownedVendors->elementAt(i));

		total += getVendorItemCount(vendor);
	}

	return total;
}

int AuctionsMapImplementation::getVendorItemCount(SceneObject* vendor, bool forSaleOnly) {
	Locker locker(_this.getReferenceUnsafeStaticCast());
	
	if(vendor == NULL) {
		logger.error("null vendor in AuctionsMapImplementation::getVendorItemCount");
		return 0;
	}

	Reference<TerminalItemList*> vendorItems = vendorItemsForSale.get(vendor->getObjectID());

	if(vendorItems == NULL)
		return 0;

	int size = 0;

	ReadLocker rlocker(vendorItems);

	for (int i = 0; i < vendorItems->size(); ++i) {
		AuctionItem* item = vendorItems->get(i);
		if (item == NULL)
			continue;

		if (forSaleOnly && item->getStatus() != AuctionItem::FORSALE)
			continue;

		int itemSize = item->getSize();

		if (itemSize > 50)
			size += 50;
		else if (itemSize > 0)
			size += itemSize;
		else
			size++;
	}

	return size;
}

void AuctionsMapImplementation::deleteTerminalItems(SceneObject* vendor) {
	if(vendor->isBazaarTerminal()) {
		return;
	}

	Locker locker(_this.getReferenceUnsafeStaticCast());

	Reference<TerminalItemList*> vendorItems = vendorItemsForSale.get(vendor->getObjectID());
	ZoneServer* zserv = vendor->getZoneServer();

	if(vendorItems != NULL) {
		ReadLocker rlocker(vendorItems);

		for(int i = 0; i < vendorItems->size(); ++i) {
			ManagedReference<AuctionItem*> item = vendorItems->get(i);

			if(item != NULL) {
				uint64 oid = item->getAuctionedItemObjectID();

				allItems.drop(oid);
				ObjectManager::instance()->destroyObjectFromDatabase(item->_getObjectID());

				ManagedReference<SceneObject*> sceno = zserv->getObject(oid);

				if (sceno != NULL) {
					Core::getTaskManager()->executeTask([=] () {
						Locker locker(sceno);
						sceno->destroyObjectFromDatabase(true);
					}, "DeleteTerminalItemLambda");
				}
			}
		}
	}

	vendorItemsForSale.dropTerminalListing(vendor);
}

void AuctionsMapImplementation::updateUID(SceneObject* vendor, const String& oldUID, const String& newUID) {
	Locker locker(_this.getReferenceUnsafeStaticCast());
	
	if (vendor == NULL) {
		logger.error("NULL vendor while updating UID");
		return;
	}

	Zone* zone = vendor->getZone();

	if (zone == NULL) {
		logger.error("NULL zone while updating UID  Vendor Is Bazaar: " + String::valueOf(vendor->isBazaarTerminal()));
		return;
	}

	String planet = zone->getZoneName();

	String region = "@planet_n:" + planet;
	ManagedReference<CityRegion*> cityRegion = vendor->getCityRegion().get();
	if(cityRegion != NULL)
		region = cityRegion->getRegionName();

	if(vendor->isVendor())
		vendorItemsForSale.updateTerminalUID(planet, region, vendor, newUID);
	else
		bazaarItemsForSale.updateTerminalUID(planet, region, vendor, newUID);
}

void AuctionsMapImplementation::updateVendorSearch(SceneObject* vendor, bool enabled) {
	Locker locker(_this.getReferenceUnsafeStaticCast());
	
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

