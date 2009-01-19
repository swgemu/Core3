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

#include "../../../ZoneClientSession.h"
#include "../../player/Player.h"

#include "../../../packets.h"

#include "Wearable.h"
#include "WearableImplementation.h"

#include "../../../managers/player/PlayerManager.h"

#include "../../../objects/draftschematic/DraftSchematicValuesImplementation.h"

WearableImplementation::WearableImplementation(uint64 objid, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp)
		: WearableServant(objid, CLOTHING) {
	objectCRC = tempCRC;

	customName = n;

	templateTypeName = "wearables_name";
	templateName = tempn;

	equipped = eqp;
	init();
}

WearableImplementation::WearableImplementation(CreatureObject* creature, uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp)
		: WearableServant(oid, CLOTHING) {

	objectCRC = tempCRC;

	customName = n;

	templateTypeName = "wearables_name";
	templateName = tempn;

	if ((equipped = eqp))
		setParent(creature, 0x04);
	else
		setParent((TangibleObject*) creature->getInventory(), 0xFFFFFFFF);
	init();
}

WearableImplementation::WearableImplementation(CreatureObject* creature, uint32 tempCRC, const UnicodeString& n, const String& tempn, bool eqp)
		: WearableServant(creature->getNewItemID(), CLOTHING) {
	//creature->getNewItemID();
	objectCRC = tempCRC;

	customName = n;

	templateTypeName = "wearables_name";
	templateName = tempn;

	if ((equipped = eqp))
		setParent(creature, 0x04);
	else
		setParent((TangibleObject*) creature->getInventory(), 0xFFFFFFFF);
	init();
}

void WearableImplementation::parseItemAttributes() {

	maxCondition = itemAttributes->getMaxCondition();
	conditionDamage = maxCondition - itemAttributes->getCurrentCondition();

	String name = "sockets";
	sockets = itemAttributes->getIntAttribute(name);

	name = "skillMod0Type";
	skillMod0Type = itemAttributes->getIntAttribute(name);
	name = "skillMod0Value";
	skillMod0Value = itemAttributes->getIntAttribute(name);

	name = "skillMod1Type";
	skillMod1Type = itemAttributes->getIntAttribute(name);
	name = "skillMod1Value";
	skillMod1Value = itemAttributes->getIntAttribute(name);

	name = "skillMod2Type";
	skillMod2Type = itemAttributes->getIntAttribute(name);
	name = "skillMod2Value";
	skillMod2Value = itemAttributes->getIntAttribute(name);

	name = "socket0Type";
	socket0Type = itemAttributes->getIntAttribute(name);
	name = "socket0Value";
	socket0Value = itemAttributes->getIntAttribute(name);

	name = "socket1Type";
	socket1Type = itemAttributes->getIntAttribute(name);
	name = "socket1Value";
	socket1Value = itemAttributes->getIntAttribute(name);

	name = "socket2Type";
	socket2Type = itemAttributes->getIntAttribute(name);
	name = "socket2Value";
	socket2Value = itemAttributes->getIntAttribute(name);

	name = "socket3Type";
	socket3Type = itemAttributes->getIntAttribute(name);
	name = "socket3Value";
	socket3Value = itemAttributes->getIntAttribute(name);
}

void WearableImplementation::init() {
	setConditionDamage(0);
	setCondition(1000,1000);

	skillMod0Type = 0;
	skillMod0Value = 0;

	skillMod1Type = 0;
	skillMod1Value = 0;

	skillMod2Type = 0;
	skillMod2Value = 0;

	setSockets(0);
	socket0Type = 0;
	socket0Value = 0;

	socket1Type = 0;
	socket1Value = 0;

	socket2Type = 0;
	socket2Value = 0;

	socket3Type = 0;
	socket3Value = 0;
}

void WearableImplementation::sendTo(Player* player, bool doClose) {
	ZoneClientSession* client = player->getClient();
	if (client == NULL)
		return;

	SceneObjectImplementation::create(client);

	if (parent != NULL)
		link(client, parent);

	BaseMessage* tano3 = new TangibleObjectMessage3((TangibleObject*) _this);
	client->sendMessage(tano3);

	if (doClose)
		SceneObjectImplementation::close(client);

}

void WearableImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
	if (player->getInventoryItem(getObjectID()) != NULL) {

		if (getConditionDamage() > 0)
			omr->addRadialItem(0, 70, 3, "Repair");
	}

	//TODO:Cell permission check
	if (_this->getParent() != NULL) {
		bool cellPermission = true;

		if (_this->getParent()->isCell() && cellPermission) {
			omr->addRadialItem(0, 10, 3, "Pickup");
		}
	}

	omr->finish();
	player->sendMessage(omr);
}

void WearableImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;

	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);

}

void WearableImplementation::updateCraftingValues(DraftSchematic* draftSchematic){
	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	int hitPoints = (int)craftingValues->getCurrentValue("hitpoints");
	setCondition(hitPoints,hitPoints);

	int sockets = (int)craftingValues->getCurrentValue("sockets");
	setSockets(sockets);
}

void WearableImplementation::setSocket(int index, int type, int value) {
	switch (index) {
	case 0:
		setSocket0Value(value);
		setSocket0Type(type);
		break;
	case 1:
		setSocket1Value(value);
		setSocket1Type(type);
		break;
	case 2:
		setSocket2Value(value);
		setSocket2Type(type);
		break;
	case 3:
		setSocket3Value(value);
		setSocket3Type(type);
		break;
	}
}

void WearableImplementation::setSocketValue(int index, int value) {
	switch (index) {
	case 0:
		setSocket0Value(value);
		break;
	case 1:
		setSocket1Value(value);
		break;
	case 2:
		setSocket2Value(value);
		break;
	case 3:
		setSocket3Value(value);
		break;
	}
}

void WearableImplementation::setSocketType(int index, int type) {
	switch (index) {
	case 0:
		setSocket0Type(type);
		break;
	case 1:
		setSocket1Type(type);
		break;
	case 2:
		setSocket2Type(type);
		break;
	case 3:
		setSocket3Type(type);
		break;
	}
}

int WearableImplementation::getSocketType(int index) {
	switch (index) {
	case 0:
		return socket0Type;
		break;
	case 1:
		return socket1Type;
		break;
	case 2:
		return socket2Type;
		break;
	case 3:
		return socket3Type;
		break;
	}
	return -1;
}

int WearableImplementation::getSocketValue(int index) {
	switch (index) {
	case 0:
		return socket0Value;
		break;
	case 1:
		return socket1Value;
		break;
	case 2:
		return socket2Value;
		break;
	case 3:
		return socket3Value;
		break;
	}
	return 0;
}

int WearableImplementation::addSkillMod(int skillModType, int skillModValue) {

	if (skillModType == 0 || skillModValue == 0) {
		return -1;
	}

	int i = 0;

	for (; i < 4; i++) {
		if (getSocketType(i) == skillModType) {
			int modValue = getSocketValue(i);

			if (skillModValue <= modValue)
				return -2;
			else if (skillModValue > modValue){
				setSocketValue(i, skillModValue);
				updated = true;
				return -3;
			}
		}
	}

	if (sockets > 0)
		for (i = 0; i < 4; i++)
			if (getSocketValue(i) == 0) {
				setSocket(i, skillModType, skillModValue);
				updated = true;
				setSockets(sockets - 1);
				return i;
			}

	return -1;
}

void WearableImplementation::addAttributes(AttributeListMessage* alm) {
	StringBuffer conditionStr;
	conditionStr << getCondition() << '/' << maxCondition;
	alm->insertAttribute("Condition", conditionStr);

	alm->insertAttribute("Volume", "1");

	if(sockets > 0)
		alm->insertAttribute("Sockets", sockets);

	if (skillMod0Type != 0)
		generateSkillMods(alm, skillMod0Type, skillMod0Value);

	if (skillMod1Type != 0)
		generateSkillMods(alm, skillMod1Type, skillMod1Value);

	if (skillMod2Type != 0)
		generateSkillMods(alm, skillMod2Type, skillMod2Value);

	if (socket0Type != 0)
		generateSkillMods(alm, socket0Type, socket0Value);

	if (socket1Type != 0)
		generateSkillMods(alm, socket1Type, socket1Value);

	if (socket2Type != 0)
		generateSkillMods(alm, socket2Type, socket2Value);

	if (socket3Type != 0)
		generateSkillMods(alm, socket3Type, socket3Value);

	if (craftersName != "") {

		alm->insertAttribute("crafter", craftersName);
	}
	if (craftedSerial != "") {

		alm->insertAttribute("serial_number", craftedSerial);
	}
}

