
#include "server/zone/objects/tangible/pharmaceutical/RangedStimPack.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "templates/params/creature/CreatureAttribute.h"

void RangedStimPackImplementation::fillAttributeList(AttributeListMessage* msg, CreatureObject* object) {
	StimPackImplementation::fillAttributeList(msg, object);

	Vector<byte> atts = getAttributes();

	if (atts.contains(CreatureAttribute::HEALTH)) {
		msg->insertAttribute("examine_heal_damage_health", Math::getPrecision(effectiveness, 0));
	}

	if (atts.contains(CreatureAttribute::ACTION)) {
		msg->insertAttribute("examine_heal_damage_action", Math::getPrecision(effectiveness, 0));
	}

	if (atts.contains(CreatureAttribute::MIND)) {
		msg->insertAttribute("examine_heal_damage_mind", Math::getPrecision(effectiveness, 0));
	}

	msg->insertAttribute("examine_heal_range", Math::getPrecision(range, 0));

	if (isArea()) {
		msg->insertAttribute("examine_heal_area", Math::getPrecision(area, 0));
	}

	msg->insertAttribute("combat_healing_ability", medicineUseRequired);
}
