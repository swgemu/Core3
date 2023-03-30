#include "server/zone/objects/ship/components/ShipEngineComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/DeltaMessage.h"

void ShipEngineComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<SharedTangibleObjectTemplate*>(templateData);

	if (shot != nullptr) {
		float pitch = shot->getShipPitch() * Math::DEG2RAD;
		float yaw = shot->getShipYaw() * Math::DEG2RAD;
		float roll = shot->getShipRoll() * Math::DEG2RAD;
		float speed = shot->getShipSpeed();

		enginePitchAccelerationRate = pitch;
		engineYawAccelerationRate = yaw;
		engineRollAccelerationRate = roll;

		enginePitchRateMaximum = pitch;
		engineYawRateMaximum = yaw;
		engineRollRateMaximum = roll;

		engineAccelerationRate = speed * 0.8f;
		engineDecelerationRate = speed * 0.6f;
		engineSpeedMaximum = speed;
	}
}

void ShipEngineComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);

	for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
		const auto& attribute = values->getExperimentalPropertySubtitle(i);
		auto value = values->getCurrentValue(attribute);

		if (attribute == "ship_component_engine_pitch_rate_maximum") {
			float pitch = value * Math::DEG2RAD;

			enginePitchAccelerationRate = pitch;
			enginePitchRateMaximum = pitch;
		} else if (attribute == "ship_component_engine_yaw_rate_maximum") {
			float yaw = value * Math::DEG2RAD;

			engineYawAccelerationRate = yaw;
			engineYawRateMaximum = yaw;
		} else if (attribute == "ship_component_engine_roll_rate_maximum") {
			float roll = value * Math::DEG2RAD;

			engineRollAccelerationRate = roll;
			engineRollRateMaximum = roll;
		} else if (attribute == "ship_component_engine_speed_maximum") {
			engineAccelerationRate = value * 0.8f;
			engineDecelerationRate = value * 0.6f;
			engineSpeedMaximum = value;
		}
	}
}

void ShipEngineComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	ShipComponentImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_engine_pitch_rate_maximum", String::valueOf(Math::getPrecision(enginePitchRateMaximum * Math::RAD2DEG, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_engine_yaw_rate_maximum", String::valueOf(Math::getPrecision(engineYawRateMaximum * Math::RAD2DEG, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_engine_roll_rate_maximum", String::valueOf(Math::getPrecision(engineRollRateMaximum * Math::RAD2DEG, 1)));
	alm->insertAttribute("@obj_attr_n:ship_component.ship_component_engine_speed_maximum", String::valueOf(Math::getPrecision(engineSpeedMaximum, 1)));

	if (reverseEngineeringLevel != 0) {
		alm->insertAttribute("@obj_attr_n:reverseengineeringlevel", reverseEngineeringLevel);
	}
}

void ShipEngineComponentImplementation::install(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::install(pilot, ship, slot, notifyClient);

	DeltaMessage* ship1 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;
	DeltaMessage* ship6 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 6) : nullptr;

	ship->setEngineMaxPitchRate(enginePitchRateMaximum, false, ship1);
	ship->setEngineMaxYawRate(engineYawRateMaximum, false, ship1);
	ship->setEngineMaxRollRate(engineRollRateMaximum, false, ship1);
	ship->setEnginePitchRate(enginePitchAccelerationRate, false, ship1);
	ship->setEngineYawRate(engineYawAccelerationRate, false, ship1);
	ship->setEngineRollRate(engineRollAccelerationRate, false, ship1);
	ship->setEngineAccelerationRate(engineAccelerationRate, false, ship1);
	ship->setEngineDecelerationRate(engineDecelerationRate, false, ship1);
	ship->setMaxSpeed(engineSpeedMaximum, false, ship1);

	ship->setMaxPitchRate(enginePitchRateMaximum, false, ship6);
	ship->setMaxYawRate(engineYawRateMaximum, false, ship6);
	ship->setMaxRollRate(engineRollRateMaximum, false, ship6);
	ship->setCurrentPitchRate(enginePitchAccelerationRate, false, ship6);
	ship->setCurrentYawRate(engineYawAccelerationRate, false, ship6);
	ship->setCurrentRollRate(engineRollAccelerationRate, false, ship6);
	ship->setShipAccelerationRate(engineAccelerationRate, false, ship6);
	ship->setShipDecelerationRate(engineDecelerationRate, false, ship6);
	ship->setCurrentSpeed(engineSpeedMaximum, false, ship6);

	if (notifyClient) {
		ship1->close();
		ship6->close();

		pilot->sendMessage(ship1);
		ship->broadcastMessage(ship6, true);
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
		ship->broadcastMessage(ship6, true);
	}
}
