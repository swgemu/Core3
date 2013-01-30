/*
 * AuctionManagerImplementation.cpp
 *
 *  Created on: 13/03/2010
 *      Author: victor
 */

#include "AuctionManager.h"
#include "AuctionsMap.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/auction/AuctionItem.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/packets/auction/ItemSoldMessage.h"
#include "server/zone/packets/auction/CancelLiveAuctionResponseMessage.h"
#include "server/zone/packets/auction/AuctionQueryHeadersResponseMessage.h"
#include "server/zone/packets/auction/RetrieveAuctionItemResponseMessage.h"
#include "server/zone/packets/auction/BidAuctionResponseMessage.h"
#include "server/zone/packets/auction/IsVendorOwnerMessageCallback.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/chat/ChatManager.h"
#include "CheckAuctionsTask.h"
#include "ExpireAuctionTask.h"
#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"
#include "server/zone/objects/tangible/components/vendor/AuctionTerminalDataComponent.h"

void AuctionManagerImplementation::initialize() {

	Locker locker(_this.get());

	auctionMap = new AuctionsMap();

	ObjectDatabase* auctionDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("auctionitems", true);
	ObjectDatabaseManager::instance()->commitLocalTransaction();

	ObjectDatabaseIterator iterator(auctionDatabase);

	uint64 objectID = 0;

	Vector<ManagedReference<AuctionItem*> > orphanedBazaarItems;
	ManagedReference<SceneObject*> defaultBazaar = NULL;

	while (iterator.getNextKey(objectID)) {
		ManagedReference<AuctionItem*> auctionItem = cast<AuctionItem*>(Core::getObjectBroker()->lookUp(objectID));
		ObjectDatabaseManager::instance()->commitLocalTransaction();

		if(auctionItem == NULL) {
			error("unable to load auction item: " + String::valueOf(objectID));
			continue;
		}

		ManagedReference<SceneObject*> vendor = cast<SceneObject*>(zoneServer->getObject(auctionItem->getVendorID()));

		if(vendor == NULL || vendor->getZone() == NULL) {
			if(auctionItem->isOnBazaar()) {
				orphanedBazaarItems.add(auctionItem);
				continue;
			}

			if(vendor != NULL) {
				vendor->destroyObjectFromWorld(true);
				vendor->destroyObjectFromDatabase();
			}

			ObjectManager::instance()->destroyObjectFromDatabase(auctionItem->_getObjectID());
			warning("Auction Item's vendor is gone, deleting auction item: " + String::valueOf(auctionItem->_getObjectID()));
			continue;
		}

		if(vendor->isBazaarTerminal() && defaultBazaar == NULL)
			defaultBazaar = vendor;

		auctionMap->addItem(NULL, vendor, auctionItem);

		if(auctionItem->isOnBazaar() || auctionItem->getStatus() == AuctionItem::OFFERED)
			auctionMap->addToCommodityLimit(auctionItem);

		if(auctionItem->isAuction()) {
			Reference<Task*> newTask = new ExpireAuctionTask(_this.get(), auctionItem);
			newTask->schedule((auctionItem->getExpireTime() - time(0)) * 1000);

			Locker locker(&auctionEvents);
			auctionEvents.put(auctionItem->getAuctionedItemObjectID(), newTask);
		}
	}

	/// This is in case a bazaar is removed, it could move and item
	/// to a difference city, but at least it doesn't poof
	if(defaultBazaar != NULL) {

		for(int i = 0; i < orphanedBazaarItems.size(); ++i) {
			ManagedReference<AuctionItem*> auctionItem = orphanedBazaarItems.get(i);

			String vuid = getVendorUID(defaultBazaar);
			auctionMap->addItem(NULL, defaultBazaar, auctionItem);
			auctionItem->setVendorID(defaultBazaar->getObjectID());

			if(auctionItem->isAuction()) {
				Reference<Task*> newTask = new ExpireAuctionTask(_this.get(), auctionItem);
				newTask->schedule((auctionItem->getExpireTime() - time(0)) * 1000);

				Locker locker(&auctionEvents);
				auctionEvents.put(auctionItem->getAuctionedItemObjectID(), newTask);
			}
		}
	}

	for(int i = 0; i < pendingUIDUpdates.size(); ++i) {
		ManagedReference<SceneObject*> vendor = pendingUIDUpdates.elementAt(i).getKey();
		String uid = pendingUIDUpdates.get(vendor);
		String oldUID = pendingOldUIDUpdates.get(vendor);

		auctionMap->updateUID(vendor, oldUID, uid);
	}

	locker.release();

	checkAuctions();
	checkVendorItems();

	info("loaded auctionsMap of size: " + String::valueOf(auctionMap->getTotalItemCount()), true);

	marketEnabled = true;
}

void AuctionManagerImplementation::checkVendorItems() {

	TerminalListVector items = auctionMap->getVendorTerminalData("", "", 0);

	info("Checking " + String::valueOf(items.size()) + " vendor terminals", true);

	doAuctionMaint(&items);
}

void AuctionManagerImplementation::checkAuctions() {

	CheckAuctionsTask* task = new CheckAuctionsTask(_this.get());
	task->schedule(CHECKEVERY * 60 * 1000);

	TerminalListVector items = auctionMap->getBazaarTerminalData("", "", 0);

	info("Checking " + String::valueOf(items.size()) + " bazaar terminals", true);

	doAuctionMaint(&items);
}

void AuctionManagerImplementation::doAuctionMaint(TerminalListVector* items) {

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;

	for (int i = 0; i < items->size(); ++i) {
		Reference<TerminalItemList*> list = items->get(i);
		if (list == NULL)
			continue;

		for (int j = 0; j < list->size(); ++j) {
			ManagedReference<AuctionItem*> item = list->get(j);
			if (item == NULL)
				continue;

			ManagedReference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());
			uint64 objectId = item->getAuctionedItemObjectID();

			if(vendor == NULL || vendor->getZone() == NULL) {
				auctionMap->deleteItem(vendor, item);
				continue;
			}

			String vuid = getVendorUID(vendor);

			Locker locker(item);

			if (item->getExpireTime() <= currentTime) {
				if (item->getStatus() == AuctionItem::EXPIRED) {
					expireSale(item);
				}
			}

			if (item->getStatus() == AuctionItem::RETRIEVED) {

				auctionMap->deleteItem(vendor, item);

			}
		}
	}
}

