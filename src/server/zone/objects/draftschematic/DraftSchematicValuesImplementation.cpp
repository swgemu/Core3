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

#include "DraftSchematicValuesImplementation.h"

#include "../../packets.h"

DraftSchematicValuesImplementation::DraftSchematicValuesImplementation() : DraftSchematicValuesServant() {
	EMPTY = "";
	experimentalValuesMap.setNullValue(NULL);
}

DraftSchematicValuesImplementation::~DraftSchematicValuesImplementation() {
	for (int i = 0; i < experimentalValuesMap.size(); ++i) {
		delete experimentalValuesMap.get(i);
	}

	experimentalValuesMap.removeAll();

	valuesToSend.removeAll();
}

void DraftSchematicValuesImplementation::addExperimentalProperty(const String& title, const String& subtitle,
		const float min, const float max, const int precision) {
	Subclasses* subclasses;

	if (experimentalValuesMap.contains(title)) {
		subclasses = experimentalValuesMap.get(title);

		subclasses->addSubtitle(subtitle, min, max, precision);
	} else {
		subclasses = new Subclasses(title, subtitle, min, max, precision);

		experimentalValuesMap.put(title, subclasses);
	}
}

String& DraftSchematicValuesImplementation::getExperimentalPropertyTitle(
		const String& subtitle) {

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int j = 0; j < subclasses->size(); ++j) {
			values = subclasses->get(j);

			if (values->getName() == subtitle) {
				return subclasses->getClassName();
			}
		}
	}
	return EMPTY;
}


String& DraftSchematicValuesImplementation::getExperimentalPropertyTitle(
		const int i) {

	Subclasses* subclasses;

	subclasses = experimentalValuesMap.get(i);

	if (subclasses != NULL) {
		return subclasses->getClassName();
	}

	return EMPTY;
}

String& DraftSchematicValuesImplementation::getExperimentalPropertySubtitleClass(const int i) {
	Subclasses* subclasses;
	int count = 0;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		if (count + subclasses->size() <= i){
			count += subclasses->size();
		} else {
			return subclasses->getClassName();
		}
	}

	return EMPTY;
}

String& DraftSchematicValuesImplementation::getExperimentalPropertySubtitle(const int i) {
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

String& DraftSchematicValuesImplementation::getExperimentalPropertySubtitle(const String title, const int i) {
	Subclasses* subclasses;

	subclasses = experimentalValuesMap.get(title);

	if (subclasses != NULL)
		return subclasses->get(i)->getName();
	else
		return EMPTY;
}

int DraftSchematicValuesImplementation::getExperimentalPropertySubtitleSize() {
	Subclasses* subclasses;
	int size = 0;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		size += subclasses->size();
	}

	return size;
}

int DraftSchematicValuesImplementation::getExperimentalPropertySubtitleSize(const String title) {
	Subclasses* subclasses = NULL;

	subclasses = experimentalValuesMap.get(title);

	if (subclasses != NULL)
		return subclasses->size();

	return -1234;
}

