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

public:
	const static uint32 VERYEASY = 0;
	const static uint32 EASY = 1;
	const static uint32 MEDIUM = 2;
	const static uint32 HARD = 3;
	const static uint32 VERYHARD = 4;

	LairTemplate() {
		buildings.setAllowDuplicateInsertPlan();
		buildings.setNullValue(NULL);
	}

	virtual ~LairTemplate() {
		for (int i = 0; i < buildings.size(); ++i)
			delete buildings.elementAt(i).getValue();
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
		Vector<String>* buildings = this->buildings.get(VERYEASY);

		if (buildings == NULL) {
			buildings = new Vector<String>();
			this->buildings.put(VERYEASY, buildings);
		}

		for (int i = 1; i <= veryEasy.getTableSize(); ++i) {
			buildings->add(veryEasy.getStringAt(i));
		}

		veryEasy.pop();

		LuaObject easy = templateData->getObjectField("buildingsEasy");
		buildings = this->buildings.get(EASY);

		if (buildings == NULL) {
			buildings = new Vector<String>();
			this->buildings.put(EASY, buildings);
		}

		for (int i = 1; i <= easy.getTableSize(); ++i) {
			buildings->add(easy.getStringAt(i));
		}

		easy.pop();

		LuaObject medium = templateData->getObjectField("buildingsMedium");

		buildings = this->buildings.get(MEDIUM);

		if (buildings == NULL) {
			buildings = new Vector<String>();
			this->buildings.put(MEDIUM, buildings);
		}

		for (int i = 1; i <= medium.getTableSize(); ++i) {
			buildings->add(medium.getStringAt(i));
		}

		medium.pop();

		LuaObject hard = templateData->getObjectField("buildingsHard");

		buildings = this->buildings.get(HARD);

		if (buildings == NULL) {
			buildings = new Vector<String>();
			this->buildings.put(HARD, buildings);
		}

		for (int i = 1; i <= hard.getTableSize(); ++i) {
			buildings->add(hard.getStringAt(i));
		}

		hard.pop();

		LuaObject veryHard = templateData->getObjectField("buildingsVeryHard");

		buildings = this->buildings.get(VERYHARD);

		if (buildings == NULL) {
			buildings = new Vector<String>();
			this->buildings.put(VERYHARD, buildings);
		}

		for (int i = 1; i <= veryHard.getTableSize(); ++i) {
			buildings->add(veryHard.getStringAt(i));
		}

		veryHard.pop();

	}


};

}
}
}
}

using namespace server::zone::templates::mobile;


#endif /* LAIRTEMPLATE_H_ */
