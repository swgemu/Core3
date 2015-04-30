/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CRAFTINGVALUES_H_
#define CRAFTINGVALUES_H_

#include "ValuesClasses.h"


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
	VectorMap<String, Reference<Subclasses*> > experimentalValuesMap;

	Vector<String> valuesToSend;

	String EMPTY;

	bool doHide;

	ManagedReference<ManufactureSchematic*> schematic;
	ManagedReference<CreatureObject*> player;
	VectorMap<String, bool> slots;

public:

	static float VALUENOTFOUND;

	enum {
		NORMAL = 1,
		HIDDEN = 2
	};

public:
	CraftingValues();
	CraftingValues(const CraftingValues& values);

	~CraftingValues();

	void setManufactureSchematic(ManufactureSchematic* manu);
	ManufactureSchematic* getManufactureSchematic();
	void setPlayer(CreatureObject* play);
	CreatureObject* getPlayer();

	// Experimental Titles
	void addExperimentalProperty(const String& title, const String& subtitle,
			const float min, const float max, const int precision,
			const bool filler, const int combine);

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

	short getCombineType(const String& attribute);

	void setCurrentValue(const String& attribute, const float value);
	void setCurrentValue(const String& attribute, const float value, const float min, const float max);

	float getCurrentValue(const String& attribute);

	float getCurrentValue(const int i);

	void unlockValue(const String& attribute);
	void lockValue(const String& attribute);
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

	void recalculateValues(bool initial);

	String toString();

	inline int getExperimentalPropertyTitleSize(){
		return experimentalValuesMap.size();
	}

	inline void setSlot(const String& value, bool filled) {
		slots.put(value, filled);
	}

	inline void clearSlots() {
		slots.removeAll();
	}

	inline bool hasSlotFilled(const String& name) {
		if(!slots.contains(name))
			return false;

		return slots.get(name);
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
