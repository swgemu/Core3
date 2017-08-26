#include "server/zone/objects/ship/components/ShipComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/DeltaMessage.h"

void ShipComponentImplementation::updateCraftingValues(CraftingValues* values,
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
        
        if (attribute == "energy_maintenance" || attribute == "ship_component_energy_required") {
            energyCost = (min + max) - current;
        } else if(attribute == "energy_efficiency") {
            energyEfficiency = current;
        } else if (attribute == "efficiency") {
            efficiency = current;
        } else if (attribute == "armorhpmax" || attribute == "ship_component_armor") {
            armor = armorMax = current;
        } else if (attribute == "hitpointsmax" || attribute == "ship_component_hitpoints") {
            hitpoints = hitpointsMax = current;
        } else if (attribute == "mass" || attribute == "ship_component_mass") {
            mass = (min + max ) - current;
        }
        
        info("Attribute: " + attribute + " min: " + String::valueOf(min) + " max: " + String::valueOf(max) + " current: " + String::valueOf(current), true);
    }
    ComponentImplementation::updateCraftingValues(values, firstUpdate);
}



void ShipComponentImplementation::fillAttributeList(AttributeListMessage* alm,
                                                CreatureObject* object) {
    alm->insertAttribute("ship_component_armor", String::valueOf(Math::getPrecision(getArmor(), 1)));
    alm->insertAttribute("ship_component_hitpoints", String::valueOf(Math::getPrecision(getHitpoints(), 1)));
    if (getEnergyCost() > 0.0f)
        alm->insertAttribute("ship_component_energy_required", String::valueOf(Math::getPrecision(getEnergyCost(), 1)));
    alm->insertAttribute("ship_component_mass", String::valueOf(Math::getPrecision(getMass(), 1)));
}


void ShipComponentImplementation::install(CreatureObject* owner, ShipObject* ship, int slot, bool notifyClient) {
//    ShipComponentData* component = ShipManager::instance()->getShipComponentFromTemplate(getObjectTemplate()->getFullTemplateString());
//    
//    DeltaMessage* message = new DeltaMessage(getObjectID(), 'SHIP', 6);
//    message->startUpdate(15);
//    shipComponents.set(slot, component->getName().hashCode(), message);
//    message->close();
//    owner->sendMessage(message);
//    
//    
}
