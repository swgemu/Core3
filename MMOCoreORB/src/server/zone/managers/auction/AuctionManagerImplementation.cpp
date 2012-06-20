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
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/area/BadgeActiveArea.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/chat/ChatManager.h"
#include "CheckAuctionsTask.h"
#include "server/zone/managers/vendor/VendorManager.h"
#include "server/zone/objects/tangible/components/vendor/VendorDataComponent.h"

void AuctionManagerImplementation::initialize() {
	Locker locker(_this.get());

	auctionMap = new AuctionsMap();

	ObjectDatabase* auctionDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("auctionitems", true);
	ObjectDatabaseManager::instance()->commitLocalTransaction();

	ObjectDatabaseIterator iterator(auctionDatabase);

	uint64 objectID = 0;

	while (iterator.getNextKey(objectID)) {
		ManagedReference<AuctionItem*> auctionItem = cast<AuctionItem*>(Core::getObjectBroker()->lookUp(objectID));
		ObjectDatabaseManager::instance()->commitLocalTransaction();

		if(auctionItem == NULL) {
			error("unable to load auction item: " + String::valueOf(objectID));
			continue;
		}

		ManagedReference<SceneObject*> vendor = cast<SceneObject*>(Core::getObjectBroker()->lookUp(auctionItem->getVendorID()));

		if(vendor == NULL) {
			error("unable to load vendor: " + String::valueOf(auctionItem->getVendorID()));
			continue;
		}

		String vuid = getVendorUID(vendor);
		auctionMap->addItem(vendor, vuid, auctionItem);
	}

	checkAuctions();
	checkVendorItems();
}

void AuctionManagerImplementation::checkVendorItems() {

	SortedVector<ManagedReference<AuctionItem* > > items = auctionMap->getVendorItems(NULL, "", "");

	info("Checking " + String::valueOf(items.size()) + " vendor items");

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = currentTime + 2592000;

	for (int i = 0; i < items.size(); ++i) {
		ManagedReference<AuctionItem*> item = items.get(i);
		if (item == NULL)
			continue;

		ManagedReference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());
		uint64 objectId = item->getAuctionedItemObjectID();

		if (vendor == NULL)
			continue;

		String vuid = getVendorUID(vendor);

		Locker _ilocker(item);
		if (item->getExpireTime() <= currentTime) {
			if (item->isInStockroom()) {
				auctionMap->removeItem(vendor, vuid, item);
				ObjectManager::instance()->destroyObjectFromDatabase(item->_getObjectID());
			} else {
				ChatManager* cman = zoneServer->getChatManager();

				//Send the mail to the vendor owner
				String sender = "auctioner";

				UnicodeString subject1("@auction:subject_vendor_seller");

				StringIdChatParameter body1("@auction:seller_fail");
				body1.setTO(item->getItemName());

				cman->sendMail(sender, subject1, body1, item->getOwnerName());

				// move to available items / stockroom
				item->setInStockroom(true);
				item->setExpireTime(availableTime);
				item->setBuyerID(item->getOwnerID());
				item->clearAuctionWithdraw();
			}
		}

		if (item->isRemovedByOwner() && !item->isInStockroom()) {
			//If this condition has been reached, the item has been removed from the db in retriveItem()
			auctionMap->removeItem(vendor, vuid, item);

			ObjectManager::instance()->destroyObjectFromDatabase(item->_getObjectID());
		}
	}
}

