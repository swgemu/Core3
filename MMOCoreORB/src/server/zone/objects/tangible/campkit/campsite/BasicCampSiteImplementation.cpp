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

#include "BasicCampSiteImplementation.h"
#include "../CampKit.h"

BasicCampSiteImplementation::BasicCampSiteImplementation(Player* player, uint64 oid, CampKit* campKit) : BasicCampSiteServant(player, oid,  campKit) {
	objectID = oid;


	name = UnicodeString("0");;
	defaultName = "";

	campOwner = player;

	campArea = NULL;
	visitor = new VisitorList();
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

BasicCampSiteImplementation::~BasicCampSiteImplementation() {
	campArea = NULL;
	despawnEvent = NULL;
	if (abandonEvent != NULL)
		abandonEvent->endNow();

	abandonEvent = NULL;
	visitor = NULL;
	container = NULL;
	zone = NULL;
}

void BasicCampSiteImplementation::init() {
	persistent = false;
	updated = false;

	building = NULL;

	objectCount = 0;

	objectType = SceneObjectImplementation::TANGIBLE;
	objectSubType = TangibleObjectImplementation::MISC;

	equipped = false;

	pvpStatusBitmask = 0;

	name = UnicodeString("Basic Camp");
	defaultName = "basic_name";
	objectCRC = 0x897A440;
	campModifier = 60;
	aggroMod = 0;
}

void BasicCampSiteImplementation::spawnCampItems() {
    float x = getPositionX();
	float z = getPositionZ();
	float y = getPositionY();

	SceneObject* terminal = new CampTerminal(_this,campOwner->getNewItemID(),(x + 2.3f), z, (y + 1.7f));
	terminal->setDirection(0.000000f, 0.0f, 1.0f, -0.7f);
	terminal->insertToZone(campOwner->getZone());
	// 0 : terminal
	addCampObject(terminal);
	// 2 : logs & fire
	addCampObject(campOwner->getNewItemID(), 0x6E4F92CB,  (x + 0.506110f), z, (y - 0.596347f), 0.000000f, 0.0f, 0.0f, 0.0f);
	addCampObject(campOwner->getNewItemID(), 0x96740DBC,  (x + 0.506110f), z, (y - 0.596347f), 0.000000f, 0.0f, 0.0f, 0.0f);
	// 3 : chair
	addCampObject(campOwner->getNewItemID(), 0xB85D0E73, UnicodeString("A Lawn Chair"), (x + 0.863f), z, (y -2.85f), 0.000000f, 0.0f, -0.009319f, -0.999957f);

}
