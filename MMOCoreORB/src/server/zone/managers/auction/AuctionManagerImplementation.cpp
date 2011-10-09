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
#include "server/zone/objects/tangible/terminal/vendor/bazaar/BazaarTerminal.h"
#include "server/zone/objects/tangible/terminal/vendor/VendorTerminal.h"
#include "server/zone/objects/creature/vendor/VendorCreature.h"
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

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/chat/ChatManager.h"
#include "CheckAuctionsTask.h"
#include "server/zone/managers/vendor/VendorManager.h"

void AuctionManagerImplementation::initialize() {
	auctionMap = new AuctionsMap();

	ObjectDatabase* auctionDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("auctions", true);
	ObjectDatabaseManager::instance()->commitLocalTransaction();

	ObjectDatabaseIterator iterator(auctionDatabase);

	uint64 objectID = 0;

	while (iterator.getNextKey(objectID)) {
		AuctionItem* auctionItem = cast<AuctionItem*>(Core::getObjectBroker()->lookUp(objectID));
		ObjectDatabaseManager::instance()->commitLocalTransaction();

		if (auctionItem->isOnBazaar())
			auctionMap->addBazaarItem(auctionItem->getAuctionedItemObjectID(), auctionItem);
		else
			auctionMap->addVendorItem(auctionItem->getAuctionedItemObjectID(), auctionItem);
	}

	checkAuctions();
}

