/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef VALUESMAP_H_
#define VALUESMAP_H_

#include "ValuesClasses.h"

class ValuesMap : public VectorMap<String, Reference<Subclasses*> > {
	String EMPTY = "";

public:
	static float VALUENOTFOUND;

	// Ingredient combine types
	static const short RESOURCECOMBINE = 0x00;
	static const short LINEARCOMBINE = 0x01;
	static const short PERCENTAGECOMBINE = 0x02;
	static const short BITSETCOMBINE = 0x03;
	static const short OVERRIDECOMBINE = 0x04;
	static const short LIMITEDCOMBINE = 0x05;

	void addExperimentalProperty(const String& title, const String& subtitle,
			const float min, const float max, const int precision,
			const bool filler, const int combine);

	String& getExperimentalPropertyTitle(const String& subtitle);
	String& getExperimentalPropertyTitle(const int i);
	String& getVisibleExperimentalPropertyTitle(const int i);

	String& getExperimentalPropertySubtitlesTitle(const int i);
	String& getExperimentalPropertySubtitle(const int i);
	String& getExperimentalPropertySubtitle(const String& title, const int i);

	int getExperimentalPropertySubtitleSize();
	int getExperimentalPropertySubtitleSize(const String& title);

	bool hasProperty(const String& attribute);

	bool isHidden(const String& attribute);
	void setHidden(const String& attribute);
	void unsetHidden(const String& attribute);

	short getCombineType(const String& attribute);

	void setCurrentValue(const String& attribute, const float value);
	void setCurrentValue(const String& attribute, const float value, const float min, const float max);

	float getCurrentValue(const String& attribute);
	float getCurrentValue(const int i);

	void lockValue(const String& attribute);
	void unlockValue(const String& attribute);
	void resetValue(const String& attribute);

	void setCurrentPercentage(const String& subtitle, const float value);
	void setCurrentPercentage(const String& subtitle, const float value, const float max);

	float getCurrentPercentage(const String& attribute);
	float getCurrentPercentage(const int i);

	float getCurrentVisiblePercentage(const String title);

	void setMaxPercentage(const String& attribute, const float value);

	float getMaxPercentage(const String& attribute);
	float getMaxPercentage(const int i);

	float getMaxVisiblePercentage(const int i);

	float getMinValue(const String& attribute);
	float getMaxValue(const String& attribute);

	void setMinValue(const String& attribute, const float value);
	void setMaxValue(const String& attribute, const float value);

	int getPrecision(const String& attribute);
	void setPrecision(const String& attribute, const int precision);

	inline int getVisibleExperimentalPropertyTitleSize() {
		int tempSize = 0;
		Subclasses* subclasses;

		for(int i = 0; i < size(); ++i) {
			subclasses = get(i);

			if(!subclasses->hasAllHiddenItems())
				tempSize++;
		}

		return tempSize;
	}

	inline int getSubtitleCount() {
		Subclasses* subclasses;

		int count = 0;

		for (int j = 0; j < size(); ++j) {
			subclasses = get(j);

			count += subclasses->size();
		}

		return count;
	}

	inline int getTitleLine(String& title) {
		Subclasses* subClasses;
		String exptitle;
		int counter = 0;

		for (int j = 0; j < size(); ++j) {

			subClasses = get(j);

			exptitle = subClasses->getClassTitle();

			if (!subClasses->isClassHidden()) {
				if (title == exptitle)
					return counter;

				counter++;
			}
		}

		return -1;
	}
};

#endif /*VALUESMAP_H_*/
