#include "server/zone/objects/ship/components/ShipChassisComponent.h"
#include "templates/tangible/ship/ShipChassisTemplate.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"

void ShipChassisComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	auto chassisTemplate = dynamic_cast<ShipChassisTemplate*>(templateData);

	if (chassisTemplate == nullptr)
		return;

	chassisDeed = chassisTemplate->getChassisDeed();
	certification = chassisTemplate->getCertificationsRequired();
	dealerFee = chassisTemplate->getDealerFee();

	pob = chassisTemplate->isPob();
}

void ShipChassisComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {
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

	String certRequired = getCertificationRequired();

	if (!certRequired.isEmpty()) {
		msg << "@skl_n:" << certRequired;
		alm->insertAttribute("pilotskillrequired", msg);

		msg.deleteAll();
	}

	if (player != nullptr && player->isPlayerCreature()) {
		auto ghost = player->getPlayerObject();

		if (ghost != nullptr && ghost->isPrivileged()) {
			msg << chassisDeed;
			alm->insertAttribute("Deed", msg);
		}
	}
}

void ShipChassisComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);

	setMass(getAttributeValue("massmax"));
	setHitpointsMax(getAttributeValue("hp"));
}
