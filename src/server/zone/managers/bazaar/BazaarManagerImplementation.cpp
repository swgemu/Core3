/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "events/CheckBazaarStatus.h"

#include "BazaarManagerImplementation.h"

#include "../../Zone.h"
#include "../../ZoneServer.h"

#include "BazaarTerminalDetails.h"

#include "../../packets.h"
#include "../../objects.h"
#include "../../objects/auction/AuctionController.h"
#include "../../packets/scene/AttributeListMessage.h"

#include "../../objects/tangible/ItemAttributes.h"

#include "../item/ItemManager.h"

#include "../player/PlayerManager.h"
#include "../../../chat/ChatManager.h"

BazaarManagerImplementation::BazaarManagerImplementation(ZoneServer* zoneserver, ZoneProcessServerImplementation* server)
	: AuctionController(), BazaarManagerServant(), Logger("BazaarManager") {

	processServer = server;
	zoneServer = zoneserver;

	setLogging(false);
	setGlobalLogging(true);

	bazaarTerminals = new BazaarTerminals();

	info("Setting up bazaars");

	// Set up the bazaar planet managers
	for (int i = 0; i < 10; ++i)  {
		BazaarPlanetManager* bpManager = new BazaarPlanetManager(i);
		bpManager->deploy("BazaarPlanetManager", i);

		bazaarPlanets[i] = bpManager;
	}

	BazaarMap* bazaarLocations = bazaarTerminals->getBazaarMap();
	bazaarLocations->resetIterator();
	while (bazaarLocations->hasNext()) {
		BazaarTerminalDetails* bazaar = bazaarLocations->getNextValue();
		bazaarPlanets[bazaar->getPlanet()]->addBazaar(bazaar);
	}

	// Populate the bazaars
	info("Starting to populate the bazaars");

	for (int i = 0; i < 10; ++i)  {
		StringBuffer query;
		query << "SELECT * from `bazaar_items` where `planet` = " << i << ";";

		ResultSet* items = ServerDatabase::instance()->executeQuery(query);

		while (items->next()) {
			uint64 objectId = items->getUnsignedLong(0);
			AuctionItem* item  = new AuctionItem(objectId);

			item->setVendorID(items->getLong(10));
			item->setPlanet(i);

			BazaarMap* bazaarLocations = bazaarTerminals->getBazaarMap();
			BazaarTerminalDetails* bazaar = bazaarLocations->get(item->getVendorID());

			String region = bazaar->getRegion();
			String planet = Planet::getPlanetName(i);

			item->setLocation(planet, region, item->getVendorID(), bazaar->getX(), bazaar->getZ(), false);
			item->setOwnerID(items->getUnsignedLong(4));
			item->setOwnerName(items->getString(5));
			item->setItemName(items->getString(1));
			item->setItemDescription(items->getString(2));
			item->setItemType(items->getUnsignedInt(3));
			item->setPrice(items->getUnsignedInt(6));
			item->setAuction(items->getBoolean(7));
			item->setSold(items->getBoolean(8));
			item->setExpireTime(items->getUnsignedInt(9));
			item->setBuyerID(items->getUnsignedLong(12));
			item->setBidderName(items->getString(13));

			if (!item->isSold()) {
				bazaarPlanets[i]->addBazaarItem(item);
			}

			addItem(item);
		}

		delete items;
	}

	info("Bazaars populated");

	// Setup event handling to check auction items

	checkEvent = new CheckBazaarStatus(this);
	checkAuctions();
}

BazaarManagerImplementation::~BazaarManagerImplementation() {
	delete bazaarTerminals;
	bazaarTerminals = NULL;

	if (checkEvent->isQueued())
		processServer->removeEvent(checkEvent);

	delete checkEvent;
	checkEvent = NULL;

	for (int i = 0; i < 10; ++i)
		bazaarPlanets[i]->finalize();

}

bool BazaarManagerImplementation::isBazaarTerminal(uint64 objectID) {
	return bazaarTerminals->isBazaarTerminal(objectID) != NULL;
}

