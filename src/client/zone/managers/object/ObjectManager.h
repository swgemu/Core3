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
class ObjectMap;

class ObjectManager : public Mutex, public Logger {
	Lua* luaInstance;

	ObjectMap* objectMap;

	ObjectFactory<SceneObject* (LuaObject*), uint32> objectFactory;

	void registerObjectTypes();

public:
	ObjectManager();
	virtual ~ObjectManager();

	SceneObject* createObject(uint32 objectCRC, uint64 objectID);

	SceneObject* getObject(uint64 objectID);

	// LUA templates
	void registerFunctions();
	static int includeFile(lua_State* L);

};


#endif /* OBJECTMANAGER_H_ */
