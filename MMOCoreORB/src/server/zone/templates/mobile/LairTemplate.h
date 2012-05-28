/*
 * LairTemplate.h
 *
 *  Created on: 29/08/2011
 *      Author: TheAnswer
 */

#ifndef LAIRTEMPLATE_H_
#define LAIRTEMPLATE_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace templates {
namespace mobile {

class LairTemplate : public Object {
protected:
	VectorMap<String, uint32> mobiles;
	int spawnLimit;

	VectorMap<uint32, Vector<String>* > buildings;

	String name;

public:
	enum { VERYEASY = 0, EASY, MEDIUM, HARD, VERYHARD};

	//      0-50 50-100 100-200 200-300 300+

	LairTemplate(const String& templateName) {
		buildings.setAllowDuplicateInsertPlan();
		buildings.setNullValue(NULL);

		name = templateName;
	}

	virtual ~LairTemplate() {
		for (int i = 0; i < buildings.size(); ++i)
			delete buildings.elementAt(i).getValue();
	}

	String getBuilding(int level) {
		Vector<String>* objects = NULL;

		if (level <= 50) {
			objects = buildings.get((uint32)VERYEASY);
		} else if (level <= 100) {
			objects = buildings.get((uint32)EASY);
		} else if (level <= 200) {
			objects = buildings.get((uint32)MEDIUM);
		} else if (level <= 300) {
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
		spawnLimit = templateData->getIntField("spawnLimit");

		LuaObject mobs = templateData->getObjectField("mobiles");

		for (int i = 1; i <= mobs.getTableSize(); ++i) {
			lua_rawgeti(mobs.getLuaState(), -1, i);
			LuaObject mobile(mobs.getLuaState());

			if (mobile.isValidTable()) {
				String mob = mobile.getStringAt(1);
				int level = mobile.getIntAt(2);

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

	int getSpawnLimit() {
		return spawnLimit;
	}

	VectorMap<String, uint32>* getMobiles() {
		return &mobiles;
	}

	bool isLairTemplate() {
		return true;
	}

	String& getName() {
		return name;
	}

};

}
}
}
}

using namespace server::zone::templates::mobile;


#endif /* LAIRTEMPLATE_H_ */
