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
#include "../../packets.h"

#include "BuildingObjectImplementation.h"

#include "cell/CellObject.h"

#include "../player/Player.h"
#include "../player/PlayerImplementation.h"
#include "../../Zone.h"
#include "../../ZoneClientSessionImplementation.h"

BuildingObjectImplementation::BuildingObjectImplementation(uint64 oid, bool staticBuild)
		: QuadTree(-1024, -1024, 1024, 1024), BuildingObjectServant(oid, BUILDING) {

	staticBuilding = staticBuild;

	persistent = false;
	updated = false;

	buildingType = UNKNOWN; // default building Type
	objectCRC = 0;

	setDefaultName();

	name = "";
	owner = "";

	objectType = SceneObjectImplementation::BUILDING;

	cells.setInsertPlan(SortedVector<SceneObject*>::NO_DUPLICATE);

	itemAttributes = new ItemAttributes();

	StringBuffer name;
	name << "Building = " << objectID;

	SceneObjectImplementation::setLoggingName(name.toString());
	SceneObjectImplementation::setLogging(false);
	SceneObjectImplementation::setGlobalLogging(true);
}

BuildingObjectImplementation::~BuildingObjectImplementation() {
	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);
		server->getZoneServer()->removeObject(cell);
		cell->removeUndeploymentEvent();
		cell->finalize();
	}

	delete itemAttributes;
	itemAttributes = NULL;
}

void BuildingObjectImplementation::addCell(CellObject* cell) {
	cells.put(cell);
}

void BuildingObjectImplementation::notifyInsert(QuadTreeEntry* obj) {
	SceneObjectImplementation* scno = (SceneObjectImplementation*) obj;

	if (scno->isPlayer() || scno->isNonPlayerCreature()) {
		for (int i = 0; i < cells.size(); ++i) {
			CellObject* cell = cells.get(i);

			for (int j = 0; j < cell->getChildrenSize(); ++j) {
				SceneObject* child = cell->getChild(j);

				if (child->isPlayer() || child->isNonPlayerCreature()) {
					child->addInRangeObject(obj, false);

					SceneObjectImplementation* a = (SceneObjectImplementation*) child->_getImplementation();
					if (a != NULL)
						obj->addInRangeObject(a, false);
				}
			}
		}
	}
}

void BuildingObjectImplementation::notifyDissapear(QuadTreeEntry* obj) {
	SceneObjectImplementation* scno = (SceneObjectImplementation*) obj;

	for (int i = 0; i < cells.size(); ++i) {
		CellObject* cell = cells.get(i);

		for (int j = 0; j < cell->getChildrenSize(); ++j) {
			SceneObject* child = cell->getChild(j);

			child->removeInRangeObject(obj);

			SceneObjectImplementation* a = (SceneObjectImplementation*) child->_getImplementation();

			if (a != NULL)
				obj->removeInRangeObject(a);
		}
	}
}

void BuildingObjectImplementation::sendTo(Player* player, bool doClose) {
	// send buio packets if not static

	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	if (staticBuilding)
		return;

	SceneObjectImplementation::create(client);

	//System::out << "generating building objects" << endl;
	BaseMessage* buio3 = new BuildingObjectMessage3((BuildingObject*) _this);
	player->sendMessage(buio3);

	BaseMessage* buio6 = new BuildingObjectMessage6((BuildingObject*) _this);
	player->sendMessage(buio6);

	sendCells(player, true);

	//System::out << "finished sending cells..." << endl;
	SceneObjectImplementation::close(client);

	//sendCellUpdates(player);

}

