#include "../../../player/Player.h"
#include "../../../../packets.h"

#include "HarvesterDeed.h"
#include "HarvesterDeedImplementation.h"
#include "../DeedObject.h"
#include "../DeedObjectImplementation.h"


HarvesterDeedImplementation::HarvesterDeedImplementation(CreatureObject* creature, uint32 tempcrc, const UnicodeString& n, const String& tempn) :
		HarvesterDeedServant(creature->getNewItemID(), tempcrc, n, tempn, TangibleObjectImplementation::INSTALLATIONDEED) {
	objectCRC = tempcrc;

	name = n;
	templateName = tempn;

	init();
}

HarvesterDeedImplementation::HarvesterDeedImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn) :
		HarvesterDeedServant(objid, tempcrc, n, tempn, TangibleObjectImplementation::INSTALLATIONDEED) {
	objectID = objid;

	objectCRC = tempcrc;

	name = n;
	templateName = tempn;

	init();
}

HarvesterDeedImplementation::HarvesterDeedImplementation(CreatureObject* creature, HarvesterObject* hino) :
	HarvesterDeedServant(creature->getNewItemID(), TangibleObjectImplementation::INSTALLATIONDEED) {

	info("HarvesterDeedImplementation(CreatureObject* creature, HarvesterObject* hino)");

	objectCRC = hino->getDeedCRC();
	templateTypeName = "deed"; // STF
	templateName = getDefaultTemplateName(objectCRC);
	info(templateName);
	name = "";

	setSurplusMaintenance(hino->getSurplusMaintenance());
	setMaintenanceRate(hino->getMaintenanceRate());
	setSurplusPower(hino->getSurplusPower());
	setPowerRate(hino->getPowerRate());
	setHopperSize(hino->getHopperSizeMax());
	setExtractionRate(hino->getExtractionRate());

	init();
}


HarvesterDeedImplementation::~HarvesterDeedImplementation() {
}

void HarvesterDeedImplementation::init() {
	initType();
	initSize();

	setLotSize(1); // All Harvesters
	objectSubType = TangibleObjectImplementation::INSTALLATIONDEED;

	switch (type) {
	case ORE:
		switch (size) {
		case SMALL:
			targetTemplate = "small_ore_mine";
			targetFile = "object/installation/mining_ore/shared_mining_ore_harvester_style_1.iff";

			targetName = UnicodeString("Personal Mineral Extractor");
			break;
		case MEDIUM:
			targetTemplate = "ore_mine";
			targetFile
					= "object/installation/mining_ore/shared_mining_ore_harvester_style_2.iff";

			targetName = UnicodeString("Mineral Mining Installation");
			break;
		case LARGE:
			targetTemplate = "heavy_ore_mine";
			targetFile
					= "object/installation/mining_ore/shared_mining_ore_harvester_heavy.iff";

			targetName = UnicodeString("Heavy Mineral Mining Installation");
			break;
		}

		break;
	case MOISTURE:
		switch (size) {
		case SMALL:
			targetTemplate = "moisture_mine";
			targetFile
					= "object/installation/mining_liquid/shared_mining_liquid_moisture_harvester.iff";

			targetName = UnicodeString("Personal Moisture Vaporator");
			break;
		case MEDIUM:
			targetTemplate = "moisture_mine_medium";
			targetFile
					= "object/installation/mining_liquid/shared_mining_liquid_moisture_harvester_medium.iff";

			targetName = UnicodeString("Moisture Vaporator");
			break;
		case LARGE:
			targetTemplate = "moisture_mine_large";
			targetFile
					= "object/installation/mining_liquid/shared_mining_liquid_moisture_harvester_heavy.iff";

			targetName = UnicodeString("High Efficiency Moisture Vaporator");
			break;
		}

		break;
	case LIQUID:
		switch (size) {
		case SMALL:
			targetTemplate = "liquid_mine";
			targetFile
					= "object/installation/mining_liquid/shared_mining_liquid_harvester_style_1.iff";

			targetName = UnicodeString("Personal Chemical Extractor");
			break;
		case MEDIUM:
			targetTemplate = "liquid_mine_medium";
			targetFile = "object/installation/mining_liquid/shared_mining_liquid_harvester_style_2.iff";

			targetName = UnicodeString("Chemical Extractor");
			break;
		case LARGE:
			targetTemplate = "liquid_mine_large";
			targetFile = "object/installation/mining_liquid/shared_mining_liquid_harvester_style_3.iff";

			targetName = UnicodeString("Deep Crust Chemical Extractor");
			break;
		}

		break;
	case GAS:
		switch (size) {
		case SMALL:
			targetTemplate = "gas_mine";
			targetFile
					= "object/installation/mining_gas/shared_mining_gas_harvester_style_1.iff";

			targetName = UnicodeString("Personal Natural Gas Processor");
			break;
		case MEDIUM:
			targetTemplate = "gas_mine_medium";
			targetFile
					= "object/installation/mining_gas/shared_mining_gas_harvester_style_2.iff";

			targetName = UnicodeString("Natural Gas Processor");
			break;
		case LARGE:
			targetTemplate = "gas_mine_large";
			targetFile
					= "object/installation/mining_gas/shared_mining_gas_harvester_style_3.iff";

			targetName = UnicodeString("Heavy Natural Gas Processor");
			break;
		}

		break;
	case FLORA:
		switch (size) {
		case SMALL:
			targetTemplate = "flora_farm";
			targetFile
					= "object/installation/mining_organic/shared_mining_organic_flora_farm.iff";

			targetName = UnicodeString("Micro Flora Farm");
			break;
		case MEDIUM:
			targetTemplate = "flora_farm_medium";
			targetFile
					= "object/installation/mining_organic/shared_mining_organic_flora_farm_medium.iff";

			targetName = UnicodeString("Automated Flora Farm");
			break;
		case LARGE:
			targetTemplate = "flora_farm_heavy";
			targetFile
					= "object/installation/mining_organic/shared_mining_organic_flora_farm_heavy.iff";

			targetName = UnicodeString("High Capacity Flora Farm");
			break;
		}

		break;
	case CREATURE:
		targetTemplate = "organic_harvester";
		targetFile
				= "object/installation/mining_organic/shared_mining_organic_creature_farm.iff";

		targetName = UnicodeString("Creature Harvester");
		break;
	}

	switch (size) {
	case SMALL:
		targetTempFile
			= "object/installation/mining_ore/construction/shared_construction_mining_ore_harvester_style_1.iff";
		break;
	case MEDIUM:
		targetTempFile
				= "object/installation/mining_ore/construction/shared_construction_mining_ore_harvester_style_2.iff";
		break;
	case LARGE:
		targetTempFile
				= "object/installation/mining_ore/construction/shared_construction_mining_ore_harvester_style_heavy.iff";
		break;
	}
}

