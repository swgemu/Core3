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
#include "server/zone/Zone.h"
#include "server/zone/objects/area/ActiveArea.h"

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
		{ "setCustomObjectName", &LuaSceneObject::setCustomObjectName},
		{ "getDistanceTo", &LuaSceneObject::getDistanceTo },
		{ "updateDirection", &LuaSceneObject::updateDirection },
		{ "getServerObjectCRC", &LuaSceneObject::getServerObjectCRC },
		{ "showFlyText", &LuaSceneObject::showFlyText },
		{ "getContainerObject", &LuaSceneObject::getContainerObject },
		{ "hasFullContainerObjects", &LuaSceneObject::hasFullContainerObjects },
		{ "getContainerObjectsSize", &LuaSceneObject::getContainerObjectsSize },
		{ "getSlottedObject", &LuaSceneObject::getSlottedObject },
		{ "transferObject", &LuaSceneObject::transferObject },
//		{ "removeObject", &LuaSceneObject::removeObject },
		{ "getGameObjectType", &LuaSceneObject::getGameObjectType },
		{ "faceObject", &LuaSceneObject::faceObject },
		{ "destroyObjectFromWorld", &LuaSceneObject::destroyObjectFromWorld },
		{ "destroyObjectFromDatabase", &LuaSceneObject::destroyObjectFromDatabase },
		{ "isCreatureObject", &LuaSceneObject::isCreatureObject },
		{ "isPlayerCreature", &LuaSceneObject::isPlayerCreature },
		{ "sendTo", &LuaSceneObject::sendTo },
		{ "getCustomObjectName", &LuaSceneObject::getCustomObjectName },
		{ "getContainerObjectById", &LuaSceneObject::getContainerObjectById },
		{ "setDirectionalHeading", &LuaSceneObject::setDirectionalHeading },
		{ "getZoneName", &LuaSceneObject::getZoneName },
		{ "getTemplateObjectPath", &LuaSceneObject::getTemplateObjectPath },
		{ "teleport", &LuaSceneObject::teleport },
		{ "setObjectMenuComponent", &LuaSceneObject::setObjectMenuComponent },
		{ "setContainerComponent", &LuaSceneObject::setContainerComponent },
		{ "switchZone", &LuaSceneObject::switchZone },
		{ "setContainerInheritPermissionsFromParent", &LuaSceneObject::setContainerInheritPermissionsFromParent},
		{ "setContainerAllowPermission", &LuaSceneObject::setContainerAllowPermission},
		{ "setContainerDenyPermission", &LuaSceneObject::setContainerDenyPermission},
		{ "setContainerDefaultAllowPermission", &LuaSceneObject::setContainerDefaultAllowPermission},
		{ "clearContainerDefaultAllowPermission", &LuaSceneObject::clearContainerDefaultAllowPermission},
		{ "setContainerDefaultDenyPermission", &LuaSceneObject::setContainerDefaultDenyPermission},
		{ "clearContainerDefaultDenyPermission", &LuaSceneObject::clearContainerDefaultDenyPermission},
		{ "hasActiveArea", &LuaSceneObject::hasActiveArea},
		{ "setObjectName", &LuaSceneObject::setObjectName},
		{ "isASubChildOf", &LuaSceneObject::isASubChildOf},
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

int LuaSceneObject::setObjectMenuComponent(lua_State* L) {
	String value = lua_tostring(L, -1);

	realObject->setObjectMenuComponent(value);

	return 0;
}

int LuaSceneObject::setContainerComponent(lua_State* L) {
	String value = lua_tostring(L, -1);

	realObject->setContainerComponent(value);

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
	if (realObject != NULL) {
		String tempPath = realObject->getObjectTemplate()->getFullTemplateString();

		lua_pushstring(L, tempPath);
	} else {
		lua_pushstring(L, "");
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

int LuaSceneObject::hasActiveArea(lua_State* L) {
	uint64 objectid = lua_tointeger(L, -1);

	bool res = realObject->hasActiveArea(objectid);

	lua_pushboolean(L, res);

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
	SceneObject* obj = realObject->getParent().get().get();

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

	if (obj == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, obj);
	}

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
	if (obj == NULL) {
		lua_pushnil(L);
	} else {
		lua_pushlightuserdata(L, obj);
	}

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

int LuaSceneObject::hasFullContainerObjects(lua_State* L) {
	bool full = realObject->hasFullContainerObjects();

	lua_pushboolean(L, full);

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

int LuaSceneObject::destroyObjectFromDatabase(lua_State* L) {
	realObject->destroyObjectFromDatabase(true);

	return 0;
}

int LuaSceneObject::isCreatureObject(lua_State* L) {
	bool val = realObject->isCreatureObject();

	lua_pushboolean(L, val);

	return 1;
}

int LuaSceneObject::isPlayerCreature(lua_State* L) {
	bool val = realObject->isPlayerCreature();

	lua_pushboolean(L, val);

	return 1;
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

int LuaSceneObject::setContainerInheritPermissionsFromParent(lua_State* L) {
	bool val = lua_toboolean(L, -1);

	realObject->setContainerInheritPermissionsFromParent(val);

	return 0;
}

int LuaSceneObject::setContainerAllowPermission(lua_State* L) {
	String group = lua_tostring(L, -2);
	uint16 perm = lua_tointeger(L, -1);

	realObject->setContainerAllowPermission(group, perm);

	return 0;
}

int LuaSceneObject::setContainerDenyPermission(lua_State* L) {
	String group = lua_tostring(L, -2);
	uint16 perm = lua_tointeger(L, -1);

	realObject->setContainerDenyPermission(group, perm);

	return 0;
}

int LuaSceneObject::setContainerDefaultAllowPermission(lua_State* L) {
	uint16 perm = lua_tointeger(L, -1);

	realObject->setContainerDefaultAllowPermission(perm);

	return 0;
}

int LuaSceneObject::clearContainerDefaultAllowPermission(lua_State* L) {
	uint16 perm = lua_tointeger(L, -1);

	realObject->clearContainerDefaultAllowPermission(perm);

	return 0;
}

int LuaSceneObject::setContainerDefaultDenyPermission(lua_State* L) {
	uint16 perm = lua_tointeger(L, -1);

	realObject->setContainerDefaultDenyPermission(perm);

	return 0;
}

int LuaSceneObject::clearContainerDefaultDenyPermission(lua_State* L) {
	uint16 perm = lua_tointeger(L, -1);

	realObject->clearContainerDefaultDenyPermission(perm);

	return 0;
}

int LuaSceneObject::setObjectName(lua_State* L) {
	String file = lua_tostring(L, -2);
	String key = lua_tostring(L, -1);

	StringId stringid(file, key);

	realObject->setObjectName(stringid);

	return 0;
}

int LuaSceneObject::isASubChildOf(lua_State* L) {
	SceneObject* obj = lua_touserdata(L, -1);

	lua_pushboolean(L, realObject->isASubChildOf(obj));

	return 1;
}
