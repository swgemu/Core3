#include "server/zone/objects/ship/components/ShipEngineComponent.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

#define RAD_PER_DEG 57.2958f
#define DEG_PER_RAD 1.0f/RAD_PER_DEG
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
    SharedTangibleObjectTemplate *tmpl = static_cast<SharedTangibleObjectTemplate*>(templateData);
    if (tmpl == NULL) {
        error("NULL Template");
    }

    maxPitch = tmpl->getShipPitch();
    maxYaw = tmpl->getShipYaw();
    maxRoll = tmpl->getShipRoll();
    maxSpeed = tmpl->getShipSpeed();
}

void ShipEngineComponentImplementation::updateCraftingValues(CraftingValues* values,
                                                       bool firstUpdate) {
    for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
        String attribute;
        float current;
        
        attribute = values->getExperimentalPropertySubtitle(i);
        current = values->getCurrentValue(attribute);
        
        if (attribute == "ship_component_engine_pitch_rate_maximum") {
            maxPitch = Math::max(1.0f, current * DEG_PER_RAD);
        } else if(attribute == "ship_component_engine_roll_rate_maximum") {
            maxRoll = Math::max(1.0f, current * DEG_PER_RAD);
        } else if (attribute == "ship_component_engine_yaw_rate_maximum") {
            maxYaw = Math::max(1.0f, current * DEG_PER_RAD);
        } else if (attribute == "ship_component_engine_speed_maximum") {
            maxSpeed = current;
        }
    }
    ShipComponentImplementation::updateCraftingValues(values, firstUpdate);
}



void ShipEngineComponentImplementation::fillAttributeList(AttributeListMessage* alm,
                                                    CreatureObject* object) {
    ShipComponentImplementation::fillAttributeList(alm, object);

    alm->insertAttribute("ship_component_engine_yaw_rate_maximum", String::valueOf(Math::getPrecision(maxYaw * RAD_PER_DEG, 1)));
    alm->insertAttribute("ship_component_engine_pitch_rate_maximum", String::valueOf(Math::getPrecision(maxPitch * RAD_PER_DEG, 2)));
    alm->insertAttribute("ship_component_engine_roll_rate_maximum", String::valueOf(Math::getPrecision(maxRoll * RAD_PER_DEG, 1)));
    alm->insertAttribute("ship_component_engine_speed_maximum", String::valueOf(Math::getPrecision(maxSpeed, 1)));
}

void ShipEngineComponentImplementation::install(CreatureObject* owner, ShipObject* ship, int slot, bool notifyClient) {
    //TODO: acceleration/deceleration rate?
    DeltaMessage *message = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : NULL;
    ship->setEnginePitchRate(maxPitch, notifyClient, message);
    ship->setEngineYawRate(maxYaw, notifyClient, message);
    ship->setEngineRollRate(maxRoll, notifyClient, message);
    ship->setEngineMaxPitchRate(maxPitch, notifyClient, message);
    ship->setEngineMaxYawRate(maxYaw, notifyClient, message);
    ship->setEngineMaxRollRate(maxRoll, notifyClient, message);
    ship->setEngineAccelerationRate(acceleration, notifyClient, message);
    ship->setEngineDecelerationRate(deceleration, notifyClient, message);
    ship->setMaxSpeed(maxSpeed, notifyClient, message);
    ship->setChassisSpeed(1.0f, notifyClient, message);
    ship->setEnergyCost(slot, getEnergyCost(), message);
    ship->setComponentMass(slot, getMass(), message);

    
    DeltaMessage *message2 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 3) : NULL;
    ship->setComponentMaxHitpoints(slot, getMaxHitpoints(), message2);
    ship->setComponentHitpoints(slot, getHitpoints(), message2);
    ship->setComponentArmor(slot, getArmor(), message2);
    ship->setComponentMaxArmor(slot, getMaxArmor(), message2);

    DeltaMessage *message3 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 6) : NULL;
    ship->setShipAccelerationRate(acceleration, notifyClient, message);
    ship->setShipDecelerationRate(deceleration, notifyClient, message);
    ship->setMaxPitchRate(maxPitch, notifyClient, message);
    ship->setMaxRollRate(maxRoll, notifyClient, message);
    ship->setMaxYawRate(maxYaw, notifyClient, message);
    ship->setCurrentPitchRate(maxPitch, notifyClient, message);
    ship->setCurrentRollRate(maxRoll, notifyClient, message);
    ship->setCurrentYawRate(maxYaw, notifyClient, message);

    if (notifyClient) {
        message->close();
        message2->close();
        message3->close();
        owner->sendMessage(message);
        owner->sendMessage(message2);
        owner->sendMessage(message3);
    }
}
