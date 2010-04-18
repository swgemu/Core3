/*
 * ObjectManager.cpp
 *
 *  Created on: 13/11/2009
 *      Author: victor
 */

#include "ObjectManager.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/objects/intangible/IntangibleObject.h"
#include "server/zone/objects/intangible/VehicleControlDevice.h"
#include "server/zone/objects/tangible/Container.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/objects/tangible/Food.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/staticobject/StaticObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/tangible/weapon/MeleeWeaponObject.h"
#include "server/zone/objects/tangible/weapon/RangedWeaponObject.h"
#include "server/zone/objects/tangible/weapon/PistolWeaponObject.h"
#include "server/zone/objects/tangible/weapon/RifleWeaponObject.h"
#include "server/zone/objects/tangible/weapon/OneHandMeleeWeapon.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"
#include "server/zone/objects/tangible/tool/ToolTangibleObject.h"
#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/building/cloning/CloningBuildingObject.h"
#include "server/zone/objects/building/medical/MedicalBuildingObject.h"
#include "server/zone/objects/building/recreation/RecreationBuildingObject.h"
#include "server/zone/objects/building/travel/TravelBuildingObject.h"
#include "server/zone/objects/building/tutorial/TutorialBuildingObject.h"
#include "server/zone/objects/tangible/deed/Deed.h"
#include "server/zone/objects/tangible/deed/playerhouse/PlayerHouseDeed.h"
#include "server/zone/objects/tangible/wearables/ArmorObject.h"
#include "server/zone/objects/tangible/wearables/ClothingObject.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/objects/tangible/terminal/characterbuilder/CharacterBuilderTerminal.h"
#include "server/zone/objects/tangible/terminal/startinglocation/StartingLocationTerminal.h"
#include "server/zone/objects/tangible/terminal/bank/BankTerminal.h"
#include "server/zone/objects/tangible/terminal/bazaar/BazaarTerminal.h"
#include "server/zone/objects/tangible/terminal/mission/MissionTerminal.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/tangible/fishing/FishingPoleObject.h"
#include "server/zone/objects/tangible/fishing/FishingBaitObject.h"

#include "server/db/ServerDatabase.h"

#include "ObjectMap.h"

#include "server/zone/Zone.h"
#include "server/zone/ZoneProcessServerImplementation.h"
#include "server/zone/managers/template/TemplateManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

#include "server/chat/ChatManager.h"

using namespace engine::db;

Lua* ObjectManager::luaTemplatesInstance = NULL;

ObjectManager::ObjectManager() : DOBObjectManagerImplementation(), Logger("ObjectManager") {
	server = NULL;

	databaseManager = ObjectDatabaseManager::instance();
	templateManager = TemplateManager::instance();

	registerObjectTypes();

	luaTemplatesInstance = new Lua();
	luaTemplatesInstance->init();

	info("loading object templates...", true);
	registerFunctions();
	registerGlobals();
	luaTemplatesInstance->runFile("scripts/object/main.lua");

	databaseManager->loadDatabase("staticobjects", true, 0);

	loadLastUsedObjectID();

	setLogging(false);
	setGlobalLogging(true);
}

ObjectManager::~ObjectManager() {
	info("closing databases...", true);

	ObjectDatabaseManager::instance()->finalize();

	delete luaTemplatesInstance;
	luaTemplatesInstance = NULL;
}