bool DraftSchematicValuesImplementation::hasProperty(const String& attribute) {

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

void DraftSchematicValuesImplementation::setCurrentValue(
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

void DraftSchematicValuesImplementation::setCurrentValue(const String& attribute,
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

float DraftSchematicValuesImplementation::getCurrentValue(
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

	return -1234;
}

float DraftSchematicValuesImplementation::getCurrentValue(const int i) {
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

	return -1234;
}

void DraftSchematicValuesImplementation::lockValue(const String& attribute) {
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

void DraftSchematicValuesImplementation::resetValue(const String& attribute) {
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

void DraftSchematicValuesImplementation::setCurrentPercentage(
		const String& subtitle, const float value) {

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

void DraftSchematicValuesImplementation::setCurrentPercentage(const String& subtitle,
		const float value, const float min, const float max) {

	Subclasses* subclasses;
	Values* values;

	for (int j = 0; j < experimentalValuesMap.size(); ++j) {
		subclasses = experimentalValuesMap.get(j);

		for (int i = 0; i < subclasses->size(); ++i) {

			values = subclasses->get(i);

			if (values->getName() == subtitle) {

				values->setMaxValue(max);
				values->setMinValue(min);

				if (value > max)
					values->setPercentage(max);
				else
					values->setPercentage(value);

				return;
			}
		}
	}
}

float DraftSchematicValuesImplementation::getCurrentPercentage(
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

	return -1234;
}

float DraftSchematicValuesImplementation::getCurrentPercentage(const int i) {
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

	return -1234;
}

float DraftSchematicValuesImplementation::getCurrentPercentageAverage(const int i) {
	Subclasses* subclasses;
	Values* values;

	subclasses = experimentalValuesMap.get(i);

	if (subclasses == NULL)
		return -1;

	float average = 0;
	float count = 0;

	for (int j = 0; j < subclasses->size(); ++j) {
		values = subclasses->get(j);

		if (values->getMaxPercentage() < 1.0f) {

			average += values->getPercentage();
			count++;
		}
	}

	return (average / count);
}

float DraftSchematicValuesImplementation::getCurrentPercentageAverage(const String title) {
	Subclasses* subclasses;
	Values* values;

	subclasses = experimentalValuesMap.get(title);

	if (subclasses == NULL)
		return -1;

	float average = 0;
	float count = 0;

	for (int j = 0; j < subclasses->size(); ++j) {
		values = subclasses->get(j);

		if (values->getMaxPercentage() < 1.0f) {

			average += values->getPercentage();
			count++;
		}
	}

	return (average / count);
}

void DraftSchematicValuesImplementation::setMaxPercentage(
		const String& attribute, const float value) {

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

float DraftSchematicValuesImplementation::getMaxPercentage(
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

	return -1234;
}

float DraftSchematicValuesImplementation::getMaxPercentage(const int i) {
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

	return -1234;
}

float DraftSchematicValuesImplementation::getMaxPercentageAverage(const int i) {
	Subclasses* subclasses;
	Values* values;

	subclasses = experimentalValuesMap.get(i);

	float average = 0;
	float count = 0;

	for (int j = 0; j < subclasses->size(); ++j) {
		values = subclasses->get(j);

		if (values->getMaxPercentage() < 1.0f) {

			average += values->getMaxPercentage();
			count++;
		}
	}

	return (average / count);
}

float DraftSchematicValuesImplementation::getMaxValue(const String& attribute) {
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

	return -1234;
}

float DraftSchematicValuesImplementation::getMinValue(const String& attribute) {
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

	return -1234;
}

void DraftSchematicValuesImplementation::setMinValue(const String& attribute, const float value) {
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

void DraftSchematicValuesImplementation::setMaxValue(const String& attribute, const float value) {
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

int DraftSchematicValuesImplementation::getPrecision(const String& attribute) {
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

	return -1234;
}

void DraftSchematicValuesImplementation::setPrecision(const String& attribute, const int value) {
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

void DraftSchematicValuesImplementation::recalculateValues(DraftSchematic* draftSchematic) {
	String experimentalPropTitle, attributeName;
	float percentage, min, max, newValue, oldValue;
	DraftSchematicAttribute * attrib;

	for (int i = 0; i < draftSchematic->getAttributesToSetListSize(); ++i) {
		attrib = draftSchematic->getAttributeToSet(i);
		experimentalPropTitle = attrib->getAttributeExperimentalProperty();

		attributeName = attrib->getAttributeName();
		min = attrib->getMinValue();
		max = attrib->getMaxValue();
		percentage = getCurrentPercentage(attributeName);//experimentalPropTitle);

		oldValue = getCurrentValue(attributeName);

		if (experimentalPropTitle == "null") {
			if (max > min)
				newValue = max;
			else
				newValue = min;
		} else {
			if (max > min)
				newValue = (percentage * (max - min)) + min;
			else
				newValue = (float(1.0f - percentage) * (min - max)) + max;
		}

		if (newValue != oldValue) {
			setCurrentValue(attributeName, newValue);
			valuesToSend.add(attributeName);
		}
	}
	//toString();
}


void DraftSchematicValuesImplementation::toString() {
	Subclasses* tempSubclasses;

	for (int i = 0;i < experimentalValuesMap.size(); ++i) {
		tempSubclasses = experimentalValuesMap.get(i);

		System::out << "\n*************************" << endl;
		System::out << "Subclass " << i << endl;
		System::out << "Class: " << tempSubclasses->getClassName() << endl;
		System::out << "Name: " << tempSubclasses->getName() << endl;
		tempSubclasses->toString();
		System::out << "**************************" << endl;
	}
}
