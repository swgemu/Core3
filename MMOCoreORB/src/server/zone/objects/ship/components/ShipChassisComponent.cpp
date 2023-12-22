#include "server/zone/objects/ship/components/ShipChassisComponent.h"

void ShipChassisComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	// TODO: Load this information from the object template

	/*
		templateType = SHIPCHASSIS,
		chassisDeed = "object/tangible/ship/crafted/chassis/awing_deed.iff",
		dealerFee = 8000,
		certRequired = "pilot_rebel_navy_starships_04",
		POB = 0,
	*/
}

void ShipChassisComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	alm->insertAttribute("volume", 1);
	alm->insertAttribute("crafter", craftersName);
	alm->insertAttribute("serial_number", objectSerial);

	StringBuffer msg;
	msg << Math::getPrecision(mass, 2);

	alm->insertAttribute("@obj_attr_n:chassismassmax", msg);
	msg.deleteAll();

	msg << Math::getPrecision(hitpointsMax, 4);

	alm->insertAttribute("@crafting:hp", msg);
	msg.deleteAll();

	msg << "@skl_n:" << getCertificationRequired();
	alm->insertAttribute("pilotskillrequired", msg);
}

void ShipChassisComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);

	setMass(getAttributeValue("massmax"));
	setHitpointsMax(getAttributeValue("hp"));
}
