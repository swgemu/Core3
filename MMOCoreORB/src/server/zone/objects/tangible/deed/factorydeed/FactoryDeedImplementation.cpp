#include "../../../player/Player.h"
#include "../../../../packets.h"

#include "FactoryDeed.h"
#include "FactoryDeedImplementation.h"
#include "../DeedObject.h"
#include "../DeedObjectImplementation.h"

FactoryDeedImplementation::FactoryDeedImplementation(CreatureObject* creature, uint32 tempcrc, const UnicodeString& n, const String& tempn)
	: FactoryDeedServant(creature->getNewItemID(), tempcrc, n, tempn, TangibleObjectImplementation::INSTALLATIONDEED) {
	objectCRC = tempcrc;

	name = n;
	templateName = tempn;

	init();
}

FactoryDeedImplementation::FactoryDeedImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn)
	: FactoryDeedServant(objid, tempcrc, n, tempn, TangibleObjectImplementation::INSTALLATIONDEED) {
	objectID = objid;

	objectCRC = tempcrc;

	name = n;
	templateName = tempn;

	init();
}

FactoryDeedImplementation::~FactoryDeedImplementation() {
}

void FactoryDeedImplementation::parseItemAttributes() {
	DeedObjectImplementation::parseItemAttributes();

	String attr = "surplusMaintenance";
	setSurplusMaintenance(itemAttributes->getIntAttribute(attr));

	attr = "surplusPower";
	setSurplusPower(itemAttributes->getIntAttribute(attr));

	attr = "maintenanceRate";
	setMaintenanceRate(itemAttributes->getFloatAttribute(attr));

	attr = "hopperSize";
	setHopperSize(itemAttributes->getFloatAttribute(attr));

	attr = "lotSize";
	setLotSize(itemAttributes->getIntAttribute(attr));
}

void FactoryDeedImplementation::addAttributes(AttributeListMessage* alm) {
	addHeaderAttributes(alm);

	alm->insertAttribute("examine_maintenance", (int) getSurplusMaintenance());
	alm->insertAttribute("examine_maintenance_rate", (float) getMaintenanceRate());
	alm->insertAttribute("examine_power", (int) getSurplusPower());
	alm->insertAttribute("examine_hoppersize", (float) getHopperSize());

	addFooterAttributes(alm);
}

void FactoryDeedImplementation::init() {
	objectSubType = TangibleObjectImplementation::INSTALLATIONDEED;
	setLotSize(1); // All Harvesters/Generators/Factories

	targetTempFile = "object/installation/base/shared_construction_installation_base.iff";

	if (templateName.indexOf("clothing") != -1){
		type = WEARABLES;

		targetTemplate = "clothing_factory";
		targetFile = "object/installation/manufacture/shared_clothing_factory.iff";

		targetName = String("Clothing Factory");
	} else if (templateName.indexOf("food") != -1){
		type = FOOD;

		targetTemplate = "food_factory";
		targetFile = "object/installation/manufacture/shared_food_factory.iff";

		targetName = String("Food Factory");
	} else if (templateName.indexOf("structure") != -1){
		type = STRUCTURE;

		targetTemplate = "structure_factory";
		targetFile = "object/installation/manufacture/shared_structure_factory.iff";

		targetName = String("Structure Factory");
	} else {
		type = EQUIPMENT;

		targetTemplate = "weapon_factory";
		targetFile = "object/installation/manufacture/shared_weapon_factory.iff";

		targetName = String("Equipment Factory");
	}
}