void AuctionManagerImplementation::addSaleItem(CreatureObject* player, uint64 objectid, SceneObject* vendor, const UnicodeString& description, int price, uint32 duration, bool auction, bool premium) {

	if (vendor == NULL || (!vendor->isVendor() && !vendor->isBazaarTerminal())) {
		error("terminal is not a valid vendor object");
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::VENDORNOTWORKING);
		player->sendMessage(soldMessage);
		return;
	}

	ManagedReference<AuctionItem*> oldItem = auctionMap->getItem(objectid);
	ManagedReference<SceneObject*> objectToSell = zoneServer->getObject(objectid);
	String vendorUID = getVendorUID(vendor);

	if (objectToSell == NULL) {
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::INVALIDITEM);
		player->sendMessage(soldMessage);
		return;
	}

	if(oldItem == NULL) {
		if (objectToSell == NULL || !objectToSell->isASubChildOf(player) || objectToSell->isNoTrade()) {
			if(objectToSell != NULL && !objectToSell->isNoTrade())
				error("trying to add invalid object");
			ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::INVALIDITEM);
			player->sendMessage(soldMessage);
			return;
		}
	} else {

		if(oldItem->getStatus() == AuctionItem::FORSALE) {
			ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::ALREADYFORSALE);
			player->sendMessage(soldMessage);
			return;
		}

		/// Is it being sold from the stockroom
		if (oldItem->getOwnerID() != player->getObjectID()) {
			error("trying to add invalid object");
			ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::INVALIDITEM);
			player->sendMessage(soldMessage);
			return;
		}

		auctionMap->deleteItem(vendor, oldItem);

	}

	ManagedReference<Zone*> zone = vendor->getZone();
	if (zone == NULL) {
		error("null vendor zone");
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::UNKNOWNERROR);
		player->sendMessage(soldMessage);
		return;
	}


	int res = checkSaleItem(player, objectToSell, vendor, price, premium);

	if (res != 0) {
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, res);
		player->sendMessage(soldMessage);
		return;
	}

	ManagedReference<AuctionItem*> item = createVendorItem(player, objectToSell.get(), vendor, description, price, duration, auction, premium);
	if(item == NULL) {
		error("Unable to create vendor item");
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::UNKNOWNERROR);
		player->sendMessage(soldMessage);
		return;
	}

	Locker locker(item);

	int result = auctionMap->addItem(player, vendor, item);

	if(result != ItemSoldMessage::SUCCESS) {
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, result);
		player->sendMessage(soldMessage);
		auctionMap->removeFromCommodityLimit(item);
		return;
	}

	objectToSell->destroyObjectFromWorld(true);

	if (vendor->isBazaarTerminal()) {
		StringIdChatParameter str("@base_player:sale_fee");

		float costReduction = 1;
		if(player->hasSkill("crafting_merchant_sales_01"))
				costReduction = .80f;
		if(player->hasSkill("crafting_merchant_sales_03"))
				costReduction = .60f;

		if (item->isPremiumAuction()) {
			player->subtractBankCredits(costReduction * (SALESFEE * 5));
			str.setDI(costReduction * (SALESFEE * 5));

		} else {
			player->subtractBankCredits(costReduction * SALESFEE);
			str.setDI(costReduction * SALESFEE);
		}

		player->sendSystemMessage(str);
	}

	if (item->getStatus() == AuctionItem::OFFERED) {

		VendorDataComponent* vendorData = NULL;
		DataObjectComponentReference* data = vendor->getDataObjectComponent();
		if(data != NULL && data->get() != NULL && data->get()->isVendorData())
			vendorData = cast<VendorDataComponent*>(data->get());

		if(vendorData != NULL) {
			ManagedReference<SceneObject*> strongRef = zoneServer->getObject(vendorData->getOwnerId());

			if (strongRef != NULL && strongRef->isPlayerCreature()) {
				ManagedReference<CreatureObject*> strongOwnerRef = cast<CreatureObject*>(strongRef.get());

				if(strongOwnerRef->isOnline()) {
					strongOwnerRef->sendSystemMessage(player->getFirstName() + " has offered an item to " + vendor->getDisplayedName());
				}
			}
		}
	}

	item->setPersistent(1);

	if(item->isAuction()) {
		Reference<Task*> newTask = new ExpireAuctionTask(_this.get(), item);
		newTask->schedule((item->getExpireTime() - time(0)) * 1000);

		Locker locker(&auctionEvents);
		auctionEvents.put(item->getAuctionedItemObjectID(), newTask);
	}

	BaseMessage* msg = new ItemSoldMessage(objectid, 0);
	player->sendMessage(msg);

}

String AuctionManagerImplementation::getVendorUID(SceneObject* vendor) {

	//planet.region.vendorname.oid#x,y

	if(vendor->getZone() == NULL) {
		error("no zone for our poor vendor");
		return "nozone.nozone.sadpandavendor." + String::valueOf(vendor->getObjectID()) + "#0,0";
	}

	String uid = "error.error.errorvendor." + String::valueOf(vendor->getObjectID()) + "#0,0";

	AuctionTerminalDataComponent* terminalData = NULL;
	DataObjectComponentReference* data = vendor->getDataObjectComponent();
	if(data != NULL && data->get() != NULL && data->get()->isAuctionTerminalData())
		terminalData = cast<AuctionTerminalDataComponent*>(data->get());

	if(terminalData != NULL)
		uid = terminalData->getUID();

	return uid;
}

