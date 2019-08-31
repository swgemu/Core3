/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef VALUESMAP_H_
#define VALUESMAP_H_

#include "ValuesClasses.h"

class ValuesMap : public VectorMap<String, Reference<Subclasses*> > {
	const static String EMPTY;

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

	const String& getExperimentalPropertyTitle(const String& subtitle) const;
	const String& getExperimentalPropertyTitle(const int i) const;
	const String& getVisibleExperimentalPropertyTitle(const int i) const;

	const String& getExperimentalPropertySubtitlesTitle(const int i) const;
	const String& getExperimentalPropertySubtitle(const int i) const;
	const String& getExperimentalPropertySubtitle(const String& title, const int i) const;

	int getExperimentalPropertySubtitleSize() const;
	int getExperimentalPropertySubtitleSize(const String& title) const;

	bool hasProperty(const String& attribute) const;

	bool isHidden(const String& attribute) const;
	void setHidden(const String& attribute);
	void unsetHidden(const String& attribute);

	short getCombineType(const String& attribute) const;

	void setCurrentValue(const String& attribute, const float value);
	void setCurrentValue(const String& attribute, const float value, const float min, const float max);

	float getCurrentValue(const String& attribute) const;
	float getCurrentValue(const int i) const;

	void lockValue(const String& attribute);
	void unlockValue(const String& attribute);
	void resetValue(const String& attribute);

	void setCurrentPercentage(const String& subtitle, const float value);
	void setCurrentPercentage(const String& subtitle, const float value, const float max);

	float getCurrentPercentage(const String& attribute) const;
	float getCurrentPercentage(const int i) const;

	float getCurrentVisiblePercentage(const String title) const;

	void setMaxPercentage(const String& attribute, const float value);

	float getMaxPercentage(const String& attribute) const;
	float getMaxPercentage(const int i) const;

	float getMaxVisiblePercentage(const int i) const;

	float getMinValue(const String& attribute) const;
	float getMaxValue(const String& attribute) const;

	void setMinValue(const String& attribute, const float value);
	void setMaxValue(const String& attribute, const float value);

	int getPrecision(const String& attribute) const;
	void setPrecision(const String& attribute, const int precision);

	inline int getVisibleExperimentalPropertyTitleSize() const {
		int tempSize = 0;
		const Subclasses* subclasses;

		for(int i = 0; i < size(); ++i) {
			subclasses = get(i);

			if(!subclasses->hasAllHiddenItems())
				tempSize++;
		}

		return tempSize;
	}

	inline int getSubtitleCount() const {
		const Subclasses* subclasses;

		int count = 0;

		for (int j = 0; j < size(); ++j) {
			subclasses = get(j);

			count += subclasses->size();
		}

		return count;
	}

	inline int getTitleLine(const String& title) const {
		const Subclasses* subClasses;
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
