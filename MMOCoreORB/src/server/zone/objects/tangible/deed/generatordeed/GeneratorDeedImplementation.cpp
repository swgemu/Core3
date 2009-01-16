#include "../../../player/Player.h"
#include "../../../../packets.h"

#include "GeneratorDeed.h"
#include "GeneratorDeedImplementation.h"
#include "../DeedObject.h"
#include "../DeedObjectImplementation.h"

GeneratorDeedImplementation::GeneratorDeedImplementation(CreatureObject* creature, uint32 tempcrc, const UnicodeString& n, const String& tempn)
		: GeneratorDeedServant(creature->getNewItemID(), tempcrc, n, tempn, TangibleObjectImplementation::INSTALLATIONDEED) {
	objectCRC = tempcrc;

	customName = n;
	templateName = tempn;

	init();
}
GeneratorDeedImplementation::GeneratorDeedImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn)
		: GeneratorDeedServant(objid, tempcrc, n, tempn, TangibleObjectImplementation::INSTALLATIONDEED) {
	objectID = objid;

	objectCRC = tempcrc;

	customName = n;
	templateName = tempn;

	init();
}

GeneratorDeedImplementation::~GeneratorDeedImplementation() {
}

void GeneratorDeedImplementation::parseItemAttributes() {
	DeedObjectImplementation::parseItemAttributes();

	String attr = "surplusMaintenance";
	setSurplusMaintenance(itemAttributes->getIntAttribute(attr));

	attr = "maintenanceRate";
	setMaintenanceRate(itemAttributes->getFloatAttribute(attr));

	attr = "extractionRate";
	setExtractionRate(itemAttributes->getFloatAttribute(attr));

	attr = "hopperSize";
	setHopperSize(itemAttributes->getFloatAttribute(attr));

	attr = "lotSize";
	setLotSize(itemAttributes->getIntAttribute(attr));
}

void GeneratorDeedImplementation::updateCraftingValues(DraftSchematic* draftSchematic) {
	DraftSchematicValues* craftingValues = draftSchematic->getCraftingValues();

	int extractionRate = (int)craftingValues->getCurrentValue("extractrate");
	setExtractionRate(extractionRate);

	int hopperSize = (int)craftingValues->getCurrentValue("hoppersize");
	setHopperSize(hopperSize);

	int hitPoints = (int)craftingValues->getCurrentValue("hitpoints");
	//setHitPoints(hitPoints); isnt this the same as default 100/100? they only take damage when at 0 maintenance

	setSurplusMaintenance(0);
	setMaintenanceRate(10);//dunno what this is supposed to be set to for each harvester
	//TODO: figure out lot sizes for all the different sizes.
	setLotSize(1);
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
	setLotSize(1); // All Harvesters/Generators/Factories

	targetTempFile = "object/installation/base/shared_construction_installation_base.iff";

	if ((templateName.indexOf("fusion") != -1)){
		type = FUSION;

		targetTemplate = "fusion_generator";
		targetFile = "object/installation/generators/shared_power_generator_fusion_style_1.iff";

		targetName = String("Fusion Power Generator");
	} else if ((templateName.indexOf("photo") != -1)){
		type = PHOTOBIO;

		targetTemplate = "photobio_generator";
		targetFile = "object/installation/generators/shared_power_generator_photo_bio_style_1.iff";

		targetName = String("Photo Power Generator");
	} else if ((templateName.indexOf("solar") != -1)){
		type = SOLAR;

		targetTemplate = "solar_generator";
		targetFile = "object/installation/generators/shared_power_generator_solar_style_1.iff";

		targetName = String("Solar Power Generator");
	} else if ((templateName.indexOf("wind") != -1)){
		type = WIND;

		targetTempFile = "object/installation/base/shared_construction_installation_base.iff";
		targetTemplate = "wind_generator";
		targetFile = "object/installation/generators/shared_power_generator_wind_style_1.iff";

		targetName = String("Wind Power Generator");
	}
}
