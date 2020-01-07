/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CRAFTINGVALUES_H_
#define CRAFTINGVALUES_H_

#include "templates/crafting/ValuesMap.h"
#include "engine/engine.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace manufactureschematic {

   class ManufactureSchematic;
}
}
}
}

using namespace server::zone::objects::manufactureschematic;

namespace server {
 namespace zone {
  namespace objects {
   namespace creature {

   class CreatureObject;
}
}
}
}

using namespace server::zone::objects::creature;



namespace server {
 namespace zone {
  namespace objects {
   namespace manufactureschematic {
   	 namespace craftingvalues {


class CraftingValues : public Serializable, public Logger {
	ValuesMap experimentalValuesMap;

	Vector<String> valuesToSend;

	bool doHide;

	ManagedWeakReference<ManufactureSchematic*> schematic;
	ManagedWeakReference<CreatureObject*> player;
	VectorMap<String, bool> slots;

public:

	enum {
		NORMAL = 1,
		HIDDEN = 2
	};

public:
	CraftingValues();
	CraftingValues(const CraftingValues& values);
	CraftingValues(const ValuesMap& values);

	~CraftingValues();

	void setManufactureSchematic(ManufactureSchematic* manu);
	ManufactureSchematic* getManufactureSchematic();
	void setPlayer(CreatureObject* play);
	CreatureObject* getPlayer();

	// Experimental Titles
	void addExperimentalProperty(const String& title, const String& subtitle,
			const float min, const float max, const int precision,
			const bool filler, const int combine) {
		experimentalValuesMap.addExperimentalProperty(title, subtitle, min, max, precision, filler, combine);
	}

	const String& getExperimentalPropertyTitle(const String& subtitle) const {
		return experimentalValuesMap.getExperimentalPropertyTitle(subtitle);
	}

	const String& getExperimentalPropertyTitle(const int i) const {
		return experimentalValuesMap.getExperimentalPropertyTitle(i);
	}

	const String& getVisibleExperimentalPropertyTitle(const int i) const {
		return experimentalValuesMap.getVisibleExperimentalPropertyTitle(i);
	}

	const String& getExperimentalPropertySubtitlesTitle(const int i) const {
		return experimentalValuesMap.getExperimentalPropertySubtitlesTitle(i);
	}

	const String& getExperimentalPropertySubtitle(const int i) const {
		return experimentalValuesMap.getExperimentalPropertySubtitle(i);
	}

	const String& getExperimentalPropertySubtitle(const String title, const int i) const {
		return experimentalValuesMap.getExperimentalPropertySubtitle(title, i);
	}

	int getExperimentalPropertySubtitleSize() const {
		return experimentalValuesMap.getExperimentalPropertySubtitleSize();
	}

	int getExperimentalPropertySubtitleSize(const String title) const {
		return experimentalValuesMap.getExperimentalPropertySubtitleSize(title);
	}

	bool hasProperty(const String& attribute) const {
		return experimentalValuesMap.hasProperty(attribute);
	}

	bool isHidden(const String& attribute) const {
		return experimentalValuesMap.isHidden(attribute);
	}

	void setHidden(const String& attribute) {
		experimentalValuesMap.setHidden(attribute);
	}

	void unsetHidden(const String& attribute) {
		experimentalValuesMap.unsetHidden(attribute);
	}

	short getCombineType(const String& attribute) const {
		return experimentalValuesMap.getCombineType(attribute);
	}

	void setCurrentValue(const String& attribute, const float value) {
		experimentalValuesMap.setCurrentValue(attribute, value);
	}

	void setCurrentValue(const String& attribute, const float value, const float min, const float max) {
		experimentalValuesMap.setCurrentValue(attribute, value, min, max);
	}

	float getCurrentValue(const String& attribute) const {
		return experimentalValuesMap.getCurrentValue(attribute);
	}

	float getCurrentValue(const int i) const {
		return experimentalValuesMap.getCurrentValue(i);
	}

	void lockValue(const String& attribute) {
		experimentalValuesMap.lockValue(attribute);
	}

	void unlockValue(const String& attribute) {
		experimentalValuesMap.unlockValue(attribute);
	}

	void resetValue(const String& attribute) {
		experimentalValuesMap.resetValue(attribute);
	}

	void setCurrentPercentage(const String& subtitle, const float value) {
		experimentalValuesMap.setCurrentPercentage(subtitle, value);
	}

	void setCurrentPercentage(const String& subtitle, const float value, const float max) {
		experimentalValuesMap.setCurrentPercentage(subtitle, value, max);
	}

	float getCurrentPercentage(const String& attribute) const {
		return experimentalValuesMap.getCurrentPercentage(attribute);
	}

	float getCurrentPercentage(const int i) const {
		return experimentalValuesMap.getCurrentPercentage(i);
	}

	float getCurrentVisiblePercentage(const String title) const {
		return experimentalValuesMap.getCurrentVisiblePercentage(title);
	}

	void setMaxPercentage(const String& attribute, const float value) {
		experimentalValuesMap.setMaxPercentage(attribute, value);
	}

	float getMaxPercentage(const String& attribute) const {
		return experimentalValuesMap.getMaxPercentage(attribute);
	}

	float getMaxPercentage(const int i) const {
		return experimentalValuesMap.getMaxPercentage(i);
	}

	float getMaxVisiblePercentage(const int i) const {
		return experimentalValuesMap.getMaxVisiblePercentage(i);
	}

	float getMinValue(const String& attribute) const {
		return experimentalValuesMap.getMinValue(attribute);
	}

	float getMaxValue(const String& attribute) const {
		return experimentalValuesMap.getMaxValue(attribute);
	}

	void setMinValue(const String& attribute, const float value) {
		experimentalValuesMap.setMinValue(attribute, value);
	}

	void setMaxValue(const String& attribute, const float value) {
		experimentalValuesMap.setMaxValue(attribute, value);
	}

	int getPrecision(const String& attribute) const {
		return experimentalValuesMap.getPrecision(attribute);
	}

	void setPrecision(const String& attribute, const int precision) {
		experimentalValuesMap.setPrecision(attribute, precision);
	}

	void recalculateValues(bool initial);

	String toString() const;

	inline int getExperimentalPropertyTitleSize() const {
		return experimentalValuesMap.size();
	}

	inline void setSlot(const String& value, bool filled) {
		slots.put(value, filled);
	}

	inline void clearSlots() {
		slots.removeAll();
	}

	inline bool hasSlotFilled(const String& name) const {
		if (!slots.contains(name))
			return false;

		return slots.get(name);
	}

	inline int getVisibleExperimentalPropertyTitleSize() const {
		return experimentalValuesMap.getVisibleExperimentalPropertyTitleSize();
	}

	inline int getSubtitleCount() const {
		return experimentalValuesMap.getSubtitleCount();
	}

	inline int getValuesToSendSize() const {
		return valuesToSend.size();
	}

	inline int getTitleLine(const String& title) const {
		return experimentalValuesMap.getTitleLine(title);
	}

	const String& getValuesToSend(const int i) const {
		return valuesToSend.get(i);
	}

	float getAttributeAndValue(const String& attribute, const int i) const {
		String attributeName = getExperimentalPropertySubtitle(i);

		return getCurrentValue(attributeName);
	}

	// Clear
	inline void clear() {
		valuesToSend.removeAll();
	}

	void clearAll();

};

}
}
}
}
}

using namespace server::zone::objects::manufactureschematic::craftingvalues;

#endif /*CRAFTINGVALUES_H_*/