int AuctionManagerImplementation::checkSaleItem(CreatureObject* player, SceneObject* object, SceneObject* vendor, int price, bool premium) {

	if(vendor == NULL) {
		error("NULL Vendor");
		return ItemSoldMessage::UNKNOWNERROR;
	}

	if(auctionMap->containsItem(object->getObjectID()))
		return ItemSoldMessage::ALREADYFORSALE;

	if (price < 1)
		return ItemSoldMessage::INVALIDSALEPRICE;

	if(vendor->isVendor()) {

		VendorDataComponent* vendorData = NULL;
		DataObjectComponentReference* data = vendor->getDataObjectComponent();
		if(data != NULL && data->get() != NULL && data->get()->isVendorData())
			vendorData = cast<VendorDataComponent*>(data->get());

		if (player->getObjectID() == vendorData->getOwnerId()) {
			if (auctionMap->getVendorItemCount(vendor) >= player->getSkillMod("vendor_item_limit"))
				return ItemSoldMessage::TOOMANYITEMS;
		} else {
			if (auctionMap->getCommodityCount(player) >= MAXSALES)
				return ItemSoldMessage::TOOMANYITEMS;
		}

		if (price > MAXVENDORPRICE)
			return ItemSoldMessage::INVALIDSALEPRICE;
	}

	if(vendor->isBazaarTerminal()) {
		if (auctionMap->getCommodityCount(player) >= MAXSALES)
			return ItemSoldMessage::TOOMANYITEMS;

		if (price > MAXBAZAARPRICE)
			return ItemSoldMessage::INVALIDSALEPRICE;

		if (player->getBankCredits() < SALESFEE)
			return ItemSoldMessage::NOTENOUGHCREDITS;

		if (premium && player->getBankCredits() < SALESFEE * 5)
			return ItemSoldMessage::NOTENOUGHCREDITS;

	}

	if(object->isIntangibleObject() && !object->isManufactureSchematic())
		return ItemSoldMessage::INVALIDITEM;

	return 0;
}

AuctionItem* AuctionManagerImplementation::createVendorItem(CreatureObject* player, SceneObject* objectToSell, SceneObject* vendor, const UnicodeString& description, int price, unsigned int duration, bool auction, bool premium) {

	Zone* zone = vendor->getZone();

	if (zone == NULL)
		return NULL;

	uint64 vendorExpire = time(0) + AuctionManager::VENDOREXPIREPERIOD;
	uint64 commodityExpire = time(0) + AuctionManager::COMMODITYEXPIREPERIOD;

	String playername = player->getFirstName().toLowerCase();
	String descr = description.toString();
	String planetStr = zone->getZoneName();

	AuctionItem* item  = new AuctionItem(objectToSell->getObjectID());

	ManagedReference<CityRegion*> cityRegion = vendor->getCityRegion();
	String region = "@planet_n:" + planetStr;

	if (cityRegion != NULL)
		region = cityRegion->getRegionName();

	String name = objectToSell->getDisplayedName();

	item->setVendorUID(getVendorUID(vendor));
	item->setOnBazaar(vendor->isBazaarTerminal());

	if (premium)
		item->setAuctionPremium();

	item->setVendorID(vendor->getObjectID());
	item->setItemName(name);
	item->setItemDescription(description.toString());
	item->setItemType(objectToSell->getClientGameObjectType());
	item->setPrice(price);
	item->setAuction(auction);
	item->setStatus(AuctionItem::FORSALE);
	item->setBuyerID(0);
	item->setBidderName("");

	VendorDataComponent* vendorData = NULL;
	DataObjectComponentReference* data = vendor->getDataObjectComponent();
	if(data != NULL && data->get() != NULL && data->get()->isVendorData())
		vendorData = cast<VendorDataComponent*>(data->get());

	// Someone elses Vendor (making this sell item an offer)
	if (!vendor->isBazaarTerminal()) {
		if(vendorData == NULL)
			return NULL;

		if(vendorData->getOwnershipRightsOf(player) == 1) {
			item->setStatus(AuctionItem::OFFERED);
			item->setOfferToID(vendorData->getOwnerId());
			item->setExpireTime(commodityExpire);
		} else {
			item->setExpireTime(vendorExpire);
		}
	} else {
		item->setExpireTime(commodityExpire);
	}

	updateAuctionOwner(item, player);
	ObjectManager::instance()->persistObject(item, 0, "auctionitems");


	return item;
}

int AuctionManagerImplementation::checkBidAuction(CreatureObject* player, AuctionItem* item, int price1, int price2) {
	if ((price1 > MAXBAZAARPRICE || price2 > MAXBAZAARPRICE) && item->isOnBazaar()) {
		return BidAuctionResponseMessage::PRICEOVERFLOW;
	}

	if (price1 < 1 || price2 < 1 || price1 < item->getPrice()) {
		return BidAuctionResponseMessage::INVALIDPRICE;
	}

	if (player->getBankCredits() < price1) { // Credit Check
		return BidAuctionResponseMessage::NOTENOUGHCREDITS;
	}

	return 0;
}

