#include "server/zone/objects/ship/components/ShipEngineComponent.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

#define RAD_PER_DEG 57.2958f
#define DEG_PER_RAD 1.0f / RAD_PER_DEG
void ShipEngineComponentImplementation::initializeTransientMembers() {
	if (maxPitch < 1.0f)
		maxPitch = 1.0f;

	if (maxRoll < 1.0f)
		maxRoll = 1.0f;

	if (maxYaw < 1.0f)
		maxYaw = 1.0f;
}

void ShipEngineComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipComponentImplementation::loadTemplateData(templateData);
	SharedTangibleObjectTemplate* tmpl = static_cast<SharedTangibleObjectTemplate*>(templateData);
	if (tmpl == nullptr) {
		error("nullptr Template");
	}

	maxPitch = tmpl->getShipPitch();
	maxYaw = tmpl->getShipYaw();
	maxRoll = tmpl->getShipRoll();
	maxSpeed = tmpl->getShipSpeed();
}

void ShipEngineComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
		String attribute;
		float current;

		attribute = values->getExperimentalPropertySubtitle(i);
		current = values->getCurrentValue(attribute);

		if (attribute == "ship_component_engine_pitch_rate_maximum") {
			maxPitch = Math::max(1.0f, current * DEG_PER_RAD);
		} else if (attribute == "ship_component_engine_roll_rate_maximum") {
			maxRoll = Math::max(1.0f, current * DEG_PER_RAD);
		} else if (attribute == "ship_component_engine_yaw_rate_maximum") {
			maxYaw = Math::max(1.0f, current * DEG_PER_RAD);
		} else if (attribute == "ship_component_engine_speed_maximum") {
			maxSpeed = current;
		}
	}
	ShipComponentImplementation::updateCraftingValues(values, firstUpdate);
}

void ShipEngineComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	ShipComponentImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("ship_component_engine_yaw_rate_maximum", String::valueOf(Math::getPrecision(maxYaw * RAD_PER_DEG, 1)));
	alm->insertAttribute("ship_component_engine_pitch_rate_maximum", String::valueOf(Math::getPrecision(maxPitch * RAD_PER_DEG, 2)));
	alm->insertAttribute("ship_component_engine_roll_rate_maximum", String::valueOf(Math::getPrecision(maxRoll * RAD_PER_DEG, 1)));
	alm->insertAttribute("ship_component_engine_speed_maximum", String::valueOf(Math::getPrecision(maxSpeed, 1)));
}

void ShipEngineComponentImplementation::install(CreatureObject* owner, ShipObject* ship, int slot, bool notifyClient) {
	// TODO: acceleration/deceleration rate?
	DeltaMessage* message1 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : nullptr;
	ship->setEnginePitchRate(maxPitch, notifyClient, message1);
	ship->setEngineYawRate(maxYaw, notifyClient, message1);
	ship->setEngineRollRate(maxRoll, notifyClient, message1);
	ship->setEngineMaxPitchRate(maxPitch, notifyClient, message1);
	ship->setEngineMaxYawRate(maxYaw, notifyClient, message1);
	ship->setEngineMaxRollRate(maxRoll, notifyClient, message1);
	ship->setEngineAccelerationRate(acceleration, notifyClient, message1);
	ship->setEngineDecelerationRate(deceleration, notifyClient, message1);
	ship->setMaxSpeed(maxSpeed, notifyClient, message1);
	ship->setChassisSpeed(1.0f, notifyClient, message1);
	ship->setEnergyCost(slot, getEnergyCost(), message1);
	ship->setComponentMass(slot, getMass(), message1);

	DeltaMessage* message3 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 3) : nullptr;
	ship->setComponentMaxHitpoints(slot, getMaxHitpoints(), message3);
	ship->setComponentHitpoints(slot, getHitpoints(), message3);
	ship->setComponentArmor(slot, getArmor(), message3);
	ship->setComponentMaxArmor(slot, getMaxArmor(), message3);

	DeltaMessage* message6 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 6) : nullptr;
	ship->setShipAccelerationRate(acceleration, notifyClient, message6);
	ship->setShipDecelerationRate(deceleration, notifyClient, message6);

	ship->setCurrentPitchRate(maxPitch, notifyClient, message6);
	ship->setCurrentYawRate(maxYaw, notifyClient, message6);
	ship->setCurrentRollRate(maxRoll, notifyClient, message6);

	ship->setMaxPitchRate(maxPitch, notifyClient, message6);
	ship->setMaxYawRate(maxYaw, notifyClient, message6);
	ship->setMaxRollRate(maxRoll, notifyClient, message6);

	if (notifyClient) {
		message1->close();
		message3->close();
		message6->close();
		owner->sendMessage(message1);
		owner->sendMessage(message3);
		owner->sendMessage(message6);
	}
}
