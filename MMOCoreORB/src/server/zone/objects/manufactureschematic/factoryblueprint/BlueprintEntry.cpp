/*
 * BlueprintEntry.cpp
 *
 *  Created on: Apr 3, 2011
 *      Author: kyle
 */

#include "BlueprintEntry.h"
#include "server/zone/objects/resource/ResourceContainer.h"

BlueprintEntry::BlueprintEntry() : Serializable() {

	addSerializableVariables();
}

BlueprintEntry::BlueprintEntry(const BlueprintEntry& entry) : Object(), Serializable() {

	type = entry.type;
	key = entry.key;
	displayedName = entry.displayedName;
	serialNumber = entry.serialNumber;
	identical = entry.identical;
	quantity = entry.quantity;

	addSerializableVariables();
}

BlueprintEntry::BlueprintEntry(TangibleObject* ingredient, bool isIdentical) : Serializable() {

	createEntry(ingredient, isIdentical);

	addSerializableVariables();
}

BlueprintEntry::~BlueprintEntry() {

}

BlueprintEntry& BlueprintEntry::operator=(const BlueprintEntry& entry) {
	if (this == &entry)
		return *this;

	type = entry.type;
	key = entry.key;
	displayedName = entry.displayedName;
	serialNumber = entry.serialNumber;
	identical = entry.identical;
	quantity = entry.quantity;

	return *this;
}

bool BlueprintEntry::operator==(const BlueprintEntry& entry) {
	if (this == &entry)
		return true;

	return((type == entry.type) &&
			(key == entry.key) &&
			(displayedName == entry.displayedName) &&
			(serialNumber == entry.serialNumber) &&
			(identical == entry.identical));
}

bool BlueprintEntry::equals(BlueprintEntry* entry) {

	return((type == entry->type) &&
			(key == entry->key) &&
			(displayedName == entry->displayedName) &&
			(serialNumber == entry->serialNumber) &&
			(identical == entry->identical));
}

void BlueprintEntry::createEntry(TangibleObject* ingredient, bool isIdentical) {

	identical = isIdentical;

	if (ingredient->isResourceContainer()) {

		ResourceContainer* rcnoObject = cast<ResourceContainer*>( ingredient);

		key = rcnoObject->getSpawnName();

		displayedName = key;

		type = "resource";
	} else {

		key = String::valueOf(ingredient->getServerObjectCRC());

		if(identical)
			serialNumber = ingredient->getSerialNumber();
		else
			serialNumber = "";

		displayedName = ingredient->getObjectName()->getDisplayedName();

		type = "component";
	}

	quantity = ingredient->getUseCount();
	clearMatches();
}

void BlueprintEntry::addSerializableVariables() {
	addSerializableVariable("type", &type);
	addSerializableVariable("key", &key);
	addSerializableVariable("displayName", &displayedName);
	addSerializableVariable("serialNumber", &serialNumber);
	addSerializableVariable("identical", &identical);
	addSerializableVariable("quantity", &quantity);
}

void BlueprintEntry::insertSchematicAttribute(AttributeListMessage* alm) {

	String name = "cat_manf_schem_ing_resource.\""
			+ displayedName + serialNumber;

	alm->insertAttribute(name, quantity);
}

void BlueprintEntry::insertFactoryIngredient(SuiListBox* ingredientList) {

	StringBuffer sendstring;
	sendstring << displayedName;

	if(type == "component")
		sendstring << " (" << serialNumber << ")";

	sendstring << ":\\>200" << quantity;

	ingredientList->addMenuItem(sendstring.toString(), 0);
}

void BlueprintEntry::clearMatches() {
	matchingHopperItems.removeAll();
}

bool BlueprintEntry::hasEnoughResources() {

	if(inputHopper == NULL)
		return false;

	int count = 0;

	for(int i = 0; i < matchingHopperItems.size(); ++i) {
		TangibleObject* object = matchingHopperItems.get(i);

		if (object == NULL) {
			matchingHopperItems.remove(i);
			--i;
			continue;
		}

		if(object->getParentID() != inputHopper->getObjectID()) {
			continue;
		}

		count += object->getUseCount();
	}

	if(count >= quantity)
		return true;

	return false;
}

void BlueprintEntry::removeResources() {

	int count = 0;

	while(matchingHopperItems.size() > 0) {
		TangibleObject* object = matchingHopperItems.get(0);

		if(object->getUseCount() < quantity) {
			count += object->getUseCount();
			matchingHopperItems.removeElement(object);

			object->setUseCount(0, true);
			continue;
		}


		object->setUseCount(object->getUseCount() - (quantity - count), true);

		if(object->getUseCount() == 0)
			matchingHopperItems.removeElement(object);

		break;
	}
}

void BlueprintEntry::print() {
	System::out << "****** Entry ******" << endl;

	System::out << "Type: " << type << endl;
	System::out << "Key: " << key << endl;
	System::out << "Displayed Name: " << displayedName << endl;
	System::out << "Serial Number: " << serialNumber << endl;
	System::out << "Identical: " << identical << endl;
	System::out << "Quantity: " << quantity << endl;

	System::out << "Matching Items:" << endl;
	for(int i = 0; i < matchingHopperItems.size(); ++i) {
		TangibleObject* object = matchingHopperItems.get(i);
		System::out << object->getObjectID() << " " << object->getObjectName()->getDisplayedName() << " " << object->getUseCount() << endl;
	}

	System::out << "*******************" << endl;
}