void ObjectManager::registerObjectTypes() {
	info("registering object types");
	//objectFactory.registerObject<SceneObject>(0);
	objectFactory.registerObject<StaticObject>(SceneObject::STATICOBJECT);
	objectFactory.registerObject<CreatureObject>(SceneObject::CREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObject::NPCCREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObject::DROIDCREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObject::PROBOTCREATURE);

	objectFactory.registerObject<PlayerCreature>(SceneObject::PLAYERCREATURE);

	objectFactory.registerObject<IntangibleObject>(SceneObject::INTANGIBLE);

	objectFactory.registerObject<ArmorObject>(SceneObject::ARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObject::BODYARMOR); //chest plates

	objectFactory.registerObject<ToolTangibleObject>(SceneObject::TOOL);
	objectFactory.registerObject<CraftingTool>(SceneObject::CRAFTINGTOOL);
	objectFactory.registerObject<SurveyTool>(SceneObject::SURVEYTOOL);

	objectFactory.registerObject<Instrument>(SceneObject::INSTRUMENT);
	objectFactory.registerObject<Food>(SceneObject::FOOD);
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
	objectFactory.registerObject<PistolWeaponObject>(SceneObject::PISTOL);
	objectFactory.registerObject<RangedWeaponObject>(SceneObject::RANGEDWEAPON);
	objectFactory.registerObject<OneHandMeleeWeapon>(SceneObject::ONEHANDMELEEWEAPON);
	objectFactory.registerObject<RifleWeaponObject>(SceneObject::RIFLE);

	objectFactory.registerObject<MissionObject>(SceneObject::MISSIONOBJECT);

	objectFactory.registerObject<Terminal>(SceneObject::TERMINAL);
	objectFactory.registerObject<Terminal>(SceneObject::SPACETERMINAL);
	objectFactory.registerObject<Terminal>(SceneObject::SHIPPINGTERMINAL);
	objectFactory.registerObject<Terminal>(SceneObject::INTERACTIVETERMINAL);
	objectFactory.registerObject<MissionTerminal>(SceneObject::MISSIONTERMINAL);
	objectFactory.registerObject<BazaarTerminal>(SceneObject::BAZAAR);
	objectFactory.registerObject<BankTerminal>(SceneObject::BANK);
	objectFactory.registerObject<StartingLocationTerminal>(SceneObject::NEWBIETUTORIALTERMINAL);
	objectFactory.registerObject<CharacterBuilderTerminal>(SceneObject::CHARACTERBUILDERTERMINAL);

	objectFactory.registerObject<Deed>(SceneObject::DEED);
	objectFactory.registerObject<PlayerHouseDeed>(SceneObject::BUILDINGDEED);

	objectFactory.registerObject<GroupObject>(SceneObject::GROUPOBJECT);

	//clothing
	objectFactory.registerObject<ClothingObject>(SceneObject::CLOTHING);
	objectFactory.registerObject<ClothingObject>(SceneObject::BANDOLIER);
	objectFactory.registerObject<ClothingObject>(SceneObject::BELT);
	objectFactory.registerObject<ClothingObject>(SceneObject::BODYSUIT);
	objectFactory.registerObject<ClothingObject>(SceneObject::CAPE);
	objectFactory.registerObject<ClothingObject>(SceneObject::CLOAK);
	objectFactory.registerObject<ClothingObject>(SceneObject::FOOTWEAR);
	objectFactory.registerObject<ClothingObject>(SceneObject::DRESS);
	objectFactory.registerObject<ClothingObject>(SceneObject::HANDWEAR);
	objectFactory.registerObject<ClothingObject>(SceneObject::JACKET);
	objectFactory.registerObject<ClothingObject>(SceneObject::PANTS);
	objectFactory.registerObject<ClothingObject>(SceneObject::ROBE);
	objectFactory.registerObject<ClothingObject>(SceneObject::SHIRT);
	objectFactory.registerObject<ClothingObject>(SceneObject::VEST);
	objectFactory.registerObject<ClothingObject>(SceneObject::WOOKIEGARB);
	objectFactory.registerObject<ClothingObject>(SceneObject::MISCCLOTHING);
	objectFactory.registerObject<ClothingObject>(SceneObject::SKIRT);
	objectFactory.registerObject<ClothingObject>(SceneObject::ITHOGARB);
	objectFactory.registerObject<FishingPoleObject>(SceneObject::FISHINGPOLE);
	objectFactory.registerObject<FishingBaitObject>(SceneObject::FISHINGBAIT);
	objectFactory.registerObject<TangibleObject>(SceneObject::TANGIBLE);
	objectFactory.registerObject<VehicleControlDevice>(SceneObject::VEHICLECONTROLDEVICE);

	objectFactory.registerObject<VehicleObject>(SceneObject::VEHICLE);
	objectFactory.registerObject<VehicleObject>(SceneObject::HOVERVEHICLE);

}


