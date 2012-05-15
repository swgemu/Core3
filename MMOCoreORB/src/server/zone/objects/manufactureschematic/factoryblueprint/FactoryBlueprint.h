/*
 * FactoryBlueprint.h
 *
 *  Created on: Apr 3, 2011
 *      Author: kyle
 */

#ifndef FACTORYBLUEPRINT_H_
#define FACTORYBLUEPRINT_H_

#include "engine/engine.h"
#include "BlueprintEntry.h"
#include "server/zone/objects/tangible/TangibleObject.h"

class FactoryBlueprint  : public Serializable  {
private:
	Vector<BlueprintEntry> completeEntries;
	Vector<BlueprintEntry> consolidatedEntries;
public:
	FactoryBlueprint();
	FactoryBlueprint(const FactoryBlueprint& blueprint);

	~FactoryBlueprint();

	FactoryBlueprint& operator=(const FactoryBlueprint& blueprint);

	void addIngredient(SceneObject* ingredient, int quantity, bool isIdentical);

	void addConsolidatedEntry(BlueprintEntry* entry);

	BlueprintEntry* getConsolidatedEntry(int i);

	int getConsolidatedSize();

	BlueprintEntry* getCompleteEntry(int i);

	int getCompleteSize();

	void canManufactureItem(String &type, String &displayedName);

	void manufactureItem();

	void addSerializableVariables();

	void print();
};

#endif /* FACTORYBLUEPRINT_H_ */
