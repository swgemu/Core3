
#ifndef THEATERSPAWNTEMPLATE_H_
#define THEATERSPAWNTEMPLATE_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace templates {
namespace spawn {

class TheaterSpawnTemplate : public Object {

protected:
	Vector<String> mobiles;

	int spawnLimit;

	String building;
	// TODO: add vector for building's child objects and their position relative to the building

	String name;

	TheaterSpawnTemplate(const String& templateName) {
		spawnLimit = 15;
		name = templateName;
	}

	virtual ~TheaterSpawnTemplate() {
	}

	void readObject(LuaObject* templateData) {
		spawnLimit = templateData->getIntField("spawnLimit");

		LuaObject mobs = templateData->getObjectField("mobiles");
		for (int i = 1; i <= mobs.getTableSize(); ++i) {
			mobiles.add(mobs.getStringAt(i));
		}

		mobs.pop();

		building = templateData->getStringField("building");

	}

	String getBuilding(int level) {
		return building;
	}

	int getSpawnLimit() {
		return spawnLimit;
	}

	Vector<String>* getMobiles() {
		return &mobiles;
	}

	bool isTheaterSpawnTemplate() {
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

using namespace server::zone::templates::spawn;


#endif /* THEATERSPAWNTEMPLATE_H_ */
