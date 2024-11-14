#include "server/zone/objects/ship/components/ShipShieldComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/DeltaMessage.h"

void ShipShieldComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<ShipComponentTemplate*>(templateData);

	if (shot != nullptr) {
		const auto& attributeMap = shot->getAttributeMap();

		for (int i = 0; i < attributeMap.size(); ++i) {
			const auto& attribute = attributeMap.elementAt(i).getKey();
			float value = attributeMap.elementAt(i).getValue();

			if (attribute == "shieldHitpointsMaximumBack") {
				rearHitpoints = value;
			} else if(attribute == "shieldHitpointsMaximumFront") {
				frontHitpoints = value;
			} else if (attribute == "shieldRechargeRate") {
				rechargeRate = value;
			}
		}
	}
}

void ShipShieldComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);

	for (int i = 0; i < values->getTotalExperimentalAttributes(); ++i) {
		const auto& attribute = values->getAttribute(i);
		auto current = values->getCurrentValue(attribute);

		if (attribute == "ship_component_shield_hitpoints_back") {
			rearHitpoints = current;
		} else if(attribute == "ship_component_shield_hitpoints_front") {
			frontHitpoints = current;
		} else if (attribute == "ship_component_shield_recharge_rate") {
			rechargeRate = current;
		}
	}
}

void ShipShieldComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	ShipComponentImplementation::fillAttributeList(alm, object);

	StringBuffer msg;

	msg << "0.0/" << Math::getPrecision(frontHitpoints, 1);
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_shield_hitpoints_front", msg.toString());
	msg.deleteAll();

	msg << "0.0/" << Math::getPrecision(rearHitpoints, 1);
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_shield_hitpoints_back", msg.toString());
	msg.deleteAll();

	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_shield_recharge_rate", String::valueOf(Math::getPrecision(rechargeRate, 1)));

	if (reverseEngineeringLevel != 0) {
		alm->insertAttribute("@obj_attr_n:reverseengineeringlevel", reverseEngineeringLevel);
	}
}

void ShipShieldComponentImplementation::install(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::install(pilot, ship, slot, notifyClient);

	auto deltaVector = notifyClient ? ship->getDeltaVector() : nullptr;

	ship->setShieldRechargeRate(rechargeRate, false, nullptr, deltaVector);

	ship->setFrontShieldMax(frontHitpoints, false, nullptr, deltaVector);
	ship->setRearShieldMax(rearHitpoints, false, nullptr, deltaVector);

	ship->setFrontShield(frontHitpoints, false, nullptr, deltaVector);
	ship->setRearShield(rearHitpoints, false, nullptr, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(ship);
	}
}

void ShipShieldComponentImplementation::uninstall(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::uninstall(pilot, ship, slot, notifyClient);

	auto deltaVector = notifyClient ? ship->getDeltaVector() : nullptr;

	ship->setShieldRechargeRate(0, false, nullptr, deltaVector);

	ship->setFrontShieldMax(0, false, nullptr, deltaVector);
	ship->setRearShieldMax(0, false, nullptr, deltaVector);

	ship->setFrontShield(0, false, nullptr, deltaVector);
	ship->setRearShield(0, false, nullptr, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(ship);
	}
}
