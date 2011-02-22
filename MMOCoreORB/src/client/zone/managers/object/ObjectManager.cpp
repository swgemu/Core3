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
#include "zone/objects/player/PlayerObject.h"
#include "zone/objects/creature/CreatureObject.h"
#include "zone/objects/ObjectMap.h"

#include "zone/Zone.h"

ObjectFactory<SceneObject* (LuaObject*), uint32> ObjectManager::objectFactory;
Lua* ObjectManager::luaInstance = NULL;
Mutex ObjectManager::luaMutex;

ObjectManager::ObjectManager() : Mutex("ObjectManager"), Logger("ObjectManager") {
	luaMutex.lock();

	if (luaInstance == NULL) {
		luaInstance = new Lua();
		luaInstance->init();

		info("loading object templates...", true);
		registerFunctions();
		luaInstance->runFile("scripts/object/clientmain.lua");

		registerObjectTypes();
	}

	luaMutex.unlock();

	objectMap = new ObjectMap();

	zone = NULL;
}

ObjectManager::~ObjectManager() {
	/*delete luaInstance;
	luaInstance = NULL;*/

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
	objectFactory.registerObject<PlayerObject>(SceneObject::PLAYEROBJECT);

	objectFactory.registerObject<TangibleObject>(SceneObject::GENERICITEM);
	objectFactory.registerObject<TangibleObject>(SceneObject::WEARABLECONTAINER);

	objectFactory.registerObject<TangibleObject>(SceneObject::ARMOR);
	objectFactory.registerObject<TangibleObject>(SceneObject::BODYARMOR); //chest plates

	objectFactory.registerObject<TangibleObject>(SceneObject::CONTAINER); //chest plates



	/*objectFactory.registerObject<IntangibleObject>(SceneObject::INTANGIBLE);


	objectFactory.registerObject<Container>(SceneObject::CONTAINER);

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
		luaMutex.lock();

		LuaFunction getTemplate(luaInstance->getLuaState(), "getTemplate", 1);
		getTemplate << objectCRC; // push first argument
		luaInstance->callFunction(&getTemplate);

		LuaObject result(luaInstance->getLuaState());

		if (!result.isValidTable()) {
			luaMutex.unlock();
			return NULL;
		}

		uint32 gameObjectType = result.getIntField("gameObjectType");

		object = objectFactory.createObject(gameObjectType, &result);

		luaMutex.unlock();

		if (object == NULL)
			return object;

		object->setObjectID(objectID);
		object->setZone(zone);

		StringBuffer logName;
		logName << object->getLoggingName() << " 0x" << hex << objectID;
		object->setLoggingName(logName.toString());

		objectMap->put(objectID, object);

	} catch (Exception& e) {
		error("exception caught in SceneObject* ObjectManager::loadObjectFromTemplate(uint32 objectCRC)");
		error(e.getMessage());

		e.printStackTrace();
	} catch (...) {
		error("unreported exception caught in SceneObject* ObjectManager::loadObjectFromTemplate(uint32 objectCRC)");

		throw;
	}

	return object;
}

SceneObject* ObjectManager::getObject(uint64 objectID) {
	Locker _locker(this);

	return objectMap->get(objectID);
}

SceneObject* ObjectManager::getObject(const UnicodeString& customName) {
	Locker _locker(this);

	HashTableIterator<uint64, Reference<SceneObject*> > iterator(objectMap);

	while (iterator.hasNext()) {
		SceneObject* object = iterator.next();

		StringId name = object->getObjectName();
		UnicodeString cust = name.getCustomString();

		if (cust.toString() == customName.toString())
			return object;
	}

	return NULL;
}

void ObjectManager::destroyObject(uint64 objectID) {
	Locker _locker(this);

	Reference<SceneObject*> object = objectMap->remove(objectID);

	if (object != NULL) {
		object->info("finalizing object");

		while (object->getSlottedObjectsSize() > 0) {
			Reference<SceneObject*> obj = object->getSlottedObject(0);

			object->removeObject(obj);

			destroyObject(obj->getObjectID());
		}

		while (object->getContainerObjectsSize() > 0) {
			Reference<SceneObject*> obj = object->getContainerObject(0);

			object->removeObject(obj);

			destroyObject(obj->getObjectID());
		}

		//object->finalize();
	}
}

uint32 ObjectManager::getObjectMapSize() {
	Locker _locker(this);

	return objectMap->size();
}


void ObjectManager::registerFunctions() {
	//lua generic
	lua_register(luaInstance->getLuaState(), "includeFile", includeFile);
	lua_register(luaInstance->getLuaState(), "crcString", crcString);
	lua_register(luaInstance->getLuaState(), "addTemplateCRC", addTemplateCRC);
}

int ObjectManager::includeFile(lua_State* L) {
	String filename = Lua::getStringParameter(L);

	Lua::runFile("scripts/object/" + filename, L);

	return 0;
}

int ObjectManager::crcString(lua_State* L) {
	String ascii = Lua::getStringParameter(L);

	uint32 crc = ascii.hashCode();

	lua_pushnumber(L, crc);

	return 1;
}

int ObjectManager::addTemplateCRC(lua_State* L) {
	/*String ascii =  lua_tostring(L, -2);
	uint32 value = (uint32) lua_tonumber(L, -1);

	uint32 crc = (uint32) ascii.hashCode();

	TemplateManager::instance()->addTemplate(crc, ascii);*/

	return 0;
}
