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
	stfFile = "factory_n";
	stfName = tempn;
	customName = n;
	init();
}

FactoryCrateImplementation::FactoryCrateImplementation(uint64 object_id, TangibleObject* tano)
	: FactoryCrateServant(object_id, FACTORYCRATE) {

	objectCRC = getCRC(tano);
	stfFile = "factory_n";
	stfName = getTempN(tano);
	String name = tano->getCustomName().toString();
	if (name.isEmpty())
		name = tano->getStfName() + "(" + tano->getCraftedSerial() + ")";
	UnicodeString uniName(name);
	customName = uniName;
	init();
}

FactoryCrateImplementation::FactoryCrateImplementation(uint64 object_id)
	:FactoryCrateServant(object_id, FACTORYCRATE) {

	objectCRC = 0x28D7B8E0;
	stfName = "generic_items_crate";
	stfFile = "factory_n";
	customName = "A Factory Crate";
}

FactoryCrateImplementation::~FactoryCrateImplementation(){

}

uint32 FactoryCrateImplementation::getCRC(TangibleObject* tano) {

	if (tano->isWeapon())
		return 0xF30332FF; //weapon
	else if (tano->isArmor())
		return 0x5F411179; //armor
	else if (tano->isClothing())
		return 0x8B99A193; //clothing
	else if (tano->isConsumable())
		return 0x46A16B2B;//food
	else if (tano->isPharmaceutical())
		return 0xCABDD3C7; //chemicals
	else if (tano->isFurniture())
		return 0xE75204A1; //furniture
	else if (tano->isElectronics())
		return 0x5E744B09; //electronics
	else if (tano->isInstallation())
		return 0x226A85F8; //installation
	else
		return 0x28D7B8E0; //generic items
}

String FactoryCrateImplementation::getTempN(TangibleObject* tano) {

	if (tano->isWeapon())
		return "weapons_factory_crate"; //weapon
	else if (tano->isArmor())
		return "armor_crate"; //armor
	else if (tano->isClothing())
		return "clothing_factory_crate"; //clothing
	else if (tano->isConsumable())
		return "food_crate";//food
	else if (tano->isPharmaceutical())
		return "chemicals_crate"; //chemicals
	else if (tano->isFurniture())
		return "furniture_crate"; //furniture
	else if (tano->isElectronics())
		return "electronics_crate"; //electronics
	else if (tano->isInstallation())
		return "installation_crate"; //installation
	else
		return "generic_items_crate"; //generic items
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

int FactoryCrateImplementation::useObject(Player* player) {
	ManagedReference<TangibleObject> tano = _this->getTangibleObject();
	if (tano == NULL)
		return 0;

	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();
	if (_this->getObjectCount() >= 0){
		_this->setObjectCount(_this->getObjectCount()-1);

		TangibleObject* newItem = itemManager->clonePlayerObjectTemplate(player->getNewItemID(), tano.get());

		player->addInventoryItem(newItem);
		newItem->sendTo(player);

		sendDeltas(player);

	}
	if (getObjectCount() < 0) {
		player->removeInventoryItem(_this);
		_this->sendDestroyTo(player);
		itemManager->deletePlayerItem(player, _this, false);
		tano->finalize();
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
	String attr("objectcount");
	setObjectCount(itemAttributes->getIntAttribute(attr));

}

void FactoryCrateImplementation::generateAttributes(SceneObject* obj) {
	TangibleObject* tano = _this->getTangibleObject();
	if (!obj->isPlayer() || tano == NULL)
		return;
	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage(_this);
	addAttributes(alm);

	player->sendMessage(alm);

}

void FactoryCrateImplementation::addAttributes(AttributeListMessage* alm){

	ManagedReference<TangibleObject> tano = _this->getTangibleObject();
	if(tano == NULL)
		return;

	alm->insertAttribute("volume", "1");
	alm->insertAttribute("crafter", getCraftersName());
	alm->insertAttribute("serial_number", tano->getCraftedSerial());
	alm->insertAttribute("factory_count", getObjectCount());
	alm->insertAttribute("factory_attribs", "----------");//"#pcontrast2 ----------\\#");
	alm->insertAttribute("object_type", tano->getObjectType());//"@got_n:component_weapon_ranged");
	alm->insertAttribute("original_name", tano->getCustomName());//"@craft_weapon_ingredients_n:blaster_power_handler");
	tano->addAttributes(alm);
}



