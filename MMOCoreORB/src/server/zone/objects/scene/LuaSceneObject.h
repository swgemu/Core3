/*
 * LuaSceneObject.h
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#ifndef LUASCENEOBJECT_H_
#define LUASCENEOBJECT_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
	class SceneObject;

	class LuaSceneObject {
	public:
		// Constants
		static const char className[];
		static Luna<LuaSceneObject>::RegType Register[];

		// Initialize the pointer
		LuaSceneObject(lua_State *L);
		~LuaSceneObject();

		int _setObject(lua_State* L);
		// Methods we will need to use
		int getParent(lua_State* L);
		int getPositionX(lua_State* L);
		int getPositionZ(lua_State* L);
		int getPositionY(lua_State* L);
		int getObjectID(lua_State* L);
		int getParentID(lua_State* L);
		int isInRange(lua_State* L);
		int isInRangeWithObject(lua_State* L);
		int wlock(lua_State* L);
		int unlock(lua_State* L);
		int getServerObjectCRC(lua_State* L);
		int showFlyText(lua_State* L);
		int getDistanceTo(lua_State* L);
		int getContainerObject(lua_State* L);
		int getContainerObjectsSize(lua_State* L);
		int getSlottedObject(lua_State* L);
		int transferObject(lua_State* L);
		//int removeObject(lua_State* L);
		int getGameObjectType(lua_State* L);
		int faceObject(lua_State* L);
		int destroyObjectFromWorld(lua_State* L);
		int updateDirection(lua_State* L);
		int isCreatureObject(lua_State* L);
		int getZoneName(lua_State* L);
		int sendTo(lua_State* L);
		int getCustomObjectName(lua_State* L);
		int setCustomObjectName(lua_State* L);
		int getContainerObjectById(lua_State* L);
		int setDirectionalHeading(lua_State* L);
		int getTemplateObjectPath(lua_State* L);
		int teleport(lua_State* L);
		int switchZone(lua_State* L);
		int setObjectMenuComponent(lua_State* L);


	private:
		// The pointer to the 'real object' defined in object.cc
		Reference<SceneObject*> realObject;
	};

}
}
}
}

using namespace server::zone::objects::scene;

#endif /* LUASCENEOBJECT_H_ */
