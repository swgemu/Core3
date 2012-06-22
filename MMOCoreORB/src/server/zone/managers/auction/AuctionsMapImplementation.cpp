/*
 * AuctionsMap.cpp
 *
 *  Created on: 6/3/2012
 *      Author: kyle
 */


#include "AuctionsMap.h"
#include "server/zone/objects/auction/AuctionItem.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/ZoneServer.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/chat/ChatManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/packets/auction/ItemSoldMessage.h"

int AuctionsMapImplementation::addItem(SceneObject* vendor, String& uid, AuctionItem* item) {

	if(vendor->isBazaarTerminal())
		return addBazaarItem(uid, item);

	return addVendorItem(vendor, uid, item);
}

int AuctionsMapImplementation::addVendorItem(SceneObject* vendor, String& uid, AuctionItem* item) {

	VuidString vuid(uid);

	if(!vendorItemsForSale.contains(vuid)) {
		SortedVector<ManagedReference<AuctionItem*> > items;
		items.setNoDuplicateInsertPlan();
		vendorItemsForSale.put(vuid, items);
	}

	SortedVector<ManagedReference<AuctionItem*> >* vendorItems = &vendorItemsForSale.get(vuid);

	if(vendorItems == NULL)
		return ItemSoldMessage::VENDORNOTWORKING;

	Locker _locker(_this.get());

	if(vendorItems->contains(item))
		return ItemSoldMessage::ALREADYFORSALE;

	vendorItems->put(item);
	allItems.put(item->getAuctionedItemObjectID(), item);
	item->setVendorUID(vuid);

	if(vendorItems->size() == 1)
		sendVendorUpdateMail(vendor, false);

	return ItemSoldMessage::SUCCESS;
}

int AuctionsMapImplementation::addBazaarItem(String& uid, AuctionItem* item) {

	VuidString vuid(uid);

	if(!bazaarItemsForSale.contains(vuid)) {
		SortedVector<ManagedReference<AuctionItem*> > items;
		items.setNoDuplicateInsertPlan();
		bazaarItemsForSale.put(vuid, items);
	}

	SortedVector<ManagedReference<AuctionItem*> >* bazaarItems = &bazaarItemsForSale.get(vuid);

	if(bazaarItems == NULL)
		return ItemSoldMessage::VENDORNOTWORKING;

	Locker _locker(_this.get());

	if(bazaarItems->contains(item))
		return ItemSoldMessage::ALREADYFORSALE;

	bazaarItems->put(item);
	allItems.put(item->getAuctionedItemObjectID(), item);
	item->setVendorUID(vuid);

	int count = bazaarCount.get(item->getOwnerID()) + 1;
	bazaarCount.put(item->getOwnerID(), count);

	return ItemSoldMessage::SUCCESS;
}

int AuctionsMapImplementation::removeItem(SceneObject* vendor, String& uid, AuctionItem* item) {

	if(vendor->isBazaarTerminal())
		return removeBazaarItem(uid, item);

	return removeVendorItem(vendor, uid, item);
}

int AuctionsMapImplementation::removeVendorItem(SceneObject* vendor, String& uid, AuctionItem* item) {

	if(!vendorItemsForSale.contains(uid)) {
		return ItemSoldMessage::VENDORNOTWORKING;
	}

	SortedVector<ManagedReference<AuctionItem*> >* vendorItems = &vendorItemsForSale.get(uid);

	Locker _locker(_this.get());
	if(vendorItems->drop(item)) {
		allItems.drop(item->getAuctionedItemObjectID());

		if(vendorItems->size() == 0)
			sendVendorUpdateMail(vendor, true);

		return ItemSoldMessage::SUCCESS;
	}

	logger.error("unable to remove vendor item");
	return ItemSoldMessage::UNKNOWNERROR;
}

int AuctionsMapImplementation::removeBazaarItem(String& uid, AuctionItem* item) {

	if(!bazaarItemsForSale.contains(uid)) {
		return ItemSoldMessage::VENDORNOTWORKING;
	}

	SortedVector<ManagedReference<AuctionItem*> >* bazaarItems = &bazaarItemsForSale.get(uid);

	Locker _locker(_this.get());
	if(bazaarItems->drop(item)) {
		allItems.drop(item->getAuctionedItemObjectID());

		int count = bazaarCount.get(item->getOwnerID()) - 1;

		if(count <= 0)
			bazaarCount.drop(item->getOwnerID());
		else
			bazaarCount.put(item->getOwnerID(), count);

		return ItemSoldMessage::SUCCESS;
	}

	logger.error("unable to remove bazaar item");
	return ItemSoldMessage::UNKNOWNERROR;
}

