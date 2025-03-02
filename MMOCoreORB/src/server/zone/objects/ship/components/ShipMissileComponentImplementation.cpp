#include "server/zone/objects/ship/components/ShipMissileComponent.h"
#include "templates/SharedTangibleObjectTemplate.h"

void ShipMissileComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<SharedTangibleObjectTemplate*>(templateData);

	if (shot != nullptr) {
		const auto attributes = shot->getExperimentalAttributes();
		const auto minValues = shot->getExperimentalMin();

		for (int i = 0; i < attributes->size(); ++i) {
			auto attribute = attributes->get(i);
			auto value = minValues->get(i);

			if (attribute == "fltmaxdamage") {
				maxDamage = value;
			} else if (attribute == "fltmindamage") {
				minDamage = value;
			} else if (attribute == "fltshieldeffectiveness") {
				shieldEffectiveness = value;
			} else if (attribute == "fltarmoreffectiveness") {
				armorEffectiveness = value;
			} else if (attribute == "fltrefirerate" || attribute == "refire_rate") {
				refireRate = value * 0.001f;
			} else if (attribute == "fltmaxammo" || attribute == "ammo") {
				useCount = Math::max(value, 1.f);
			}
		}
	}
}

void ShipMissileComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ComponentImplementation::updateCraftingValues(values, firstUpdate);

	for (int i = 0; i < values->getTotalExperimentalAttributes(); ++i) {
		const auto& attribute = values->getAttribute(i);
		const auto& group = values->getAttributeGroup(attribute);
		auto value = values->getCurrentValue(attribute);

		if (attribute == "fltmaxdamage") {
			maxDamage = value;
		} else if (attribute == "fltmindamage") {
			minDamage = value;
		} else if (attribute == "fltshieldeffectiveness") {
			shieldEffectiveness = value;
		} else if (attribute == "fltarmoreffectiveness") {
			armorEffectiveness = value;
		} else if (attribute == "fltrefirerate" || attribute == "refire_rate") {
			refireRate = value * 0.001f;
		} else if (attribute == "fltmaxammo" || attribute == "ammo") {
			useCount = Math::max(value, 1.f);
		}

		if (firstUpdate && group == "misc") {
			values->setHidden(attribute);
		}
	}
}

void ShipMissileComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	alm->insertAttribute("@obj_attr_n:volume", volume);

	if (!craftersName.isEmpty()) {
		alm->insertAttribute("crafter", craftersName);
	}

	if (!objectSerial.isEmpty()) {
		alm->insertAttribute("serial_number", objectSerial);
	}

	alm->insertAttribute("@obj_attr_n:wpn_comp_damage_min", String::valueOf(Math::getPrecision(minDamage, 6)));
	alm->insertAttribute("@obj_attr_n:wpn_comp_damage_max", String::valueOf(Math::getPrecision(maxDamage, 6)));
	alm->insertAttribute("@obj_attr_n:refire_rate", String::valueOf(Math::getPrecision(refireRate, 6)));
	alm->insertAttribute("@obj_attr_n:effective_shields", String::valueOf(Math::getPrecision(shieldEffectiveness, 6)));
	alm->insertAttribute("@obj_attr_n:effective_armor", String::valueOf(Math::getPrecision(armorEffectiveness, 6)));
	alm->insertAttribute("@obj_attr_n:ammo", String::valueOf(Math::getPrecision(getUseCount(), 0)));
}
