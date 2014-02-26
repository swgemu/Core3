
#ifndef DYNAMICSPAWNTEMPLATE_H_
#define DYNAMICSPAWNTEMPLATE_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace templates {
namespace spawn {

class DynamicSpawnTemplate : public Object {

protected:
	Vector<String> mobiles;

	int spawnLimit;

	String name;

	DynamicSpawnTemplate(const String& templateName) {
		spawnLimit = 15;
		name = templateName;
	}

	virtual ~DynamicSpawnTemplate() {
	}

	void readObject(LuaObject* templateData) {
		spawnLimit = templateData->getIntField("spawnLimit");

		LuaObject mobs = templateData->getObjectField("mobiles");
		for (int i = 1; i <= mobs.getTableSize(); ++i) {
			mobiles.add(mobs.getStringAt(i));
		}

		mobs.pop();

	}

	int getSpawnLimit() {
		return spawnLimit;
	}

	Vector<String>* getMobiles() {
		return &mobiles;
	}

	bool isDynamicSpawnTemplate() {
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


#endif /* DYNAMICSPAWNTEMPLATE_H_ */