void BuildingObjectImplementation::sendCells(Player* player, bool doClose = true) {

	UpdateContainmentMessage* link;
	CellObjectMessage3* cellMsg3;
	CellObjectMessage6* cellMsg6;
	UpdateCellPermissionsMessage* perm;
	CellObject * cell;

	//System::out << "sending cells, size: " << cells.size() << endl;
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	for (int i = 1; i <= cells.size(); ++i) {
		//System::out << "sending cell cell: " << i << endl;
		cell = cells.get(i-1);

		BaseMessage* msg = new SceneObjectCreateMessage(cell);
		player->sendMessage(msg);

		link = new UpdateContainmentMessage(cell->getObjectID(), _this->getObjectID(), 0xFFFFFFFF);
		player->sendMessage(link);

		cellMsg3 = new CellObjectMessage3(cell->getObjectID(), cell->getCellNumber()); //
		player->sendMessage(cellMsg3);

		cellMsg6 = new CellObjectMessage6(cell->getObjectID());
		player->sendMessage(cellMsg6);

		perm = new UpdateCellPermissionsMessage(cell->getObjectID());
		player->sendMessage(perm);

		BaseMessage* close = new SceneObjectCloseMessage(cell);
		player->sendMessage(close);
	}
}


void BuildingObjectImplementation::sendCellUpdates(Player* player) {
	CellObjectDeltaMessage3* cdelta3;
	CellObject *cell;

	//System::out << "sending cells, size: " << cells.size() << endl;
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	for (int i = 1; i <= cells.size(); ++i) {
		//System::out << "sending cell cell: " << i << endl;
		cell = cells.get(i-1);

		CellObjectDeltaMessage3* msg = new CellObjectDeltaMessage3(cell);
		msg->updateCellNumber(i);
		msg->close();
		player->sendMessage(msg);
	}
}

void BuildingObjectImplementation::sendDestroyTo(Player* player) {
	//send destroy if not static

	//destroy(player->getClient());
}

void BuildingObjectImplementation::notifyInsertToZone(SceneObject* object) {
	SceneObjectImplementation* creoImpl = (SceneObjectImplementation*) object->_getImplementation();
	if (creoImpl == NULL)
		return;

	for (int i = 0; i < inRangeObjectCount(); ++i) {
		QuadTreeEntry* obj = getInRangeObject(i);
		SceneObjectImplementation* objImpl = (SceneObjectImplementation*) obj;

		//if (objImpl->isPlayer() || objImpl->isNonPlayerCreature()) {
			creoImpl->addInRangeObject(obj, false);
			obj->addInRangeObject(creoImpl, true);
		//}
	}
}

void BuildingObjectImplementation::parseItemAttributes() {

}

