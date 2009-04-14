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


#include "events/StructureManagerSaveStateEvent.h"
#include "events/InstallationSpawnEvent.h"
#include "events/InstallationDespawnEvent.h"
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
	cloningFacilityMap = new CloningFacilityMap(1000);

	StringBuffer loggingname;
	loggingname << "StructureManager " << zone->getZoneID();
	setLoggingName(loggingname.toString());

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

	if (cellMap != NULL) {
		delete cellMap;
		cellMap = NULL;
	}

	if (buildingMap != NULL) {
		delete buildingMap;
		buildingMap = NULL;
	}

	if (cloningFacilityMap != NULL) {
		delete cloningFacilityMap;
		cloningFacilityMap = NULL;
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

	StringBuffer msg;
	msg << "StructureManagerImplementation::loadStructures(), zone: " << zone->getZoneID();
	info(msg.toString());

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

	StringBuffer query;
	query << "SELECT * FROM staticobjects WHERE zoneid = " << planetid << ";";

	try {
		ResultSet* result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			uint64 oid = result->getUnsignedLong(1);

			uint64 parentId = result->getUnsignedLong(2);

			String file = result->getString(3);

			float oX = result->getFloat(4);
			float oY = result->getFloat(5);
			float oZ = result->getFloat(6);
			float oW = result->getFloat(7);

			float x = result->getFloat(8);
			float z = result->getFloat(9);
			float y = result->getFloat(10);

			float type = result->getFloat(11);
			bool client = result->getBoolean(12);

			//info("Loading Structures for zone: " + zone->getZoneID());

			if (file.indexOf("object/cell/") != -1) {
				BuildingObject* buio = buildingMap->get(parentId);

				if (buio == NULL)
					buio = loadStaticBuilding(parentId, planetid);

				StringBuffer msg;
				msg << "StructureManagerImplementation::loadStaticBuildings(), loading cell (" << oid << " for building: " << parentId << endl;
				info(msg.toString());

				CellObject* cell = new CellObject(oid, buio);

				cell->setObjectCRC(file.hashCode());
				cell->initializePosition(x, z, y);
				cell->setDirection(oX, oZ, oY, oW);

				cell->setZoneProcessServer(server);
				zone->registerObject(cell);

				buio->addCell(cell); // sets the cell number - assumes loading in order

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


	StringBuffer msg;
	msg << "Loading Static Building id: " << oid;
	info(msg.toString());

	StringBuffer query;
	query << "SELECT * FROM staticobjects WHERE zoneid = '" << planet << "' AND objectid = '" << oid << "';";

	try {
		ResultSet* result = ServerDatabase::instance()->executeQuery(query);

		if (result->next()) {
			uint64 oid = result->getUnsignedLong(1);
			uint64 parentId = result->getUnsignedLong(2);

			String file = result->getString(3);

			float oX = result->getFloat(4);
			float oY = result->getFloat(5);
			float oZ = result->getFloat(6);
			float oW = result->getFloat(7);

			float x = result->getFloat(8);
			float z = result->getFloat(9);
			float y = result->getFloat(10);

			float type = result->getFloat(11);
			bool client = result->getBoolean(12);

			if (file.indexOf("building") != -1 && file.indexOf("cloning") != -1) {
				CloningFacility* cloningFacility = new CloningFacility(oid, client);
				buio = (BuildingObject*) cloningFacility;

				if (cloningFacilityMap->put(oid, cloningFacility) != NULL) {
					error("Error CloningFacility already exists\n");
					raise(SIGSEGV);
				}
			} else {
				buio = new BuildingObject(oid, client);
			}

			buio->setZoneProcessServer(server);

			buio->setObjectCRC(file.hashCode());
			buio->setBuildingType(guessBuildingType(oid, file));
			//setObjectType
			//setObjectName

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

	StringBuffer msg;
	msg << "StructureManagerImplementation::loadPlayerStructures(), zone: " << zone->getZoneID();
	info(msg.toString());

	try {
	int planetid = zone->getZoneID();

	StringBuffer query;
	query << "SELECT character_structures.*, characters.firstname, characters.surname FROM character_structures inner join characters on character_structures.owner_id = characters.character_id WHERE zoneid = " << planetid << " and deleted = 0 and parent_id = 0;";
	info(query.toString());

	ResultSet* result = ServerDatabase::instance()->executeQuery(query.toString());

/*	sqlInsertStructure << "INSERT into `character_structures` (zone_id, object_id, parent_id, owner_id, name, "
	<< "`template_crc`,`template_type`,`template_subtype`,`template_name`, oX, oY, oZ, oW, X, Z, Y, deleted, attributes, noBuildArea) "*/

	while (result->next()) {
		info("Player Structure Result");
		int zone_id = result->getInt(0);

		uint64 oid = result->getUnsignedLong(1);
		uint64 parentId = result->getUnsignedLong(2);
		int cellNumber = result->getUnsignedLong(3);
		uint64 ownerId = result->getUnsignedLong(4);
		String name = result->getString(5);
		uint64 crc = result->getUnsignedLong(6);
		uint64 type = result->getUnsignedLong(7);
		uint64 subType = result->getUnsignedLong(8);
		String tempname = result->getString(9);

		float oX = result->getFloat(10);
		float oY = result->getFloat(11);
		float oZ = result->getFloat(12);
		float oW = result->getFloat(13);

		float x = result->getFloat(14);
		float z = result->getFloat(15);
		float y = result->getFloat(16);

		// deleted (17)
		String attributes = result->getString(18);
		uint64 noBuildAreaUID = result->getUnsignedLong(19);

		String ownerFirstName = result->getString(20);
		String ownerSurname = result->getString(21);

		String owner = ownerFirstName + " " + ownerSurname;

		switch(type) {
			case SceneObjectImplementation::BUILDING: {
				info("StructureManagerImplementation::loadPlayerStructures(), type = building");

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

				info("StructureManagerImplementation::loadPlayerStructures(), type = tangible");
				if (!(subType & TangibleObjectImplementation::INSTALLATION))
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
				inso->setCustomName(name);

				float height = zone->getHeight(x, y);

				if (height != 0)
					inso->initializePosition(x, height, y);
				else
					inso->initializePosition(x, z, y);

				inso->setDirection(oX, oZ, oY, oW);
				inso->setPersistent(true); // we loaded it so it must be persistent
				inso->setUpdated(false); // doesn't need updates

				inso->setAttributes(attributes);

				inso->insertToZone(zone);

				inso->parseItemAttributes();//needs to be after the insertToZone for factories

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
		StringBuffer err;
		err << "Loading Player Structures, exception: " << e.getMessage();
		error(err);
		return;
	} catch (...) {
		throw Exception("problem in StructureManagerImplementation::loadPlayerStructures()");
	}


}


void StructureManagerImplementation::createPlayerCells(Player * player, BuildingObject * buio, int cellCount) {

	for (int i = 1; i <= cellCount; ++i){
		// Get new cell object ID
		uint64 oid = player->getNewItemID();

		CellObject* cell = new CellObject(oid, buio, i); // server->getZoneServer()->getNextCellID()

		cell->setObjectCRC(String("object/cell/shared_cell.iff").hashCode());
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
		StringBuffer query;
		query << "SELECT character_structures.*, characters.firstname, characters.surname FROM character_structures inner join characters on character_structures.owner_id = characters.character_id WHERE parent_id = " << buio->getObjectID() << " and deleted = 0 order by cell_number asc;";

		info(query.toString());
		ResultSet* result = ServerDatabase::instance()->executeQuery(query.toString());

		int i = 1;
		while (result->next()) {
			info("Player Cell Result");
			int zone_id = result->getInt(0);

			uint64 oid = result->getUnsignedLong(1);
			uint64 parentId = result->getUnsignedLong(2);
			int cellNumber = result->getUnsignedLong(3);
			uint64 ownerId = result->getUnsignedLong(4);
			String name = result->getString(5);
			uint64 crc = result->getUnsignedLong(6);
			String tempname = result->getString(7);

			float oX = result->getFloat(8);
			float oY = result->getFloat(9);
			float oZ = result->getFloat(10);
			float oW = result->getFloat(11);

			float x = result->getFloat(12);
			float z = result->getFloat(13);
			float y = result->getFloat(14);

			// deleted (15)
			String attributes = result->getString(16);
			uint64 noBuildAreaUID = result->getUnsignedLong(17);

			String ownerFirstName = result->getString(18);
			String ownerSurname = result->getString(19);

			String owner = ownerFirstName + " " + ownerSurname;

			// Get new cell object ID
			CellObject* cell = new CellObject(oid, buio, i); // server->getZoneServer()->getNextCellID()

			cell->setObjectCRC(String("object/cell/shared_cell.iff").hashCode());
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
		StringBuffer err;
		err << "Loading Cell Structures, exception: " << e.getMessage();
		error(err);
		return;
	} catch (...) {
		throw Exception("problem in StructureManagerImplementation::loadPlayerCells()");
	}
}

BuildingObject* StructureManagerImplementation::findBuildingType(const String& word, float targetX, float targetY) {
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


int StructureManagerImplementation::guessBuildingType(uint64 oid, String file) {
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
	case 2835569: // Dathomir	Science Outpost	Tavern
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

	if (file.indexOf("_cantina_") != -1)
		return BuildingObjectImplementation::CANTINA;
	if (file.indexOf("_cloning_") != -1)
		return BuildingObjectImplementation::CLONING_FACILITY;
	if (file.indexOf("_starport_") != -1)
		return BuildingObjectImplementation::STARPORT;
	if (file.indexOf("_shuttleport_") != -1)
		return BuildingObjectImplementation::SHUTTLEPORT;
	if (file.indexOf("_hotel_") != -1)
		return BuildingObjectImplementation::HOTEL;
	if (file.indexOf("_bank_") != -1)
		return BuildingObjectImplementation::BANK;
	if (file.indexOf("_capitol_") != -1)
		return BuildingObjectImplementation::CAPITOL;
	if (file.indexOf("_garage_") != -1)
		return BuildingObjectImplementation::GARAGE;
	if (file.indexOf("_hospital_") != -1)
		return BuildingObjectImplementation::MEDICAL_CENTER;
	if (file.indexOf("_guild_university_") != -1)
		return BuildingObjectImplementation::GUILD_UNIVERSITY;
	if (file.indexOf("_guild_theater_") != -1)
		return BuildingObjectImplementation::GUILD_THEATER;
	if (file.indexOf("_guild_combat_") != -1)
		return BuildingObjectImplementation::GUILD_COMBAT;
	if (file.indexOf("_guild_commerce_") != -1)
		return BuildingObjectImplementation::GUILD_COMMERCE;
	if (file.indexOf("_salon_") != -1)
		return BuildingObjectImplementation::SALON;
	if (file.indexOf("_barracks_") != -1)
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

	inso->setObjectCRC(deed->getTargetTempFile().hashCode());
	inso->setCustomName(deed->getTargetName());
	inso->setStfName(deed->getTargetTemplate());

	inso->initializePosition(x, z, y);
	inso->setDirection(oX, oZ, oY, oW);
	inso->setOwner(player->getFirstName());
	inso->setOwnerID(player->getCharacterID());
	inso->setZoneProcessServer(server);

	//remove but do not delete
	player->removeInventoryItem(deed);
	deed->sendDestroyTo(player);

	int lots = player->getLotsRemaining();
	lots -= deed->getLotSize();
	player->setLotsRemaining(lots);

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

 	BaseMessage* msg = new SceneObjectDestroyMessage(deed);
 	player->getClient()->sendMessage(msg);
 	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();
 	if (itemManager != NULL)
 		itemManager->deletePlayerItem(player, deed, false);

 	deed->finalize();
}

void StructureManagerImplementation::spawnHarvester(Player * player,
 	                DeedObject *deed, float x, float z, float y, float oX, float oZ,
 	                float oY, float oW) {
	HarvesterObject*  hino = new HarvesterObject(player->getNewItemID(), (HarvesterDeed*)deed);

	//int size = deed->getSize();

 	hino->initializePosition(x, z, y);
 	hino->setDirection(oX, oZ, oY, oW);
 	hino->setOwner(player->getFirstName());
 	hino->setOwnerID(player->getCharacterID());
 	hino->setZoneProcessServer(server);

 	//hino->setMaintenanceRate(30.0f * size);
 	//hino->setPowerRate(25.0f * size);

 	installationSpawnEvent = new InstallationSpawnEvent(player, hino, player->getZone());
 	server->addEvent(installationSpawnEvent, 100);

 	installationMap->put(hino->getObjectID(), hino);

 	BaseMessage* msg = new SceneObjectDestroyMessage(deed);
 	player->getClient()->sendMessage(msg);
 	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();
 	if (itemManager != NULL)
 		itemManager->deletePlayerItem(player, deed, false);
 	deed->finalize();

 	createInstallation(hino);
}

void StructureManagerImplementation::spawnFactory(Player * player,
 	                DeedObject *deed, float x, float z, float y, float oX, float oZ,
 	                float oY, float oW) {
	FactoryObject* fact = new FactoryObject(player->getNewItemID(), (FactoryDeed*)deed);

	//int size = deed->getSize();

 	fact->initializePosition(x, z, y);
 	fact->setDirection(oX, oZ, oY, oW);
 	fact->setOwner(player->getFirstName());
 	fact->setOwnerID(player->getCharacterID());
 	fact->setZoneProcessServer(server);
 	//hino->setMaintenanceRate(30.0f * size);
 	//hino->setPowerRate(25.0f * size);

 	installationSpawnEvent = new InstallationSpawnEvent(player, fact, player->getZone());
 	server->addEvent(installationSpawnEvent, 100);

 	installationMap->put(fact->getObjectID(), fact);

 	BaseMessage* msg = new SceneObjectDestroyMessage(deed);
	player->getClient()->sendMessage(msg);
	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();
	if (itemManager != NULL)
		itemManager->deletePlayerItem(player, deed, false);
	deed->finalize();

	createInstallation(fact);
}

void StructureManagerImplementation::spawnBuilding(Player * player,
 	                DeedObject * thedeed, float x, float z, float y, float oX, float oZ,
 	                float oY, float oW) {
	PlayerHouseDeed * deed = (PlayerHouseDeed *) thedeed;
	BuildingObject* buio = new BuildingObject(player->getNewItemID(), false);
	buio->setZoneProcessServer(server);

	buio->setObjectCRC(deed->getTargetFile().hashCode());
	buio->initializePosition(x, z, y);
	buio->setDirection(oX, oZ, oY, oW);
	buio->setOwner(player->getFirstName());
	buio->setOwnerID(player->getCharacterID());

	//zone->registerObject(buio);
	createPlayerCells(player, buio, deed->getCellCount());

	//return;

	buio->insertToZone(zone); // need to do a temp structure
	buildingMap->put(buio->getObjectID(), buio);

	BaseMessage* msg = new SceneObjectDestroyMessage(thedeed);
	player->getClient()->sendMessage(msg);
	ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();
	if (itemManager != NULL)
		itemManager->deletePlayerItem(player, thedeed, false);
	thedeed->finalize();
}

void StructureManagerImplementation::createInstallation(InstallationObject* inso) {
	try {
		StringBuffer sqlInsertStructure;
		String itemname = inso->getCustomName().toString();
		MySqlDatabase::escapeString(itemname);

		String attr = inso->getAttributes();
		MySqlDatabase::escapeString(attr);

		sqlInsertStructure << "INSERT into `character_structures` (zone_id, object_id, parent_id, owner_id, name, "
		<< "`template_crc`,`template_type`,`template_subtype`,`template_name`, oX, oY, oZ, oW, X, Z, Y, attributes, noBuildArea) "
		<< "VALUES (" << inso->getZoneID()
		<< ", " << inso->getObjectID()
		<< ", 0" // parent
		<< ", " << inso->getOwnerID() // owner
		<< ",'" << itemname << "'"
		<< ", " << inso->getObjectCRC()
		<< ", " << inso->getObjectType()
		<< ", " << inso->getObjectSubType()
		<< ", " << "'" << inso->getStfName() << "'"
		<< ", " << inso->getDirectionX()
		<< ", " << inso->getDirectionY()
		<< ", " << inso->getDirectionZ()
		<< ", " << inso->getDirectionW()
		<< ", " << inso->getPositionX()
		<< ", " << inso->getPositionZ()
		<< ", " << inso->getPositionY()
		<< ", '" << attr << "'"
		<< ", 0)";

		//System::out << "installation Insert SQL: " << sqlInsertStructure.toString() << endl;
		ServerDatabase::instance()->executeStatement(sqlInsertStructure);

		inso->setPersistent(true);
		inso->setUpdated(false);

	} catch (DatabaseException& e) {
		StringBuffer err;
		err << "Can't add structure " << inso->getObjectID() << " exception: " << e.getMessage();
		System::out << err.toString() << endl; // error(err);
		return;
	}
}


void StructureManagerImplementation::saveInstallation(InstallationObject* inso) {
	try {
		StringBuffer sqlUpdateStructure;
		String itemname = inso->getCustomName().toString();
		MySqlDatabase::escapeString(itemname);

		String attr = inso->getAttributes();
		MySqlDatabase::escapeString(attr);

		sqlUpdateStructure << "UPDATE `character_structures` SET "
		<< " zone_id = " << inso->getZoneID()
		<< ", parent_id = 0" // parent
		<< ", owner_id = " << inso->getOwnerID() // owner
		<< ", name = '" << itemname << "'"
		<< ", template_crc = " << inso->getObjectCRC()
		<< ", template_type = " << inso->getObjectType()
		<< ", template_subtype = " << inso->getObjectSubType()
		<< ", template_name = " << "'" << inso->getStfName() << "'"
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

		//System::out << "installation Update SQL: " << sqlUpdateStructure.toString() << endl;
		ServerDatabase::instance()->executeStatement(sqlUpdateStructure);

		inso->setUpdated(false);

	} catch (DatabaseException& e) {
		StringBuffer err;
		err << "Can't add structure " << inso->getObjectID() << " exception: " << e.getMessage();
		System::out << err.toString() << endl; // error(err);
		return;
	}
}

void StructureManagerImplementation::deleteInstallation(InstallationObject *inso) {
	try {
		StringBuffer query;
		query << "update `character_structures` set deleted = " << 1 << " where object_id = " << inso->getObjectID();
		ServerDatabase::instance()->executeStatement(query);

		//System::out << query.toString() << endl;
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}

	installationMap->remove(inso->getObjectID());

	installationDespawnEvent = new InstallationDespawnEvent(inso);
	server->addEvent(installationDespawnEvent, 100);

}

void StructureManagerImplementation::createBuilding(BuildingObject* buio) {

	try {
		StringBuffer sqlInsertStructure;
		String itemname = buio->getName().toString();
		MySqlDatabase::escapeString(itemname);

		String attr = buio->getAttributes();
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
		<< ", '" << buio->getStfName() << "'"
		<< ", " << buio->getDirectionX()
		<< ", " << buio->getDirectionY()
		<< ", " << buio->getDirectionZ()
		<< ", " << buio->getDirectionW()
		<< ", " << buio->getPositionX()
		<< ", " << buio->getPositionZ()
		<< ", " << buio->getPositionY()
		<< ", '" << attr << "'"
		<< ", 0)";

		System::out << "building Insert SQL: " << sqlInsertStructure.toString() << endl;
		ServerDatabase::instance()->executeStatement(sqlInsertStructure);

		buio->setPersistent(true);
		buio->setUpdated(false);

		for (int i=0; i < buio->getCellCount(); i++) {
			CellObject *cell = buio->getCell(i);
			try {
				StringBuffer sqlInsertStructure;

				String attr = cell->getAttributes();
				MySqlDatabase::escapeString(attr);

				sqlInsertStructure << "INSERT into `character_structures` (object_id, parent_id, cell_number, owner_id, "
				<< "`template_crc`,`template_name`, oX, oY, oZ, oW, X, Z, Y, attributes, noBuildArea) "
				<< "VALUES (" << cell->getObjectID()
				<< ", " << buio->getObjectID() // parent
				<< ", " << (i+1) // cell number
				<< ", " << buio->getOwnerID() // owner
				<< ", " << cell->getObjectCRC()
				<< ", " << "'" << cell->getStfName() << "'"
				<< ", " << cell->getDirectionX()
				<< ", " << cell->getDirectionY()
				<< ", " << cell->getDirectionZ()
				<< ", " << cell->getDirectionW()
				<< ", " << cell->getPositionX()
				<< ", " << cell->getPositionZ()
				<< ", " << cell->getPositionY()
				<< ", '" << attr << "'"
				<< ", 0)";

				System::out << "cell Insert SQL: " << sqlInsertStructure.toString() << endl;
				ServerDatabase::instance()->executeStatement(sqlInsertStructure);
			} catch (DatabaseException& e) {
				StringBuffer err;
				err << "Can't add cell " << cell->getObjectID() << " exception: " << e.getMessage();
				System::out << err.toString() << endl; // error(err);
				return;
			}

		}

	} catch (DatabaseException& e) {
		StringBuffer err;
		err << "Can't add building " << buio->getObjectID() << " exception: " << e.getMessage();
		System::out << err.toString() << endl; // error(err);
		return;
	}


}


void StructureManagerImplementation::saveBuilding(BuildingObject* buio) {
/*
	try {
		StringBuffer sqlUpdateStructure;
		String itemname = inso->getName().toCharArray();
		MySqlDatabase::escapeString(itemname);

		String attr = inso->getAttributes();
		MySqlDatabase::escapeString(attr);

		sqlUpdateStructure << "UPDATE `character_structures` SET "
		<< " zone_id = " << inso->getZoneID()
		<< ", parent_id = 0" // parent
		<< ", owner_id = " << inso->getOwnerID() // owner
		<< ", name = '" << itemname << "'"
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

		System::out << "installation Update SQL: " << sqlUpdateStructure << endl;
		ServerDatabase::instance()->executeStatement(sqlUpdateStructure);

		inso->setUpdated(false);

	} catch (DatabaseException& e) {
		StringBuffer err;
		err << "Can't add structure " << inso->getObjectID() << " exception: " << e.getMessage();
		System::out << err.toString() << endl; // error(err);
		return;
	}
	*/
}

void StructureManagerImplementation::deleteBuilding(BuildingObject *buio) {
	/*
	try {
		StringBuffer query;
		query << "update `character_structures` set deleted = " << 1 << " where object_id = " << inso->getObjectID();
		ServerDatabase::instance()->executeStatement(query);

		//System::out << query.toString() << endl;
	} catch (DatabaseException& e) {
		System::out << e.getMessage() << "\n";
	}
	*/
}


/**
 * Used to get the closest cloning facility that is in the cloningFacilityMap
 * \param player The player to find a close facility in relation to.
 * \return Returns the closest cloning facility found.
 */
CloningFacility* StructureManagerImplementation::getClosestCloningFacility(Player* player) {
	//TODO: Can this be redone to use the quadtree?
	float playerX = player->getPositionX();
	float playerY = player->getPositionY();

	if (player->getParentID() > 0) {
		SceneObject* building = player->getBuilding();
		if (building != NULL) {
			playerX = building->getPositionX();
			playerY = building->getPositionY();
		}
	}

	CloningFacility* closestFacility = NULL;

	float closestDistance = 32768.0f;

	try {
		cloningFacilityMap->lock();

		cloningFacilityMap->resetIterator();

		while (cloningFacilityMap->hasNext()) {
			CloningFacility* facility = cloningFacilityMap->next();

			float dist = sqrt(pow(playerX - facility->getPositionX(), 2) + pow(playerY - facility->getPositionY(), 2));

			if (dist < closestDistance) {
				closestDistance = dist;
				closestFacility = facility;
			}
		}

		cloningFacilityMap->unlock();
	} catch (...) {
		cloningFacilityMap->unlock();
	}

	return closestFacility;
}
