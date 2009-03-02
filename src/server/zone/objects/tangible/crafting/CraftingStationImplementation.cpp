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

#include "../../../packets.h"
#include "../../../objects.h"
#include "CraftingStation.h"
#include "CraftingStationImplementation.h"
#include "../../../ZoneClientSession.h"

CraftingStationImplementation::CraftingStationImplementation(uint64 object_id, uint32 tempCRC,
		const UnicodeString& n, const String& tempn) : CraftingStationServant(object_id, tempCRC, n, tempn,
				CRAFTINGTOOL) {
	objectCRC = tempCRC;
	templateTypeName = "obj_n";
	templateName = tempn;
	customName = n;
	init();
}

CraftingStationImplementation::CraftingStationImplementation(CreatureObject* creature, uint32 tempCRC,
		const UnicodeString& n, const String& tempn) : CraftingStationServant(creature, tempCRC, n, tempn,
				CRAFTINGTOOL) {
	objectCRC = tempCRC;
	templateTypeName = "obj_n";
	templateName = tempn;
	customName = n;
	init();
}

CraftingStationImplementation::~CraftingStationImplementation(){

}

void CraftingStationImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	//TODO:Cell permission check
	if (_this->getParent() != NULL) {
		bool cellPermission = true;

		if (_this->getParent()->isCell() && cellPermission) {
			if (_this->isTangible())
			omr->addRadialParent(10, 3, "@ui_radial:item_pickup");
		}
	}

	omr->finish();

	player->sendMessage(omr);
}

void CraftingStationImplementation::init() {

	objectSubType = TangibleObjectImplementation::CRAFTINGSTATION;

	if (objectCRC == 0xAF09A3F0 || objectCRC == 0x2BFCD5A1)
		stationType = CLOTHING;

	if (objectCRC == 0x2FF7F78B || objectCRC == 0xBACAE4C8)
		stationType = FOOD;

	if (objectCRC == 0x1BABCF4B || objectCRC == 0x94D50879)
		stationType = STRUCTURE;

	if (objectCRC == 0x72719FEA || objectCRC == 0x812DD757)
		stationType = WEAPON;

	if (objectCRC == 0x17929444 || objectCRC == 0x185987B1)
		stationType = SPACE;

	complexityLevel = 50;

}

int CraftingStationImplementation::useObject(Player* player) {
	System::out << "Use Crafting Station\n";
	return 0;
}

/*void CraftingToolImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;
	SceneObjectImplementation::create(client);
	if (container != NULL)
		link(client, container);
	TangibleObjectMessage3* tano3 = new TangibleObjectMessage3((TangibleObject*) _this);
	client->sendMessage(tano3);
	TangibleObjectMessage6* tano6 = new TangibleObjectMessage6((TangibleObject*) _this);
	client->sendMessage(tano6);
	if (doClose)
		SceneObjectImplementation::close(client);
	generateAttributes(player);
}*/

void CraftingStationImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;
	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage(_this);
	alm->insertAttribute("volume", "1");
	alm->insertAttribute("craft_tool_effectiveness", effectiveness);
	alm->insertAttribute("craft_tool_status", "@crafting:tool_status_ready");

	if(craftersName != ""){
		alm->insertAttribute("crafter", craftersName);
	}

	if(craftedSerial != ""){
		alm->insertAttribute("serial_number", craftedSerial);
	}

	player->sendMessage(alm);
}



