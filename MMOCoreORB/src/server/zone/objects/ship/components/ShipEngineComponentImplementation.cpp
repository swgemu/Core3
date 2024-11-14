#include "server/zone/objects/ship/components/ShipEngineComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/DeltaMessage.h"

void ShipEngineComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);

	auto shot = dynamic_cast<ShipComponentTemplate*>(templateData);

	if (shot != nullptr) {
		const auto& attributeMap = shot->getAttributeMap();

		for (int i = 0; i < attributeMap.size(); ++i) {
			const auto& attribute = attributeMap.elementAt(i).getKey();
			float value = attributeMap.elementAt(i).getValue();

			if (attribute == "maxPitch") {
				float pitch = value * Math::DEG2RAD;

				enginePitchAccelerationRate = pitch;
				enginePitchRateMaximum = pitch;
			} else if (attribute == "maxYaw") {
				float yaw = value * Math::DEG2RAD;

				engineYawAccelerationRate = yaw;
				engineYawRateMaximum = yaw;
			} else if (attribute == "maxRoll") {
				float roll = value * Math::DEG2RAD;

				engineRollAccelerationRate = roll;
				engineRollRateMaximum = roll;
			} else if (attribute == "maxSpeed") {
				engineAccelerationRate = value * 0.8f;
				engineDecelerationRate = value * 0.6f;
				engineSpeedMaximum = value;
			}
		}
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

	ship->setEnginePitchRate(enginePitchRateMaximum, false, nullptr, deltaVector);
	ship->setEngineYawRate(engineYawRateMaximum, false, nullptr, deltaVector);
	ship->setEngineRollRate(engineRollRateMaximum, false, nullptr, deltaVector);
	ship->setEngineMaxSpeed(engineSpeedMaximum, false, nullptr, deltaVector);

	ship->setActualPitchRate(enginePitchRateMaximum, false, nullptr, deltaVector);
	ship->setActualYawRate(engineYawRateMaximum, false, nullptr, deltaVector);
	ship->setActualRollRate(engineRollRateMaximum, false, nullptr, deltaVector);
	ship->setActualMaxSpeed(engineSpeedMaximum, false, nullptr, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(ship);
	}
}

void ShipEngineComponentImplementation::uninstall(CreatureObject* pilot, ShipObject* ship, int slot, bool notifyClient) {
	ShipComponentImplementation::uninstall(pilot, ship, slot, notifyClient);

	auto deltaVector = notifyClient ? ship->getDeltaVector() : nullptr;

	ship->setEnginePitchRate(0.f, false, nullptr, deltaVector);
	ship->setEngineYawRate(0.f, false, nullptr, deltaVector);
	ship->setEngineRollRate(0.f, false, nullptr, deltaVector);
	ship->setEngineMaxSpeed(0.f, false, nullptr, deltaVector);

	ship->setActualPitchRate(0.f, false, nullptr, deltaVector);
	ship->setActualYawRate(0.f, false, nullptr, deltaVector);
	ship->setActualRollRate(0.f, false, nullptr, deltaVector);
	ship->setActualMaxSpeed(0.f, false, nullptr, deltaVector);

	if (deltaVector != nullptr) {
		deltaVector->sendMessages(ship);
	}
}
