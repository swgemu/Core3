/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef ATTRIBUTESMAP_H_
#define ATTRIBUTESMAP_H_

#include "ValuesClasses.h"
#include "system/util/Vector.h"

//#define DEBUG_ATTRIBUTES_MAP

class AttributesMap : public Object, public Logger {
	Mutex mutex;

	Vector<String> attributes;
	Vector<String> visibleGroups;
	VectorMap<String, String> attributeGroups;
	VectorMap<String, Reference<Values*>> attributeValues;

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

	AttributesMap() {
		setLoggingName("AttributesMap");

		attributeValues.setNullValue(nullptr);
	}

	~AttributesMap() {
	}

	void addExperimentalAttribute(const String& attribute, const String& group, const float min, const float max, const int precision, const bool filler, const int combine);

	// Returns the attribute name from the index
	const String& getAttribute(const int i) const;

	const String& getAttributeGroup(const String& attribute) const;

	const String& getVisibleAttributeGroup(const int i) const;
	int getTotalVisibleAttributeGroups() const;

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

	inline int getSize() const {
		return attributes.size();
	}

	inline void addAttribute(const String& attribute) {
		if (attributes.contains(attribute))
			return;

		attributes.add(attribute);
	}

	inline void addVisibleGroup(const String& group) {
#ifdef DEBUG_ATTRIBUTES_MAP
		info(true) << "Attempting to add Visible Experimental Group: " << group;
#endif // DEBUG_ATTRIBUTES_MAP

		if (visibleGroups.contains(group))
			return;

		visibleGroups.add(group);

#ifdef DEBUG_ATTRIBUTES_MAP
		info(true) << "Adding Visible Experimental Group: " << group << " with a new Total Groups of " << visibleGroups.size();
#endif // DEBUG_ATTRIBUTES_MAP
	}

	inline void removeVisibleGroup(const String& group) {
#ifdef DEBUG_ATTRIBUTES_MAP
		info(true) << "Attempting to remove Visible Experimental Group: " << group;
#endif // DEBUG_ATTRIBUTES_MAP

		uint32 groupHash = group.hashCode();

		for (int i = 0; i < visibleGroups.size(); ++i) {
			uint32 visHash = visibleGroups.get(i).hashCode();

			if (groupHash == visHash) {
				visibleGroups.remove(i);
				return;
			}
		}
	}

	inline bool hasExperimentalAttribute(const String& attribute) const {
		// info(true) << "hasExperimentalAttribute has a attributes size of " << attributes.size() << " and is checking for " << attribute;
		uint32 attributeHash = attribute.hashCode();

		for (int i = 0; i < attributes.size(); ++i) {
			uint32 iteratedHash = attributes.get(i).hashCode();

			if (iteratedHash == attributeHash)
				return true;
		}

		return false;
	}

	inline void removeAll() {
		Locker lock(&mutex);

		attributes.removeAll();
		visibleGroups.removeAll();
		attributeGroups.removeAll();
		attributeValues.removeAll();
	}
};

#endif /*ATTRIBUTESMAP_H_*/
