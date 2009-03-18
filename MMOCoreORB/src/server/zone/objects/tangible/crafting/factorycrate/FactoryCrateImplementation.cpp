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

/*
 * Dont use this constructor until i get it working. use the other ones please :)
 */
FactoryCrateImplementation::FactoryCrateImplementation(uint64 object_id, TangibleObject* item)
	:FactoryCrateServant(object_id, objectCRC, customName, templateName) {

	linkTangibleObject(item);//sets this object's objectCRC and templateName
	templateTypeName = "factory_n";
	customName = item->getCustomName();
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
	objectSubType = TangibleObjectImplementation::FACTORYCRATE;

}

void FactoryCrateImplementation::linkTangibleObject(TangibleObject* item){

	if (item==NULL){
		objectCRC = 0x28D7B8E0;
		templateName = "generic_items_crate";
	}

	if (item->getObjectType() & TangibleObjectImplementation::WEAPON) {
		objectCRC = 0xF30332FF; //weapon
		templateName = "weapons_factory_crate";
	}
	else if (item->getObjectType() & TangibleObjectImplementation::ARMOR) {
		objectCRC = 0x5F411179; //armor
		templateName = "armor_crate";
	}
	else if (item->getObjectType() & TangibleObjectImplementation::CLOTHING) {
		objectCRC = 0x8B99A193; //clothing
		templateName = "clothing_factory_crate";
	}
	else if ((item->getObjectType() & TangibleObjectImplementation::FOOD) || (item->getObjectType() & TangibleObjectImplementation::DRINK)) {
		objectCRC = 0x46A16B2B; //food
		templateName = "food_crate";
	}
	else if (item->getObjectType() & TangibleObjectImplementation::INSTALLATIONDEED) {
		objectCRC = 0x226A85F8; //installation
		templateName = "installation_crate";
	}
	else if (item->getObjectType() & TangibleObjectImplementation::PHARMACEUTICAL) {
		objectCRC = 0xCABDD3C7; //chemicals
		templateName = "chemicals_crate";
	}
	else if (item->getObjectType() & TangibleObjectImplementation::FURNITURE) {
		objectCRC = 0xE75204A1; //furniture
		templateName = "furniture_crate";
	}
	else if (item->getObjectType() & TangibleObjectImplementation::ELECTRONICS) {
		objectCRC = 0x5E744B09; //electronics
		templateName = "electronics_crate";
	}
	else {
		objectCRC = 0x28D7B8E0; //generic items
		templateName = "generic_items_crate";
	}

	_this->setTangibleObject(item);
}

int FactoryCrateImplementation::useObject(Player* player) {
	if (_this->getTangibleObject()==NULL)
		return 0;

	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();
	if (_this->getObjectCount() >= 0){
		_this->setObjectCount(_this->getObjectCount()-1);

		TangibleObject* newItem = itemManager->clonePlayerObjectTemplate(player->getNewItemID(), _this->getTangibleObject());

		player->addInventoryItem(newItem);
		newItem->sendTo(player);

		sendDeltas(player);

	}
	if (getObjectCount() < 0) {
		player->removeInventoryItem(_this);
		_this->sendDestroyTo(player);
		itemManager->deletePlayerItem(player, _this, false);
		_this->getTangibleObject()->finalize();
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
	if (!obj->isPlayer() || _this->getTangibleObject()==NULL)
		return;
	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage(_this);
	addAttributes(alm);

	player->sendMessage(alm);

}

void FactoryCrateImplementation::addAttributes(AttributeListMessage* alm){

	alm->insertAttribute("volume", "1");
	alm->insertAttribute("crafter", getCraftersName());
	alm->insertAttribute("serial_number", _this->getTangibleObject()->getCraftedSerial());
	alm->insertAttribute("factory_count", getObjectCount());
	alm->insertAttribute("factory_attribs", "----------");//"#pcontrast2 ----------\\#");
	alm->insertAttribute("object_type", _this->getTangibleObject()->getObjectType());//"@got_n:component_weapon_ranged");
	alm->insertAttribute("original_name", _this->getTangibleObject()->getCustomName());//"@craft_weapon_ingredients_n:blaster_power_handler");
	_this->getTangibleObject()->addAttributes(alm);
}



