/*
 * ObjectManager.cpp
 *
 *  Created on: 13/11/2009
 *      Author: victor
 */

#include "ObjectManager.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/NonPlayerCreatureObject.h"
#include "server/zone/objects/creature/Creature.h"
#include "server/zone/objects/creature/VehicleObject.h"
#include "server/zone/objects/creature/shuttle/ShuttleCreature.h"
#include "server/zone/objects/intangible/IntangibleObject.h"
#include "server/zone/objects/intangible/VehicleControlDevice.h"
#include "server/zone/objects/tangible/Container.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/objects/tangible/consumable/Food.h"
#include "server/zone/objects/tangible/consumable/Drink.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/trainer/TrainerCreature.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/staticobject/StaticObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/tangible/weapon/MeleeWeaponObject.h"
#include "server/zone/objects/tangible/weapon/RangedWeaponObject.h"
#include "server/zone/objects/tangible/weapon/PistolWeaponObject.h"
#include "server/zone/objects/tangible/weapon/RifleWeaponObject.h"
#include "server/zone/objects/tangible/weapon/CarbineWeaponObject.h"
#include "server/zone/objects/tangible/weapon/OneHandMeleeWeapon.h"
#include "server/zone/objects/tangible/weapon/TwoHandMeleeWeapon.h"
#include "server/zone/objects/tangible/weapon/PolearmWeaponObject.h"
#include "server/zone/objects/tangible/tool/CraftingTool.h"
#include "server/zone/objects/tangible/tool/CraftingStation.h"
#include "server/zone/objects/tangible/tool/ToolTangibleObject.h"
#include "server/zone/objects/tangible/tool/SurveyTool.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/building/cloning/CloningBuildingObject.h"
#include "server/zone/objects/building/medical/MedicalBuildingObject.h"
#include "server/zone/objects/building/recreation/RecreationBuildingObject.h"
#include "server/zone/objects/building/travel/TravelBuildingObject.h"
#include "server/zone/objects/building/tutorial/TutorialBuildingObject.h"
#include "server/zone/objects/building/city/CityHallObject.h"
#include "server/zone/objects/manufactureschematic/ManufactureSchematic.h"
#include "server/zone/objects/installation/InstallationObject.h"
#include "server/zone/objects/installation/factory/FactoryObject.h"
#include "server/zone/objects/factorycrate/FactoryCrate.h"
#include "server/zone/objects/installation/shuttle/ShuttleInstallation.h"
#include "server/zone/objects/installation/bank/BankInstallation.h"
#include "server/zone/objects/installation/generator/GeneratorObject.h"
#include "server/zone/objects/installation/harvester/HarvesterObject.h"
#include "server/zone/objects/tangible/component/Component.h"
#include "server/zone/objects/tangible/component/armor/ArmorComponent.h"
#include "server/zone/objects/tangible/deed/Deed.h"
#include "server/zone/objects/tangible/deed/building/BuildingDeed.h"
#include "server/zone/objects/tangible/deed/installation/InstallationDeed.h"
#include "server/zone/objects/tangible/wearables/ArmorObject.h"
#include "server/zone/objects/tangible/wearables/ClothingObject.h"
#include "server/zone/objects/tangible/terminal/Terminal.h"
#include "server/zone/objects/tangible/lair/LairObject.h"
#include "server/zone/objects/tangible/terminal/characterbuilder/CharacterBuilderTerminal.h"
#include "server/zone/objects/tangible/terminal/elevator/ElevatorTerminal.h"
#include "server/zone/objects/tangible/terminal/startinglocation/StartingLocationTerminal.h"
#include "server/zone/objects/tangible/terminal/bank/BankTerminal.h"
#include "server/zone/objects/tangible/terminal/ticketcollector/TicketCollector.h"
#include "server/zone/objects/tangible/terminal/travel/TravelTerminal.h"
#include "server/zone/objects/tangible/terminal/guild/GuildTerminal.h"
#include "server/zone/objects/tangible/ticket/TicketObject.h"
#include "server/zone/objects/tangible/pharmaceutical/StimPack.h"
#include "server/zone/objects/tangible/pharmaceutical/RangedStimPack.h"
#include "server/zone/objects/tangible/pharmaceutical/EnhancePack.h"
#include "server/zone/objects/tangible/pharmaceutical/CurePack.h"
#include "server/zone/objects/tangible/pharmaceutical/RevivePack.h"
#include "server/zone/objects/tangible/pharmaceutical/StatePack.h"
#include "server/zone/objects/tangible/pharmaceutical/DotPack.h"
#include "server/zone/objects/tangible/pharmaceutical/WoundPack.h"
#include "server/zone/objects/tangible/terminal/bazaar/BazaarTerminal.h"
#include "server/zone/objects/tangible/terminal/city/CityTerminal.h"
#include "server/zone/objects/tangible/terminal/city/CityVoteTerminal.h"
#include "server/zone/objects/tangible/terminal/elevator/ElevatorTerminal.h"
#include "server/zone/objects/tangible/terminal/mission/MissionTerminal.h"
#include "server/zone/objects/tangible/terminal/structure/StructureTerminal.h"
#include "server/zone/objects/tangible/sign/SignObject.h"
#include "server/zone/objects/mission/MissionObject.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/tangible/fishing/FishingPoleObject.h"
#include "server/zone/objects/tangible/fishing/FishObject.h"
#include "server/zone/objects/tangible/fishing/FishingBaitObject.h"
#include "server/zone/objects/tangible/loot/LootkitObject.h"