void AuctionManagerImplementation::checkVendorItems() {
	Locker _locker(_this);

	info("Checking " + String::valueOf(auctionMap->getVendorItemCount()) + " vendor items");

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = currentTime + 2592000;

	for (int i = 0; i < auctionMap->getVendorItemCount(); ++i) {
		ManagedReference<AuctionItem*> item = NULL;

		item = auctionMap->getVendorItem(i);

		if (item == NULL)
			continue;

		ManagedReference<SceneObject*> vendorRef = zoneServer->getObject(item->getVendorID());
		uint64 objectId = item->getAuctionedItemObjectID();

		if (vendorRef == NULL)
			continue;

		Vendor* vendor = getVendorFromObject(vendorRef);

		if (vendor == NULL)
			continue;

		Locker _ilocker(item);

		Locker _vlocker(vendorRef);

		if (item->getExpireTime() <= currentTime) {
			if (item->isInStockroom()) {
				auctionMap->dropVendorItem(objectId);
				vendor->dropVendorItem(objectId);

				ObjectManager::instance()->destroyObjectFromDatabase(item->_getObjectID());
			} else {
				ChatManager* cman = zoneServer->getChatManager();

				//Send the mail to the vendor owner
				String sender = "auctioner";

				/*PlayerManager* pman = zoneServer->getPlayerManager();
				ManagedReference<CreatureObject*> seller = pman->getPlayer(item->getOwnerName());

				if (seller)
				Locker _locker(seller);*/

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
			auctionMap->dropVendorItem(objectId);
			vendor->dropVendorItem(objectId);

			ObjectManager::instance()->destroyObjectFromDatabase(item->_getObjectID());
		}
	}
}

void AuctionManagerImplementation::checkAuctions() {
	// Check Vendors
	checkVendorItems();

	Locker _locker(_this);

	info("Checking " + String::valueOf(auctionMap->getAuctionCount()) + " bazaar items");

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = currentTime + 2592000;

	for (int i = 0; i < auctionMap->getAuctionCount(); ++i) {
		ManagedReference<AuctionItem*> item = NULL;

		item = auctionMap->getBazaarItem(i);

		if (item == NULL)
			continue;

		ManagedReference<SceneObject*> vendorRef = zoneServer->getObject(item->getVendorID());
		uint64 objectId = item->getAuctionedItemObjectID();

		if (vendorRef == NULL)
			continue;

		Vendor* vendor = getVendorFromObject(vendorRef);

		if (vendor == NULL)
			continue;

		Locker _ilocker(item);
		Locker _vlocker(vendorRef);

		if (item->getExpireTime() <= currentTime) {
			if (item->isSold()) {
				auctionMap->dropBazaarItem(objectId);
				vendor->dropVendorItem(objectId);

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

					Locker _locker(player);
					player->addBankCredits(item->getPrice());
					player->updateToDatabase();

					UnicodeString subject1("@auction:subject_auction_seller");
					UnicodeString subject2("@auction:subject_auction_buyer");

					StringIdChatParameter body1("@auction:seller_success");
					body1.setTO(item->getItemName());
					body1.setTT(item->getBidderName());
					body1.setDI(item->getPrice());

					cman->sendMail(sender, subject1, body1, item->getOwnerName());

					// Waypoint to Vendor / bazaar
					float waypointX = vendorRef->getWorldPositionX();
					float waypointY = vendorRef->getWorldPositionY();

					ManagedReference<WaypointObject*> waypoint = cast<WaypointObject*>(zoneServer->createObject(0xc456e788, 1));
					waypoint->setPlanetCRC(vendorRef->getPlanetCRC());
					waypoint->setPosition(waypointX, 0, waypointY);

					waypoint->setCustomName(vendorRef->getObjectName()->getDisplayedName());

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
			auctionMap->dropBazaarItem(objectId);
			vendor->dropVendorItem(objectId);

			ObjectManager::instance()->destroyObjectFromDatabase(item->_getObjectID());
		}
	}

	CheckAuctionsTask* task = new CheckAuctionsTask(_this);
	task->schedule(CHECKEVERY * 60000);
}

int AuctionManagerImplementation::checkSaleItem(CreatureObject* player, SceneObject* object, Vendor* vendor, int price) {
	if (player->getObjectID() == vendor->getOwnerID()) {
		if (auctionMap->getPlayerVendorItemCount(player->getObjectID()) >= player->getSkillMod("vendor_item_limit") && !vendor->isBazaarTerminal())
			return ItemSoldMessage::TOOMANYITEMS;
	}

	if (auctionMap->getPlayerAuctionCount(player->getObjectID()) >= MAXSALES && vendor->isBazaarTerminal())
		return ItemSoldMessage::TOOMANYITEMS;

	if ((auctionMap->containsAuction(object->getObjectID()) || auctionMap->containsVendorItem(object->getObjectID()))
			&& !auctionMap->checkInStockroom(object->getObjectID()))
		return ItemSoldMessage::ALREADYFORSALE;

	if (price > vendor->getMaxPrice())
		return ItemSoldMessage::INVALIDSALEPRICE;

	if (price < 1)
		return ItemSoldMessage::INVALIDSALEPRICE;

	if (player->getBankCredits() < SALESFEE && vendor->isBazaarTerminal())
		return ItemSoldMessage::NOTENOUGHCREDITS;

	return 0;
}

void AuctionManagerImplementation::addSaleItem(CreatureObject* player, uint64 objectid, Vendor* vendor, const UnicodeString& description, int price, uint32 duration, bool auction, bool premium) {
	Locker _locker(_this);

	Locker _locker2(player); // no cross lock because we never lock bazaar manager after locking player?

	ManagedReference<SceneObject*> terminal = vendor->getVendor();

	if (terminal == NULL)
		return;

	if (!terminal->isVendor() || terminal == NULL) {
		error("terminal is not a valid vendor object");
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::VENDORNOTWORKING);
		player->sendMessage(soldMessage);
		return;
	}

	//TODO: ADD MERCHANT SKILL CHECKS!

	ManagedReference<SceneObject*> objectToSell = zoneServer->getObject(objectid);

	if (objectToSell == NULL) {
		error("trying to add null object to the vendor");
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::NOTOWN);
		player->sendMessage(soldMessage);
		return;
	}

	ManagedReference<SceneObject*> toSellParent = objectToSell->getParent();

	if (toSellParent == NULL) {
		error("trying to add an object with a NULL parent.");
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::NOTOWN);
		player->sendMessage(soldMessage);
		return;
	}

	if (!toSellParent->isContainerObject() && !auctionMap->containsAuction(objectToSell->getObjectID()) && !auctionMap->containsVendorItem(objectToSell->getObjectID())) {
		error("trying to add object to the vendor that is not in a valid container");
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::NOTOWN);
		player->sendMessage(soldMessage);
		return;
	}

	if (!objectToSell->isTangibleObject()) {
		error("trying to add a non tangible object to the bazaar");
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::INVALIDITEM);
		player->sendMessage(soldMessage);
		return;
	}

	if (objectToSell->isVendor() || objectToSell->isCreatureObject()) {
		error("trying to add a vendor / creature to the vendor");
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::INVALIDITEM);
		player->sendMessage(soldMessage);
		return;
	}

	Zone* zone = terminal->getZone();

	if (zone == NULL) {
		error("null vendor zone");
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::UNKNOWNERROR);
		player->sendMessage(soldMessage);
		return;
	}


	int res = checkSaleItem(player, objectToSell, vendor, price);

	if (res != 0) {
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, res);
		player->sendMessage(soldMessage);
		return;
	}

	if (auctionMap->containsVendorItem(objectToSell->getObjectID())) {
		auctionMap->dropVendorItem(objectToSell->getObjectID());
		vendor->dropVendorItem(objectToSell->getObjectID());
	}

	AuctionItem* item = createVendorItem(player, objectToSell.get(), vendor, description, price, duration, auction, premium);

	Locker _vlocker(terminal);

	vendor->addVendorItem(item);

	if (vendor->isBazaarTerminal())
		auctionMap->addBazaarItem(objectid, item);
	else
		auctionMap->addVendorItem(objectid, item);

	objectToSell->sendDestroyTo(player);
	toSellParent->removeObject(objectToSell, true);
	terminal->addObject(objectToSell, -1, false);

	if (vendor->isBazaarTerminal()) {
		StringIdChatParameter str("@base_player:sale_fee");

		if (item->isPremiumAuction()) {
			player->substractBankCredits(SALESFEE * 5);
			str.setDI(SALESFEE);

		} else {
			player->substractBankCredits(SALESFEE);
			str.setDI(SALESFEE);
		}

		//str.setUnknownByte(1);

		player->sendSystemMessage(str);

	}

	if (item->isOfferToVendor()) {
		ManagedReference<SceneObject*> strongRef =  zoneServer->getObject(vendor->getOwnerID());

		if (strongRef == NULL || !strongRef->isPlayerCreature()) {
			ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::UNKNOWNERROR);
			player->sendMessage(soldMessage);
			return;
		}

		ManagedReference<CreatureObject*> strongOwnerRef = cast<CreatureObject*>(strongRef.get());
		strongOwnerRef->sendSystemMessage(player->getFirstName() + " has offered an item to " + terminal->getObjectName()->getDisplayedName());
	}

	BaseMessage* msg = new ItemSoldMessage(objectid, 0);
	player->sendMessage(msg);

}