void AuctionManagerImplementation::checkAuctions() {

	CheckAuctionsTask* task = new CheckAuctionsTask(_this.get());
	task->schedule(CHECKEVERY * 60 * 1000);

	SortedVector<ManagedReference<AuctionItem* > > items = auctionMap->getBazaarItems(NULL, "", "");

	info("Checking " + String::valueOf(items.size()) + " bazaar items");

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = currentTime + 2592000;

	for (int i = 0; i < items.size(); ++i) {
		ManagedReference<AuctionItem*> item = items.get(i);
		if (item == NULL)
			continue;

		ManagedReference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());
		uint64 objectId = item->getAuctionedItemObjectID();

		if (vendor == NULL)
			continue;

		String vuid = getVendorUID(vendor);

		Locker _ilocker(item);

		if (item->getExpireTime() <= currentTime) {
			if (item->isSold()) {
				auctionMap->removeItem(vendor, vuid, item);

				ObjectManager::instance()->destroyObjectFromDatabase(item->_getObjectID());
			} else {
				ChatManager* cman = zoneServer->getChatManager();

				String sender = "auctioner";

				// retrieve failed auctions for owner
				if (item->getBidderName().length() < 1) {
					item->setBuyerID(item->getOwnerID());
					item->setBidderName(item->getOwnerName());

					UnicodeString subject("@auction:subject_auction_unsuccessful");
					StringIdChatParameter body("@auction:seller_fail");
					body.setTO(item->getItemName());

					cman->sendMail(sender, subject, body, item->getOwnerName());

					// bidder won auction. handle transactions and send messages
				} else {
					PlayerManager* pman = zoneServer->getPlayerManager();
					ManagedReference<CreatureObject*> player = pman->getPlayer(item->getOwnerName());

					if (player != NULL) {
						Locker _locker(player);
						player->addBankCredits(item->getPrice());
						player->updateToDatabase();
					}

					UnicodeString subject1("@auction:subject_auction_seller");
					UnicodeString subject2("@auction:subject_auction_buyer");

					StringIdChatParameter body1("@auction:seller_success");
					body1.setTO(item->getItemName());
					body1.setTT(item->getBidderName());
					body1.setDI(item->getPrice());

					cman->sendMail(sender, subject1, body1, item->getOwnerName());

					// Waypoint to Vendor / bazaar
					float waypointX = vendor->getWorldPositionX();
					float waypointY = vendor->getWorldPositionY();

					ManagedReference<WaypointObject*> waypoint = cast<WaypointObject*>(zoneServer->createObject(0xc456e788, 1));
					waypoint->setPlanetCRC(vendor->getPlanetCRC());
					waypoint->setPosition(waypointX, 0, waypointY);

					waypoint->setCustomObjectName(vendor->getDisplayedName(), false);

					StringIdChatParameter body2("@auction:buyer_success");
					body2.setTO(item->getItemName());
					body2.setTT(item->getBidderName());
					body2.setDI(item->getPrice());

					cman->sendMail(sender, subject2, body2, item->getBidderName(), waypoint);

					item->setOwnerID(item->getBuyerID());
					item->setOwnerName(item->getBidderName());
				}

				// move to available items / stockroom
				item->setSold(true);
				item->setInStockroom(true);
				item->setExpireTime(availableTime);
				item->setBuyerID(item->getOwnerID());
				item->clearAuctionWithdraw(); // This will pervent it from being retrieved. Clear the flag.

			}
		}

		if (item->isRemovedByOwner() && !item->isInStockroom()) {
			//If this condition has been reached, the item has been removed from the db in retriveItem()
			auctionMap->removeItem(vendor, vuid, item);

			ObjectManager::instance()->destroyObjectFromDatabase(item->_getObjectID());
		}
	}
}