void AuctionManagerImplementation::doInstantBuy(CreatureObject* player, AuctionItem* item) {
	ManagedReference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());

	if (vendor == NULL)
		return;

	int tax = 0;
	ManagedReference<CityRegion*> city = NULL;
	if( vendor->getCityRegion() != NULL){
		city = vendor->getCityRegion().get();
		tax = item->getPrice() * (float) city->getSalesTax() / 100.f;
	}
	String playername = player->getFirstName().toLowerCase();

	ManagedReference<ChatManager*> cman = zoneServer->getChatManager();
	ManagedReference<PlayerManager*> pman = zoneServer->getPlayerManager();
	ManagedReference<CreatureObject*> seller = pman->getPlayer(item->getOwnerName());

	String sender = "auctioner";
	String sellerName = item->getOwnerName();

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = 0;


	Locker locker(item);

	if(item->isOnBazaar() || item->getStatus() == AuctionItem::OFFERED)
		availableTime = currentTime + AuctionManager::COMMODITYEXPIREPERIOD;
	else
		availableTime = currentTime + AuctionManager::VENDOREXPIREPERIOD;

	updateAuctionOwner(item, player);

	item->setStatus(AuctionItem::SOLD);
	item->setExpireTime(availableTime);
	item->setBuyerID(player->getObjectID());
	item->setBidderName(playername);
	item->clearAuctionWithdraw();

	player->subtractBankCredits(item->getPrice() + tax);

	BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), 0);
	player->sendMessage(msg);

	// Waypoint to Vendor / bazaar
	float waypointX = vendor->getWorldPositionX();
	float waypointY = vendor->getWorldPositionY();

	ManagedReference<WaypointObject*> waypoint = cast<WaypointObject*>(zoneServer->createObject(0xc456e788, 1));
	waypoint->setPlanetCRC(vendor->getPlanetCRC());
	waypoint->setPosition(waypointX, 0, waypointY);

	waypoint->setCustomObjectName(vendor->getDisplayedName(), false);

	if (!item->isOnBazaar()) {
		//Setup the mail to the vendor owner
		String sender = "auctioner";

		PlayerManager* pman = zoneServer->getPlayerManager();
		/*ManagedReference<CreatureObject*> seller = pman->getPlayer(item->getOwnerName());

		Locker _locker(seller);*/

		UnicodeString subject1("@auction:subject_vendor_seller");

		StringIdChatParameter body1("@auction:seller_success");
		body1.setTO(item->getItemName());
		body1.setTT(item->getBidderName());
		body1.setDI(item->getPrice());

		//Setup the mail to the buyer
		/*ManagedReference<CreatureObject*> buyer = pman->getPlayer(item->getBidderName());

		Locker _locker2(buyer);*/

		UnicodeString subject2("@auction:subject_vendor_buyer");
		StringIdChatParameter body2("@auction:buyer_success");
		body2.setTO(item->getItemName());
		body2.setTT(sellerName);
		body2.setDI(item->getPrice());

		//Send the Mail
		locker.release();

		cman->sendMail(sender, subject1, body1, sellerName);
		cman->sendMail(sender, subject2, body2, item->getBidderName(), waypoint);

	} else {

		// Setup the mail to the seller
		UnicodeString subject1("@auction:subject_instant_seller");
		StringIdChatParameter body1("@auction:seller_success");
		body1.setTO(item->getItemName());
		body1.setTT(item->getBidderName());
		body1.setDI(item->getPrice());

		// Setup the mail to the buyer
		UnicodeString subject2("@auction:subject_instant_buyer");
		StringIdChatParameter body2("@auction:buyer_success");
		body2.setTO(item->getItemName());
		body2.setTT(sellerName);
		body2.setDI(item->getPrice());

		locker.release();

		//Send the Mail
		cman->sendMail(sender, subject1, body1, sellerName);
		cman->sendMail(sender, subject2, body2, item->getBidderName(), waypoint);

	}

	if (seller == NULL) {
		error("seller null for name " + item->getOwnerName());
		return;
	}

	locker.release();

	Locker slocker(seller);
	seller->addBankCredits(item->getPrice());
	slocker.release();


	if(city != NULL && !city->isClientRegion() && tax){
		Locker clock(city);
		city->addToCityTreasury(tax);
	}

}

void AuctionManagerImplementation::doAuctionBid(CreatureObject* player, AuctionItem* item, int price1, int proxyBid) {

	if(price1 <= item->getPrice() || proxyBid <= price1) {
		BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), 1);
		player->sendMessage(msg);
		return;
	}

	String playername = player->getFirstName().toLowerCase();

	ManagedReference<ChatManager*> cman = zoneServer->getChatManager();
	ManagedReference<PlayerManager*> pman = zoneServer->getPlayerManager();
	// don't allow owner bid on the item.  don't allow old auction info
	// send auctioner invalid message
	if (playername == item->getOwnerName() || price1 <= item->getPrice() || proxyBid <= price1) {
		BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), 1);
		player->sendMessage(msg);
		return;
	}

	ManagedReference<CreatureObject*> priorBidder = pman->getPlayer(item->getBidderName());

	/// Use previous proxy
	if(priorBidder != NULL && proxyBid < item->getProxy()) {
		Locker locker(item);
		Locker plocker(priorBidder);

		int increase = price1 - item->getPrice();

		int fullPrice = proxyBid + increase - item->getPrice();

		//TODO: prior didnt have enough money -> assert.. fix properly
		if (priorBidder->getBankCredits() < fullPrice) {
			BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), BidAuctionResponseMessage::NOTENOUGHCREDITS);
			player->sendMessage(msg);

			return;
		}

		priorBidder->subtractBankCredits(fullPrice);
		item->setPrice(proxyBid + increase);
		BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), BidAuctionResponseMessage::SUCCEDED);
		player->sendMessage(msg);

		if(priorBidder != player) {
			StringIdChatParameter body("@auction:bidder_outbid");
			body.setTO(item->getItemName());
			priorBidder->sendSystemMessage(body);
		}

		return;
	}

	Locker locker(item);
	Locker plocker(player);

	if (player->getBankCredits() < item->getPrice()) {
		BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), BidAuctionResponseMessage::NOTENOUGHCREDITS);
		player->sendMessage(msg);

		return;
	}

	item->setProxy(proxyBid);

	// send prior bidder their money back
	if (item->getBidderName().length() > 0) {

		StringIdChatParameter body("@auction:bidder_outbid");
		body.setTO(item->getItemName());

		if (priorBidder != NULL) {
			Locker clocker(priorBidder, player);

			if(priorBidder != player)
				priorBidder->sendSystemMessage(body);
			priorBidder->addBankCredits(item->getPrice());
		}

		// mail prior bidder with outcome
		UnicodeString subject("@auction:subject_auction_outbid");


		item->setPrice(price1);
		item->setBuyerID(player->getObjectID());
		item->setBidderName(playername);

		// take money from high bidder
		player->subtractBankCredits(item->getPrice());

		plocker.release();
		locker.release();

		cman->sendMail("auctioner", subject, body, item->getBidderName());

		// no prior bidder, just take the money
	} else {
		item->setPrice(price1);
		item->setBuyerID(player->getObjectID());
		item->setBidderName(playername);

		player->subtractBankCredits(item->getPrice());
	}

	BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), 0);
	player->sendMessage(msg);
}

void AuctionManagerImplementation::buyItem(CreatureObject* player, uint64 objectid, int price1, int price2) {
	ManagedReference<AuctionItem*> item = auctionMap->getItem(objectid);

	if (item == NULL) {
		BaseMessage* msg = new BidAuctionResponseMessage(objectid, BidAuctionResponseMessage::INVALIDITEM);
		player->sendMessage(msg);
		return;
	}

	ManagedReference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());

	if (vendor == NULL || item->getStatus() == AuctionItem::SOLD) {
		BaseMessage* msg = new BidAuctionResponseMessage(objectid, BidAuctionResponseMessage::INVALIDITEM);
		player->sendMessage(msg);
		return;
	}

	if (item->getOwnerID() == player->getObjectID()) {
		BaseMessage* msg = new BidAuctionResponseMessage(objectid, BidAuctionResponseMessage::PURCHASEFAILED);
		player->sendMessage(msg);
		return;
	}

	ManagedReference<CityRegion*> city = vendor->getCityRegion();

	//TODO: Apply the sales tax to the price here, and check the total price
	int totalPrice = item->getPrice();

	if (city != NULL && !city->isClientRegion())
		totalPrice *= 1.f + (float) city->getSalesTax() / 100.f;

	//We should send this to checkBidAuction, but how will it work with auctions???

	int res = checkBidAuction(player, item, totalPrice , price2);

	if (res != 0) {
		BaseMessage* msg = new BidAuctionResponseMessage(objectid, res);
		player->sendMessage(msg);
		return;
	}

	//Then down here, we would actually set the price on the item to the totalPrice.

	if (!item->isAuction()) { // Instant buy
		doInstantBuy(player, item);
	} else { // For Auction Bids
		doAuctionBid(player, item, price1, price2);
	}

}