void BazaarManagerImplementation::newBazaarRequest(uint64 bazaarID, Player* player, int planet) {
	BazaarTerminalDetails* location;

	bool vendor;

	String header;

	int bazaarX;
	int bazaarZ;

	if ((location = bazaarTerminals->isBazaarTerminal(bazaarID)) == NULL)
		vendor = true;
	else
		vendor = false;

	String planetString = Planet::getPlanetName(planet);

	if (!vendor) {
		header = location->getRegion();

		bazaarX = location->getX();
		bazaarZ = location->getZ();
	}

	BaseMessage* msg = new IsVendorOwnerResponseMessage(vendor, bazaarID, planetString, header, bazaarX, bazaarZ);
	player->sendMessage(msg);

	msg = new BazaarDisplayUI(vendor, bazaarID, player);
	player->sendMessage(msg);
}

void BazaarManagerImplementation::addSaleItem(Player* player, uint64 objectid, uint64 bazaarid, UnicodeString& description, int price, uint32 duration, bool auction) {
	uint32 itemType;
	String identity;

	lock();

	player->wlock();

	// Check if the item is already for sale
	if (items.find(objectid) >= 0) {

		StringBuffer str;
		str << player->getCharacterName().toString() << " trying to add objectid "
		<< objectid << " to the bazaar again";
		error(str.toString());

		BaseMessage* msg = new ItemSoldMessage(objectid, 6);
		player->sendMessage(msg);

		player->unlock();
		unlock();
		return;
	}

	if (price > MAXPRICE) {
		BaseMessage* msg = new ItemSoldMessage(objectid, 14);
		player->sendMessage(msg);

		player->unlock();
		unlock();
		return;

	} else if (price < 1) {
		BaseMessage* msg = new ItemSoldMessage(objectid, 4);
		player->sendMessage(msg);

		player->unlock();
		unlock();
		return;
	}

	if (player->getBankCredits() < SALESFEE) {
		BaseMessage* msg = new ItemSoldMessage(objectid, 9);
		player->sendMessage(msg);

		player->unlock();
		unlock();
		return;
	}

	int numberOfItems;

	try {
		StringBuffer query1;
		query1 << "SELECT count(*) from `bazaar_items` WHERE ownerid = " << player->getObjectID() << ";";
		ResultSet* res = ServerDatabase::instance()->executeQuery(query1);

		res->next();
		numberOfItems = res->getInt(0);

		delete res;

	} catch (DatabaseException& e) {
		error("Can't count bazaar_items for user " + player->getCharacterName().toString());

		player->unlock();

		unlock();
		return;
	}

	if (numberOfItems >= MAXSALES) {
		BaseMessage* msg = new ItemSoldMessage(objectid, 13);
		player->sendMessage(msg);

		player->unlock();
		unlock();
		return;
	}

	BazaarMap* bazaarLocations = bazaarTerminals->getBazaarMap();
	BazaarTerminalDetails* bazaar = bazaarLocations->get(bazaarid);

	SceneObject* invObj = player->getInventoryItem(objectid);

	if (invObj == NULL || !invObj->isTangible()) {
		BaseMessage* msg = new ItemSoldMessage(objectid, 2);
		player->sendMessage(msg);

		player->unlock();
		unlock();
		return;
	}

	TangibleObject* obj = (TangibleObject*)invObj;

	if (obj->isEquipped()) {
		BaseMessage* msg = new ItemSoldMessage(objectid, 2);
		player->sendMessage(msg);

		player->sendSystemMessage("you must unequip your item!!");

		player->unlock();
		unlock();
		return;
	}

	itemType = obj->getObjectSubType();

	String name = obj->getName().toString();

	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();

	if (!obj->isPersistent())
		itemManager->createPlayerItem(player, obj);

	if (obj->isUpdated())
		itemManager->savePlayerItem(player, obj);

	Time expireTime;
	expireTime.addMiliTime(duration * 1000);
	uint64 expire = expireTime.getMiliTime() / 1000;

	int auctionout;

	if (auction)
		auctionout = 1;
	else
		auctionout = 0;

	int planet = bazaar->getPlanet();

	String playername = player->getFirstName().toLowerCase();

	try {
		StringBuffer query2;
		query2 << "INSERT into `bazaar_items` (objectid, name, description, item_type, ownerid, ownername,"
		<< " price, auction, sold, expire, terminalid, planet, buyerid, bidderName) "
		<< "VALUES (" << objectid << ",'" << name << "','" << description.toString() << "'," << itemType << ","
		<< player->getObjectID() << ",'" << playername << "'," << price << "," << auctionout << ",0,"
		<< expire << "," << bazaarid << "," << planet << ",0,'');";

		ServerDatabase::instance()->executeStatement(query2);

		StringBuffer query3;
		query3 << "UPDATE `character_items` SET character_id = 0 where item_id = " << objectid << ";";

		ServerDatabase::instance()->executeStatement(query3);

	} catch (DatabaseException& e) {
		StringBuffer err;
		err << "Can't add bazaar_item " << objectid;
		error(err);
		player->unlock();
		unlock();
		return;
	}

	AuctionItem* item  = new AuctionItem(objectid);

	item->setPlanet(planet);
	item->setVendorID(bazaarid);

	String region = bazaar->getRegion();
	String planetStr = Planet::getPlanetName(planet);

	item->setLocation(planetStr, region, bazaarid, bazaar->getX(), bazaar->getZ(), false);
	item->setOwnerID(player->getObjectID());
	item->setOwnerName(playername);
	item->setItemName(name);
	item->setItemDescription(description.toString());
	item->setItemType(itemType);
	item->setPrice(price);
	item->setAuction(auction);
	item->setSold(false);
	item->setExpireTime(expire);
	item->setBuyerID(0);
	item->setBidderName("");

	bazaarPlanets[planet]->addBazaarItem(item);

	addItem(item, false);

	String str1 = "base_player";
	String str2 = "sale_fee";
	UnicodeString uni = UnicodeString("");

	player->removeInventoryItem(objectid);

	obj->finalize();

	BaseMessage* msg = new ChatSystemMessage(str1, str2, uni, SALESFEE, true);
	player->sendMessage(msg);

	msg = new ItemSoldMessage(objectid, 0);
	player->sendMessage(msg);

	msg = new SceneObjectDestroyMessage(objectid);
	player->sendMessage(msg);

	player->subtractBankCredits(SALESFEE);

	player->unlock();
	unlock();
}

