/*
 * LuaSceneObject.h
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#ifndef LUASCENEOBJECT_H_
#define LUASCENEOBJECT_H_

#include "engine/engine.h"

#define DYNAMIC_CAST_LUAOBJECTS 1

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
		int _getObject(lua_State* L);
		// Methods we will need to use
		int getParent(lua_State* L);
		int getPositionX(lua_State* L);
		int getPositionZ(lua_State* L);
		int getPositionY(lua_State* L);
		int getDirectionAngle(lua_State* L);
		int getWorldPositionX(lua_State* L);
		int getWorldPositionZ(lua_State* L);
		int getWorldPositionY(lua_State* L);
		int getObjectID(lua_State* L);
		int getParentID(lua_State* L);
		int isInRange(lua_State* L);
		int isInRangeWithObject(lua_State* L);
		int wlock(lua_State* L);
		int unlock(lua_State* L);
		int getServerObjectCRC(lua_State* L);
		int showFlyText(lua_State* L);
		int getDistanceTo(lua_State* L);
		int getDistanceToPosition(lua_State* L);
		int getContainerObject(lua_State* L);
		int getContainerObjectsSize(lua_State* L);
		int getContainerVolumeLimit(lua_State* L);
		int getSlottedObject(lua_State* L);
		int transferObject(lua_State* L);
		//int removeObject(lua_State* L);
		int getGameObjectType(lua_State* L);
		int faceObject(lua_State* L);
		int isFacingObject(lua_State* L);
		int destroyObjectFromWorld(lua_State* L);
		int destroyObjectFromDatabase(lua_State* L);
		int updateDirection(lua_State* L);
		int isCreatureObject(lua_State* L);
		int isAiAgent(lua_State* L);
		int isPlayerCreature(lua_State* L);
		int isCreature(lua_State* L);
		int isBuildingObject(lua_State* L);
		int isActiveArea(lua_State* L);
		int getZoneName(lua_State* L);
		int sendTo(lua_State* L);
		int getCustomObjectName(lua_State* L);
		int setCustomObjectName(lua_State* L);
		int getDisplayedName(lua_State* L);
		int getObjectName(lua_State* L);
		int getContainerObjectById(lua_State* L);
		int hasFullContainerObjects(lua_State* L);
		int setDirectionalHeading(lua_State* L);
		int getTemplateObjectPath(lua_State* L);
		int teleport(lua_State* L);
		int switchZone(lua_State* L);
		int setObjectMenuComponent(lua_State* L);
		int setContainerComponent(lua_State* L);
		int setContainerInheritPermissionsFromParent(lua_State* L);
		int setContainerAllowPermission(lua_State* L);
		int setContainerDenyPermission(lua_State* L);
		int setContainerDefaultAllowPermission(lua_State* L);
		int clearContainerDefaultAllowPermission(lua_State* L);
		int setContainerDefaultDenyPermission(lua_State* L);
		int clearContainerDefaultDenyPermission(lua_State* L);
		int setContainerOwnerID(lua_State* L);
		int setObjectName(lua_State* L);
		int isASubChildOf(lua_State* L);
		int isOwned(lua_State* L);
		int playEffect(lua_State* L);

	protected:
		SceneObject* _getRealSceneObject() {
			return realObject.get();
		}

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
