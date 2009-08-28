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
#include "server/zone/objects/tangible/wearables/ArmorObject.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/objects/tangible/terminal/startinglocation/StartingLocationTerminal.h"
#include "server/db/ServerDatabase.h"
#include "ObjectMap.h"
#include "server/zone/Zone.h"

Lua* ObjectManager::luaTemplatesInstance = NULL;

ObjectManager::ObjectManager() : DOBObjectManagerImplementation(), Logger("ObjectManager") {
	server = NULL;

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
}

void ObjectManager::registerObjectTypes() {
	info("registering object types");
	//objectFactory.registerObject<SceneObject>(0);
	objectFactory.registerObject<CreatureObject>(SceneObjectImplementation::CREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObjectImplementation::NPCCREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObjectImplementation::DROIDCREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObjectImplementation::PROBOTCREATURE);

	objectFactory.registerObject<PlayerCreature>(SceneObjectImplementation::PLAYERCREATURE);

	objectFactory.registerObject<IntangibleObject>(SceneObjectImplementation::INTANGIBLE);

	objectFactory.registerObject<ArmorObject>(SceneObjectImplementation::ARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObjectImplementation::BODYARMOR); //chest plates

	objectFactory.registerObject<Container>(SceneObjectImplementation::CONTAINER);
	objectFactory.registerObject<TangibleObject>(SceneObjectImplementation::GENERICITEM);
	objectFactory.registerObject<TangibleObject>(SceneObjectImplementation::WEARABLECONTAINER);

	objectFactory.registerObject<CellObject>(SceneObjectImplementation::CELLOBJECT);
	objectFactory.registerObject<PlayerObject>(SceneObjectImplementation::PLAYEROBJECT);

	objectFactory.registerObject<WaypointObject>(SceneObjectImplementation::WAYPOINT);

	objectFactory.registerObject<BuildingObject>(SceneObjectImplementation::BUILDING);

	objectFactory.registerObject<WeaponObject>(SceneObjectImplementation::WEAPON);
	objectFactory.registerObject<MeleeWeaponObject>(SceneObjectImplementation::MELEEWEAPON);


	objectFactory.registerObject<Terminal>(SceneObjectImplementation::TERMINAL);
	objectFactory.registerObject<Terminal>(SceneObjectImplementation::SPACETERMINAL);
	objectFactory.registerObject<Terminal>(SceneObjectImplementation::SHIPPINGTERMINAL);
	objectFactory.registerObject<Terminal>(SceneObjectImplementation::INTERACTIVETERMINAL);
	objectFactory.registerObject<StartingLocationTerminal>(SceneObjectImplementation::NEWBIETUTORIALTERMINAL);


	//temporary
	objectFactory.registerObject<CreatureObject>(SceneObjectImplementation::HOVERVEHICLE);

}

void ObjectManager::loadLastUsedObjectID() {
	info("loading last used object id");

	StringBuffer query;

	query << "SELECT COUNT(*) FROM objects;";
	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

	if (!result->next()) {
		delete result;
		return;
	}

	if (result->getInt(0) > 0) {
		delete result;

		query.deleteAll();

		query << "SELECT MAX(objectid) FROM objects;";
		result = ServerDatabase::instance()->executeQuery(query);

		if (!result->next()) {
			delete result;
			return;
		}

		nextObjectID = result->getUnsignedLong(0) + 1;

		delete result;
	}

	info("done loading last use object id");
}


DistributedObjectStub* ObjectManager::loadPersistentObject(uint64 objectID) {
	SceneObject* object = NULL;
	String objectData;

	try {
		lock();

		DistributedObject* dobject = getObject(objectID, false);

		if (dobject != NULL) {
			object = dynamic_cast<SceneObject*>(dobject);

			if (object == NULL) {
				error("different object already in database");
				unlock();

				return NULL;
			} else {
				unlock();

				return object;
			}
		}

		StringBuffer query;
		query << "SELECT data FROM objects WHERE objectid = " << objectID;
		ResultSet* result = ServerDatabase::instance()->executeQuery(query);

		if (!result->next()) {
			//error("object not found in database");
			delete result;

			unlock();

			return NULL;
		}

		objectData = result->getString(0);
		delete result;

		VectorMap<String, String> variableDataMap;
		Serializable::getVariableDataMap(objectData, variableDataMap);

		uint32 serverObjectCRC = UnsignedInteger::valueOf(variableDataMap.get("serverObjectCRC"));

		object = createObject(serverObjectCRC, false, objectID, false);

		if (object == NULL) {
			error("could not load object from database");
			unlock();
			return NULL;
		}

		unlock();

	} catch (Exception& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in SceneObject* ObjectManager::loadFromDatabase(uint64 objectID)");
	}

	try {
		object->wlock();

		object->setPersistent(true);
		object->deSerialize(objectData);

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

	object->info("loaded from db", true);

	return object;
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

int ObjectManager::updatePersistentObject(DistributedObject* object) {
	try {
		String objectData;
		((ManagedObject*)object)->serialize(objectData);
		objectData.escapeString();

		StringBuffer query;
		query << "UPDATE objects SET data = '" << objectData << "' WHERE objectid = " << object->_getObjectID() << ";";
		ServerDatabase::instance()->executeStatement(query);
	} catch (...) {
		error("unreported exception caught in ObjectManager::updateToDatabase(SceneObject* object)");
	}

	return 1;
}

SceneObject* ObjectManager::createObject(uint32 objectCRC, bool persistent, uint64 oid, bool doLock) {
	SceneObject* object = NULL;

	try {
		lock(doLock);

		object = loadObjectFromTemplate(objectCRC);

		if (object == NULL) {
			unlock(doLock);
			return NULL;
		}

		object->setZoneProcessServer(server);
		object->setPersistent(persistent);

		if (oid == 0)
			oid = getNextFreeObjectID(false);

		object->_setObjectID(oid);

		String logName = object->getLoggingName();

		StringBuffer newLogName;
		newLogName << logName << " 0x" << hex << oid;

		object->setLoggingName(newLogName.toString());

		object->deploy(newLogName.toString());

		if (persistent) {
			String objectData;
			object->serialize(objectData);
			objectData.escapeString();

			StringBuffer query;
			query << "INSERT INTO `objects` (`objectid`, `data`) VALUES (" << object->getObjectID() << ", '" << objectData << "');";
			ServerDatabase::instance()->executeStatement(query);

			object->queueUpdateToDatabaseTask();
		}

		unlock(doLock);
	} catch (Exception& e) {
		unlock(doLock);

		error("exception caught in SceneObject* ObjectManager::createObject(uint32 objectCRC, uint64 oid)");
		error(e.getMessage());

		e.printStackTrace();
	} catch (...) {
		unlock(doLock);

		error("unreported exception caught in SceneObject* ObjectManager::createObject(uint32 objectCRC, uint64 oid)");
	}

	return object;
}

int ObjectManager::destroyObject(uint64 objectID) {
	lock();

	/*try {
		ManagedReference<SceneObject*> object = remove(objectID);

		if (object == NULL) {
			unlock();
			return;
		}

		if (object->isPlayerCreature()) {
			unlock();
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

	unlock();

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
