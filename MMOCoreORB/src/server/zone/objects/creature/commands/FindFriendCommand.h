/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FINDFRIENDCOMMAND_H_
#define FINDFRIENDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/ChatManager.h"
#include "server/zone/Zone.h"

#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/player/PlayerObject.h"

class FindFriendCommand : public QueueCommand {
public:

	FindFriendCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		auto player = cast<CreatureObject*>(creature);

		auto ghost = player->getPlayerObject();

		String name = arguments.toString().toLowerCase();

		auto chatManager = server->getChatManager();

		auto targetPlayer = chatManager->getPlayer(name);

		if (targetPlayer == nullptr) {
			StringIdChatParameter message("@ui_cmnty:friend_location_failed"); // Unable to locate %TU
			message.setTU(name);

			player->sendSystemMessage(message);
			return GENERALERROR;
		}

		auto targetGhost = targetPlayer->getPlayerObject();
		String myFirstName = player->getFirstName().toLowerCase();

		if (!targetGhost->hasFriend(myFirstName)) {
			StringIdChatParameter message("@ui_cmnty:friend_location_failed"); // Unable to locate %TU
			message.setTU(name);

			player->sendSystemMessage(message);
			return GENERALERROR;
		}

		if (targetGhost->isIgnoring(myFirstName)) {
			StringIdChatParameter message("@ui_cmnty:friend_location_failed"); // Unable to locate %TU
			message.setTU(name);

			player->sendSystemMessage(message);
			return GENERALERROR;
		}

		auto zone = targetPlayer->getZone();

		if (zone == nullptr) {
			StringIdChatParameter message("@ui_cmnty:friend_location_failed"); // Unable to locate %TU
			message.setTU(name);

			player->sendSystemMessage(message);
			return GENERALERROR;
		}

		String planet = zone->getZoneName();

		float x, z = 0, y;

		auto parent = targetPlayer->getParent().get();

		if (parent != nullptr && parent->isCellObject()) {
			ManagedReference<SceneObject*> building = parent->getParent().get();

			x = building->getPositionX();
			y = building->getPositionY();
		} else {
			x = targetPlayer->getPositionX();
			y = targetPlayer->getPositionY();
		}

		auto obj = (server->getZoneServer()->createObject(0xc456e788, 1)).castTo<WaypointObject*>();

		Locker locker(obj);

		obj->setPlanetCRC(planet.hashCode());
		obj->setPosition(x, z, y);
		obj->setCustomObjectName(name, false);
		obj->setSpecialTypeID(WaypointObject::SPECIALTYPE_FINDFRIEND);
		obj->setActive(true);

		ghost->addWaypoint(obj, true, true);

		StringIdChatParameter message("@ui_cmnty:friend_location"); // The friend waypoint has been updated to the location of %TU.
		message.setTU(name);

		player->sendSystemMessage(message);

		return SUCCESS;
	}

};

#endif //FINDFRIENDCOMMAND_H_
