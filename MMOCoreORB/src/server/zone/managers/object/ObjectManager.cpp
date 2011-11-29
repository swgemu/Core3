/*
 * ObjectManager.cpp
 *
 *  Created on: 13/11/2009
 *      Author: victor
 */

#include "ObjectManager.h"
#include "objects.h"


#include "server/db/ServerDatabase.h"

#include "ObjectMap.h"

#include "server/zone/Zone.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/templates/SharedObjectTemplate.h"
#include "UpdateModifiedObjectsThread.h"
#include "server/chat/ChatManager.h"
#include "UpdateModifiedObjectsTask.h"
#include "engine/db/berkley/BTransaction.h"
#include "CommitMasterTransactionTask.h"
#include "ObjectVersionUpdateManager.h"

using namespace engine::db;

ObjectManager::ObjectManager() : DOBObjectManagerImplementation(), Logger("ObjectManager") {
	server = NULL;
	objectUpdateInProcess = false;

	databaseManager = ObjectDatabaseManager::instance();
	databaseManager->loadDatabases();
	templateManager = TemplateManager::instance();
	templateManager->loadLuaTemplates();

	registerObjectTypes();

	databaseManager->loadObjectDatabase("clientobjects", true, 0);
	databaseManager->loadObjectDatabase("sceneobjects", true);
	databaseManager->loadObjectDatabase("playerstructures", true);
	databaseManager->loadObjectDatabase("buffs", true);
	databaseManager->loadObjectDatabase("missionobjectives", true);
	databaseManager->loadObjectDatabase("missionobservers", true);
	databaseManager->loadObjectDatabase("cityregions", true);
	databaseManager->loadObjectDatabase("guilds", true);
	databaseManager->loadObjectDatabase("spawnareas", true);
	databaseManager->loadObjectDatabase("spawnobservers", true);
	databaseManager->loadObjectDatabase("aiobservers", true);
	databaseManager->loadObjectDatabase("sceneobjectcomponents", true);

	ObjectDatabaseManager::instance()->commitLocalTransaction();

	loadLastUsedObjectID();

	totalUpdatedObjects = 0;

	setLogging(false);
	setGlobalLogging(true);

	updateModifiedObjectsTask = new UpdateModifiedObjectsTask();
	//updateModifiedObjectsTask->schedule(UPDATETODATABASETIME);


	for (int i = 0; i < INITIALUPDATEMODIFIEDOBJECTSTHREADS; ++i) {
		createUpdateModifiedObjectsThread();
	}
}

ObjectManager::~ObjectManager() {
	//info("closing databases...", true);

	//ObjectDatabaseManager::instance()->finalize();

	if (updateModifiedObjectsTask->isScheduled())
		updateModifiedObjectsTask->cancel();
}

