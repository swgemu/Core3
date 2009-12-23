/*
 * ObjectManager.cpp
 *
 *  Created on: 13/11/2009
 *      Author: victor
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
#include "server/db/ObjectDatabaseEnvironment.h"

//#define NULLHIGH 0x0000FFFFFFFFFFFF;

Lua* ObjectManager::luaTemplatesInstance = NULL;

ObjectManager::ObjectManager() : DOBObjectManagerImplementation(), Logger("ObjectManager") {
	server = NULL;

	databaseEnvironment = ObjectDatabaseEnvironment::instance();

	registerObjectTypes();

	luaTemplatesInstance = new Lua();
	luaTemplatesInstance->init();

	info("loading object templates...", true);
	registerFunctions();
	luaTemplatesInstance->runFile("scripts/object/main.lua");

	databaseEnvironment->loadDatabase("staticobjects", true, 0);

	loadLastUsedObjectID();

	setLogging(false);
	setGlobalLogging(true);
}

ObjectManager::~ObjectManager() {
	info("closing databases...", true);

	ObjectDatabaseEnvironment::instance()->finalize();

	delete luaTemplatesInstance;
	luaTemplatesInstance = NULL;
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

	uint64 maxObjectID = 0;
	uint64 objectID;

	uint64 nullify = 0x0000FFFF;
	nullify = (nullify << 32) + 0xFFFFFFFF;

	for (int i = 0; i < databaseEnvironment->getDatabaseCount(); ++i) {
		ObjectDatabase* db = databaseEnvironment->getDatabase(i);

		ObjectDatabaseIterator iterator(db);

		while (iterator.getNextKey(objectID)) {
			objectID = objectID & nullify;

			if (objectID > maxObjectID)
				maxObjectID = objectID;
		}
	}

	if (nextObjectID < maxObjectID + 1)
		nextObjectID = maxObjectID + 1;

	info("done loading last use object id " + String::valueOf(nextObjectID));
}

void ObjectManager::loadStaticObjects() {
	Locker _locker(this);

	info("loading static objects...", true);

	ObjectDatabase* staticDatabase = databaseEnvironment->loadDatabase("staticobjects", true, 0);

	ObjectDatabaseIterator iterator(staticDatabase);

	uint32 serverObjectCRC;
	uint64 objectID;

	ObjectInputStream objectData(2000);

	while (iterator.getNextKeyAndValue(objectID, &objectData)) {
		SceneObject* object = (SceneObject*) getObject(objectID);

		if (object != NULL)
			continue;

		if (!Serializable::getVariable<uint32>("serverObjectCRC", &serverObjectCRC, &objectData)) {
			error("unknown scene object in static database");
			continue;
		}

		if (object == NULL) {
			object = createObject(serverObjectCRC, 0, "staticobjects", objectID);

			if (object == NULL) {
				error("could not load object from static database");

				continue;
			}

			deSerializeObject(object, &objectData);

			objectData.reset();
		}
	}
}

int ObjectManager::updatePersistentObject(DistributedObject* object) {
	try {
		ObjectOutputStream* objectData = new ObjectOutputStream(500);

		((ManagedObject*)object)->writeObject(objectData);

		uint64 oid = object->_getObjectID();

		ObjectDatabase* database = getTable(oid);

		if (database != NULL) {
			StringBuffer msg;
			String dbName;

			database->getDatabaseName(dbName);

			msg << "saving to database with table " << dbName << " and object id 0x" << oid;
			info(msg.toString(), true);

			database->putData(oid, objectData);

			delete objectData;
		} else {
			StringBuffer err;
			err << "unknown database id of objectID 0x" << hex << oid;
			error(err.toString());
		}

		/*objectData.escapeString();

		StringBuffer query;
		query << "UPDATE objects SET data = '" << objectData << "' WHERE objectid = " << object->_getObjectID() << ";";
		ServerDatabase::instance()->executeStatement(query);*/
	} catch (...) {
		error("unreported exception caught in ObjectManager::updateToDatabase(SceneObject* object)");
	}

	return 1;
}

