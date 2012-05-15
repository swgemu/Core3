/*
 * BlueprintEntry.h
 *
 *  Created on: Apr 3, 2011
 *      Author: kyle
 */

#ifndef BLUEPRINTENTRY_H_
#define BLUEPRINTENTRY_H_

#include "engine/engine.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

/**
 * This class defines a collective entry that makes up a single blueprint item
 * Ex.  If a schematic contains 2 identical ingredients, they will combine to
 * a single blueprint entry
 */
class BlueprintEntry : public Serializable {
private:

	/// Type of resource
	String type;

	/// Unique identifier - Resource = spawnName; Component = server script crc
	String key;

	/// Name to display in UI
	String displayedName;

	/// Serial number of tangible item
	String serialNumber;

	/// Designates if this item needs to be identical
	bool identical;

	/// Quantity of ingredient neededs
	int quantity;

	/// Input hopper
	ManagedReference<SceneObject* > inputHopper;

	/// Matching items from factory hopper
	Vector<ManagedReference<TangibleObject*> > matchingHopperItems;

public:

	/// Default Constructor
	BlueprintEntry();

	// Copy ctor
	BlueprintEntry(const BlueprintEntry& entry);

	/// Constructor
	BlueprintEntry(TangibleObject* ingredient, bool isIdentical = false);

	// Deconstructor
	~BlueprintEntry();

	BlueprintEntry& operator=(const BlueprintEntry& entry);
	bool operator==(const BlueprintEntry& entry);

	bool equals(BlueprintEntry* entry);

	/// Inserts string for ManufactureSchematic attributes
	void insertSchematicAttribute(AttributeListMessage* alm);

	/// Inserts factory ingredient for ingredient list sui
	void insertFactoryIngredient(SuiListBox* ingredientList);

	/// Clear contents
	void clearMatches();

	/// See if this entry has enough resources to continue
	bool hasEnoughResources();

	/// Remove resources from vector
	void removeResources();

	/// Print internal state
	void print();

	/// If item requires identical
	bool needsIdentical() {
		return identical;
	}

	void setIdentical(bool value) {
		identical = value;
	}

	/// Getter for type
	String getType() {
		return type;
	}

	/// Getter for key
	String getKey() {
		return key;
	}

	/// Getter for serial
	String getSerial() {
		return serialNumber;
	}

	/// Getter for displayed name
	String getDisplayedName() {
		return displayedName;
	}

	/// getter for quantity
	int getQuantity() {
		return quantity;
	}

	void setQuantity(int value) {
		quantity = value;
	}

	/// increase for quantity
	void increaseQuantity(int value) {
		quantity += value;
	}

	/// Add a match to the vector
	void addMatch(TangibleObject* object) {
		matchingHopperItems.add(object);
	}

	void setDisplayedName(String value) {
		displayedName = value;
	}

	void setType(String value) {
		type = value;
	}

	void setKey(String value) {
		key = value;
	}

	void setSerial(String value) {
		serialNumber = value;
	}

	void setHopper(SceneObject* hopper) {
		inputHopper = hopper;
	}

private:

	/// Adds members to be serialized
	void addSerializableVariables();
};

#endif /* BLUEPRINTENTRY_H_ */
