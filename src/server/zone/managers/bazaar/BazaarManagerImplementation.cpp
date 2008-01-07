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

#include "../../ZoneServer.h"

#include "BazaarManager.h"
#include "BazaarManagerImplementation.h"

#include "../../packets/auction/IsVendorOwnerResponseMessage.h"
#include "../../packets/auction/BazaarDisplayUI.h"
#include "../../packets/auction/AuctionQueryHeadersResponseMessage.h"
#include "../../objects/terrain/PlanetNames.h"

BazaarManagerImplementation::BazaarManagerImplementation(ZoneServer* server) : BazaarManagerServant(), Mutex("BazaarManager") {
	
	for(int i = 0; i < 10; i++)
		bazaarPlanets[i] = NULL;  // Add as required
	bazaarTerminals = new BazaarTerminals();
}

bool BazaarManagerImplementation::isBazaarTerminal(long objectID) {
	if(bazaarTerminals->isBazaarTerminal(objectID) != NULL)
		return true;
	else
		return false;	
}

void BazaarManagerImplementation::newBazaarRequest(long bazaarID, Player* player, int planet) {
	BazaarTerminalDetails* location;
	bool vendor;
	string header;
	int bazaarX;
	int bazaarZ;
	
	if((location = bazaarTerminals->isBazaarTerminal(bazaarID)) == NULL)
		vendor = true;
	else
		vendor = false;
	
	string planetString = PlanetNames[planet];
	if(!vendor) {
		header = location->getRegion();
		bazaarX = location->getX();
		bazaarZ = location->getZ();
	}

	IsVendorOwnerResponseMessage* msg = new IsVendorOwnerResponseMessage(vendor, bazaarID, planetString, header, bazaarX, bazaarZ);
	player->sendMessage(msg);
	BazaarDisplayUI* msg2 = new BazaarDisplayUI(vendor, bazaarID, player);
	player->sendMessage(msg2);
}

void BazaarManagerImplementation::addInstantItem(Player* player, long objectid, long bazaarid, string& description, int price) {
	
}

void BazaarManagerImplementation::addAuctionItem(Player* player, long objectid, long bazaarid, string& description, int price, int duration) {
	
}

void BazaarManagerImplementation::getBazaarData(Player* player, long objectid, int screen, int extent, int category, int counter) {
	// Return an empty bazaar packet
	AuctionQueryHeadersResponseMessage* reply = new AuctionQueryHeadersResponseMessage(screen, counter);
	// Populate Bazaar with some items
	if(screen == 2) {
		string name = "Death Star (damaged)";
		string owner = "Darth Vader";
		string planet = "corellia";
		string region = "coronet";
		reply->addAuctionItem(123456, name, 5000, false, 7200, 0, 123545, owner, false, planet, region, objectid);
		name = "Light Saber";
		owner = "Luke Skywalker";
		planet = "tatooine";
		region = "mos_eisley";
		reply->addAuctionItem(123457, name, 50000, true, 7200, 0, 123546, owner, false, planet, region, objectid);
			
	}
	reply->createMessage();
	player->sendMessage(reply);
}
