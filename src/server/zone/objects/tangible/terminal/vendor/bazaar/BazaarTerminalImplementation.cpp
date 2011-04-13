/*
 * BazaarTerminalImplementation.cpp
 *
 *  Created on: Mar 18, 2011
 *      Author: polonel
 */

#include "BazaarTerminal.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/region/Region.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/auction/AuctionItem.h"

void BazaarTerminalImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	VendorTerminalImplementation::loadTemplateData(templateData);

	vendor.setVendorType(Vendor::BAZAARTERMINAL);
}