void AuctionManagerImplementation::addSaleItem(CreatureObject* player, uint64 objectid, TangibleObject* vendor, const UnicodeString& description, int price, uint32 duration, bool auction, bool premium) {

	if (vendor == NULL || (!vendor->isVendor() && !vendor->isBazaarTerminal())) {
		error("terminal is not a valid vendor object");
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::VENDORNOTWORKING);
		player->sendMessage(soldMessage);
		return;
	}

	ManagedReference<AuctionItem*> oldItem = auctionMap->getItem(objectid);
	ManagedReference<SceneObject*> objectToSell = zoneServer->getObject(objectid);

	if(oldItem == NULL) {
		if (objectToSell == NULL || !objectToSell->isASubChildOf(player) || objectToSell->isNoTrade()) {
			error("trying to add invalid object");
			ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::INVALIDITEM);
			player->sendMessage(soldMessage);
			return;
		}
	} else {
		/// Is on offer on the vendor
		if (oldItem->getBuyerID() != player->getObjectID()) {
			error("trying to add invalid object");
			ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::INVALIDITEM);
			player->sendMessage(soldMessage);
			return;
		}
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

	String vendorUID = getVendorUID(vendor);

	int result = auctionMap->addItem(vendor, vendorUID, item);

	if(result != ItemSoldMessage::SUCCESS) {
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, result);
		player->sendMessage(soldMessage);
		return;
	}

	if(oldItem != NULL) {
		auctionMap->removeItem(vendor, vendorUID, oldItem);
		ObjectManager::instance()->destroyObjectFromDatabase(oldItem->_getObjectID());
	}

	objectToSell->destroyObjectFromWorld(true);

	if (vendor->isBazaarTerminal()) {
		StringIdChatParameter str("@base_player:sale_fee");

		float costReduction = 1;
		if(player->hasSkill("crafting_merchant_sales_1"))
				costReduction = .80f;
		if(player->hasSkill("crafting_merchant_sales_3"))
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

	if (item->isOfferToVendor()) {

		VendorDataComponent* vendorData = NULL;
		DataObjectComponentReference* data = vendor->getDataObjectComponent();
		if(data != NULL && data->get() != NULL && data->get()->isVendorData())
			vendorData = cast<VendorDataComponent*>(data->get());

		if(vendorData != NULL) {
			error("null vendor data on offer");
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

	BaseMessage* msg = new ItemSoldMessage(objectid, 0);
	player->sendMessage(msg);

}

String AuctionManagerImplementation::getVendorUID(SceneObject* vendor) {

	//planet.region.vendorname.oid#x,y

	if(vendor->getZone() == NULL) {
		error("no zone for our poor vendor");
		return "nozone.nozone.sadpandavendor." + String::valueOf(vendor->getObjectID()) + "#0,0";
	}

	String UID = "error.error.errorvendor." + String::valueOf(vendor->getObjectID()) + "#0,0";

	if(vendor->isBazaarTerminal()) {

		UID = vendor->getZone()->getZoneName() + ".";

		String region = vendor->getZone()->getZoneName();
		ManagedReference<CityRegion*> cityRegion = vendor->getCityRegion();
		if(cityRegion != NULL)
			region = cityRegion->getRegionName();

		UID += region + "." + vendor->getDisplayedName() + "#";
		UID += String::valueOf(vendor->getPositionX()) + "," + String::valueOf(vendor->getPositionY());

	} else if(vendor->isVendor()) {
		VendorDataComponent* vendorData = NULL;
		DataObjectComponentReference* data = vendor->getDataObjectComponent();
		if(data != NULL && data->get() != NULL && data->get()->isVendorData())
			vendorData = cast<VendorDataComponent*>(data->get());

		if(vendorData != NULL)
			UID = vendorData->getUID();
	} else {
		error("wasn't a vendor or bazaar");
	}

	return UID;
}

int AuctionManagerImplementation::checkSaleItem(CreatureObject* player, SceneObject* object, TangibleObject* vendor, int price, bool premium) {

	if(vendor == NULL) {
		error("NULL Vendor");
		return ItemSoldMessage::UNKNOWNERROR;
	}

	if (price < 1)
		return ItemSoldMessage::INVALIDSALEPRICE;

	if(vendor->isVendor()) {

		VendorDataComponent* vendorData = NULL;
		DataObjectComponentReference* data = vendor->getDataObjectComponent();
		if(data != NULL && data->get() != NULL && data->get()->isVendorData())
			vendorData = cast<VendorDataComponent*>(data->get());

		if (player->getObjectID() == vendorData->getOwnerId()) {
			if (auctionMap->getVendorItemCount(player->getPlayerObject()) >= player->getSkillMod("vendor_item_limit"))
				return ItemSoldMessage::TOOMANYITEMS;
		}

		if (price > MAXVENDORPRICE)
			return ItemSoldMessage::INVALIDSALEPRICE;
	}

	if(vendor->isBazaarTerminal()) {
		if (auctionMap->getBazaarItemCount(player->getPlayerObject()) >= MAXSALES)
			return ItemSoldMessage::TOOMANYITEMS;

		if (price > MAXBAZAARPRICE)
			return ItemSoldMessage::INVALIDSALEPRICE;

		if (player->getBankCredits() < SALESFEE)
			return ItemSoldMessage::NOTENOUGHCREDITS;

		if (premium && player->getBankCredits() < SALESFEE * 5)
			return ItemSoldMessage::NOTENOUGHCREDITS;

	}
	return 0;
}

AuctionItem* AuctionManagerImplementation::createVendorItem(CreatureObject* player, SceneObject* objectToSell, TangibleObject* vendor, const UnicodeString& description, int price, unsigned int duration, bool auction, bool premium) {

	Zone* zone = vendor->getZone();

	if (zone == NULL)
		return NULL;

	Time expireTime;
	expireTime.addMiliTime(duration * 1000);
	uint64 expire = expireTime.getMiliTime() / 1000;

	String playername = player->getFirstName().toLowerCase();
	String descr = description.toString();
	String planetStr = zone->getZoneName();

	AuctionItem* item  = new AuctionItem(objectToSell->getObjectID());

	item->setPlanet(planetStr);

	ManagedReference<CityRegion*> cityRegion = vendor->getCityRegion();
	String region = "";

	if (cityRegion != NULL)
		region = cityRegion->getRegionName();

	StringId* objectName = objectToSell->getObjectName();

	String name = objectToSell->getCustomObjectName().toString();

	if (name.length() < 2)
		objectName->getFullPath(name);

	//printf("planet:%s region:%s\n", planetStr.toCharArray(), region.toCharArray());

	item->setLocation(planetStr, region, vendor->getObjectID(), (int)vendor->getWorldPositionX(), (int)vendor->getWorldPositionY(), !vendor->isBazaarTerminal());

	if (premium)
		item->setAuctionPremium();

	item->setVendorID(vendor->getObjectID());
	item->setOwnerID(player->getObjectID());
	item->setOwnerName(playername);
	item->setItemName(name);
	item->setItemDescription(description.toString());
	item->setItemType(objectToSell->getClientGameObjectType());
	item->setPrice(price);
	item->setAuction(auction);
	item->setSold(false);
	item->setInStockroom(false);
	item->setRemovedByOwner(false);
	item->setExpireTime(expire);
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
			item->setOfferToVendor(true);
			item->setOfferToID(vendorData->getOwnerId());
		}
	}

	if (vendor->isBazaarTerminal()) {
		item->setOnBazaar(true);
	}

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

void AuctionManagerImplementation::doInstantBuy(CreatureObject* player, AuctionItem* item, int price1, int price2) {
	ManagedReference<SceneObject*> vendor = zoneServer->getObject(item->getVendorID());
	if (vendor == NULL)
		return;

	String playername = player->getFirstName().toLowerCase();

	ChatManager* cman = zoneServer->getChatManager();
	PlayerManager* pman = zoneServer->getPlayerManager();

	String sender = "auctioner";

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = currentTime + 2592000;

	item->setSold(true);
	item->setExpireTime(availableTime);
	item->setBuyerID(player->getObjectID());
	item->setBidderName(playername);

	player->subtractBankCredits(price1);

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
		body2.setTT(item->getOwnerName());
		body2.setDI(item->getPrice());

		//Send the Mail
		cman->sendMail(sender, subject1, body1, item->getOwnerName());
		cman->sendMail(sender, subject2, body2, item->getBidderName(), waypoint);

	} else {

		// Setup the mail to the seller
		UnicodeString subject1("@auction:subject_instant_seller");
		StringIdChatParameter body1("@auction:seller_success");
		body1.setTO(item->getItemName());
		body1.setTT(item->getBidderName());
		body1.setDI(price1);

		// Setup the mail to the buyer
		UnicodeString subject2("@auction:subject_instant_buyer");
		StringIdChatParameter body2("@auction:buyer_success");
		body2.setTO(item->getItemName());
		body2.setTT(item->getOwnerName());
		body2.setDI(price1);


		//Send the Mail
		cman->sendMail(sender, subject1, body1, item->getOwnerName());
		cman->sendMail(sender, subject2, body2, item->getBidderName(), waypoint);

	}

	if(item->isOfferToVendor()) {
		item->setRemovedByOwner(true);
		item->clearAuctionWithdraw();
	}

	// pay the seller
	ManagedReference<CreatureObject*> seller = pman->getPlayer(item->getOwnerName());

	if (seller == NULL) {
		error("seller null for name " + item->getOwnerName());
		return;
	}

	Locker clocker(seller, player);

	seller->addBankCredits(price1);

}

