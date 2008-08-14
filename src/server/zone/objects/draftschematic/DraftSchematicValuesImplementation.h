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

#ifndef DRAFTSCHEMATICVALUESIMPLEMENTATION_H_
#define DRAFTSCHEMATICVALUESIMPLEMENTATION_H_


#include "../../packets.h"

#include "ValuesClasses.h"
#include "DraftSchematicAttribute.h"
#include "DraftSchematicValues.h"
#include "DraftSchematic.h"


class DraftSchematicValuesImplementation : public DraftSchematicValuesServant {

	VectorMap<string, Subclasses*> experimentalValuesMap;

	Vector<string> valuesToSend;

	string EMPTY;


public:
	DraftSchematicValuesImplementation() : DraftSchematicValuesServant() {

		EMPTY = "";

	}
	~DraftSchematicValuesImplementation(){

		for(int i = 0; i < experimentalValuesMap.size(); ++i){

			delete experimentalValuesMap.get(i);

		}

		experimentalValuesMap.removeAll();

		valuesToSend.removeAll();

	}
	// Experimental Titles
	inline void addExperimentalPropertySubtitle(const string& title, const string& subtitle){

		Subclasses* subclasses;

		if(experimentalValuesMap.contains(title)){

			subclasses = experimentalValuesMap.get(title);

			subclasses->addSubtitle(subtitle);

		} else {

			subclasses = new Subclasses(title, subtitle);

			experimentalValuesMap.put(title, subclasses);

		}

	}

	inline string& getExperimentalPropertyTitle(const string& subtitle) {

		Subclasses* subClass;

		for(int j = 0; j < experimentalValuesMap.size(); ++j) {

			subClass = experimentalValuesMap.get(j);

			if(subClass->getName() == subtitle) {

				return subClass->getClassName();

			}
		}
		return EMPTY;
	}


	inline string& getExperimentalPropertyTitle(const int i){

		Subclasses* subClass;

		subClass = experimentalValuesMap.get(i);

		if(subClass != NULL){

			return subClass->getClassName();

		} else {

			return EMPTY;

		}

	}

	inline string& getExperimentalPropertySubtitleClass(const int i){

		Subclasses* subClasses;
		int count = 0;

		for(int j = 0; j < experimentalValuesMap.size(); ++j){

			subClasses = experimentalValuesMap.get(j);

			if(count + subClasses->size() <= i){

				count += subClasses->size();

			} else {


				return subClasses->getClassName();
			}

		}
		return EMPTY;
	}

	inline string& getExperimentalPropertySubtitle(const int i){

		Subclasses* subClasses;
		int count = 0;

		for(int j = 0; j < experimentalValuesMap.size(); ++j){

			subClasses = experimentalValuesMap.get(j);

			if(count + subClasses->size() <= i){

				count += subClasses->size();

			} else {

				count = i - count;

				Values* values = subClasses->get(count);

				return values->getName();
			}

		}
		return EMPTY;
	}

	inline string& getExperimentalPropertySubtitle(const string title, const int i){

		Subclasses* subClasses;

		subClasses = experimentalValuesMap.get(title);

		if(subClasses != NULL)
			return subClasses->get(i)->getName();
		else
			return EMPTY;
	}

	inline int getExperimentalPropertySubtitleSize(){

		Subclasses* subClasses;
		int size = 0;

		for(int j = 0; j < experimentalValuesMap.size(); ++j){

			subClasses = experimentalValuesMap.get(j);

			size += subClasses->size();

		}

		return size;

	}

	inline int getExperimentalPropertySubtitleSize(const string title){

		Subclasses* subclasses = NULL;

		subclasses = experimentalValuesMap.get(title);

		if(subclasses != NULL)
			return subclasses->size();
		else
			return -1234;

	}

	inline int getExperimentalPropertyTitleSize(){


		return experimentalValuesMap.size();

	}

	inline void setCurrentValue(const string& attribute, const float value) {

		Subclasses* subClasses;

		for (int j = 0; j < experimentalValuesMap.size(); ++j) {

			subClasses = experimentalValuesMap.get(j);

			if (subClasses->getName() == attribute) {

				subClasses->setValue(attribute, value);
				return;

			}
		}
	}

	inline int getValuesToSendSize(){

		return valuesToSend.size();

	}

	string& getValuesToSend(const int i){

		return valuesToSend.get(i);

	}

	inline float getCurrentValue(const string& attribute) {

		Subclasses* subClasses;
		Values* values;

		for (int j = 0; j < experimentalValuesMap.size(); ++j) {

			subClasses = experimentalValuesMap.get(j);

			if (subClasses->getName() ==  attribute) {

				return subClasses->getValue(attribute);

			}
		}
		return -1234;
	}

	float getCurrentValue(const int i){

		Subclasses* subClasses;
		int count = 0;

		for(int j = 0; j < experimentalValuesMap.size(); ++j){

			subClasses = experimentalValuesMap.get(j);

			if(count + subClasses->size() <= i){

				count += subClasses->size();

			} else {

				count = i - count;

				Values* values = subClasses->get(count);

				return values->getValue();
			}

		}
		return -1234;

	}

