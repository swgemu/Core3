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

#ifndef BAZAARMANAGERIMPLEMENTATION_H_
#define BAZAARMANAGERIMPLEMENTATION_H_

#include "engine/engine.h"

#include "BazaarTerminals.h"
#include "BazaarPlanetManager.h"
#include "BazaarPlanetManagerImplementation.h"

#include "../../objects.h"
#include "../../objects/auction/AuctionController.h"

#include "BazaarManager.h"

class CheckBazaarStatus;

class BazaarManagerImplementation : public AuctionController, public BazaarManagerServant, public Logger {
	ZoneProcessServerImplementation* processServer;
	ZoneServer*	zoneServer;

	CheckBazaarStatus* checkEvent;

	BazaarPlanetManager* bazaarPlanets[10];

	BazaarTerminals* bazaarTerminals;

public:
	static const int MAXPRICE = 20000;
	static const int MAXSALES = 20;
	static const int SALESFEE = 5;
	static const int CHECKEVERY = 2; // Minutes

	static const int ARMOR = 0x00000100;
	static const int BUILDING = 0x00000200;
	static const int ENTITY = 0x00000400;
	static const int DATA = 0x00000800;
	static const int INSTALLATION = 0x00001000;
	static const int MISC = 0x00002000;
	static const int TOOL = 0x00008000;
	static const int WEAPON = 0x00020000;
	static const int COMPONENT = 0x00040000;
	static const int WEAPONPOWERUP = 0x00080000;
	static const int ARMORPOWERUP = 0x00100000;
	static const int JEWELRY = 0x00200000;
	static const int RESOURCECONTAINER = 0x00400000;
	static const int DEED = 0x00800000;
	static const int CLOTHING = 0x01000000;
	static const int SHIPCOMPONENT = 0x40000000;

public:
	BazaarManagerImplementation(ZoneServer* zoneServer, ZoneProcessServerImplementation* server);
	~BazaarManagerImplementation();

	void newBazaarRequest(uint64 bazaarID, Player* player, int planet);
	bool isBazaarTerminal(uint64 objectID);

	void addSaleItem(Player* player, uint64 objectid, uint64 bazaarid, unicode& description, int price, uint32 duration, bool auction);

	BazaarPlanetManager* getPlanet(uint64 bazaarid);
	RegionBazaar* getBazaar(uint64 bazaarid);

	void checkAuctions();
	void buyItem(Player* player, uint64 objectid, int price1, int price2);
	void retrieveItem(Player* player, uint64 objectid, uint64 bazaarid);

	void getItemAttributes(Player* player, uint64 objectId);

};

#endif /*BAZAARMANAGERIMPLEMENTATION_H_*/