SortedVector<ManagedReference<AuctionItem* > > AuctionsMapImplementation::getVendorItems(SceneObject* vendor, const String& vuid, const String& search) {
	int lowerbound = 0;
	int upperbound = vendorItemsForSale.size() - 1;

	VuidString searchTerm(search);

	if(!searchTerm.isEmpty()) {
		lowerbound = vendorItemsForSale.lowerBound(searchTerm);
		upperbound = vendorItemsForSale.upperBound(searchTerm);
	}

	SortedVector<ManagedReference<AuctionItem* > > results;

	if(lowerbound != -1 && upperbound == -1)
		upperbound = lowerbound;

	if(lowerbound == -1 || upperbound == -1 || vendorItemsForSale.isEmpty())
		return results;

	VendorDataComponent* vendorData = NULL;
	DataObjectComponentReference* data = NULL;

	if(vendor != NULL) {
		data = vendor->getDataObjectComponent();
		if(data != NULL && data->get() != NULL && data->get()->isVendorData())
			vendorData = cast<VendorDataComponent*>(data->get());
	}

	for(int i = lowerbound; i <= upperbound; ++i) {

		SortedVector<ManagedReference<AuctionItem* > >* items = &vendorItemsForSale.get(i);
		SceneObject* thisVendor = NULL;
		VendorDataComponent* thisVendorData = NULL;

		for(int j = 0; j < items->size(); ++j) {
			ManagedReference<AuctionItem*> item = items->get(j);
			if(vendor == NULL) {
				results.add(item);
				continue;
			}

			if(thisVendor == NULL) {
				thisVendor = vendor->getZoneServer()->getObject(item->getVendorID());

				if(thisVendor != NULL && thisVendor->isVendor()) {
					DataObjectComponentReference* thisData = thisVendor->getDataObjectComponent();
					if(thisData != NULL && thisData->get() != NULL && thisData->get()->isVendorData())
						thisVendorData = cast<VendorDataComponent*>(thisData->get());
				}
			}

			if(thisVendorData == NULL || thisVendor == NULL) {
				logger.error("NULL vendor data");
				continue;
			}

			if(thisVendor == vendor || thisVendorData->isVendorSearchEnabled())
				results.add(item);
		}
	}

	return results;
}

SortedVector<ManagedReference<AuctionItem* > > AuctionsMapImplementation::getBazaarItems(SceneObject* vendor, const String& vuid, const String& search) {

	int lowerbound = 0;
	int upperbound = bazaarItemsForSale.size() - 1;

	VuidString searchTerm(search);

	if(!searchTerm.isEmpty()) {
		lowerbound = bazaarItemsForSale.lowerBound(searchTerm);
		upperbound = bazaarItemsForSale.upperBound(searchTerm);
	}
	//System::out << "\nSearch: " << searchTerm << " LowerBound: " << lowerbound << " Upperbound: " << upperbound << "\n" << endl;

	SortedVector<ManagedReference<AuctionItem* > > results;

	//System::out << "Vendors\n" << endl;
	//for(int i = 0; i < bazaarItemsForSale.size(); ++i)
	//	System::out << "  " << i << ". "  << bazaarItemsForSale.elementAt(i).getKey() << "   " << bazaarItemsForSale.elementAt(i).getKey().compareTo(search) << "\n" << endl;


	if(lowerbound != -1 && upperbound == -1)
		upperbound = lowerbound;

	if(lowerbound == -1 || upperbound == -1 || bazaarItemsForSale.isEmpty())
		return results;

	//System::out << "\nVendor Match\n " << endl;
	for(int i = lowerbound; i <= upperbound; ++i) {

		//System::out << i << ". " << bazaarItemsForSale.elementAt(i).getKey() << "\n" << endl;

		SortedVector<ManagedReference<AuctionItem* > >* items = &bazaarItemsForSale.get(i);

		for(int j = 0; j < items->size(); ++j) {
			ManagedReference<AuctionItem*> item = items->get(j);
			if(item != NULL)
				results.add(item);
		}
	}
	//System::out << "\n" << endl;

	return results;
}

int AuctionsMapImplementation::getVendorItemCount(const String& uid) {

	if(!vendorItemsForSale.contains(uid))
		return 0;

	return vendorItemsForSale.get(uid).size();
}

