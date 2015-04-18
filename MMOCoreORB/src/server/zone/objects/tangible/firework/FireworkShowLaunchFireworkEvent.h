/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FIREWORKSHOWLAUNCHFIREWORKEVENT_H_
#define FIREWORKSHOWLAUNCHFIREWORKEVENT_H_


#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/firework/FireworkObject.h"
#include "server/zone/objects/tangible/firework/components/FireworkShowDataComponent.h"
#include "server/zone/objects/staticobject/StaticObject.h"
#include "FireworkRemoveEvent.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"

class FireworkShowLaunchFireworkEvent : public Task {
	ManagedReference<FireworkShowDataComponent*> fireworkShowData;
	ManagedReference<FireworkObject*> fireworkShow;
	ManagedWeakReference<CreatureObject*> player;
	ManagedReference<StaticObject*> worldFireworkShow;
	int removeDelay;

public:
	FireworkShowLaunchFireworkEvent(CreatureObject* player, FireworkObject* fireworkShow, FireworkShowDataComponent* fireworkShowData, StaticObject* worldFireworkShow) : Task(1000) {
		this->fireworkShowData = fireworkShowData;
		this->player = player;
		this->fireworkShow = fireworkShow;
		this->worldFireworkShow = worldFireworkShow;
		this->removeDelay = 30000; // Launched firework stays in world for 30 secs
	}

	void run() {
		ManagedReference<FireworkShowDataComponent*> fireworkShowData = this->fireworkShowData.get();
		ManagedReference<CreatureObject*> player = this->player.get();
		ManagedReference<StaticObject*> worldFireworkShow = this->worldFireworkShow.get();
		ManagedReference<FireworkObject*> fireworkShow = this->fireworkShow.get();

		if (player == NULL || worldFireworkShow == NULL || fireworkShowData == NULL || fireworkShow == NULL)
			return;

		if (fireworkShowData->getTotalFireworkCount() == 0)
			return;

		try {
			Locker locker(player);

			ManagedReference<FireworkObject*> firework = fireworkShowData->getFirework(0);

			if (firework == NULL)
				return;

			ManagedReference<StaticObject*> fireworkObject = (player->getZoneServer()->createObject(firework->getFireworkObjectPath().hashCode(), 0)).castTo<StaticObject*>();

			if (fireworkObject == NULL)
				return;


			int x = worldFireworkShow->getPositionX();
			int y = worldFireworkShow->getPositionY();
			int z = worldFireworkShow->getZone()->getHeight(x, y);
			fireworkObject->initializePosition(x, z, y);
			player->getZone()->transferObject(fireworkObject, -1, true);

			fireworkShowData->removeFirework(0);

			firework->destroyObjectFromDatabase(false);

			Reference<FireworkRemoveEvent*> fireworkRemoveEvent = new FireworkRemoveEvent(player, fireworkObject);
			fireworkRemoveEvent->schedule(removeDelay);

			if (fireworkShowData->getTotalFireworkCount() > 0) {
				int launchDelay = fireworkShowData->getFireworkDelay(0);
				reschedule(launchDelay);
			} else {
				Reference<FireworkRemoveEvent*> fireworkRemoveEvent = new FireworkRemoveEvent(player, worldFireworkShow);
				fireworkRemoveEvent->schedule(2000);
				fireworkShow->destroyObjectFromDatabase(false);
			}

		} catch (Exception& e) {
			player->error("unreported exception on FireworkShowLaunchFireworkEvent::run()");
		}
	}
};


#endif /* FIREWORKSHOWLAUNCHFIREWORKEVENT_H_ */
