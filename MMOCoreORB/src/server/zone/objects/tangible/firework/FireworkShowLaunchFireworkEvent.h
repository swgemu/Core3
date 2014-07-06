/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

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