void ObjectManager::loadLastUsedObjectID() {
	info("loading last used object id");

	uint64 maxObjectID = 0;
	uint64 objectID;

	uint64 nullify = 0x0000FFFF;
	nullify = (nullify << 32) + 0xFFFFFFFF;

	for (int i = 0; i < databaseManager->getDatabaseCount(); ++i) {
		ObjectDatabase* db = databaseManager->getDatabase(i);

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

	ObjectDatabase* staticDatabase = databaseManager->loadDatabase("staticobjects", true, 0);

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
		ObjectOutputStream objectData(500);

		((ManagedObject*)object)->writeObject(&objectData);

		uint64 oid = object->_getObjectID();

		ObjectDatabase* database = getTable(oid);

		if (database != NULL) {
			StringBuffer msg;
			String dbName;

			database->getDatabaseName(dbName);

			msg << "saving to database with table " << dbName << " and object id 0x" << hex << oid;
			info(msg.toString(), true);

			database->putData(oid, &objectData);
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

		if (!result.isValidTable()) {
			error("unknown template " + String::valueOf(objectCRC));
			return NULL;
		}

		uint32 gameObjectType = result.getIntField("gameObjectType");

		object = objectFactory.createObject(gameObjectType);

		if (object == NULL) {
			error("creating object unknown gameObjectType " + String::valueOf(gameObjectType));
			return NULL;
		}

		object->setServerObjectCRC(objectCRC);
		object->loadTemplateData(&result);

	} catch (Exception& e) {
		error("exception caught in SceneObject* ObjectManager::loadObjectFromTemplate(uint32 objectCRC)");
		error(e.getMessage());

		e.printStackTrace();
	} catch (...) {
		error("unreported exception caught in SceneObject* ObjectManager::loadObjectFromTemplate(uint32 objectCRC)");
	}

	return object;
}

void ObjectManager::persistObject(ManagedObject* object, int persistenceLevel, const String& database) {
	Locker _locker(this);

	uint64 newObjectID = getNextObjectID(database);

	object->_setObjectID(newObjectID);

	object->setPersistent(persistenceLevel);

	updatePersistentObject(object);
}

DistributedObjectStub* ObjectManager::loadPersistentObject(uint64 objectID) {
	DistributedObjectStub* object = NULL;

	Locker _locker(this);

	uint16 tableID = (uint16)(objectID >> 48);

	/*StringBuffer infoMsg;
	infoMsg << "trying to get database with table id 0x" << hex << tableID << " with obejct id 0x" << hex << objectID;
	info(infoMsg.toString(), true);*/

	ObjectDatabase* database = databaseManager->getDatabase(tableID);

	if (database == NULL)
		return NULL;

	// only for debugging proposes
	DistributedObject* dobject = getObject(objectID);

	if (dobject != NULL) {
		//error("different object already in database");
		return (DistributedObjectStub*) dobject;
	}

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
	String logName = object->getLoggingName();

	try {
		object->wlock();

		object->readObject(data);

		Zone* zone = object->getZone();

		if (zone != NULL)
			object->insertToZone(zone);

		object->setLoggingName(logName);

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
		oid = getNextObjectID(database);
	}

	object = instantiateSceneObject(objectCRC, oid);

	if (object == NULL) {
		StringBuffer msg;
		msg << "could not create object CRC = 0x" << hex << objectCRC << " template:" << templateManager->getTemplateFile(objectCRC);
		error(msg.toString());
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
			oid = getNextObjectID(database);
		}

		object->_setObjectID(oid);
		object->_setImplementation(servant);

		((ManagedObjectImplementation*)servant)->setPersistent(persistenceLevel);
		servant->_setStub(object);
		servant->_setClassHelper(helper);
		servant->_serializationHelperMethod();

		object->deploy();

		if (persistenceLevel > 0) {
			updatePersistentObject(object);

			object->queueUpdateToDatabaseTask();
		}

	} else {
		error("unknown className:" + className + " in classMap");
	}

	return object;
}