int AuctionManagerImplementation::checkRetrieve(CreatureObject* player, uint64 objectIdToRetrieve, SceneObject* vendor) {
    // Check both Bazaar and Vendors

	if (!auctionMap->containsItem(objectIdToRetrieve))
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;

	ManagedReference<SceneObject*> saleItem = zoneServer->getObject(objectIdToRetrieve);
	
	if (saleItem == NULL) {
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;
	}

	if(saleItem->isIntangibleObject()) {
		ManagedReference<SceneObject*> datapad = player->getSlottedObject("datapad");
		if (datapad->hasFullContainerObjects())
			return RetrieveAuctionItemResponseMessage::FULLINVENTORY;
	} else {
		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

		if (inventory->hasFullContainerObjects())
			return RetrieveAuctionItemResponseMessage::FULLINVENTORY;
	}

	ManagedReference<AuctionItem*> item = auctionMap->getItem(objectIdToRetrieve);
	if (item == NULL || item->getStatus() == AuctionItem::RETRIEVED) {
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;
	}

	if(item->isAuction() && item->getStatus() == AuctionItem::FORSALE)
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;

	/*
	if(item->getStatus() == AuctionItem::SOLD && player->getObjectID() == item->getOwnerID()) {
		item->setStatus(AuctionItem::EXPIRED);
		return RetrieveAuctionItemResponseMessage::DONTRETRIEVE;
	}
	*/

	String playername = player->getFirstName();

	// only the owner can yank his own auction off the vendor
	if (item->getStatus() != AuctionItem::SOLD && (player->getObjectID() != item->getOwnerID()))
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;

	// the bidder is the only one who can get his auction after expiration
	if (item->getStatus() == AuctionItem::SOLD && item->getBuyerID() != player->getObjectID()) {
		player->sendSystemMessage(item->getBidderName() + " bought this, " + player->getFirstName() + " trying to retrieve");
		error(item->getBidderName() + " bought this, " + player->getFirstName() + " trying to retrieve");
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;
	}

	if(vendor->isVendor() && !vendor->isInRange(player, 8.0f))
		return RetrieveAuctionItemResponseMessage::TOOFAR;


	if (vendor->isBazaarTerminal()) {
		ManagedReference<CityRegion*> region = vendor->getCityRegion();

		String location = vendor->getZone()->getZoneName() + ".";

		if (region != NULL) {
			location += region->getRegionName();
			//String region = terminal->getBazaarRegion();

			if (!item->getVendorUID().beginsWith(location)) {
				return RetrieveAuctionItemResponseMessage::TOOFAR;
			}
		} else {
			StringBuffer msg;
			msg << "null area for bazaar terminal at" << vendor->getPositionX() << " " << vendor->getPositionY() << " zone " << vendor->getZone()->getZoneName();
			error(msg);
		}

		if (!item->getVendorUID().beginsWith(location)) {
			return RetrieveAuctionItemResponseMessage::TOOFAR;
		}
	}

	return 0;
}

void AuctionManagerImplementation::refundAuction(AuctionItem* item) {
	ManagedReference<PlayerManager*> pman = zoneServer->getPlayerManager();
	ManagedReference<CreatureObject*> bidder = pman->getPlayer(item->getBidderName());
	ManagedReference<ChatManager*> cman = zoneServer->getChatManager();

	// send the player a mail and system message
	UnicodeString subject("@auction:subject_auction_cancelled");
	StringIdChatParameter body("auction", "buyer_canceled");
	body.setTO(item->getItemName());
	body.setTT(item->getOwnerName());

	if (bidder != NULL) {
		int bankCredits = bidder->getBankCredits();
		bidder->setBankCredits(bankCredits + item->getPrice());
		bidder->sendSystemMessage(body);
	}

	cman->sendMail("auctioner", subject, body, item->getBidderName());
}

void AuctionManagerImplementation::retrieveItem(CreatureObject* player, uint64 objectid, uint64 vendorID) {

	ManagedReference<SceneObject*> vendor = zoneServer->getObject(vendorID);
	RetrieveAuctionItemResponseMessage* msg = NULL;

	// check for valid vendor terminal
	if ((vendor == NULL || !vendor->isVendor()) && !vendor->isBazaarTerminal()) {
		msg = new RetrieveAuctionItemResponseMessage(objectid, RetrieveAuctionItemResponseMessage::NOTALLOWED);
		player->sendMessage(msg);
		return;
	}

	int res = checkRetrieve(player, objectid, vendor);

	if (res != 0) {
		if(res != RetrieveAuctionItemResponseMessage::TOOFAR) {
			if(res == RetrieveAuctionItemResponseMessage::DONTRETRIEVE)
				res = 0;
			msg = new RetrieveAuctionItemResponseMessage(objectid, res);
			player->sendMessage(msg);
		}
		return;
	}

	ManagedReference<AuctionItem*> item = auctionMap->getItem(objectid);
	if (item == NULL) {
		error("NULL item in retrieveItem()");
		return;
	}

	ManagedReference<SceneObject*> objectToRetrieve = zoneServer->getObject(objectid);

	if (objectToRetrieve == NULL) {
		error("null objectToRetrieve in retrieveItem()");
		msg = new RetrieveAuctionItemResponseMessage(objectid, 0);
		player->sendMessage(msg);
		return;
	}

	Locker locker(item);
	Locker plocker(player);

	ManagedReference<SceneObject*> destination = NULL;

	if(objectToRetrieve->isIntangibleObject())
		destination = player->getSlottedObject("datapad");
	else
		destination = player->getSlottedObject("inventory");

	if(destination->transferObject(objectToRetrieve, -1, false)) {
		destination->broadcastObject(objectToRetrieve, true);

		item->setStatus(AuctionItem::RETRIEVED);

		String vuid = getVendorUID(vendor);

		auctionMap->deleteItem(vendor, item);

		msg = new RetrieveAuctionItemResponseMessage(objectid, 0);
		player->sendMessage(msg);
	} else {
		msg = new RetrieveAuctionItemResponseMessage(objectid, RetrieveAuctionItemResponseMessage::NOTALLOWED);
		player->sendMessage(msg);
	}
}

