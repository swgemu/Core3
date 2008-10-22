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

#include "ValuesClasses.h"
#include "DraftSchematicAttribute.h"
#include "DraftSchematicValues.h"
#include "DraftSchematic.h"

#include "../tangible/crafting/CraftingTool.h"


class DraftSchematicValuesImplementation : public DraftSchematicValuesServant {
	VectorMap<string, Subclasses*> experimentalValuesMap;

	Vector<string> valuesToSend;

	string EMPTY;

public:
	DraftSchematicValuesImplementation();
	~DraftSchematicValuesImplementation();
	// Experimental Titles
	void addExperimentalProperty(const string& title, const string& subtitle,
			const float min, const float max, const int precision);

	string& getExperimentalPropertyTitle(const string& subtitle);
	string& getExperimentalPropertyTitle(const int i);

	string& getExperimentalPropertySubtitleClass(const int i);

	string& getExperimentalPropertySubtitle(const int i);

	string& getExperimentalPropertySubtitle(const string title, const int i);

	int getExperimentalPropertySubtitleSize();

	int getExperimentalPropertySubtitleSize(const string title);

	bool hasProperty(const string& attribute);

	void setCurrentValue(const string& attribute, const float value);
	void setCurrentValue(const string& attribute, const float value, const float min, const float max);

	float getCurrentValue(const string& attribute);

	float getCurrentValue(const int i);

	void lockValue(const string& attribute);
	void resetValue(const string& attribute);

	void setCurrentPercentage(const string& subtitle, const float value);
	void setCurrentPercentage(const string& subtitle, const float value, const float min, const float max);

	float getCurrentPercentage(const string& attribute);
	float getCurrentPercentage(const int i);

	float getCurrentPercentageAverage(const int i);
	float getCurrentPercentageAverage(const string title);

	void setMaxPercentage(const string& attribute, const float value);

	float getMaxPercentage(const string& attribute);
	float getMaxPercentage(const int i);

	float getMaxPercentageAverage(const int i);

	float getMinValue(const string& attribute);
	float getMaxValue(const string& attribute);

	void setMinValue(const string& attribute, const float value);
	void setMaxValue(const string& attribute, const float value);

	int getPrecision(const string& attribute);
	void setPrecision(const string& attribute, const int precision);

	void recalculateValues(DraftSchematic* draftSchematic);

	void toString();

	inline int getExperimentalPropertyTitleSize(){
		return experimentalValuesMap.size();
	}

	inline int getValuesToSendSize(){
		return valuesToSend.size();
	}

	inline int getTitleLine(string& title){

		Subclasses* subClasses;
		string exptitle;

		for (int j = 0; j < experimentalValuesMap.size(); ++j) {

			subClasses = experimentalValuesMap.get(j);

			exptitle = subClasses->getClassName();

			if(title == exptitle)
				return j;
		}

		return -1;

	}

	string& getValuesToSend(const int i){
		return valuesToSend.get(i);
	}

	float getAttributeAndValue(DraftSchematic* draftSchematic, string& attribute, const int i){

		DraftSchematicAttribute* attrib = draftSchematic->getAttributeToSet(i);

		attribute = attrib->getAttributeName();
		return getCurrentValue(attribute);

	}

	// Clear
	inline void clear(){
		valuesToSend.removeAll();
	}

	inline void clearAll(){
		experimentalValuesMap.removeAll();
		valuesToSend.removeAll();
	}

};

#endif /*DRAFTSCHEMATICVALUESIMPLEMENTATION_H_*/
