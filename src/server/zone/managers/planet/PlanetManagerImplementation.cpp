/*
 * PlanetManagerImplementation.cpp
 *
 *  Created on: 30/01/2010
 *      Author: victor
 */

#include "PlanetManager.h"
#include "server/zone/objects/terrain/PlanetNames.h"
#include "server/db/ServerDatabase.h"
#include "server/zone/Zone.h"
#include "server/zone/managers/structure/StructureManager.h"

void PlanetManagerImplementation::initialize() {
	loadRegions();

	terrainManager = new TerrainManager();

	int zoneID = zone->getZoneID();

	if (zoneID < 10) {
		String planetName = Planet::getPlanetName(zoneID);

		terrainManager->initialize("planets/" + planetName + "/" + planetName + ".trn");
	}

	structureManager = new StructureManager(zone, server);
	structureManager->loadStructures();
}

void PlanetManagerImplementation::loadRegions() {
	int zoneID = zone->getZoneID();

	String managerName = "PlanetManager ";
	setLoggingName(managerName + Planet::getPlanetName(zoneID));

	if (zoneID > 9)
		return;

	ResultSet* result = NULL;

	try {
		StringBuffer query;
		query << "SELECT * from clientregion_" << Planet::getPlanetName(zoneID);

		result = ServerDatabase::instance()->executeQuery(query);

		while (result->next()) {
			String fullName = result->getString(0);

			float x = result->getFloat(1);
			float y = result->getFloat(2);
			float radius = result->getFloat(3);

			regionMap.addRegion(fullName, x, y, radius);
		}
	} catch (DatabaseException& e) {
		error(e.getMessage());
	} catch (...) {
		error("unknown exception caught in void PlanetManagerImplementation::loadRegions()");
	}

	delete result;

	if (regionMap.size() != 0) {
		StringBuffer msg;
		msg << "loaded " << regionMap.size() << " client regions";
		info(msg.toString(), true);
	}
}

void PlanetManagerImplementation::initializeTransientMembers() {
	ManagedObjectImplementation::initializeTransientMembers();

	terrainManager = new TerrainManager();
}


void PlanetManagerImplementation::finalize() {
	delete terrainManager;
	terrainManager = NULL;
}

