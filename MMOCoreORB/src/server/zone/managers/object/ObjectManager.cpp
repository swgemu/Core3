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
#include "server/chat/ChatManager.h"
#include "engine/db/berkley/BTransaction.h"
#include "ObjectVersionUpdateManager.h"
#include "server/ServerCore.h"
#include "server/zone/objects/scene/SceneObjectType.h"
#include "DeleteCharactersTask.h"
#include "server/conf/ConfigManager.h"
#include "server/zone/objects/tangible/wearables/WearableContainerObject.h"

using namespace engine::db;

//databaseManager->truncateDatabases();

// http://tinyurl.com/2g9mqh

ObjectManager::ObjectManager() : DOBObjectManager() {
	server = NULL;

	deleteCharactersTask = new DeleteCharactersTask();

	databaseManager = ObjectDatabaseManager::instance();
	databaseManager->loadDatabases(ServerCore::truncateDatabases());

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

	ObjectDatabaseManager::instance()->commitLocalTransaction();
	databaseManager->setLogLevel(databaseManager->DEBUG);


	loadLastUsedObjectID();

	setLogging(false);
	setGlobalLogging(true);
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
	objectFactory.registerObject<TangibleObject>(SceneObjectType::LAIR);
	objectFactory.registerObject<StaticObject>(SceneObjectType::FLORA);

	objectFactory.registerObject<FsVillageArea>(SceneObjectType::FSVILLAGEAREA);
	objectFactory.registerObject<LairSpawnArea>(SceneObjectType::LAIRSPAWNAREA);
	objectFactory.registerObject<ActiveArea>(SceneObjectType::ACTIVEAREA);
	objectFactory.registerObject<BadgeActiveArea>(SceneObjectType::BADGEAREA);
	objectFactory.registerObject<GarageArea>(SceneObjectType::GARAGEAREA);
	objectFactory.registerObject<MissionSpawnActiveArea>(SceneObjectType::MISSIONSPAWNAREA);
	objectFactory.registerObject<MissionReconActiveArea>(SceneObjectType::MISSIONRECONAREA);
	objectFactory.registerObject<DynamicSpawnArea>(SceneObjectType::DYNAMICSPAWNAREA);
	objectFactory.registerObject<StaticSpawnArea>(SceneObjectType::STATICSPAWNAREA);
	objectFactory.registerObject<CampSiteActiveArea>(SceneObjectType::CAMPAREA);
	objectFactory.registerObject<Region>(SceneObjectType::REGIONAREA);
	objectFactory.registerObject<StaticObject>(SceneObjectType::STATICOBJECT);
	objectFactory.registerObject<Creature>(SceneObjectType::CREATURE);
	objectFactory.registerObject<NonPlayerCreatureObject>(SceneObjectType::NPCCREATURE);
	objectFactory.registerObject<JunkdealerCreature>(SceneObjectType::JUNKDEALERCREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObjectType::DROIDCREATURE);
	objectFactory.registerObject<NonPlayerCreatureObject>(SceneObjectType::PROBOTCREATURE);
	objectFactory.registerObject<TangibleObject>(SceneObjectType::VENDOR);

	objectFactory.registerObject<CreatureObject>(SceneObjectType::PLAYERCREATURE);

	objectFactory.registerObject<IntangibleObject>(SceneObjectType::INTANGIBLE);
	objectFactory.registerObject<IntangibleObject>(SceneObjectType::DATA2);

	objectFactory.registerObject<ArmorObject>(SceneObjectType::ARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObjectType::BODYARMOR); //chest plates
	objectFactory.registerObject<ArmorObject>(SceneObjectType::HEADARMOR);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::MISCARMOR); // Some Belts Bando's'
	objectFactory.registerObject<ArmorObject>(SceneObjectType::LEGARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObjectType::ARMARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObjectType::HANDARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObjectType::FOOTARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObjectType::SHIELDGENERATOR);

	objectFactory.registerObject<ToolTangibleObject>(SceneObjectType::TOOL);
	objectFactory.registerObject<RepairTool>(SceneObjectType::REPAIRTOOL);
	objectFactory.registerObject<CraftingTool>(SceneObjectType::CRAFTINGTOOL);
	objectFactory.registerObject<SurveyTool>(SceneObjectType::SURVEYTOOL);

	objectFactory.registerObject<CraftingStation>(SceneObjectType::CRAFTINGSTATION);

	objectFactory.registerObject<TangibleObject>(SceneObjectType::FURNITURE);

	objectFactory.registerObject<SignObject>(SceneObjectType::SIGN);

	objectFactory.registerObject<Instrument>(SceneObjectType::INSTRUMENT);
	objectFactory.registerObject<Food>(SceneObjectType::FOOD);
	objectFactory.registerObject<Drink>(SceneObjectType::DRINK);
	objectFactory.registerObject<Container>(SceneObjectType::CONTAINER);
	objectFactory.registerObject<FireworkObject>(SceneObjectType::FIREWORK);
	objectFactory.registerObject<TangibleObject>(SceneObjectType::ITEM);
	objectFactory.registerObject<TangibleObject>(SceneObjectType::GENERICITEM);
	objectFactory.registerObject<WearableContainerObject>(SceneObjectType::WEARABLECONTAINER);
	objectFactory.registerObject<LootkitObject>(SceneObjectType::LOOTKIT);
	objectFactory.registerObject<TangibleObject>(SceneObjectType::CAMPKIT);
	objectFactory.registerObject<Container>(SceneObjectType::STATICLOOTCONTAINER);
	objectFactory.registerObject<TangibleObject>(SceneObjectType::PLAYERLOOTCRATE);

	objectFactory.registerObject<SlicingTool>(SceneObjectType::SLICINGTOOL);
	objectFactory.registerObject<SlicingTool>(SceneObjectType::FLOWANALYZER);
	objectFactory.registerObject<SlicingTool>(SceneObjectType::MOLECULARCLAMP);
	objectFactory.registerObject<SlicingTool>(SceneObjectType::WEAPONUPGRADEKIT);
	objectFactory.registerObject<SlicingTool>(SceneObjectType::ARMORUPGRADEKIT);
	objectFactory.registerObject<PrecisionLaserKnife>(SceneObjectType::LASERKNIFE);

	objectFactory.registerObject<CellObject>(SceneObjectType::CELLOBJECT);
	objectFactory.registerObject<PlayerObject>(SceneObjectType::PLAYEROBJECT);

	objectFactory.registerObject<WaypointObject>(SceneObjectType::WAYPOINT);

	objectFactory.registerObject<WearableObject>(SceneObjectType::JEWELRY);
	objectFactory.registerObject<WearableObject>(SceneObjectType::RING);
	objectFactory.registerObject<WearableObject>(SceneObjectType::BRACELET);
	objectFactory.registerObject<WearableObject>(SceneObjectType::NECKLACE);
	objectFactory.registerObject<WearableObject>(SceneObjectType::EARRING);

	objectFactory.registerObject<Attachment>(SceneObjectType::ARMORATTACHMENT);
	objectFactory.registerObject<Attachment>(SceneObjectType::CLOTHINGATTACHMENT);

	objectFactory.registerObject<BuildingObject>(SceneObjectType::BUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObjectType::CAPITOLBUILDING);
	objectFactory.registerObject<TutorialBuildingObject>(SceneObjectType::TUTORIALBUILDING);
	objectFactory.registerObject<HospitalBuildingObject>(SceneObjectType::HOSPITALBUILDING);
	objectFactory.registerObject<TravelBuildingObject>(SceneObjectType::TRAVELBUILDING);
	objectFactory.registerObject<RecreationBuildingObject>(SceneObjectType::RECREATIONBUILDING);
	objectFactory.registerObject<TravelBuildingObject>(SceneObjectType::STARPORTBUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObjectType::FACTIONBUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObjectType::HOTELBUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObjectType::THEATERBUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObjectType::COMBATBUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObjectType::COMMERCEBUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObjectType::UNIVERSITYBUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObjectType::GARAGEBUILDING);
	objectFactory.registerObject<BuildingObject>(SceneObjectType::SALONBUILDING);


	objectFactory.registerObject<InstallationObject>(SceneObjectType::INSTALLATION);
	objectFactory.registerObject<GarageInstallation>(SceneObjectType::GARAGEINSTALLATION);
	objectFactory.registerObject<ShuttleInstallation>(SceneObjectType::SHUTTLEINSTALLATION);
	objectFactory.registerObject<HarvesterObject>(SceneObjectType::HARVESTER);
	objectFactory.registerObject<FactoryObject>(SceneObjectType::FACTORY);
	objectFactory.registerObject<GeneratorObject>(SceneObjectType::GENERATOR);
	objectFactory.registerObject<InstallationObject>(SceneObjectType::TURRET);
	objectFactory.registerObject<InstallationObject>(SceneObjectType::MINEFIELD);

	objectFactory.registerObject<WeaponObject>(SceneObjectType::WEAPON);
	objectFactory.registerObject<WeaponObject>(SceneObjectType::MELEEWEAPON);
	objectFactory.registerObject<WeaponObject>(SceneObjectType::PISTOL);
	objectFactory.registerObject<WeaponObject>(SceneObjectType::RANGEDWEAPON);
	objectFactory.registerObject<WeaponObject>(SceneObjectType::ONEHANDMELEEWEAPON);
	objectFactory.registerObject<WeaponObject>(SceneObjectType::SPECIALHEAVYWEAPON);
	objectFactory.registerObject<WeaponObject>(SceneObjectType::HEAVYWEAPON);
	objectFactory.registerObject<WeaponObject>(SceneObjectType::RIFLE);
	objectFactory.registerObject<WeaponObject>(SceneObjectType::CARBINE);
	objectFactory.registerObject<WeaponObject>(SceneObjectType::POLEARM);
	objectFactory.registerObject<WeaponObject>(SceneObjectType::TWOHANDMELEEWEAPON);
	objectFactory.registerObject<WeaponObject>(SceneObjectType::MINE);
	objectFactory.registerObject<WeaponObject>(SceneObjectType::THROWNWEAPON);

	objectFactory.registerObject<MissionObject>(SceneObjectType::MISSIONOBJECT);

	objectFactory.registerObject<Terminal>(SceneObjectType::TERMINAL);
	objectFactory.registerObject<Terminal>(SceneObjectType::INSURANCE);
	objectFactory.registerObject<SpaceshipTerminal>(SceneObjectType::SPACETERMINAL);
	objectFactory.registerObject<Terminal>(SceneObjectType::SHIPPINGTERMINAL);
	objectFactory.registerObject<Terminal>(SceneObjectType::INTERACTIVETERMINAL);
	objectFactory.registerObject<MissionTerminal>(SceneObjectType::MISSIONTERMINAL);
	objectFactory.registerObject<Terminal>(SceneObjectType::BAZAAR);
	objectFactory.registerObject<Terminal>(SceneObjectType::BANK);
	objectFactory.registerObject<StartingLocationTerminal>(SceneObjectType::NEWBIETUTORIALTERMINAL);
	objectFactory.registerObject<CharacterBuilderTerminal>(SceneObjectType::CHARACTERBUILDERTERMINAL);
	objectFactory.registerObject<Terminal>(SceneObjectType::PLAYERTERMINALSTRUCTURE);
	objectFactory.registerObject<TicketCollector>(SceneObjectType::TICKETCOLLECTOR);
	objectFactory.registerObject<TicketObject>(SceneObjectType::TRAVELTICKET);
	objectFactory.registerObject<TravelTerminal>(SceneObjectType::TRAVELTERMINAL);
	objectFactory.registerObject<GuildTerminal>(SceneObjectType::GUILDTERMINAL);
	objectFactory.registerObject<GamblingTerminal>(SceneObjectType::GAMBLINGTERMINAL);
	objectFactory.registerObject<Terminal>(SceneObjectType::CLONING);

	objectFactory.registerObject<Deed>(SceneObjectType::DEED);
	objectFactory.registerObject<VehicleDeed>(SceneObjectType::VEHICLEDEED);
	objectFactory.registerObject<StructureDeed>(SceneObjectType::BUILDINGDEED);
	objectFactory.registerObject<StructureDeed>(SceneObjectType::INSTALLATIONDEED);
	objectFactory.registerObject<ResourceDeed>(SceneObjectType::RESOURCEDEED);

	objectFactory.registerObject<GroupObject>(SceneObjectType::GROUPOBJECT);
	objectFactory.registerObject<GuildObject>(SceneObjectType::GUILDOBJECT);

	objectFactory.registerObject<StimPack>(SceneObjectType::STIMPACK);
	objectFactory.registerObject<RangedStimPack>(SceneObjectType::RANGEDSTIMPACK);
	objectFactory.registerObject<EnhancePack>(SceneObjectType::ENHANCEPACK);
	objectFactory.registerObject<CurePack>(SceneObjectType::CUREPACK);
	objectFactory.registerObject<DotPack>(SceneObjectType::DOTPACK);
	objectFactory.registerObject<WoundPack>(SceneObjectType::WOUNDPACK);
	objectFactory.registerObject<StatePack>(SceneObjectType::STATEPACK);
	objectFactory.registerObject<RevivePack>(SceneObjectType::REVIVEPACK);

	//clothing
	objectFactory.registerObject<ClothingObject>(SceneObjectType::CLOTHING);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::BANDOLIER);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::BELT);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::BODYSUIT);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::CAPE);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::FOOTWEAR);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::HEADWEAR);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::EYEWEAR);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::DRESS);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::HANDWEAR);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::JACKET);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::PANTS);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::ROBE);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::SHIRT);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::VEST);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::WOOKIEGARB);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::MISCCLOTHING);
	objectFactory.registerObject<ClothingObject>(SceneObjectType::SKIRT);
	//objectFactory.registerObject<ClothingObject>(SceneObjectType::ITHOGARB);
	objectFactory.registerObject<FishingPoleObject>(SceneObjectType::FISHINGPOLE);
	objectFactory.registerObject<FishingBaitObject>(SceneObjectType::FISHINGBAIT);
	objectFactory.registerObject<FishObject>(SceneObjectType::FISH);
	objectFactory.registerObject<TangibleObject>(SceneObjectType::TANGIBLE);
	objectFactory.registerObject<RobeObject>(SceneObjectType::CLOAK);

	objectFactory.registerObject<TangibleObject>(SceneObjectType::TRAP);
	objectFactory.registerObject<TangibleObject>(SceneObjectType::CAMOKIT);
	objectFactory.registerObject<TangibleObject>(SceneObjectType::LIVESAMPLE);


	objectFactory.registerObject<VehicleControlDevice>(SceneObjectType::VEHICLECONTROLDEVICE);
	objectFactory.registerObject<ShipControlDevice>(SceneObjectType::SHIPCONTROLDEVICE);

	objectFactory.registerObject<VehicleObject>(SceneObjectType::VEHICLE);
	objectFactory.registerObject<VehicleObject>(SceneObjectType::HOVERVEHICLE);

	objectFactory.registerObject<ResourceSpawn>(SceneObjectType::RESOURCESPAWN);
	objectFactory.registerObject<ResourceContainer>(SceneObjectType::RESOURCECONTAINER);
	objectFactory.registerObject<ResourceContainer>(SceneObjectType::ENERGYGAS);
	objectFactory.registerObject<ResourceContainer>(SceneObjectType::ENERGYLIQUID);
	objectFactory.registerObject<ResourceContainer>(SceneObjectType::ENERGYRADIOACTIVE);
	objectFactory.registerObject<ResourceContainer>(SceneObjectType::ENERGYSOLID);
	objectFactory.registerObject<ResourceContainer>(SceneObjectType::INORGANICCHEMICAL);
	objectFactory.registerObject<ResourceContainer>(SceneObjectType::INORGANICGAS);
	objectFactory.registerObject<ResourceContainer>(SceneObjectType::INORGANICMINERAL);
	objectFactory.registerObject<ResourceContainer>(SceneObjectType::WATER);
	objectFactory.registerObject<ResourceContainer>(SceneObjectType::ORGANICFOOD);
	objectFactory.registerObject<ResourceContainer>(SceneObjectType::ORGANICHIDE);
	objectFactory.registerObject<ResourceContainer>(SceneObjectType::ORGANICSTRUCTURAL);
	objectFactory.registerObject<ResourceContainer>(SceneObjectType::QUESTREOURCE);

	objectFactory.registerObject<DraftSchematic>(SceneObjectType::DRAFTSCHEMATIC);
	objectFactory.registerObject<ManufactureSchematic>(SceneObjectType::MANUFACTURINGSCHEMATIC);
	objectFactory.registerObject<Component>(SceneObjectType::COMPONENT);
	objectFactory.registerObject<ArmorComponent>(SceneObjectType::ARMORCOMPONENT);
	objectFactory.registerObject<Component>(SceneObjectType::CHEMISTRYCOMPONENT);
	objectFactory.registerObject<Component>(SceneObjectType::CLOTHINGCOMPONENT);
	objectFactory.registerObject<Component>(SceneObjectType::COMMUNITYCRAFTINGCOMPONENT);
	objectFactory.registerObject<Component>(SceneObjectType::DROIDCOMPONENT);
	objectFactory.registerObject<Component>(SceneObjectType::ELECTRONICSCOMPONENT);
	objectFactory.registerObject<Component>(SceneObjectType::GENETICCOMPONENT);
	objectFactory.registerObject<LightsaberCrystalComponent>(SceneObjectType::LIGHTSABERCRYSTAL);
	objectFactory.registerObject<Component>(SceneObjectType::MELEEWEAPONCOMPONENT);
	objectFactory.registerObject<Component>(SceneObjectType::MUNITIONCOMPONENT);
	objectFactory.registerObject<Component>(SceneObjectType::RANGEDWEAPONCOMPONENT);
	objectFactory.registerObject<Component>(SceneObjectType::STRUCTURECOMPONENT);
	objectFactory.registerObject<Component>(SceneObjectType::TISSUECOMPONENT);

	objectFactory.registerObject<PowerupObject>(SceneObjectType::WEAPONPOWERUP);
	objectFactory.registerObject<PowerupObject>(SceneObjectType::MELEEWEAPONPOWERUP);
	objectFactory.registerObject<PowerupObject>(SceneObjectType::RANGEDWEAPONPOWERUP);
	objectFactory.registerObject<PowerupObject>(SceneObjectType::THROWNWEAPONPOWERUP);
	objectFactory.registerObject<PowerupObject>(SceneObjectType::HEAVYWEAPONPOWERUP);
	objectFactory.registerObject<PowerupObject>(SceneObjectType::MINEPOWERUP);
	objectFactory.registerObject<PowerupObject>(SceneObjectType::SPECIALHEAVYWEAPONPOWERUP);

	objectFactory.registerObject<Component>(SceneObjectType::SHIPATTACHMENT);
	objectFactory.registerObject<Component>(SceneObjectType::SHIPREACTOR);
	objectFactory.registerObject<Component>(SceneObjectType::SHIPENGINE);
	objectFactory.registerObject<Component>(SceneObjectType::SHIPSHIELDGENERATOR);
	objectFactory.registerObject<Component>(SceneObjectType::SHIPARMOR);
	objectFactory.registerObject<Component>(SceneObjectType::SHIPWEAPON);
	objectFactory.registerObject<Component>(SceneObjectType::SHIPWEAPONCAPACITOR);
	objectFactory.registerObject<Component>(SceneObjectType::SHIPBOOSTER);
	objectFactory.registerObject<Component>(SceneObjectType::SHIPDRIODINTERFACE);
	objectFactory.registerObject<Component>(SceneObjectType::SHIPCHASSIS);
	objectFactory.registerObject<Component>(SceneObjectType::SHIPMISSILE);
	objectFactory.registerObject<Component>(SceneObjectType::SHIPCOUNTERMEASURE);
	objectFactory.registerObject<Component>(SceneObjectType::SHIPWEAPONLAUNCHER);
	objectFactory.registerObject<Component>(SceneObjectType::SHIPCOUNTERMEASURELAUNCHER);

	objectFactory.registerObject<FactoryCrate>(SceneObjectType::FACTORYCRATE);

	objectFactory.registerObject<AiGroup>(SceneObjectType::AIGROUP);
	objectFactory.registerObject<HerdGroup>(SceneObjectType::HERDGROUP);
	objectFactory.registerObject<PackGroup>(SceneObjectType::PACKGROUP);
	objectFactory.registerObject<LairGroup>(SceneObjectType::LAIRGROUP);

	objectFactory.registerObject<FighterShipObject>(SceneObjectType::SHIPFIGHTER);
	objectFactory.registerObject<SpaceStationObject>(SceneObjectType::SHIPSTATION);
}

