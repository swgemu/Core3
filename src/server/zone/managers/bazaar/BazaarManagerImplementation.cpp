/*
 * BazaarManagerImplementation.cpp
 *
 *  Created on: 13/03/2010
 *      Author: victor
 */

#include "BazaarManager.h"
#include "BazaarAuctionsMap.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/tangible/terminal/bazaar/AuctionItem.h"
#include "server/zone/objects/tangible/terminal/bazaar/BazaarTerminal.h"
#include "server/zone/packets/chat/ChatSystemMessage.h"
#include "server/zone/packets/auction/ItemSoldMessage.h"
#include "server/zone/packets/auction/AuctionQueryHeadersResponseMessage.h"
#include "server/zone/packets/auction/RetrieveAuctionItemResponseMessage.h"
#include "server/zone/packets/auction/BidAuctionResponseMessage.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/area/BadgeActiveArea.h"
#include "server/zone/objects/terrain/PlanetNames.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"
#include "server/chat/ChatManager.h"
#include "CheckAuctionsTask.h"

void BazaarManagerImplementation::initialize() {
	auctionMap = new BazaarAuctionsMap();

	ObjectDatabase* auctionDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("auctions", true);
	ObjectDatabaseManager::instance()->commitLocalTransaction();

	ObjectDatabaseIterator iterator(auctionDatabase);

	uint64 objectID = 0;

	while (iterator.getNextKey(objectID)) {
		AuctionItem* auctionItem = (AuctionItem*) Core::getObjectBroker()->lookUp(objectID);
		ObjectDatabaseManager::instance()->commitLocalTransaction();

		auctionMap->addAuction(auctionItem->getAuctionedItemObjectID(), auctionItem);
	}

	checkAuctions();
}

void BazaarManagerImplementation::checkAuctions() {
	Locker _locker(_this);

	info("Checking auctions");

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = currentTime + 2592000;

	for (int i = 0; i < auctionMap->getAuctionCount(); ++i) {
		ManagedReference<AuctionItem*> item = auctionMap->getAuction(i);
		uint64 objectId = item->getAuctionedItemObjectID();

		Locker _ilocker(item);

		if (item->getExpireTime() <= currentTime) {
			if (item->isSold()) {
				auctionMap->dropAuction(objectId);
				BazaarTerminal* terminal = item->getBazaarTerminal();
				terminal->dropAuction(objectId);

				ObjectManager::instance()->destroyObjectFromDatabase(item->_getObjectID());
			} else {
				ChatManager* cman = zoneServer->getChatManager();

				String sender = "auctioner";

				// retrieve failed auctions for owner
				if (item->getBidderName().length() < 1) {
					item->setBuyerID(item->getOwnerID());
					item->setBidderName(item->getOwnerName());

					UnicodeString subject("@auction:subject_auction_unsuccessful");
					StringIdChatParameter body("auction", "seller_fail");
					body.setTO(item->getItemName());

					cman->sendMail(sender, subject, body, item->getOwnerName());

					// bidder won auction. handle transactions and send messages
				} else {
					PlayerManager* pman = zoneServer->getPlayerManager();
					ManagedReference<PlayerCreature*> player = pman->getPlayer(item->getOwnerName());

					Locker _locker(player);
					player->addBankCredits(item->getPrice());
					player->updateToDatabase();

					UnicodeString subject1("@auction:subject_auction_seller");
					UnicodeString subject2("@auction:subject_auction_buyer");

					StringIdChatParameter body1("auction", "seller_success");
					body1.setTO(item->getItemName());
					body1.setTT(item->getBidderName());
					body1.setDI(item->getPrice());

					cman->sendMail(sender, subject1, body1, item->getOwnerName());

					StringIdChatParameter body2("auction", "buyer_success");
					body2.setTO(item->getItemName());
					body2.setTT(item->getBidderName());
					body2.setDI(item->getPrice());
					/*StringBuffer message2;

					message2 << "You have won the auction of " << item->getItemName() << " from " << item->getOwnerName() << " for " << item->getPrice() << " credits.\n"
							<< "The sale took place at " << item->getLocation();
					UnicodeString body2(message2.toString());*/

					cman->sendMail(sender, subject2, body2, item->getBidderName());

					item->setOwnerID(item->getBuyerID());
					item->setOwnerName(item->getBidderName());
				}

				// move to available items
				item->setSold(true);
				item->setExpireTime(availableTime);
				item->setBuyerID(item->getOwnerID());

				item->updateToDatabase();
			}
		}

		if (item->isRemovedByOwner()) {
			//If this condition has been reached, the item has been removed from the db in retriveItem()
			auctionMap->dropAuction(objectId);
			BazaarTerminal* terminal = item->getBazaarTerminal();
			terminal->dropAuction(objectId);

			ObjectManager::instance()->destroyObjectFromDatabase(item->_getObjectID());
		}
	}

	CheckAuctionsTask* task = new CheckAuctionsTask(_this);
	task->schedule(CHECKEVERY * 60000);
}

