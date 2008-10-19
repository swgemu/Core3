#include "../../../player/Player.h"
#include "../../../../packets.h"

#include "GeneratorDeed.h"
#include "GeneratorDeedImplementation.h"
#include "../DeedObject.h"
#include "../DeedObjectImplementation.h"

GeneratorDeedImplementation::GeneratorDeedImplementation(CreatureObject* creature, uint32 tempcrc, const unicode& n, const string& tempn)
	: GeneratorDeedServant(creature->getNewItemID(), tempcrc, n, tempn, TangibleObjectImplementation::INSTALLATIONDEED) {
	objectCRC = tempcrc;
	name = n;
	templateName = tempn;

	init();
}
GeneratorDeedImplementation::GeneratorDeedImplementation(uint64 objid, uint32 tempcrc, const unicode& n, const string& tempn)
	: GeneratorDeedServant(objid, tempcrc, n, tempn, TangibleObjectImplementation::INSTALLATIONDEED) {
	objectID = objid;
	objectCRC = tempcrc;
	name = n;
	templateName = tempn;

	init();
}

GeneratorDeedImplementation::~GeneratorDeedImplementation() {

}

void GeneratorDeedImplementation::parseItemAttributes() {
	DeedObjectImplementation::parseItemAttributes();

	string attr = "surplusMaintenance";
	setSurplusMaintenance(itemAttributes->getIntAttribute(attr));

	attr = "maintenanceRate";
	setMaintenanceRate(itemAttributes->getFloatAttribute(attr));

	attr = "extractionRate";
	setExtractionRate(itemAttributes->getFloatAttribute(attr));

	attr = "hopperSize";
	setHopperSize(itemAttributes->getFloatAttribute(attr));
}

void GeneratorDeedImplementation::addAttributes(AttributeListMessage* alm) {
	addHeaderAttributes(alm);

	alm->insertAttribute("examine_maintenance", (int)getSurplusMaintenance());
	alm->insertAttribute("examine_maintenance_rate", (float)getMaintenanceRate());
	alm->insertAttribute("examine_extractionrate", (float)getExtractionRate());
	alm->insertAttribute("examine_hoppersize", (float)getHopperSize());

	addFooterAttributes(alm);
}

void GeneratorDeedImplementation::init() {
	objectSubType = TangibleObjectImplementation::INSTALLATIONDEED;

	targetTempFile = "object/installation/base/shared_construction_installation_base.iff";

	if ((templateName.find("fusion") != string::npos)){
		type = FUSION;
		targetTemplate = "fusion_generator";
		targetFile = "object/installation/generators/shared_power_generator_fusion_style_1.iff";
		targetName = string("Fusion Power Generator");
	} else if ((templateName.find("photo") != string::npos)){
		type = PHOTOBIO;
		targetTemplate = "photobio_generator";
		targetFile = "object/installation/generators/shared_power_generator_photo_bio_style_1.iff";
		targetName = string("Photo Power Generator");
	} else if ((templateName.find("solar") != string::npos)){
		type = SOLAR;
		targetTemplate = "solar_generator";
		targetFile = "object/installation/generators/shared_power_generator_solar_style_1.iff";
		targetName = string("Solar Power Generator");
	} else if ((templateName.find("wind") != string::npos)){
		type = WIND;
		targetTempFile = "object/installation/base/shared_construction_installation_base.iff";
		targetTemplate = "wind_generator";
		targetFile = "object/installation/generators/shared_power_generator_wind_style_1.iff";
		targetName = string("Wind Power Generator");
	}
}
