/*
 * GeneratorObjectImplementation.cpp
 *
 *  Created on: Oct 18, 2008
 *      Author: swgemu
 */

#include "../../../ZoneClientSession.h"
#include "../../player/Player.h"
#include "../../../Zone.h"
#include "../../../packets.h"
#include "../../../objects.h"

#include "GeneratorObjectImplementation.h"


GeneratorObjectImplementation::GeneratorObjectImplementation(uint64 oid) : GeneratorObjectServant(oid) {
	objectID = oid;

	InstallationObjectImplementation::init();
	init();
}


GeneratorObjectImplementation::GeneratorObjectImplementation(uint64 oid, GeneratorDeed* deed) : GeneratorObjectServant(oid, deed) {
	objectID = oid;

	InstallationObjectImplementation::init();
	init();

	objectCRC = String::hashCode(deed->getTargetFile());
	name = deed->getTargetName();
	file = deed->getTargetFile();
	templateName = deed->getTargetTemplate();


	maintenance = deed->getSurplusMaintenance();
	maintenanceRate = deed->getMaintenanceRate();
	hopperSizeMax = deed->getHopperSize();
	specRate = deed->getExtractionRate();
}

GeneratorObjectImplementation::~GeneratorObjectImplementation(){

}

void GeneratorObjectImplementation::init() {
	objectSubType = TangibleObjectImplementation::GENERATOR;

	operating = 0;
}

