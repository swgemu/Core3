/*
 * FactoryBlueprint.cpp
 *
 *  Created on: Apr 3, 2011
 *      Author: kyle
 */

#include "FactoryBlueprint.h"
#include "server/zone/objects/resource/ResourceContainer.h"

FactoryBlueprint::FactoryBlueprint() :  Serializable() {

	addSerializableVariables();
}

FactoryBlueprint::FactoryBlueprint(const FactoryBlueprint& blueprint) :  Object(), Serializable()  {

	for(int i = 0; i < blueprint.completeEntries.size(); ++i)
		completeEntries.add(blueprint.completeEntries.get(i));

	for(int i = 0; i < blueprint.consolidatedEntries.size(); ++i)
		consolidatedEntries.add(blueprint.consolidatedEntries.get(i));

	addSerializableVariables();
}

FactoryBlueprint::~FactoryBlueprint() {

}

FactoryBlueprint& FactoryBlueprint::operator=(const FactoryBlueprint& blueprint) {
	if (this == &blueprint)
		return *this;

	completeEntries.removeAll();

	for(int i = 0; i < blueprint.completeEntries.size(); ++i)
		completeEntries.add(blueprint.completeEntries.get(i));

	for(int i = 0; i < blueprint.consolidatedEntries.size(); ++i)
		consolidatedEntries.add(blueprint.consolidatedEntries.get(i));


	return *this;
}


void FactoryBlueprint::addIngredient(SceneObject* ingredient, int quantity, bool isIdentical) {
	BlueprintEntry entry;

	entry.setIdentical(isIdentical);

	if (ingredient->isResourceSpawn()) {

		ManagedReference<ResourceSpawn*> spawn = cast<ResourceSpawn*>(ingredient);

		entry.setKey(spawn->getName());
		entry.setDisplayedName(spawn->getName());
		entry.setType("resource");
		entry.setQuantity(quantity);

	} else {

		ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(ingredient);

		entry.setKey(String::valueOf(tano->getServerObjectCRC()));
		entry.setDisplayedName(tano->getDisplayedName());
		entry.setType("component");
		entry.setQuantity(quantity);

		if(isIdentical)
			entry.setSerial(tano->getSerialNumber());
		else
			entry.setSerial("");

	}

	completeEntries.add(entry);
	addConsolidatedEntry(&entry);
}

int FactoryBlueprint::getConsolidatedSize() {
	return consolidatedEntries.size();
}

void FactoryBlueprint::addConsolidatedEntry(BlueprintEntry* entry) {

	for(int i = 0; i < consolidatedEntries.size(); i++) {
		BlueprintEntry* existingEntry = &consolidatedEntries.get(i);

		if(existingEntry->equals(entry)) {
			existingEntry->increaseQuantity(entry->getQuantity());
			return;
		}
	}
	consolidatedEntries.add(BlueprintEntry(*entry));
}

BlueprintEntry* FactoryBlueprint::getConsolidatedEntry(int i) {
	return &consolidatedEntries.get(i);
}

int FactoryBlueprint::getCompleteSize() {
	return completeEntries.size();
}

BlueprintEntry* FactoryBlueprint::getCompleteEntry(int i) {
	return &completeEntries.get(i);
}

void FactoryBlueprint::canManufactureItem(String &type, String &displayedName) {

	for(int i = 0; i < consolidatedEntries.size(); ++i) {
		BlueprintEntry* entry = &consolidatedEntries.get(i);

		if(!entry->hasEnoughResources()) {
			type = entry->getType();
			displayedName = entry->getDisplayedName();
			return;
		}
	}
}

void FactoryBlueprint::manufactureItem() {

	for(int i = 0; i < consolidatedEntries.size(); ++i) {
		BlueprintEntry* entry = &consolidatedEntries.get(i);

		entry->removeResources();
	}
}

void FactoryBlueprint::addSerializableVariables() {
	addSerializableVariable("completeEntries", &completeEntries);
	addSerializableVariable("consolidatedEntries", &consolidatedEntries);
}

void FactoryBlueprint::print() {

	System::out << "***** Display *****" << endl;

	for(int i = 0; i < completeEntries.size(); ++i) {
		BlueprintEntry* entry = &completeEntries.get(i);
		entry->print();
	}

	System::out << "*******************" << endl;
	System::out << "** Consolidated ***" << endl;

	for(int i = 0; i < consolidatedEntries.size(); ++i) {
		BlueprintEntry* entry = &consolidatedEntries.get(i);
		entry->print();
	}
	System::out << "*******************" << endl;
}

