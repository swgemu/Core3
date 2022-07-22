#include "server/zone/objects/ship/components/ShipArmorComponent.h"
#include "server/zone/packets/DeltaMessage.h"
#include "server/zone/objects/ship/ShipObject.h"

void ShipArmorComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
    alm->insertAttribute("ship_component_armor", String::valueOf(Math::getPrecision(getArmor(), 1)));
    alm->insertAttribute("ship_component_hitpoints", String::valueOf(Math::getPrecision(getHitpoints(), 1)));
    alm->insertAttribute("ship_component_mass", String::valueOf(Math::getPrecision(getMass(), 1)));
}

void ShipArmorComponentImplementation::install(CreatureObject* owner, ShipObject *ship, int slot, bool notifyClient) {
    ShipComponentImplementation::install(owner, ship, slot, notifyClient);
    
    DeltaMessage *message = notifyClient ? new DeltaMessage(ship->getObjectID(), 'SHIP', 3) : NULL;
    ship->setComponentMaxHitpoints(slot, getMaxHitpoints(), message);
    ship->setComponentHitpoints(slot, getHitpoints(), message);
    ship->setComponentArmor(slot, getArmor(), message);
    ship->setComponentMaxArmor(slot, getMaxArmor(), message);
    ship->setComponentMass(slot, getMass(), message);

    if (notifyClient) {
        message->close();
        owner->sendMessage(message);
    }
}
