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
#include "server/zone/Zone.h"
#include "server/zone/ZoneClientSession.h"
#include "server/zone/packets/cell/UpdateCellPermissionsMessage.h"
#include "server/zone/packets/scene/SceneObjectCreateMessage.h"
#include "ComponentSlots.h"

//#include "server/zone/packets/tangible/TangibleObjectMessage8.h"
//#include "server/zone/packets/tangible/TangibleObjectMessage9.h"

void ShipObjectImplementation::sendTo(SceneObject* player, bool doClose, bool forceLoadContainer) {
	//info("testing");


    BaseMessage* msg = new SceneObjectCreateMessage(asSceneObject());
    player->sendMessage(msg);

    link(player, containmentType);

    try {
        sendBaselinesTo(player);
        SceneObjectImplementation::close(player);
        sendContainerObjectsTo(player, forceLoadContainer);

        sendSlottedObjectsTo(player);
    } catch (Exception& e) {
        error(e.getMessage());
        e.printStackTrace();
    }

    auto closeObjects = player->getCloseObjects();

    // for some reason client doesnt like when you send cell creatures while sending cells?
    for (int i = 0; i < cells.size(); ++i) {
        CellObject* cell = cells.get(i);

        auto perms = cell->getContainerPermissions();

        if (!perms->hasInheritPermissionsFromParent()) {
            CreatureObject* creo = cast<CreatureObject*>(player);

            if (creo != nullptr && !cell->checkContainerPermission(creo, ContainerPermissions::WALKIN)) {
                BaseMessage* perm = new UpdateCellPermissionsMessage(cell->getObjectID(), false);
                player->sendMessage(perm);
            }
        }

        if (!cell->isContainerLoaded())
            continue;

        for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
            ManagedReference<SceneObject*> containerObject = cell->getContainerObject(j);

            if (containerObject != nullptr && ((containerObject->isCreatureObject())))
                containerObject->sendTo(player, true, false);
        }
    }

    SceneObjectImplementation::sendSlottedObjectsTo(player);
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
	info("ShipName: " + shipTempl->getShipName(), true);
    setShipName(shipTempl->getShipName());
    auto portal = shipTempl->getPortalLayout();

    if (portal == nullptr)
        totalCellNumber = 0;
    else
        totalCellNumber = portal->getCellTotalNumber();
}

void ShipObjectImplementation::createChildObjects() {
    auto layout = getObjectTemplate()->getPortalLayout();
    if (layout == nullptr)
        return;

    for (int i = 0; i < totalCellNumber; ++i) {

        Reference<CellObject*> newCell = getZoneServer()->createObject(0xAD431713, getPersistenceLevel()).castTo<CellObject*>();

        if (newCell == nullptr) {
            error("could not create cell");
            continue;
        }

        Locker clocker(newCell, asShipObject());

        if (!transferObject(newCell, -1, true, true)) {
            error("could not add cell");
            continue;
        }

        newCell->setCellNumber(i+1);
        if (i != 0) {
            cellNameMap.put(layout->getCellProperty(i-1)->getName(), newCell);
        }
        cells.put(i, newCell);
    }

    ZoneServer* zoneServer = getZoneServer();

    for (int i = 0; i < templateObject->getChildObjectsSize(); ++i) {
        const ChildObject *child = templateObject->getChildObject(i);

        if (child == nullptr)
            continue;

        ManagedReference<SceneObject *> obj = zoneServer->createObject(child->getTemplateFile().hashCode(), getPersistenceLevel());

        if (obj == nullptr)
            continue;

        Locker objLocker(obj, asSceneObject());

        Vector3 childPosition = child->getPosition();
        childObjects.put(obj);
        obj->initializePosition(childPosition.getX(), childPosition.getZ(), childPosition.getY());
        obj->setDirection(child->getDirection());

        int totalCells = getTotalCellNumber();

        try {
            if (totalCells >= child->getCellId()) {
                ManagedReference<CellObject *> cellObject = getCell(child->getCellId());
                info("Inserting into " + String::valueOf(cellObject->getObjectID()), true);
                if (cellObject != nullptr) {
                    if (!cellObject->transferObject(obj, child->getContainmentType(), true)) {
                        obj->destroyObjectFromDatabase(true);
                        continue;
                    }
                    //cellObject->broadcastObject(obj, false);
                } else {
                    error("NULL CELL OBJECT");
                    obj->destroyObjectFromDatabase(true);
                    continue;
                }
            }
        } catch (Exception &e) {
            error("unreported exception caught in void SceneObjectImplementation::createChildObjects()!");
            e.printStackTrace();
        }
    }

    updateToDatabase();
}