AuctionQueryHeadersResponseMessage* AuctionManagerImplementation::fillAuctionQueryHeadersResponseMessage(CreatureObject* player, SceneObject* vendor, TerminalListVector* terminalList, int screen, uint32 category, int clientcounter, int offset) {
	AuctionQueryHeadersResponseMessage* reply = new AuctionQueryHeadersResponseMessage(screen, clientcounter, player);

	String pname = player->getFirstName().toLowerCase();
	uint32 now = time(0);
	int displaying = 0;
	/*System::out << "Screen =" + String::valueOf(screen) << endl;
	System::out << "Category =" + String::valueOf(category) << endl;
	System::out << "VendorItemSize =" + String::valueOf(auctionMap->getVendorItemCount()) << endl;
	System::out << "AuctionItemSize =" + String::valueOf(auctionMap->getAuctionCount()) << endl;
	System::out << "______________________________" << endl;*/

	for (int j = 0; (j < terminalList->size()) && (displaying < (offset + 100)); ++j) {

		Reference<TerminalItemList*> items = terminalList->get(j);

		if(items == NULL)
			continue;

		/// Exclude non-searchable vendor Items
		if(vendor->isBazaarTerminal() && screen == 7 && !items->isSearchable())
			continue;

		try {
			items->rlock();

			for (int i = 0; (i < items->size()) && (displaying < (offset + 100)); i++) {
				ManagedReference<AuctionItem*> item = items->get(i);

				if(item == NULL)
					continue;

				if(!item->isAuction() && item->getExpireTime() <= now) {
					expireSale(item);
					continue;
				}

				switch(screen) {
				case 7: // Vendor search Bazaar && Vendor

					if(vendor->isVendor() && item->getVendorID() != vendor->getObjectID()) {
						if(item->getOwnerID() != player->getObjectID())
							continue;
					}
				case 2: // All Auctions (Bazaar)
					if (item->getStatus() == AuctionItem::FORSALE) {
						if (category & 255) { // Searching a sub category
							if (item->getItemType() == category) {
								if (displaying >= offset)
									reply->addItemToList(items->get(i));

								displaying++;
							}
						} else if (item->getItemType() & category) {
							if (displaying >= offset)
								reply->addItemToList(items->get(i));

							displaying++;

						} else if ((category == 8192) && (item->getItemType() < 256)) {
							if (displaying >= offset)
								reply->addItemToList(items->get(i));

							displaying++;
						} else if (category == 0 && vendor->isVendor()) { // Searching all items
							if (displaying >= offset)
								reply->addItemToList(item);

							displaying++;
						}
					}
					break;
				case 3: // My auctions/sales
					if (item->getStatus() == AuctionItem::FORSALE && (item->getOwnerID() == player->getObjectID())) {
						reply->addItemToList(item);
					}
					break;
				case 4: // My Bids
					if (item->isAuction() && item->getStatus() == AuctionItem::FORSALE && (item->getBidderName() == pname)) {
						reply->addItemToList(item);
					}
					break;
				case 5: // Retrieve items screen
					if ((item->getStatus() == AuctionItem::SOLD && item->getBuyerID() == player->getObjectID()) ||
							(item->getStatus() == AuctionItem::EXPIRED && item->getOwnerID() == player->getObjectID())) {
						reply->addItemToList(item);
					}
					break;
				case 6: // Offers to Vendor (vendor owner)
					if (item->getStatus() == AuctionItem::OFFERED && item->getOfferToID() == player->getObjectID()) {
						reply->addItemToList(item);
					}
					break;
				case 8: // Stockroom
					if ((item->getStatus() == AuctionItem::EXPIRED && item->getOwnerID() == player->getObjectID()) ||
							(item->getStatus() == AuctionItem::SOLD && item->getBuyerID() == player->getObjectID()))
						reply->addItemToList(item);
					break;
				case 9: // Offers to vendor (browsing player)
					if (item->getStatus() == AuctionItem::OFFERED && item->getOwnerID() == player->getObjectID()) {
						reply->addItemToList(item);
					}
					break;
				}
			}
			items->unlock();
		} catch(Exception& e) {
			error(e.getMessage());
			items->unlock();
		}
	}

	if (displaying == (offset + 100))
		reply->createMessage(offset, true);
	else
		reply->createMessage(offset);

	return reply;
}

void AuctionManagerImplementation::getData(CreatureObject* player, int extent, uint64 vendorObjectID, int screen, unsigned int category, int clientcounter, int offset) {
	ManagedReference<TangibleObject*> vendorInUse = cast<TangibleObject*>(zoneServer->getObject(vendorObjectID));

	if (vendorInUse == NULL || (!vendorInUse->isVendor() && !vendorInUse->isBazaarTerminal())) {
		error("null vendor in getData()");
		return;
	}

	ManagedReference<SceneObject*> parent = vendorInUse->getRootParent();

	if (parent != NULL && parent != player->getRootParent().get())
		return;

	if(player->getZone() == NULL) {
		error("player not in a zone");
		return;
	}

	ManagedReference<BuildingObject*> rootParent = cast<BuildingObject*>(parent.get());
	if(rootParent != NULL && !rootParent->isAllowedEntry(player))
		return;

	//Handle Merchant XP for players using other players vendors...
	if (!vendorInUse->isBazaarTerminal()) {

		DataObjectComponentReference* data = vendorInUse->getDataObjectComponent();
		if(data == NULL || data->get() == NULL || !data->get()->isVendorData()) {
			error("Vendor has no data component in getData");
			return;
		}

		VendorDataComponent* vendorData = cast<VendorDataComponent*>(data->get());
		if(vendorData == NULL) {
			error("Vendor has wrong data component in getData");
			return;
		}

		vendorData->awardUseXP();
	}

	String planet = "";
	String region = "";
	ManagedReference<SceneObject*> vendor = NULL;

	switch (extent) {
	case 3:
		vendor = vendorInUse;
	case 2:
		if(player->getCityRegion() != NULL)
			region = player->getCityRegion().get()->getRegionName();
		else {
			region = "@planet_n:" + player->getZone()->getZoneName();
			vendor = vendorInUse;
		}
	case 1:
		planet = player->getZone()->getZoneName();
	default:
		break;
	}

	getAuctionData(player, vendorInUse, planet, region, vendor, screen, category, clientcounter, offset);

}