uint64 ObjectManager::getNextObjectID(const String& database) {
	uint64 oid = 0;

	if (database.length() > 0) {
		uint16 tableID;

		tableID = databaseManager->getDatabaseID(database);

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

			table = databaseManager->loadDatabase(database, true, tableID);
		} else {
			table = databaseManager->loadDatabase(database, true);
		}
	}

	return table;
}

ObjectDatabase* ObjectManager::getTable(uint64 objectID) {
	ObjectDatabase* table = NULL;

	if (objectID != 0) {
		uint16 tableID = (uint16) (objectID >> 48);

		table = databaseManager->getDatabase(tableID);
	}

	return table;
}

int ObjectManager::destroyObject(uint64 objectID) {
	Locker _locker(this);

	ObjectDatabase* table = getTable(objectID);

	if (table != NULL) {
		table->deleteData(objectID);
	} else {
		StringBuffer msg;
		msg << "could not delete object id from database table NULL for id 0x" << hex << objectID;
		error(msg);
	}

	return 1;
}

void ObjectManager::registerFunctions() {
	//lua generic
	lua_register(luaTemplatesInstance->getLuaState(), "includeFile", includeFile);
	lua_register(luaTemplatesInstance->getLuaState(), "crcString", crcString);
	lua_register(luaTemplatesInstance->getLuaState(), "addTemplateCRC", addTemplateCRC);
}