#include "server/zone/objects/resource/ResourceSpawn.h"
#include "server/zone/objects/resource/ResourceContainer.h"

#include "server/zone/objects/area/BadgeActiveArea.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/objects/area/MissionSpawnActiveArea.h"

#include "server/db/ServerDatabase.h"

#include "ObjectMap.h"

#include "server/zone/Zone.h"
#include "server/zone/ZoneProcessServerImplementation.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/templates/SharedObjectTemplate.h"

#include "server/chat/ChatManager.h"

using namespace engine::db;

ObjectManager::ObjectManager() : DOBObjectManagerImplementation(), Logger("ObjectManager") {
	server = NULL;

	databaseManager = ObjectDatabaseManager::instance();
	databaseManager->loadDatabases();
	templateManager = TemplateManager::instance();
	templateManager->loadLuaTemplates();

	registerObjectTypes();

	databaseManager->loadDatabase("staticobjects", true, 0);
	databaseManager->loadDatabase("sceneobjects", true);
	databaseManager->loadDatabase("playerstructures", true);
	databaseManager->loadDatabase("buffs", true);
	databaseManager->loadDatabase("missionobjectives", true);
	databaseManager->loadDatabase("missionobservers", true);
	databaseManager->loadDatabase("cityregions", true);

	ObjectDatabaseManager::instance()->commitLocalTransaction();

	loadLastUsedObjectID();

	setLogging(false);
	setGlobalLogging(true);
}

ObjectManager::~ObjectManager() {
	info("closing databases...", true);

	ObjectDatabaseManager::instance()->finalize();
}

