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

#ifndef CITYBANCOMMAND_H_
#define CITYBANCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "../../building/city/CityHallObject.h"
#include "server/zone/objects/area/ActiveArea.h"
#include "server/zone/objects/region/Region.h"

class CitybanCommand : public QueueCommand {
public:

	CitybanCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		ManagedReference<PlayerCreature*> player = (PlayerCreature*) creature;

		ManagedReference<SceneObject*> targetObject = player->getZoneServer()->getObject(target);

		if (targetObject == NULL || !targetObject->isPlayerCreature())
			return INVALIDTARGET;

		PlayerCreature* targetPlayer = (PlayerCreature*) targetObject.get();

		ManagedReference<CityRegion*> cityRegion = player->getCityRegion();

		if (cityRegion == NULL)
			return GENERALERROR;

		/* TODO: Reimplement
		ManagedReference<CityHallObject*> cityHall = region->getCityHall();

		if (cityHall == NULL)
			return GENERALERROR;

		Locker _locker(cityHall);

		//Can't ban someone who's already been banned
		if (cityHall->isBanned(target))
			return GENERALERROR;

		if (!cityHall->isMayor(player->getObjectID()) && !cityHall->isMilitiaMember(player->getObjectID())) {
			player->sendSystemMessage("@city/city:not_militia"); //You must be a member of the city militia to use this command.
			return GENERALERROR;
		}

		if (targetPlayer->getPlayerObject()->isPrivileged()) {
			player->sendSystemMessage("@city/city:not_csr_ban"); //You cannot ban a Customer Service Representative from the city!

			StringIdChatParameter params;
			params.setStringId("@city/city:csr_ban_attempt_msg");
			params.setTT(player);
			params.setTO(cityHall->getCityName());
			targetPlayer->sendSystemMessage(params); //%TT tried to /cityBan you from %TO!
			return GENERALERROR;
		}

		if (cityHall->isCitizen(target)) {
			player->sendSystemMessage("@city/city:not_citizen_ban"); //You can't city ban a citizen of the city!
			return GENERALERROR;
		}

		cityHall->addBannedPlayer(target);
		cityHall->updateToDatabaseWithoutChildren();

		targetPlayer->sendSystemMessage("@city/city:city_banned"); //You have been banned from the this city.  You may no longer use any city services.

		StringIdChatParameter params;
		params.setStringId("@city/city:city_ban_done");
		params.setTT(targetPlayer);
		player->sendSystemMessage(params); //%TT has been banned from the city and is no longer able to access city services.

		*/

		return SUCCESS;
	}

};

#endif //CITYBANCOMMAND_H_