void ShipObjectImplementation::sendContainerObjectsTo(SceneObject* player, bool forceLoad) {
    for (int i = 0; i < cells.size(); ++i) {
        CellObject* cell = cells.get(i);

        cell->sendTo(player, true);
        for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
            ManagedReference<SceneObject*> containerObject = cell->getContainerObject(j);

            if (containerObject != nullptr && ((!containerObject->isCreatureObject()))) {
                containerObject->sendTo(player, true, false);
                info("Sent: " + containerObject->getObjectTemplate()->getTemplateFileName() + " " + String::valueOf(containerObject->getObjectID()), true);
            }
        }
    }
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

ShipObject* ShipObject::asShipObject() {
    return this;
}

void ShipObjectImplementation::install(CreatureObject* owner, SceneObject* sceno, int slot, bool notifyClient) {
	ManagedReference<ShipComponent*> shipComponent = dynamic_cast<ShipComponent*>(sceno);
	if (shipComponent == nullptr)
		return;

	info("DataName: " + shipComponent->getComponentDataName() + " hash: " + String::hexvalueOf((int64)shipComponent->getComponentDataName().hashCode()), true);
    const ShipComponentData *component = ShipManager::instance()->getShipComponent(shipComponent->getComponentDataName());
    if (component == nullptr) {
        fatal("NULL ShipComponentData");
    }

    DeltaMessage *message = notifyClient ? new DeltaMessage(getObjectID(), 'SHIP', 6) : nullptr;
    UnicodeString string = UnicodeString(component->getName());
	info("Loading: " + component->getName(), true);
    components.put(slot, cast<ShipComponent*>(sceno));
    setComponentCRC(slot, component->getName().hashCode(), message);
    setComponentName(slot, string, message);
    if (message != nullptr) {
        message->close();
        owner->sendMessage(message);
    }

	shipComponent->install(owner, _this.getReferenceUnsafeStaticCast(), slot, notifyClient);
	shipComponent->destroyObjectFromWorld(true);

}

String ShipObjectImplementation::getParkingLocation() {
    if (parkingLocation == "") {
        ManagedReference<SceneObject*> creo = owner.get();
        if (creo != nullptr) {
            Zone* zone = creo->getZone();
            if (zone != nullptr)
                parkingLocation = zone->getZoneName();
        }
    }
    return parkingLocation;
}

void ShipObjectImplementation::uninstall(CreatureObject* owner, int slot, bool notifyClient) {
    DeltaMessage* message = new DeltaMessage(getObjectID(), 'SHIP', 6);
    message->startUpdate(15);
    shipComponents.set(slot, 0, message);
    components.remove(0);
    message->close();
    owner->sendMessage(message);
}


