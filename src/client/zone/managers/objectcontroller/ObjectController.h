/*
 * ObjectController.h
 *
 *  Created on: Sep 6, 2009
 *      Author: theanswer
 */

#ifndef OBJECTCONTROLLER_H_
#define OBJECTCONTROLLER_H_

#include "engine/engine.h"

class Zone;
class SceneObject;

class ObjectController : public Singleton<ObjectController> {
	Zone* zone;
public:
	ObjectController();

	void handleObjectController(SceneObject* object, uint32 header1, uint32 header2, Message* pack);

	void handleSpatialChat(SceneObject* object, Message* pack);

	bool doCommand(uint32 crc, const UnicodeString& arguments);

	void doSayCommand(const UnicodeString& msg);

	inline void setZone(Zone* zon) {
		zone = zon;
	}
};


#endif /* OBJECTCONTROLLER_H_ */
