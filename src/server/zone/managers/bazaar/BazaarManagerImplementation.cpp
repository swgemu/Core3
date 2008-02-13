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

#include "../../objects/tangible/ItemAttributes.h"

#include "../item/ItemManager.h"

BazaarManagerImplementation::BazaarManagerImplementation(ZoneServer* zoneServer, ZoneProcessServerImplementation* server) : AuctionController(),
	BazaarManagerServant(), Mutex("BazaarManager"), Logger("BazaarManager") {

	processServer = server;
	
	setLogging(false); 
	setGlobalLogging(true);
	
	bazaarTerminals = new BazaarTerminals();
	
	info("Setting up bazaars");
	
	// Set up the bazaar planet managers
	for (int i = 0; i < 10; i++)  {
		BazaarPlanetManagerImplementation* bpmImpl = new BazaarPlanetManagerImplementation(i);
		bazaarPlanets[i] = (BazaarPlanetManager*) bpmImpl->deploy("BazaarPlanetManager" );	
	}
	
	BazaarMap* bazaarLocations = bazaarTerminals->getBazaarMap();
	bazaarLocations->resetIterator();
	while (bazaarLocations->hasNext()) {
		BazaarTerminalDetails* bazaar = bazaarLocations->getNextValue();
		bazaarPlanets[bazaar->getPlanet()]->addBazaar(bazaar);
	}
	
	// Populate the bazaars
	info("Starting to populate the bazaars");

	for (int i = 0; i < 10; i++)  {		
		stringstream query;
		query << "SELECT * from `bazaar_items` where `planet` = " << i << ";";
		
		ResultSet* items = ServerDatabase::instance()->executeQuery(query);

		while (items->next()) {
			AuctionItem* item  = new AuctionItem();
			
			item->planet = i;
			uint64 objectId = items->getUnsignedLong(0);
			item->id = objectId;
			
			item->vendorID = items->getLong(9);
			
			BazaarMap* bazaarLocations = bazaarTerminals->getBazaarMap();
			BazaarTerminalDetails* bazaar = bazaarLocations->get(item->vendorID);
				
			string region = bazaar->getRegion();
			string planet = PlanetNames[i];
			item->setLocation(planet, region, item->vendorID, bazaar->getX(), bazaar->getZ(), false);
			item->ownerID = items->getUnsignedLong(3);
			item->ownerName = items->getString(4);
			item->itemName = items->getString(1);
			item->itemType = items->getUnsignedInt(2);
			item->price = items->getUnsignedInt(5);
			item->auction = items->getBoolean(6);
			item->sold = items->getBoolean(7);
			item->expireTime = items->getUnsignedInt(8);
			item->buyerID = items->getUnsignedLong(11);
			
			if (!item->sold)
				bazaarPlanets[i]->addBazaarItem(item);
			addItem(item);
		}
		delete items;
	}
	
	info("Bazaars populated");
	
	// Setup event handling to check auction items

	checkEvent = new CheckBazaarStatus(this);
	checkAuctions();

}

bool BazaarManagerImplementation::isBazaarTerminal(long long objectID) {
	if (bazaarTerminals->isBazaarTerminal(objectID) != NULL)
		return true;
	else
		return false;	
}