BazaarPlanetManager* BazaarManagerImplementation::getPlanet(uint64 bazaarid) {
	BazaarTerminalDetails* location;

	location = bazaarTerminals->getBazaarMap()->get(bazaarid);
	int planet = location->getPlanet();
	return bazaarPlanets[planet];
}

RegionBazaar* BazaarManagerImplementation::getBazaar(uint64 bazaarid) {
	BazaarTerminalDetails* location;

	if ((location = bazaarTerminals->isBazaarTerminal(bazaarid)) != NULL) {
		return location->getTerminal();
	} else
		return NULL;
}

void BazaarManagerImplementation::checkAuctions() {
	info("Checking auctions");

	Time expireTime;
	uint64 currentTime = expireTime.getMiliTime() / 1000;
	uint64 availableTime = currentTime + 2592000;

	for (int i = 0; i < items.size(); ++i) {
		AuctionItem* item = items.get(i);
		uint64 objectId = item->getID();

		try {
			item->wlock();

			if (item->getExpireTime() <= currentTime) {
				if (item->isSold()) {
					bazaarPlanets[item->getPlanet()]->removeBazaarItem(objectId);

					if (removeItem(objectId, false)) {
						//item->finalize(); the reference is still stored somewhere else
					} else {
						StringBuffer err;
						err << "checkAuctions cannot remove bazaar item from items " << objectId;
						error(err);
					}

					StringBuffer del1;
					del1 << "DELETE from `bazaar_items` WHERE objectid = " << objectId << ";";

					StringBuffer del2;
					del2 << "DELETE from `character_items` WHERE item_id = " << objectId << ";";

					try {
						ServerDatabase::instance()->executeStatement(del1);

					} catch (DatabaseException& e) {
						StringBuffer err;
						err << "Can't delete bazaar_item " << objectId;
						error(err);
						error(e.getMessage());

						/*unlock();
						return;*/
					}

					try {
						ServerDatabase::instance()->executeStatement(del2);

					} catch (DatabaseException& e) {
						StringBuffer err;
						err << "Can't delete character_item " << objectId;
						error(err);
						error(e.getMessage());

						/*unlock();
						return;*/
					}
				} else {
					ChatManager* cman = processServer->getChatManager();

					// retrieve failed auctions for owner
					if (item->getBidderName().length() < 1) {
						item->setBuyerID(item->getOwnerID());
						item->setBidderName(item->getOwnerName());

						StringBuffer message;
						UnicodeString subject("Auction Unsuccessful");

						message << "Your auction of " << item->getItemName() <<
						" has been completed and has not been  purchased.";
						UnicodeString body(message.toString());

						cman->sendMail("Auctioner", subject, body, item->getOwnerName());

						// bidder won auction. handle transactions and send messages
					} else {
						PlayerManager* pman = zoneServer->getPlayerManager();
						pman->modifyRecipientOfflineBank(item->getOwnerName(), item->getPrice());

						String sender = "Auctioner";
						StringBuffer message1;
						UnicodeString subject1("Auction Sale Complete");
						UnicodeString subject2("Auction Won");

						message1 << "Your auction of " << item->getItemName() << " has been sold to " << item->getBidderName()
						<< " for " << item->getPrice() << " credits.";

						UnicodeString body1(message1.toString());

						cman->sendMail(sender, subject1, body1, item->getOwnerName());

						StringBuffer message2;

						message2 << "You have won the auction of " << item->getItemName() << " from " << item->getOwnerName() << " for " << item->getPrice() << " credits.\n"
						<< "The sale took place at " << item->getLocation();
						UnicodeString body2(message2.toString());
						cman->sendMail(sender, subject2, body2, item->getBidderName());

						item->setOwnerID(item->getBuyerID());
						item->setOwnerName(item->getBidderName());
					}

					// move to available items
					bazaarPlanets[item->getPlanet()]->removeBazaarItem(objectId);

					item->setSold(true);
					item->setExpireTime(availableTime);
					item->setBuyerID(item->getOwnerID());

					StringBuffer update;
					update << "UPDATE `bazaar_items` SET sold = 1, expire = " << availableTime << ", buyerid = "
					<< item->getBuyerID() << ", bidderName = '" << item->getBidderName() << "', ownerid = "
					<< item->getOwnerID() << ", ownerName = '" << item->getOwnerName() << "' where objectid = " << item->getID() << ";";

					try {
						ServerDatabase::instance()->executeStatement(update);
					} catch (DatabaseException& e) {
						StringBuffer err;
						err << "Can't update bazaar_item " << objectId;
						error(err);
						error(e.getMessage());

						item->unlock();
						unlock();
						return;
					}
				}
			}

			item->unlock();
		} catch (...) {
			item->unlock();
			error("unreported exception caught in BazaarManagerImplementation::checkAuctions()");
		}
	}

	processServer->addEvent(checkEvent, CHECKEVERY * 60000);
}

