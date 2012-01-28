/*
 * LuaSceneObject.cpp
 *
 *  Created on: 27/05/2011
 *      Author: victor
 */

#include "LuaSceneObject.h"
#include "SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/packets/cell/UpdateCellPermissionsMessage.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/object/Animation.h"

const char LuaSceneObject::className[] = "LuaSceneObject";

Luna<LuaSceneObject>::RegType LuaSceneObject::Register[] = {
		{ "_setObject", &LuaSceneObject::_setObject },
		{ "getParent", &LuaSceneObject::getParent },
		{ "getObjectID", &LuaSceneObject::getObjectID },
		{ "getPositionX", &LuaSceneObject::getPositionX },
		{ "getPositionY", &LuaSceneObject::getPositionY },
		{ "getPositionZ", &LuaSceneObject::getPositionZ },
		{ "getParentID", &LuaSceneObject::getParentID },
		{ "isInRangeWithObject", &LuaSceneObject::isInRangeWithObject },
		{ "doAnimation", &LuaSceneObject::doAnimation },
		{ "setCustomObjectName", &LuaSceneObject::setCustomObjectName},
		{ "getDistanceTo", &LuaSceneObject::getDistanceTo },
		{ "updateDirection", &LuaSceneObject::updateDirection },
		{ "getServerObjectCRC", &LuaSceneObject::getServerObjectCRC },
		{ "showFlyText", &LuaSceneObject::showFlyText },
		{ "getContainerObject", &LuaSceneObject::getContainerObject },
		{ "getContainerObjectsSize", &LuaSceneObject::getContainerObjectsSize },
		{ "getSlottedObject", &LuaSceneObject::getSlottedObject },
		{ "transferObject", &LuaSceneObject::transferObject },
//		{ "removeObject", &LuaSceneObject::removeObject },
		{ "getGameObjectType", &LuaSceneObject::getGameObjectType },
		{ "faceObject", &LuaSceneObject::faceObject },
		{ "destroyObjectFromWorld", &LuaSceneObject::destroyObjectFromWorld },
		{ "isCreatureObject", &LuaSceneObject::isCreatureObject },
		{ "updateCellPermission", &LuaSceneObject::updateCellPermission },
		{ "updateCellPermissionGroup", &LuaSceneObject::updateCellPermissionGroup },
		{ "sendTo", &LuaSceneObject::sendTo },
		{ "getCustomObjectName", &LuaSceneObject::getCustomObjectName },
		{ "getContainerObjectById", &LuaSceneObject::getContainerObjectById },
		{ "getContainerObjectByTemplate", &LuaSceneObject::getContainerObjectByTemplate },
		{ "setDirectionalHeading", &LuaSceneObject::setDirectionalHeading },
		{ "getZoneName", &LuaSceneObject::getZoneName },
		{ "getTemplateObjectPath", &LuaSceneObject::getTemplateObjectPath },
		{ "teleport", &LuaSceneObject::teleport },
		{ "switchZone", &LuaSceneObject::switchZone },
		{ 0, 0 }
};

LuaSceneObject::LuaSceneObject(lua_State *L) {
	realObject = (SceneObject*)lua_touserdata(L, 1);
}

LuaSceneObject::~LuaSceneObject(){
}

int LuaSceneObject::_setObject(lua_State* L) {
	realObject = (SceneObject*)lua_touserdata(L, -1);

	return 0;
}

int LuaSceneObject::doAnimation(lua_State* L) {
	String anim = lua_tostring(L, -1);



	if (realObject != NULL && realObject->isCreatureObject() && anim != "") {
		CreatureObject* creature = cast<CreatureObject*>(realObject.get());

		Animation* msg = new Animation(creature, anim);

		realObject->broadcastMessage(msg, true);
	}

	return 0;
}

int LuaSceneObject::setCustomObjectName(lua_State* L) {
	String value = lua_tostring(L, -1);

	realObject->setCustomObjectName(value, true);

	return 0;
}

int LuaSceneObject::switchZone(lua_State* L) {
	uint64 parentid = lua_tointeger(L, -1);
	float y = lua_tonumber(L, -2);
	float z = lua_tonumber(L, -3);
	float x = lua_tonumber(L, -4);
	String planet = lua_tostring(L, -5);

	realObject->switchZone(planet, x, z, y, parentid);

	return 0;
}

int LuaSceneObject::getTemplateObjectPath(lua_State* L) {
	SceneObject* obj = (SceneObject*) lua_touserdata(L, -1);

	if (obj != NULL) {
		String tempPath = obj->getObjectTemplate()->getFullTemplateString();

		lua_pushstring(L, tempPath);
	} else {
		lua_pushnil(L);
	}

	return 1;
}

int LuaSceneObject::teleport(lua_State* L) {
	uint64 parentID = lua_tointeger(L, -1);
	float y = lua_tonumber(L, -2);
	float z = lua_tonumber(L, -3);
	float x = lua_tonumber(L, -4);

	realObject->teleport(x, z, y, parentID);

	return 0;
}