void AuctionsMapImplementation::deleteVendorItems(const String& uid) {

	if(!vendorItemsForSale.contains(uid))
		return;

	SortedVector<ManagedReference<AuctionItem* > >* items = &vendorItemsForSale.get(uid);

	Locker locker(_this.get());
	while(items->size() > 0) {
		ManagedReference<AuctionItem* > item = items->remove(0);

		ObjectManager::instance()->destroyObjectFromDatabase(item->_getObjectID());
	}

	vendorItemsForSale.drop(uid);
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
		vendorData->setEmpty(true);
		VendorManager::instance()->handleUnregisterVendor(owner, cast<TangibleObject*>(vendor));
	} else {
		StringIdChatParameter body("@auction:vendor_status_normal");
		body.setTO(vendor->getDisplayedName());
		cman->sendMail(sender, subject, body, owner->getFirstName());
		vendorData->setEmpty(false);
	}

}

void AuctionsMapImplementation::updateUID(SceneObject* vendor, const String& oldUID, const String& newUID) {

	if(vendorItemsForSale.contains(oldUID)) {
		Locker locker(_this.get());
		SortedVector<ManagedReference<AuctionItem* > > itemList = vendorItemsForSale.get(oldUID);
		vendorItemsForSale.drop(oldUID);

		String planetStr = vendor->getZone()->getZoneName();
		ManagedReference<CityRegion*> cityRegion = vendor->getCityRegion();
		String region = "";

		if (cityRegion != NULL)
			region = cityRegion->getRegionName();

		for(int i = 0; i < itemList.size(); ++i) {
			ManagedReference<AuctionItem* > item = itemList.get(i);
			if(item == NULL)
				continue;

			item->setPlanet(planetStr);
			item->setRegion(region);
			item->setVendorUID(newUID);
		}

		vendorItemsForSale.put(newUID, itemList);
	}

	if(bazaarItemsForSale.contains(oldUID)) {
		Locker locker(_this.get());
		SortedVector<ManagedReference<AuctionItem* > > itemList = bazaarItemsForSale.get(oldUID);
		bazaarItemsForSale.drop(oldUID);

		String planetStr = vendor->getZone()->getZoneName();
		ManagedReference<CityRegion*> cityRegion = vendor->getCityRegion();
		String region = planetStr;

		if (cityRegion != NULL)
			region = cityRegion->getRegionName();

		for(int i = 0; i < itemList.size(); ++i) {
			ManagedReference<AuctionItem* > item = itemList.get(i);
			if(item == NULL)
				continue;

			item->setPlanet(planetStr);
			item->setRegion(region);
			item->setVendorUID(newUID);
		}

		bazaarItemsForSale.put(newUID, itemList);
	}
}

//bool AuctionsMapImplementation::addItem(String& vendorUID, AuctionItem* item) {
//
//	/// Send mail every 5 days
//	if (lastTimeVendorEmpty - time(0) > 60 * 60 * 24 * 5 * mailNum) {
//		sendVendorUpdateMail(true);
//		mailNum++;
//	}
//
//	/// Destroy after 30 days
//	if (lastTimeVendorEmpty - time(0) > 60 * 60 * 24 * 30) {
//		sendVendorDestroyMail();
//		vendor->destroyObjectFromWorld(true);
//		vendor->destroyObjectFromDatabase(true);
//		return;
//	}
//}
//

//
//void AuctionsMapImplementation::sendVendorDestroyMail() {
//
//	ChatManager* cman = vendor->getZoneServer()->getChatManager();
//	ManagedReference<CreatureObject*> owner = cast<CreatureObject*>(vendor->getZoneServer()->getObject(ownerId));
//
//	String sender = vendor->getDisplayedName();
//	UnicodeString subject("@auction:vendor_status_subject");
//
//	if (cman == NULL || owner == NULL)
//		return;
//
//	Locker playerLocker(owner);
//
//	StringIdChatParameter body("@auction:vendor_status_deleted");
//	body.setTO(vendor->getDisplayedName());
//	cman->sendMail(sender, subject, body, owner->getFirstName());
//
//}
//
//
//inline void addVendorItem(AuctionItem* item) {
//	if (vendorItems.size() == 0 && !vendor->isBazaarTerminal()) {
//		sendVendorUpdateMail(false);
//		mailNum = 1;
//		lastTimeVendorEmpty = 0;
//	}
//
//	vendorItems.put(item->getAuctionedItemObjectID(), item);
//}
//
//inline bool containsVendorItem(uint64 itemID) {
//	return vendorItems.contains(itemID);
//}
//
//inline void dropVendorItem(uint64 itemID) {
//	vendorItems.drop(itemID);
//
//	if (vendorItems.size() == 0 && !vendor->isBazaarTerminal())
//		sendVendorUpdateMail(true);
//}
//
//inline void dropVendorItem(AuctionItem* item) {
//	vendorItems.drop(item->getAuctionedItemObjectID());
//
//	if (vendorItems.size() == 0 && !vendor->isBazaarTerminal())
//		sendVendorUpdateMail(true);
//}
