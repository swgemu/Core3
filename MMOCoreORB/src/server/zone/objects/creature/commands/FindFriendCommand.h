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

#ifndef FINDFRIENDCOMMAND_H_
#define FINDFRIENDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/ChatManager.h"
#include "server/zone/Zone.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/waypoint/WaypointObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/cell/CellObject.h"

class FindFriendCommand : public QueueCommand {
public:

	FindFriendCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* player = cast<CreatureObject*>(creature);

		PlayerObject* ghost = player->getPlayerObject();

		String name = arguments.toString().toLowerCase();

		ChatManager* chatManager = server->getChatManager();

		ManagedReference<CreatureObject*> targetPlayer = chatManager->getPlayer(name);

		if (targetPlayer == NULL) {
			ManagedReference<StringIdChatParameter*> message = new StringIdChatParameter("@ui_cmnty:friend_location_failed"); // Unable to locate %TU
			message->setTU(name);

			player->sendSystemMessage(*message);
			return GENERALERROR;
		}

		PlayerObject* targetGhost = targetPlayer->getPlayerObject();
		String myFirstName = player->getFirstName().toLowerCase();

		if (!targetGhost->hasFriend(myFirstName)) {
			ManagedReference<StringIdChatParameter*> message = new StringIdChatParameter("@ui_cmnty:friend_location_failed"); // Unable to locate %TU
			message->setTU(name);

			player->sendSystemMessage(*message);
			return GENERALERROR;
		}

		Zone* zone = targetPlayer->getZone();

		if (zone == NULL) {
			ManagedReference<StringIdChatParameter*> message = new StringIdChatParameter("@ui_cmnty:friend_location_failed"); // Unable to locate %TU
			message->setTU(name);

			player->sendSystemMessage(*message);
			return GENERALERROR;
		}

		String planet = zone->getZoneName();

		float x, z = 0, y;

		ManagedReference<SceneObject*> parent = targetPlayer->getParent();

		if (parent != NULL && parent->isCellObject()) {
			ManagedReference<SceneObject*> building = parent->getParent();

			x = building->getPositionX();
			y = building->getPositionY();
		} else {
			x = targetPlayer->getPositionX();
			y = targetPlayer->getPositionY();
		}

		ManagedReference<WaypointObject*> obj = ( server->getZoneServer()->createObject(0xc456e788, 1)).castTo<WaypointObject*>();
		obj->setPlanetCRC(planet.hashCode());
		obj->setPosition(x, z, y);
		obj->setCustomObjectName(name, false);
		obj->setSpecialTypeID(WaypointObject::SPECIALTYPE_FINDFRIEND);
		obj->setActive(true);

		ghost->addWaypoint(obj, true, true);

		ManagedReference<StringIdChatParameter*> message = new StringIdChatParameter("@ui_cmnty:friend_location"); // The friend waypoint has been updated to the location of %TU.
		message->setTU(name);

		player->sendSystemMessage(*message);

		return SUCCESS;
	}

};

#endif //FINDFRIENDCOMMAND_H_