int ShipObjectImplementation::notifyObjectInsertedToChild(SceneObject* object, SceneObject* child, SceneObject* oldParent) {
    ManagedReference<Zone*> zone = getZone();

    Locker* _locker = nullptr;

    if (zone != nullptr)
        _locker = new Locker(zone);

    try {
        if (object->getCloseObjects() != nullptr)
            object->addInRangeObject(object, false);

        if (child->isCellObject()) {
            bool runInRange = true;

            if ((oldParent == nullptr || !oldParent->isCellObject()) || oldParent == child) {

                if (oldParent == nullptr || (oldParent != nullptr && dynamic_cast<Zone*>(oldParent) == nullptr && !oldParent->isCellObject())) {
                    //notifyObjectInsertedToZone(object);
                    runInRange = false;
                }

                if (!object->isPlayerCreature()) {
                    broadcastDestroy(object, true);
                    broadcastObject(object, false);
                }
            }

            if (runInRange) {
                ManagedReference<CellObject*> cell = cast<CellObject*>(child);

                if (cell != nullptr) {
                    for (int j = 0; j < cell->getContainerObjectsSize(); ++j) {
                        ManagedReference<SceneObject*> cobj = cell->getContainerObject(j);

                        if (cobj != object) {

                            if (cobj->getCloseObjects() != nullptr) {
                                if (!cobj->getCloseObjects()->contains(object)) {
                                    cobj->addInRangeObject(object, false);
                                    object->sendTo(cobj, true, false);
                                }
                            } else
                                cobj->notifyInsert(object);

                            if (object->getCloseObjects() != nullptr) {
                                if (!object->getCloseObjects()->contains(cobj.get())) {
                                    object->addInRangeObject(cobj.get(), false);
                                    cobj->sendTo(object, true, false);//sendTo because notifyInsert doesnt send objects with parent
                                } else {
                                    if (object->getClient() != nullptr && cobj->isCreatureObject()) {
                                        object->sendMessage(cobj->link(cell->getObjectID(), -1));
                                    }
                                }
                            } else {
                                object->notifyInsert(cobj.get());
                            }

                        }
                    }
                }
            }
        }

    } catch (Exception& e) {
        error(e.getMessage());
        e.printStackTrace();
    }

    if (zone != nullptr) {
        delete _locker;

        if (object->isTangibleObject()) {
            TangibleObject* tano = object->asTangibleObject();
            zone->updateActiveAreas(tano);
        }
    }
    //info("Added: " + object->getDisplayedName(), true);
    //TangibleObjectImplementation::notifyObjectInsertedToChild(object, child, oldParent);

    return 0;
}

int ShipObjectImplementation::notifyObjectRemovedFromChild(SceneObject* object, SceneObject* child) {
    TangibleObjectImplementation::notifyObjectRemovedFromChild(object, child);
    info("Removed: " + object->getDisplayedName(), true);
    /*SceneObject* parent = sceneObject->getParent();
    Zone* zone = sceneObject->getZone();

    if (!parent->isCellObject())
        return;

    if (building != parent->getParent()) {
        error("removing from wrong building object");
        return;
    }

    sceneObject->broadcastMessage(sceneObject->link((uint64)0, (uint32)0xFFFFFFFF), true, false);*/

    //parent->removeObject(sceneObject, false);


    //remove(object);

    //    	building->removeNotifiedSentObject(sceneObject);


    return 0;
}

void ShipObjectImplementation::damageArmor(float damage, DeltaMessage* delta) {
    // Assume damage > total armor
    float armor0 = getCurrentArmorMap()->get(Components::ARMOR0);
    float armor1 = getCurrentArmorMap()->get(Components::ARMOR1);
    float half = damage * 0.5f;
    armor0 -= damage;
    bool hasArmor0 = armor0 != 0;
    bool hasArmor1 = armor1 != 0;
    float remaining = 0;
    armor0 -= half;

    if (armor0 < 0) {
        remaining = -armor0;
        armor0 = 0;
    }

    armor1 -= remaining + half;

    if (hasArmor0) {
        setComponentArmor(Components::ARMOR0, armor0, delta);
    }

    if (hasArmor1) {
        setComponentArmor(Components::ARMOR1, armor1, delta);
    }
}

void ShipObjectImplementation::doRecovery(int mselapsed) {
    float dt = mselapsed/1000.0f;

    for (const auto& entry : components) {
        int slot = entry.getKey();
        ShipComponent* component = entry.getValue();
        switch (slot) {
            case Components::SHIELD0:
            case Components::SHIELD1:
                break;
            case Components::REACTOR:
            {
                break;
            }
            case Components::ENGINE:
                break;
            case Components::CAPACITOR:
            {
                float amount = getCapacitorRechargeRate() * dt;
                float cur = getCapacitorEnergy();
                setCapacitorEnergy(Math::min(cur+amount, getCapacitorMaxEnergy()), true);
                break;
            }
        }
    }
}
