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


#include "Drink.h"
#include "DrinkImplementation.h"

#include "../../../../objects.h"

DrinkImplementation::DrinkImplementation(uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempn)
		: DrinkServant(oid, tempCRC, n, tempn, TangibleObjectImplementation::DRINK) {

	objectCRC = tempCRC;

	customName = n;
	templateName = tempn;

	init();
}

DrinkImplementation::DrinkImplementation(CreatureObject* creature, uint64 oid, uint32 tempCRC, const UnicodeString& n, const String& tempn)
		: DrinkServant(creature, oid, tempCRC, n, tempn, TangibleObjectImplementation::DRINK) {

	objectCRC = tempCRC;

	customName = n;
	templateName = tempn;

	setParent((TangibleObject*) creature->getInventory(), 0xFFFFFFFF);

	init();
}

DrinkImplementation::~DrinkImplementation() {
}

void DrinkImplementation::init() {
	quantity = 1;
	filling = 1;
	flavor = 1;
	nutrition = 1;
}

int DrinkImplementation::useObject(Player* player) {
	//TODO: add an effect to the player, increase filling, etc.
	return 1;
}

void DrinkImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);
}

void DrinkImplementation::updateCraftingValues(DraftSchematic* draftSchematic){
	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	int hitPoints = (int)craftingValues->getCurrentValue("hitpoints");
	//do something with hitPoints
	int nutrition = (int)craftingValues->getCurrentValue("nutrition");
	setNutrition(nutrition);

	int flavor = (int)craftingValues->getCurrentValue("flavor");
	setFlavor(flavor);

	int quantity = (int)craftingValues->getCurrentValue("quantity");
	setQuantity(quantity);

	int filling = (int)craftingValues->getCurrentValue("filling");
	setFilling(filling);
}

void DrinkImplementation::parseItemAttributes() {
	String attr = "nutrition";
	setNutrition(itemAttributes->getIntAttribute(attr));

	attr = "flavor";
	setFlavor(itemAttributes->getIntAttribute(attr));

	attr = "quantity";
	setQuantity(itemAttributes->getIntAttribute(attr));

	attr = "filling";
	setFilling(itemAttributes->getIntAttribute(attr));
}

void DrinkImplementation::addHeaderAttributes(AttributeListMessage* alm) {
	alm->insertAttribute("volume", "1");
	//alm->insertAttribute("counter_uses_remaining", getUsesRemaining());

	if (craftersName != ""){
		alm->insertAttribute("crafter", craftersName);
	}

	if (craftedSerial != ""){
		alm->insertAttribute("serial_number", craftedSerial);
	}
}

void DrinkImplementation::addFooterAttributes(AttributeListMessage* alm) {

}

void DrinkImplementation::addAttributes(AttributeListMessage* alm) {
	addHeaderAttributes(alm);
	addFooterAttributes(alm);
}
