/*
 * LuaBuildingObject.h
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#ifndef LUABUILDINGOBJECT_H_
#define LUABUILDINGOBJECT_H_

#include "engine/engine.h"

#include "server/zone/objects/scene/LuaSceneObject.h"

namespace server {
namespace zone {
namespace objects {
namespace building {
	class BuildingObject;

	class LuaBuildingObject : public LuaSceneObject {
	public:
		// Constants
		static const char className[];
		static Luna<LuaBuildingObject>::RegType Register[];

		// Initialize the pointer
		LuaBuildingObject(lua_State *L);
		~LuaBuildingObject();

		int _setObject(lua_State* L);
		// Methods we will need to use
		int getCell(lua_State* L);
		int grantPermission(lua_State* L);
	private:
		// The pointer to the 'real object' defined in object.cc
		Reference<BuildingObject*> realObject;
	};

}
}
}
}

using namespace server::zone::objects::building;

#endif /*LUABUILDINGOBJECT_H_*/
