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

#include "objects.h"
#include "../../../../packets.h"

#include "../../../../ZoneClientSessionImplementation.h"

#include "../../../../managers/resource/ResourceManager.h"
#include "../../../../managers/resource/ResourceManagerImplementation.h"

#include "../../../../managers/item/ItemManager.h"

ResourceDeedImplementation::ResourceDeedImplementation(CreatureObject* creature, uint32 tempcrc, const UnicodeString& n, const String& tempn)
	: ResourceDeedServant(creature, tempcrc, n, tempn, DEED) {

	objectID = creature->getNewItemID();
	objectCRC = tempcrc;
	customName = n;
	stfName = tempn;
	init();
}

ResourceDeedImplementation::ResourceDeedImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn)
	: ResourceDeedServant(objid, tempcrc, n, tempn, DEED) {

	objectID = objid;
	objectCRC = tempcrc;
	customName = n;
	stfName = tempn;
	init();
}

ResourceDeedImplementation::~ResourceDeedImplementation() {

}

void ResourceDeedImplementation::init() {

	//deedSubType = DEED;
	objectSubType = DEED;

}

void ResourceDeedImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	//TODO:Cell permission check
	if (_this->getParent() != NULL) {
		bool cellPermission = true;

		if (_this->getParent()->isCell() && cellPermission) {
			if (_this->isTangible())
			omr->addRadialParent(10, 3, "@ui_radial:item_pickup");
		}
	}

	omr->addRadialParent(20, 3, "@ui_radial:item_use");

	omr->finish();

	player->sendMessage(omr);
}

int ResourceDeedImplementation::useObject(Player* player) {

	ResourceManager* resourceManager = player->getZone()->getZoneServer()->getResourceManager();

	SuiListBox* sui1 = new SuiListBox(player, SuiWindowType::FREE_RESOURCE);//beginning of sui chain

	sui1->setPromptTitle("Resources");
	sui1->setPromptText("Choose resource class.");
	sui1->setCancelButton(true, "");
	player->addSuiBox(sui1);
	resourceManager->generateSUI(player, sui1);

	player->setResourceDeedID(_this->getObjectID());
	uint64 objID = player->getResourceDeedID();
	player->sendMessage(sui1->generateMessage());

	return 1;
}

void ResourceDeedImplementation::destroyDeed(Player* player) {
	_this->sendDestroyTo(player);

	Zone* zone = player->getZone();
	if (zone != NULL) {
		ZoneServer* zoneServer = zone->getZoneServer();

		ItemManager* itemManager;

		if (zoneServer != NULL && ((itemManager = zoneServer->getItemManager()) != NULL)) {
			player->removeInventoryItem(objectID);
			itemManager->deletePlayerItem(player, _this, false);

			_this->finalize();
		}
	}
}
