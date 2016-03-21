/*
 * ObjectManager.cpp
 *
 *  Created on: Sep 5, 2009
 *      Author: theanswer
 */

#include "ObjectManager.h"
#include "client/zone/objects/scene/SceneObject.h"
#include "client/zone/objects/scene/variables/StringId.h"
#include "client/zone/objects/building/ClientBuilding.h"
#include "client/zone/objects/player/PlayerCreature.h"
#include "client/zone/objects/player/PlayerObject.h"
#include "client/zone/objects/creature/CreatureObject.h"
#include "client/zone/objects/ObjectMap.h"
#include "templates/manager/TemplateManager.h"
#include "client/zone/Zone.h"

ObjectFactory<SceneObject* (SharedObjectTemplate*), uint32> ObjectManager::objectFactory;
Lua* ObjectManager::luaInstance = NULL;
Mutex ObjectManager::luaMutex;

ObjectManager::ObjectManager() : Mutex("ObjectManager"), Logger("ObjectManager") {
	//luaMutex.lock();
//
//	if (luaInstance == NULL) {
//		luaInstance = new Lua();
//		luaInstance->init();
//
//		info("loading object templates...");
//		registerFunctions();
//		luaInstance->runFile("scripts/object/clientmain.lua");
//
//		registerObjectTypes();
//	}
	
	//TemplateManager::instance()->loadLuaTemplates();;

	//luaMutex.unlock();
	
	registerObjectTypes();

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
	objectFactory.registerObject<SceneObject>(0x5);
	
	objectFactory.registerObject<ClientBuilding>(0x200);
	objectFactory.registerObject<ClientBuilding>(0x201);
	objectFactory.registerObject<ClientBuilding>(0x202);
	objectFactory.registerObject<ClientBuilding>(0x203);
	
	
	objectFactory.registerObject<SceneObject>(0);
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
	objectFactory.registerObject<TangibleObject>(0x2006);
	objectFactory.registerObject<TangibleObject>(0x200f);
	objectFactory.registerObject<SceneObject>(0x2009);
	objectFactory.registerObject<TangibleObject>(0x4001);
	objectFactory.registerObject<TangibleObject>(0x4002);
	objectFactory.registerObject<TangibleObject>(0x4003);
	objectFactory.registerObject<TangibleObject>(0x4004);
	objectFactory.registerObject<TangibleObject>(0x4005); //terminal
	
	objectFactory.registerObject<TangibleObject>(0x4006); //terminal
	objectFactory.registerObject<TangibleObject>(0x6); //terminal
	objectFactory.registerObject<TangibleObject>(0x200a); //terminal
	objectFactory.registerObject<TangibleObject>(0x200b); //terminal
	objectFactory.registerObject<TangibleObject>(0x200c); //terminal
	
	
	
	
	


	objectFactory.registerObject<IntangibleObject>(SceneObject::INTANGIBLE);


	objectFactory.registerObject<SceneObject>(SceneObject::CONTAINER);

	objectFactory.registerObject<SceneObject>(SceneObject::CELLOBJECT);
	objectFactory.registerObject<SceneObject>(SceneObject::PLAYEROBJECT);

	objectFactory.registerObject<SceneObject>(SceneObject::WAYPOINT);

	objectFactory.registerObject<ClientBuilding>(SceneObject::BUILDING);

	objectFactory.registerObject<SceneObject>(SceneObject::WEAPON);
	objectFactory.registerObject<SceneObject>(SceneObject::MELEEWEAPON);

	objectFactory.registerObject<SceneObject>(SceneObject::MISSIONOBJECT);


	objectFactory.registerObject<SceneObject>(SceneObject::TERMINAL);
	objectFactory.registerObject<SceneObject>(SceneObject::SPACETERMINAL);
	objectFactory.registerObject<SceneObject>(SceneObject::SHIPPINGTERMINAL);
	objectFactory.registerObject<SceneObject>(SceneObject::INTERACTIVETERMINAL);
	objectFactory.registerObject<SceneObject>(SceneObject::NEWBIETUTORIALTERMINAL);

	//temporary
	objectFactory.registerObject<CreatureObject>(SceneObject::HOVERVEHICLE);

}


SceneObject* ObjectManager::createObject(uint32 objectCRC, uint64 objectID) {
	Locker _locker(this);
	SharedObjectTemplate *shot = TemplateManager::instance()->getTemplate(objectCRC);
	if (shot == NULL)
		return NULL;
	SceneObject *obj = objectFactory.createObject(shot->getClientGameObjectType(), shot);
	if (obj == NULL) {
		error("Unknown GOT: " + String::hexvalueOf((int64)shot->getGameObjectType()));
		return NULL;
	}
	obj->setObjectID(objectID);
	obj->setZone(zone);
	objectMap->put(objectID, obj);
	//object = objectFactory.createObject(shot->getGameObjectType(),
//	return NULL;
//	try {
//		luaMutex.lock();
//
//		LuaFunction getTemplate(luaInstance->getLuaState(), "getTemplate", 1);
//		getTemplate << objectCRC; // push first argument
//		getTemplate.callFunction();
//
//		LuaObject result(luaInstance->getLuaState());
//
//		if (!result.isValidTable()) {
//			luaMutex.unlock();
//			return NULL;
//		}
//
//		uint32 gameObjectType = result.getIntField("gameObjectType");
//
//		object = objectFactory.createObject(gameObjectType, &result);
//
//		luaMutex.unlock();
//
//		if (object == NULL)
//			return object;
//
//		object->setObjectID(objectID);
//		object->setZone(zone);
//
//		StringBuffer logName;
//		logName << object->getLoggingName() << " 0x" << hex << objectID;
//		object->setLoggingName(logName.toString());
//
//		objectMap->put(objectID, object);
//
//	} catch (Exception& e) {
//		error("exception caught in SceneObject* ObjectManager::loadObjectFromTemplate(uint32 objectCRC)");
//		error(e.getMessage());
//
//		e.printStackTrace();
//	}

	return obj;
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
//	//lua generic
//	lua_register(luaInstance->getLuaState(), "includeFile", includeFile);
//	lua_register(luaInstance->getLuaState(), "crcString", crcString);
//	lua_register(luaInstance->getLuaState(), "addTemplateCRC", addTemplateCRC);
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

//int ObjectManager::addTemplateCRC(lua_State* L) {
//	String ascii =  lua_tostring(L, -2);
//	
//	LuaObject obj(L);
//	
//	uint32 crc = (uint32) ascii.hashCode();
//	
//	TemplateManager::instance()->addTemplate(crc, ascii, &obj);
//	
//	//	uint64 seconds = Logger::getElapsedTime();
//	
//	int val = loadedTemplatesCount.increment();
//	
//	if (ConfigManager::instance()->isProgressMonitorActivated()) {
//		if (val % 159 == 0)
//			printf("\r\tLoading templates: [%d%%]\t", (int) (float(val) / 15998.f * 100.f));
//	}
//	
//	//System::out << str;
//	
//	return 0;
//}
