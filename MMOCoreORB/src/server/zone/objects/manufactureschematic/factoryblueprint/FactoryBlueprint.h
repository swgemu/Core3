/*
 * FactoryBlueprint.h
 *
 *  Created on: Apr 3, 2011
 *      Author: kyle
 */

#ifndef FACTORYBLUEPRINT_H_
#define FACTORYBLUEPRINT_H_

#include <algorithm>

#include "BlueprintEntry.h"
#include "engine/engine.h"
#include "server/zone/objects/installation/factory/FactoryObject.h"
#include "system/io/Serializable.h"
#include "system/util/Vector.h"

namespace server {
namespace zone {
namespace objects {
namespace installation {
namespace factory {
class FactoryObject;
}  // namespace factory
}  // namespace installation
namespace scene {
class SceneObject;
}  // namespace scene
}  // namespace objects
}  // namespace zone
}  // namespace server
namespace sys {
namespace lang {
class String;
}  // namespace lang
}  // namespace sys

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

	void manufactureItem(FactoryObject* factory);

	void addSerializableVariables();

	void print();
};

#endif /* FACTORYBLUEPRINT_H_ */
