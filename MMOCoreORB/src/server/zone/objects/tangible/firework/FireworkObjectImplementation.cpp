/*
 * FireworkObjectImplementation.cpp
 *
 *  Created on: May 8, 2010
 *      Author: swgemu
 */

#include "server/zone/objects/tangible/firework/FireworkObject.h"
#include "FireworkRemoveEvent.h"
#include "FireworkLaunchEvent.h"
#include "FireworkShowLaunchFireworkEvent.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/staticobject/StaticObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/tangible/firework/components/FireworkShowDataComponent.h"
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

	if(templ->isFireworkShow()) {
		isShow = true;
	}
}

void FireworkObjectImplementation::destroyObjectFromDatabase(bool destroyContainedObjects) {
	ManagedReference<FireworkObject*> firework = _this.get();

	if (firework != NULL && firework->isFireworkObject()) {

		DataObjectComponent* data = firework->getDataObjectComponent()->get();

		if(data != NULL && data->isFireworkShowData()) {
			FireworkShowDataComponent* fireworkShowData = cast<FireworkShowDataComponent*>(data);
			if (fireworkShowData->getTotalFireworkCount() > 0) {
				for (int i=0; i< fireworkShowData->getTotalFireworkCount(); i++) {
					ManagedReference<FireworkObject*> firework = fireworkShowData->getFirework(0);
					fireworkShowData->removeFirework(0);
					if (firework != NULL)
						firework->destroyObjectFromDatabase(false);
				}
			}

		}

	}

	TangibleObjectImplementation::destroyObjectFromDatabase(destroyContainedObjects);
}

void FireworkObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	ManagedReference<FireworkObject*> firework = _this.get();

	if (firework == NULL)
		return;

	DataObjectComponent* data = firework->getDataObjectComponent()->get();

	if (data == NULL || !data->isFireworkShowData()) {
		String effect = "@firework_n:" + fireworkObject.subString(fireworkObject.lastIndexOf("/") + 1, fireworkObject.lastIndexOf("."));
		alm->insertAttribute("@obj_attr_n:pattern", effect);
	} else {
		FireworkShowDataComponent* fireworkShowData = cast<FireworkShowDataComponent*>(data);

		if (fireworkShowData == NULL)
			return;

		alm->insertAttribute("examine_hoppersize", firework->getCapacity());

		int totalFireworks = fireworkShowData->getTotalFireworkCount();
		alm->insertAttribute("blank_entry", "");
		alm->insertAttribute("length", "\\#pcontrast2 " + String::valueOf(totalFireworks) + " Fireworks");

		for (int i = 0; i < totalFireworks; i++) {
			ManagedReference<FireworkObject*> firework = fireworkShowData->getFirework(i);
			if (firework == NULL)
				continue;
			String fireworkObj = firework->getFireworkObjectPath();
			String effect = "@firework_n:" + fireworkObj.subString(fireworkObj.lastIndexOf("/") + 1, fireworkObj.lastIndexOf("."));
			alm->insertAttribute("pattern", effect);
		}

	}

}

void FireworkObjectImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {

	ManagedReference<FireworkObject*> firework = _this.get();

	if (firework == NULL)
		return;

	DataObjectComponent* data = firework->getDataObjectComponent()->get();

	if (data != NULL && data->isFireworkShowData()) {
		FireworkShowDataComponent* fireworkShowData = cast<FireworkShowDataComponent*>(data);

		if (fireworkShowData == NULL)
			return;

		capacity = values->getCurrentValue("charges");

	} else {
		setUseCount(values->getCurrentValue("charges"));
	}
}

int FireworkObjectImplementation::getDisplayedUseCount() {

	ManagedReference<FireworkObject*> firework = _this.get();

	if (firework == NULL)
		return 0;

	DataObjectComponent* data = firework->getDataObjectComponent()->get();

	if (data != NULL && data->isFireworkShowData()) {
		FireworkShowDataComponent* fireworkShowData = cast<FireworkShowDataComponent*>(data);

		if (fireworkShowData == NULL)
			return 0;

		return fireworkShowData->getTotalFireworkCount();
	}

	return TangibleObjectImplementation::getDisplayedUseCount();
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
	ManagedReference<StaticObject*> launcherObject = (server->getZoneServer()->createObject(fireworkObject.hashCode(), 0)).castTo<StaticObject*>();

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
	player->getZone()->transferObject(launcherObject, -1, true);

	if (getUseCount() > 1) {
		setUseCount(getUseCount() - 1, true);
	} else {
		destroyObjectFromWorld(true);

		if (isPersistent())
			destroyObjectFromDatabase(true);
	}

	Reference<FireworkRemoveEvent*> fireworkRemoveEvent = new FireworkRemoveEvent(player, launcherObject);
	fireworkRemoveEvent->schedule(removeDelay * 1000);

}

void FireworkObjectImplementation::beginShowLaunch(CreatureObject* player) {
	if (player == NULL || player->getParent() != NULL)
		return;

	ManagedReference<FireworkObject*> fireworkShow = _this.get();

	if (fireworkShow == NULL)
		return;

	DataObjectComponent* data = fireworkShow->getDataObjectComponent()->get();

	if(data == NULL || !data->isFireworkShowData())
		return;

	FireworkShowDataComponent* fireworkShowData = cast<FireworkShowDataComponent*>(data);

	if (fireworkShowData->getTotalFireworkCount() == 0)
		return;

	ManagedReference<StaticObject*> showLauncherObject = (server->getZoneServer()->createObject(fireworkObject.hashCode(), 0)).castTo<StaticObject*>();

	if (showLauncherObject == NULL)
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

	showLauncherObject->initializePosition(x, z, y);
	player->getZone()->transferObject(showLauncherObject, -1, true);

	fireworkShow->destroyObjectFromWorld(true);

	int launchDelay = fireworkShowData->getFireworkDelay(0);
	Reference<FireworkShowLaunchFireworkEvent*> fireworkShowLaunchFireworkEvent = new FireworkShowLaunchFireworkEvent(player, fireworkShow, fireworkShowData, showLauncherObject);
	fireworkShowLaunchFireworkEvent->schedule(launchDelay);

}