int AuctionManagerImplementation::checkBidAuction(CreatureObject* player, AuctionItem* item, int price1, int price2) {
	if ((price1 > MAXPRICE || price2 > MAXPRICE) && item->isOnBazaar()) {
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
	ManagedReference<SceneObject*> vendorRef = zoneServer->getObject(item->getVendorID());
	if (vendorRef == NULL)
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

	player->substractBankCredits(price1);

	BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), 0);
	player->sendMessage(msg);

	// Waypoint to Vendor / bazaar
	float waypointX = vendorRef->getWorldPositionX();
	float waypointY = vendorRef->getWorldPositionY();

	ManagedReference<WaypointObject*> waypoint = cast<WaypointObject*>(zoneServer->createObject(0xc456e788, 1));
	waypoint->setPlanetCRC(vendorRef->getPlanetCRC());
	waypoint->setPosition(waypointX, 0, waypointY);

	waypoint->setCustomName(vendorRef->getObjectName()->getDisplayedName());

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
		// Setup the mail to the buyer
		UnicodeString subject1("@auction:subject_instant_buyer");
		StringIdChatParameter body1("@auction:buyer_success");
		body1.setTO(item->getItemName());
		body1.setTT(item->getOwnerName());
		body1.setDI(price1);

		// Setup the mail to the seller
		UnicodeString subject2("@auction:subject_instant_seller");
		StringIdChatParameter body2("@auction:seller_success");
		body2.setTO(item->getItemName());
		body2.setTT(item->getBidderName());
		body2.setDI(price1);

		//Send the Mail
		cman->sendMail(sender, subject1, body1, item->getOwnerName());
		cman->sendMail(sender, subject2, body2, item->getBidderName(), waypoint);

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
		player->substractBankCredits(price1);

		// no prior bidder, just take the money
	} else {
		item->setPrice(price1);
		item->setBuyerID(player->getObjectID());
		item->setBidderName(playername);

		player->substractBankCredits(price1);
	}

	BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), 0);
	player->sendMessage(msg);
}

