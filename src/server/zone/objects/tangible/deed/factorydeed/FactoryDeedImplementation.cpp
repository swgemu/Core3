#include "../../../player/Player.h"
#include "../../../../packets.h"

#include "FactoryDeed.h"
#include "FactoryDeedImplementation.h"
#include "../DeedObject.h"
#include "../DeedObjectImplementation.h"
#include "../../../installation/factory/FactoryObject.h"

FactoryDeedImplementation::FactoryDeedImplementation(CreatureObject* creature, uint32 tempcrc, const UnicodeString& n, const String& tempn)
	: FactoryDeedServant(creature->getNewItemID(), tempcrc, n, tempn, TangibleObjectImplementation::INSTALLATIONDEED) {
	objectCRC = tempcrc;

	customName = n;
	stfName = tempn;

	init();
}

FactoryDeedImplementation::FactoryDeedImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn)
	: FactoryDeedServant(objid, tempcrc, n, tempn, TangibleObjectImplementation::INSTALLATIONDEED) {
	objectID = objid;

	objectCRC = tempcrc;

	customName = n;
	stfName = tempn;

	init();
}

FactoryDeedImplementation::FactoryDeedImplementation(CreatureObject* creature, FactoryObject* fact) :
	FactoryDeedServant(creature->getNewItemID(), TangibleObjectImplementation::INSTALLATIONDEED) {

	info("FactoryDeedImplementation(CreatureObject* creature, FactoryObject* fact)");

	objectCRC = fact->getDeedCRC();
	stfFile = "deed"; // STF
	stfName = getDefaultTemplateName(objectCRC);
	info(stfName);
	customName = "";

	setSurplusMaintenance((uint32)fact->getSurplusMaintenance());
	setMaintenanceRate(fact->getMaintenanceRate());
	setSurplusPower((uint32)fact->getSurplusPower());
	setPowerRate(fact->getPowerRate());
	setHopperSize(fact->getHopperSizeMax());
	setBuildRate(fact->getBuildRate());

	init();
}

FactoryDeedImplementation::~FactoryDeedImplementation() {
}

void FactoryDeedImplementation::updateCraftingValues(DraftSchematic* draftSchematic) {
	/*extractrate, buildrate, hoppersize, hitpoints
	 * Incoming Values:				Range:
	 * extractrate					0-0 factories dont extract anything
	 * buildrate					5-12(Wearable)
	 * hoppersize					1500-4000(Wearable)
	 * hitpoints					5000-7000(Wearable)
	 */
	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	float buildrate = craftingValues->getCurrentValue("buildrate");
	setBuildRate(buildrate);

	int hopperSize = (int)craftingValues->getCurrentValue("hoppersize");
	setHopperSize(hopperSize);

	//int hitPoints = (int)craftingValues->getCurrentValue("hitpoints");
	//setHitPoints(hitPoints);

	setSurplusMaintenance(0);
	setSurplusPower(0);
	setPowerRate(50);
	setMaintenanceRate(35);
}

void FactoryDeedImplementation::parseItemAttributes() {
	DeedObjectImplementation::parseItemAttributes();

	String attr = "surplusMaintenance";
	setSurplusMaintenance(itemAttributes->getIntAttribute(attr));

	attr = "surplusPower";
	setSurplusPower(itemAttributes->getIntAttribute(attr));

	attr = "powerRate";
	setPowerRate(itemAttributes->getFloatAttribute(attr));

	attr = "maintenanceRate";
	setMaintenanceRate(itemAttributes->getFloatAttribute(attr));

	attr = "hopperSize";
	setHopperSize(itemAttributes->getFloatAttribute(attr));

	attr = "lotSize";
	setLotSize(itemAttributes->getIntAttribute(attr));

	attr = "buildRate";
	setBuildRate(itemAttributes->getFloatAttribute(attr));
}

void FactoryDeedImplementation::addAttributes(AttributeListMessage* alm) {
	addHeaderAttributes(alm);

	alm->insertAttribute("examine_maintenance", (int) getSurplusMaintenance());
	alm->insertAttribute("examine_maintenance_rate", (float) getMaintenanceRate());
	alm->insertAttribute("examine_power", (int) getSurplusPower());
	//alm->insertAttribute("examine_power_rate", (float) getPowerRate());
	alm->insertAttribute("examine_hoppersize", (float) getHopperSize());

	addFooterAttributes(alm);
}

void FactoryDeedImplementation::init() {
	objectSubType = TangibleObjectImplementation::INSTALLATIONDEED;
	setLotSize(1); // All Harvesters/Generators/Factories

	targetTempFile = "object/installation/base/shared_construction_installation_base.iff";

	if (stfName.indexOf("clothing") != -1){
		type = WEARABLES;

		targetTemplate = "clothing_factory";
		targetFile = "object/installation/manufacture/shared_clothing_factory.iff";

		targetName = String("Clothing Factory");
	} else if (stfName.indexOf("food") != -1){
		type = FOOD;

		targetTemplate = "food_factory";
		targetFile = "object/installation/manufacture/shared_food_factory.iff";

		targetName = String("Food Factory");
	} else if (stfName.indexOf("structure") != -1){
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