int BazaarManagerImplementation::checkSaleItem(PlayerCreature* player, SceneObject* object, int price) {
	if (auctionMap->getPlayerAuctionCount(player->getObjectID()) >= MAXSALES)
		return ItemSoldMessage::TOOMANYITEMS;

	if (auctionMap->containsAuction(object->getObjectID()))
		return ItemSoldMessage::ALREADYFORSALE;

	if (price > MAXPRICE)
		return ItemSoldMessage::OVER20000;

	if (price < 1)
		return ItemSoldMessage::INVALIDSALEPRICE;

	if (player->getBankCredits() < SALESFEE)
		return ItemSoldMessage::NOTENOUGHCREDITS;

	return 0;
}

void BazaarManagerImplementation::addSaleItem(PlayerCreature* player, uint64 objectid, uint64 bazaarid, const UnicodeString& description, int price, uint32 duration, bool auction) {
	Locker _locker(_this);

	Locker _locker2(player); // no cross lock because we never lock bazaar manager after locking player?

	ManagedReference<SceneObject*> bazaar = zoneServer->getObject(bazaarid);

	if (!bazaar->isBazaarTerminal()) {
		error("bazaar is not a bazaar terminal");
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::VENDORNOTWORKING);
		player->sendMessage(soldMessage);
		return;
	}

	BazaarTerminal* terminal = (BazaarTerminal*) bazaar.get();

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
	ManagedReference<SceneObject*> objectToSell = zoneServer->getObject(objectid);

	if (objectToSell == NULL) {
		error("trying to add null object to the bazaar");
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::NOTOWN);
		player->sendMessage(soldMessage);
		return;
	}

	ManagedReference<SceneObject*> toSellParent = objectToSell->getParent();

	if (toSellParent == NULL) {
		error("trying to add object to the bazaar with a null parent");
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::NOTOWN);
		player->sendMessage(soldMessage);
		return;
	}

	if (!objectToSell->isASubChildOf(inventory)) {
		error("trying to add object to the bazaar that is not in the inventory");
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

	Zone* zone = terminal->getZone();

	if (zone == NULL) {
		error("null bazaar zone");
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, ItemSoldMessage::UNKNOWNERROR);
		player->sendMessage(soldMessage);
		return;
	}

	int res = checkSaleItem(player, objectToSell, price);

	if (res != 0) {
		ItemSoldMessage* soldMessage = new ItemSoldMessage(objectid, res);
		player->sendMessage(soldMessage);
		return;
	}

	AuctionItem* item = createAuctionItem(player, objectToSell.get(), terminal, description, price, duration, auction);

	terminal->addAuction(item);
	auctionMap->addAuction(objectid, item);
	terminal->updateToDatabase();

	objectToSell->sendDestroyTo(player);
	toSellParent->removeObject(objectToSell, true);

	player->substractBankCredits(SALESFEE);

	inventory->updateToDatabase();
	objectToSell->updateToDatabase();

	StringIdChatParameter str("base_player", "sale_fee");
	str.setDI(SALESFEE);
	str.setUnknownByte(1);
	BaseMessage* cmsg = new ChatSystemMessage(str);
	player->sendMessage(cmsg);

	BaseMessage* msg = new ItemSoldMessage(objectid, 0);
	player->sendMessage(msg);
}