void AuctionManagerImplementation::doAuctionBid(CreatureObject* player, AuctionItem* item, int price1, int price2) {
	String playername = player->getFirstName().toLowerCase();

	ChatManager *cman = zoneServer->getChatManager();
	PlayerManager *pman = zoneServer->getPlayerManager();
	// don't allow owner or last bidder bid on the item.  don't allow old auction info
	// send auctioner invalid message
	if (playername == item->getBidderName() || playername == item->getOwnerName() || price1 <= item->getPrice()) {
		BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), 1);
		player->sendMessage(msg);
		return;
	}

	// send prior bidder their money back
	if (item->getBidderName().length() > 0) {
		ManagedReference<CreatureObject*> priorBidder = pman->getPlayer(item->getBidderName());

		StringIdChatParameter body("@auction:bidder_outbid");
		body.setTO(item->getItemName());

		if (priorBidder != NULL) {
			Locker clocker(priorBidder, player);

			priorBidder->sendSystemMessage(body);
			priorBidder->addBankCredits(item->getPrice());

			clocker.release();
		}

		// mail prior bidder with outcome
		UnicodeString subject("@auction:subject_auction_outbid");

		cman->sendMail("auctioner", subject, body, item->getBidderName());
		item->setPrice(price1);
		item->setBuyerID(player->getObjectID());
		item->setBidderName(playername);

		// take money from high bidder
		player->subtractBankCredits(price1);

		// no prior bidder, just take the money
	} else {
		item->setPrice(price1);
		item->setBuyerID(player->getObjectID());
		item->setBidderName(playername);

		player->subtractBankCredits(price1);
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

	if (item->isSold()) {
		BaseMessage* msg = new BidAuctionResponseMessage(objectid, BidAuctionResponseMessage::INVALIDITEM);
		player->sendMessage(msg);
		return;
	}

	if (item->getOwnerID() == player->getObjectID()) {
		BaseMessage* msg = new BidAuctionResponseMessage(objectid, BidAuctionResponseMessage::PURCHASEFAILED);
		player->sendMessage(msg);
		return;
	}

	int res = checkBidAuction(player, item, price1, price2);

	if (res != 0) {
		BaseMessage* msg = new BidAuctionResponseMessage(objectid, res);
		player->sendMessage(msg);
		return;
	}

	if (!item->isAuction()) { // Instant buy
		doInstantBuy(player, item, price1, price2);
	} else { // For Auction Bids
		doAuctionBid(player, item, price1, price2);
	}

}


