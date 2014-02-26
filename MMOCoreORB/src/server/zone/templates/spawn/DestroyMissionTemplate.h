
#ifndef DESTROYMISSIONTEMPLATE_H_
#define DESTROYMISSIONTEMPLATE_H_

#include "engine/engine.h"
#include "server/zone/managers/gcw/GCWManager.h"

namespace server {
namespace zone {
namespace templates {
namespace spawn {

class DestroyMissionTemplate : public Object {
public:
	enum LairType {CREATURE, NPC};

protected:
	// String = mobileTemplate, int = number of levels to offset from mission level
	VectorMap<String, int> mobiles;

	VectorMap<uint32, Reference<Vector<String>*> > buildings;

	String name;

	unsigned int faction;

	LairType lairType;

public:
	enum { VERYEASY = 0, EASY, MEDIUM, HARD, VERYHARD};

	//      0-20 20-40 40-60 60-80 80+

	DestroyMissionTemplate(const String& templateName) {
		buildings.setAllowDuplicateInsertPlan();
		buildings.setNullValue(NULL);

		name = templateName;
		faction = 0;
		lairType = CREATURE;
	}

	virtual ~DestroyMissionTemplate() {
	}

	String getBuilding(int level) {
		Vector<String>* objects = NULL;

		if (level <= 20) {
			objects = buildings.get((uint32)VERYEASY);
		} else if (level <= 40) {
			objects = buildings.get((uint32)EASY);
		} else if (level <= 60) {
			objects = buildings.get((uint32)MEDIUM);
		} else if (level <= 80) {
			objects = buildings.get((uint32)HARD);
		} else {
			objects = buildings.get((uint32)VERYHARD);
		}

		if (objects == NULL) {
			for (int i = 0; i < buildings.size() && objects == NULL; ++i) {
				objects = buildings.elementAt(i).getValue();
			}
		}

		if (objects != NULL && objects->size() > 0)
			return objects->get(System::random(objects->size() - 1));
		else
			return String();
	}

	void readObject(LuaObject* templateData) {

		if (templateData->getStringField("faction").length() > 0) {
			String factionString = templateData->getStringField("faction");

			if (factionString == "imperial") {
				faction = GCWManager::IMPERIALHASH;
			} else if (factionString == "rebel") {
				faction = GCWManager::REBELHASH;
			}
		}

		if (templateData->getStringField("lairType").length() > 0) {
			if (templateData->getStringField("lairType") == "npc")
				lairType = NPC;
		}

		LuaObject mobs = templateData->getObjectField("mobiles");

		for (int i = 1; i <= mobs.getTableSize(); ++i) {
			lua_rawgeti(mobs.getLuaState(), -1, i);
			LuaObject mobile(mobs.getLuaState());

			if (mobile.isValidTable()) {
				String mob = mobile.getStringAt(1);
				int level = (int)mobile.getIntAt(2);

				mobiles.put(mob, level);
			}

			mobile.pop();
		}

		mobs.pop();

		LuaObject veryEasy = templateData->getObjectField("buildingsVeryEasy");
		Vector<String>* buildings = this->buildings.get((uint32)VERYEASY);

		if (buildings == NULL) {
			buildings = new Vector<String>();
			this->buildings.put(VERYEASY, buildings);
		}

		for (int i = 1; i <= veryEasy.getTableSize(); ++i) {
			buildings->add(veryEasy.getStringAt(i));
		}

		veryEasy.pop();

		LuaObject easy = templateData->getObjectField("buildingsEasy");
		buildings = this->buildings.get((uint32)EASY);

		if (buildings == NULL) {
			buildings = new Vector<String>();
			this->buildings.put(EASY, buildings);
		}

		for (int i = 1; i <= easy.getTableSize(); ++i) {
			buildings->add(easy.getStringAt(i));
		}

		easy.pop();

		LuaObject medium = templateData->getObjectField("buildingsMedium");

		buildings = this->buildings.get((uint32)MEDIUM);

		if (buildings == NULL) {
			buildings = new Vector<String>();
			this->buildings.put(MEDIUM, buildings);
		}

		for (int i = 1; i <= medium.getTableSize(); ++i) {
			buildings->add(medium.getStringAt(i));
		}

		medium.pop();

		LuaObject hard = templateData->getObjectField("buildingsHard");

		buildings = this->buildings.get((uint32)HARD);

		if (buildings == NULL) {
			buildings = new Vector<String>();
			this->buildings.put(HARD, buildings);
		}

		for (int i = 1; i <= hard.getTableSize(); ++i) {
			buildings->add(hard.getStringAt(i));
		}

		hard.pop();

		LuaObject veryHard = templateData->getObjectField("buildingsVeryHard");

		buildings = this->buildings.get((uint32)VERYHARD);

		if (buildings == NULL) {
			buildings = new Vector<String>();
			this->buildings.put((uint32)VERYHARD, buildings);
		}

		for (int i = 1; i <= veryHard.getTableSize(); ++i) {
			buildings->add(veryHard.getStringAt(i));
		}

		veryHard.pop();

	}

	VectorMap<String, int>* getMobiles() {
		return &mobiles;
	}

	bool isDestroyMissionTemplate() {
		return true;
	}

	String& getName() {
		return name;
	}

	unsigned int getFaction() {
		return faction;
	}

	LairType getLairType() {
		return lairType;
	}

};

}
}
}
}

using namespace server::zone::templates::spawn;


#endif /* DESTROYMISSIONTEMPLATE_H_ */