void BazaarManagerImplementation::newBazaarRequest(long long bazaarID, Player* player, int planet) {
	BazaarTerminalDetails* location;
	
	bool vendor;
	
	string header;
	
	int bazaarX;
	int bazaarZ;
	
	if ((location = bazaarTerminals->isBazaarTerminal(bazaarID)) == NULL)
		vendor = true;
	else
		vendor = false;
	
	string planetString = PlanetNames[planet];
	
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

void BazaarManagerImplementation::addSaleItem(Player* player, long long objectid, long long bazaarid, string& description, int price, unsigned int duration, bool auction) {
	uint32 itemType;
	string identity;
	
	lock();
	
	player->wlock();

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
	
	// TODO:  This seems to crash server for multiple sales
	//stringstream query1;
	//query1 << "SELECT count(*) from `bazaar_items` WHERE ownerid = " << player->getCharacterID() << ";";
	//ResultSet* res = ServerDatabase::instance()->executeQuery(query1);

	int numberOfItems = 0;
		
	//delete res;
		
	if (numberOfItems >= MAXSALES) {
		BaseMessage* msg = new ItemSoldMessage(objectid, 13);
		player->sendMessage(msg);
		player->unlock();
		unlock();
		return;			
	}
	
	BazaarMap* bazaarLocations = bazaarTerminals->getBazaarMap();
	BazaarTerminalDetails* bazaar = bazaarLocations->get(bazaarid);
	
	TangibleObject* obj = (TangibleObject*)player->getInventoryItem(objectid);
	
	if (obj == NULL) {
		BaseMessage* msg = new ItemSoldMessage(objectid, 2);
		player->sendMessage(msg);
		player->unlock();
		unlock();
		return;			
	}
	
	itemType = obj->getObjectSubType();

	if(description.size() == 0) {
		// Get the item name
		description = obj->getName().c_str();
	}

	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();

	if(!obj->isPersistent()) {
		itemManager->createPlayerItem(player, obj);
		itemManager->savePlayerItem(player, obj);
	} else {
		itemManager->savePlayerItem(player, obj); // need to save it in case of changes
	}
		
	Time* expireTime = new Time();
	expireTime->addMiliTime(duration * 1000);
	uint64 expire = expireTime->getMiliTime() / 1000;
	
	int auctionout;
	if(auction)
		auctionout = 1;
	else
		auctionout = 0;

	int planet = bazaar->getPlanet();
	
	try {
		stringstream query2;
		query2 << "INSERT into `bazaar_items` (objectid, description, item_type, ownerid, ownername,"
			<< " price, auction, sold, expire, terminalid, planet, buyerid) "
			<< "VALUES (" << objectid << ",'\\" << description << "'," << itemType << "," << player->getObjectID()
			<< ",'" << player->getCharacterName().c_str() << "'," << price << "," << auctionout << ",0," 
			<< expire << "," << bazaarid << "," << planet << ",0);";
	
		ServerDatabase::instance()->executeQuery(query2);
		
		stringstream query3;
		query3 << "UPDATE `character_items` SET character_id = 0 where item_id = " << objectid << ";";
	
		ServerDatabase::instance()->executeQuery(query3);
		
	} catch(DatabaseException& e) {
		cout << "Can't add bazaar_item " << objectid << "\n";
		player->unlock();
		unlock();
		return;
	}
	
	AuctionItem* item  = new AuctionItem();
	
	item->planet = planet;
	item->id = objectid;
	item->vendorID = bazaarid;
	string region = bazaar->getRegion();
	string planetStr = PlanetNames[planet];	
	item->setLocation(planetStr, region, bazaarid, bazaar->getX(), bazaar->getZ(), false);
	item->ownerID = player->getObjectID();
	item->ownerName = player->getCharacterName().c_str();
	item->itemName = description;
	item->itemType = itemType;
	item->price = price;
	item->auction = auction;
	item->sold = false;
	item->expireTime = expire;
	item->buyerID = 0;
	
	addItem(item);
	bazaarPlanets[planet]->addBazaarItem(item);
	
	string str1 = "base_player";
	string str2 = "sale_fee";
	unicode uni = unicode("");

	player->removeInventoryItem(objectid);
	
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

BazaarPlanetManager* BazaarManagerImplementation::getPlanet(long long bazaarid) {
	BazaarTerminalDetails* location;
	
	location = bazaarTerminals->getBazaarMap()->get(bazaarid);
	int planet = location->getPlanet();
	return bazaarPlanets[planet];
}

RegionBazaar* BazaarManagerImplementation::getBazaar(long long bazaarid) {
	BazaarTerminalDetails* location;

	if ((location = bazaarTerminals->isBazaarTerminal(bazaarid)) != NULL) {
		return location->getTerminal();
	}
	else
		return NULL;
}

void BazaarManagerImplementation::updateItemStatus(uint64 itemid) {
	updated.add(itemid);
}

void BazaarManagerImplementation::checkAuctions() {
	lock();
	
	info("Checking auctions");

	Time* expireTime = new Time();
	uint64 currentTime = expireTime->getMiliTime() / 1000;
	uint64 availableTime = currentTime + 2592000;
	
	for (int i = 0; i < items.size(); i++) {
		AuctionItem* item = items.get(i);
		
		if (item->expireTime <= currentTime) {
			if (item->sold) {
				bazaarPlanets[item->planet]->removeBazaarItem(item->id);
				removeItem(item->id);
				
				stringstream del1;
				del1 << "DELETE from `bazaar_items` WHERE objectid = " << item->id << ";";

				stringstream del2;
				del2 << "DELETE from `character_items` WHERE objectid = " << item->id << ";";
				
				try {
					ServerDatabase::instance()->executeQuery(del1);
					ServerDatabase::instance()->executeQuery(del2);
				} catch (DatabaseException& e) {
					cout << "Can't delete bazaar_item " << item->id << "\n";
					
					unlock();
					return;
				}
			} else {
				// move to available items
				bazaarPlanets[item->planet]->removeBazaarItem(item->id);
				
				item->sold = true;
				item->expireTime = availableTime;
				item->buyerID = item->ownerID;
				
				stringstream update;
				update << "UPDATE `bazaar_items` SET sold = 1, expire = " << availableTime << ", buyerid = " 
					<< item->ownerID << " where objectid = " << item->id << ";";

				try {
					ServerDatabase::instance()->executeQuery(update);
				} catch (DatabaseException& e) {
					cout << "Can't update bazaar_item " << item->id << "\n";
					cout << update.str() << "\n";
					
					unlock();
					return;
				}
			}
		}
	}

	processServer->addEvent(checkEvent, CHECKEVERY * 60000);

	unlock();
}

void BazaarManagerImplementation::buyItem(Player* player, long long objectid, int price1, int price2) {
	
	lock();
	player->wlock();
	
	AuctionItem* item = getItem(objectid);
	
	Time* expireTime = new Time();
	uint64 currentTime = expireTime->getMiliTime() / 1000;
	uint64 availableTime = currentTime + 2592000;
	
	if (player->getBankCredits() < price1) { // Credit Check
		
		BaseMessage* msg = new BidAuctionResponseMessage(objectid, 9);
		player->unlock();
		unlock();
		return;
	}

	else if (price1 == price2) { // Instant buy
		
		BaseMessage* msg = new BidAuctionResponseMessage(objectid, 0);
		player->sendMessage(msg);

		// move to available items
		bazaarPlanets[item->planet]->removeBazaarItem(item->id);
		
		item->sold = true;
		item->expireTime = availableTime;
		item->buyerID = player->getObjectID();
		
		player->subtractBankCredits(price1); 
		
		stringstream update;
		update << "UPDATE `bazaar_items` SET sold = 1, expire = " << availableTime << ", buyerid = "
			<< item->buyerID <<" where objectid = " << item->id << ";";
		try {
			
			ServerDatabase::instance()->executeQuery(update);

		} catch (DatabaseException& e) {
			cout << "Can't update bazaar_item " << item->id << "\n";
			cout << update.str() << "\n";
			player->unlock();
			unlock();
			return;
		}
	} else { // For Auction Bids
		
		item->price = price1; 
		item->buyerID = player->getObjectID(); 
		         
		stringstream update; 
		update << "UPDATE `bazaar_items` SET price = " << price1 << ", buyerid = " << item->buyerID << " where objectid = " << objectid << ";"; 
		try { 
	                                 
		 	ServerDatabase::instance()->executeQuery(update);
		 	
		} catch (DatabaseException& e) { 
		 	cout << "Can't update bazaar_item " << item->id << "\n"; 
		 	cout << update.str() << "\n"; 
		 	player->unlock(); 
		 	unlock(); 
		 	return; 
		} 
                 
		BaseMessage* msg = new BidAuctionResponseMessage(objectid, 0); 
		player->sendMessage(msg);
	}

	player->unlock();
	unlock();
	
}

void BazaarManagerImplementation::retrieveItem(Player* player, uint64 objectid, uint64 bazaarid) {
	BaseMessage* msg;
	lock();
	
	// Check player is at correct bazaar
	AuctionItem* item = getItem(objectid);
	BazaarTerminalDetails* location = bazaarTerminals->getBazaarMap()->get(bazaarid);
	string region = location->getRegion();
	
	if (item->location.find(region) == string::npos) {

		string game = "SWG";
		string galaxy = "core3";
		unicode message = "retrieve fail";
		
		msg = new ChatInstantMessageToClient(game, galaxy, player->getFirstName(), message);
		player->sendMessage(msg);

		msg = new ChatOnSendInstantMessage(1);
		player->sendMessage(msg);
		
		unlock();
		return;
	}
	
	// TODO: Check if inventory is full
	
	try {
		stringstream update;
		update << "UPDATE `character_items` SET character_id = " << player->getCharacterID() << " WHERE item_id = " << objectid;
		stringstream delBazaar;
		delBazaar << "DELETE FROM `bazaar_items` WHERE objectid = " << objectid;
		
		ServerDatabase::instance()->executeQuery(update);
		ServerDatabase::instance()->executeQuery(delBazaar);
		
	} catch(DatabaseException& e) {
		cout << "Can't remove bazaar_item " << objectid << "\n";
		player->unlock();
		unlock();
		return;
	}

	ItemManager* itemManager = processServer->getItemManager();
	TangibleObject* tano = itemManager->getPlayerItem(player, objectid);
	tano->sendTo(player);
	
	msg = new RetrieveAuctionItemResponseMessage(objectid, 0);
	player->sendMessage(msg);
	
	removeItem(objectid);
	
	unlock();
}