void AuctionManagerImplementation::getAuctionData(CreatureObject* player, SceneObject* usedVendor, const String& planet, const String& region, SceneObject* vendor, int screen, uint32 category, int clientcounter, int offset) {

	TerminalListVector terminalList;

	if (usedVendor->isBazaarTerminal() && screen != 7) { // This is to prevent bazaar items from showing on Vendor Search
		terminalList = auctionMap->getBazaarTerminalData(planet, region, vendor);
	} else {
		terminalList = auctionMap->getVendorTerminalData(planet, region, vendor);
	}

	AuctionQueryHeadersResponseMessage* msg = fillAuctionQueryHeadersResponseMessage(player, usedVendor, &terminalList, screen, category, clientcounter, offset);
	player->sendMessage(msg);
}

void AuctionManagerImplementation::getItemAttributes(CreatureObject* player, uint64 objectid) {

	ManagedReference<AuctionItem*> auctionItem = auctionMap->getItem(objectid);
	if(auctionItem == NULL)
		return;

	ManagedReference<SceneObject*> object = zoneServer->getObject(auctionItem->getAuctionedItemObjectID());

	if (object == NULL) {
		error("not a valid object in getItemAttributes");
		return;
	}

	UnicodeString description(auctionItem->getItemDescription());
	AttributeListMessage* msg = new AttributeListMessage(objectid, description);

	object->fillAttributeList(msg, player);
	//msg->insertInt(0);
	String templateFile = TemplateManager::instance()->getTemplateFile(object->getClientObjectCRC());
	msg->insertAscii(templateFile);

	String cust = "";
	if(object->isTangibleObject()) {
		ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(object.get());
		if(tano != NULL)
			tano->getCustomizationString(cust);
	}
	msg->insertAscii(cust);

	player->sendMessage(msg);

}

void AuctionManagerImplementation::cancelItem(CreatureObject* player, uint64 objectID) {

	ManagedReference<AuctionItem*> item = auctionMap->getItem(objectID);

	// Item wasnt found. it doesn't exist
	if (item == NULL) {
		error("null item in cancelItem()");
		BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, CancelLiveAuctionResponseMessage::INVALIDITEM);
		player->sendMessage(msg);
		return;
	}

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = 0;

	if (item->getStatus() == AuctionItem::FORSALE) {
		if(item->getOwnerID() != player->getObjectID()) {
			error("not the owner of the item in cancelItem()");
			BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, CancelLiveAuctionResponseMessage::NOTOWNER);
			player->sendMessage(msg);
			return;
		}

		if(item->isOnBazaar())
			availableTime = currentTime + AuctionManager::COMMODITYEXPIREPERIOD;
		else
			availableTime = currentTime + AuctionManager::VENDOREXPIREPERIOD;

	} else if (item->getStatus() == AuctionItem::OFFERED) {
		if(item->getOfferToID() != player->getObjectID() &&
				item->getOwnerID() != player->getObjectID()) {
			error("not the target of offered item in cancelItem()");
			BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, CancelLiveAuctionResponseMessage::INVALIDITEM);
			player->sendMessage(msg);
			return;
		}
		/// 7 Days
		availableTime = currentTime + AuctionManager::COMMODITYEXPIREPERIOD;

	} else {
		BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, CancelLiveAuctionResponseMessage::ALREADYCOMPLETED);
		player->sendMessage(msg);
		return;
	}

	if (item->getExpireTime() <= 0) {
		BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, CancelLiveAuctionResponseMessage::ALREADYCOMPLETED);
		player->sendMessage(msg);
		return;
	}

	// refund auction money
	if (item->isAuction()) {
		refundAuction(item);
		Locker locker(&auctionEvents);

		if(auctionEvents.contains(item->getAuctionedItemObjectID())) {
			Reference<Task*> newTask = auctionEvents.get(item->getAuctionedItemObjectID());
			
			if(newTask != NULL)
				newTask->cancel();
				
			auctionEvents.drop(item->getAuctionedItemObjectID());
		}
	}

	/// If the offeree cancels
	if(item->getStatus() == AuctionItem::OFFERED && item->getOfferToID() == player->getObjectID()) {

		ManagedReference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());

		if(vendor != NULL) {
			ManagedReference<ChatManager*> cman = zoneServer->getChatManager();
			String sender = "auctioner";

			// Waypoint to Vendor / bazaar
			float waypointX = vendor->getWorldPositionX();
			float waypointY = vendor->getWorldPositionY();

			ManagedReference<WaypointObject*> waypoint = cast<WaypointObject*>(zoneServer->createObject(0xc456e788, 1));
			waypoint->setPlanetCRC(vendor->getPlanetCRC());
			waypoint->setPosition(waypointX, 0, waypointY);

			waypoint->setCustomObjectName(vendor->getDisplayedName(), false);

			UnicodeString subject("@auction:subject_auction_unsuccessful");
			StringIdChatParameter body("@auction:seller_fail");
			body.setTO(item->getItemName());

			//Send the Mail
			cman->sendMail(sender, subject, body, item->getOwnerName(), waypoint);
		}
	}

	Locker locker(item);

	item->setStatus(AuctionItem::EXPIRED);
	item->setExpireTime(availableTime);
	item->clearAuctionWithdraw();

	BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, 0);
	player->sendMessage(msg);

}

