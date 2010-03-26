/*
 * BazaarTerminalImplementation.cpp
 *
 *  Created on: 14/03/2010
 *      Author: victor
 */

#include "BazaarTerminal.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/Zone.h"
#include "AuctionItem.h"

void BazaarTerminalImplementation::initializeTransientMembers() {
	TerminalImplementation::initializeTransientMembers();

	PlanetManager* planetManager = zone->getPlanetManager();
	Region* region = planetManager->getRegion(bazaarRegion);
	region->addBazaar(_this);

	auctions.setNullValue(NULL);
	auctions.setNoDuplicateInsertPlan();

	Logger::setLoggingName("BazaarTerminal");
}
