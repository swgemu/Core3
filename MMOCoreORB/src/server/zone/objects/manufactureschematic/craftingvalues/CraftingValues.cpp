/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "CraftingValues.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"

CraftingValues::CraftingValues() {
	experimentalValuesMap.setNullValue(NULL);
	doHide = true;
	setLoggingName("CraftingValues");
	setLogging(false);
}


CraftingValues::CraftingValues(const CraftingValues& values) : Object(), Serializable(), Logger(), slots(values.slots) {
	valuesToSend = values.valuesToSend;
	doHide = values.doHide;
	schematic = values.schematic;
	player = values.player;

	for (int i = 0; i < values.experimentalValuesMap.size(); ++i) {
		VectorMapEntry<String, Reference<Subclasses*> > entry = values.experimentalValuesMap.elementAt(i);

		Subclasses* subclass = entry.getValue();

		Subclasses* subclasses = new Subclasses(*subclass);

		experimentalValuesMap.put(entry.getKey(), subclasses);
	}

	setLoggingName("CraftingValues");
	setLogging(false);
}

CraftingValues::CraftingValues(const ValuesMap& values) : Object(), Serializable(), Logger() {
	experimentalValuesMap.setNullValue(NULL);
	doHide = true;

	for (int i = 0; i < values.size(); ++i) {
		VectorMapEntry<String, Reference<Subclasses*> > entry = values.elementAt(i);

		Subclasses* subclass = entry.getValue();

		Subclasses* subclasses = new Subclasses(*subclass);

		experimentalValuesMap.put(entry.getKey(), subclasses);
	}

	setLoggingName("CraftingValues");
	setLogging(false);
}

CraftingValues::~CraftingValues() {
	experimentalValuesMap.removeAll();
	schematic = NULL;
	player = NULL;
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

	for (int i = 0; i < getSubtitleCount(); ++i) {
		attributeName = getExperimentalPropertySubtitle(i);
		experimentalPropTitle = getExperimentalPropertyTitle(attributeName);

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
	experimentalValuesMap.removeAll();
	valuesToSend.removeAll();
	schematic = NULL;
	player = NULL;
	clearSlots();
}

String CraftingValues::toString() {
	Subclasses* tempSubclasses;

	StringBuffer str;

	for (int i = 0;i < experimentalValuesMap.size(); ++i) {
		tempSubclasses = experimentalValuesMap.get(i);

		str << "\n*************************" << endl;
		str << "Subclass " << i << endl;
		str << "Class: " << tempSubclasses->getClassTitle() << endl;
		str << tempSubclasses->toString();
		str << "**************************" << endl;
	}

	return str.toString();
}