void ObjectManager::registerObjectTypes() {
	info("registering object types");
	//objectFactory.registerObject<SceneObject>(0);
	objectFactory.registerObject<TangibleObject>(6);
	objectFactory.registerObject<TangibleObject>(SceneObject::GENERALTANGIBLEOBJECT);
	objectFactory.registerObject<StaticObject>(SceneObject::FLORA);

	objectFactory.registerObject<ActiveArea>(SceneObject::ACTIVEAREA);
	objectFactory.registerObject<BadgeActiveArea>(SceneObject::BADGEAREA);
	objectFactory.registerObject<GarageArea>(SceneObject::GARAGEAREA);
	objectFactory.registerObject<MissionSpawnActiveArea>(SceneObject::MISSIONSPAWNAREA);
	objectFactory.registerObject<MissionReconActiveArea>(SceneObject::MISSIONRECONAREA);
	objectFactory.registerObject<DynamicSpawnArea>(SceneObject::DYNAMICSPAWNAREA);
	objectFactory.registerObject<StaticSpawnArea>(SceneObject::STATICSPAWNAREA);
	objectFactory.registerObject<Region>(SceneObject::REGIONAREA);
	objectFactory.registerObject<StaticObject>(SceneObject::STATICOBJECT);
	objectFactory.registerObject<Creature>(SceneObject::CREATURE);
	objectFactory.registerObject<NonPlayerCreatureObject>(SceneObject::NPCCREATURE);
	objectFactory.registerObject<JunkdealerCreature>(SceneObject::JUNKDEALERCREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObject::DROIDCREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObject::PROBOTCREATURE);
	objectFactory.registerObject<InformantCreature>(SceneObject::INFORMANTCREATURE);
	objectFactory.registerObject<VendorCreature>(SceneObject::VENDORCREATURE);

	objectFactory.registerObject<CreatureObject>(SceneObject::PLAYERCREATURE);

	objectFactory.registerObject<IntangibleObject>(SceneObject::INTANGIBLE);

	objectFactory.registerObject<ArmorObject>(SceneObject::ARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObject::BODYARMOR); //chest plates
	objectFactory.registerObject<ArmorObject>(SceneObject::HEADARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObject::MISCARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObject::LEGARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObject::ARMARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObject::HANDARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObject::FOOTARMOR);
	objectFactory.registerObject<PsgArmorObject>(SceneObject::SHIELDGENERATOR);

	objectFactory.registerObject<ToolTangibleObject>(SceneObject::TOOL);
	objectFactory.registerObject<ToolTangibleObject>(SceneObject::REPAIRTOOL);
	objectFactory.registerObject<CraftingTool>(SceneObject::CRAFTINGTOOL);
	objectFactory.registerObject<SurveyTool>(SceneObject::SURVEYTOOL);

	objectFactory.registerObject<CraftingStation>(SceneObject::CRAFTINGSTATION);

	objectFactory.registerObject<TangibleObject>(SceneObject::FURNITURE);

	objectFactory.registerObject<SignObject>(SceneObject::SIGN);

	objectFactory.registerObject<Instrument>(SceneObject::INSTRUMENT);
	objectFactory.registerObject<Food>(SceneObject::FOOD);
	objectFactory.registerObject<Drink>(SceneObject::DRINK);
	objectFactory.registerObject<Container>(SceneObject::CONTAINER);
	objectFactory.registerObject<FireworkObject>(SceneObject::FIREWORK);
	objectFactory.registerObject<TangibleObject>(SceneObject::ITEM);
	objectFactory.registerObject<TangibleObject>(SceneObject::GENERICITEM);
	objectFactory.registerObject<Container>(SceneObject::WEARABLECONTAINER);
	objectFactory.registerObject<LootkitObject>(SceneObject::LOOTKIT);
	objectFactory.registerObject<CampKit>(SceneObject::CAMPKIT);
	objectFactory.registerObject<Container>(SceneObject::STATICLOOTCONTAINER);
	objectFactory.registerObject<TangibleObject>(SceneObject::PLAYERLOOTCRATE);

	objectFactory.registerObject<SlicingTool>(SceneObject::SLICINGTOOL);
	objectFactory.registerObject<SlicingTool>(SceneObject::FLOWANALYZER);
	objectFactory.registerObject<SlicingTool>(SceneObject::MOLECULARCLAMP);
	objectFactory.registerObject<SlicingTool>(SceneObject::WEAPONUPGRADEKIT);
	objectFactory.registerObject<SlicingTool>(SceneObject::ARMORUPGRADEKIT);
	objectFactory.registerObject<PrecisionLaserKnife>(SceneObject::LASERKNIFE);

	objectFactory.registerObject<CellObject>(SceneObject::CELLOBJECT);
	objectFactory.registerObject<PlayerObject>(SceneObject::PLAYEROBJECT);

	objectFactory.registerObject<WaypointObject>(SceneObject::WAYPOINT);

	objectFactory.registerObject<WearableObject>(SceneObject::WEARABLE);
	objectFactory.registerObject<WearableObject>(SceneObject::RING);
	objectFactory.registerObject<WearableObject>(SceneObject::BRACELET);
	objectFactory.registerObject<WearableObject>(SceneObject::NECKLACE);
	objectFactory.registerObject<WearableObject>(SceneObject::EARRING);

	objectFactory.registerObject<Attachment>(SceneObject::ARMORATTACHMENT);
	objectFactory.registerObject<Attachment>(SceneObject::CLOTHINGATTACHMENT);

	objectFactory.registerObject<BuildingObject>(SceneObject::BUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObject::CAPITOLBUILDING);
	objectFactory.registerObject<TutorialBuildingObject>(SceneObject::TUTORIALBUILDING);
	objectFactory.registerObject<CloningBuildingObject>(SceneObject::CLONINGBUILDING);
	objectFactory.registerObject<MedicalBuildingObject>(SceneObject::MEDICALBUILDING);
	objectFactory.registerObject<TravelBuildingObject>(SceneObject::TRAVELBUILDING);
	objectFactory.registerObject<RecreationBuildingObject>(SceneObject::RECREATIONBUILDING);
	objectFactory.registerObject<TravelBuildingObject>(SceneObject::STARPORTBUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObject::FACTIONPERKBUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObject::HOTELBUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObject::THEATERBUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObject::COMBATBUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObject::COMMERCEBUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObject::UNIVERSITYBUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObject::GARAGEBUILDING);
	objectFactory.registerObject<CityHallObject>(SceneObject::CITYHALLBUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObject::SALONBUILDING);


	objectFactory.registerObject<InstallationObject>(SceneObject::INSTALLATION);
	objectFactory.registerObject<GarageInstallation>(SceneObject::GARAGEINSTALLATION);
	objectFactory.registerObject<ShuttleInstallation>(SceneObject::SHUTTLEINSTALLATION);
	objectFactory.registerObject<HarvesterObject>(SceneObject::HARVESTER);
	objectFactory.registerObject<FactoryObject>(SceneObject::FACTORY);
	objectFactory.registerObject<GeneratorObject>(SceneObject::GENERATOR);

	objectFactory.registerObject<WeaponObject>(SceneObject::WEAPON);
	objectFactory.registerObject<WeaponObject>(SceneObject::MELEEWEAPON);
	objectFactory.registerObject<WeaponObject>(SceneObject::PISTOL);
	objectFactory.registerObject<WeaponObject>(SceneObject::RANGEDWEAPON);
	objectFactory.registerObject<WeaponObject>(SceneObject::ONEHANDMELEEWEAPON);
	objectFactory.registerObject<WeaponObject>(SceneObject::RIFLE);
	objectFactory.registerObject<WeaponObject>(SceneObject::CARBINE);
	objectFactory.registerObject<WeaponObject>(SceneObject::POLEARM);
	objectFactory.registerObject<WeaponObject>(SceneObject::TWOHANDMELEEWEAPON);
	objectFactory.registerObject<WeaponObject>(SceneObject::LIGHTNINGRIFLE);

	objectFactory.registerObject<MissionObject>(SceneObject::MISSIONOBJECT);

	objectFactory.registerObject<Terminal>(SceneObject::TERMINAL);
	objectFactory.registerObject<Terminal>(SceneObject::INSURANCE);
	objectFactory.registerObject<SpaceshipTerminal>(SceneObject::SPACETERMINAL);
	objectFactory.registerObject<Terminal>(SceneObject::SHIPPINGTERMINAL);
	objectFactory.registerObject<Terminal>(SceneObject::INTERACTIVETERMINAL);
	objectFactory.registerObject<MissionTerminal>(SceneObject::MISSIONTERMINAL);
	objectFactory.registerObject<BazaarTerminal>(SceneObject::BAZAAR);
	objectFactory.registerObject<BankTerminal>(SceneObject::BANK);
	objectFactory.registerObject<StartingLocationTerminal>(SceneObject::NEWBIETUTORIALTERMINAL);
	objectFactory.registerObject<CharacterBuilderTerminal>(SceneObject::CHARACTERBUILDERTERMINAL);
	objectFactory.registerObject<StructureTerminal>(SceneObject::PLAYERTERMINALSTRUCTURE);
	objectFactory.registerObject<ElevatorTerminal>(SceneObject::ELEVATORTERMINAL);
	objectFactory.registerObject<TicketCollector>(SceneObject::TICKETCOLLECTOR);
	objectFactory.registerObject<TicketObject>(SceneObject::TRAVELTICKET);
	objectFactory.registerObject<TravelTerminal>(SceneObject::TRAVELTERMINAL);
	objectFactory.registerObject<GuildTerminal>(SceneObject::GUILDTERMINAL);
	objectFactory.registerObject<CityTerminal>(SceneObject::CITYTERMINAL);
	objectFactory.registerObject<CityVoteTerminal>(SceneObject::CITYVOTETERMINAL);
	objectFactory.registerObject<GamblingTerminal>(SceneObject::GAMBLINGTERMINAL);
	objectFactory.registerObject<CloningTerminal>(SceneObject::CLONING);
	objectFactory.registerObject<VendorTerminal>(SceneObject::VENDORTERMINAL);

	objectFactory.registerObject<LairObject>(SceneObject::LAIR);

	objectFactory.registerObject<Deed>(SceneObject::DEED);
	objectFactory.registerObject<VehicleDeed>(SceneObject::VEHICLEDEED);
	objectFactory.registerObject<BuildingDeed>(SceneObject::BUILDINGDEED);
	objectFactory.registerObject<InstallationDeed>(SceneObject::INSTALLATIONDEED);
	objectFactory.registerObject<ResourceDeed>(SceneObject::RESOURCEDEED);

	objectFactory.registerObject<GroupObject>(SceneObject::GROUPOBJECT);
	objectFactory.registerObject<GuildObject>(SceneObject::GUILDOBJECT);

	objectFactory.registerObject<StimPack>(SceneObject::STIMPACK);
	objectFactory.registerObject<RangedStimPack>(SceneObject::RANGEDSTIMPACK);
	objectFactory.registerObject<EnhancePack>(SceneObject::ENHANCEPACK);
	objectFactory.registerObject<CurePack>(SceneObject::CUREPACK);
	objectFactory.registerObject<DotPack>(SceneObject::DOTPACK);
	objectFactory.registerObject<WoundPack>(SceneObject::WOUNDPACK);
	objectFactory.registerObject<StatePack>(SceneObject::STATEPACK);
	objectFactory.registerObject<RevivePack>(SceneObject::REVIVEPACK);

	//clothing
	objectFactory.registerObject<ClothingObject>(SceneObject::CLOTHING);
	objectFactory.registerObject<ClothingObject>(SceneObject::BANDOLIER);
	objectFactory.registerObject<ClothingObject>(SceneObject::BELT);
	objectFactory.registerObject<ClothingObject>(SceneObject::BODYSUIT);
	objectFactory.registerObject<ClothingObject>(SceneObject::CAPE);
	objectFactory.registerObject<ClothingObject>(SceneObject::CLOAK);
	objectFactory.registerObject<ClothingObject>(SceneObject::FOOTWEAR);
	objectFactory.registerObject<ClothingObject>(SceneObject::HEADWEAR);
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
	objectFactory.registerObject<FishObject>(SceneObject::FISH);
	objectFactory.registerObject<TangibleObject>(SceneObject::TANGIBLE);

	objectFactory.registerObject<VehicleControlDevice>(SceneObject::VEHICLECONTROLDEVICE);
	objectFactory.registerObject<ShipControlDevice>(SceneObject::SHIPCONTROLDEVICE);

	objectFactory.registerObject<VehicleObject>(SceneObject::VEHICLE);
	objectFactory.registerObject<VehicleObject>(SceneObject::HOVERVEHICLE);

	objectFactory.registerObject<ResourceSpawn>(SceneObject::RESOURCESPAWN);
	objectFactory.registerObject<ResourceContainer>(SceneObject::RESOURCECONTAINER);
	objectFactory.registerObject<ResourceContainer>(SceneObject::ENERGYGAS);
	objectFactory.registerObject<ResourceContainer>(SceneObject::ENERGYLIQUID);
	objectFactory.registerObject<ResourceContainer>(SceneObject::ENERGYRADIOACTIVE);
	objectFactory.registerObject<ResourceContainer>(SceneObject::ENERGYSOLID);
	objectFactory.registerObject<ResourceContainer>(SceneObject::INORGANICCHEMICAL);
	objectFactory.registerObject<ResourceContainer>(SceneObject::INORGANICGAS);
	objectFactory.registerObject<ResourceContainer>(SceneObject::INORGANICMINERAL);
	objectFactory.registerObject<ResourceContainer>(SceneObject::WATER);
	objectFactory.registerObject<ResourceContainer>(SceneObject::ORGANICFOOD);
	objectFactory.registerObject<ResourceContainer>(SceneObject::ORGANICHIDE);
	objectFactory.registerObject<ResourceContainer>(SceneObject::ORGANICSTRUCTURAL);
	objectFactory.registerObject<ResourceContainer>(SceneObject::QUESTREOURCE);

	objectFactory.registerObject<DraftSchematic>(SceneObject::DRAFTSCHEMATIC);
	objectFactory.registerObject<ManufactureSchematic>(SceneObject::MANUFACTURINGSCHEMATIC);
	objectFactory.registerObject<Component>(SceneObject::COMPONENT);
	objectFactory.registerObject<ArmorComponent>(SceneObject::ARMORCOMPONENT);
	objectFactory.registerObject<Component>(SceneObject::CHEMISTRYCOMPONENT);
	objectFactory.registerObject<Component>(SceneObject::CLOTHINGCOMPONENT);
	objectFactory.registerObject<Component>(SceneObject::COMMUNITYCRAFTINGCOMPONENT);
	objectFactory.registerObject<Component>(SceneObject::DROIDCOMPONENT);
	objectFactory.registerObject<Component>(SceneObject::ELECTRONICSCOMPONENT);
	objectFactory.registerObject<Component>(SceneObject::GENETICCOMPONENT);
	objectFactory.registerObject<Component>(SceneObject::LIGHTSABERCRYSTAL);
	objectFactory.registerObject<Component>(SceneObject::MELEEWEAPONCOMPONENT);
	objectFactory.registerObject<Component>(SceneObject::MUNITIONCOMPONENT);
	objectFactory.registerObject<Component>(SceneObject::RANGEDWEAPONCOMPONENT);
	objectFactory.registerObject<Component>(SceneObject::STRUCTURECOMPONENT);
	objectFactory.registerObject<Component>(SceneObject::TISSUECOMPONENT);

	objectFactory.registerObject<Component>(SceneObject::SHIPATTACHMENT);
	objectFactory.registerObject<Component>(SceneObject::SHIPREACTOR);
	objectFactory.registerObject<Component>(SceneObject::SHIPENGINE);
	objectFactory.registerObject<Component>(SceneObject::SHIPSHIELDGENERATOR);
	objectFactory.registerObject<Component>(SceneObject::SHIPARMOR);
	objectFactory.registerObject<Component>(SceneObject::SHIPWEAPON);
	objectFactory.registerObject<Component>(SceneObject::SHIPWEAPONCAPACITOR);
	objectFactory.registerObject<Component>(SceneObject::SHIPBOOSTER);
	objectFactory.registerObject<Component>(SceneObject::SHIPDRIODINTERFACE);
	objectFactory.registerObject<Component>(SceneObject::SHIPCHASSIS);
	objectFactory.registerObject<Component>(SceneObject::SHIPMISSILE);
	objectFactory.registerObject<Component>(SceneObject::SHIPCOUNTERMEASURE);
	objectFactory.registerObject<Component>(SceneObject::SHIPWEAPONLAUNCHER);
	objectFactory.registerObject<Component>(SceneObject::SHIPCOUNTERMEASURELAUNCHER);

	objectFactory.registerObject<FactoryCrate>(SceneObject::FACTORYCRATE);

	objectFactory.registerObject<AiGroup>(SceneObject::AIGROUP);
	objectFactory.registerObject<HerdGroup>(SceneObject::HERDGROUP);
	objectFactory.registerObject<PackGroup>(SceneObject::PACKGROUP);
	objectFactory.registerObject<LairGroup>(SceneObject::LAIRGROUP);

	objectFactory.registerObject<FighterShipObject>(SceneObject::SHIPFIGHTER);
	objectFactory.registerObject<SpaceStationObject>(SceneObject::SHIPSTATION);
}

