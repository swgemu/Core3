#include "../../../player/Player.h"
#include "../../../../packets.h"

#include "GeneratorDeed.h"
#include "GeneratorDeedImplementation.h"
#include "../DeedObject.h"
#include "../DeedObjectImplementation.h"

GeneratorDeedImplementation::GeneratorDeedImplementation(CreatureObject* creature, uint32 tempcrc, const unicode& n, const string& tempn)
	: GeneratorDeedServant(creature->getNewItemID(), tempcrc, n, tempn, INSTALLATIONDEED) {
	objectCRC = tempcrc;
	name = n;
	templateName = tempn;
	init();
}
GeneratorDeedImplementation::GeneratorDeedImplementation(uint64 objid, uint32 tempcrc, const unicode& n, const string& tempn)
	: GeneratorDeedServant(objid, tempcrc, n, tempn, INSTALLATIONDEED) {
	objectID = objid;
	objectCRC = tempcrc;
	name = n;
	templateName = tempn;
	init();
}
GeneratorDeedImplementation::~GeneratorDeedImplementation() {

}

void GeneratorDeedImplementation::init() {

	deedSubType = GENERATOR;

	if ((templateName.find("fusion") != string::npos)){
		targetTemplate = "power_generator_fusion_style_1";
		// = "object/installation/mining_organic/shared_mining_organic_flora_farm_medium.iff";
		targetFile
			= "object/installation/generators/shared_power_generator_fusion_style_1.iff";
		targetName = unicode("Fusion Power Generator");
	} else if ((templateName.find("photo") != string::npos)){
		targetTemplate = "power_generator_photo_bio_style_1";
		targetFile
			= "object/installation/generators/shared_power_generator_photo_bio_style_1.iff";
		targetName = unicode("Photo Power Generator");
	} else if ((templateName.find("solar") != string::npos)){
		targetTemplate = "power_generator_solar_style_1";
		targetFile
			= "object/installation/generators/shared_power_generator_solar_style_1.iff";
		targetName = unicode("Solar Power Generator");
	} else if ((templateName.find("wind") != string::npos)){
		targetTemplate = "wind_generator";
		targetFile
			= "object/installation/generators/shared_power_generator_wind_style_1.iff";
		targetName = unicode("Wind Power Generator");
	}
}
