/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "ObjectManager.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/intangible/IntangibleObject.h"
#include "server/zone/objects/tangible/Container.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/tangible/weapon/MeleeWeaponObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/building/cloning/CloningBuildingObject.h"
#include "server/zone/objects/building/medical/MedicalBuildingObject.h"
#include "server/zone/objects/building/recreation/RecreationBuildingObject.h"
#include "server/zone/objects/building/travel/TravelBuildingObject.h"
#include "server/zone/objects/building/tutorial/TutorialBuildingObject.h"
#include "server/zone/objects/tangible/wearables/ArmorObject.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/objects/tangible/terminal/startinglocation/StartingLocationTerminal.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/db/ServerDatabase.h"
#include "ObjectMap.h"
#include "server/zone/Zone.h"
#include "server/chat/ChatManager.h"
#include "server/zone/ZoneProcessServerImplementation.h"
#include "server/db/ObjectDatabase.h"

Lua* ObjectManager::luaTemplatesInstance = NULL;

ObjectManager::ObjectManager() : DOBObjectManagerImplementation(), Logger("ObjectManager") {
	server = NULL;

	database = new ObjectDatabase("objects.db");
	staticDatabase = new ObjectDatabase("staticobjects.db");

	registerObjectTypes();

	luaTemplatesInstance = new Lua();
	luaTemplatesInstance->init();

	info("loading object templates...", true);
	registerFunctions();
	luaTemplatesInstance->runFile("scripts/object/main.lua");

	loadLastUsedObjectID();

	setLogging(false);
	setGlobalLogging(true);
}

ObjectManager::~ObjectManager() {
	delete luaTemplatesInstance;
	luaTemplatesInstance = NULL;

	closeDatabases();
}

void ObjectManager::registerObjectTypes() {
	info("registering object types");
	//objectFactory.registerObject<SceneObject>(0);
	objectFactory.registerObject<CreatureObject>(SceneObject::CREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObject::NPCCREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObject::DROIDCREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObject::PROBOTCREATURE);

	objectFactory.registerObject<PlayerCreature>(SceneObject::PLAYERCREATURE);

	objectFactory.registerObject<IntangibleObject>(SceneObject::INTANGIBLE);

	objectFactory.registerObject<ArmorObject>(SceneObject::ARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObject::BODYARMOR); //chest plates

	objectFactory.registerObject<Container>(SceneObject::CONTAINER);
	objectFactory.registerObject<TangibleObject>(SceneObject::GENERICITEM);
	objectFactory.registerObject<TangibleObject>(SceneObject::WEARABLECONTAINER);

	objectFactory.registerObject<CellObject>(SceneObject::CELLOBJECT);
	objectFactory.registerObject<PlayerObject>(SceneObject::PLAYEROBJECT);

	objectFactory.registerObject<WaypointObject>(SceneObject::WAYPOINT);

	objectFactory.registerObject<BuildingObject>(SceneObject::BUILDING);
	objectFactory.registerObject<TutorialBuildingObject>(SceneObject::TUTORIALBUILDING);
	objectFactory.registerObject<CloningBuildingObject>(SceneObject::CLONINGBUILDING);
	objectFactory.registerObject<MedicalBuildingObject>(SceneObject::MEDICALBUILDING);
	objectFactory.registerObject<TravelBuildingObject>(SceneObject::TRAVELBUILDING);
	objectFactory.registerObject<RecreationBuildingObject>(SceneObject::RECREATIONBUILDING);

	objectFactory.registerObject<WeaponObject>(SceneObject::WEAPON);
	objectFactory.registerObject<MeleeWeaponObject>(SceneObject::MELEEWEAPON);

	objectFactory.registerObject<MissionObject>(SceneObject::MISSIONOBJECT);


	objectFactory.registerObject<Terminal>(SceneObject::TERMINAL);
	objectFactory.registerObject<Terminal>(SceneObject::SPACETERMINAL);
	objectFactory.registerObject<Terminal>(SceneObject::SHIPPINGTERMINAL);
	objectFactory.registerObject<Terminal>(SceneObject::INTERACTIVETERMINAL);
	objectFactory.registerObject<StartingLocationTerminal>(SceneObject::NEWBIETUTORIALTERMINAL);


	//temporary
	objectFactory.registerObject<CreatureObject>(SceneObject::HOVERVEHICLE);

}