void AuctionManagerImplementation::expireSale(AuctionItem* item) {
	Locker locker(item);
		
	if(item->getStatus() == AuctionItem::EXPIRED) {
		deleteExpiredSale(item);
		return;
	}

	ManagedReference<ChatManager*> cman = zoneServer->getChatManager();

	//Send the mail to the vendor owner
	String sender = "auctioner";

	UnicodeString subject1("@auction:subject_vendor_seller");

	StringIdChatParameter body1("@auction:seller_fail");
	body1.setTO(item->getItemName());
	
	locker.release();

	cman->sendMail(sender, subject1, body1, item->getOwnerName());

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = 0;

	if(item->isOnBazaar())
		availableTime = currentTime + AuctionManager::COMMODITYEXPIREPERIOD;
	else
		availableTime = currentTime + AuctionManager::VENDOREXPIREPERIOD;

	item->setStatus(AuctionItem::EXPIRED);
	item->setExpireTime(availableTime);
	item->clearAuctionWithdraw();
}

void AuctionManagerImplementation::expireBidAuction(AuctionItem* item) {

	Locker locker(item);

	ManagedReference<ChatManager*> cman = zoneServer->getChatManager();

	//Send the mail to the vendor owner
	String sender = "auctioner";

	UnicodeString subject1("@auction:subject_auction_item_expired");

	StringIdChatParameter body1("@auction:seller_fail");
	body1.setTO(item->getItemName());

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = 0;

	if(item->isOnBazaar())
		availableTime = currentTime + AuctionManager::COMMODITYEXPIREPERIOD;
	else
		availableTime = currentTime + AuctionManager::VENDOREXPIREPERIOD;

	item->setStatus(AuctionItem::EXPIRED);
	item->setExpireTime(availableTime);
	item->clearAuctionWithdraw();
	
	locker.release();
	
	cman->sendMail(sender, subject1, body1, item->getOwnerName());
}

void AuctionManagerImplementation::expireAuction(AuctionItem* item) {
	ManagedReference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());
	if (vendor == NULL)
		return;

	String playername = item->getBidderName();
	String sellerName = item->getOwnerName();
	ManagedReference<ChatManager*> cman = zoneServer->getChatManager();
	ManagedReference<PlayerManager*> pman = zoneServer->getPlayerManager();

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = currentTime + AuctionManager::COMMODITYEXPIREPERIOD;

	Locker locker(item);
	item->setExpireTime(availableTime);
	item->clearAuctionWithdraw();

	if(playername.isEmpty()) {
		locker.release();
		expireBidAuction(item);

	} else {
		// Someone won the auction
		ManagedReference<CreatureObject*> buyer = pman->getPlayer(item->getBidderName());

		item->setStatus(AuctionItem::SOLD);
		updateAuctionOwner(item, buyer);

		// Waypoint to Vendor / bazaar
		float waypointX = vendor->getWorldPositionX();
		float waypointY = vendor->getWorldPositionY();

		ManagedReference<WaypointObject*> waypoint = cast<WaypointObject*>(zoneServer->createObject(0xc456e788, 1));
		waypoint->setPlanetCRC(vendor->getPlanetCRC());
		waypoint->setPosition(waypointX, 0, waypointY);

		waypoint->setCustomObjectName(vendor->getDisplayedName(), false);

		String sender = "auctioner";
		UnicodeString subject1("@auction:subject_vendor_seller");
		StringIdChatParameter body1("@auction:seller_success");
		body1.setTO(item->getItemName());
		body1.setTT(item->getBidderName());
		body1.setDI(item->getPrice());

		UnicodeString subject2("@auction:subject_vendor_buyer");
		StringIdChatParameter body2("@auction:buyer_success");
		body2.setTO(item->getItemName());
		body2.setTT(sellerName);
		body2.setDI(item->getPrice());

		//Send the Mail
		locker.release();
		
		cman->sendMail(sender, subject1, body1, sellerName);
		cman->sendMail(sender, subject2, body2, item->getBidderName(), waypoint);
	}
}

void AuctionManagerImplementation::deleteExpiredSale(AuctionItem* item) {
	Locker locker(item);
		
	ManagedReference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());
	if (vendor != NULL) {

		ManagedReference<ChatManager*> cman = zoneServer->getChatManager();
		String sender = "auctioner";

		// Waypoint to Vendor / bazaar
		float waypointX = vendor->getWorldPositionX();
		float waypointY = vendor->getWorldPositionY();

		ManagedReference<WaypointObject*> waypoint = cast<WaypointObject*>(zoneServer->createObject(0xc456e788, 1));
		waypoint->setPlanetCRC(vendor->getPlanetCRC());
		waypoint->setPosition(waypointX, 0, waypointY);

		waypoint->setCustomObjectName(vendor->getDisplayedName(), false);

		UnicodeString subject("@auction:subject_auction_unsuccessful");
		StringIdChatParameter body("@auction:item_expired");
		body.setTO(item->getItemName());

		//Send the Mail
		locker.release();
		
		cman->sendMail(sender, subject, body, item->getOwnerName(), waypoint);
	}

	auctionMap->deleteItem(vendor, item);
}

void AuctionManagerImplementation::displayInfo(CreatureObject* player) {
	ManagedReference<SuiListBox*> list = new SuiListBox(player, SuiWindowType::MARKET_INFO, 0x00);
	list->setPromptTitle("Market Info");
	list->setPromptText("Information about the commodities market");

	list->addMenuItem("Terminals with items");
	list->addMenuItem("\tBazaars: " + String::valueOf(auctionMap->getBazaarCount()));
	list->addMenuItem("\tVendors: " + String::valueOf(auctionMap->getVendorCount()));
	list->addMenuItem("Total Items: " + String::valueOf(auctionMap->getTotalItemCount()));

	player->sendMessage(list->generateMessage());
}

void AuctionManagerImplementation::updateAuctionOwner(AuctionItem* item, CreatureObject* player) {

	Locker locker(item);

	ManagedReference<PlayerManager*> pman = zoneServer->getPlayerManager();
	ManagedReference<CreatureObject*> previousOwner = pman->getPlayer(item->getOwnerName());

	if(player == previousOwner)
		return;

	auctionMap->removeFromCommodityLimit(item);

	item->setOwnerID(player->getObjectID());
	item->setOwnerName(player->getFirstName());

	if(!item->isOnBazaar() && item->getStatus() != AuctionItem::OFFERED)
		return;

	auctionMap->addToCommodityLimit(item);
}