int AuctionManagerImplementation::checkRetrieve(CreatureObject* player, uint64 objectIdToRetrieve, SceneObject* vendor) {
    // Check both Bazaar and Vendors

	if (!auctionMap->containsItem(objectIdToRetrieve))
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;

	SceneObject* inventory = player->getSlottedObject("inventory");

	if (inventory->hasFullContainerObjects())
		return RetrieveAuctionItemResponseMessage::FULLINVENTORY;

	ManagedReference<AuctionItem*> item = auctionMap->getItem(objectIdToRetrieve);
	if (item == NULL) {
		error("Null item in checkRetrieve");
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;
	}

	String playername = player->getFirstName();

	// only the owner can yank his own auction off the vendor
	if (!item->isSold() && (playername.toLowerCase() != item->getOwnerName().toLowerCase()))
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;

	// the bidder is the only one who can get his auction after expiration
	if (item->isSold() && item->getBuyerID() != player->getObjectID())
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;

	// Only BazaarTerminals use regions
	if (vendor->isBazaarTerminal()) {
		ManagedReference<CityRegion*> region = vendor->getCityRegion();

		if (region != NULL) {
			String regionName = region->getRegionName();
			//String region = terminal->getBazaarRegion();

			if (item->getLocation().indexOf(regionName) == -1) {
				return RetrieveAuctionItemResponseMessage::NOTALLOWED;
			}
		} else {
			StringBuffer msg;
			msg << "null area for bazaar terminal at" << vendor->getPositionX() << " " << vendor->getPositionY() << " zone " << vendor->getZone()->getZoneName();
			error(msg);
		}
	}

	return 0;
}