void ObjectManager::updateObjectVersion() {
	if (ObjectVersionUpdateManager::instance()->run() == 0) {
		ObjectDatabaseManager::instance()->commitLocalTransaction();

		ObjectDatabaseManager::instance()->checkpoint();
	}
}

void ObjectManager::loadLastUsedObjectID() {
	info("loading last used object id");

	uint64 storedID = databaseManager->getLastUsedObjectID();

	if (!ServerCore::truncateDatabases() && storedID != 0) {
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

		if (!Serializable::getVariable<uint32>(String("SceneObject.serverObjectCRC").hashCode(), &serverObjectCRC, &objectData)) {
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

			String logName = object->getLoggingName();

			deSerializeObject(object, &objectData);

			object->setLoggingName(logName);

			objectData.reset();
		}
	}
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
		if (Serializable::getVariable<uint32>(String("SceneObject.serverObjectCRC").hashCode(), &serverObjectCRC, &objectData)) {
			object = instantiateSceneObject(serverObjectCRC, objectID, true);

			if (object == NULL) {
				error("could not load object from database");
				return NULL;
			}

			_locker.release();

			SceneObject* scene = cast<SceneObject*>(object);

			String loggingName = scene->getLoggingName();
			uint32 templateObjectType = scene->getGameObjectType();

			deSerializeObject(scene, &objectData);

			scene->setGameObjectType(templateObjectType); // we dont want this to be the old one

			scene->setLoggingName(loggingName);

			(cast<SceneObject*>(object))->info("loaded from db");

		} else if (Serializable::getVariable<String>(String("_className").hashCode(), &className, &objectData)) {
			object = createObject(className, false, "", objectID, false);

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

	object->initializeTransientMembers();

	if (persistenceLevel > 0) {
		object->setPersistent(persistenceLevel);

		updatePersistentObject(object);

		object->queueUpdateToDatabaseTask();
	}


	return object;
}

ManagedObject* ObjectManager::createObject(const String& className, int persistenceLevel, const String& database, uint64 oid, bool initializeTransientMembers) {
	ManagedObject* object = NULL;

	Locker _locker(this);

	DistributedObjectBroker* broker = DistributedObjectBroker::instance();

	object = cast<ManagedObject*>(broker->createObjectStub(className, ""));
	DistributedObjectServant* servant = broker->createObjectServant(className, object);

	loadTable(database, oid);

	if (oid == 0) {
		oid = getNextObjectID(database);
	}

	object->_setObjectID(oid);

	servant->_serializationHelperMethod();

	if (initializeTransientMembers)
		object->initializeTransientMembers();

	object->setPersistent(persistenceLevel);

	object->deploy();

	databaseManager->addTemporaryObject(object);

	if (persistenceLevel > 0) {
		updatePersistentObject(object);

		object->queueUpdateToDatabaseTask();
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
	//assert(DistributedObjectBroker::instance()->isRootBroker());

	return DOBObjectManager::getNextFreeObjectID();
//	its saved every 5min, that should be enough
//	databaseManager->updateLastUsedObjectID(val);

	//return nextObjectID;
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

int ObjectManager::destroyObjectFromDatabase(uint64 objectID) {
	Locker _locker(this);

	DistributedObject* obj = getObject(objectID);

	if (obj != NULL)
	{
		//setLogging(true);
		//info("Marking " + String::valueOf(objectID) + " for deletion deletion");
	//	setLogging(false);
		obj->_setMarkedForDeletion(true);

	}

	return 1;
}

void ObjectManager::printInfo() {
	StringBuffer msg;
	msg << "total objects in map " << localObjectDirectory.getSize();
	info(msg.toString(), true);
}

String ObjectManager::getInfo() {
	StringBuffer msg;
	msg << "total objects in map " << localObjectDirectory.getSize();
	return msg.toString();
}

void ObjectManager::onUpdateModifiedObjectsToDatabase() {
	galaxyId = -1;

	if (server != NULL && server->getZoneServer() != NULL) {
		galaxyId = server->getZoneServer()->getGalaxyID();

		//characters_dirty chars
		try {
			charactersSaved = ServerDatabase::instance()->executeQuery("SELECT * FROM characters_dirty WHERE galaxy_id = " + String::valueOf(galaxyId));
		} catch (Exception& e) {
			error(e.getMessage());
		}
	}
}

void ObjectManager::onCommitData() {
	if (charactersSaved != NULL) {
		try {
			StringBuffer query;
			query << "REPLACE INTO characters (character_oid, account_id, galaxy_id, firstname, surname, race, gender, template) VALUES";

			StringBuffer deleteQuery;
			deleteQuery << "DELETE FROM characters_dirty WHERE ";

			bool first = true;

			int count = 0;

			while (charactersSaved->next()) {
				if (!first) {
					query << ",";
					deleteQuery << " OR ";
				}

				query << "(" << charactersSaved->getUnsignedLong(0) << ", " << charactersSaved->getInt(1) << ", "
						<< charactersSaved->getInt(2) << ", " << "\'" << String(charactersSaved->getString(3)).escapeString() << "\', "
						<< "\'" << String(charactersSaved->getString(4)).escapeString() << "\', " << charactersSaved->getInt(5) << ", "
						<< charactersSaved->getInt(6) << ", \'" << String(charactersSaved->getString(7)).escapeString() << "')";

				deleteQuery << "character_oid = " << charactersSaved->getUnsignedLong(0) << " AND galaxy_id = " << galaxyId;

				first = false;
				++count;
			}

			if (count > 0) {
				ServerDatabase::instance()->executeStatement(query.toString());
				ServerDatabase::instance()->executeStatement(deleteQuery.toString());
			}
		} catch (Exception& e) {
			System::out << e.getMessage();
		}
	}

	//Spawn the delete characters task.
	if (!deleteCharactersTask->isScheduled()) {
		deleteCharactersTask->updateDeletedCharacters();
		int mins = ConfigManager::instance()->getPurgeDeletedCharacters();
		deleteCharactersTask->schedule(mins * 60 * 1000);
	}
}
