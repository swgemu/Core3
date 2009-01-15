/*
 * FactoryObjectImplementation.cpp
 *
 *  Created on: Oct 18, 2008
 *      Author: swgemu
 */

#include "../../../ZoneClientSession.h"
#include "../../player/Player.h"
#include "../../../Zone.h"
#include "../../../packets.h"
#include "../../../objects.h"

#include "FactoryObjectImplementation.h"


FactoryObjectImplementation::FactoryObjectImplementation(uint64 oid) : FactoryObjectServant(oid) {
	objectID = oid;

	//(InstallationObject*)_this
	InstallationObjectImplementation::init();
	init();
}


FactoryObjectImplementation::FactoryObjectImplementation(uint64 oid, FactoryDeed* deed) : FactoryObjectServant(oid, deed) {
	objectID = oid;

	InstallationObjectImplementation::init();
	init();

	objectCRC = deed->getTargetFile().hashCode();
	customName = deed->getTargetName();
	file = deed->getTargetFile();
	templateName = deed->getTargetTemplate();


	setSurplusMaintenance(deed->getSurplusMaintenance());
	setMaintenanceRate(deed->getMaintenanceRate());
	setSurplusPower(deed->getSurplusPower());
	setPowerRate(getMaintenanceRate());
	setHopperSizeMax(deed->getHopperSize());
}

FactoryObjectImplementation::~FactoryObjectImplementation(){

}

void FactoryObjectImplementation::init() {
	objectSubType = TangibleObjectImplementation::FACTORY;

	operating = 0;
}

int FactoryObjectImplementation::getFactoryType() {
	switch(objectCRC) {
		default:
			return 0;
	}
}
