#include "server/zone/objects/ship/components/ShipShieldComponent.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

void ShipShieldComponentImplementation::updateCraftingValues(CraftingValues* values,
                                                       bool firstUpdate) {
    for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
        String attribute = values->getExperimentalPropertySubtitle(i);
        float current = values->getCurrentValue(attribute);
        
        if (attribute == "ship_component_shield_hitpoints_back") {
            rearHitpoints = current;
        } else if(attribute == "ship_component_shield_hitpoints_front") {
            frontHitpoints = current;
        } else if (attribute == "ship_component_shield_recharge_rate") {
            rechargeRate = current;
        }
        
    }
    ShipComponentImplementation::updateCraftingValues(values, firstUpdate);
}

void ShipShieldComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
    ShipComponentImplementation::loadTemplateData(templateData);
    SharedTangibleObjectTemplate *tmpl = static_cast<SharedTangibleObjectTemplate*>(templateData);
    if (tmpl == NULL) {
        error("NULL Template");
    }

    rearHitpoints = tmpl->getShieldHitpointsRear();
    frontHitpoints = tmpl->getShieldHitpointsFront();
    rechargeRate = tmpl->getShipRechargeRate();
}

void ShipShieldComponentImplementation::fillAttributeList(AttributeListMessage* alm,
                                                    CreatureObject* object) {
    ShipComponentImplementation::fillAttributeList(alm, object);
    
    alm->insertAttribute("ship_component_shield_hitpoints_front", String::valueOf(Math::getPrecision(frontHitpoints, 1)));
    alm->insertAttribute("ship_component_shield_hitpoints_back", String::valueOf(Math::getPrecision(rearHitpoints, 1)));
    alm->insertAttribute("ship_component_shield_recharge_rate", String::valueOf(Math::getPrecision(rechargeRate, 1)));
}

void ShipShieldComponentImplementation::install(CreatureObject* owner, ShipObject* ship, int slot, bool notifyClient) {
    DeltaMessage *message = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : NULL;
    ship->setEnergyCost(slot, getEnergyCost(), message);
    ship->setShieldRechargeRate(slot, rechargeRate, message);
    ship->setComponentMass(slot, getMass(), message);

    
    DeltaMessage *message2 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 3) : NULL;
    ship->setComponentMaxHitpoints(slot, getMaxHitpoints(), message2);
    ship->setComponentHitpoints(slot, getHitpoints(), message2);
    ship->setComponentArmor(slot, getArmor(), message2);
    ship->setComponentMaxArmor(slot, getMaxArmor(), message2);
    ship->setFrontShieldMax(frontHitpoints+ship->getMaxFrontShield(), notifyClient, message2);
    ship->setRearShieldMax(rearHitpoints+ship->getMaxRearShield(), notifyClient, message2);

    
    DeltaMessage *message3 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 6) : NULL;
    ship->setFrontShield(frontHitpoints+ship->getFrontShield(), true, message3);
    ship->setRearShield(rearHitpoints+ship->getRearShield(), true, message3);
    
    if (notifyClient) {
        message->close();
        message2->close();
        message3->close();
        owner->sendMessage(message);
        owner->sendMessage(message2);
        owner->sendMessage(message3);
    }

}