SceneObject* ObjectManager::loadObjectFromTemplate(uint32 objectCRC) {
	Locker _locker(this);

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

DistributedObjectStub* ObjectManager::loadPersistentObject(uint64 objectID) {
	DistributedObjectStub* object = NULL;

	Locker _locker(this);

	uint16 tableID = (uint16)(objectID >> 48);

	/*StringBuffer infoMsg;
	infoMsg << "trying to get database with table id 0x" << hex << tableID << " with obejct id 0x" << hex << objectID;
	info(infoMsg.toString(), true);*/

	ObjectDatabase* database = databaseEnvironment->getDatabase(tableID);

	// only for debugging proposes
	/*DistributedObject* dobject = getObject(objectID);

	if (dobject != NULL && dobject->_getObjectID() != objectID) {
		error("different object already in database");

		return NULL;
	}*/

	ObjectInputStream objectData(500);

	if (database->getData(objectID, &objectData)) {
		return NULL;
	}

	uint32 serverObjectCRC = 0;
	String className;

	if (Serializable::getVariable<uint32>("serverObjectCRC", &serverObjectCRC, &objectData)) {
		object = instantiateSceneObject(serverObjectCRC, objectID);

		if (object == NULL) {
			error("could not load object from database");
			return NULL;
		}

		deSerializeObject((SceneObject*)object, &objectData);

		((SceneObject*)object)->info("loaded from db");

	} else if (Serializable::getVariable<String>("_className", &className, &objectData)) {
		object = createObject(className, false, "", objectID);

		if (object == NULL) {
			error("could not load object from database");
			return NULL;
		}

		deSerializeObject((ManagedObject*)object, &objectData);
	} else {
		error("could not load object from database, unknown template crc or class name");
	}


	return object;
}


void ObjectManager::deSerializeObject(ManagedObject* object, ObjectInputStream* data) {
	try {
		object->wlock();

		object->readObject(data);

		if (object->isPersistent())
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

		object->readObject(data);

		Zone* zone = object->getZone();

		if (zone != NULL)
			object->insertToZone(zone);

		if (object->isPersistent())
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

SceneObject* ObjectManager::instantiateSceneObject(uint32 objectCRC, uint64 oid) {
	SceneObject* object = NULL;

	Locker _locker(this);

	object = loadObjectFromTemplate(objectCRC);

	if (object == NULL)
		return NULL;

	object->setZoneProcessServer(server);

	object->_setObjectID(oid);

	String logName = object->getLoggingName();

	StringBuffer newLogName;
	newLogName << logName << " 0x" << hex << oid;

	object->setLoggingName(newLogName.toString());

	object->deploy(newLogName.toString());
	info("deploying.." + newLogName.toString());

	return object;
}

SceneObject* ObjectManager::createObject(uint32 objectCRC, int persistenceLevel, const String& database, uint64 oid) {
	SceneObject* object = NULL;

	loadTable(database, oid);

	if (oid == 0) {
		if (database != "staticobjects")
			oid = getNextObjectID(database);
		else
			oid = getNextFreeObjectID();
	}

	object = instantiateSceneObject(objectCRC, oid);

	if (object == NULL) {
		error("could not create object CRC = " + String::valueOf(objectCRC));
		return NULL;
	}

	if (persistenceLevel > 0) {
		object->setPersistent(persistenceLevel);

		updatePersistentObject(object);

		object->queueUpdateToDatabaseTask();
	}

	return object;
}


ManagedObject* ObjectManager::createObject(const String& className, int persistenceLevel, const String& database, uint64 oid) {
	ManagedObject* object = NULL;

	Locker _locker(this);

	DistributedObjectClassHelperMap* classMap = DistributedObjectBroker::instance()->getClassMap();

	DistributedObjectClassHelper* helper = classMap->get(className);

	if (helper != NULL) {
		object = (ManagedObject*) helper->instantiateObject();
		DistributedObjectServant* servant = helper->instantiateServant();

		loadTable(database, oid);

		if (oid == 0) {
			if (database != "staticobjects")
				oid = getNextObjectID(database);
			else
				oid = getNextFreeObjectID();
		}

		object->_setObjectID(oid);
		object->_setImplementation(servant);

		servant->_setStub(object);
		servant->_setClassHelper(helper);
		servant->_serializationHelperMethod();

		object->deploy();

		if (persistenceLevel > 0) {
			updatePersistentObject(object);

			object->queueUpdateToDatabaseTask();

			object->setPersistent(persistenceLevel);
		}

	} else {
		error("unknown className:" + className + " in classMap");
	}

	return object;
}

uint64 ObjectManager::getNextObjectID(const String& database) {
	uint64 oid = 0;

	if (database.length() > 0) {
		uint16 tableID = (uint16) database.hashCode();

		oid += tableID;

		oid = oid << 48;
	}

	oid += getNextFreeObjectID();

	return oid;
}

ObjectDatabase* ObjectManager::loadTable(const String& database, uint64 objectID) {
	ObjectDatabase* table = NULL;

	if (database.length() > 0) {
		if (objectID != 0) {
			uint16 tableID = (uint16) (objectID >> 48);

			table = databaseEnvironment->loadDatabase(database, true, tableID);
		} else {
			table = databaseEnvironment->loadDatabase(database, true);
		}
	}

	return table;
}

ObjectDatabase* ObjectManager::getTable(uint64 objectID) {
	ObjectDatabase* table = NULL;

	if (objectID != 0) {
		uint16 tableID = (uint16) (objectID >> 48);

		table = databaseEnvironment->getDatabase(tableID);
	}

	return table;
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

