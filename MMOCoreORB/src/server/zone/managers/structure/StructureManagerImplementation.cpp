/*
 * StructureManagerImplementation.cpp
 *
 *  Created on: Oct 25, 2008
 *      Author: swgemu
 */


#include "events/StructureManagerSaveStateEvent.h"
#include "events/InstallationSpawnEvent.h"
#include "events/TempInstallationSpawnEvent.h"
#include "events/TempInstallationDespawnEvent.h"

#include "StructureManagerImplementation.h"

#include "../../ZoneProcessServerImplementation.h"

#include "../../objects.h"


StructureManagerImplementation::StructureManagerImplementation(Zone* zone, ZoneProcessServerImplementation* server) : StructureManagerServant(), Logger("StructureManager") {
	StructureManagerImplementation::zone = zone;
	StructureManagerImplementation::server = server;

	buildingMap = new BuildingMap(10000);
	cellMap = new CellMap(10000);
	installationMap = new InstallationMap(1000);

	stringstream loggingname;
	loggingname << "StructureManager " << zone->getZoneID();
	setLoggingName(loggingname.str());

	setLogging(false);
	setGlobalLogging(true);
}

StructureManagerImplementation::~StructureManagerImplementation() {
	if (structureManagerSaveStateEvent != NULL) {
		if (structureManagerSaveStateEvent->isQueued())
			server->removeEvent(structureManagerSaveStateEvent);

		delete structureManagerSaveStateEvent;
		structureManagerSaveStateEvent = NULL;
	}

	if (installationMap != NULL) {
		delete installationMap;
		installationMap = NULL;
	}

	if(cellMap != NULL) {
		delete cellMap;
		cellMap = NULL;
	}

	if(buildingMap != NULL) {
		delete buildingMap;
		buildingMap = NULL;
	}
}

void StructureManagerImplementation::init() {
	info("StructureManagerImplementation::init()");

	structureManagerSaveStateEvent = NULL;
	initializeEvents();

	server->addEvent(structureManagerSaveStateEvent, 100000); // 300000
}

void StructureManagerImplementation::initializeEvents() {
	if (structureManagerSaveStateEvent == NULL)
		structureManagerSaveStateEvent = new StructureManagerSaveStateEvent(_this);
	else
		structureManagerSaveStateEvent->setStructureManager(_this);

}

void StructureManagerImplementation::loadStructures() {
	init();

	info("Loading Structures for zone: " + zone->getZoneID());
	loadStaticBuildings();
	loadPlayerStructures(); // loads both buildings + installations

}

void StructureManagerImplementation::unloadStructures() {
	saveStructures();

	clearBuildings(); // handles both static + player
	clearInstallations();
}

void StructureManagerImplementation::saveStructures(bool doSchedule) {
	saveBuildings();
	saveInstallations();

	if (structureManagerSaveStateEvent == NULL)
		return;

	if (doSchedule) {
		structureManagerSaveStateEvent->setStructureManager(_this);
		server->addEvent(structureManagerSaveStateEvent, 300000);
	} else {
		if (structureManagerSaveStateEvent->isQueued())
			server->removeEvent(structureManagerSaveStateEvent);
		structureManagerSaveStateEvent->setStructureManager(NULL);
	}

}

void StructureManagerImplementation::loadStaticBuildings() {
	int planetid = zone->getZoneID();

	//lock();

	stringstream query;
	query << "SELECT * FROM staticobjects WHERE zoneid = " << planetid << ";";

	try {
		ResultSet* result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			uint64 oid = result->getUnsignedLong(1);

			uint64 parentId = result->getUnsignedLong(2);

			string file = result->getString(3);

			float oX = result->getFloat(4);
			float oY = result->getFloat(5);
			float oZ = result->getFloat(6);
			float oW = result->getFloat(7);

			float x = result->getFloat(8);
			float z = result->getFloat(9);
			float y = result->getFloat(10);

			float type = result->getFloat(11);

			if ((int) file.find("object/cell/") >= 0) {
				BuildingObject* buio = buildingMap->get(parentId);

				if (buio == NULL)
					buio = loadStaticBuilding(parentId, planetid);

				CellObject* cell = new CellObject(oid, buio);

				cell->setObjectCRC(String::hashCode(file));
				cell->initializePosition(x, z, y);
				cell->setDirection(oX, oZ, oY, oW);

				cell->setZoneProcessServer(server);
				zone->registerObject(cell);

				buio->addCell(cell);

				if (cellMap->put(oid, cell) != NULL) {
					error("Error CELL/BUILDING already exists\n");
					raise(SIGSEGV);
				}
			}
		}

		delete result;
	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in PlanetManagerImplementation::loadStaticBuildings()\n");
	}

	//unlock();
}

