/*
 * ObjectManager.h
 *
 *  Created on: Sep 5, 2009
 *      Author: theanswer
 */

#ifndef OBJECTMANAGER_H_
#define OBJECTMANAGER_H_

#include "engine/engine.h"

class SceneObject;

class ObjectManager : public Logger, public ThreadLocal<ObjectManager> {
	Lua* luaInstance;

public:
	ObjectManager();
	virtual ~ObjectManager();

	SceneObject* createObject(uint32 objectCRC, uint64 objectID);

	ObjectManager* initValue() {
		ObjectManager* obj = new ObjectManager();
		return obj;
	}

	// LUA templates
	void registerFunctions();
	static int includeFile(lua_State* L);

};


#endif /* OBJECTMANAGER_H_ */
