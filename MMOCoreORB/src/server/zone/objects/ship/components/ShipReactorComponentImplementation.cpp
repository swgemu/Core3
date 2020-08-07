#include "server/zone/objects/ship/components/ShipReactorComponent.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

void ShipReactorComponentImplementation::updateCraftingValues(CraftingValues* values,
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
        
        if (attribute == "ship_component_reactor_generation_rate") {
            reactorGenerationRate = current;
        }
        
    }
    ShipComponentImplementation::updateCraftingValues(values, firstUpdate);
}

void ShipReactorComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
    ShipComponentImplementation::loadTemplateData(templateData);
    SharedTangibleObjectTemplate *tmpl = static_cast<SharedTangibleObjectTemplate*>(templateData);
    if (tmpl == NULL) {
        error("NULL Template");
    }

    reactorGenerationRate = tmpl->getShipMaxEnergy();
}

void ShipReactorComponentImplementation::fillAttributeList(AttributeListMessage* alm,
                                                    CreatureObject* object) {
    ShipComponentImplementation::fillAttributeList(alm, object);
    
    alm->insertAttribute("ship_component_reactor_generation_rate", String::valueOf(Math::getPrecision(reactorGenerationRate, 1)));
}

void ShipReactorComponentImplementation::install(CreatureObject* owner, ShipObject* ship, int slot, bool notifyClient) {
    DeltaMessage *message = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : NULL;
    ship->setReactorGenerationRate(reactorGenerationRate, true, message);
    ship->setEnergyCost(slot, getEnergyCost(), message);
    ship->setComponentMass(slot, getMass(), message);

    
    DeltaMessage *message2 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 3) : NULL;
    ship->setComponentMaxHitpoints(slot, getMaxHitpoints(), message2);
    ship->setComponentHitpoints(slot, getHitpoints(), message2);
    ship->setComponentArmor(slot, getArmor(), message2);
    ship->setComponentMaxArmor(slot, getMaxArmor(), message2);

    if (notifyClient) {
        message->close();
        message2->close();
        owner->sendMessage(message);
        owner->sendMessage(message2);
    }
}