int LuaSceneObject::getZoneName(lua_State* L) {
	Zone* zone = realObject->getZone();

	String name = "";

	if (zone != NULL) {
		name = zone->getZoneName();
	}

	lua_pushstring(L, name);

	return 1;
}

int LuaSceneObject::getPositionX(lua_State* L) {
	lua_pushnumber(L, realObject->getPositionX());

	return 1;
}

int LuaSceneObject::getPositionZ(lua_State* L) {
	lua_pushnumber(L, realObject->getPositionZ());

	return 1;
}

int LuaSceneObject::getPositionY(lua_State* L) {
	lua_pushnumber(L, realObject->getPositionY());

	return 1;
}

int LuaSceneObject::getObjectID(lua_State* L) {
	lua_pushinteger(L, realObject->getObjectID());

	return 1;
}

int LuaSceneObject::getParentID(lua_State* L) {
	lua_pushinteger(L, realObject->getParentID());

	return 1;
}

int LuaSceneObject::isInRange(lua_State* L) {
//public boolean isInRange(float x, float y, float range) {
	float range = lua_tonumber(L, -1);
	float y = lua_tonumber(L, -2);
	float x = lua_tonumber(L, -3);

	bool res = (static_cast<QuadTreeEntry*>(realObject))->isInRange(x, y, range);

	lua_pushnumber(L, res);

	return 1;
}

int LuaSceneObject::getGameObjectType(lua_State* L) {
	uint32 type = realObject->getGameObjectType();

	lua_pushnumber(L, type);

	return 1;
}

int LuaSceneObject::getDistanceTo(lua_State* L) {
	SceneObject* obj = (SceneObject*)lua_touserdata(L, -1);

	float res = realObject->getDistanceTo(obj);

	lua_pushnumber(L, res);

	return 1;
}

int LuaSceneObject::getServerObjectCRC(lua_State* L) {
	uint32 crc = realObject->getServerObjectCRC();

	lua_pushnumber(L, crc);

	return 1;
}

int LuaSceneObject::faceObject(lua_State* L) {
	SceneObject* obj = (SceneObject*)lua_touserdata(L, -1);

	realObject->faceObject(obj);

	return 0;
}

int LuaSceneObject::isInRangeWithObject(lua_State* L) {
	float range = lua_tonumber(L, -1);
	SceneObject* obj = (SceneObject*)lua_touserdata(L, -2);

	bool res = realObject->isInRange(obj, range);

	lua_pushnumber(L, res);

	return 1;
}

int LuaSceneObject::getParent(lua_State* L) {
	SceneObject* obj = realObject->getParent();

	if (obj == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, obj);
	}

	return 1;
}

int LuaSceneObject::getContainerObject(lua_State* L) {
	int idx = lua_tonumber(L, -1);

	SceneObject* obj = realObject->getContainerObject(idx);

	lua_pushlightuserdata(L, obj);

	return 1;
}

int LuaSceneObject::getContainerObjectByTemplate(lua_State* L) {
	String objectTemplate = lua_tostring(L, -1);

	uint32 objectCRC = objectTemplate.hashCode();

	SceneObject* sco = NULL;
	SceneObject* inventory = NULL;

	if (realObject->isPlayerCreature()) {
		inventory = realObject->getSlottedObject("inventory");
	} else {
		inventory = realObject;
	}

	if (inventory == NULL) {
		realObject->info("Inventory NULL", true);
		lua_pushnil(L);

		return 1;
	}

	for (int i=0; i< inventory->getContainerObjectsSize(); i++) {
		sco = inventory->getContainerObject(i);

		if (sco == NULL)
			continue;

		if (sco->getContainerObjectsSize() > 0) {
			for (int j=0; j < sco->getContainerObjectsSize(); j++) {
				SceneObject* child = sco->getContainerObject(j);

				if (child == NULL)
					continue;

				if (child->getServerObjectCRC() == objectCRC) {
					lua_pushlightuserdata(L, child);
					return 1;
				}
			}
		}

		if (sco->getServerObjectCRC() == objectCRC) {
			lua_pushlightuserdata(L, sco);
			return 1;
		}
	}

	lua_pushnil(L);

	return 1;
}

int LuaSceneObject::getContainerObjectById(lua_State* L) {
	uint64 objectID = lua_tointeger(L, -1);

	SceneObject* obj = realObject->getContainerObject(objectID);

	if (obj != NULL) {
		lua_pushlightuserdata(L, obj);
	} else {
		lua_pushnil(L);
	}

    return 1;
}

int LuaSceneObject::getSlottedObject(lua_State* L) {
	String slot = lua_tostring(L, -1);

	SceneObject* obj = realObject->getSlottedObject(slot);

	lua_pushlightuserdata(L, obj);

	return 1;
}