	inline void setCurrentPercentage(const string& subtitle, const float value){

		float max = 0;

		Subclasses* subClasses;

		for(int j = 0; j < experimentalValuesMap.size(); ++j){

			subClasses = experimentalValuesMap.get(j);

			if(subClasses->getName() == subtitle){

				max = subClasses->getMaxPercentage(subtitle);

				if(value > max)
					subClasses->setPercentage(subtitle, max);
				else
					subClasses->setPercentage(subtitle, value);

				return;

			}
		}
	}

	float getCurrentPercentage(const string& attribute){

		Subclasses* subClasses;

		for(int j = 0; j < experimentalValuesMap.size(); ++j){

			subClasses = experimentalValuesMap.get(j);

			if(subClasses->getName() == attribute){

				return subClasses->getPercentage(attribute);

			}
		}
		return -1234;
	}
	float getCurrentPercentage(const int i){

		Subclasses* subClasses;
		int count = 0;

		for(int j = 0; j < experimentalValuesMap.size(); ++j){

			subClasses = experimentalValuesMap.get(j);

			if(count + subClasses->size() <= i){

				count += subClasses->size();

			} else {

				count = i - count;

				Values* values = subClasses->get(count);

				return values->getPercentage();
			}

		}
		return -1234;

	}

	float getCurrentPercentageAverage(const int i){

		Subclasses* subClasses;
		Values* values;

		subClasses = experimentalValuesMap.get(i);

		float average = 0;

		for(int j = 0; j < subClasses->size(); ++j){

			values = subClasses->get(j);

			average += values->getPercentage();

		}

		return (average / subClasses->size());

	}

	inline void setMaxPercentage(const string& attribute, const float value){

		float max;

		Subclasses* subClasses;

		for(int j = 0; j < experimentalValuesMap.size(); ++j){

			subClasses = experimentalValuesMap.get(j);

			if(subClasses->getName() == attribute){

				subClasses->setMaxPercentage(attribute, value);
				return;
			}
		}
	}

	float getMaxPercentage(const string& attribute){

		Subclasses* subClasses;

		for(int j = 0; j < experimentalValuesMap.size(); ++j){

			subClasses = experimentalValuesMap.get(j);

			if(subClasses->getName() == attribute){

				return subClasses->getMaxPercentage(attribute);

			}
		}
		return -1234;
	}
	float getMaxPercentage(const int i){

		Subclasses* subClasses;
		int count = 0;

		for(int j = 0; j < experimentalValuesMap.size(); ++j){

			subClasses = experimentalValuesMap.get(j);

			if(count + subClasses->size() <= i){

				count += subClasses->size();

			} else {

				count = i - count;

				Values* values = subClasses->get(count);

				return values->getMaxPercentage();
			}

		}
		return -1234;
	}

	float getMaxPercentageAverage(const int i){

		Subclasses* subClasses;
		Values* values;

		subClasses = experimentalValuesMap.get(i);

		float average = 0;

		for(int j = 0; j < subClasses->size(); ++j){

			values = subClasses->get(j);

			average += values->getMaxPercentage();

		}

		return (average / subClasses->size());

	}

	void recalculateValues(DraftSchematic* draftSchematic){

		string experimentalPropTitle, attributeName;
		float percentage, min, max, newValue, oldValue;
		DraftSchematicAttribute * attrib;

		for(int i = 0; i < draftSchematic->getAttributesToSetListSize(); ++i){

			attrib = draftSchematic->getAttributeToSet(i);
			experimentalPropTitle = attrib->getAttributeExperimentalProperty();

			attributeName = attrib->getAttributeName();
			min = attrib->getMinValue();
			max = attrib->getMaxValue();
			percentage = getCurrentPercentage(experimentalPropTitle);

			oldValue = getCurrentValue(experimentalPropTitle);

			if(experimentalPropTitle == "null"){
				newValue = max;
			} else {
				newValue = (percentage * (max - min)) + min;
			}

			if (newValue != oldValue) {

				setCurrentValue(experimentalPropTitle, newValue);
				valuesToSend.add(attributeName);

			}

		}
	}


	// Clear
	inline void clear(){
		valuesToSend.removeAll();
	}

	inline void clearAll(){
		experimentalValuesMap.removeAll();
		valuesToSend.removeAll();
	}

	void toString(){
		Subclasses* tempSubclasses;

		for (int i = 0;i < experimentalValuesMap.size(); ++i) {
			tempSubclasses = experimentalValuesMap.get(i);

			cout << "\n*************************" << endl;
			cout << "Subclass " << i << endl;
			cout << "Class: " << tempSubclasses->getClassName() << endl;
			cout << "Name: " << tempSubclasses->getName() << endl;
			tempSubclasses->toString();
			cout << "**************************" << endl;
		}
	}

};

#endif /*DRAFTSCHEMATICVALUESIMPLEMENTATION_H_*/