void BuildingObjectImplementation::setDefaultName()
{
	switch(getBuildingType())
	{
		case BuildingObjectImplementation::UNKNOWN: {
			switch(objectCRC) {
				case 0x90B33646: // object/building/player/shared_player_house_corellia_large_style_01.iff
				case 0x4BA49ED1: //	object/building/player/shared_player_house_corellia_large_style_02.iff
				case 0xFD0E9334: //	object/building/player/shared_player_house_corellia_medium_style_01.iff
				case 0x26193BA3: //	object/building/player/shared_player_house_corellia_medium_style_02.iff
				case 0xB09FC1F0: //	object/building/player/shared_player_house_corellia_small_style_01.iff
				case 0xF489E568: //	object/building/player/shared_player_house_corellia_small_style_01_floorplan_02.iff
				case 0x6B886967: //	object/building/player/shared_player_house_corellia_small_style_02.iff
				case 0x73E08240: //	object/building/player/shared_player_house_corellia_small_style_02_floorplan_02.iff
				case 0xB0D88CF3: //	object/building/player/shared_player_house_generic_large_style_01.iff
				case 0x6BCF2464: //	object/building/player/shared_player_house_generic_large_style_02.iff
				case 0x0E9790D4: //	object/building/player/shared_player_house_generic_medium_style_01.iff
				case 0xD5803843: //	object/building/player/shared_player_house_generic_medium_style_02.iff
				case 0x90F47B45: //	object/building/player/shared_player_house_generic_small_style_01.iff
				case 0xEF5EC851: //	object/building/player/shared_player_house_generic_small_style_01_floorplan_02.iff
				case 0x4BE3D3D2: //	object/building/player/shared_player_house_generic_small_style_02.iff
				case 0x6837AF79: //	object/building/player/shared_player_house_generic_small_style_02_floorplan_02.iff
				case 0x72CD9203: //	object/building/player/shared_player_house_naboo_large_style_01.iff
					defaultName = "base_building";
					break;
				case 0x4F81CB23: //	object/building/player/shared_player_house_naboo_medium_style_01.iff
					defaultName = "housing_naboo_medium";
					break;
				case 0x52E165B5: //	object/building/player/shared_player_house_naboo_small_style_01.iff
				case 0x89F6CD22: //	object/building/player/shared_player_house_naboo_small_style_02.iff
				case 0xB3EC8C88: //	object/building/player/shared_player_house_tatooine_large_style_01.iff
				case 0x37D4CD0D: //	object/building/player/shared_player_house_tatooine_medium_style_01.iff
				case 0x93C07B3E: //	object/building/player/shared_player_house_tatooine_small_style_01.iff
				case 0x48D7D3A9: //	object/building/player/shared_player_house_tatooine_small_style_02.iff
				case 0x9F3FA0EE: //	object/building/player/shared_player_merchant_tent_style_01.iff
				case 0x44280879: //	object/building/player/shared_player_merchant_tent_style_02.iff
				case 0x0D256FF4: //	object/building/player/shared_player_merchant_tent_style_03.iff
				default:
					defaultName = "base_building";
			}
		}

		case BuildingObjectImplementation::BANK:
		case BuildingObjectImplementation::CANTINA:
		case BuildingObjectImplementation::CAPITOL:
		case BuildingObjectImplementation::CLONING_FACILITY:
		case BuildingObjectImplementation::GARAGE:
		case BuildingObjectImplementation::GUILD:
		case BuildingObjectImplementation::GUILD_COMBAT:
		case BuildingObjectImplementation::GUILD_COMMERCE:
		case BuildingObjectImplementation::GUILD_THEATER:
		case BuildingObjectImplementation::GUILD_UNIVERSITY:
		case BuildingObjectImplementation::HOTEL:
		case BuildingObjectImplementation::MEDICAL_CENTER:
		case BuildingObjectImplementation::SHUTTLEPORT:
		case BuildingObjectImplementation::STARPORT:
		case BuildingObjectImplementation::THEMEPARK:
		case BuildingObjectImplementation::JUNKSHOP:
		case BuildingObjectImplementation::TAVERN:
		case BuildingObjectImplementation::BARRACKS:
		case BuildingObjectImplementation::REBEL_HQ:
		case BuildingObjectImplementation::IMPERIAL_HQ:
		case BuildingObjectImplementation::CITYHALL:
		case BuildingObjectImplementation::THEATER:
		case BuildingObjectImplementation::MUSEUM:
		case BuildingObjectImplementation::SALON:
		case BuildingObjectImplementation::SF_REBEL_FORWARD_BASE:
		case BuildingObjectImplementation::SF_IMPERIAL_FORWARD_BASE:
		case BuildingObjectImplementation::SF_REBEL_MINOR_BASE:
		case BuildingObjectImplementation::SF_IMPERIAL_MINOR_BASE:
		case BuildingObjectImplementation::SF_REBEL_MAJOR_BASE:
		case BuildingObjectImplementation::SF_IMPERIAL_MAJOR_BASE:
		case BuildingObjectImplementation::SF_REBEL_HQ:
		case BuildingObjectImplementation::SF_IMPERIAL_HQ:
		case BuildingObjectImplementation::REBEL_FORWARD_BASE:
		case BuildingObjectImplementation::IMPERIAL_FORWARD_BASE:
		case BuildingObjectImplementation::REBEL_MINOR_BASE:
		case BuildingObjectImplementation::IMPERIAL_MINOR_BASE:
		case BuildingObjectImplementation::REBEL_MAJOR_BASE:
		case BuildingObjectImplementation::IMPERIAL_MAJOR_BASE:
			defaultName = "base_building";
	}
}