int LuaSceneObject::transferObject(lua_State* L) {
	//transferObject(SceneObject object, int containmentType, boolean notifyClient = false);

	bool notifyClient = lua_tonumber(L, -1);
	int containmentType = lua_tonumber(L, -2);
	SceneObject* obj = (SceneObject*) lua_touserdata(L, -3);

	realObject->transferObject(obj, containmentType, notifyClient);

	return 0;
}

/*int LuaSceneObject::removeObject(lua_State* L) {

	//removeObject(SceneObject object, boolean notifyClient = false);

	bool notifyClient = lua_tonumber(L, -1);
	SceneObject* obj = (SceneObject*) lua_touserdata(L, -2);

	realObject->removeObject(obj, notifyClient);

	return 0;
}*/

int LuaSceneObject::getContainerObjectsSize(lua_State* L) {
	int num = realObject->getContainerObjectsSize();

	lua_pushnumber(L, num);

	return 1;
}

int LuaSceneObject::showFlyText(lua_State* L) {
	//final string file, final string uax, byte red, byte green, byte blue

	byte blue = lua_tonumber(L, -1);
	byte green = lua_tonumber(L, -2);
	byte red = lua_tonumber(L, -3);

	String aux = lua_tostring(L, -4);
	String file = lua_tostring(L, -5);

	realObject->showFlyText(file, aux, red, green, blue);

	return 0;
}

int LuaSceneObject::updateDirection(lua_State* L) {
	//void updateDirection(float fw, float fx, float fy, float fz);

	float fz = lua_tonumber(L, -1);
	float fy = lua_tonumber(L, -2);
	float fx = lua_tonumber(L, -3);
	float fw = lua_tonumber(L, -4);

	realObject->updateDirection(fw, fx, fy, fz);

	return 0;
}

int LuaSceneObject::destroyObjectFromWorld(lua_State* L) {
	realObject->destroyObjectFromWorld(true);

	return 0;
}

int LuaSceneObject::isCreatureObject(lua_State* L) {
	bool val = realObject->isCreatureObject();

	lua_pushboolean(L, val);

	return 1;
}

int LuaSceneObject::updateCellPermission(lua_State* L) {
	//realObject->info("getting values",true);
	int allowEntry = lua_tonumber(L, -2);
	CreatureObject* obj = (CreatureObject*)lua_touserdata(L, -1);
	//realObject->info("allowentry:" + String::valueOf(allowEntry), true);
	if (obj == NULL)
		return 0;

	//realObject->info("values not NULL", true);

	if (realObject == NULL) {
		obj->info("Cell NULL", true);
		return 0;
	}


	if (!realObject->isCellObject()) {
		realObject->info("Unknown entity error: Cell", true);
		return 0;
	}

	if (!obj->isCreatureObject()) {
		//realObject->info("Unknown entity error: Creature", true);
		obj->info("Unknown entity error: Creature", true);
		return 0;
	}

	//realObject->info("checks are fine", true);

	BaseMessage* perm = new UpdateCellPermissionsMessage(realObject->getObjectID(), allowEntry);
	obj->sendMessage(perm);

	return 0;
}

int LuaSceneObject::updateCellPermissionGroup(lua_State* L) {
	//realObject->info("getting values",true);
	int allowEntry = lua_tonumber(L, -2);
	CreatureObject* obj = (CreatureObject*)lua_touserdata(L, -1);
	//realObject->info("allowentry:" + String::valueOf(allowEntry), true);
	if (obj == NULL)
		return 0;

	//realObject->info("values not NULL", true);

	if (!realObject->isCellObject()) {
		realObject->info("Unknown entity error: Cell", true);
		return 0;
	}

	if (!obj->isCreatureObject()) {
		//realObject->info("Unknown entity error: Creature", true);
		obj->info("Unknown entity error: Creature", true);
		return 0;
	}

	BaseMessage* perm = new UpdateCellPermissionsMessage(realObject->getObjectID(), allowEntry);

	//realObject->info("checks are fine", true);
	if (obj->isGrouped()) {
		// do group
		GroupObject* group = obj->getGroup();
		if (group != NULL) {
			group->broadcastMessage(perm);
		}
	} else {
		// do single creature
		obj->sendMessage(perm);
	}

	return 0;
}

int LuaSceneObject::wlock(lua_State* L) {
	return 0;
}

int LuaSceneObject::unlock(lua_State* L) {
	return 0;
}

int LuaSceneObject::sendTo(lua_State* L) {
	SceneObject* obj = (SceneObject*) lua_touserdata(L, -1);

	realObject->sendTo(obj, true);

	return 0;
}

int LuaSceneObject::getCustomObjectName(lua_State* L) {
	String objname = realObject->getCustomObjectName().toString();

	lua_pushstring(L, objname);

	return 1;
}

int LuaSceneObject::setDirectionalHeading(lua_State* L) {
	int heading = lua_tointeger(L, -1);

	SceneObject* obj = (SceneObject*) lua_touserdata(L, -2);

	realObject->setDirection(heading);

	return 0;
}