void ObjectManager::updateObjectVersion() {
	ObjectVersionUpdateManager::instance()->run();

	ObjectDatabaseManager::instance()->commitLocalTransaction();
}

void ObjectManager::loadLastUsedObjectID() {
	info("loading last used object id");

	uint64 storedID = databaseManager->getLastUsedObjectID();

	if (storedID != 0) {
		info("loading stored id..");
		nextObjectID = storedID + 1;

		info("done loading last used object id 0x" + String::hexvalueOf((int64)nextObjectID).toUpperCase());
		return;
	}

	info("loading bruteforce id..");

	uint64 maxObjectID = 0;
	uint64 objectID;

	uint64 nullify = 0x0000FFFF;
	nullify = (nullify << 32) + 0xFFFFFFFF;

	for (int i = 0; i < databaseManager->getTotalDatabaseCount(); ++i) {
		LocalDatabase* database = databaseManager->getDatabase(i);

		if (!database->isObjectDatabase())
			continue;

		ObjectDatabase* db = cast<ObjectDatabase*>(database);

		String dbName;
		db->getDatabaseName(dbName);

		ObjectDatabaseIterator iterator(db);

		while (iterator.getNextKey(objectID)) {
			objectID = objectID & nullify;

			if (objectID > maxObjectID)
				maxObjectID = objectID;
		}
	}

	if (nextObjectID < maxObjectID + 1)
		nextObjectID = maxObjectID + 1;

	info("done loading last used object id 0x" + String::hexvalueOf((int64)nextObjectID).toUpperCase());
}

