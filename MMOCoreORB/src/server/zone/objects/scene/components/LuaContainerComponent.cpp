/*
 * LuaContainerComponent.cpp
 *
 *  Created on: 05/02/2012
 *      Author: Elvaron
 */

#include "LuaContainerComponent.h"

#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/objects/scene/TransferErrorCode.h"

LuaContainerComponent::LuaContainerComponent(String className) {
	luaClassName = className;
}

LuaContainerComponent::~LuaContainerComponent(){
}

int LuaContainerComponent::canAddObject(SceneObject* sceneObject, SceneObject* object, int containmentType, String& errorDescription) {
	if (sceneObject == object) {
		errorDescription = "@container_error_message:container02"; //You cannot add something to itself.

		return TransferErrorCode::CANTADDTOITSELF;
	}

	Lua* lua = DirectorManager::instance()->getLuaInstance();

	LuaFunction runMethod(lua->getLuaState(), luaClassName, "canAddObject", 1);
	runMethod << sceneObject;
	runMethod << object;
	runMethod << containmentType;

	lua->callFunction(&runMethod);

	int result = lua_tointeger(lua->getLuaState(), -1);

	lua_pop(lua->getLuaState(), 1);

	if (result == -1)
		result = ContainerComponent::canAddObject(sceneObject, object, containmentType, errorDescription);

	return result;
}

bool LuaContainerComponent::transferObject(SceneObject* sceneObject, SceneObject* object, int containmentType, bool notifyClient) {
	if (sceneObject == object)
		return false;

	Lua* lua = DirectorManager::instance()->getLuaInstance();

	LuaFunction runMethod(lua->getLuaState(), luaClassName, "transferObject", 1);
	runMethod << sceneObject;
	runMethod << object;
	runMethod << containmentType;

	lua->callFunction(&runMethod);

	int result = lua_tointeger(lua->getLuaState(), -1);

	lua_pop(lua->getLuaState(), 1);

	if (result == -1)
		result = ContainerComponent::transferObject(sceneObject, object, containmentType, notifyClient);

	return result;
}

bool LuaContainerComponent::removeObject(SceneObject* sceneObject, SceneObject* object, SceneObject* destination, bool notifyClient) {
	if (sceneObject == object)
		return false;

	Lua* lua = DirectorManager::instance()->getLuaInstance();

	LuaFunction runMethod(lua->getLuaState(), luaClassName, "removeObject", 1);
	runMethod << sceneObject;
	runMethod << object;
	runMethod << destination;

	lua->callFunction(&runMethod);

	int result = lua_tointeger(lua->getLuaState(), -1);

	lua_pop(lua->getLuaState(), 1);

	if (result == -1)
		result = ContainerComponent::removeObject(sceneObject, object, destination, notifyClient);

	return result;
}

/**
 * Is called when this object has been inserted with an object
 * @param object object that has been inserted
 */
int LuaContainerComponent::notifyObjectInserted(SceneObject* sceneObject, SceneObject* object) {
	return ContainerComponent::notifyObjectInserted(sceneObject, object);
}

/**
 * Is called when an object was removed
 * @param object object that has been inserted
 */
int LuaContainerComponent::notifyObjectRemoved(SceneObject* sceneObject, SceneObject* object, SceneObject* destination) {
	return ContainerComponent::notifyObjectRemoved(sceneObject, object, destination);
}
