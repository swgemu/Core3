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

#include "BazaarManagerImplementation.h"

#include "../../ZoneServer.h"

#include "BazaarTerminalDetails.h"

#include "../../packets/auction/IsVendorOwnerResponseMessage.h"
#include "../../packets/auction/BazaarDisplayUI.h"
#include "../../packets/auction/AuctionQueryHeadersResponseMessage.h"
#include "../../packets/auction/ItemSoldMessage.h"
#include "../../objects/auction/AuctionItem.h"
#include "../../packets/chat/ChatSystemMessage.h"
#include "../../packets/scene/SceneObjectDestroyMessage.h"

#include "../../objects/terrain/PlanetNames.h"

BazaarManagerImplementation::BazaarManagerImplementation(ZoneServer* server) 
		: BazaarManagerServant(), Mutex("BazaarManager"), Logger("BazaarManager") {

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
			item->ownerID = items->getInt(3);
			item->ownerName = items->getString(4);
			item->itemName = items->getString(1);
			item->itemType = items->getLong(2);
			item->price = items->getInt(5);
			item->auction = items->getBoolean(6);
			item->sold = items->getBoolean(7);
			item->expireTime = items->getUnsignedInt(8);
			
			bazaarPlanets[i]->addItem(item);
		}
		delete items;
	}
	
	info("Bazaars populated");
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
	stringstream query, query2, query3;
	uint32 itemType;
	string identity;
	
	BazaarMap* bazaarLocations = bazaarTerminals->getBazaarMap();
	BazaarTerminalDetails* bazaar = bazaarLocations->get(bazaarid);
	
	query << "SELECT name, template_type from `character_items` where `item_id` = " << objectid << ";";
	ResultSet* items = ServerDatabase::instance()->executeQuery(query);
	
	if(items->next()) {
		itemType = items->getUnsignedInt(1);
	} else {
		cout << "Item " << objectid << " not found\n";
		return;
	}
	if(description.size() == 0) {
		// Get the item name
		description = items->getString(0);
	}
	
	delete items;
	
	time_t expire = time(NULL) + duration;
	
	int auctionout;
	if(auction)
		auctionout = 1;
	else
		auctionout =0;

	int planet = bazaar->getPlanet();
	
	try {
		query2 << "INSERT into `bazaar_items` (objectid, description, item_type, ownerid, ownername,"
			<< " price, auction, sold, expire, terminalid, planet) "
			<< "VALUES (" << objectid << ",'" << description << "'," << itemType << "," << player->getCharacterID()
			<< ",'" << player->getCharacterName().c_str() << "'," << price << "," << auctionout << ",0," 
			<< expire << "," << bazaarid << "," << planet << ");";
	
		ServerDatabase::instance()->executeQuery(query2);
		
		query3 << "UPDATE `character_items` SET character_id = 0 where item_id = " << objectid << ";";
	
		ServerDatabase::instance()->executeQuery(query3);
		
	} catch(DatabaseException& e) {
		cout << "Can't add bazaar_item " << objectid << "\n";
		cout << query2.str() << "\n";
		return;
	}
	
	player->removeInventoryItem(objectid);
	
	AuctionItem* item  = new AuctionItem();
	
	item->planet = planet;
	item->id = objectid;
	item->vendorID = bazaarid;
	string region = bazaar->getRegion();
	string planetStr = PlanetNames[planet];	
	item->setLocation(planetStr, region, bazaarid, bazaar->getX(), bazaar->getZ(), false);
	item->ownerID = player->getCharacterID();
	item->ownerName = player->getCharacterName().c_str();
	item->itemName = description;
	item->itemType = itemType;
	item->price = price;
	item->auction = auction;
	item->sold = false;
	item->expireTime = expire;
	
	bazaarPlanets[planet]->addItem(item);
	
	string str1 = "base_player";
	string str2 = "sale_fee";
	unicode uni = unicode("");
	int saleFee = 20;
	
	BaseMessage* msg = new ChatSystemMessage(str1, str2, uni, saleFee, true);
	player->sendMessage(msg);
	
	msg = new ItemSoldMessage(objectid);
	player->sendMessage(msg);
	
	msg = new SceneObjectDestroyMessage(objectid);
	player->sendMessage(msg);
	
	// TODO: update bank account update item in database
}

RegionBazaar* BazaarManagerImplementation::getBazaar(long long objectid) {
	BazaarTerminalDetails* location;

	if ((location = bazaarTerminals->isBazaarTerminal(objectid)) != NULL) {
		return location->getTerminal();
	}
	else
		return NULL;
}

void BazaarManagerImplementation::getBazaarData(Player* player, long long objectid, int screen, int extent, int category, int counter) {
	// Return an empty bazaar packet
	AuctionQueryHeadersResponseMessage* reply = new AuctionQueryHeadersResponseMessage(screen, counter);
	
	reply->createMessage();
	
	player->sendMessage(reply);
}

void BazaarManagerImplementation::updateItemStatus(uint64 itemid) {
	updated.add(itemid);
}
