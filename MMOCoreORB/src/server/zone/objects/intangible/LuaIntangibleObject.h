/*
 * LuaIntangibleObject.h
 *
 *  Created on: 13/01/2012
 *      Author: victor
 */

#ifndef LUAINTANGIBLEOBJECT_H_
#define LUAINTANGIBLEOBJECT_H_

#include "server/zone/objects/scene/LuaSceneObject.h"

#include "IntangibleObject.h"

class LuaIntangibleObject : public LuaSceneObject {
public:
	// Constants
	static const char className[];
	static Luna<LuaIntangibleObject>::RegType Register[];

	// Initialize the pointer
	LuaIntangibleObject(lua_State *L);
	~LuaIntangibleObject();

	int _setObject(lua_State* L);
	// Methods we will need to use


private:
	// The pointer to the 'real object' defined in object.cc
	Reference<IntangibleObject*> realObject;
};


#endif /* LUAINTANGIBLEOBJECT_H_ */
