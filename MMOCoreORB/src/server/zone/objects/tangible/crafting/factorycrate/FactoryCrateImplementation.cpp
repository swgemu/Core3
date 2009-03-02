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

#include "../../../../packets.h"
#include "../../../../objects.h"
#include "../component/Component.h"
#include "../component/ComponentImplementation.h"
#include "FactoryCrate.h"
#include "FactoryCrateImplementation.h"
#include "../../../../ZoneClientSession.h"

FactoryCrateImplementation::FactoryCrateImplementation(uint64 object_id, uint32 tempCRC,
		const UnicodeString& n, const String& tempn) : FactoryCrateServant(object_id, tempCRC, n, tempn,
				FACTORYCRATE) {
	objectCRC = tempCRC;
	templateTypeName = "factory_n";
	templateName = tempn;
	customName = n;
	init();
}

FactoryCrateImplementation::FactoryCrateImplementation(CreatureObject* creature, uint32 tempCRC,
		const UnicodeString& n, const String& tempn) : FactoryCrateServant(creature, tempCRC, n, tempn,
				FACTORYCRATE) {
	objectCRC = tempCRC;
	templateTypeName = "factory_n";
	templateName = tempn;
	customName = n;
	init();
}


FactoryCrateImplementation::~FactoryCrateImplementation(){

}

void FactoryCrateImplementation::sendRadialResponseTo(Player* player, ObjectMenuResponse* omr) {
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

void FactoryCrateImplementation::init() {
	linkedItem = NULL;
	objectSubType = TangibleObjectImplementation::FACTORYCRATE;
}

void FactoryCrateImplementation::linkTangibleObject(TangibleObject* item){
	if (item==NULL)
		return;
	if (item->getObjectType() & TangibleObjectImplementation::WEAPON) {
		setObjectCRC(0xF30332FF); //weapon
	}
	else if (item->getObjectType() & TangibleObjectImplementation::ARMOR) {
		setObjectCRC(0x5F411179); //armor
	}
	else if (item->getObjectType() & TangibleObjectImplementation::CLOTHING) {
		setObjectCRC(0x8B99A193); //clothing
	}
	else if ((item->getObjectType() & TangibleObjectImplementation::FOOD) || (item->getObjectType() & TangibleObjectImplementation::DRINK)) {
		setObjectCRC(0x46A16B2B); //food
	}
	else if (item->getObjectType() & TangibleObjectImplementation::INSTALLATIONDEED) {
		setObjectCRC(0x226A85F8); //installation
	}
	else if (item->getObjectType() & TangibleObjectImplementation::PHARMACEUTICAL) {
		setObjectCRC(0xCABDD3C7); //chemicals
	}
	else if (item->getObjectType() & TangibleObjectImplementation::FURNITURE) {
		setObjectCRC(0xE75204A1); //furniture
	}
	else if (item->getObjectType() & TangibleObjectImplementation::ELECTRONICS) {
		setObjectCRC(0x5E744B09); //electronics
	}
	else {
		setObjectCRC(0x28D7B8E0); //generic items
	}

	_this->setLinkedItem(item);
}

int FactoryCrateImplementation::useObject(Player* player) {
	if (_this->getLinkedItem()==NULL)
		return 0;

	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();
	if (_this->getObjectCount()>0){
		_this->setObjectCount(_this->getObjectCount()-1);

		TangibleObject* newItem = itemManager->clonePlayerObjectTemplate(player->getNewItemID(), _this->getLinkedItem());

		player->addInventoryItem(newItem);
		newItem->sendTo(player);

		sendDeltas(player);

	}
	if (getObjectCount() <= 0) {
		player->removeInventoryItem(_this);
		_this->sendDestroyTo(player);
		itemManager->deletePlayerItem(player, _this, false);
		_this->getLinkedItem()->finalize();
		_this->finalize();
	}
	return 1;

}

void FactoryCrateImplementation::sendDeltas(Player* player) {

	TangibleObjectDeltaMessage3* todm3 = new TangibleObjectDeltaMessage3(_this);

	todm3->setQuantity(_this->getObjectCount());
	todm3->close();

	player->sendMessage(todm3);
}

void FactoryCrateImplementation::parseItemAttributes(){

}

void FactoryCrateImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer() || _this->getLinkedItem()==NULL)
		return;
	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage(_this);
	addAttributes(alm);

	player->sendMessage(alm);

}

void FactoryCrateImplementation::addAttributes(AttributeListMessage* alm){

	alm->insertAttribute("volume", "1");
	alm->insertAttribute("crafter", getCraftersName());
	alm->insertAttribute("serial_number", _this->getLinkedItem()->getCraftedSerial());
	alm->insertAttribute("factory_count", getObjectCount());
	alm->insertAttribute("factory_attribs", "----------");//"#pcontrast2 ----------\\#");
	alm->insertAttribute("object_type", _this->getLinkedItem()->getObjectType());//"@got_n:component_weapon_ranged");
	alm->insertAttribute("original_name", _this->getLinkedItem()->getCustomName());//"@craft_weapon_ingredients_n:blaster_power_handler");
	String itemAttribs = _this->getLinkedItem()->getAttributes();

	int index1 = 0;
	int index2;
	int index3;

	while ((index2 = itemAttribs.indexOf(":", index1)) != -1) {
		String attrPair = itemAttribs.subString(index1, index2);

		if ((index3 = attrPair.indexOf("=", 0)) != -1) {
			String key = attrPair.subString(0, index3);

			String value = attrPair.subString(index3 + 1, attrPair.length());

			alm->insertAttribute(key, value);
		}

		index1 = index2 + 1;
	}

}



