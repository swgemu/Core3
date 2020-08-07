#include "server/zone/objects/ship/components/ShipCapacitorComponent.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

void ShipCapacitorComponentImplementation::updateCraftingValues(CraftingValues* values,
                                                       bool firstUpdate) {
    for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
        String attribute = values->getExperimentalPropertySubtitle(i);
        float current = values->getCurrentValue(attribute);
        
        if (attribute == "ship_component_capacitor_energy") {
            capacitorEnergy = current;
        } else if(attribute == "ship_component_capacitor_energy_recharge_rate") {
            capacitorRechargeRate = current;
        }
        
    }
    ShipComponentImplementation::updateCraftingValues(values, firstUpdate);
}

void ShipCapacitorComponentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
    ShipComponentImplementation::loadTemplateData(templateData);
    SharedTangibleObjectTemplate *tmpl = static_cast<SharedTangibleObjectTemplate*>(templateData);
    if (tmpl == NULL) {
        error("NULL Template");
    }

    capacitorEnergy = tmpl->getShipMaxEnergy();
    capacitorRechargeRate = tmpl->getShipRechargeRate();
}

void ShipCapacitorComponentImplementation::fillAttributeList(AttributeListMessage* alm,
                                                    CreatureObject* object) {
    ShipComponentImplementation::fillAttributeList(alm, object);
    
    alm->insertAttribute("ship_component_capacitor_energy", String::valueOf(Math::getPrecision(capacitorEnergy, 1)));
    alm->insertAttribute("ship_component_capacitor_energy_recharge_rate", String::valueOf(Math::getPrecision(capacitorRechargeRate, 1)));
}

void ShipCapacitorComponentImplementation::install(CreatureObject* owner, ShipObject* ship, int slot, bool notifyClient) {
    DeltaMessage *message = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 1) : NULL;
    ship->setCapacitorRechargeRate(capacitorRechargeRate, notifyClient, message);
    ship->setEnergyCost(slot, getEnergyCost(), message);
    ship->setCapacitorMaxEnergy(capacitorEnergy, notifyClient, message);
    ship->setComponentMass(slot, getMass(), message);

    
    DeltaMessage *message2 = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 3) : NULL;
    ship->setComponentMaxHitpoints(slot, getMaxHitpoints(), message2);
    ship->setComponentHitpoints(slot, getHitpoints(), message2);
    ship->setComponentArmor(slot, getArmor(), message2);
    ship->setComponentMaxArmor(slot, getMaxArmor(), message2);

	StringBuffer buff;
	buff << "energyCost: " << getEnergyCost() << endl;
	buff << "recharge: " << capacitorRechargeRate << endl;
	buff << "energy: " << capacitorEnergy << endl;
	buff << "mass: " << getMass() << endl;
	buff << "Armor: " << getArmor() << endl;
	buff << "maxArmor: " << getMaxArmor() << endl;
	info(buff.toString(), true);
    
    if (notifyClient) {
        message->close();
        message2->close();
        owner->sendMessage(message);
        owner->sendMessage(message2);
    }

    
    ship->setCapacitorEnergy(capacitorEnergy, notifyClient);
}
