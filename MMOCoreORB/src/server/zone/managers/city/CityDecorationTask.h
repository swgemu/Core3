/*
 * CityDecorationTask.h
 *
 *  Created on: Aug 26, 2013
 *      Author: root
 */

#ifndef CITYDECORATIONTASK_H_
#define CITYDECORATIONTASK_H_

#include "engine/engine.h"
#include "server/chat/ChatManager.h"
#include "server/zone/objects/region/CityRegion.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/objects/scene/SceneObject.h"

class CityDecorationTask : public Task {
	ManagedReference<CreatureObject*> mayor;
	ManagedReference<TangibleObject*> obj;
	byte option;

public:
	enum {
		PLACE = 0,
		REMOVE = 1
	};

	CityDecorationTask( CreatureObject* creature, TangibleObject* object, byte function) {
		mayor = creature;
		obj = object;
		option = function;
	}

	void run() {

		switch (option) {
			case 0:
				placeDecoration();
				break;

			case 1:
				removeDecoration();
				break;
		}
	}

	void placeDecoration() {
		Locker _lock(mayor);

		ManagedReference<CityRegion*> city = mayor->getCityRegion();

		if(city == NULL) {
			mayor->sendSystemMessage("@player_structure:cant_place_civic"); //This structure must be placed within the borders of the city in which you are mayor.
			return;
		}

		CityManager* cityManager = mayor->getZoneServer()->getCityManager();

		if(!city->isMayor(mayor->getObjectID())) {
			mayor->sendSystemMessage("@player_structure:cant_place_civic"); //This structure must be placed within the borders of the city in which you are mayor.
			return;
		}

		PlayerObject* mayorGhost = mayor->getPlayerObject().get();
		if (mayorGhost == NULL) {
			return;
		}

		if ((obj->isCityStreetLamp() && !mayorGhost->hasAbility("place_streetlamp")) || (obj->isCityStatue() && !mayorGhost->hasAbility("place_statue")) || (obj->isCityFountain() && !mayorGhost->hasAbility("place_fountain"))) {
			mayor->sendSystemMessage("@city/city:no_skill_deco"); // You lack the skill to place this decoration in your city.
			return;
		}

		if(!cityManager->canSupportMoreDecorations(city)) {
			StringIdChatParameter param("city/city", "no_more_decos"); //"Your city can't support any more decorations at its current rank!");
			mayor->sendSystemMessage(param);
			return;
		}

		Zone* zone = mayor->getZone();

		if (zone == NULL || obj->getObjectTemplate() == NULL)
			return;

		Reference<SceneObject*> objTooClose = zone->getPlanetManager()->findObjectTooCloseToDecoration(mayor->getPositionX(), mayor->getPositionY(), obj->getObjectTemplate()->getNoBuildRadius());

		if (objTooClose != NULL && !obj->isCityStreetLamp()) {
			StringIdChatParameter msg;
			msg.setStringId("@city/city:deco_too_close"); //"You can't place a decoration here, it would be too close to structure %TO.");

			msg.setTO(objTooClose);
			//msg.setTO(objTooClose->getObjectNameStringIdFile(), obj->getObjectNameStringIdName());
			mayor->sendSystemMessage(msg);
			return;
		}

		if(city->getCityTreasury() < 1000) {
			StringIdChatParameter msg;
			msg.setStringId("@city/city:action_no_money");
			msg.setDI(1000);
			mayor->sendSystemMessage(msg); //"The city treasury must have %DI credits in order to perform that action.");
			return;
		}

		Locker tlock(obj, mayor);

		if(!obj->isASubChildOf(mayor)) {
			mayor->sendSystemMessage("@space/quest:not_in_inv"); // The object must be in your inventory
			return;
		}

		obj->initializePosition(mayor->getWorldPositionX(), mayor->getWorldPositionZ(),mayor->getWorldPositionY());
		obj->rotate(mayor->getDirectionAngle() - obj->getDirectionAngle());

		if(zone->transferObject(obj, -1, true)) {
			tlock.release();
			Locker clock(city, mayor);
			city->addDecoration(obj);
			city->subtractFromCityTreasury(1000);
		}

	}

	void removeDecoration() {
		Locker _lock(mayor);

		ManagedReference<CityRegion*> city = mayor->getCityRegion();

		if(city == NULL)
			return;

		if(!city->isMayor(mayor->getObjectID())) {
			return;
		}

		Zone* zone = mayor->getZone();

		if (zone == NULL)
			return;

		ManagedReference<SceneObject*> inv = mayor->getSlottedObject("inventory");

		if(inv == NULL)
			return;

		if(inv->isContainerFull()) {
			//mayor->sendSystemMessage("@error_message:inv_full"); // You inventory is full
			mayor->sendSystemMessage("@event_perk:promoter_full_inv"); //"Your inventory is full. Please make some room and try again.");
			return;
		} else {
			Locker tlock(obj, mayor);

			if(	inv->transferObject(obj, -1, true)) {
				inv->broadcastObject(obj, true);
				tlock.release();
				Locker clock(city, mayor);
				city->removeDecoration(obj);

				mayor->sendSystemMessage("@city/city:mt_removed"); // The object has been removed from the city.
			}
		}
	}

};

#endif /* CITYDECORATIONTASK_H_ */