void ObjectManager::registerObjectTypes() {
	info("registering object types");
	//objectFactory.registerObject<SceneObject>(0);
	objectFactory.registerObject<TangibleObject>(SceneObject::GENERALTANGIBLEOBJECT);
	objectFactory.registerObject<BadgeActiveArea>(SceneObject::BADGEAREA);
	objectFactory.registerObject<MissionSpawnActiveArea>(SceneObject::MISSIONSPAWNAREA);
	objectFactory.registerObject<Region>(SceneObject::REGIONAREA);
	objectFactory.registerObject<StaticObject>(SceneObject::STATICOBJECT);
	objectFactory.registerObject<Creature>(SceneObject::CREATURE);
	objectFactory.registerObject<NonPlayerCreatureObject>(SceneObject::NPCCREATURE);
	objectFactory.registerObject<ShuttleCreature>(SceneObject::SHUTTLECREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObject::DROIDCREATURE);
	objectFactory.registerObject<CreatureObject>(SceneObject::PROBOTCREATURE);
	objectFactory.registerObject<TrainerCreature>(SceneObject::TRAINERCREATURE);

	objectFactory.registerObject<PlayerCreature>(SceneObject::PLAYERCREATURE);

	objectFactory.registerObject<IntangibleObject>(SceneObject::INTANGIBLE);

	objectFactory.registerObject<ArmorObject>(SceneObject::ARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObject::BODYARMOR); //chest plates
	objectFactory.registerObject<ArmorObject>(SceneObject::HEADARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObject::MISCARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObject::LEGARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObject::ARMARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObject::HANDARMOR);
	objectFactory.registerObject<ArmorObject>(SceneObject::FOOTARMOR);

	objectFactory.registerObject<ToolTangibleObject>(SceneObject::TOOL);
	objectFactory.registerObject<CraftingTool>(SceneObject::CRAFTINGTOOL);
	objectFactory.registerObject<SurveyTool>(SceneObject::SURVEYTOOL);

	objectFactory.registerObject<CraftingStation>(SceneObject::CRAFTINGSTATION);

	objectFactory.registerObject<TangibleObject>(SceneObject::FURNITURE);

	objectFactory.registerObject<SignObject>(SceneObject::SIGN);

	objectFactory.registerObject<Instrument>(SceneObject::INSTRUMENT);
	objectFactory.registerObject<Food>(SceneObject::FOOD);
	objectFactory.registerObject<Drink>(SceneObject::DRINK);
	objectFactory.registerObject<Container>(SceneObject::CONTAINER);
	objectFactory.registerObject<TangibleObject>(SceneObject::FIREWORK);
	objectFactory.registerObject<TangibleObject>(SceneObject::ITEM);
	objectFactory.registerObject<TangibleObject>(SceneObject::GENERICITEM);
	objectFactory.registerObject<TangibleObject>(SceneObject::WEARABLECONTAINER);
	objectFactory.registerObject<LootkitObject>(SceneObject::LOOTKIT);

	objectFactory.registerObject<CellObject>(SceneObject::CELLOBJECT);
	objectFactory.registerObject<PlayerObject>(SceneObject::PLAYEROBJECT);

	objectFactory.registerObject<WaypointObject>(SceneObject::WAYPOINT);

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


	objectFactory.registerObject<InstallationObject>(SceneObject::INSTALLATION);
	objectFactory.registerObject<InstallationObject>(SceneObject::GARAGEINSTALLATION);
	objectFactory.registerObject<ShuttleInstallation>(SceneObject::SHUTTLEINSTALLATION);
	objectFactory.registerObject<BankInstallation>(SceneObject::BANKINSTALLATION);
	objectFactory.registerObject<HarvesterObject>(SceneObject::HARVESTER);
	objectFactory.registerObject<FactoryObject>(SceneObject::FACTORY);
	objectFactory.registerObject<GeneratorObject>(SceneObject::GENERATOR);

	objectFactory.registerObject<WeaponObject>(SceneObject::WEAPON);
	objectFactory.registerObject<MeleeWeaponObject>(SceneObject::MELEEWEAPON);
	objectFactory.registerObject<PistolWeaponObject>(SceneObject::PISTOL);
	objectFactory.registerObject<RangedWeaponObject>(SceneObject::RANGEDWEAPON);
	objectFactory.registerObject<OneHandMeleeWeapon>(SceneObject::ONEHANDMELEEWEAPON);
	objectFactory.registerObject<RifleWeaponObject>(SceneObject::RIFLE);
	objectFactory.registerObject<CarbineWeaponObject>(SceneObject::CARBINE);
	objectFactory.registerObject<PolearmWeaponObject>(SceneObject::POLEARM);
	objectFactory.registerObject<TwoHandMeleeWeapon>(SceneObject::TWOHANDMELEEWEAPON);
	objectFactory.registerObject<RifleWeaponObject>(SceneObject::LIGHTNINGRIFLE);

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
	objectFactory.registerObject<StructureTerminal>(SceneObject::PLAYERTERMINALSTRUCTURE);
	objectFactory.registerObject<ElevatorTerminal>(SceneObject::ELEVATORTERMINAL);
	objectFactory.registerObject<TicketCollector>(SceneObject::TICKETCOLLECTOR);
	objectFactory.registerObject<TicketObject>(SceneObject::TRAVELTICKET);
	objectFactory.registerObject<TravelTerminal>(SceneObject::TRAVELTERMINAL);
	objectFactory.registerObject<GuildTerminal>(SceneObject::GUILDTERMINAL);
	objectFactory.registerObject<CityTerminal>(SceneObject::CITYTERMINAL);
	objectFactory.registerObject<CityVoteTerminal>(SceneObject::CITYVOTETERMINAL);

	objectFactory.registerObject<LairObject>(SceneObject::LAIR);

	objectFactory.registerObject<Deed>(SceneObject::DEED);
	objectFactory.registerObject<BuildingDeed>(SceneObject::BUILDINGDEED);
	objectFactory.registerObject<InstallationDeed>(SceneObject::INSTALLATIONDEED);

	objectFactory.registerObject<GroupObject>(SceneObject::GROUPOBJECT);

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

	objectFactory.registerObject<FactoryCrate>(SceneObject::FACTORYCRATE);
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
	if (!((ManagedObject*)object)->isPersistent())
		return 1;

	try {
		ManagedObject* managedObject = ((ManagedObject*)object);
		ObjectOutputStream objectData(500);

		((ManagedObject*)object)->writeObject(&objectData);

		uint64 oid = object->_getObjectID();

		uint32 lastSaveCRC = managedObject->getLastCRCSave();

		uint32 currentCRC = BaseProtocol::generateCRC(&objectData);

		if (lastSaveCRC == currentCRC)
			return 1;

		ObjectDatabase* database = getTable(oid);

		if (database != NULL) {
			StringBuffer msg;
			String dbName;

			database->getDatabaseName(dbName);

			msg << "saving to database with table " << dbName << " and object id 0x" << hex << oid;
			info(msg.toString());

			database->putData(oid, &objectData, object);

			managedObject->setLastCRCSave(currentCRC);
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

		object->setServerObjectCRC(objectCRC);
		object->loadTemplateData(templateData);

	} catch (Exception& e) {
		error("exception caught in SceneObject* ObjectManager::loadObjectFromTemplate(uint32 objectCRC)");
		error(e.getMessage());

		e.printStackTrace();
	} catch (...) {
		error("unreported exception caught in SceneObject* ObjectManager::loadObjectFromTemplate(uint32 objectCRC)");
	}

	return object;
}

SceneObject* ObjectManager::cloneObject(SceneObject* object) {
	ObjectOutputStream objectData(500);

	((ManagedObject*)object)->writeObject(&objectData);
	objectData.reset();

	ObjectInputStream objectInput;
	objectData.copy(&objectInput, 0);
	objectInput.reset();

	uint32 serverCRC = object->getServerObjectCRC();

	SceneObject* clonedObject = NULL;

	ObjectDatabase* database = getTable(object->getObjectID());
	String databaseName;

	if (database != NULL) {
		database->getDatabaseName(databaseName);
	}

	if (object->isPersistent()) {
		clonedObject = createObject(serverCRC, object->getPersistenceLevel(), databaseName);
	} else {
		clonedObject = createObject(serverCRC, 0, databaseName);
	}

	Locker locker(clonedObject);

	clonedObject->readObject(&objectInput);

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
	Locker _locker(object);

	try {
		object->readObject(data);

		if (object->isPersistent())
			object->queueUpdateToDatabaseTask();

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
		error("could not deserialize object from DB");
	} catch (...) {
		error("could not deserialize object from DB");
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

		object->notifyLoadFromDatabase();

	} catch (Exception& e) {
		error(e.getMessage());
		e.printStackTrace();
		error("could not deserialize object from DB");
	} catch (...) {
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

int ObjectManager::destroyObjectFromDatabase(uint64 objectID) {
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