void AuctionManagerImplementation::refundAuction(AuctionItem* item) {
	PlayerManager* pman = zoneServer->getPlayerManager();
	ManagedReference<CreatureObject*> bidder = pman->getPlayer(item->getBidderName());
	ChatManager* cman = zoneServer->getChatManager();

	// send the player a mail and system message
	UnicodeString subject("@auction:subject_auction_cancelled");
	StringIdChatParameter body("auction", "buyer_canceled" );
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

	VendorDataComponent* vendorData = NULL;
	DataObjectComponentReference* data = vendor->getDataObjectComponent();
	if(data != NULL && data->get() != NULL && data->get()->isVendorData())
		vendorData = cast<VendorDataComponent*>(data->get());


	int res = checkRetrieve(player, objectid, vendor);

	if (res != 0) {
		msg = new RetrieveAuctionItemResponseMessage(objectid, res);
		player->sendMessage(msg);
		return;
	}

	ManagedReference<AuctionItem*> item = auctionMap->getItem(objectid);
	if (item == NULL) {
		error("NULL item in retrieveItem()");
		return;
	}

	// refund money to bidder for sniping the auction
	if (!item->isSold() && item->getBidderName().length() > 0) {
		refundAuction(item);
	}

	ManagedReference<SceneObject*> objectToRetrieve = zoneServer->getObject(objectid);

	if (objectToRetrieve == NULL) {
		error("null objectToRetrieve in retrieveItem()");
		msg = new RetrieveAuctionItemResponseMessage(objectid, 0);
		player->sendMessage(msg);
		return;
	}

	if (item->isOfferToVendor() && item->getOwnerID() != player->getObjectID()
			&& vendorData != NULL && vendorData->isVendorOwner(player)) {
		item->setOfferToVendor(false);
		item->setInStockroom(true);
		item->setOwnerID(player->getObjectID());
		msg = new RetrieveAuctionItemResponseMessage(objectid, 0);
		player->sendMessage(msg);
		return;
	}

	SceneObject* inventory = player->getSlottedObject("inventory");
	inventory->transferObject(objectToRetrieve, -1, false);
	inventory->broadcastObject(objectToRetrieve, true);

	//TODO: CHANGE THIS VAR TO MAKE MORE SENSE
	item->setRemovedByOwner(true);
	item->setInStockroom(false);

	String vuid = getVendorUID(vendor);
	auctionMap->removeItem(vendor, vuid, item);

	ObjectManager::instance()->destroyObjectFromDatabase(item->_getObjectID());

	msg = new RetrieveAuctionItemResponseMessage(objectid, 0);
	player->sendMessage(msg);
}

