/*
 * ObjectManager.cpp
 *
 *  Created on: Sep 5, 2009
 *      Author: theanswer
 */

#include "ObjectManager.h"
#include "zone/objects/scene/SceneObject.h"
#include "zone/objects/scene/variables/StringId.h"

#include "zone/objects/player/PlayerCreature.h"
#include "zone/objects/creature/CreatureObject.h"
#include "zone/objects/ObjectMap.h"

ObjectManager::ObjectManager() : Mutex("ObjectManager"), Logger("ObjectManager") {
	luaInstance = new Lua();
	luaInstance->init();

	objectMap = new ObjectMap();

	info("loading object templates...", true);
	registerFunctions();
	luaInstance->runFile("scripts/object/main.lua");

	registerObjectTypes();
}

ObjectManager::~ObjectManager() {
	delete luaInstance;
	luaInstance = NULL;

	delete objectMap;
	objectMap = NULL;
}

void ObjectManager::registerObjectTypes() {
	info("registering object types");
	//objectFactory.registerObject<SceneObject>(0);
	objectFactory.registerObject<CreatureObject>(SceneObject::CREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObject::NPCCREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObject::DROIDCREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObject::PROBOTCREATURE);

	objectFactory.registerObject<PlayerCreature>(SceneObject::PLAYERCREATURE);

	/*objectFactory.registerObject<IntangibleObject>(SceneObject::INTANGIBLE);

	objectFactory.registerObject<ArmorObject>(SceneObject::ARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObject::BODYARMOR); //chest plates

	objectFactory.registerObject<Container>(SceneObject::CONTAINER);
	objectFactory.registerObject<TangibleObject>(SceneObject::GENERICITEM);
	objectFactory.registerObject<TangibleObject>(SceneObject::WEARABLECONTAINER);

	objectFactory.registerObject<CellObject>(SceneObject::CELLOBJECT);
	objectFactory.registerObject<PlayerObject>(SceneObject::PLAYEROBJECT);

	objectFactory.registerObject<WaypointObject>(SceneObject::WAYPOINT);

	objectFactory.registerObject<BuildingObject>(SceneObject::BUILDING);

	objectFactory.registerObject<WeaponObject>(SceneObject::WEAPON);
	objectFactory.registerObject<MeleeWeaponObject>(SceneObject::MELEEWEAPON);

	objectFactory.registerObject<MissionObject>(SceneObject::MISSIONOBJECT);


	objectFactory.registerObject<Terminal>(SceneObject::TERMINAL);
	objectFactory.registerObject<Terminal>(SceneObject::SPACETERMINAL);
	objectFactory.registerObject<Terminal>(SceneObject::SHIPPINGTERMINAL);
	objectFactory.registerObject<Terminal>(SceneObject::INTERACTIVETERMINAL);
	objectFactory.registerObject<StartingLocationTerminal>(SceneObject::NEWBIETUTORIALTERMINAL);


	//temporary
	objectFactory.registerObject<CreatureObject>(SceneObject::HOVERVEHICLE);*/

}


SceneObject* ObjectManager::createObject(uint32 objectCRC, uint64 objectID) {
	Locker _locker(this);

	SceneObject* object = NULL;

	try {
		LuaFunction getTemplate(luaInstance->getLuaState(), "getTemplate", 1);
		getTemplate << objectCRC; // push first argument
		luaInstance->callFunction(&getTemplate);

		LuaObject result(luaInstance->getLuaState());

		if (!result.isValidTable())
			return NULL;

		uint32 gameObjectType = result.getIntField("gameObjectType");

		object = objectFactory.createObject(gameObjectType, &result);

		if (object == NULL)
			return object;

		object->setObjectID(objectID);

		objectMap->put(objectID, object);

	} catch (Exception& e) {
		error("exception caught in SceneObject* ObjectManager::loadObjectFromTemplate(uint32 objectCRC)");
		error(e.getMessage());

		e.printStackTrace();
	} catch (...) {
		error("unreported exception caught in SceneObject* ObjectManager::loadObjectFromTemplate(uint32 objectCRC)");
	}

	return object;
}

SceneObject* ObjectManager::getObject(uint64 objectID) {
	Locker _locker(this);

	return objectMap->get(objectID);
}

SceneObject* ObjectManager::getObject(const UnicodeString& customName) {
	Locker _locker(this);

	HashTableIterator<uint64, SceneObject*> iterator(objectMap);

	while (iterator.hasNext()) {
		SceneObject* object = iterator.next();

		StringId name = object->getObjectName();
		UnicodeString cust = name.getCustomString();

		if (cust.toString() == customName.toString())
			return object;
	}

	return NULL;
}


void ObjectManager::registerFunctions() {
	//lua generic
	lua_register(luaInstance->getLuaState(), "includeFile", includeFile);
}

int ObjectManager::includeFile(lua_State* L) {
	String filename = Lua::getStringParameter(L);

	Lua::runFile("scripts/object/" + filename, L);

	return 0;
}
