/*
 * NewbieTutorialRequest.h
 *
 *  Created on: Nov 20, 2008
 *      Author: swgemu
 */

#ifndef NEWBIETUTORIALREQUEST_H_
#define NEWBIETUTORIALREQUEST_H_

#include "server/zone/packets/MessageCallback.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/building/TutorialBuildingObject.h"
/* Valid action strings found:
 * openCharacterSheet
 * closeCharacterSheet
 * openInventory
 * closeInventory
 * openStatMigration
 * closeStatMigration
 * openHolocron
 * closeHolocron
 * zoomCamera
 * overlayMap
 * changeLookAtTarget
 * changeMouseMode
 * equipToolbar
 */
class NewbieTutorialRequest : public BaseMessage {
public:
   /**
    * Sets a trigger on certain actions.
    *
    * The client can have multiple triggers set at once.
    *
    * Once a trigger is activated, a NewbieTutorialRequest
    * packet is sent echoing the request and the trigger is reset.
    *
    * NOTE: there is a bug in the client which causes the
    *       closeInventory trigger to never reset
    *
    * See list above for valid action strings
    *
    * @param action action to be monitored
    */
   NewbieTutorialRequest(const String& action) : BaseMessage() {
		insertShort(0x02);
		insertInt(0x90DD61AF);  // CRC

		insertAscii(action); //try openContainer openStatMigration etc.
   }

};

/**
 * Sends clientReady on zone.
 * Echos string sent by NewbieTutorialRequest, when action is triggered.
 */
class NewbieTutorialResponseCallback : public MessageCallback {
	String response;
public:
	NewbieTutorialResponseCallback(ZoneClientSession* client, ZoneProcessServer* server) :
		MessageCallback(client, server) {

	}

	void parse(Message* message) {
		message->parseAscii(response);
	}

	void run() {
		if (client == NULL)
			return;

		ManagedReference<CreatureObject*> player = client->getPlayer();

		if (player == NULL)
			return;

		Locker locker(player);

		//player->info("received response: " + response, true);

		if (response == "zoomCamera") {
			player->notifyObservers(ObserverEventType::NEWBIETUTORIALZOOMCAMERA, NULL, 0);
		} else if (response == "chatbox") {
			player->notifyObservers(ObserverEventType::CHAT, NULL, 0);
		} else if (response == "closeHolocron") {
			player->notifyObservers(ObserverEventType::NEWBIETUTORIALHOLOCRON, NULL, 0);
		} else if (response == "openInventory") {
			player->notifyObservers(ObserverEventType::NEWBIEOPENINVENTORY);
		} else if (response == "closeInventory") {
			player->notifyObservers(ObserverEventType::NEWBIECLOSEINVENTORY);
		} else if (response == "clientReady") {
			Zone* zone = player->getZone();

			if (zone == NULL || zone->getZoneName() != "tutorial")
				return;

			ManagedReference<TutorialBuildingObject*> bldg = player->getParentRecursively(SceneObjectType::TUTORIALBUILDING).castTo<TutorialBuildingObject*>();

			if (bldg != NULL && bldg->getTutorialOwnerID() == player->getObjectID()) {
				DirectorManager::instance()->startScreenPlay(player, "TutorialScreenPlay");
			}
		}
	}

};

#endif /* NEWBIETUTORIALREQUEST_H_ */