void ObjectManager::registerGlobals() {
	//ItemMasks
	luaTemplatesInstance->setGlobalShort("MALE", WearableObject::MALE);
	luaTemplatesInstance->setGlobalShort("FEMALE", WearableObject::FEMALE);

	luaTemplatesInstance->setGlobalShort("HUMAN", WearableObject::HUMAN);
	luaTemplatesInstance->setGlobalShort("TRANDOSHAN", WearableObject::TRANDOSHAN);
	luaTemplatesInstance->setGlobalShort("TWILEK", WearableObject::TWILEK);
	luaTemplatesInstance->setGlobalShort("BOTHAN", WearableObject::BOTHAN);
	luaTemplatesInstance->setGlobalShort("ZABRAK", WearableObject::ZABRAK);
	luaTemplatesInstance->setGlobalShort("RODIAN", WearableObject::RODIAN);
	luaTemplatesInstance->setGlobalShort("MONCALAMARI", WearableObject::MONCALAMARI);
	luaTemplatesInstance->setGlobalShort("WOOKIEE", WearableObject::WOOKIEE);
	luaTemplatesInstance->setGlobalShort("SULLUSTAN", WearableObject::SULLUSTAN);
	luaTemplatesInstance->setGlobalShort("ITHORIAN", WearableObject::ITHORIAN);

	luaTemplatesInstance->setGlobalShort("NEUTRAL", WearableObject::NEUTRAL);
	luaTemplatesInstance->setGlobalShort("IMPERIAL", WearableObject::IMPERIAL);
	luaTemplatesInstance->setGlobalShort("REBEL", WearableObject::REBEL);
	luaTemplatesInstance->setGlobalShort("COVERT", WearableObject::COVERT);

	luaTemplatesInstance->setGlobalShort("ALL", WearableObject::ALL);
	luaTemplatesInstance->setGlobalShort("ALLSEXES",  WearableObject::ALLSEXES);
	luaTemplatesInstance->setGlobalShort("ALLFACTIONS", WearableObject::ALLFACTIONS);
	luaTemplatesInstance->setGlobalShort("HUMANOIDS", WearableObject::HUMANOIDS);
	luaTemplatesInstance->setGlobalShort("HUMANOID_FOOTWEAR", WearableObject::HUMANOID_FOOTWEAR);
	luaTemplatesInstance->setGlobalShort("HUMANOID_MALES", WearableObject::HUMANOID_MALES);
	luaTemplatesInstance->setGlobalShort("HUMANOID_FEMALES", WearableObject::HUMANOID_FEMALES);
	luaTemplatesInstance->setGlobalShort("HUMANOID_IMPERIALS", WearableObject::HUMANOID_IMPERIALS);
	luaTemplatesInstance->setGlobalShort("HUMANOID_REBELS", WearableObject::HUMANOID_REBELS);
	luaTemplatesInstance->setGlobalShort("WOOKIEES", WearableObject::WOOKIEES);
	luaTemplatesInstance->setGlobalShort("ITHORIANS", WearableObject::ITHORIANS);
	luaTemplatesInstance->setGlobalShort("TWILEKS", WearableObject::TWILEKS);

	luaTemplatesInstance->setGlobalInt("KINETIC", WeaponObject::KINETIC);
	luaTemplatesInstance->setGlobalInt("ENERGY", WeaponObject::ENERGY);
	luaTemplatesInstance->setGlobalInt("ELECTRICITY", WeaponObject::ELECTRICITY);
	luaTemplatesInstance->setGlobalInt("STUN", WeaponObject::STUN);
	luaTemplatesInstance->setGlobalInt("BLAST", WeaponObject::BLAST);
	luaTemplatesInstance->setGlobalInt("HEAT", WeaponObject::HEAT);
	luaTemplatesInstance->setGlobalInt("COLD", WeaponObject::COLD);
	luaTemplatesInstance->setGlobalInt("ACID", WeaponObject::ACID);
	luaTemplatesInstance->setGlobalInt("LIGHTSABER", WeaponObject::LIGHTSABER);
	luaTemplatesInstance->setGlobalInt("FORCE", WeaponObject::FORCE);


	luaTemplatesInstance->setGlobalInt("MELEEATTACK", WeaponObject::MELEEATTACK);
	luaTemplatesInstance->setGlobalInt("RANGEDATTACK", WeaponObject::RANGEDATTACK);
	luaTemplatesInstance->setGlobalInt("FORCEATTACK", WeaponObject::FORCEATTACK);
	luaTemplatesInstance->setGlobalInt("TRAPATTACK", WeaponObject::TRAPATTACK);
	luaTemplatesInstance->setGlobalInt("GRENADEATTACK", WeaponObject::GRENADEATTACK);
	luaTemplatesInstance->setGlobalInt("HEAVYACIDBEAMATTACK", WeaponObject::HEAVYACIDBEAMATTACK);
	luaTemplatesInstance->setGlobalInt("HEAVYLIGHTNINGBEAMATTACK", WeaponObject::HEAVYLIGHTNINGBEAMATTACK);
	luaTemplatesInstance->setGlobalInt("HEAVYPARTICLEBEAMATTACK", WeaponObject::HEAVYPARTICLEBEAMATTACK);
	luaTemplatesInstance->setGlobalInt("HEAVYROCKETLAUNCHERATTACK", WeaponObject::HEAVYROCKETLAUNCHERATTACK);
	luaTemplatesInstance->setGlobalInt("HEAVYLAUNCHERATTACK", WeaponObject::HEAVYLAUNCHERATTACK);
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
	String ascii =  lua_tostring(L, -2);
	uint32 value = (uint32) lua_tonumber(L, -1);

	uint32 crc = (uint32) ascii.hashCode();

	TemplateManager::instance()->addTemplate(crc, ascii);

	return 0;
}

