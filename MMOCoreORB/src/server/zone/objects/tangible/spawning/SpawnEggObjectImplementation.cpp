/*
 * SpawnEggObjectImplementation.cpp
 *
 *	5/04/24
 *	Author: Hakry
 *
 */

#include "server/zone/objects/tangible/spawning/SpawnEggObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/Zone.h"

void SpawnEggObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player){
	if (player == nullptr || !player->isPlayerCreature()) {
		return;
	}

	auto zone = getZone();

	if (zone == nullptr) {
		return;
	}

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr || !ghost->isPrivileged()) {
		return;
	}

	StringBuffer msg;

	msg << "Spawner Active: "<< (isActive() ? "True" : "False") << endl;

	if (isActive()) {
		Time now;
		msg << "Active Time Remaining: " << (-1 * activeTime.miliDifference() / 1000 / 60) << " minutes remaining." << endl;
	}

	msg << "Spawner Inactive: " << (isInactive() ? "True" : "False") << endl;

	if (isInactive()) {
		Time now;
		msg << "Inactive Time Remaining: " << (-1 * inactiveTime.miliDifference() / 1000 / 60) << " minutes remaining." << endl;
	}

	msg
	<< "Spawner Name: " << spawnerName << endl
	<< "Current Spawn List: " << currentSpawnList << endl
	<< "Zone: " << zone->getZoneName() << endl
	<< "Location: " << getWorldPosition().toString() << endl;

	player->sendSystemMessage(msg.toString());
}

void SpawnEggObjectImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (player == nullptr || !player->isPlayerCreature()) {
		return;
	}

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr || !ghost->isPrivileged()) {
		return;
	}

	TangibleObjectImplementation::fillObjectMenuResponse(menuResponse, player);

	menuResponse->addRadialMenuItem(RadialOptions::SERVER_OBSERVE, 3, "Toggle Spawner Visibility");
}

int SpawnEggObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (player == nullptr || !player->isPlayerCreature()) {
		return 1;
	}

	auto ghost = player->getPlayerObject();

	if (ghost == nullptr || !ghost->isPrivileged()) {
		return 1;
	}

	auto thisSpawnEgg = _this.getReferenceUnsafeStaticCast();

	if (thisSpawnEgg == nullptr) {
		return 1;
	}

	switch(selectedID) {
		case (RadialOptions::SERVER_OBSERVE): {
			if (!isInvisible()) {
				setInvisible(true);
				player->broadcastDestroy(thisSpawnEgg, false);
			} else {
				setInvisible(false);
				player->broadcastObject(thisSpawnEgg, false);
			}

			return 0;
		}
		default:
			break;
	}

	return 1;
}

void SpawnEggObjectImplementation::setActive(uint64 miliTime) {
	Locker lock(_this.getReferenceUnsafeStaticCast());

	if (isActive()) {
		return;
	}

	activeTime.updateToCurrentTime();
	activeTime.addMiliTime(miliTime);
}

void SpawnEggObjectImplementation::setInactive(uint64 miliTime) {
	Locker lock(_this.getReferenceUnsafeStaticCast());

	inactiveTime.updateToCurrentTime();
	inactiveTime.addMiliTime(miliTime);
}

bool SpawnEggObjectImplementation::isActive() const {
	return activeTime.isFuture();
}

bool SpawnEggObjectImplementation::isInactive() const {
	return inactiveTime.isFuture();
}