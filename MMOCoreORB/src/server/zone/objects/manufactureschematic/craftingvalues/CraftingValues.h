/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CRAFTINGVALUES_H_
#define CRAFTINGVALUES_H_

#include "templates/crafting/AttributesMap.h"
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
	AttributesMap attributesMap;

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
	CraftingValues(const AttributesMap& map);

	~CraftingValues();

	void setManufactureSchematic(ManufactureSchematic* manu);
	ManufactureSchematic* getManufactureSchematic();
	void setPlayer(CreatureObject* play);
	CreatureObject* getPlayer();

	// new Implementation of AttributesMap
	void addExperimentalAttribute(const String& attribute, const String& group, const float min, const float max, const int precision, const bool filler, const int combine) {
		attributesMap.addExperimentalAttribute(attribute, group, min, max, precision, filler, combine);
	}

	const String& getAttribute(const int i) const {
		return attributesMap.getAttribute(i);
	}

	const String& getAttributeGroup(const String& attribute) const {
		return attributesMap.getAttributeGroup(attribute);
	}

	const String& getVisibleAttributeGroup(const int i) const {
		return attributesMap.getVisibleAttributeGroup(i);
	}

	int getTotalExperimentalAttributes() const {
		return attributesMap.getSize();
	}

	bool hasExperimentalAttribute(const String& attribute) const {
		return attributesMap.hasExperimentalAttribute(attribute);
	}

	bool isHidden(const String& attribute) const {
		return attributesMap.isHidden(attribute);
	}

	void setHidden(const String& attribute) {
		attributesMap.setHidden(attribute);
	}

	void unsetHidden(const String& attribute) {
		attributesMap.unsetHidden(attribute);
	}

	short getCombineType(const String& attribute) const {
		return attributesMap.getCombineType(attribute);
	}

	void setCurrentValue(const String& attribute, const float value) {
		attributesMap.setCurrentValue(attribute, value);
	}

	void setCurrentValue(const String& attribute, const float value, const float min, const float max) {
		attributesMap.setCurrentValue(attribute, value, min, max);
	}

	float getCurrentValue(const String& attribute) const {
		return attributesMap.getCurrentValue(attribute);
	}

	float getCurrentValue(const int i) const {
		return attributesMap.getCurrentValue(i);
	}

	void lockValue(const String& attribute) {
		attributesMap.lockValue(attribute);
	}

	void unlockValue(const String& attribute) {
		attributesMap.unlockValue(attribute);
	}

	void resetValue(const String& attribute) {
		attributesMap.resetValue(attribute);
	}

	void setCurrentPercentage(const String& subtitle, const float value) {
		attributesMap.setCurrentPercentage(subtitle, value);
	}

	void setCurrentPercentage(const String& subtitle, const float value, const float max) {
		attributesMap.setCurrentPercentage(subtitle, value, max);
	}

	float getCurrentPercentage(const String& attribute) const {
		return attributesMap.getCurrentPercentage(attribute);
	}

	float getCurrentPercentage(const int i) const {
		return attributesMap.getCurrentPercentage(i);
	}

	float getCurrentVisiblePercentage(const String title) const {
		return attributesMap.getCurrentVisiblePercentage(title);
	}

	void setMaxPercentage(const String& attribute, const float value) {
		attributesMap.setMaxPercentage(attribute, value);
	}

	float getMaxPercentage(const String& attribute) const {
		return attributesMap.getMaxPercentage(attribute);
	}

	float getMaxPercentage(const int i) const {
		return attributesMap.getMaxPercentage(i);
	}

	float getMaxVisiblePercentage(const int i) const {
		return attributesMap.getMaxVisiblePercentage(i);
	}

	float getMinValue(const String& attribute) const {
		return attributesMap.getMinValue(attribute);
	}

	float getMaxValue(const String& attribute) const {
		return attributesMap.getMaxValue(attribute);
	}

	void setMinValue(const String& attribute, const float value) {
		attributesMap.setMinValue(attribute, value);
	}

	void setMaxValue(const String& attribute, const float value) {
		attributesMap.setMaxValue(attribute, value);
	}

	int getPrecision(const String& attribute) const {
		return attributesMap.getPrecision(attribute);
	}

	void setPrecision(const String& attribute, const int precision) {
		attributesMap.setPrecision(attribute, precision);
	}

	inline int getTotalVisibleAttributeGroups() const {
		return attributesMap.getTotalVisibleAttributeGroups();
	}

	void recalculateValues(bool initial);

	String toString() const;

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

	inline int getValuesToSendSize() const {
		return valuesToSend.size();
	}

	const String& getValuesToSend(const int i) const {
		return valuesToSend.get(i);
	}

	float getAttributeAndValue(const String& attribute, const int i) const {
		String attributeName = getAttribute(i);

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
