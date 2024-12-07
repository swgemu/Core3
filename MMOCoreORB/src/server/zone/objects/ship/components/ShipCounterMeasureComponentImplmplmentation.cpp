#include "server/zone/objects/ship/components/ShipCounterMeasureComponent.h"

void ShipCounterMeasureComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
    alm->insertAttribute("@obj_attr_n:volume", volume);

    if (!craftersName.isEmpty()) {
        alm->insertAttribute("crafter", craftersName);
    }

    if (!objectSerial.isEmpty()) {
        alm->insertAttribute("serial_number", objectSerial);
    }

    alm->insertAttribute("@obj_attr_n:chaff_effectiveness_min", String::valueOf(Math::getPrecision(chaffMinEffectiveness, 6)));
    alm->insertAttribute("@obj_attr_n:chaff_effectiveness_max", String::valueOf(Math::getPrecision(chaffMaxEffectiveness, 6)));
    alm->insertAttribute("@obj_attr_n:refire_rate", String::valueOf(Math::getPrecision(refireRate, 7)));
    alm->insertAttribute("@obj_attr_n:ammo", String::valueOf(Math::getPrecision(ammunition, 0)));
}