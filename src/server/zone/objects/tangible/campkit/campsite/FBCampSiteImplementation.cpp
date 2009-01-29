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

#include "FBCampSiteImplementation.h"
#include "../CampKit.h"
#include "../../crafting/CraftingStation.h"

FBCampSiteImplementation::FBCampSiteImplementation(Player* player, uint64 oid, CampKit* campKit) : FBCampSiteServant(player, oid,  campKit) {
	objectID = oid;


	name = UnicodeString("0");;
	defaultName = "";

	campOwner = player;

	campArea = NULL;
	areaRange = 13.5f;
	visitor = new VisitorList();
	recoveries = new RecoveryList();
	currentXP = 0.0f;
	campType = campKit->getCampType();

	maxXP = campKit->getXP();
	duration = campKit->getDuration();
	campModifier = 0;
	abandoned = false;
	abandonEvent = NULL;
	despawnEvent = NULL;
	initializePosition(player->getPositionX(),player->getPositionZ(),player->getPositionY());
	init();
}

FBCampSiteImplementation::~FBCampSiteImplementation() {
	campArea = NULL;
	despawnEvent = NULL;
	if (abandonEvent != NULL)
		abandonEvent->endNow();

	abandonEvent = NULL;
	visitor = NULL;
	recoveries = NULL;
	zone = NULL;
}

void FBCampSiteImplementation::init() {
	persistent = false;
	updated = false;

	objectCount = 0;

	objectType = SceneObjectImplementation::TANGIBLE;
	objectSubType = TangibleObjectImplementation::MISC;

	equipped = false;

	pvpStatusBitmask = 0;

	name = UnicodeString("FB Camp");
	defaultName = "basic_name";
	objectCRC = 0x286327C3;
	campModifier = 100;
	aggroMod = 75;
}

void FBCampSiteImplementation::spawnCampItems() {
    float x = getPositionX();
	float z = getPositionZ();
	float y = getPositionY();

	UnicodeString campName = campOwner->getFirstName() +"'s Field Base Camp";
	CampTerminal* terminal = new CampTerminal(_this,campOwner->getNewItemID(),(x - 8.0f), z, (y + 2.0f));
	terminal->setDirection(0.000000f, 0.0f, 0.7f, -0.7f);
	terminal->setCustomName(campName);
	terminal->insertToZone(campOwner->getZone());
	// 0 : terminal
	addCampObject(terminal);
	// 1 & 2 : logs & fire
	addCampObject(campOwner->getNewItemID(), 0x6E4F92CB,  (x + 0.5f), z, (y + 0.5f), 0.000000f, 0.0f, 0.0f, 0.0f);
	addCampObject(campOwner->getNewItemID(), 0x96740DBC,  (x + 0.5f), z, (y + 0.5f), 0.000000f, 0.0f, 0.0f, 0.0f);
	// 3: medic station
	CraftingStation* medicStation = new CraftingStation(campOwner->getNewItemID(),0x2FF7F78B,UnicodeString("Food and Chemical Crafting Station"),"food_station_name ");
	medicStation->initializePosition((x + 0.65f),z,(y - 7.0f));
	medicStation->setDirection(0.0f, 0.0f, 0.0f, 0.0f);
	medicStation->setEffectiveness(100);
	addCampObject(medicStation);
	// 4 : chair
	addCampObject(campOwner->getNewItemID(), 0xB85D0E73, UnicodeString("A Lawn Chair"), (x - 12.0f), z, (y + 5.0f), 0.000000f, 0.0f, 0.75f, 0.6f);
	addCampObject(campOwner->getNewItemID(), 0xB85D0E73, UnicodeString("A Lawn Chair"), (x - 11.7f), z, (y + 6.5f), 0.000000f, 0.0f, 0.75f, 0.6f);
	addCampObject(campOwner->getNewItemID(), 0x634AA6E4, UnicodeString("A Chair"), (x + 1.7f), z, (y + 1.0f), 0.000000f, 0.0f, 0.6f, 0.8f);
	addCampObject(campOwner->getNewItemID(), 0x634AA6E4, UnicodeString("A Chair"), (x + 1.7f), z, (y + 2.5f), 0.000000f, 0.0f, 0.85f, 0.52f);
	addCampObject(campOwner->getNewItemID(), 0x634AA6E4, UnicodeString("A Chair"), (x + 4.7f), z, (y + 2.5f), 0.000000f, 0.0f, 0.85f, -0.52f);
	addCampObject(campOwner->getNewItemID(), 0x634AA6E4, UnicodeString("A Chair"), (x + 4.7f), z, (y + 1.0f), 0.000000f, 0.0f, 0.6f, -0.8f);

	addCampObject(campOwner->getNewItemID(), 0x634AA6E4, UnicodeString("A Chair"), (x - 0.5f), z, (y - 1.5f), 0.000000f, 0.0f, 0.75f, 0.65f);
	addCampObject(campOwner->getNewItemID(), 0x634AA6E4, UnicodeString("A Chair"), (x - 0.7f), z, (y - 3.2f), 0.000000f, 0.0f, 0.56f, 0.81f);
	addCampObject(campOwner->getNewItemID(), 0x634AA6E4, UnicodeString("A Chair"), (x + 2.7f), z, (y - 1.7f), 0.000000f, 0.0f, 0.74f, -0.67f);
	addCampObject(campOwner->getNewItemID(), 0x634AA6E4, UnicodeString("A Chair"), (x + 2.2f), z, (y - 3.8f), 0.000000f, 0.0f, -0.49f, 0.86f);

}

void FBCampSiteImplementation::abandonCamp() {
	CampSiteImplementation::abandonCamp();
	campObjects.get(3)->removeFromZone();
}
