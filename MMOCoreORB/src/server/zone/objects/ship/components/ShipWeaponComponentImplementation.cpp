#include "server/zone/objects/ship/components/ShipWeaponComponent.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

void ShipWeaponComponentImplementation::updateCraftingValues(CraftingValues* values,
                                                       bool firstUpdate) {
    for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
        String attribute;
        float min;
        float max;
        float current;
        
        attribute = values->getExperimentalPropertySubtitle(i);
        min = values->getMinValue(attribute);
        max = values->getMaxValue(attribute);
        current = values->getCurrentValue(attribute);
        
        if (attribute == "effective_armor") {
            armorEffectiveness = current * 0.001f;
        } else if(attribute == "damage_max") {
            maxDamage = current;
        } else if (attribute == "damage_min") {
            minDamage = current;
        } else if (attribute == "energy_per_shot") {
            energyPerShot = current;
        } else if (attribute == "refire_rate") {
            refireRate = current * 0.001f;
        } else if (attribute == "effective_shields") {
            shieldEffectiveness = current * 0.001f;
        }
    }
    ShipComponentImplementation::updateCraftingValues(values, firstUpdate);
}

void ShipWeaponComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
    ShipComponentImplementation::loadTemplateData(templateData);
    SharedTangibleObjectTemplate *tmpl = static_cast<SharedTangibleObjectTemplate*>(templateData);
    if (tmpl == NULL) {
        error("NULL Template");
    }

    armorEffectiveness = tmpl->getWeaponArmorEffectiveness();
    shieldEffectiveness = tmpl->getWeaponShieldEffectiveness();
    maxDamage = tmpl->getWeaponMaxDamage();
    minDamage = tmpl->getWeaponMinDamage();
    refireRate = tmpl->getWeaponRefireRate();
    energyPerShot = tmpl->getEnergyPerShot();
}

void ShipWeaponComponentImplementation::fillAttributeList(AttributeListMessage* alm,
                                                    CreatureObject* object) {
    ShipComponentImplementation::fillAttributeList(alm, object);
    
    
    StringBuffer display;
    display << Math::getPrecision(minDamage, 3) << " - " << Math::getPrecision(maxDamage, 3);
    alm->insertAttribute("ship_component_weapon_damage", display.toString());

    alm->insertAttribute("ship_component_weapon_effectiveness_shields", String::valueOf(Math::getPrecision(shieldEffectiveness, 3)));
    alm->insertAttribute("ship_component_weapon_effectiveness_armor", String::valueOf(Math::getPrecision(armorEffectiveness, 3)));
    alm->insertAttribute("ship_component_weapon_energy_per_shot", String::valueOf(Math::getPrecision(energyPerShot, 1)));
    alm->insertAttribute("ship_component_weapon_refire_rate", String::valueOf(Math::getPrecision(refireRate, 3)));
    
}

void ShipWeaponComponentImplementation::install(CreatureObject* owner, ShipObject* ship, int slot, bool notifyClient) {
    ShipComponentImplementation::install(owner, ship, slot, notifyClient);
    
    DeltaMessage *message = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : NULL;
    ship->setEnergyCost(slot, getEnergyCost(), message);
    ship->setComponentMass(slot, getMass(), message);
    ship->setMaxDamage(slot, maxDamage, message);
    ship->setMinDamage(slot, minDamage, message);
    ship->setShieldEffectiveness(slot, shieldEffectiveness, message);
    ship->setArmorEffectiveness(slot, armorEffectiveness, message);
    ship->setEnergyPerShot(slot, energyPerShot, message);
    ship->setRefireRate(slot, refireRate, message);

    
    DeltaMessage *message2 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 3) : NULL;
    ship->setComponentMaxHitpoints(slot, getMaxHitpoints(), message2);
    ship->setComponentHitpoints(slot, getHitpoints(), message2);
    ship->setComponentArmor(slot, getArmor(), message2);
    ship->setComponentMaxArmor(slot, getMaxArmor(), message2);

    
    DeltaMessage *message3 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 4) : NULL;
    ship->setRefireEfficiency(slot, 1.0f, message3);
    
    if (notifyClient) {
        message->close();
        message2->close();
        message3->close();
        owner->sendMessage(message);
        owner->sendMessage(message2);
        owner->sendMessage(message3);
    }
}
