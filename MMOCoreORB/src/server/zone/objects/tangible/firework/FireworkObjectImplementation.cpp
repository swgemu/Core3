/*
 * FireworkObjectImplementation.cpp
 *
 *  Created on: May 8, 2010
 *      Author: swgemu
 */

#include "FireworkObject.h"
#include "FireworkRemoveEvent.h"
#include "FireworkLaunchEvent.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/staticobject/StaticObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "system/util/VectorMap.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/Zone.h"


void FireworkObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	if (!templateData->isFireworkObjectTemplate()) {
		error("critical error");
		return;
	}

	FireworkObjectTemplate* templ = cast<FireworkObjectTemplate*>(templateData);

	if (templ == NULL)
		return;

	fireworkObject = templ->getFireworkObject();

	if(templ->isShow()) {
		isShow = true;
	}
}

void FireworkObjectImplementation::updateCraftingValues(CraftingValues* values,
		bool firstUpdate) {

	if (values->hasProperty("charges")) {
		if(isShow) {
			capacity = values->getCurrentValue("charges");
		} else {
			setUseCount(values->getCurrentValue("charges"));
		}
	}
}

int FireworkObjectImplementation::getDisplayedUseCount() {

	if(getContainerObjectsSize() < 1)
		return TangibleObjectImplementation::getDisplayedUseCount();

	ManagedReference<SceneObject*> fireworkHopper = getContainerObject(0);

	if(fireworkHopper == NULL) {
		return 0;
	}

	return fireworkHopper->getContainerObjectsSize();
}

void FireworkObjectImplementation::launch(CreatureObject* player, int removeDelay) {
	if (player == NULL)
		return;

	if(getDelay() == 0) {
		completeLaunch(player, removeDelay);
		return;
	}

	Reference<FireworkLaunchEvent*> launchEvent = new FireworkLaunchEvent(player, _this.get(), removeDelay);
	launchEvent->schedule(delay * 1000);
}

void FireworkObjectImplementation::completeLaunch(CreatureObject* player, int removeDelay) {

	ManagedReference<StaticObject*> launcherObject = cast<StaticObject*>(server->getZoneServer()->createObject(fireworkObject.hashCode(), 0));

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
	int z = player->getZone()->getHeight(x, y);

	launcherObject->initializePosition(x, z, y);
	//launcherObject->insertToZone(player->getZone());
	player->getZone()->transferObject(launcherObject, -1, true);

	if (getUseCount() > 1) {
		setUseCount(getUseCount() - 1, true);
	} else {

		destroyObjectFromWorld(true);
		/*if (parent != NULL)
			getParent()->removeObject(_this.get(), true);*/

		if (isPersistent())
			destroyObjectFromDatabase(true);
	}

	Reference<FireworkRemoveEvent*> fireworkRemoveEvent = new FireworkRemoveEvent(player, launcherObject);
	fireworkRemoveEvent->schedule(removeDelay * 1000);

}
