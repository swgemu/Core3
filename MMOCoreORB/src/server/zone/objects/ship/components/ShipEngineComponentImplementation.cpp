#include "server/zone/objects/ship/components/ShipEngineComponent.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "templates/tangible/SharedShipObjectTemplate.h"

void ShipEngineComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<SharedTangibleObjectTemplate*>(templateData);

	if (shot != nullptr) {
		maxPitch = shot->getShipPitch() * Math::DEG2RAD;
		maxRoll = shot->getShipRoll() * Math::DEG2RAD;
		maxYaw = shot->getShipYaw() * Math::DEG2RAD;
		maxSpeed = shot->getShipSpeed();

		acceleration = maxSpeed;
		deceleration = maxSpeed;
	}
}

void ShipEngineComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);

	for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
		const String& attribute = values->getExperimentalPropertySubtitle(i);
		float value = values->getCurrentValue(attribute);

		if (attribute == "ship_component_engine_pitch_rate_maximum") {
			maxPitch = value * Math::DEG2RAD;
		} else if (attribute == "ship_component_engine_roll_rate_maximum") {
			maxRoll = value * Math::DEG2RAD;
		} else if (attribute == "ship_component_engine_yaw_rate_maximum") {
			maxYaw = value * Math::DEG2RAD;
		} else if (attribute == "ship_component_engine_speed_maximum") {
			maxSpeed = value;
		}
	}
}

void ShipEngineComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	ShipComponentImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_engine_yaw_rate_maximum", String::valueOf(Math::getPrecision(maxYaw * Math::RAD2DEG, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_engine_pitch_rate_maximum", String::valueOf(Math::getPrecision(maxPitch * Math::RAD2DEG, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_engine_roll_rate_maximum", String::valueOf(Math::getPrecision(maxRoll * Math::RAD2DEG, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_engine_speed_maximum", String::valueOf(Math::getPrecision(maxSpeed, 1)));

	if (craftersName.isEmpty()) {
		alm->insertAttribute("@obj_attr_n:reverseengineeringlevel", getReverseEngineeringLevel());
	}
}

void ShipEngineComponentImplementation::install(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::install(pilot, ship, slot, notifyClient);

	DeltaMessage* ship1 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;
	DeltaMessage* ship6 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 6) : nullptr;

	ship->setEngineMaxPitchRate(maxPitch, false, ship1);
	ship->setEngineMaxYawRate(maxYaw, false, ship1);
	ship->setEngineMaxRollRate(maxRoll, false, ship1);
	ship->setEnginePitchRate(maxPitch, false, ship1);
	ship->setEngineYawRate(maxYaw, false, ship1);
	ship->setEngineRollRate(maxRoll, false, ship1);
	ship->setEngineAccelerationRate(maxSpeed, false, ship1);
	ship->setEngineDecelerationRate(maxSpeed, false, ship1);
	ship->setMaxSpeed(maxSpeed, false, ship1);

	ship->setMaxPitchRate(maxPitch, false, ship6);
	ship->setMaxYawRate(maxYaw, false, ship6);
	ship->setMaxRollRate(maxRoll, false, ship6);
	ship->setCurrentPitchRate(maxPitch, false, ship6);
	ship->setCurrentYawRate(maxYaw, false, ship6);
	ship->setCurrentRollRate(maxRoll, false, ship6);
	ship->setShipAccelerationRate(maxSpeed, false, ship6);
	ship->setShipDecelerationRate(maxSpeed, false, ship6);
	ship->setCurrentSpeed(maxSpeed, false, ship6);

	if (notifyClient) {
		ship1->close();
		ship6->close();

		pilot->sendMessage(ship1);
		pilot->sendMessage(ship6);
	}
}

void ShipEngineComponentImplementation::uninstall(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::uninstall(pilot, ship, slot, notifyClient);

	DeltaMessage* ship1 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;
	DeltaMessage* ship6 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 6) : nullptr;

	ship->setEnginePitchRate(0.f, false, ship1);
	ship->setEngineYawRate(0.f, false, ship1);
	ship->setEngineRollRate(0.f, false, ship1);
	ship->setEngineMaxPitchRate(0.f, false, ship1);
	ship->setEngineMaxYawRate(0.f, false, ship1);
	ship->setEngineMaxRollRate(0.f, false, ship1);
	ship->setEngineAccelerationRate(0.f, false, ship1);
	ship->setEngineDecelerationRate(0.f, false, ship1);
	ship->setMaxSpeed(0.f, false);

	ship->setMaxPitchRate(0.f, false, ship6);
	ship->setMaxYawRate(0.f, false, ship6);
	ship->setMaxRollRate(0.f, false, ship6);
	ship->setCurrentPitchRate(0.f, false, ship6);
	ship->setCurrentYawRate(0.f, false, ship6);
	ship->setCurrentRollRate(0.f, false, ship6);
	ship->setShipAccelerationRate(0.f, false, ship6);
	ship->setShipDecelerationRate(0.f, false, ship6);
	ship->setCurrentSpeed(0.f, false, ship6);

	if (notifyClient) {
		ship1->close();
		ship6->close();

		pilot->sendMessage(ship1);
		pilot->broadcastMessage(ship6, true);
	}
}