AuctionQueryHeadersResponseMessage* AuctionManagerImplementation::fillAuctionQueryHeadersResponseMessage(CreatureObject* player, TangibleObject* vendor, SortedVector<ManagedReference<AuctionItem*> >* items, int screen, uint32 category, int count, int offset) {
	AuctionQueryHeadersResponseMessage* reply = new AuctionQueryHeadersResponseMessage(screen, count, player);

	int displaying = 0;
	String pname = player->getFirstName().toLowerCase();

	/*System::out << "Screen =" + String::valueOf(screen) << endl;
	System::out << "Category =" + String::valueOf(category) << endl;
	System::out << "VendorItemSize =" + String::valueOf(auctionMap->getVendorItemCount()) << endl;
	System::out << "AuctionItemSize =" + String::valueOf(auctionMap->getAuctionCount()) << endl;
	System::out << "______________________________" << endl;*/

	VendorDataComponent* vendorData = NULL;
	DataObjectComponentReference* data = vendor->getDataObjectComponent();
	if(data != NULL && data->get() != NULL && data->get()->isVendorData())
		vendorData = cast<VendorDataComponent*>(data->get());

	switch(screen) {
	case 2: // All Auctions (Bazaar)
		for (int i = 0; (i < items->size()) && (displaying < (offset + 100)); i++) {
			AuctionItem* item = items->get(i);

			if (!item->isSold() && !item->isRemovedByOwner()) {
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
				}
			}
		}

		break;
	case 3: // My auctions/sales
		for (int i = 0; i < items->size(); i++) {
			if ((items->get(i)->getOwnerID() == player->getObjectID()) && !items->get(i)->isSold()
					&& !items->get(i)->isRemovedByOwner()) {
				// if the player is the owner of the item. give them the withdraw option.
				/*if (items->get(i)->getOwnerID() == player->getObjectID())
					items->get(i)->setAuctionWithdraw();
				else
					items->get(i)->clearAuctionWithdraw();*/

				reply->addItemToList(items->get(i));
			}
		}

		break;
	case 4: // My Bids
		for (int i = 0; i < items->size(); i++) {
			if ((items->get(i)->getBidderName() == pname) && !items->get(i)->isSold())
				reply->addItemToList(items->get(i));
		}

		break;
	case 5: // Retrieve items screen
		for (int i = 0; i < items->size(); i++) {
			if (items->get(i)->isSold() && items->get(i)->getBuyerID() == player->getObjectID())
				reply->addItemToList(items->get(i));

			else if (items->get(i)->isRemovedByOwner() && items->get(i)->getOwnerID() == player->getObjectID())
				reply->addItemToList(items->get(i));
		}

		break;
	case 6: // Offers to Vendor (owner)
		for (int i = 0; i < items->size(); i++) {
			AuctionItem* item = items->get(i);
			if (!item->isSold() && !item->isRemovedByOwner() && item->isOfferToVendor() && item->getOfferToID() == player->getObjectID())
				reply->addItemToList(items->get(i));
		}
		break;
	case 7: // Vendor items screen (including Vendor location search)
		for (int i = 0; (i < items->size()) && (displaying < (offset + 100)); i++) {
			AuctionItem* item = items->get(i);

			// This stops from seeing other ppl's items when searching entire galaxy from player's vendor.
			if (!item->isSold() && !item->isRemovedByOwner() && !item->isOfferToVendor() && !item->isInStockroom()) {

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
				} else if (category == 0) { // Searching all items
					if (displaying >= offset)
						reply->addItemToList(items->get(i));

					displaying++;
				}
			}
		}

		break;
	case 8: // Stockroom
		for (int i = 0; i < items->size(); i++) {
			if (items->get(i)->isInStockroom() && items->get(i)->getOwnerID() == player->getObjectID()
					&& !items->get(i)->isOnBazaar() && !items->get(i)->isOfferToVendor())
				reply->addItemToList(items->get(i));
		}
		break;
	case 9: // Offers to vendor (not the Owner)
		for (int i = 0; i < items->size(); i++) {
			AuctionItem* item = items->get(i);
			if (!item->isSold() && !item->isRemovedByOwner() && item->isOfferToVendor()
					&& item->getOwnerID() == player->getObjectID())
				reply->addItemToList(items->get(i));
		}
		break;
	}

	if (displaying == (offset + 100))
		reply->createMessage(offset, true);
	else
		reply->createMessage(offset);

	return reply;
}

