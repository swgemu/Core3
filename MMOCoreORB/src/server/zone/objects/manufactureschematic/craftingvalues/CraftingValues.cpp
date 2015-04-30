/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "CraftingValues.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"

float CraftingValues::VALUENOTFOUND = -999999;

CraftingValues::CraftingValues() {
	EMPTY = "";
	experimentalValuesMap.setNullValue(NULL);
	doHide = true;
	setLoggingName("CraftingValues");
	setLogging(false);
}


CraftingValues::CraftingValues(const CraftingValues& values) : Object(), Serializable(), Logger(), slots(values.slots) {
	valuesToSend = values.valuesToSend;
	EMPTY = values.EMPTY;
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


CraftingValues::~CraftingValues() {
	//valuesToSend.removeAll();
	//info("Deleting CraftingValues");
}

void CraftingValues::setManufactureSchematic(ManufactureSchematic* manu) {
	schematic = manu;
}

ManufactureSchematic* CraftingValues::getManufactureSchematic() {
	return schematic;
}

void CraftingValues::setPlayer(CreatureObject* play) {
	player = play;
}

CreatureObject* CraftingValues::getPlayer() {
	return player;
}

void CraftingValues::addExperimentalProperty(const String& title, const String& subtitle,
		const float min, const float max, const int precision, const bool filler, const int combine) {
	Subclasses* subclasses;

	if (experimentalValuesMap.contains(title)) {
		subclasses = experimentalValuesMap.get(title);

		subclasses->addSubtitle(subtitle, min, max, precision, filler, combine);
	} else {
		subclasses = new Subclasses(title, subtitle, min, max, precision, filler, combine);

		experimentalValuesMap.put(title, subclasses);
	}
}

String& CraftingValues::getExperimentalPropertyTitle(
		const String& subtitle) {

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int j = 0; j < subclasses->size(); ++j) {
			values = subclasses->get(j);

			if (values->getName() == subtitle) {
				return subclasses->getClassTitle();
			}
		}
	}
	return EMPTY;
}


String& CraftingValues::getExperimentalPropertyTitle(
		const int i) {

	Subclasses* subclasses;

	subclasses = experimentalValuesMap.get(i);

	if (subclasses != NULL) {
		return subclasses->getClassTitle();
	}

	return EMPTY;
}

String& CraftingValues::getVisibleExperimentalPropertyTitle(
		const int i) {

	Subclasses* subclasses;
	int counter = -1;
	String title;

	for(int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		if(!subclasses->hasAllHiddenItems())
			counter++;

		if(counter == i)
			return subclasses->getClassTitle();
	}

	return EMPTY;
}

String& CraftingValues::getExperimentalPropertySubtitlesTitle(const int i) {
	Subclasses* subclasses;
	int count = 0;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		if (count + subclasses->size() <= i){
			count += subclasses->size();
		} else {
			return subclasses->getClassTitle();
		}
	}

	return EMPTY;
}

String& CraftingValues::getExperimentalPropertySubtitle(const int i) {
	Subclasses* subclasses;
	int count = 0;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		if (count + subclasses->size() <= i) {
			count += subclasses->size();
		} else {
			count = i - count;

			Values* values = subclasses->get(count);

			return values->getName();
		}
	}

	return EMPTY;
}

String& CraftingValues::getExperimentalPropertySubtitle(const String title, const int i) {
	Subclasses* subclasses;

	subclasses = experimentalValuesMap.get(title);

	if (subclasses != NULL)
		return subclasses->get(i)->getName();
	else
		return EMPTY;
}

int CraftingValues::getExperimentalPropertySubtitleSize() {
	Subclasses* subclasses;
	int size = 0;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		size += subclasses->size();
	}

	return size;
}

int CraftingValues::getExperimentalPropertySubtitleSize(const String title) {
	Subclasses* subclasses = NULL;

	subclasses = experimentalValuesMap.get(title);

	if (subclasses != NULL)
		return subclasses->size();

	return (int)VALUENOTFOUND;
}

bool CraftingValues::hasProperty(const String& attribute) {

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return true;
			}
		}
	}
	return false;
}

bool CraftingValues::isHidden(const String& attribute) {

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return values->isFiller();
			}
		}
	}
	return false;
}

void CraftingValues::setHidden(const String& attribute) {

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->setFiller(true);
			}
		}
	}
}

void CraftingValues::unsetHidden(const String& attribute) {

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->setFiller(false);
			}
		}
	}
}

void CraftingValues::setCurrentValue(
		const String& attribute, const float value) {

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->setValue(value);
				return;
			}
		}
	}
}

void CraftingValues::setCurrentValue(const String& attribute,
		const float value, const float min, const float max) {

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {

				values->setMaxValue(max);
				values->setMinValue(min);

				values->setValue(value);
				return;
			}
		}
	}
}

