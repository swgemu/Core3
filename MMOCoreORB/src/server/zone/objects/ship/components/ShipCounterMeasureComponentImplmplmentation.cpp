#include "server/zone/objects/ship/components/ShipCounterMeasureComponent.h"
#include "templates/SharedTangibleObjectTemplate.h"

void ShipCounterMeasureComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<SharedTangibleObjectTemplate*>(templateData);

	if (shot != nullptr) {
		const auto attributes = shot->getExperimentalAttributes();
		const auto minValues = shot->getExperimentalMin();

		for (int i = 0; i < attributes->size(); ++i) {
			auto attribute = attributes->get(i);
			auto value = minValues->get(i);

			if (attribute == "fltmineffectiveness") {
				effectivenessMin = value;
			} else if (attribute == "fltmaxeffectiveness") {
				effectivenessMax = value;
			} else if (attribute == "fltrefirerate" || attribute == "refire_rate") {
				refireRate = value * 0.001f;
			} else if (attribute == "fltmaxammo" || attribute == "ammo") {
				useCount = Math::max(value, 1.f);
			} else if (attribute == "energy_per_shot") {
				energyPerShot = Math::max(value, 0.f);
			}
		}
	}
}

void ShipCounterMeasureComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ComponentImplementation::updateCraftingValues(values, firstUpdate);

	for (int i = 0; i < values->getTotalExperimentalAttributes(); ++i) {
		auto attribute = values->getAttribute(i);
		auto value = values->getCurrentValue(attribute);

		if (attribute == "fltmineffectiveness") {
			effectivenessMin = value;
		} else if (attribute == "fltmaxeffectiveness") {
			effectivenessMax = value;
		} else if (attribute == "fltrefirerate" || attribute == "refire_rate") {
			refireRate = value * 0.001f;
		} else if (attribute == "fltmaxammo" || attribute == "ammo") {
			useCount = Math::max(value, 1.f);
		} else if (attribute == "energy_per_shot") {
			energyPerShot = Math::max(value, 0.f);
		}
	}
}

void ShipCounterMeasureComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	alm->insertAttribute("@obj_attr_n:volume", volume);

	if (!craftersName.isEmpty()) {
		alm->insertAttribute("crafter", craftersName);
	}

	if (!objectSerial.isEmpty()) {
		alm->insertAttribute("serial_number", objectSerial);
	}

	alm->insertAttribute("@obj_attr_n:chaff_effectiveness_min", String::valueOf(Math::getPrecision(effectivenessMin, 6)));
	alm->insertAttribute("@obj_attr_n:chaff_effectiveness_max", String::valueOf(Math::getPrecision(effectivenessMax, 6)));
	alm->insertAttribute("@obj_attr_n:refire_rate", String::valueOf(Math::getPrecision(refireRate, 6)));
	alm->insertAttribute("@obj_attr_n:ammo", String::valueOf(Math::getPrecision(getUseCount(), 0)));

	if (energyPerShot != 0.f) {
		alm->insertAttribute("@obj_attr_n:energy_per_shot", String::valueOf(Math::getPrecision(energyPerShot, 6)));
	}
}