BuildingObject* StructureManagerImplementation::loadStaticBuilding(uint64 oid, int planet) {
	BuildingObject* buio = NULL;

	stringstream query;
	query << "SELECT * FROM staticobjects WHERE zoneid = '" << planet << "' AND objectid = '" << oid << "';";

	try {
		ResultSet* result = ServerDatabase::instance()->executeQuery(query);

		if (result->next()) {
			uint64 oid = result->getUnsignedLong(1);
			uint64 parentId = result->getUnsignedLong(2);

			string file = result->getString(3);

			float oX = result->getFloat(4);
			float oY = result->getFloat(5);
			float oZ = result->getFloat(6);
			float oW = result->getFloat(7);

			float x = result->getFloat(8);
			float z = result->getFloat(9);
			float y = result->getFloat(10);

			float type = result->getFloat(11);

			buio = new BuildingObject(oid, true);
			buio->setZoneProcessServer(server);

			buio->setObjectCRC(String::hashCode(file));

			buio->setBuildingType(guessBuildingType(oid, file));

			buio->initializePosition(x, z, y);
			buio->setDirection(oX, oZ, oY, oW);
			buio->setPersistent(true); // static = persistent - don't save
			buio->setUpdated(false); // static = persistent
			buio->insertToZone(zone);

			if (buildingMap->put(oid, buio) != NULL) {
				error("Error CELL/BUILDING already exists\n");
				raise(SIGSEGV);
			}
		}

		delete result;
	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (...) {
		error("unreported exception caught in PlanetManagerImplementation::loadStaticBuilding");
	}

	return buio;
}

void StructureManagerImplementation::loadPlayerStructures() {

	info("Loading Player Structures");

	try {
	int planetid = zone->getZoneID();

	stringstream query;
	query << "SELECT character_structures.*, characters.firstname, characters.surname FROM character_structures inner join characters on character_structures.owner_id = characters.character_id WHERE zoneid = " << planetid << " and deleted = 0 and parent_id = 0;";
	ResultSet* result = ServerDatabase::instance()->executeQuery(query.str());

/*	sqlInsertStructure << "INSERT into `character_structures` (zone_id, object_id, parent_id, owner_id, name, "
	<< "`template_crc`,`template_type`,`template_subtype`,`template_name`, oX, oY, oZ, oW, X, Z, Y, deleted, attributes, noBuildArea) "*/

	while (result->next()) {
		info("Player Structure Result");
		int zone_id = result->getInt(0);

		uint64 oid = result->getUnsignedLong(1);
		uint64 parentId = result->getUnsignedLong(2);
		int cellNumber = result->getUnsignedLong(3);
		uint64 ownerId = result->getUnsignedLong(4);
		string name = result->getString(5);
		uint64 crc = result->getUnsignedLong(6);
		uint64 type = result->getUnsignedLong(7);
		uint64 subType = result->getUnsignedLong(8);
		string tempname = result->getString(9);

		float oX = result->getFloat(10);
		float oY = result->getFloat(11);
		float oZ = result->getFloat(12);
		float oW = result->getFloat(13);

		float x = result->getFloat(14);
		float z = result->getFloat(15);
		float y = result->getFloat(16);

		// deleted (17)
		string attributes = result->getString(18);
		uint64 noBuildAreaUID = result->getUnsignedLong(19);

		string ownerFirstName = result->getString(20);
		string ownerSurname = result->getString(21);

		string owner = ownerFirstName + " " + ownerSurname;

		switch(type) {
			case SceneObjectImplementation::BUILDING: {
				info("building");

				BuildingObject* buio = new BuildingObject(oid, false);
				buio->setZoneProcessServer(server);

				buio->setObjectCRC(crc);
				buio->setObjectType(type);
				buio->setName(name);
				buio->initializePosition(x, z, y);
				buio->setDirection(oX, oZ, oY, oW);
				buio->setPersistent(true); // we loaded it so it must be persistent
				buio->setUpdated(false); // doesn't need updates

				buio->setAttributes(attributes);
				buio->parseItemAttributes();

				// Load Cells
				loadPlayerCells(buio);

				buio->insertToZone(zone);
				//zone->registerObject(buio); ?
				buildingMap->put(oid, buio);

				break;
			}
			case SceneObjectImplementation::TANGIBLE: {

				info("tangible");
				if(!(subType & TangibleObjectImplementation::INSTALLATION))
						break;

				InstallationObject* inso;
				switch(subType) {
					case TangibleObjectImplementation::FACTORY:
						inso = new FactoryObject(oid);
						break;
					case TangibleObjectImplementation::GENERATOR:
						inso = new GeneratorObject(oid);
						break;
					case TangibleObjectImplementation::HARVESTER:
						info("harvester");
						inso = new HarvesterObject(oid);
						break;
					case TangibleObjectImplementation::TURRET:
					case TangibleObjectImplementation::MINEFIELD:
					default: // Installation
						inso = new InstallationObject(oid);
						break;
				}

				inso->setZoneProcessServer(server);
				inso->setObjectCRC(crc);
				inso->setObjectType(type);
				inso->setObjectSubType(subType);
				inso->setName(name);
				inso->initializePosition(x, z, y);
				inso->setDirection(oX, oZ, oY, oW);
				inso->setPersistent(true); // we loaded it so it must be persistent
				inso->setUpdated(false); // doesn't need updates

				inso->setAttributes(attributes);
				inso->parseItemAttributes();

				inso->insertToZone(zone);
				zone->registerObject(inso);
				installationMap->put(oid, inso);
				break;
			}
			default:
				info("default");
				break;
		}

		/*
		if ((int) file.find("object/building/") >= 0) {
		} else if ((int)file.find("object/cell/") >= 0) {
			BuildingObject* buio = buildingMap->get(parentId);

			if (buio == NULL)
				buio = loadBuilding(parentId, planetid);

			CellObject* cell = new CellObject(oid, buio);

			cell->setObjectCRC(String::hashCode(file));
			cell->initializePosition(x, z, y);
			cell->setDirection(oX, oZ, oY, oW);
			//cell->insertToZone(zone);
			zone->registerObject(cell);

			buio->addCell(cell);
			buio->setAssociatedArea(noBuildAreaUID);
			cellMap->put(oid, cell);
		} else if ((int)file.find("object/installation/") >= 0) {

		}*/
	}

	delete result;
	} catch (DatabaseException& e) {
		stringstream err;
		err << "Loading Player Structures, exception: " << e.getMessage();
		error(err);
		return;
	} catch (...) {
		throw Exception("problem in StructureManagerImplementation::loadPlayerStructures()");
	}


}


void StructureManagerImplementation::createPlayerCells(Player * player, BuildingObject * buio, int cellCount) {

	for(int i = 1; i <= cellCount; ++i){
		// Get new cell object ID
		uint64 oid = player->getNewItemID();

		CellObject* cell = new CellObject(oid, buio, i); // server->getZoneServer()->getNextCellID()

		cell->setObjectCRC(String::hashCode("object/cell/shared_cell.iff"));
		cell->initializePosition(0, 0, 0);
		cell->setDirection(0, 0, 0, 1); // void SceneObject::setDirection(float x, float z, float y, float w) {
		cell->setCellNumber(i);
		//cell->insertToZone(zone);
		zone->registerObject(cell);

		buio->addCell(cell);
		cellMap->put(oid, cell);
	}

}


void StructureManagerImplementation::loadPlayerCells(BuildingObject * buio) {

	try {
		stringstream query;
		query << "SELECT character_structures.*, characters.firstname, characters.surname FROM character_structures inner join characters on character_structures.owner_id = characters.character_id WHERE parent_id = " << buio->getObjectID() << " and deleted = 0 order by cell_number asc;";

		info(query.str());
		ResultSet* result = ServerDatabase::instance()->executeQuery(query.str());

		int i = 1;
		while (result->next()) {
			info("Player Cell Result");
			int zone_id = result->getInt(0);

			uint64 oid = result->getUnsignedLong(1);
			uint64 parentId = result->getUnsignedLong(2);
			int cellNumber = result->getUnsignedLong(3);
			uint64 ownerId = result->getUnsignedLong(4);
			string name = result->getString(5);
			uint64 crc = result->getUnsignedLong(6);
			string tempname = result->getString(7);

			float oX = result->getFloat(8);
			float oY = result->getFloat(9);
			float oZ = result->getFloat(10);
			float oW = result->getFloat(11);

			float x = result->getFloat(12);
			float z = result->getFloat(13);
			float y = result->getFloat(14);

			// deleted (15)
			string attributes = result->getString(16);
			uint64 noBuildAreaUID = result->getUnsignedLong(17);

			string ownerFirstName = result->getString(18);
			string ownerSurname = result->getString(19);

			string owner = ownerFirstName + " " + ownerSurname;

			// Get new cell object ID
			CellObject* cell = new CellObject(oid, buio, i); // server->getZoneServer()->getNextCellID()

			cell->setObjectCRC(String::hashCode("object/cell/shared_cell.iff"));
			cell->initializePosition(0, 0, 0);
			cell->setDirection(0, 0, 0, 1); // void SceneObject::setDirection(float x, float z, float y, float w) {
			cell->setCellNumber(i);

			cell->setAttributes(attributes);
			cell->parseItemAttributes();

			//cell->insertToZone(zone);
			zone->registerObject(cell);

			buio->addCell(cell);
			cellMap->put(oid, cell);
			i++;
		}
		delete result;
	} catch (DatabaseException& e) {
		stringstream err;
		err << "Loading Cell Structures, exception: " << e.getMessage();
		error(err);
		return;
	} catch (...) {
		throw Exception("problem in StructureManagerImplementation::loadPlayerCells()");
	}
}

BuildingObject* StructureManagerImplementation::findBuildingType(const string& word, float targetX, float targetY) {
	//lock();

	uint16 accumDistance, distance = 32768;
	BuildingObject* buiID = 0;

	buildingMap->resetIterator();

	while (buildingMap->hasNext()) {
		BuildingObject* building = buildingMap->next();

		if (word == "starport" && building->getBuildingType() == BuildingObjectImplementation::STARPORT) {
			accumDistance= static_cast<uint16>(fabs( (targetX - building->getPositionX() ) + (targetY - building->getPositionY()) ));

			if ( accumDistance < distance) {
				distance = accumDistance;
				buiID = building;
			}
		}

		if (word == "cloner" && building->getBuildingType() == BuildingObjectImplementation::CLONING_FACILITY) {
			accumDistance= static_cast<uint16>(fabs( (targetX - building->getPositionX() ) + (targetY - building->getPositionY()) ));

			if ( accumDistance < distance) {
				distance = accumDistance;
				buiID = building;
			}
		}

		if (word == "shuttle" && building->getBuildingType() == BuildingObjectImplementation::SHUTTLEPORT) {
			accumDistance= static_cast<uint16>(fabs( (targetX - building->getPositionX() ) + (targetY - building->getPositionY()) ));

			if ( accumDistance < distance) {
				distance = accumDistance;
				buiID = building;
			}
		}

		if (word == "HOTEL" && building->getBuildingType() == BuildingObjectImplementation::HOTEL) {
			accumDistance= static_cast<uint16>(fabs( (targetX - building->getPositionX() ) + (targetY - building->getPositionY()) ));

			if ( accumDistance < distance) {
				distance = accumDistance;
				buiID = building;
			}
		}

		if (word == "bank" && building->getBuildingType() == BuildingObjectImplementation::BANK) {
			accumDistance= static_cast<uint16>(fabs( (targetX - building->getPositionX() ) + (targetY - building->getPositionY()) ));

			if ( accumDistance < distance) {
				distance = accumDistance;
				buiID = building;
			}
		}

		if (word == "garage" && building->getBuildingType() == BuildingObjectImplementation::GARAGE) {
			accumDistance= static_cast<uint16>(fabs( (targetX - building->getPositionX() ) + (targetY - building->getPositionY()) ));

			if ( accumDistance < distance) {
				distance = accumDistance;
				buiID = building;
			}
		}

		if (word == "medical" && building->getBuildingType() == BuildingObjectImplementation::MEDICAL_CENTER) {
			accumDistance= static_cast<uint16>(fabs( (targetX - building->getPositionX() ) + (targetY - building->getPositionY()) ));

			if ( accumDistance < distance) {
				distance = accumDistance;
				buiID = building;
			}
		}

		if (word == "salon" && building->getBuildingType() == BuildingObjectImplementation::SALON) {
			accumDistance= static_cast<uint16>(fabs( (targetX - building->getPositionX() ) + (targetY - building->getPositionY()) ));

			if ( accumDistance < distance) {
				distance = accumDistance;
				buiID = building;
			}
		}
	}

	//unlock();

	return buiID;
}


int StructureManagerImplementation::guessBuildingType(uint64 oid, string file) {
	// Special buildings
	switch (oid)
	{
	// Cantinas
	case 1076941: // Tatooine	Mos Eisley	Cantina (Lucky Despot)
		return BuildingObjectImplementation::CANTINA;
	case 1153495: // Tatooine	Mos Entha	Cantina (The Fallen Star)
		return BuildingObjectImplementation::CANTINA;
	case 3355385: // Tatooine - Anchorhead Cantina
		return BuildingObjectImplementation::CANTINA;
	case 9925364: // Endor - Research Outpost Cantina
		return BuildingObjectImplementation::CANTINA;
	case 6645602: // Endor - Smuggler's Outpost Cantina
		return BuildingObjectImplementation::CANTINA;
	case 1028489: // Tatooine - Bestine Cantina
		return BuildingObjectImplementation::CANTINA;
	case 3035375: // Yavin IV - Labor Outpost Cantina
		return BuildingObjectImplementation::CANTINA;
	case 7925448: // Yavin IV - Mining Outpost Cantina
		return BuildingObjectImplementation::CANTINA;

		// Taverns
	case 6205563: // Dantooine	Mining Outpost	Tavern
		return BuildingObjectImplementation::TAVERN;
	case 6205495: // Dantooine	Pirate Outpost	Tavern
		return BuildingObjectImplementation::TAVERN;
	case 1213343: // Tatooine	Anchorhead	Tavern
		return BuildingObjectImplementation::TAVERN;
	case 1154120: // Tatooine	Mos Taike	Tavern
		return BuildingObjectImplementation::TAVERN;
	case 6955366: // Dathomir	Trade Outpost	Tavern
		return BuildingObjectImplementation::TAVERN;

		// Medical Centers
	case 1414856: // Endor	Smuggler's Outpost	Medical Center
		return BuildingObjectImplementation::MEDICAL_CENTER;
	case 1414867: // Endor	Research Outpost	Medical Center
		return BuildingObjectImplementation::MEDICAL_CENTER;
	case 2835549: // Dathomir	Science Outpost	Medical Center
		return BuildingObjectImplementation::MEDICAL_CENTER;
	case 3035371: // Yavin IV	Labor Outpost	Medical Center
		return BuildingObjectImplementation::MEDICAL_CENTER;
	case 7925474: // Yavin IV	Mining Outpost	Medical Center
		return BuildingObjectImplementation::MEDICAL_CENTER;

		// Museum
	case 1028167: //Tatooine	Bestine	Museum
		return BuildingObjectImplementation::MUSEUM;

		// Junk Shop
	case 1255995: // Tatooine	Mos Espa	Watto�s Junk Shop
		return BuildingObjectImplementation::JUNKSHOP;
	}

	if ((int) file.find("_cantina_") >= 0)
		return BuildingObjectImplementation::CANTINA;
	if ((int) file.find("_cloning_") >= 0)
		return BuildingObjectImplementation::CLONING_FACILITY;
	if ((int) file.find("_starport_") >= 0)
		return BuildingObjectImplementation::STARPORT;
	if ((int) file.find("_shuttleport_") >= 0)
		return BuildingObjectImplementation::SHUTTLEPORT;
	if ((int) file.find("_hotel_") >= 0)
		return BuildingObjectImplementation::HOTEL;
	if ((int) file.find("_bank_") >= 0)
		return BuildingObjectImplementation::BANK;
	if ((int) file.find("_capitol_") >= 0)
		return BuildingObjectImplementation::CAPITOL;
	if ((int) file.find("_garage_") >= 0)
		return BuildingObjectImplementation::GARAGE;
	if ((int) file.find("_hospital_") >= 0)
		return BuildingObjectImplementation::MEDICAL_CENTER;
	if ((int) file.find("_guild_university_") >= 0)
		return BuildingObjectImplementation::GUILD_UNIVERSITY;
	if ((int) file.find("_guild_theater_") >= 0)
		return BuildingObjectImplementation::GUILD_THEATER;
	if ((int) file.find("_guild_combat_") >= 0)
		return BuildingObjectImplementation::GUILD_COMBAT;
	if ((int) file.find("_guild_commerce_") >= 0)
		return BuildingObjectImplementation::GUILD_COMMERCE;
	if ((int) file.find("_salon_") >= 0)
		return BuildingObjectImplementation::SALON;
	if ((int) file.find("_barracks_") >= 0)
		return BuildingObjectImplementation::BARRACKS;


	/*BuildingObjectImplementation::SF_REBEL_FORWARD_BASE;
	BuildingObjectImplementation::SF_IMPERIAL_FORWARD_BASE;
	BuildingObjectImplementation::SF_REBEL_MINOR_BASE;
	BuildingObjectImplementation::SF_IMPERIAL_MINOR_BASE;
	BuildingObjectImplementation::SF_REBEL_MAJOR_BASE;
	BuildingObjectImplementation::SF_IMPERIAL_MAJOR_BASE;
	BuildingObjectImplementation::SF_REBEL_HQ;
	BuildingObjectImplementation::SF_IMPERIAL_HQ;
	BuildingObjectImplementation::REBEL_FORWARD_BASE;
	BuildingObjectImplementation::IMPERIAL_FORWARD_BASE;
	BuildingObjectImplementation::REBEL_MINOR_BASE;
	BuildingObjectImplementation::IMPERIAL_MINOR_BASE;
	BuildingObjectImplementation::REBEL_MAJOR_BASE;
	BuildingObjectImplementation::IMPERIAL_MAJOR_BASE;
	BuildingObjectImplementation::REBEL_HQ;
	BuildingObjectImplementation::IMPERIAL_HQ;*/

	return BuildingObjectImplementation::UNKNOWN;
}

void StructureManagerImplementation::clearBuildings() {
	buildingMap->resetIterator();

	while (buildingMap->hasNext()) {
		BuildingObject* building = buildingMap->next();

		building->removeFromZone();
		building->removeUndeploymentEvent();
		building->finalize();
	}

	buildingMap->removeAll();

	info("cleared buildings");
}


void StructureManagerImplementation::saveBuildings() {
	buildingMap->resetIterator();

	while (buildingMap->hasNext()) {
		BuildingObject* buio = buildingMap->next();

		if (!buio->isPersistent()) {
			createBuilding(buio);
		} else if (buio->isUpdated()) {
			saveBuilding(buio);
		}
	}

	info("saved buildings");
}

void StructureManagerImplementation::saveInstallations() {
	installationMap->resetIterator();

	while (installationMap->hasNext()) {
		InstallationObject* inso = installationMap->next();

		if (!inso->isPersistent()) {
			createInstallation(inso);
		} else if (inso->isUpdated()) {
			saveInstallation(inso);
		}
	}

	info("saved installations");
}

void StructureManagerImplementation::clearInstallations() {
	installationMap->resetIterator();

	while (installationMap->hasNext()) {
		InstallationObject* inso = installationMap->next();

		/*if (!inso->isPersistent()) {
			createInstallation(inso);
		} else if (inso->isUpdated()) {
			saveInstallation(inso);
		}*/

		inso->removeFromZone();
		inso->removeUndeploymentEvent();
		inso->finalize();
	}

	installationMap->removeAll();

	info("cleared installations");
}


void StructureManagerImplementation::spawnTempStructure(Player * player,
 	                DeedObject * deed, float x, float z, float y, float oX, float oZ,
 	                float oY, float oW) {
	InstallationObject* inso = new InstallationObject(player->getNewItemID());

	inso->setObjectCRC(String::hashCode(deed->getTargetTempFile()));
	inso->setName(deed->getTargetName());
	inso->setTemplateName(deed->getTargetTemplate());

	inso->initializePosition(x, z, y);
	inso->setDirection(oX, oZ, oY, oW);
	inso->setOwner(player->getFirstName());
	inso->setOwnerID(player->getCharacterID());
	inso->setZoneProcessServer(server);


	tempInstallationSpawnEvent = new TempInstallationSpawnEvent(inso, player->getZone());
	tempInstallationDespawnEvent = new TempInstallationDespawnEvent(inso, player, deed, x, z, y, oX, oZ, oY, oW);

	server->addEvent(tempInstallationSpawnEvent, 100); // trigger spawn now
	server->addEvent(tempInstallationDespawnEvent, 10000); // set despawn for 10 seconds
}

void StructureManagerImplementation::spawnInstallation(Player * player,
	                DeedObject * deed, float x, float z, float y, float oX, float oZ,
 	                float oY, float oW) {
	InstallationObject* inso = new InstallationObject(player->getNewItemID(), deed);


	inso->initializePosition(x, z, y);
	inso->setDirection(oX, oZ, oY, oW);
	inso->setOwner(player->getFirstName());
	inso->setOwnerID(player->getCharacterID());
	inso->setZoneProcessServer(server);

	installationSpawnEvent = new InstallationSpawnEvent(player, inso, player->getZone());
	server->addEvent(installationSpawnEvent, 100);

 	installationMap->put(inso->getObjectID(), inso);
}

void StructureManagerImplementation::spawnHarvester(Player * player,
 	                DeedObject *deed, float x, float z, float y, float oX, float oZ,
 	                float oY, float oW) {
	HarvesterObject*  hino = new HarvesterObject(player->getNewItemID(), (HarvesterDeed*)deed);

 	hino->initializePosition(x, z, y);
 	hino->setDirection(oX, oZ, oY, oW);
 	hino->setOwner(player->getFirstName());
 	hino->setOwnerID(player->getCharacterID());
 	hino->setZoneProcessServer(server);

 	installationSpawnEvent = new InstallationSpawnEvent(player, hino, player->getZone());
 	server->addEvent(installationSpawnEvent, 100);

 	installationMap->put(hino->getObjectID(), hino);
}

void StructureManagerImplementation::spawnBuilding(Player * player,
 	                DeedObject * thedeed, float x, float z, float y, float oX, float oZ,
 	                float oY, float oW) {
	PlayerHouseDeed * deed = (PlayerHouseDeed *) thedeed;
	BuildingObject* buio = new BuildingObject(player->getNewItemID(), false);
	buio->setZoneProcessServer(server);

	buio->setObjectCRC(String::hashCode(deed->getTargetFile()));
	buio->initializePosition(x, z, y);
	buio->setDirection(oX, oZ, oY, oW);
	buio->setOwner(player->getFirstName());
	buio->setOwnerID(player->getCharacterID());

	//zone->registerObject(buio);
	createPlayerCells(player, buio, deed->getCellCount());

	//return;

	buio->insertToZone(zone); // need to do a temp structure
	buildingMap->put(buio->getObjectID(), buio);
}

void StructureManagerImplementation::createInstallation(InstallationObject* inso) {
	try {
		stringstream sqlInsertStructure;
		string itemname = inso->getName().c_str();
		MySqlDatabase::escapeString(itemname);

		string attr = inso->getAttributes();
		MySqlDatabase::escapeString(attr);

		sqlInsertStructure << "INSERT into `character_structures` (zone_id, object_id, parent_id, owner_id, name, "
		<< "`template_crc`,`template_type`,`template_subtype`,`template_name`, oX, oY, oZ, oW, X, Z, Y, attributes, noBuildArea) "
		<< "VALUES (" << inso->getZoneID()
		<< ", " << inso->getObjectID()
		<< ", 0" // parent
		<< ", " << inso->getOwnerID() // owner
		<< ",'\\" << itemname << "'"
		<< ", " << inso->getObjectCRC()
		<< ", " << inso->getObjectType()
		<< ", " << inso->getObjectSubType()
		<< ", " << "'" << inso->getTemplateName() << "'"
		<< ", " << inso->getDirectionX()
		<< ", " << inso->getDirectionY()
		<< ", " << inso->getDirectionZ()
		<< ", " << inso->getDirectionW()
		<< ", " << inso->getPositionX()
		<< ", " << inso->getPositionZ()
		<< ", " << inso->getPositionY()
		<< ", '" << attr << "'"
		<< ", 0)";

		//cout << "installation Insert SQL: " << sqlInsertStructure.str() << endl;
		ServerDatabase::instance()->executeStatement(sqlInsertStructure);

		inso->setPersistent(true);
		inso->setUpdated(false);

	} catch (DatabaseException& e) {
		stringstream err;
		err << "Can't add structure " << inso->getObjectID() << " exception: " << e.getMessage();
		cout << err.str() << endl; // error(err);
		return;
	}
}


void StructureManagerImplementation::saveInstallation(InstallationObject* inso) {
	try {
		stringstream sqlUpdateStructure;
		string itemname = inso->getName().c_str();
		MySqlDatabase::escapeString(itemname);

		string attr = inso->getAttributes();
		MySqlDatabase::escapeString(attr);

		sqlUpdateStructure << "UPDATE `character_structures` SET "
		<< " zone_id = " << inso->getZoneID()
		<< ", parent_id = 0" // parent
		<< ", owner_id = " << inso->getOwnerID() // owner
		<< ", name = '\\" << itemname << "'"
		<< ", template_crc = " << inso->getObjectCRC()
		<< ", template_type = " << inso->getObjectType()
		<< ", template_subtype = " << inso->getObjectSubType()
		<< ", template_name = " << "'" << inso->getTemplateName() << "'"
		<< ", oX = " << inso->getDirectionX()
		<< ", oY = " << inso->getDirectionY()
		<< ", oZ = " << inso->getDirectionZ()
		<< ", oW = " << inso->getDirectionW()
		<< ", X = " << inso->getPositionX()
		<< ", Z = " << inso->getPositionZ()
		<< ", Y = " << inso->getPositionY()
		<< ", attributes = '" << attr << "'"
		<< ", noBuildArea = 0"
		<< " WHERE object_id = " << inso->getObjectID();

		//cout << "installation Update SQL: " << sqlUpdateStructure.str() << endl;
		ServerDatabase::instance()->executeStatement(sqlUpdateStructure);

		inso->setUpdated(false);

	} catch (DatabaseException& e) {
		stringstream err;
		err << "Can't add structure " << inso->getObjectID() << " exception: " << e.getMessage();
		cout << err.str() << endl; // error(err);
		return;
	}
}

void StructureManagerImplementation::deleteInstallation(InstallationObject *inso) {
	try {
		stringstream query;
		query << "update `character_structures` set deleted = " << 1 << " where object_id = " << inso->getObjectID();
		ServerDatabase::instance()->executeStatement(query);

		//cout << query.str() << endl;
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
}

void StructureManagerImplementation::createBuilding(BuildingObject* buio) {

	try {
		stringstream sqlInsertStructure;
		string itemname = buio->getName().c_str();
		MySqlDatabase::escapeString(itemname);

		string attr = buio->getAttributes();
		MySqlDatabase::escapeString(attr);

		sqlInsertStructure << "INSERT into `character_structures` (zone_id, object_id, parent_id, owner_id, name, "
		<< "`template_crc`,`template_type`,`template_name`, oX, oY, oZ, oW, X, Z, Y, attributes, noBuildArea) "
		<< "VALUES (" << buio->getZoneID()
		<< ", " << buio->getObjectID()
		<< ", 0" // parent
		<< ", " << buio->getOwnerID() // owner
		<< ", '" << itemname << "'"
		<< ", " << buio->getObjectCRC()
		<< ", " << buio->getObjectType()
		<< ", '" << buio->getTemplateName() << "'"
		<< ", " << buio->getDirectionX()
		<< ", " << buio->getDirectionY()
		<< ", " << buio->getDirectionZ()
		<< ", " << buio->getDirectionW()
		<< ", " << buio->getPositionX()
		<< ", " << buio->getPositionZ()
		<< ", " << buio->getPositionY()
		<< ", '" << attr << "'"
		<< ", 0)";

		cout << "building Insert SQL: " << sqlInsertStructure.str() << endl;
		ServerDatabase::instance()->executeStatement(sqlInsertStructure);

		buio->setPersistent(true);
		buio->setUpdated(false);

		for(int i=0; i < buio->getCellCount(); i++) {
			CellObject *cell = buio->getCell(i);
			try {
				stringstream sqlInsertStructure;

				string attr = cell->getAttributes();
				MySqlDatabase::escapeString(attr);

				sqlInsertStructure << "INSERT into `character_structures` (object_id, parent_id, cell_number, owner_id, "
				<< "`template_crc`,`template_name`, oX, oY, oZ, oW, X, Z, Y, attributes, noBuildArea) "
				<< "VALUES (" << cell->getObjectID()
				<< ", " << buio->getObjectID() // parent
				<< ", " << (i+1) // cell number
				<< ", " << buio->getOwnerID() // owner
				<< ", " << cell->getObjectCRC()
				<< ", " << "'" << cell->getTemplateName() << "'"
				<< ", " << cell->getDirectionX()
				<< ", " << cell->getDirectionY()
				<< ", " << cell->getDirectionZ()
				<< ", " << cell->getDirectionW()
				<< ", " << cell->getPositionX()
				<< ", " << cell->getPositionZ()
				<< ", " << cell->getPositionY()
				<< ", '" << attr << "'"
				<< ", 0)";

				cout << "cell Insert SQL: " << sqlInsertStructure.str() << endl;
				ServerDatabase::instance()->executeStatement(sqlInsertStructure);
			} catch (DatabaseException& e) {
				stringstream err;
				err << "Can't add cell " << cell->getObjectID() << " exception: " << e.getMessage();
				cout << err.str() << endl; // error(err);
				return;
			}

		}

	} catch (DatabaseException& e) {
		stringstream err;
		err << "Can't add building " << buio->getObjectID() << " exception: " << e.getMessage();
		cout << err.str() << endl; // error(err);
		return;
	}


}


void StructureManagerImplementation::saveBuilding(BuildingObject* buio) {
/*
	try {
		stringstream sqlUpdateStructure;
		string itemname = inso->getName().c_str();
		MySqlDatabase::escapeString(itemname);

		string attr = inso->getAttributes();
		MySqlDatabase::escapeString(attr);

		sqlUpdateStructure << "UPDATE `character_structures` SET "
		<< " zone_id = " << inso->getZoneID()
		<< ", parent_id = 0" // parent
		<< ", owner_id = " << inso->getOwnerID() // owner
		<< ", name = '\\" << itemname << "'"
		<< ", template_crc = " << inso->getObjectCRC()
		<< ", template_type = " << inso->getObjectType()
		<< ", template_subtype = " << inso->getObjectSubType()
		<< ", template_name = " << "'" << inso->getTemplateName() << "'"
		<< ", oX = " << inso->getDirectionX()
		<< ", oY = " << inso->getDirectionY()
		<< ", oZ = " << inso->getDirectionZ()
		<< ", oW = " << inso->getDirectionW()
		<< ", X = " << inso->getPositionX()
		<< ", Z = " << inso->getPositionZ()
		<< ", Y = " << inso->getPositionY()
		<< ", attributes = '" << attr << "'"
		<< ", noBuildArea = 0"
		<< " WHERE object_id = " << inso->getObjectID();

		cout << "installation Update SQL: " << sqlUpdateStructure << endl;
		ServerDatabase::instance()->executeStatement(sqlUpdateStructure);

		inso->setUpdated(false);

	} catch (DatabaseException& e) {
		stringstream err;
		err << "Can't add structure " << inso->getObjectID() << " exception: " << e.getMessage();
		cout << err.str() << endl; // error(err);
		return;
	}
	*/
}

void StructureManagerImplementation::deleteBuilding(BuildingObject *buio) {
	/*
	try {
		stringstream query;
		query << "update `character_structures` set deleted = " << 1 << " where object_id = " << inso->getObjectID();
		ServerDatabase::instance()->executeStatement(query);

		//cout << query.str() << endl;
	} catch (DatabaseException& e) {
		cout << e.getMessage() << "\n";
	}
	*/
}