int BazaarManagerImplementation::checkBidAuction(PlayerCreature* player, AuctionItem* item, int price1, int price2) {
	if (price1 > MAXPRICE || price2 > MAXPRICE) {
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

void BazaarManagerImplementation::doInstantBuy(PlayerCreature* player, AuctionItem* item, int price1, int price2) {
	String playername = player->getFirstName().toLowerCase();

	ChatManager *cman = zoneServer->getChatManager();
	PlayerManager *pman = zoneServer->getPlayerManager();

	String sender = "auctioner";

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = currentTime + 2592000;

	item->setSold(true);
	item->setExpireTime(availableTime);
	item->setBuyerID(player->getObjectID());
	item->setBidderName(playername);

	item->updateToDatabase();

	player->substractBankCredits(price1);

	BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), 0);
	player->sendMessage(msg);

	StringIdChatParameter body("auction", "buyer_success");
	body.setTO(item->getItemName());
	body.setTT(item->getOwnerName());
	body.setDI(price1);
	// send the bidder a message
	/*StringBuffer body;

	body << "You have won the auction of " << item->getItemName() << " from " << item->getOwnerName() << " for " << price1 << " credits.\n"
			"The sale took place at " << item->getLocation();*/
	UnicodeString subject1("@auction:subject_instant_buyer");
	//UnicodeString ubody1(body.toString());

	player->sendSystemMessage(body);
	cman->sendMail(sender, subject1, body, item->getBidderName());

	// send the seller a message

	StringIdChatParameter body2("auction", "seller_success");
	body2.setTO(item->getItemName());
	body2.setTT(item->getBidderName());
	body2.setDI(price1);
	/*StringBuffer body2;

	body2 << "Your auction of " << item->getItemName() << " has been sold to " << item->getBidderName()
											<< " for " << price1 << " credits.";*/
	UnicodeString subject2("@auction:subject_instant_seller");
	//UnicodeString ubody2(body2.toString());
	cman->sendMail(sender, subject2, body2, item->getOwnerName());

	// pay the seller
	ManagedReference<PlayerCreature*> seller = pman->getPlayer(item->getOwnerName());

	if (seller == NULL) {
		error("SELLER NULL FOR NAME " + item->getOwnerName());
		return;
	}

	Locker clocker(seller, player);

	seller->sendSystemMessage(body2);
	seller->addBankCredits(price1);

	seller->updateToDatabase();
}