void ObjectManager::loadLastUsedObjectID() {
	info("loading last used object id");

	ObjectDatabaseIterator iterator(database);
	ObjectDatabaseIterator staticIterator(staticDatabase);

	uint64 maxObjectID = 0;
	uint64 objectID;

	while (iterator.getNextKey(objectID)) {
		if (objectID > maxObjectID)
			maxObjectID = objectID;
	}

	while (staticIterator.getNextKey(objectID)) {
		if (objectID > maxObjectID)
			maxObjectID = objectID;
	}

	if (nextObjectID < maxObjectID + 1)
		nextObjectID = maxObjectID + 1;

	info("done loading last use object id " + String::valueOf(nextObjectID));
}

/*void ObjectManager::savePersistentObjects() {
	Locker _locker(this);

}*/

void ObjectManager::closeDatabases() {
	Locker _locker(this);

	if (database != NULL) {
		database->sync();

		delete database;
		database = NULL;
	}

	if (staticDatabase != NULL) {
		staticDatabase->sync();

		delete staticDatabase;
		staticDatabase = NULL;
	}
}


DistributedObjectStub* ObjectManager::loadPersistentObject(uint64 objectID) {
	DistributedObjectStub* object = NULL;

	Locker _locker(this);

	bool permanant = false;

	// only for debugging proposes
	DistributedObject* dobject = getObject(objectID);

	if (dobject != NULL && dobject->_getObjectID() != objectID) {
		error("different object already in database");

		return NULL;
	}

	ObjectInputStream* objectData = new ObjectInputStream(500);

	if (database->getData(objectID, objectData)) {
		//Not found in regular database, let's check static
		if (staticDatabase->getData(objectID, objectData)) {
			//Not found in static database either.
			delete objectData;
			return NULL;
		} else {
			permanant = true;
		}
	}

	uint32 serverObjectCRC = 0;
	String className;

	if (Serializable::getVariable<uint32>("serverObjectCRC", &serverObjectCRC, objectData)) {
		object = createObject(serverObjectCRC, false, permanant, objectID);

		if (object == NULL) {
			error("could not load object from database");
			delete objectData;
			return NULL;
		}

		deSerializeObject((SceneObject*)object, objectData);

		((SceneObject*)object)->info("loaded from db");

	} else if (Serializable::getVariable<String>("_className", &className, objectData)) {
		object = createObject(className, false, permanant, objectID);

		if (object == NULL) {
			error("could not load object from database");
			delete objectData;
			return NULL;
		}

		deSerializeObject((ManagedObject*)object, objectData);
	} else {
		error("could not load object from database, unknown template crc or class name");
		object = NULL;
	}

	delete objectData;

	return object;
}

ManagedObject* ObjectManager::createObject(const String& className, bool persistent, bool permanent, uint64 oid) {
	ManagedObject* object = NULL;

	Locker _locker(this);

	DistributedObjectClassHelperMap* classMap = DistributedObjectBroker::instance()->getClassMap();

	DistributedObjectClassHelper* helper = classMap->get(className);

	if (helper != NULL) {
		object = (ManagedObject*) helper->instantiateObject();
		DistributedObjectServant* servant = helper->instantiateServant();

		if (oid == 0)
			oid = getNextFreeObjectID();

		object->_setObjectID(oid);
		object->_setImplementation(servant);

		servant->_setStub(object);
		servant->_setClassHelper(helper);
		servant->_serializationHelperMethod();

		object->deploy();

		if (persistent) {
			updatePersistentObject(object, permanent);

			object->queueUpdateToDatabaseTask();

			object->setPersistent();

			/*//TODO: Uncomment once permanent flags are moved to ManagedObject
			if (permanent)
				object->setPermanent();
			*/
		}

	} else {
		error("unknown className:" + className + " in classMap");
	}

	return object;
}

void ObjectManager::deSerializeObject(ManagedObject* object, ObjectInputStream* data) {
	try {
		object->wlock();

		object->setPersistent();
		object->readObject(data);

		object->queueUpdateToDatabaseTask();

		object->unlock();
	} catch (Exception& e) {
		object->unlock();
		error("could not deserialize object from DB");
	} catch (...) {
		object->unlock();
		error("could not deserialize object from DB");
	}
}

