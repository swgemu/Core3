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
#include "server/zone/packets/auction/ItemSoldMessage.h"

int AuctionsMapImplementation::addItem(SceneObject* vendor, String& uid, AuctionItem* item) {

	if(vendor->isBazaarTerminal())
		return addBazaarItem(uid, item);

	return addVendorItem(vendor, uid, item);
}

int AuctionsMapImplementation::addVendorItem(SceneObject* vendor, String& uid, AuctionItem* item) {

	if(!vendorItemsForSale.contains(uid)) {
		SortedVector<ManagedReference<AuctionItem*> >* items = new SortedVector<ManagedReference<AuctionItem*> >();
		items->setNoDuplicateInsertPlan();
		vendorItemsForSale.put(uid, items);
System::out << uid << "\n" << endl;
	}

	SortedVector<ManagedReference<AuctionItem*> >* vendorItems = vendorItemsForSale.get(uid);

	if(vendorItems == NULL)
		return ItemSoldMessage::VENDORNOTWORKING;

	Locker _locker(_this.get());

	if(vendorItems->contains(item))
		return ItemSoldMessage::ALREADYFORSALE;

	vendorItems->put(item);
	allItems.put(item->getAuctionedItemObjectID(), item);

	if(vendorItems->size() == 1)
		sendVendorUpdateMail(vendor, false);

	return ItemSoldMessage::SUCCESS;
}

int AuctionsMapImplementation::addBazaarItem(String& uid, AuctionItem* item) {

	if(!bazaarItemsForSale.contains(uid)) {
		SortedVector<ManagedReference<AuctionItem*> >* items = new SortedVector<ManagedReference<AuctionItem*> >();
		items->setNoDuplicateInsertPlan();
		bazaarItemsForSale.put(uid, items);
	}
System::out << uid << "\n" << endl;
	SortedVector<ManagedReference<AuctionItem*> >* bazaarItems = bazaarItemsForSale.get(uid);

	if(bazaarItems == NULL)
		return ItemSoldMessage::VENDORNOTWORKING;

	Locker _locker(_this.get());

	if(bazaarItems->contains(item))
		return ItemSoldMessage::ALREADYFORSALE;

	bazaarItems->put(item);
	allItems.put(item->getAuctionedItemObjectID(), item);

	return ItemSoldMessage::SUCCESS;
}

SortedVector<ManagedReference<AuctionItem* > > AuctionsMapImplementation::getVendorItems(const String& search) {
	int lowerbound = 0;
	int upperbound = vendorItemsForSale.size() - 1;

	if(!search.isEmpty()) {
		lowerbound = vendorItemsForSale.lowerBound(search);
		upperbound = vendorItemsForSale.upperBound(search);
	}

	SortedVector<ManagedReference<AuctionItem* > > results;

	if(lowerbound == -1 || upperbound == -1)
		return results;

	for(int i = lowerbound; i <= upperbound; ++i) {

		SortedVector<ManagedReference<AuctionItem* > >* items = vendorItemsForSale.get(i);

		for(int j = 0; j < items->size(); ++j) {
			ManagedReference<AuctionItem*> item = items->get(j);
			if(item != NULL)
				results.add(item);
		}
	}

	return results;
}

SortedVector<ManagedReference<AuctionItem* > > AuctionsMapImplementation::getBazaarItems(const String& search) {

	int lowerbound = 0;
	int upperbound = bazaarItemsForSale.size() - 1;

	if(!search.isEmpty()) {
		lowerbound = bazaarItemsForSale.lowerBound(search);
		upperbound = bazaarItemsForSale.upperBound(search);
	}
System::out << "Search: " << search << "\n" << endl;
	SortedVector<ManagedReference<AuctionItem* > > results;

	if(lowerbound == -1 || upperbound == -1)
		return results;

	for(int i = lowerbound; i <= upperbound; ++i) {

		SortedVector<ManagedReference<AuctionItem* > >* items = bazaarItemsForSale.get(i);

		for(int j = 0; j < items->size(); ++j) {
			ManagedReference<AuctionItem*> item = items->get(j);
			if(item != NULL)
				results.add(item);
		}
	}

	return results;
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
	} else {
		StringIdChatParameter body("@auction:vendor_status_normal");
		body.setTO(vendor->getDisplayedName());
		cman->sendMail(sender, subject, body, owner->getFirstName());
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
