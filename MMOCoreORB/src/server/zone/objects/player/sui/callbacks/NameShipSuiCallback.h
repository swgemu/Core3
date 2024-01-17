/*
 * NameShipSuiCallback.h
 *
 *  Created on: 1/26/2024
 *  Author: Hakry
 */

#ifndef NAMESHIPSUICALLBACK_H_
#define NAMESHIPSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/managers/name/NameManager.h"
#include "templates/tangible/ship/SharedShipObjectTemplate.h"

class NameShipSuiCallback : public SuiCallback {
public:
	NameShipSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* player, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		if (player == nullptr)
			return;

		bool cancelPressed = (eventIndex == 1);

		if (!sui->isInputBox() || cancelPressed || args->size() < 1)
			return;

		ManagedReference<SceneObject*> object = sui->getUsingObject().get();

		if (object == nullptr || !object->isShipControlDevice())
			return;

		auto shipDevice = object.castTo<ShipControlDevice*>();

		if (shipDevice == nullptr)
			return;

		auto ship = shipDevice->getControlledObject()->asShipObject();

		if (ship == nullptr) {
			return;
		}

		String shipName = args->get(0).toString();
		bool emptyName = true;

		if (!shipName.isEmpty()) {
			emptyName = false;

			ZoneProcessServer* zps = player->getZoneProcessServer();

			if (zps == nullptr)
				return;

			NameManager* nameManager = zps->getNameManager();

			if (nameManager == nullptr)
				return;

			// Player Entered a name, validate with nane manager
			if (nameManager->validateShipName(shipName) != NameManagerResult::ACCEPTED) {
				player->sendSystemMessage("@sui:rename_ship_reserved");
				return;
			}
		}

		Locker shipLock(ship, player);

		ship->setShipName(shipName, true);

		shipLock.release();

		if (emptyName) {
			// Entered name was emtpy, control device needs ships displayed name
			shipName = ship->getDisplayedName();
		}

		Locker deviceLock(shipDevice, player);

		shipDevice->setCustomObjectName(shipName, true);
	}
};

#endif /* NAMESHIPSUICALLBACK_H_ */