void ObjectManager::deSerializeObject(SceneObject* object, ObjectInputStream* data) {
	try {
		object->wlock();

		object->setPersistent();
		object->readObject(data);

		Zone* zone = object->getZone();

		if (zone != NULL)
			object->insertToZone(zone);

		object->queueUpdateToDatabaseTask();

		object->unlock();
	} catch (Exception& e) {
		object->unlock();
		error("could not deserialize object from DB");
	} catch (...) {
		object->unlock();
		error("could not deserialize object from DB");
	}

	if (object->isPlayerCreature())
		server->getZoneServer()->getChatManager()->addPlayer((PlayerCreature*) object);
}

SceneObject* ObjectManager::loadObjectFromTemplate(uint32 objectCRC) {
	SceneObject* object = NULL;

	try {
		LuaFunction getTemplate(luaTemplatesInstance->getLuaState(), "getTemplate", 1);
		getTemplate << objectCRC; // push first argument
		luaTemplatesInstance->callFunction(&getTemplate);

		LuaObject result(luaTemplatesInstance->getLuaState());

		if (!result.isValidTable())
			return NULL;

		uint32 gameObjectType = result.getIntField("gameObjectType");

		object = objectFactory.createObject(gameObjectType, &result);
		object->setServerObjectCRC(objectCRC);

	} catch (Exception& e) {
		error("exception caught in SceneObject* ObjectManager::loadObjectFromTemplate(uint32 objectCRC)");
		error(e.getMessage());

		e.printStackTrace();
	} catch (...) {
		error("unreported exception caught in SceneObject* ObjectManager::loadObjectFromTemplate(uint32 objectCRC)");
	}

	return object;
}

int ObjectManager::updatePersistentObject(DistributedObject* object, bool permanent) {
	if (database == NULL)
		return 0;

	try {
		ObjectOutputStream* objectData = new ObjectOutputStream(500);

		((ManagedObject*)object)->writeObject(objectData);

		if(permanent)
			staticDatabase->putData(object->_getObjectID(), objectData);
		else
			database->putData(object->_getObjectID(), objectData);

		delete objectData;

		/*objectData.escapeString();

		StringBuffer query;
		query << "UPDATE objects SET data = '" << objectData << "' WHERE objectid = " << object->_getObjectID() << ";";
		ServerDatabase::instance()->executeStatement(query);*/
	} catch (...) {
		error("unreported exception caught in ObjectManager::updateToDatabase(SceneObject* object)");
	}

	return 1;
}

SceneObject* ObjectManager::createObject(uint32 objectCRC, bool persistent, bool permanent, uint64 oid) {
	SceneObject* object = NULL;

	Locker _locker(this);

	object = loadObjectFromTemplate(objectCRC);

	if (object == NULL) {
		return NULL;
	}

	object->setZoneProcessServer(server);

	if (persistent)
		object->setPersistent();

	if (permanent)
		object->setPermanent();

	if (oid == 0)
		oid = getNextFreeObjectID();

	object->_setObjectID(oid);

	String logName = object->getLoggingName();

	StringBuffer newLogName;
	newLogName << logName << " 0x" << hex << oid;

	object->setLoggingName(newLogName.toString());

	object->deploy(newLogName.toString());

	if (persistent) {
		updatePersistentObject(object, permanent);

		object->queueUpdateToDatabaseTask();
	}

	return object;
}

int ObjectManager::destroyObject(uint64 objectID) {
	Locker _locker(this);

	/*try {
		ManagedReference<SceneObject*> object = remove(objectID);

		if (object == NULL) {
			return;
		}

		if (object->isPlayerCreature()) {
			return;
		}

		ManagedReference<SceneObject*> parent = object->getParent();

		if (parent != NULL)
			error("warning trying to destroy object with parent");

		object->finalize();

		// remove from db

	} catch (...) {
		error("unreported exception caught in void ObjectManager::destroyObject(uint64 objectID)");
	}*/

	return 1;
}

void ObjectManager::registerFunctions() {
	//lua generic
	lua_register(luaTemplatesInstance->getLuaState(), "includeFile", includeFile);
}

int ObjectManager::includeFile(lua_State* L) {
	String filename = Lua::getStringParameter(L);

	Lua::runFile("scripts/object/" + filename, L);

	return 0;
}
