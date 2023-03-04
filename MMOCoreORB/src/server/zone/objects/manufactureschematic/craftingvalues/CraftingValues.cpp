/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "CraftingValues.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"

CraftingValues::CraftingValues() {
	doHide = true;
	setLoggingName("CraftingValues");
	setLogging(false);
}


CraftingValues::CraftingValues(const CraftingValues& values) : Object(), Serializable(), Logger(), slots(values.slots) {
	valuesToSend = values.valuesToSend;
	doHide = values.doHide;
	schematic = values.schematic;
	player = values.player;
	experimentalValuesMap = values.experimentalValuesMap;

	setLoggingName("CraftingValues");
	setLogging(false);
}

CraftingValues::CraftingValues(const ValuesMap& values) : Object(), Serializable(), Logger() {
	doHide = true;
	experimentalValuesMap = values;

	setLoggingName("CraftingValues");
	setLogging(false);
}

CraftingValues::~CraftingValues() {
	schematic = nullptr;
	player = nullptr;
}

void CraftingValues::setManufactureSchematic(ManufactureSchematic* manu) {
	schematic = manu;
}

ManufactureSchematic* CraftingValues::getManufactureSchematic() {
	return schematic.get();
}

void CraftingValues::setPlayer(CreatureObject* play) {
	player = play;
}

CreatureObject* CraftingValues::getPlayer() {
	return player.get();
}

void CraftingValues::recalculateValues(bool initial) {
	String experimentalPropTitle, attributeName;
	float percentage = 0.f, min = 0.f, max = 0.f, newValue = 0.f, oldValue = 0.f;
	bool hidden = false;

	for (int i = 0; i < getTotalExperimentalAttributes(); ++i) {
		attributeName = getAttribute(i);
		experimentalPropTitle = getAttributeGroup(attributeName);

		min = getMinValue(attributeName);
		max = getMaxValue(attributeName);

		hidden = isHidden(attributeName);

		percentage = getCurrentPercentage(attributeName);

		oldValue = getCurrentValue(attributeName);

		if (experimentalPropTitle == "") {
			if (max > min)
				newValue = max;
			else
				newValue = min;
		} else if(max != min) {
			if (max > min)
				newValue = (percentage * (max - min)) + min;
			else
				newValue = (float(1.0f - percentage) * (min - max)) + max;
		} else if(max == min) {
			newValue = max;
		}

		if (initial || (newValue != oldValue && !initial && !hidden)) {
			setCurrentValue(attributeName, newValue);
			valuesToSend.add(attributeName);
		}
	}
}

void CraftingValues::clearAll() {
	doHide = true;
	//experimentalValuesMap.removeAll();
	valuesToSend.removeAll();
	schematic = nullptr;
	player = nullptr;
	clearSlots();
}

String CraftingValues::toString() const {
	StringBuffer str;

	for (int i = 0;i < experimentalValuesMap.getSize(); ++i) {
		String property = experimentalValuesMap.getAttribute(i);

		str << "\n*************************" << endl;
		str << "Property: #" << i << property << endl;
		str << "Group: " << experimentalValuesMap.getAttributeGroup(i) << endl;
		str << "**************************" << endl;
	}

	return str.toString();
}
