/*
 * CamoKitImplementation2.cpp
 *
 *  Created on: Oct 20, 2008
 *      Author: swgdev
 */

#include "../../../managers/item/ItemManager.h"

#include "../TangibleObject.h"

#include "engine/engine.h"

#include "CamoKitImplementation.h"

#include "../../../packets.h"

CamoKitImplementation::CamoKitImplementation(unsigned long long oid, unsigned int tempCRC, const UnicodeString& n, const String& tempn)
	: CamoKitServant(oid, CAMOKIT) {
		objectCRC = tempCRC;

		templateTypeName = "obj_n";
		templateName = tempn;

		name = n;

		setPlanet(0);
		setUsesRemaining(5);
		setEquipped(false);

}
CamoKitImplementation::CamoKitImplementation(Player* player, unsigned int tempCRC, const UnicodeString& n, const String& tempn)
: CamoKitServant(player->getNewItemID(), CAMOKIT) {
	objectCRC = tempCRC;

	templateTypeName = "obj_n";
	templateName = tempn;

	name = n;
	planet = 0;


	usesRemaining = 5 ;

    setContainer((TangibleObject*) player->getInventory(), 0xFFFFFFFF);

    setEquipped(false);
}

void CamoKitImplementation::useCharge(Player* player) {
	if (usesRemaining <= 0) {
		remove(player);
		return;
	}

	setUsesRemaining(getUsesRemaining() - 1);
	updated = true;

	if (usesRemaining == 0)
		remove(player);
}

int CamoKitImplementation::getPlanet() {
	return planet;
}

int CamoKitImplementation::getUsesRemaining() {
	return usesRemaining;
}

int CamoKitImplementation::getConcealMin() {
	return concealMin;
}


void CamoKitImplementation::setPlanet(const int tp) {
	planet = tp;
	String attr = "planetType";
	itemAttributes->setIntAttribute(attr, planet);
}

void CamoKitImplementation::setUsesRemaining(const int us) {
	usesRemaining = us;
	String attr = "uses";
	itemAttributes->setIntAttribute(attr, usesRemaining);
}

void CamoKitImplementation::setConcealMin(const int min) {
	concealMin = min;
	String attr = "concealMin";
	itemAttributes->setIntAttribute(attr, concealMin);
}

void CamoKitImplementation::remove(Player* player) {
	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();

	itemManager->deletePlayerItem(player, _this, false);

	player->removeInventoryItem(objectID);

	BaseMessage* msg = new SceneObjectDestroyMessage(objectID);
	player->sendMessage(msg);
}

void CamoKitImplementation::sendDeltas(Player* player) {
	TangibleObjectDeltaMessage3 * dtano3 = new TangibleObjectDeltaMessage3((TangibleObject*)_this);
	dtano3->addIntUpdate(7, (getUsesRemaining() == 1) ? 0 : getUsesRemaining()); //Update the number of charges on the pack in inventory.
	dtano3->close();
	player->sendMessage(dtano3);
}

void CamoKitImplementation::addHeaderAttributes(AttributeListMessage* alm) {
	alm->insertAttribute("volume", "1");
	alm->insertAttribute("counter_uses_remaining", getUsesRemaining());

	if(craftersName != ""){
		alm->insertAttribute("crafter", craftersName);
	}

	if(craftedSerial != ""){
		alm->insertAttribute("serial_number", craftedSerial);
	}
}

void CamoKitImplementation::addFooterAttributes(AttributeListMessage* alm) {
	//alm->insertAttribute("healing_ability", getPlanet());
}

void CamoKitImplementation::addAttributes(AttributeListMessage* alm) {
	addHeaderAttributes(alm);
	addFooterAttributes(alm);
}

void CamoKitImplementation::generateAttributes(SceneObject* obj) {
	if (!obj->isPlayer())
		return;

	Player* player = (Player*) obj;
	AttributeListMessage* alm = new AttributeListMessage((TangibleObject*) _this);

	addAttributes(alm);

	player->sendMessage(alm);
}

void CamoKitImplementation::parseItemAttributes() {
	String attr = "uses";
	setUsesRemaining(itemAttributes->getIntAttribute(attr));
	attr = "planetType";
	setPlanet(itemAttributes->getIntAttribute(attr));
	attr = "concealMin";
	setConcealMin(itemAttributes->getIntAttribute(attr));
}
