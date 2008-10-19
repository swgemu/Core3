#include "../../../player/Player.h"
#include "../../../../packets.h"

#include "HarvesterDeed.h"
#include "HarvesterDeedImplementation.h"
#include "../DeedObject.h"
#include "../DeedObjectImplementation.h"


HarvesterDeedImplementation::HarvesterDeedImplementation(CreatureObject* creature, uint32 tempcrc, const unicode& n, const string& tempn) :
	HarvesterDeedServant(creature->getNewItemID(), tempcrc, n, tempn, TangibleObjectImplementation::INSTALLATIONDEED) {
	objectCRC = tempcrc;
	name = n;
	templateName = tempn;

	init();
}

HarvesterDeedImplementation::HarvesterDeedImplementation(uint64 objid, uint32 tempcrc, const unicode& n, const string& tempn) :
	HarvesterDeedServant(objid, tempcrc, n, tempn, TangibleObjectImplementation::INSTALLATIONDEED) {
	objectID = objid;
	objectCRC = tempcrc;
	name = n;
	templateName = tempn;

	init();
}

HarvesterDeedImplementation::~HarvesterDeedImplementation() {

}
void HarvesterDeedImplementation::init() {
	getType();
	getSize();

	objectSubType = TangibleObjectImplementation::INSTALLATIONDEED;

	switch (type) {
	case ORE:
		switch (size) {
		case SMALL:
			targetTemplate = "small_ore_mine";
			targetFile = "object/installation/mining_ore/shared_mining_ore_harvester_style_1.iff";
			targetName = unicode("Personal Mineral Extractor");
			break;

		case MEDIUM:
			targetTemplate = "ore_mine";
			targetFile
					= "object/installation/mining_ore/shared_mining_ore_harvester_style_2.iff";
			targetName = unicode("Mineral Mining Installation");
			break;

		case LARGE:
			targetTemplate = "heavy_ore_mine";
			targetFile
					= "object/installation/mining_ore/shared_mining_ore_harvester_heavy.iff";
			targetName = unicode("Heavy Mineral Mining Installation");
			break;

		}
		break;
	case MOISTURE:

		switch (size) {

		case SMALL:
			targetTemplate = "moisture_mine";
			targetFile
					= "object/installation/mining_liquid/shared_mining_liquid_moisture_harvester.iff";
			targetName = unicode("Personal Moisture Vaporator");
			break;

		case MEDIUM:
			targetTemplate = "moisture_mine_medium";
			targetFile
					= "object/installation/mining_liquid/shared_mining_liquid_moisture_harvester_medium.iff";
			targetName = unicode("Moisture Vaporator");
			break;

		case LARGE:
			targetTemplate = "moisture_mine_large";
			targetFile
					= "object/installation/mining_liquid/shared_mining_liquid_moisture_harvester_heavy.iff";
			targetName = unicode("High Efficiency Moisture Vaporator");
			break;

		}
		break;

	case LIQUID:
		switch (size) {

		case SMALL:
			targetTemplate = "liquid_mine";
			targetFile
					= "object/installation/mining_liquid/shared_mining_liquid_harvester_style_1.iff";
			targetName = unicode("Personal Chemical Extractor");
			break;

		case MEDIUM:
			targetTemplate = "liquid_mine_medium";
			targetFile = "object/installation/mining_liquid/shared_mining_liquid_harvester_style_2.iff";
			targetName = unicode("Chemical Extractor");
			break;

		case LARGE:
			targetTemplate = "liquid_mine_large";
			targetFile = "object/installation/mining_liquid/shared_mining_liquid_harvester_style_3.iff";
			targetName = unicode("Deep Crust Chemical Extractor");
			break;

		}
		break;

	case GAS:
		switch (size) {
		case SMALL:
			targetTemplate = "gas_mine";
			targetFile
					= "object/installation/mining_gas/shared_mining_gas_harvester_style_1.iff";
			targetName = unicode("Personal Natural Gas Processor");
			break;

		case MEDIUM:
			targetTemplate = "gas_mine_medium";
			targetFile
					= "object/installation/mining_gas/shared_mining_gas_harvester_style_2.iff";
			targetName = unicode("Natural Gas Processor");
			break;

		case LARGE:
			targetTemplate = "gas_mine_large";
			targetFile
					= "object/installation/mining_gas/shared_mining_gas_harvester_style_3.iff";
			targetName = unicode("Heavy Natural Gas Processor");
			break;

		}
		break;

	case FLORA:
		switch (size) {
	case SMALL:
			targetTemplate = "flora_farm";
			targetFile
					= "object/installation/mining_organic/shared_mining_organic_flora_farm.iff";
			targetName = unicode("Micro Flora Farm");
			break;

		case MEDIUM:
			targetTemplate = "flora_farm_medium";
			targetFile
					= "object/installation/mining_organic/shared_mining_organic_flora_farm_medium.iff";
			targetName = unicode("Automated Flora Farm");
			break;

		case LARGE:
			targetTemplate = "flora_farm_heavy";
			targetFile
					= "object/installation/mining_organic/shared_mining_organic_flora_farm_heavy.iff";
		targetName = unicode("High Capacity Flora Farm");
			break;

		}
		break;

	case CREATURE:
			targetTemplate = "organic_harvester";
			targetFile
					= "object/installation/mining_organic/shared_mining_organic_creature_farm.iff";
			targetName = unicode("Creature Harvester");
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

	string attr = "surplusMaintenance";
	setSurplusMaintenance(itemAttributes->getIntAttribute(attr));

	attr = "surplusPower";
	setSurplusPower(itemAttributes->getIntAttribute(attr));

	attr = "maintenanceRate";
	setMaintenanceRate(itemAttributes->getFloatAttribute(attr));

	attr = "extractionRate";
	setExtractionRate(itemAttributes->getFloatAttribute(attr));

	attr = "hopperSize";
	setHopperSize(itemAttributes->getFloatAttribute(attr));
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

void HarvesterDeedImplementation::getType(){
	if ((templateName.find("ore") != string::npos))
		type = ORE;
	else if ((templateName.find("flora") != string::npos))
		type = FLORA;
	else if ((templateName.find("gas") != string::npos))
		type = GAS;
	else if ((templateName.find("liquid") != string::npos))
		type = LIQUID;
	else if ((templateName.find("moisture") != string::npos))
		type = MOISTURE;
	else if ((templateName.find("creature") != string::npos))
		type = CREATURE;
}

void HarvesterDeedImplementation::getSize() {
	if ((templateName.find("heavy") != string::npos))
		size = LARGE;
	else if ((templateName.find("medium") != string::npos) || (templateName.find("s2") != string::npos))
		size = MEDIUM;
	else
		size = SMALL;
}