void AuctionManagerImplementation::buyItem(CreatureObject* player, uint64 objectid, int price1, int price2) {
	Locker _locker(_this);
	Locker _locker2(player);

	ManagedReference<AuctionItem*> item = NULL;

	// We have to find the item since we don't have a Vendor Object
	item = auctionMap->getBazaarItem(objectid);

	if (item == NULL)
	// it wasn't on the bazaar.. search vendors
	item = auctionMap->getVendorItem(objectid);

	// the item wasn't found on either. it doesn't exist for sell..
	if (item == NULL) {
		BaseMessage* msg = new BidAuctionResponseMessage(objectid, BidAuctionResponseMessage::INVALIDITEM);
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


int AuctionManagerImplementation::checkRetrieve(CreatureObject* player, uint64 objectIdToRetrieve, Vendor* vendor) {
    // Check both Bazaar and Vendors
	if (!auctionMap->containsAuction(objectIdToRetrieve) && !auctionMap->containsVendorItem(objectIdToRetrieve))
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;

	SceneObject* inventory = player->getSlottedObject("inventory");

	if (inventory->hasFullContainerObjects())
		return RetrieveAuctionItemResponseMessage::FULLINVENTORY;

	ManagedReference<AuctionItem*> item = NULL;

	if (vendor->isBazaarTerminal())
		item = auctionMap->getBazaarItem(objectIdToRetrieve);
	else
		item = auctionMap->getVendorItem(objectIdToRetrieve);

	// item wasn't found on any terminal.. it doesn't exist.
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
		ManagedReference<SceneObject*> strongRef = vendor->getVendor();
		ManagedReference<CityRegion*> region = strongRef->getCityRegion();

		if (region != NULL) {
			String regionName = region->getRegionName();
			//String region = terminal->getBazaarRegion();

			if (item->getLocation().indexOf(regionName) == -1) {
				return RetrieveAuctionItemResponseMessage::NOTALLOWED;
			}
		} else {
			StringBuffer msg;
			msg << "null area for bazaar terminal at" << strongRef->getPositionX() << " " << strongRef->getPositionY() << " zone " << strongRef->getZone()->getZoneName();
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
	BaseMessage* msg = NULL;
	ManagedReference<AuctionItem*> item = NULL;

	ManagedReference<SceneObject*> terminal = zoneServer->getObject(vendorID);

	// check for valid vendor terminal
	if (terminal == NULL || !terminal->isVendor()) {
		msg = new RetrieveAuctionItemResponseMessage(objectid, RetrieveAuctionItemResponseMessage::NOTALLOWED);
		player->sendMessage(msg);
		return;
	}

	Vendor* vendor = getVendorFromObject(terminal);

	if (vendor == NULL) {
		error("null vendor in retrieveItem()");
		return;
	}

	Locker _locker(_this);
	Locker _locker2(player);

	Locker _vlocker(terminal);

	int res = checkRetrieve(player, objectid, vendor);

	if (res != 0) {
		msg = new RetrieveAuctionItemResponseMessage(objectid, res);
		player->sendMessage(msg);
		return;
	}

	if (vendor->isBazaarTerminal())
		item = auctionMap->getBazaarItem(objectid);
	else
		item = auctionMap->getVendorItem(objectid);

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

	if (item->isOfferToVendor() && item->getOwnerID() != player->getObjectID()) {
		item->setOfferToVendor(false);
		item->setInStockroom(true);
		item->setOwnerID(player->getObjectID());
		msg = new RetrieveAuctionItemResponseMessage(objectid, 0);
		player->sendMessage(msg);
		return;
	}

	terminal->removeObject(objectToRetrieve);

	objectToRetrieve->sendTo(player, true);

	SceneObject* inventory = player->getSlottedObject("inventory");
	inventory->addObject(objectToRetrieve, -1, true);

	//TODO: CHANGE THIS VAR TO MAKE MORE SENSE
	item->setRemovedByOwner(true);
	item->setInStockroom(false);

	if (item->isOnBazaar())
		auctionMap->dropBazaarItem(objectid);
	else
		auctionMap->dropVendorItem(objectid);

	vendor->dropVendorItem(objectid);

	ObjectManager::instance()->destroyObjectFromDatabase(item->_getObjectID());

	msg = new RetrieveAuctionItemResponseMessage(objectid, 0);
	player->sendMessage(msg);
}

AuctionItem* AuctionManagerImplementation::createVendorItem(CreatureObject* player, SceneObject* objectToSell, Vendor* vendor, const UnicodeString& description, int price, unsigned int duration, bool auction, bool premium) {
	ManagedReference<SceneObject*> terminal = vendor->getVendor();

	if (terminal == NULL)
		return NULL;

	Zone* zone = terminal->getZone();

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

	ManagedReference<CityRegion*> cityRegion = terminal->getCityRegion();
	String region = "";

	if (cityRegion != NULL)
		region = cityRegion->getRegionName();

	StringId* objectName = objectToSell->getObjectName();

	String name = objectName->getCustomString().toString();

	if (name.length() < 2)
		objectName->getFullPath(name);

	item->setLocation(planetStr, region, terminal->getObjectID(), (int)terminal->getWorldPositionX(), (int)terminal->getWorldPositionY(), !vendor->isBazaarTerminal());

	if (premium)
		item->setAuctionPremium();

	item->setVendorID(terminal->getObjectID());
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

	// Someone elses Vendor (making this sell item an offer)
	if (vendor->getOwnershipRightsOf(player) == 1)
		item->setOfferToVendor(true);

	if (vendor->isBazaarTerminal())
		item->setOnBazaar(true);

	ObjectManager::instance()->persistObject(item, 1, "auctions");

	return item;
}

AuctionQueryHeadersResponseMessage* AuctionManagerImplementation::fillAuctionQueryHeadersResponseMessage(CreatureObject* player, Vendor* vendor, VectorMap<unsigned long long, ManagedReference<AuctionItem*> >* items, int screen, uint32 category, int count, int offset) {
	AuctionQueryHeadersResponseMessage* reply = new AuctionQueryHeadersResponseMessage(screen, count);

	int displaying = 0;
	String pname = player->getFirstName().toLowerCase();

	/*System::out << "Screen =" + String::valueOf(screen) << endl;
	System::out << "Category =" + String::valueOf(category) << endl;
	System::out << "VendorItemSize =" + String::valueOf(auctionMap->getVendorItemCount()) << endl;
	System::out << "AuctionItemSize =" + String::valueOf(auctionMap->getAuctionCount()) << endl;
	System::out << "______________________________" << endl;*/

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
				if (items->get(i)->getOwnerID() == player->getObjectID())
					items->get(i)->setAuctionWithdraw();
				else
					items->get(i)->clearAuctionWithdraw();

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
			if (!item->isSold() && !item->isRemovedByOwner() && item->isOfferToVendor())
				reply->addItemToList(items->get(i));
		}
		break;
	case 7: // Vendor items screen (including Vendor location search)
		// TODO: Also so you cannot withdraw or retrieve your items from the bazaar terminals...
		for (int i = 0; (i < items->size()) && (displaying < (offset + 100)); i++) {
			AuctionItem* item = items->get(i);
			// This stops from seeing other ppl's items when searching entire galaxy from player's vendor.
			if (vendor->isVendorOwner(player->getObjectID())) {
				if (!item->isSold() && !item->isRemovedByOwner() && !item->isOfferToVendor() && !item->isInStockroom()) {
					// Make sure the item belogs to the owner before displaying
					if (item->getOwnerID() == player->getObjectID()) {
						item->setAuctionWithdraw();

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
			} else {
				// handles if the enable / disable of the vendor search option
				ManagedReference<SceneObject*> obj = zoneServer->getObject(item->getVendorID());
				Vendor* itemVendor = getVendorFromObject(obj);
				if (itemVendor == NULL)
					continue;

				if (vendor->isBazaarTerminal() && !itemVendor->isVendorSearchEnabled())
					continue;

				// handles displaying other users items and the bazaar vendor search...
				if (!item->isSold() && !item->isRemovedByOwner() && !item->isOfferToVendor() && !item->isInStockroom()) {
					if (item->getOwnerID() == player->getObjectID())
						item->setAuctionWithdraw();
					else
						item->clearAuctionWithdraw();

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
		}
		break;
	case 8: // Stockroom
		for (int i = 0; i < items->size(); i++) {
			if (items->get(i)->isInStockroom() && items->get(i)->getOwnerID() == player->getObjectID()
					&& !items->get(i)->isOnBazaar() && !items->get(i)->isOfferToVendor())
				reply->addItemToList(items->get(i));
		}
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

void AuctionManagerImplementation::getData(CreatureObject* player, int extent, uint64 vendorObjectID, int screen, unsigned int category, int count, int offset) {
	ManagedReference<SceneObject*> sceno = zoneServer->getObject(vendorObjectID);

	if (sceno == NULL || !sceno->isVendor()) {
		error("null vendor in getData()");
		return;
	}

	Vendor* vendor = getVendorFromObject(sceno);

	if (vendor == NULL) {
		error("null vendor in getData()");
		return;
	}

	//Handle Merchant XP for players using other players vendors...
	if (!vendor->isBazaarTerminal())
		VendorManager::instance()->handleAwardVendorLookXP(player, vendor);
	else {
		//if ()
		ManagedReference<CityRegion*> cityRegion = sceno->getCityRegion();

		if (cityRegion == NULL) {
			getGalaxyData(player, vendor, screen, category, count, offset);
			return;
		}

	}

	switch (extent) {
	case 0:
		getGalaxyData(player, vendor, screen, category, count, offset);
		break;
	case 1:
		getPlanetData(player, vendor, screen, category, count, offset);
		break;
	case 2:
		getRegionData(player, vendor, screen, category, count, offset);
		break;
	case 3:
		getLocalVendorData(player, vendor, screen, category, count, offset);
		break;
	default:
		break;
	}
}

void AuctionManagerImplementation::getLocalVendorData(CreatureObject* player, Vendor* vendor, int screen, uint32 category, int count, int offset) {
	VectorMap<uint64, ManagedReference<AuctionItem*> >* items = vendor->getVendorItems();

	if (items == NULL) {
		error("Unable to get Vendor items in getVendorData");
		return;
	}

	AuctionQueryHeadersResponseMessage* msg = fillAuctionQueryHeadersResponseMessage(player, vendor, items, screen, category, count, offset);
	player->sendMessage(msg);
}

void AuctionManagerImplementation::getGalaxyData(CreatureObject* player, Vendor* vendor, int screen, uint32 category, int count, int offset) {
	//using a Bazaar. get the bazaar auctionMap
	if (vendor->isBazaarTerminal() && screen != 7) { // This is to pervent bazaar items from showing on Vendor Search
		AuctionQueryHeadersResponseMessage* msg = fillAuctionQueryHeadersResponseMessage(player, vendor, auctionMap->getBazaarItems(), screen, category, count, offset);
		player->sendMessage(msg);
	} else {
		AuctionQueryHeadersResponseMessage* msg = fillAuctionQueryHeadersResponseMessage(player, vendor, auctionMap->getVendorItems(), screen, category, count, offset);
		player->sendMessage(msg);
	}
}

void AuctionManagerImplementation::getPlanetData(CreatureObject* player, Vendor* vendor, int screen, uint32 category, int count, int offset) {
	ManagedReference<SceneObject*> vendorRef = vendor->getVendor();

	if (vendorRef == NULL)
		return;

	Zone* zone = vendorRef->getZone();

	if (zone == NULL) {
		error("null zone int getPlanetData()");
		return;
	}

	PlanetManager* planetManager = zone->getPlanetManager();

	VectorMap<uint64, ManagedReference<AuctionItem*> > items;

	for (int u = 0; u < planetManager->getRegionCount(); ++u) {
		ManagedReference<CityRegion*> regionObject = planetManager->getRegion(u);

		/*
		for (int i = 0; i < regionObject->getBazaarCount(); ++i) {
			BazaarTerminal* term = regionObject->getBazaar(i);
			Vendor* vendorObj = term->getVendor();

			if (vendorObj == NULL)
				continue;

			VectorMap<uint64, ManagedReference<AuctionItem*> >* regionItems = vendorObj->getVendorItems();

			for (int j = 0; j < regionItems->size(); ++j) {
				items.put(regionItems->elementAt(j).getKey(), regionItems->elementAt(j).getValue());
			}
		}
		*/
	}

	AuctionQueryHeadersResponseMessage* msg = fillAuctionQueryHeadersResponseMessage(player, vendor, &items, screen, category, count, offset);
	player->sendMessage(msg);
}

void AuctionManagerImplementation::getRegionData(CreatureObject* player, Vendor* vendor, int screen, uint32 category, int count, int offset) {
	ManagedReference<SceneObject*> vendorRef = vendor->getVendor();

	if (vendorRef == NULL)
		return;

	Zone* zone = vendorRef->getZone();

	if (zone == NULL) {
		error("null zone int getRegionBazaarData");
		return;
	}

	//TODO: Vendors dont' have regions yet.
	if (!vendor->isBazaarTerminal())
		return;


	ManagedReference<CityRegion*> cityRegion = vendorRef->getCityRegion();

	if (cityRegion == NULL) {
		error("null region in getRegionData()");
		return;
	}

	String region = cityRegion->getRegionName();

	/* TODO: This needs to be refactored with the new city region code.
	StringId* name = area->getObjectName();

	PlanetManager* planetManager = zone->getPlanetManager();

	Vector<ManagedReference<Region*> > regions = planetManager->getRegions(*name);

	VectorMap<uint64, ManagedReference<AuctionItem*> > items;

	for (int i = 0; i < regions.size(); ++i) {
		Region* regionObject = regions.get(i);

		for (int i = 0; i < regionObject->getBazaarCount(); ++i) {
			BazaarTerminal* term = regionObject->getBazaar(i);
			Vendor* vendorObj = term->getVendor();

			if (vendorObj == NULL)
				continue;

			VectorMap<uint64, ManagedReference<AuctionItem*> >* regionItems = vendorObj->getVendorItems();

			for (int j = 0; j < regionItems->size(); ++j) {
				items.put(regionItems->elementAt(j).getKey(), regionItems->elementAt(j).getValue());
			}
		}
	}

	AuctionQueryHeadersResponseMessage* msg = fillAuctionQueryHeadersResponseMessage(player, vendor, &items, screen, category, count, offset);
	player->sendMessage(msg);
	*/
}

void AuctionManagerImplementation::getItemAttributes(CreatureObject* player, uint64 objectid) {
	Locker _locker(_this);

	UnicodeString description;
	ManagedReference<AuctionItem*> item = NULL;

	item = auctionMap->getBazaarItem(objectid);

	// item wasn't on the bazaar. Check if its on a vendor. (it has to be right??)
	if (item == NULL)
		item = auctionMap->getVendorItem(objectid);

	_locker.release();

	if (item == NULL) {
		error("null auction item in getItemAttributes()");
		return;
	}

	ManagedReference<SceneObject*> object = zoneServer->getObject(objectid);

	if (object == NULL)
		return;

	if (!object->isTangibleObject()) {
		error("not a valid object in getItemAttributes");
		return;
	}

	TangibleObject* tano = cast<TangibleObject*>(object.get());

	description = item->getItemDescription();

	AttributeListMessage* msg = new AttributeListMessage(objectid, description);

	object->fillAttributeList(msg, player);
	//msg->insertInt(0);
	String cust = TemplateManager::instance()->getTemplateFile(object->getClientObjectCRC());
	msg->insertAscii(cust);
	tano->getCustomizationString(cust);
	msg->insertAscii(cust);

	player->sendMessage(msg);

}

void AuctionManagerImplementation::cancelItem(CreatureObject* player, uint64 objectID) {
	ManagedReference<AuctionItem*> item = NULL;

	//find the item
	item = auctionMap->getBazaarItem(objectID);

	if (item == NULL)
		item = auctionMap->getVendorItem(objectID);

	// Item wasnt found. it doesn't exist
	if (item == NULL) {
		error("null item in cancelItem()");
		BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, CancelLiveAuctionResponseMessage::INVALIDITEM);
		player->sendMessage(msg);
		return;
	}

	if (item->getOwnerID() != player->getObjectID()) {
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

	Locker _locker(_this);
	Locker _locker2(player);

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = currentTime + 2592000;

	// remove from the sale item list
	item->setRemovedByOwner(true);
	item->setInStockroom(true);
	item->clearAuctionWithdraw();
	item->setExpireTime(availableTime);

	BaseMessage* msg = new CancelLiveAuctionResponseMessage(objectID, 0);
	player->sendMessage(msg);

}

Vendor* AuctionManagerImplementation::getVendorFromObject(SceneObject* obj) {
	if (obj == NULL)
		return NULL;

	Vendor* vendor = NULL;

	if (obj->isTerminal()) {
		Terminal* term = cast<Terminal*>(obj);

		if (term->isVendorTerminal()) {
			VendorTerminal* terminal = cast<VendorTerminal*>(term);
			if (terminal != NULL)
				vendor = terminal->getVendor();
		}

	} else if (obj->isCreatureObject()) {
		CreatureObject* creature = cast<CreatureObject*>(obj);

		if (creature->isVendorCreature()) {
			VendorCreature* vendorCreature = cast<VendorCreature*>(obj);
			if (vendorCreature != NULL)
				vendor = vendorCreature->getVendor();
		}

	}

	return vendor;
}