void AuctionManagerImplementation::getData(CreatureObject* player, int extent, uint64 vendorObjectID, int screen, unsigned int category, int clientcounter, int offset) {
	ManagedReference<TangibleObject*> vendor = cast<TangibleObject*>(zoneServer->getObject(vendorObjectID));

	if (vendor == NULL || (!vendor->isVendor() && !vendor->isBazaarTerminal())) {
		error("null vendor in getData()");
		return;
	}

	ManagedReference<SceneObject*> parent = vendor->getRootParent();

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
	if (!vendor->isBazaarTerminal()) {

		DataObjectComponentReference* data = vendor->getDataObjectComponent();
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

	String searchQuery = "";

	switch (extent) {
	case 0:
		break;
	case 1:
		searchQuery = player->getZone()->getZoneName();
		break;
	case 2:
		if(player->getCityRegion() != NULL) {
			searchQuery = player->getZone()->getZoneName();
			searchQuery += "." + player->getCityRegion().get()->getRegionName();
		} else {
			searchQuery = getVendorUID(vendor);
		}
		break;
	case 3:
		searchQuery = getVendorUID(vendor);
		break;
	default:
		break;
	}

	getAuctionData(player, vendor, searchQuery, screen, category, clientcounter, offset);

}

void AuctionManagerImplementation::getAuctionData(CreatureObject* player, TangibleObject* vendor, String& search, int screen, uint32 category, int clientcounter, int offset) {

	SortedVector<ManagedReference<AuctionItem* > > items;
	String vuid = getVendorUID(vendor);

	if (vendor->isBazaarTerminal() && screen != 7) { // This is to prevent bazaar items from showing on Vendor Search
		items = auctionMap->getBazaarItems(vendor, vuid, search);
	} else {
		items = auctionMap->getVendorItems(vendor, vuid, search);
	}

	AuctionQueryHeadersResponseMessage* msg = fillAuctionQueryHeadersResponseMessage(player, vendor, &items, screen, category, clientcounter, offset);
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
		TangibleObject* tano = cast<TangibleObject*>(object.get());
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

	if ((!item->isOfferToVendor()) && item->getOwnerID() != player->getObjectID()) {
		error("not the owner of the item in cancelItem()");
		BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, CancelLiveAuctionResponseMessage::NOTOWNER);
		player->sendMessage(msg);
		return;
	}

	if (item->getExpireTime() <= 0) {
		BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, CancelLiveAuctionResponseMessage::ALREADYCOMPLETED);
		player->sendMessage(msg);
		return;
	}

	if (item->isSold()) {
		BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, CancelLiveAuctionResponseMessage::ALREADYCOMPLETED);
		player->sendMessage(msg);
		return;
	}

	Locker _locker(item);

	if(item->isOfferToVendor()) {

		Time expireTime;
		uint64 currentTime = expireTime.getMiliTime() / 1000;
		uint64 availableTime = currentTime + 2592000;

		item->setSold(true);
		item->setRemovedByOwner(true);
		item->setExpireTime(availableTime);
		item->setBuyerID(item->getOwnerID());
		item->setBidderName(item->getOwnerName());
		item->clearAuctionWithdraw();

	} else {

		Time expireTime;
		uint64 currentTime = expireTime.getMiliTime() / 1000;
		uint64 availableTime = currentTime + 2592000;

		// remove from the sale item list
		item->setRemovedByOwner(true);
		item->setInStockroom(true);
		item->clearAuctionWithdraw();
		item->setExpireTime(availableTime);
	}

	BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, 0);
	player->sendMessage(msg);

}
