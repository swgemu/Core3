/*
 * FireworkObjectImplementation.cpp
 *
 *  Created on: May 8, 2010
 *      Author: swgemu
 */

#include "FireworkObject.h"
#include "FireworkEvent.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/staticobject/StaticObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "system/util/VectorMap.h"

int FireworkObjectImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (player == NULL)
		return 0;

	if (selectedID == 20) {
		launch(player);
	}

	return 0;
}


void FireworkObjectImplementation::launch(CreatureObject* player) {
	if (player == NULL)
		return;

	ManagedReference<StaticObject*> launcherObject = (StaticObject*)server->getZoneServer()->createObject(fireworkObject.hashCode(), 0);

	if (launcherObject == NULL)
		return;

	player->setPosture(CreaturePosture::CROUCHED);
	player->doAnimation("manipulate_low");

	float angle = player->getDirectionAngle();

	if (angle > 360)
		angle = angle - 360;

	float distance = 2.0;

	angle = 2 * M_PI * angle / 360;

	int x = player->getPositionX() + sin(angle) * (distance);
	int y = player->getPositionY() + cos(angle) * (distance);
	int z = player->getPositionZ();

	launcherObject->initializePosition(x, z, y);
	launcherObject->insertToZone(player->getZone());

	if (getUseCount() > 1) {
		setUseCount(getUseCount() - 1, true);
	} else {

		if (parent != NULL)
			parent->removeObject(_this, true);

		if (isPersistent())
			destroyObjectFromDatabase(true);
	}

	Reference<FireworkEvent*> fireworkEvent = new FireworkEvent(player, launcherObject);
	fireworkEvent->schedule(30 * 1000);
}
