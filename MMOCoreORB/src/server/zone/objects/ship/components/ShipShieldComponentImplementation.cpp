#include "server/zone/objects/ship/components/ShipShieldComponent.h"
#include "server/zone/objects/ship/components/ShipComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "templates/tangible/SharedShipObjectTemplate.h"
#include "server/zone/packets/DeltaMessage.h"

void ShipShieldComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<SharedTangibleObjectTemplate*>(templateData);

	if (shot != nullptr) {
		frontHitpoints = shot->getShieldHitpointsFront();
		rearHitpoints = shot->getShieldHitpointsRear();
		rechargeRate = shot->getShipRechargeRate();
	}
}

void ShipShieldComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);

	for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
		const String& attribute = values->getExperimentalPropertySubtitle(i);
		float current = values->getCurrentValue(attribute);

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

	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_shield_hitpoints_front", String::valueOf(Math::getPrecision(frontHitpoints, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_shield_hitpoints_back", String::valueOf(Math::getPrecision(rearHitpoints, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_shield_recharge_rate", String::valueOf(Math::getPrecision(rechargeRate, 1)));

	if (craftersName.isEmpty()) {
		alm->insertAttribute("@obj_attr_n:reverseengineeringlevel", getReverseEngineeringLevel());
	}
}

void ShipShieldComponentImplementation::install(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::install(pilot, ship, slot, notifyClient);

	DeltaMessage* ship1 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;
	DeltaMessage* ship3 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 3) : nullptr;
	DeltaMessage* ship6 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 6) : nullptr;

	ship->setShieldRechargeRate(rechargeRate, false, ship1);

	ship->setFrontShieldMax(frontHitpoints, false, ship3);
	ship->setRearShieldMax(rearHitpoints, false, ship3);

	ship->setFrontShield(frontHitpoints, false, ship6);
	ship->setRearShield(rearHitpoints, false, ship6);

	if (notifyClient) {
		ship1->close();
		ship3->close();
		ship6->close();

		pilot->sendMessage(ship1);
		pilot->broadcastMessage(ship3, true);
		pilot->broadcastMessage(ship6, true);
	}
}

void ShipShieldComponentImplementation::uninstall(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::uninstall(pilot, ship, slot, notifyClient);

	DeltaMessage* ship1 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;
	DeltaMessage* ship3 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 3) : nullptr;
	DeltaMessage* ship6 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 6) : nullptr;

	ship->setShieldRechargeRate(0, false, ship1);

	ship->setFrontShieldMax(0, false, ship3);
	ship->setRearShieldMax(0, false, ship3);

	ship->setFrontShield(0, false, ship6);
	ship->setRearShield(0, false, ship6);

	if (notifyClient) {
		ship1->close();
		ship3->close();
		ship6->close();

		pilot->sendMessage(ship1);
		pilot->sendMessage(ship3);
		pilot->sendMessage(ship6);
	}
}