void ObjectManager::loadStaticObjects() {
	Locker _locker(this);

	info("loading static objects...", true);

	ObjectDatabase* staticDatabase = databaseManager->loadObjectDatabase("clientobjects", true, 0);

	ObjectDatabaseIterator iterator(staticDatabase);

	uint32 serverObjectCRC;
	uint64 objectID;

	ObjectInputStream objectData(2000);

	while (iterator.getNextKeyAndValue(objectID, &objectData)) {
		SceneObject* object = cast<SceneObject*>(getObject(objectID));

		if (object != NULL)
			continue;

		if (!Serializable::getVariable<uint32>("serverObjectCRC", &serverObjectCRC, &objectData)) {
			error("unknown scene object in static database");
			continue;
		}

		if (object == NULL) {
			object = createObject(serverObjectCRC, 0, "clientobjects", objectID);

			if (object == NULL) {
				error("could not load object from static database");

				continue;
			}

			_locker.release();
			deSerializeObject(object, &objectData);

			objectData.reset();
		}
	}
}

int ObjectManager::commitUpdatePersistentObjectToDB(DistributedObject* object) {
	totalUpdatedObjects.increment();

	/*if (!((ManagedObject*)object)->isPersistent())
		return 1;*/

	try {
		ManagedObject* managedObject = cast<ManagedObject*>(object);
		ObjectOutputStream* objectData = new ObjectOutputStream(500);

		(cast<ManagedObject*>(object))->writeObject(objectData);

		uint64 oid = object->_getObjectID();

		uint32 lastSaveCRC = managedObject->getLastCRCSave();

		uint32 currentCRC = BaseProtocol::generateCRC(objectData);

		if (lastSaveCRC == currentCRC) {
			object->_setUpdated(false);

			delete objectData;
			return 1;
		}

		ObjectDatabase* database = getTable(oid);

		if (database != NULL) {
			//StringBuffer msg;
			String dbName;

			database->getDatabaseName(dbName);

			/*msg << "saving to database with table " << dbName << " and object id 0x" << hex << oid;
				info(msg.toString());*/

			database->putData(oid, objectData, object);

			managedObject->setLastCRCSave(currentCRC);

			object->_setUpdated(false);
		} else {
			delete objectData;

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

		throw;
	}

	return 0;
}

int ObjectManager::updatePersistentObject(DistributedObject* object) {
	//use a linked list
	object->_setUpdated(true);

	return 0;
}

SceneObject* ObjectManager::loadObjectFromTemplate(uint32 objectCRC) {
	Locker _locker(this);

	SceneObject* object = NULL;

	try {
		SharedObjectTemplate* templateData = templateManager->getTemplate(objectCRC);

		if (templateData == NULL) {
			error("trying to create object with unknown objectcrc 0x" + String::hexvalueOf((int)objectCRC));
			return NULL;
		}

		uint32 gameObjectType = templateData->getGameObjectType();

		object = objectFactory.createObject(gameObjectType);

		if (object == NULL) {
			error("creating object unknown gameObjectType " + String::valueOf(gameObjectType));
			return NULL;
		}

		databaseManager->addTemporaryObject(object);

		object->setServerObjectCRC(objectCRC);
		object->loadTemplateData(templateData);

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

/*ManagedObject* ObjectManager::cloneManagedObject(ManagedObject* object, bool makeTransient) {
	ObjectOutputStream objectData(500);

	object->writeObject(&objectData);
	objectData.reset();

	ObjectInputStream objectInput;
	objectData.copy(&objectInput, 0);
	objectInput.reset();

	DistributedObjectClassHelper* helper = object->_getClassHelper();
	String className = helper->getClassName();

	ManagedObject* clonedObject = NULL;

	ObjectDatabase* database = getTable(object->getObjectID());
	String databaseName;

	if (database != NULL) {
		database->getDatabaseName(databaseName);
	}

	if (makeTransient || !object->isPersistent()) {
		clonedObject = createObject(className, 0, databaseName);
		clonedObject->setPersistent(0);
	} else if (object->isPersistent()) {
		clonedObject = createObject(className, object->getPersistenceLevel(), databaseName);
	}

	Locker locker(clonedObject);

	clonedObject->readObject(&objectInput);
}*/

SceneObject* ObjectManager::cloneObject(SceneObject* object, bool makeTransient) {
	ObjectOutputStream objectData(500);

	(cast<ManagedObject*>(object))->writeObject(&objectData);
	objectData.reset();

	ObjectInputStream objectInput;
	objectData.copy(&objectInput, 0);
	objectInput.reset();

	uint32 serverCRC = object->getServerObjectCRC();

	SceneObject* clonedObject = NULL;

	ObjectDatabase* database = getTable(object->getObjectID());
	String databaseName;
	uint64 oid;

	if (database != NULL) {
		database->getDatabaseName(databaseName);

		oid = getNextObjectID(databaseName);
	} else
		oid = getNextFreeObjectID();


	clonedObject = instantiateSceneObject(serverCRC, oid, false);

	if (makeTransient || !object->isPersistent()) {
		//clonedObject = createObject(serverCRC, 0, databaseName);
		clonedObject->setPersistent(0);
	} else if (object->isPersistent()) {
		//clonedObject = createObject(serverCRC, object->getPersistenceLevel(), databaseName);
		clonedObject->setPersistent(object->getPersistenceLevel());
	}

	Locker locker(clonedObject);

	clonedObject->readObject(&objectInput);
	clonedObject->createComponents();
	clonedObject->setParent(NULL);

	if (clonedObject->isPersistent())
		updatePersistentObject(clonedObject);

	return clonedObject;
}

void ObjectManager::persistObject(ManagedObject* object, int persistenceLevel, const String& database) {
	Locker _locker(this);

	if (object->isPersistent()) {
		//error("object is already persistent");
		return;
	}

	if (database.length() > 0) {
		uint64 objectID = object->_getObjectID();

		uint16 tableID = (uint16)(objectID >> 48);

		uint16 newDatabaseTableID = databaseManager->getDatabaseID(database);

		if (tableID != newDatabaseTableID) {
			uint64 newObjectID = getNextObjectID(database);

			object->_setObjectID(newObjectID);

			object->deploy();
		}
	} else {
		throw Exception("no database specified in ObjectManager::persistObject");
	}

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

	LocalDatabase* db = databaseManager->getDatabase(tableID);

	if (db == NULL || !db->isObjectDatabase())
		return NULL;

	ObjectDatabase* database = cast<ObjectDatabase*>( db);

	// only for debugging proposes
	DistributedObject* dobject = getObject(objectID);

	if (dobject != NULL) {
		//error("different object already in database");
		return cast<DistributedObjectStub*>( dobject);
	}

	ObjectInputStream objectData(500);

	if (database->getData(objectID, &objectData)) {
		return NULL;
	}

	uint32 serverObjectCRC = 0;
	String className;

	try {
		if (Serializable::getVariable<uint32>("serverObjectCRC", &serverObjectCRC, &objectData)) {
			object = instantiateSceneObject(serverObjectCRC, objectID, true);

			if (object == NULL) {
				error("could not load object from database");
				return NULL;
			}

			_locker.release();
			deSerializeObject(cast<SceneObject*>(object), &objectData);

			(cast<SceneObject*>(object))->info("loaded from db");

		} else if (Serializable::getVariable<String>("_className", &className, &objectData)) {
			object = createObject(className, false, "", objectID);

			if (object == NULL) {
				error("could not load object from database");
				return NULL;
			}

			_locker.release();
			deSerializeObject(cast<ManagedObject*>(object), &objectData);

		} else {
			error("could not load object from database, unknown template crc or class name");
		}
	} catch (...) {
		error("could not load object from database");

		throw;
	}

	return object;
}


void ObjectManager::deSerializeObject(ManagedObject* object, ObjectInputStream* data) {
	Locker _locker(object);

	try {
		object->readObject(data);

		if (object->isPersistent())
			object->queueUpdateToDatabaseTask();

	//	uint32 lastSaveCRC = managedObject->getLastCRCSave();

		uint32 currentCRC = BaseProtocol::generateCRC(data);

		object->setLastCRCSave(currentCRC);

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
		error("could not deserialize object from DB");
	} catch (...) {
		error("could not deserialize object from DB");

		throw;
	}
}

void ObjectManager::deSerializeObject(SceneObject* object, ObjectInputStream* data) {
	Locker locker(object);
	String logName = object->getLoggingName();

	try {
		object->readObject(data);

		object->setLoggingName(logName);

		if (object->isPersistent())
			object->queueUpdateToDatabaseTask();

		uint32 currentCRC = BaseProtocol::generateCRC(data);

		object->setLastCRCSave(currentCRC);

		object->notifyLoadFromDatabase();

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
		error("could not deserialize object from DB");
	} catch (...) {
		error("could not deserialize object from DB");

		throw;
	}
}

SceneObject* ObjectManager::instantiateSceneObject(uint32 objectCRC, uint64 oid, bool createComponents) {
	SceneObject* object = NULL;

	Locker _locker(this);

	object = loadObjectFromTemplate(objectCRC);

	if (object == NULL)
		return NULL;

	object->setZoneProcessServer(server);

	object->_setObjectID(oid);

	if (createComponents)
		object->createComponents();

	String logName = object->getLoggingName();

	StringBuffer newLogName;
	newLogName << logName << " 0x" << hex << oid;

	object->setLoggingName(newLogName.toString());

	object->deploy(newLogName.toString());
	info("deployed.." + newLogName.toString());

	return object;
}

SceneObject* ObjectManager::createObject(uint32 objectCRC, int persistenceLevel, const String& database, uint64 oid) {
	SceneObject* object = NULL;

	loadTable(database, oid);

	if (oid == 0) {
		oid = getNextObjectID(database);
	}

	object = instantiateSceneObject(objectCRC, oid, true);

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
		object = cast<ManagedObject*>( helper->instantiateObject());
		DistributedObjectServant* servant = helper->instantiateServant();

		loadTable(database, oid);

		if (oid == 0) {
			oid = getNextObjectID(database);
		}

		object->_setObjectID(oid);
		object->_setImplementation(servant);

		servant->_setStub(object);
		servant->_setClassHelper(helper);
		servant->_serializationHelperMethod();
		object->initializeTransientMembers();

		object->setPersistent(persistenceLevel);

		object->deploy();

		databaseManager->addTemporaryObject(object);

		if (persistenceLevel > 0) {
			updatePersistentObject(object);

			object->queueUpdateToDatabaseTask();
		}

	} else {
		error("unknown className:" + className + " in classMap");
	}

	return object;
}

void ObjectManager::createObjectID(const String& name, DistributedObjectStub* object) {
	Locker _locker(this);

	uint64 objectid = object->_getObjectID();

	if (objectid == 0) {
		objectid = getNextFreeObjectID();
		object->_setObjectID(objectid);
	}

	if (name.isEmpty()) {
		/*if (object->_getName().isEmpty())*/ {
			StringBuffer orbname;
			orbname << "_OrbObject" << objectid;

			object->_setName(orbname.toString());
		}
	} else
		object->_setName(name);
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

uint64 ObjectManager::getNextFreeObjectID() {
	Locker _locker(this);

	uint64 val = ++nextObjectID;

	databaseManager->updateLastUsedObjectID(val);

	return val;
}

ObjectDatabase* ObjectManager::loadTable(const String& database, uint64 objectID) {
	ObjectDatabase* table = NULL;

	if (database.length() > 0) {
		if (objectID != 0) {
			uint16 tableID = (uint16) (objectID >> 48);

			table = databaseManager->loadObjectDatabase(database, true, tableID);
		} else {
			table = databaseManager->loadObjectDatabase(database, true);
		}
	}

	return table;
}

ObjectDatabase* ObjectManager::getTable(uint64 objectID) {
	ObjectDatabase* table = NULL;
	LocalDatabase* local = NULL;

	if (objectID != 0) {
		uint16 tableID = (uint16) (objectID >> 48);

		local = databaseManager->getDatabase(tableID);

		if (local == NULL || !local->isObjectDatabase())
			return NULL;
		else
			table = cast<ObjectDatabase*>( local);
	}

	return table;
}

int ObjectManager::destroyObjectFromDatabase(uint64 objectID) {
	Locker _locker(this);

	DistributedObject* obj = getObject(objectID);

	if (obj != NULL)
		obj->_setMarkedForDeletion(true);

	return 1;
}

void ObjectManager::printInfo() {
	StringBuffer msg;
	msg << "total objects in map " << localObjectDirectory.getSize();
	info(msg.toString(), true);
}

UpdateModifiedObjectsThread* ObjectManager::createUpdateModifiedObjectsThread() {
	UpdateModifiedObjectsThread* thread = new UpdateModifiedObjectsThread(updateModifiedObjectsThreads.size(), this);
	thread->start();

	updateModifiedObjectsThreads.add(thread);

	return thread;
}

int ObjectManager::deployUpdateThreads(Vector<DistributedObject*>* objectsToUpdate, Vector<DistributedObject*>* objectsToDelete, engine::db::berkley::Transaction* transaction) {
	if (objectsToUpdate->size() == 0)
		return 0;

	totalUpdatedObjects = 0;

	Time start;

	int numberOfObjects = objectsToUpdate->size();

	info("numberOfObjects to update:" + String::valueOf(numberOfObjects), true);


	int numberOfThreads = numberOfObjects / MAXOBJECTSTOUPDATEPERTHREAD;
	int rest = numberOfThreads > 0 ? numberOfObjects % numberOfThreads : 0;

	if (rest != 0)
		++numberOfThreads;

	while (numberOfThreads > updateModifiedObjectsThreads.size())
		createUpdateModifiedObjectsThread();

	if (numberOfThreads < 4)
		numberOfThreads = 4;

	int numberPerThread  = numberOfObjects / numberOfThreads;

	if (numberPerThread == 0) {
		numberPerThread = numberOfObjects;
		numberOfThreads = 1;
	}

	for (int i = 0; i < numberOfThreads; ++i) {
		UpdateModifiedObjectsThread* thread = updateModifiedObjectsThreads.get(i);

		thread->waitFinishedWork();

		int start = i * numberPerThread;
		int end = 0;

		if (i == numberOfThreads - 1) {
			end = numberOfObjects - 1;
			thread->setObjectsToDeleteVector(objectsToDelete);
		} else
			end = start + numberPerThread - 1;

		thread->setObjectsToUpdateVector(objectsToUpdate);
		thread->setStartOffset(start);
		thread->setEndOffset(end);
		thread->setTransaction(transaction);

		thread->signalActivity();
	}

	for (int i = 0; i < numberOfThreads; ++i) {
		UpdateModifiedObjectsThread* thread = updateModifiedObjectsThreads.get(i);

		thread->waitFinishedWork();
	}

	return numberOfThreads;

}

void ObjectManager::finishObjectUpdate(bool startNew) {
	Locker _locker(this);

	objectUpdateInProcess = false;

	if (startNew)
		updateModifiedObjectsTask->schedule(UPDATETODATABASETIME);

	info("updated objects: " + String::valueOf(totalUpdatedObjects), true);
}

void ObjectManager::cancelUpdateModifiedObjectsTask() {
	Locker locker(this);

	if (updateModifiedObjectsTask->isScheduled())
		updateModifiedObjectsTask->cancel();
}

int ObjectManager::commitDestroyObjectToDB(uint64 objectID) {
	ObjectDatabase* table = getTable(objectID);

	if (table != NULL) {
		table->deleteData(objectID);

		return 0;
	} else {
		StringBuffer msg;
		msg << "could not delete object id from database table NULL for id 0x" << hex << objectID;
		error(msg);
	}

	return 1;
}

void ObjectManager::updateModifiedObjectsToDatabase(bool startTask) {
	//ObjectDatabaseManager::instance()->checkpoint();

	if (objectUpdateInProcess) {
		error("object manager already updating objects to database... try again later");
		return;
	}

//#ifndef WITH_STM
	Vector<Locker*>* lockers = Core::getTaskManager()->blockTaskManager();

	Locker _locker(this);
//#endif

#ifdef WITH_STM
	TransactionalMemoryManager::instance()->blockTransactions();
#endif

	objectUpdateInProcess = true;

	databaseManager->updateLastUsedObjectID(nextObjectID);

	ObjectDatabaseManager::instance()->commitLocalTransaction();

	engine::db::berkley::Transaction* transaction = ObjectDatabaseManager::instance()->startTransaction();

	if (updateModifiedObjectsTask->isScheduled())
		updateModifiedObjectsTask->cancel();

	info("starting saving objects to database", true);

	Vector<DistributedObject*> objectsToUpdate;
	Vector<DistributedObject*> objectsToDelete;
	Vector<Reference<DistributedObject*> > objectsToDeleteFromRAM;

	localObjectDirectory.getObjectsMarkedForUpdate(objectsToUpdate, objectsToDelete, objectsToDeleteFromRAM);

	Time start;

//#ifndef WITH_STM
	int numberOfThreads = deployUpdateThreads(&objectsToUpdate, &objectsToDelete, transaction);
//#endif

	info("copied objects into ram in " + String::valueOf(start.miliDifference()) + " ms", true);

	info("objects to delete from ram: " + String::valueOf(objectsToDeleteFromRAM.size()), true);

	for (int i = 0; i < objectsToDeleteFromRAM.size(); ++i) {
		DistributedObject* object = objectsToDeleteFromRAM.get(i);

		/*DistributedObjectBroker::instance()->undeploy(object->_getName());

			localObjectDirectory.remove(object->_getObjectID());*/
		localObjectDirectory.removeHelper(object->_getObjectID());
	}

	info("finished deleting objects from ram", true);

#ifdef WITH_STM
	TransactionalMemoryManager::instance()->unblockTransactions();
#endif

//#ifndef WITH_STM
	Core::getTaskManager()->unblockTaskManager(lockers);
	delete lockers;
//#endif
	Reference<CommitMasterTransactionTask*> watchDog = new CommitMasterTransactionTask(transaction, &updateModifiedObjectsThreads, numberOfThreads, startTask);
	watchDog->schedule(500);



#ifndef WITH_STM
	_locker.release();
#endif
}
