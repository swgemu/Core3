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

	for (int i = 0; i < values->getTotalExperimentalAttributes(); ++i) {
		const auto& attribute = values->getAttribute(i);
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

	auto deltaVector = notifyClient ? ship->getDeltaVector() : nullptr;

	ship->setEngineMaxPitchRate(enginePitchRateMaximum, false, nullptr, deltaVector);
	ship->setEngineMaxYawRate(engineYawRateMaximum, false, nullptr, deltaVector);
	ship->setEngineMaxRollRate(engineRollRateMaximum, false, nullptr, deltaVector);
	ship->setEnginePitchRate(enginePitchAccelerationRate, false, nullptr, deltaVector);
	ship->setEngineYawRate(engineYawAccelerationRate, false, nullptr, deltaVector);
	ship->setEngineRollRate(engineRollAccelerationRate, false, nullptr, deltaVector);
	ship->setEngineAccelerationRate(engineAccelerationRate, false, nullptr, deltaVector);
	ship->setEngineDecelerationRate(engineDecelerationRate, false, nullptr, deltaVector);
	ship->setMaxSpeed(engineSpeedMaximum, false, nullptr, deltaVector);

	ship->setMaxPitchRate(enginePitchRateMaximum, false, nullptr, deltaVector);
	ship->setMaxYawRate(engineYawRateMaximum, false, nullptr, deltaVector);
	ship->setMaxRollRate(engineRollRateMaximum, false, nullptr, deltaVector);
	ship->setCurrentPitchRate(enginePitchAccelerationRate, false, nullptr, deltaVector);
	ship->setCurrentYawRate(engineYawAccelerationRate, false, nullptr, deltaVector);
	ship->setCurrentRollRate(engineRollAccelerationRate, false, nullptr, deltaVector);
	ship->setShipAccelerationRate(engineAccelerationRate, false, nullptr, deltaVector);
	ship->setShipDecelerationRate(engineDecelerationRate, false, nullptr, deltaVector);
	ship->setCurrentSpeed(engineSpeedMaximum, false, nullptr, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(ship, pilot);
	}
}

void ShipEngineComponentImplementation::uninstall(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::uninstall(pilot, ship, slot, notifyClient);

	auto deltaVector = notifyClient ? ship->getDeltaVector() : nullptr;

	ship->setEnginePitchRate(0.f, false, nullptr, deltaVector);
	ship->setEngineYawRate(0.f, false, nullptr, deltaVector);
	ship->setEngineRollRate(0.f, false, nullptr, deltaVector);
	ship->setEngineMaxPitchRate(0.f, false, nullptr, deltaVector);
	ship->setEngineMaxYawRate(0.f, false, nullptr, deltaVector);
	ship->setEngineMaxRollRate(0.f, false, nullptr, deltaVector);
	ship->setEngineAccelerationRate(0.f, false, nullptr, deltaVector);
	ship->setEngineDecelerationRate(0.f, false, nullptr, deltaVector);
	ship->setMaxSpeed(0.f, false);

	ship->setMaxPitchRate(0.f, false, nullptr, deltaVector);
	ship->setMaxYawRate(0.f, false, nullptr, deltaVector);
	ship->setMaxRollRate(0.f, false, nullptr, deltaVector);
	ship->setCurrentPitchRate(0.f, false, nullptr, deltaVector);
	ship->setCurrentYawRate(0.f, false, nullptr, deltaVector);
	ship->setCurrentRollRate(0.f, false, nullptr, deltaVector);
	ship->setShipAccelerationRate(0.f, false, nullptr, deltaVector);
	ship->setShipDecelerationRate(0.f, false, nullptr, deltaVector);
	ship->setCurrentSpeed(0.f, false, nullptr, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(ship, pilot);
	}
}
