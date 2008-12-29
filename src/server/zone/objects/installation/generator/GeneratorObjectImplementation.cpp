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

	objectCRC = deed->getTargetFile().hashCode();
	name = deed->getTargetName();
	file = deed->getTargetFile();
	templateName = deed->getTargetTemplate();

	setSurplusMaintenance(deed->getSurplusMaintenance());
	setMaintenanceRate(deed->getMaintenanceRate());
	setHopperSizeMax(deed->getHopperSize());
	setExtractionRate(deed->getExtractionRate());
}

GeneratorObjectImplementation::~GeneratorObjectImplementation(){
}

void GeneratorObjectImplementation::init() {
	objectSubType = TangibleObjectImplementation::GENERATOR;

	operating = 0;
}