void HarvesterDeedImplementation::parseItemAttributes() {
	DeedObjectImplementation::parseItemAttributes();

	String attr = "surplusMaintenance";
	setSurplusMaintenance(itemAttributes->getIntAttribute(attr));

	attr = "surplusPower";
	setSurplusPower(itemAttributes->getIntAttribute(attr));

	attr = "maintenanceRate";
	setMaintenanceRate(itemAttributes->getFloatAttribute(attr));

	attr = "extractionRate";
	setExtractionRate(itemAttributes->getFloatAttribute(attr));

	attr = "hopperSize";
	setHopperSize(itemAttributes->getFloatAttribute(attr));

	attr = "lotSize";
	setLotSize(itemAttributes->getIntAttribute(attr));
}

void HarvesterDeedImplementation::addAttributes(AttributeListMessage* alm) {
	addHeaderAttributes(alm);

	alm->insertAttribute("examine_maintenance", (int)getSurplusMaintenance());
	alm->insertAttribute("examine_maintenance_rate", (float)getMaintenanceRate());
	alm->insertAttribute("examine_power", (int)getSurplusPower());
	alm->insertAttribute("examine_extractionrate", (float)getExtractionRate());
	alm->insertAttribute("examine_hoppersize", (float)getHopperSize());

	addFooterAttributes(alm);
}

void HarvesterDeedImplementation::initType(){
	if ((templateName.indexOf("ore") != -1))
		type = ORE;
	else if ((templateName.indexOf("flora") != -1))
		type = FLORA;
	else if ((templateName.indexOf("gas") != -1))
		type = GAS;
	else if ((templateName.indexOf("liquid") != -1))
		type = LIQUID;
	else if ((templateName.indexOf("moisture") != -1))
		type = MOISTURE;
	else if ((templateName.indexOf("creature") != -1))
		type = CREATURE;
}

void HarvesterDeedImplementation::initSize() {
	if ((templateName.indexOf("heavy") != -1))
		size = LARGE;
	else if ((templateName.indexOf("medium") != -1) || (templateName.indexOf("s2") != -1))
		size = MEDIUM;
	else
		size = SMALL;
}

