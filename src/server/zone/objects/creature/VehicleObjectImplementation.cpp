/*
 * VehicleObjectImplementation.cpp
 *
 *  Created on: 10/04/2010
 *      Author: victor
 */

#include "VehicleObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/PlayerCreature.h"
#include "server/zone/objects/intangible/VehicleControlDevice.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/Zone.h"


void VehicleObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, PlayerCreature* player) {
	if (linkedCreature != player)
		return;

	menuResponse->addRadialMenuItem(205, 1, "@pet/pet_menu:menu_enter_exit");
	menuResponse->addRadialMenuItem(61, 3, "");

	if (checkInRangeGarage() && !isDestroyed())
		menuResponse->addRadialMenuItem(62, 3, "Repair");
}

void VehicleObjectImplementation::insertToZone(Zone* zone) {
	SceneObjectImplementation::insertToZone(zone);

	inflictDamage(_this, 0, System::random(50), true);
}

bool VehicleObjectImplementation::checkInRangeGarage() {
	if (zone == NULL)
		return false;

	Locker _locker(zone);

	for (int i = 0; i < inRangeObjectCount(); ++i) {
		SceneObjectImplementation* scno = (SceneObjectImplementation*) getInRangeObject(i);

		if (scno == this)
			continue;

		if (scno->isGarage() && scno->isInRange(_this, 15))
			return true;
	}

	return false;
}


int VehicleObjectImplementation::handleObjectMenuSelect(PlayerCreature* player, byte selectedID) {
	if (selectedID == 61 && linkedCreature == player) {
		unlock();

		controlDevice->storeObject(player);

		wlock(player);
	} else if (selectedID == 62) {
		if (!isDestroyed())
			healDamage(player, 0, conditionDamage, true);
	}

	return 0;
}

int VehicleObjectImplementation::inflictDamage(TangibleObject* attacker, int damageType, int damage, bool destroy, bool notifyClient) {
	return TangibleObjectImplementation::inflictDamage(attacker, damageType, damage, destroy, notifyClient);
}

int VehicleObjectImplementation::healDamage(TangibleObject* healer, int damageType, int damage, bool notifyClient) {
	return TangibleObjectImplementation::healDamage(healer, damageType, damage, notifyClient);
}

int VehicleObjectImplementation::notifyObjectDestructionObservers(TangibleObject* attacker, int condition) {
	unlock();

	try {
		Locker clocker(linkedCreature, attacker);

		linkedCreature->executeObjectControllerAction(String("dismount").hashCode());

	} catch (...) {
	}

	wlock(attacker);

	return CreatureObjectImplementation::notifyObjectDestructionObservers(attacker, condition);
}