void BazaarManagerImplementation::doAuctionBid(PlayerCreature* player, AuctionItem* item, int price1, int price2) {
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
		//StringBuffer body;

		ManagedReference<PlayerCreature*> priorBidder = pman->getPlayer(item->getBidderName());
		//body << playername << " outbid you on " << item->getItemName() << ".";
		StringIdChatParameter body("auction", "bidder_outbid");
		body.setTO(item->getItemName());

		if (priorBidder != NULL) {
			Locker clocker(priorBidder, player);

			priorBidder->sendSystemMessage(body);
			priorBidder->addBankCredits(item->getPrice());

			priorBidder->updateToDatabase();

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

	item->updateToDatabase();

	BaseMessage* msg = new BidAuctionResponseMessage(item->getAuctionedItemObjectID(), 0);
	player->sendMessage(msg);
}

void BazaarManagerImplementation::buyItem(PlayerCreature* player, uint64 objectid, int price1, int price2) {
	Locker _locker(_this);
	Locker _locker2(player);

	ManagedReference<AuctionItem*> item = auctionMap->getAuction(objectid);

	if (item == NULL) { // send invalid item message
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


int BazaarManagerImplementation::checkRetrieve(PlayerCreature* player, uint64 objectIdToRetrieve, BazaarTerminal* terminal) {
	if (!auctionMap->containsAuction(objectIdToRetrieve))
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;

	SceneObject* inventory = player->getSlottedObject("inventory");

	if (inventory->hasFullContainerObjects())
		return RetrieveAuctionItemResponseMessage::FULLINVENTORY;

	ManagedReference<AuctionItem*> item = auctionMap->getAuction(objectIdToRetrieve);

	String playername = player->getFirstName();

	// only the owner can yank his own auction off the bazaar
	if (!item->isSold() && (playername.toLowerCase() != item->getOwnerName().toLowerCase()))
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;

	// the bidder is the only one who can get his auction after expiration
	if (item->isSold() && item->getBuyerID() != player->getObjectID())
		return RetrieveAuctionItemResponseMessage::NOTALLOWED;

	ManagedReference<ActiveArea*> area = terminal->getActiveRegion();

	if (area != NULL) {
		String region = area->getObjectName()->getStringID();
		//String region = terminal->getBazaarRegion();

		if (item->getLocation().indexOf(region) == -1)
			return RetrieveAuctionItemResponseMessage::NOTALLOWED;
	} else {
		StringBuffer msg;
		msg << "null area for bazaar terminal at" << terminal->getPositionX() << " " << terminal->getPositionY() << " zone " << terminal->getZone()->getZoneID();
		error(msg);
	}

	return 0;
}

void BazaarManagerImplementation::refundAuction(AuctionItem* item) {
	PlayerManager* pman = zoneServer->getPlayerManager();
	ManagedReference<PlayerCreature*> bidder = pman->getPlayer(item->getBidderName());
	ChatManager* cman = zoneServer->getChatManager();

	// send the player a mail and system message
	UnicodeString subject("@auction:subject_auction_cancelled");
	StringIdChatParameter body("auction", "buyer_canceled" );
	body.setTO(item->getItemName());
	body.setTT(item->getOwnerName());
	/*StringBuffer mess;
	mess <<  "Your bid on " << item->getItemName() << " was retracted because the auction was cancelled by the owner.";
	UnicodeString body(mess.toString());*/

	if (bidder != NULL) {
		int bankCredits = bidder->getBankCredits();
		bidder->setBankCredits(bankCredits + item->getPrice());
		bidder->sendSystemMessage(body);
	}

	cman->sendMail("auctioner", subject, body, item->getBidderName());
}

void BazaarManagerImplementation::retrieveItem(PlayerCreature* player, uint64 objectid, uint64 bazaarid) {
	BaseMessage* msg = NULL;
	ManagedReference<AuctionItem*> item = NULL;

	ManagedReference<SceneObject*> bazaarScene = zoneServer->getObject(bazaarid);

	if (bazaarScene == NULL || !bazaarScene->isBazaarTerminal()) {
		msg = new RetrieveAuctionItemResponseMessage(objectid, RetrieveAuctionItemResponseMessage::NOTALLOWED);
		player->sendMessage(msg);
		return;
	}

	BazaarTerminal* terminal = (BazaarTerminal*) bazaarScene.get();

	Locker _locker(_this);
	Locker _locker2(player);

	int res = checkRetrieve(player, objectid, terminal);

	if (res != 0) {
		msg = new RetrieveAuctionItemResponseMessage(objectid, res);
		player->sendMessage(msg);
		return;
	}

	// Check player is at correct bazaar
	item = auctionMap->getAuction(objectid);

	// refund money to bidder for sniping the auction
	if (!item->isSold() && item->getBidderName().length() > 0) {
		refundAuction(item);
	}

	ManagedReference<SceneObject*> objectToRetrieve = zoneServer->getObject(objectid);
	if (objectToRetrieve == NULL) {
		//TODO: temphack
		msg = new RetrieveAuctionItemResponseMessage(objectid, 0);
		player->sendMessage(msg);
		return;
	}

	objectToRetrieve->sendTo(player, true);

	SceneObject* inventory = player->getSlottedObject("inventory");
	inventory->addObject(objectToRetrieve, -1, true);
	inventory->updateToDatabase();

	item->setRemovedByOwner(true);

	BazaarTerminal* ownedTerminal = item->getBazaarTerminal();
	ownedTerminal->dropAuction(objectid);
	auctionMap->dropAuction(objectid);
	ObjectManager::instance()->destroyObjectFromDatabase(item->_getObjectID());

	msg = new RetrieveAuctionItemResponseMessage(objectid, 0);
	player->sendMessage(msg);
}

AuctionItem* BazaarManagerImplementation::createAuctionItem(PlayerCreature* player, SceneObject* objectToSell, BazaarTerminal* terminal, const UnicodeString& description, int price, unsigned int duration, bool auction) {
	Zone* zone = terminal->getZone();

	Time expireTime;
	expireTime.addMiliTime(duration * 1000);
	uint64 expire = expireTime.getMiliTime() / 1000;

	int planet = zone->getZoneID();

	String playername = player->getFirstName().toLowerCase();
	String descr = description.toString();

	AuctionItem* item  = new AuctionItem(objectToSell->getObjectID());

	item->setPlanet(planet);
	item->setBazaarTerminal(terminal);

	ActiveArea* area = terminal->getActiveRegion();
	String region = area->getObjectName()->getStringID();
	String planetStr = Planet::getPlanetName(planet);

	StringId* objectName = objectToSell->getObjectName();

	String name = objectName->getCustomString().toString();

	if (name.length() < 2)
		objectName->getFullPath(name);

	item->setLocation(planetStr, region, terminal->getObjectID(), (int)terminal->getPositionX(), (int)terminal->getPositionY(), false);
	item->setOwnerID(player->getObjectID());
	item->setOwnerName(playername);
	item->setItemName(name);
	item->setItemDescription(description.toString());
	item->setItemType(objectToSell->getClientGameObjectType());
	item->setPrice(price);
	item->setAuction(auction);
	item->setSold(false);
	item->setRemovedByOwner(false);
	item->setExpireTime(expire);
	item->setBuyerID(0);
	item->setBidderName("");

	ObjectManager::instance()->persistObject(item, 1, "auctions");

	return item;
}

AuctionQueryHeadersResponseMessage* BazaarManagerImplementation::fillAuctionQueryHeadersResponseMessage(PlayerCreature* player, VectorMap<unsigned long long, ManagedReference<AuctionItem*> >* items, int screen, uint32 category, int count, int offset) {
	AuctionQueryHeadersResponseMessage* reply = new AuctionQueryHeadersResponseMessage(screen, count);

	int displaying = 0;
	String pname = player->getFirstName().toLowerCase();

	switch(screen) {
	case 2: // All Auctions
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
			if ((items->get(i)->getOwnerID() == player->getObjectID()) && !items->get(i)->isSold())
				reply->addItemToList(items->get(i));
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
		}

		break;
	}

	if (displaying == (offset + 100))
		reply->createMessage(offset, true);
	else
		reply->createMessage(offset);

	return reply;
}

void BazaarManagerImplementation::getBazaarData(PlayerCreature* player, int extent, uint64 bazaarObjectid, int screen, unsigned int category, int count, int offset) {
	ManagedReference<SceneObject*> bazaar = zoneServer->getObject(bazaarObjectid);

	if (bazaar == NULL) {
		error("null bazaar in getRegionBazaarData");
		return;
	}

	if (!bazaar->isBazaarTerminal()) {
		error("bazaar is not a bazaar terminal");
		return;
	}

	BazaarTerminal* terminal = (BazaarTerminal*) bazaar.get();

	switch (extent) {
	case 0:
		getAllBazaarData(player, terminal, screen, category, count, offset);
		break;
	case 1:
		getPlanetBazaarData(player, terminal, screen, category, count, offset);
		break;
	case 2:
		getRegionBazaarData(player, terminal, screen, category, count, offset);
		break;
	default:
		break;
	}
}

void BazaarManagerImplementation::getAllBazaarData(PlayerCreature* player, BazaarTerminal* terminal, int screen, uint32 category, int count, int offset) {
	AuctionQueryHeadersResponseMessage* msg = fillAuctionQueryHeadersResponseMessage(player, auctionMap->getAuctions(), screen, category, count, offset);
	player->sendMessage(msg);
}

void BazaarManagerImplementation::getPlanetBazaarData(PlayerCreature* player, BazaarTerminal* terminal, int screen, uint32 category, int count, int offset) {
	Zone* zone = terminal->getZone();

	if (zone == NULL) {
		error("null zone int getRegionBazaarData");
		return;
	}

	PlanetManager* planetManager = zone->getPlanetManager();

	VectorMap<uint64, ManagedReference<AuctionItem*> > items;

	for (int u = 0; u < planetManager->getRegionCount(); ++u) {
		ManagedReference<Region*> regionObject = planetManager->getRegion(u);

		for (int i = 0; i < regionObject->getBazaarCount(); ++i) {
			BazaarTerminal* term = regionObject->getBazaar(i);

			VectorMap<uint64, ManagedReference<AuctionItem*> >* regionItems = term->getAuctions();

			for (int j = 0; j < regionItems->size(); ++j) {
				items.put(regionItems->elementAt(j).getKey(), regionItems->elementAt(j).getValue());
			}
		}
	}

	AuctionQueryHeadersResponseMessage* msg = fillAuctionQueryHeadersResponseMessage(player, &items, screen, category, count, offset);
	player->sendMessage(msg);
}

void BazaarManagerImplementation::getRegionBazaarData(PlayerCreature* player, BazaarTerminal* terminal, int screen, uint32 category, int count, int offset) {
	Zone* zone = terminal->getZone();

	if (zone == NULL) {
		error("null zone int getRegionBazaarData");
		return;
	}

	//String region = terminal->getBazaarRegion();
	ActiveArea* area = terminal->getActiveRegion();
	String region = area->getObjectName()->getStringID();

	if (area == NULL || !area->isRegion()) {
		StringId* name = area->getObjectName();
		info("area wtf " + name->getStringID(), true);
		error("null region in getRegionBazaarData");
		return;
	}

	StringId* name = area->getObjectName();

	PlanetManager* planetManager = zone->getPlanetManager();

	Vector<ManagedReference<Region*> > regions = planetManager->getRegions(*name);

	VectorMap<uint64, ManagedReference<AuctionItem*> > items;

	for (int i = 0; i < regions.size(); ++i) {
		Region* regionObject = regions.get(i);

		for (int i = 0; i < regionObject->getBazaarCount(); ++i) {
			BazaarTerminal* term = regionObject->getBazaar(i);

			VectorMap<uint64, ManagedReference<AuctionItem*> >* regionItems = term->getAuctions();

			for (int j = 0; j < regionItems->size(); ++j) {
				items.put(regionItems->elementAt(j).getKey(), regionItems->elementAt(j).getValue());
			}
		}
	}

	AuctionQueryHeadersResponseMessage* msg = fillAuctionQueryHeadersResponseMessage(player, &items, screen, category, count, offset);
	player->sendMessage(msg);
}

void BazaarManagerImplementation::getItemAttributes(PlayerCreature* player, uint64 objectid) {
	Locker _locker(_this);

	UnicodeString description;
	ManagedReference<AuctionItem*> item = auctionMap->getAuction(objectid);

	_locker.release();

	ManagedReference<SceneObject*> object = zoneServer->getObject(objectid);

	if (object == NULL)
		return;

	if (!object->isTangibleObject()) {
		error("non tangible object");
		return;
	}

	TangibleObject* tano = (TangibleObject*) object.get();

	if (item == NULL) {
		error("null auction item in bazaar manager");
		return;
	}

	if (object == NULL) {
		error("null object retrieved from database");
		return;
	}

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


