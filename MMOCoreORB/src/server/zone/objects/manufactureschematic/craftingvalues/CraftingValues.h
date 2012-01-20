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

#ifndef CRAFTINGVALUES_H_
#define CRAFTINGVALUES_H_

#include "ValuesClasses.h"

class CraftingValues : public Serializable, public Logger {
	VectorMap<String, Reference<Subclasses*> > experimentalValuesMap;

	Vector<String> valuesToSend;

	String EMPTY;

	bool doHide;

public:

	static float VALUENOTFOUND;

	static const int NORMAL = 1;
	static const int HIDDEN = 2;

public:
	CraftingValues();
	CraftingValues(const CraftingValues& values);

	~CraftingValues();
	// Experimental Titles
	void addExperimentalProperty(const String& title, const String& subtitle,
			const float min, const float max, const int precision, const bool filler);

	String& getExperimentalPropertyTitle(const String& subtitle);
	String& getExperimentalPropertyTitle(const int i);
	String& getVisibleExperimentalPropertyTitle(const int i);

	String& getExperimentalPropertySubtitlesTitle(const int i);

	String& getExperimentalPropertySubtitle(const int i);

	String& getExperimentalPropertySubtitle(const String title, const int i);

	int getExperimentalPropertySubtitleSize();

	int getExperimentalPropertySubtitleSize(const String title);

	bool hasProperty(const String& attribute);

	bool isHidden(const String& attribute);
	void setHidden(const String& attribute);
	void unsetHidden(const String& attribute);

	void setCurrentValue(const String& attribute, const float value);
	void setCurrentValue(const String& attribute, const float value, const float min, const float max);

	float getCurrentValue(const String& attribute);

	float getCurrentValue(const int i);

	void unlockValue(const String& attribute);
	void lockValue(const String& attribute);
	void resetValue(const String& attribute);

	void setCurrentPercentage(const String& subtitle, const float value);
	void setCurrentPercentage(const String& subtitle, const float value, const float min, const float max);

	float getCurrentPercentage(const String& attribute);
	float getCurrentPercentage(const int i);

	float getCurrentPercentageAverage(const int i);
	float getCurrentPercentageAverage(const String title);

	void setMaxPercentage(const String& attribute, const float value);

	float getMaxPercentage(const String& attribute);
	float getMaxPercentage(const int i);

	float getMaxPercentageAverage(const int i);

	float getMinValue(const String& attribute);
	float getMaxValue(const String& attribute);

	void setMinValue(const String& attribute, const float value);
	void setMaxValue(const String& attribute, const float value);

	int getPrecision(const String& attribute);
	void setPrecision(const String& attribute, const int precision);

	void recalculateValues(bool initial);

	String toString();

	inline int getExperimentalPropertyTitleSize(){
		return experimentalValuesMap.size();
	}

	inline int getVisibleExperimentalPropertyTitleSize(){
		int tempSize = 0;
		Subclasses* subclasses;

		for(int i = 0; i < experimentalValuesMap.size(); ++i) {
			subclasses = experimentalValuesMap.get(i);

			if(!subclasses->hasAllHiddenItems())
				tempSize++;
		}
		return tempSize;
	}

	inline int getSubtitleCount(){
		Subclasses* subclasses;

		int count = 0;

		for (int j = 0; j < experimentalValuesMap.size(); ++j) {
			subclasses = experimentalValuesMap.get(j);

			count += subclasses->size();
		}
		return count;
	}

	inline int getValuesToSendSize(){
		return valuesToSend.size();
	}

	inline int getTitleLine(String& title){

		Subclasses* subClasses;
		String exptitle;
		int counter = 0;

		for (int j = 0; j < experimentalValuesMap.size(); ++j) {

			subClasses = experimentalValuesMap.get(j);

			exptitle = subClasses->getClassTitle();

			if(!subClasses->isClassHidden()) {
				if (title == exptitle)
					return counter;
				counter++;
			}
		}

		return -1;

	}

	String& getValuesToSend(const int i){
		return valuesToSend.get(i);
	}

	float getAttributeAndValue(String& attribute, const int i){

		String attributeName = getExperimentalPropertySubtitle(i);

		return getCurrentValue(attributeName);

	}

	// Clear
	inline void clear(){
		valuesToSend.removeAll();
	}

	inline void clearAll() {
		doHide = true;
		experimentalValuesMap.removeAll();
		valuesToSend.removeAll();
	}

};

#endif /*CRAFTINGVALUES_H_*/
