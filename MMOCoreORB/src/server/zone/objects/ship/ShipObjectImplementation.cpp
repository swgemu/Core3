/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/ship/components/ShipComponent.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "system/lang/UnicodeString.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/ship/ShipObjectMessage1.h"
#include "server/zone/packets/ship/ShipObjectMessage3.h"
#include "server/zone/packets/ship/ShipObjectMessage4.h"
#include "server/zone/packets/ship/ShipObjectMessage6.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "templates/tangible/SharedShipObjectTemplate.h"
//#include "server/zone/packets/tangible/TangibleObjectMessage8.h"
//#include "server/zone/packets/tangible/TangibleObjectMessage9.h"

void ShipObjectImplementation::sendTo(SceneObject* player, bool doClose, bool forceLoadContainer) {
	//info("testing");
	TangibleObjectImplementation::sendTo(player, doClose, forceLoadContainer);
}

void ShipObjectImplementation::setShipName(const String& name, bool notifyClient) {
    shipName = name;
    shipNameCRC.update(name.hashCode(), false);
}

void ShipObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();
}

void ShipObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
    TangibleObjectImplementation::loadTemplateData(templateData);
    SharedShipObjectTemplate *shipTempl = dynamic_cast<SharedShipObjectTemplate*>(templateData);
    setShipName(shipTempl->getShipName());
}

void ShipObjectImplementation::updateCraftingValues(CraftingValues* values,
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
        info("Attribute: " + attribute + " min: " + String::valueOf(min) + " max: " + String::valueOf(max) + " current: " + String::valueOf(current), true);
    }
    TangibleObjectImplementation::updateCraftingValues(values, firstUpdate);
}

uint16 ShipObjectImplementation::getUniqueID() {
	uint32 hash = UnsignedLong::hashCode(getObjectID());
	uint16 id = (uint16) (hash ^ (hash >> 16));

	//info("uniqueId: 0x" + String::hexvalueOf(id), true);

	return id;
}

void ShipObjectImplementation::sendBaselinesTo(SceneObject* player) {
	//info("sending ship baselines", true);

	BaseMessage* ship3 = new ShipObjectMessage3(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(ship3);


	//if (player->getParent().get() == _this.getReferenceUnsafeStaticCast() || getRootParent().get() == player) {
		BaseMessage* ship4 = new ShipObjectMessage4(_this.getReferenceUnsafeStaticCast());
		player->sendMessage(ship4);
	
		BaseMessage* ship1 = new ShipObjectMessage1(_this.getReferenceUnsafeStaticCast());
		player->sendMessage(ship1);
	//}

	BaseMessage* ship6 = new ShipObjectMessage6(_this.getReferenceUnsafeStaticCast());
	player->sendMessage(ship6);
/*
	BaseMessage* ship8 = new TangibleObjectMessage8(_this);
	player->sendMessage(ship8);

	BaseMessage* ship9 = new TangibleObjectMessage9(_this);
	player->sendMessage(ship9);*/
}

ShipObject* ShipObjectImplementation::asShipObject() {
    return _this.getReferenceUnsafeStaticCast();
}

void ShipObjectImplementation::install(CreatureObject* owner, SceneObject* sceno, int slot, bool notifyClient) {
    String templateName = sceno->getObjectTemplate()->getFullTemplateString();

    ShipComponentData *component = ShipManager::instance()->getShipComponentFromTemplate(templateName);

    DeltaMessage *message = notifyClient ? new DeltaMessage(getObjectID(), 'SHIP', 6) : NULL;
    UnicodeString string = UnicodeString(component->getName());
    setComponentCRC(slot, component->getName().hashCode(), message);
    setComponentName(slot, string, message);
    if (message != NULL) {
        message->close();
        owner->sendMessage(message);
    }
    
    ManagedReference<ShipComponent*> shipComponent = dynamic_cast<ShipComponent*>(sceno);
    if (shipComponent != NULL) {
        shipComponent->install(owner, _this.getReferenceUnsafeStaticCast(), slot, notifyClient);
        shipComponent->destroyObjectFromWorld(true);
    }
}

void ShipObjectImplementation::uninstall(CreatureObject* owner, int slot, bool notifyClient) {
    DeltaMessage* message = new DeltaMessage(getObjectID(), 'SHIP', 6);
    message->startUpdate(15);
    shipComponents.set(slot, 0, message);
    message->close();
    owner->sendMessage(message);
}