void BazaarManagerImplementation::buyItem(Player* player, uint64 objectid, int price1, int price2) {
	AuctionItem* item = NULL;

	try {
		lock();
		player->wlock();

		ChatManager *cman = processServer->getChatManager();
		PlayerManager *pman = processServer->getPlayerManager();
		item = getItem(objectid, false);

		String playername = player->getFirstName().toLowerCase();

		if (item == NULL) { // send invalid item message
			BaseMessage* msg = new BidAuctionResponseMessage(objectid, 2);
			player->sendMessage(msg);

			player->unlock();
			unlock();
			return;
		}

		item->wlock();

		if (price1 > MAXPRICE || price2 > MAXPRICE) {
			BaseMessage* msg = new BidAuctionResponseMessage(objectid, 14);
			player->sendMessage(msg);

			item->unlock();
			player->unlock();
			unlock();
			return;
		} else if (price1 < 1 || price2 < 1) {
			BaseMessage* msg = new BidAuctionResponseMessage(objectid, 4);
			player->sendMessage(msg);

			item->unlock();
			player->unlock();
			unlock();
			return;
		}

		Time expireTime;
		uint64 currentTime = expireTime.getMiliTime() / 1000;
		uint64 availableTime = currentTime + 2592000;

		if (player->getBankCredits() < price1) { // Credit Check
			BaseMessage* msg = new BidAuctionResponseMessage(objectid, 9);
			player->sendMessage(msg);

			item->unlock();
			player->unlock();
			unlock();
			return;
		}

		if (!item->getAuction()) { // Instant buy
			item->setSold(true);
			item->setExpireTime(availableTime);
			item->setBuyerID(player->getObjectID());
			item->setBidderName(playername);

			StringBuffer update;
			update << "UPDATE `bazaar_items` SET sold = 1, expire = " << availableTime << ", buyerid = "
			<< item->getBuyerID() << ", bidderName='" << item->getBidderName() << "' where objectid = " << item->getID() << ";";

			try {
				ServerDatabase::instance()->executeStatement(update);

				player->subtractBankCredits(price1);

				// move to available items
				bazaarPlanets[item->getPlanet()]->removeBazaarItem(item->getID());

				BaseMessage* msg = new BidAuctionResponseMessage(objectid, 0);
				player->sendMessage(msg);

				// send the bidder a message
				StringBuffer body;

				body << "You have won the auction of " << item->getItemName() << " from " << item->getOwnerName() << " for " << price1 << " credits.\n"
				"The sale took place at " << item->getLocation();
				UnicodeString subject1("Instant Sale Item, Puchased");
				UnicodeString ubody1(body.toString());

				player->sendSystemMessage(body.toString());
				cman->sendMail("Auctioner", subject1, ubody1, item->getBidderName());

				// send the seller a message
				StringBuffer body2;

				body2 << "Your auction of " << item->getItemName() << " has been sold to " << item->getBidderName()
				<< " for " << price1 << " credits.";
				UnicodeString subject2("Instant Sale Complete");
				UnicodeString ubody2(body2.toString());
				cman->sendMail("Auctioner", subject2, ubody2, item->getOwnerName());

				// pay the seller
				Player* seller = pman->getPlayer(item->getOwnerName());

				if (seller != NULL) {
					try {
						if (seller != player)
							seller->wlock(player);

						seller->sendSystemMessage(body2.toString());
						seller->addBankCredits(price1);

						if (seller != player)
							seller->unlock();
					} catch(...) {
						if (player != seller)
							seller->unlock();
						error("unreported1 exception caught in BazaarManagerImplementation::buyItem(Player* player, uint64 objectid, int price1, int price2)");
					}
				} else {
					if (!pman->modifyRecipientOfflineBank(item->getOwnerName(), price1)) {
						item->unlock();
						player->unlock();
						unlock();
						return;
					}
				}
			} catch (DatabaseException& e) {
				BaseMessage* msg = new BidAuctionResponseMessage(objectid, 2);
				player->sendMessage(msg);

				StringBuffer err;
				err << "Can't update bazaar_item " << item->getID();
				error(err);
				error(e.getMessage());

				item->unlock();
				player->unlock();
				unlock();
				return;
			}
		} else { // For Auction Bids
			// don't allow owner or last bidder bid on the item.  don't allow old auction info
			// send auctioner invalid message
			if (playername == item->getBidderName() || playername == item->getOwnerName() || price1 <= item->getPrice()) {
				BaseMessage* msg = new BidAuctionResponseMessage(objectid, 1);
				player->sendMessage(msg);

				item->unlock();
				player->unlock();
				unlock();
				return;
			}

			// send prior bidder their money back
			if (item->getBidderName().length() > 0) {
				StringBuffer body;

				Player* priorBidder = pman->getPlayer(item->getBidderName());
				body << playername << " outbid you on " << item->getItemName() << ".";

				if (priorBidder != NULL) {
					try {
						if (priorBidder != player)
							priorBidder->wlock(player);

						priorBidder->sendSystemMessage(body.toString());
						priorBidder->addBankCredits(item->getPrice());

						if (priorBidder != player)
							priorBidder->unlock();
					} catch (...) {
						if (priorBidder != player)
							priorBidder->unlock();

						error("unreported2 exception caught in BazaarManagerImplementation::buyItem(Player* player, uint64 objectid, int price1, int price2)");
					}
				} else {
					if (!pman->modifyRecipientOfflineBank(item->getBidderName(), item->getPrice())) {
						item->unlock();
						player->unlock();
						unlock();

						return;
					}
				}

				// mail prior bidder with outcome
				UnicodeString subject("Outbid");
				UnicodeString ubody(body.toString());

				cman->sendMail("Bazaar", subject, ubody, item->getBidderName());
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

			StringBuffer update;
			update << "UPDATE `bazaar_items` SET price = " << price1 << ", bidderName = '" << item->getBidderName() << "', buyerid = " << player->getObjectID() << " where objectid = " << objectid << ";";
			try {

				ServerDatabase::instance()->executeStatement(update);

			} catch (DatabaseException& e) {
				StringBuffer err;
				err << "Can't update bazaar_item " << item->getID();
				error(err);
				error(e.getMessage());

				BaseMessage* msg = new BidAuctionResponseMessage(objectid, 2);
				player->sendMessage(msg);

				item->unlock();
				player->unlock();
				unlock();
				return;
			}

			BaseMessage* msg = new BidAuctionResponseMessage(objectid, 0);
			player->sendMessage(msg);
		}

		item->unlock();
		player->unlock();
		unlock();

	} catch (Exception& e) {
		if (item != NULL)
			item->unlock();

		player->unlock();
		unlock();

		error("Unreported3 exception caught in BazaarManagerImplementation::buyItem(Player* player, uint64 objectid, int price1, int price2)");
		e.printStackTrace();
	} catch (...) {
		if (item != NULL)
			item->unlock();
		player->unlock();
		unlock();

		error("Unreported3 exception caught in BazaarManagerImplementation::buyItem(Player* player, uint64 objectid, int price1, int price2)");
	}
}

void BazaarManagerImplementation::retrieveItem(Player* player, uint64 objectid, uint64 bazaarid) {
	BaseMessage* msg;
	AuctionItem* item = NULL;

	try {
		lock();
		player->wlock();

		// Check player is at correct bazaar
		item = getItem(objectid, false);
		String playername = player->getFirstName().toCharArray();

		// object was probably already retrieved
		if (item == NULL) {
			msg = new RetrieveAuctionItemResponseMessage(objectid, 1);
			player->sendMessage(msg);

			player->unlock();
			unlock();
			return;
		}

		item->wlock();

		// only the owner can yank his own auction off the bazaar
		if (!item->isSold() && item->getOwnerName() != playername ) {
			msg = new RetrieveAuctionItemResponseMessage(objectid, 1);
			player->sendMessage(msg);

			item->unlock();
			player->unlock();
			unlock();
			return;
		}

		// the bidder is the only one who can get his auction after expiration
		if (item->isSold() && item->getBuyerID() != player->getObjectID()) {
			msg = new RetrieveAuctionItemResponseMessage(objectid, 1);
			player->sendMessage(msg);

			item->unlock();
			player->unlock();
			unlock();
			return;
		}

		BazaarTerminalDetails* location = bazaarTerminals->getBazaarMap()->get(bazaarid);
		String region = location->getRegion();

		if (item->getLocation().indexOf(region) == -1) {
			msg = new RetrieveAuctionItemResponseMessage(objectid, 1);
			player->sendMessage(msg);

			item->unlock();

			player->unlock();

			unlock();
			return;
		}

		// Check if inventory is full
		Inventory* inventory = player->getInventory();

		if (inventory->objectsSize() > 79) {
			msg = new RetrieveAuctionItemResponseMessage(objectid, 12);

			item->unlock();
			player->sendMessage(msg);
			player->unlock();
			unlock();
			return;
		}

		try {
			StringBuffer update;
			update << "UPDATE `character_items` SET character_id = " << player->getCharacterID() << " WHERE item_id = " << objectid;
			StringBuffer delBazaar;
			delBazaar << "DELETE FROM `bazaar_items` WHERE objectid = " << objectid;

			ServerDatabase::instance()->executeStatement(update);
			ServerDatabase::instance()->executeStatement(delBazaar);

		} catch (DatabaseException& e) {
			StringBuffer err;
			err << "Can't remove bazaar_item " << objectid;
			error(err);
			error(e.getMessage());
			msg = new RetrieveAuctionItemResponseMessage(objectid, 1);

			item->unlock();
			player->sendMessage(msg);
			player->unlock();
			unlock();
			return;
		}

		// refund money to bidder for sniping the auction
		if (!item->isSold() && item->getBidderName().length() > 0) {
			PlayerManager* pman = processServer->getPlayerManager();
			Player* bidder = pman->getPlayer(item->getBidderName());
			ChatManager* cman = processServer->getChatManager();

			// send the player a mail and system message
			UnicodeString subject("Auction Cancelled");
			StringBuffer mess;
			mess <<  "Your bid on " << item->getItemName() << " was retracted because the auction was cancelled by the owner.";
			UnicodeString body(mess.toString());

			if (bidder != NULL) {
				try {
					if (bidder != player)
						bidder->wlock(player);

					bidder->addBankCredits(item->getPrice());
					bidder->sendSystemMessage(mess.toString());

					if (bidder != player)
						bidder->unlock();
				} catch (...) {
					if (bidder != player)
						bidder->unlock();
					error("Unreporeted1 exception caught in BazaarManagerImplementation::retrieveItem(Player* player, uint64 objectid, uint64 bazaarid)");
				}
			} else
				pman->modifyRecipientOfflineBank(item->getBidderName(), item->getPrice());

			cman->sendMail("auctioner", subject, body, item->getBidderName());
			bazaarPlanets[item->getPlanet()]->removeBazaarItem(item->getID());
		}

		ItemManager* itemManager = processServer->getItemManager();
		TangibleObject* tano = itemManager->getPlayerItem(player, objectid);

		// TODO: handle this case
		if (tano == NULL) {
			StringBuffer err;
			err << "retrieveItem NULL pointer for bazaar_item " << objectid;
			error(err);

			if (removeItem(objectid, false)) {
				//item->finalize();  the reference is still stored somewhere else
			} else {
				StringBuffer errMsg;
				errMsg << "retrieveItem cannot remove bazaar item from items " << objectid;
				error(errMsg);
			}

			item->unlock();
			player->unlock();
			unlock();
			return;
		}

		tano->sendTo(player);

		msg = new RetrieveAuctionItemResponseMessage(objectid, 0);

		item->unlock();
		player->sendMessage(msg);
		player->unlock();

		if (removeItem(objectid, false)) {
			//item->finalize();  the reference is still stored somewhere else
		} else {
			StringBuffer errMsg;
			errMsg << "retrieveItem cannot remove bazaar item from items " << objectid;
			error(errMsg);
		}

		unlock();
	} catch (...) {
		if (item != NULL)
			item->unlock();
		player->unlock();
		unlock();

		error("Unreported2 exception caught in BazaarManagerImplementation::retrieveItem(Player* player, uint64 objectid, uint64 bazaarid)");
	}
}

void BazaarManagerImplementation::getItemAttributes(Player* player, uint64 objectid) {
	if (player == NULL)
		return;

	lock();
	player->wlock();

	ItemManager* itemManager = zoneServer->getItemManager();
	TangibleObject* object = itemManager->getPlayerItem(NULL, objectid);

	if (object == NULL) {
		player->unlock();
		unlock();
		return;
	}

	UnicodeString description;
	AuctionItem* item = getItem(objectid, false);
	if (item == NULL)
		description = UnicodeString("");
	else
		description = UnicodeString(item->getItemDescription());

	AttributeListMessage* msg = new AttributeListMessage(objectid, description);

	object->addAttributes(msg);
	msg->insertInt(0);
	player->sendMessage(msg);

	object->finalize();
	player->unlock();
	unlock();
}
