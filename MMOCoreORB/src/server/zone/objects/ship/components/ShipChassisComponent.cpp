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

	int totalSkills = chassisTemplate->getTotalSkillsRequired();

	for (int i = 0; i < totalSkills; ++i) {
		String skillName = chassisTemplate->getSkillRequired(i);

		skillsRequired.add(skillName);
	}

	dealerFee = chassisTemplate->getDealerFee();

	pob = chassisTemplate->isPob();
}

void ShipChassisComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {
	alm->insertAttribute("volume", 1);
	alm->insertAttribute("crafter", craftersName);
	alm->insertAttribute("serial_number", objectSerial);

	StringBuffer msg;

	msg.append(getMass(), 2);
	alm->insertAttribute("@obj_attr_n:chassismassmax", msg);
	msg.deleteAll();

	msg << Math::getPrecision(getMaxHitpoints(), 4);
	alm->insertAttribute("@crafting:hp", msg);
	msg.deleteAll();

	if (getTotalSkillsRequired() == 1) {
		String skillName = getSkillRequired(0);

		msg << "@skl_n:" << skillName;
		alm->insertAttribute("pilotskillrequired", msg);
		msg.deleteAll();
	}

	if (player != nullptr && player->isPlayerCreature()) {
		auto ghost = player->getPlayerObject();

		if (ghost != nullptr && ghost->isPrivileged()) {
			msg << chassisDeed;
			alm->insertAttribute("Deed", msg);
			msg.deleteAll();

			msg << "@cmd_d:" << getCertificationRequired();
			alm->insertAttribute("pilotskillrequired", msg);
			msg.deleteAll();
		}
	}
}

void ShipChassisComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);

	setMass(getAttributeValue("massmax"));
	setHitpointsMax(getAttributeValue("hp"));
}