float CraftingValues::getCurrentValue(
		const String& attribute) {

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return values->getValue();
			}
		}
	}

	return VALUENOTFOUND;
}

float CraftingValues::getCurrentValue(const int i) {
	Subclasses* subclasses;
	int count = 0;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		if (count + subclasses->size() <= i) {
			count += subclasses->size();
		} else {
			count = i - count;

			Values* values = subclasses->get(count);

			return values->getValue();
		}
	}

	return VALUENOTFOUND;
}

void CraftingValues::lockValue(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->lockValue();
				return;
			}
		}
	}
}

void CraftingValues::unlockValue(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->unlockValue();
				return;
			}
		}
	}
}

void CraftingValues::resetValue(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->resetValue();
				return;
			}
		}
	}
}

void CraftingValues::setCurrentPercentage(
		const String& subtitle, float value) {

	float max = 0.0f;

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == subtitle) {
				max = values->getMaxPercentage();

				if (value > max)
					values->setPercentage(max);
				else
					values->setPercentage(value);

				return;
			}
		}
	}
}

void CraftingValues::setCurrentPercentage(const String& subtitle,
		 float value, float max) {

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == subtitle) {

				values->setMaxPercentage(max);

				if (value > max)
					values->setPercentage(max);
				else
					values->setPercentage(value);

				return;
			}
		}
	}
}

float CraftingValues::getCurrentPercentage(
		const String& attribute) {

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return values->getPercentage();
			}
		}
	}

	return VALUENOTFOUND;
}

float CraftingValues::getCurrentPercentage(const int i) {
	Subclasses* subclasses;
	int count = 0;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		if (count + subclasses->size() <= i) {
			count += subclasses->size();
		} else {
			count = i - count;

			Values* values = subclasses->get(count);

			return values->getPercentage();
		}
	}

	return VALUENOTFOUND;
}

float CraftingValues::getCurrentVisiblePercentage(const String title) {
	Subclasses* subclasses;
	Values* values;

	subclasses = experimentalValuesMap.get(title);

	if (subclasses == NULL)
		return -1;

	float value = 0;
	// shouldnt this show the avg so with 1 item who cares, btu more than 1 we wana should avg of all not the LAST one
	for (int j = 0; j < subclasses->size(); ++j) {
		values = subclasses->get(j);

		if (values->getMinValue() != values->getMaxValue() &&
				values->getMaxPercentage() <= 1.0f &&
				!values->isFiller()) {

			float item = values->getPercentage();
			if (item > value)
				value = item;

		}
	}

	return value;
}

void CraftingValues::setMaxPercentage(
		const String& attribute, float value) {

	float max;

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->setMaxPercentage(value);
				return;
			}
		}
	}
}

float CraftingValues::getMaxPercentage(
		const String& attribute) {

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return values->getMaxPercentage();
			}
		}
	}

	return VALUENOTFOUND;
}

float CraftingValues::getMaxPercentage(const int i) {
	Subclasses* subclasses;
	int count = 0;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		if (count + subclasses->size() <= i) {
			count += subclasses->size();
		} else {
			count = i - count;

			Values* values = subclasses->get(count);

			return values->getMaxPercentage();
		}
	}

	return VALUENOTFOUND;
}

float CraftingValues::getMaxVisiblePercentage(const int i) {
	Subclasses* subclasses;
	Values* values;

	String title = getVisibleExperimentalPropertyTitle(i);

	subclasses = experimentalValuesMap.get(title);

	float value = 0;
	float count = 0;

	for (int j = 0; j < subclasses->size(); ++j) {
		values = subclasses->get(j);

		if (values->getMinValue() != values->getMaxValue() &&
				values->getMaxPercentage() <= 1.0f
				&& !values->isFiller()) {

			if(values->getMaxPercentage() > value)
				value = values->getMaxPercentage();
		}
	}

	return value;
}

float CraftingValues::getMaxValue(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return values->getMaxValue();
			}
		}
	}

	return VALUENOTFOUND;
}

float CraftingValues::getMinValue(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return values->getMinValue();
			}
		}
	}

	return VALUENOTFOUND;
}

void CraftingValues::setMinValue(const String& attribute, const float value) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->setMinValue(value);
			}
		}
	}
}

void CraftingValues::setMaxValue(const String& attribute, const float value) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->setMaxValue(value);
			}
		}
	}
}

int CraftingValues::getPrecision(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return values->getPrecision();
			}
		}
	}

	return (int)VALUENOTFOUND;
}

void CraftingValues::setPrecision(const String& attribute, const int value) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				values->setPrecision(value);
			}
		}
	}
}

short CraftingValues::getCombineType(const String& attribute) {
	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == attribute) {
				return values->getCombineType();
			}
		}
	}

	return (int)VALUENOTFOUND;
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

		percentage = getCurrentPercentage(attributeName);//experimentalPropTitle);

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

	//toString();
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
