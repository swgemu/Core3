#include "server/zone/objects/ship/components/ShipComponent.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/packets/DeltaMessage.h"


void ShipComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
    ComponentImplementation::loadTemplateData(templateData);
    SharedTangibleObjectTemplate *tmpl = static_cast<SharedTangibleObjectTemplate*>(templateData);
    if (tmpl == NULL) {
        error("NULL Template");
    }

    float cost = tmpl->getShipEnergyConsumption();
    float arm = armorMax = tmpl->getShipArmor();
    float hp = hitpointsMax = tmpl->getShipHitpoints();
    float ma = tmpl->getShipMass();
    if (cost > 0)
        energyCost = cost;

    if (arm > 0)
        armor = arm;

    if (hp > 0)
        hitpoints = hp;

    if (ma > 0)
        mass = ma;
}

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

void ShipComponentImplementation::updateComponentData(bool notifyClient) {
	ManagedReference<ShipObject*> strong = ship;
	if (strong == nullptr || slot == -1)
		return;

	Reference<CreatureObject*> creo = strong->getOwner().get().castTo<CreatureObject*>();
	DeltaMessage *delta = notifyClient ? new DeltaMessage(strong->getObjectID(), 'SHIP', 3) : NULL;

	strong->setComponentOptions(slot, flags, delta);

	if (!delta || !creo)
		return;

	delta->close();
	creo->broadcastMessage(delta, true, true);
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
