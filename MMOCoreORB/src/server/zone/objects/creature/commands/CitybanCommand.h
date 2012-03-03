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

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ZoneServer* zserv = creature->getZoneServer();

		ManagedReference<SceneObject*> targetObject = zserv->getObject(target);

		if (targetObject == NULL || !targetObject->isCreatureObject()) {
			try {
				String targetFirstName;
				UnicodeTokenizer tokenizer(arguments);
				tokenizer.getStringToken(targetFirstName);

				targetObject = zserv->getPlayerManager()->getPlayer(targetFirstName);
			} catch (Exception& e) {
				return INVALIDPARAMETERS;
			}
		}

		if (targetObject == NULL || !targetObject->isCreatureObject()) {
			return INVALIDTARGET;
		}

		CreatureObject* targetCreature = cast<CreatureObject*>(targetObject.get());

		ManagedReference<CityRegion*> city = creature->getCityRegion();

		if (city == NULL) {
			creature->sendSystemMessage("@city/city:not_in_city"); //You must be in a city to use this command.
			return GENERALERROR;
		}

		Locker lock(city, creature);

		if (city->isBanned(targetCreature->getObjectID()))
			return INVALIDTARGET; //They are already banned.

		if (!city->isMilitiaMember(creature->getObjectID())) {
			creature->sendSystemMessage("@city/city:not_militia"); //You must be a member of the city militia to use this command.
			return GENERALERROR;
		}

		ManagedReference<PlayerObject*> ghost = targetCreature->getPlayerObject();

		if (ghost != NULL && ghost->isPrivileged()) {
			//Can't ban a CSR
			creature->sendSystemMessage("@city/city:not_csr_ban"); //You cannot ban a Customer Service Representative from the city!

			StringIdChatParameter params("city/city", "csr_ban_attempt_msg");
			params.setTT(creature->getDisplayedName());
			params.setTO(city->getRegionName());

			targetCreature->sendSystemMessage(params); //%TT tried to /cityBan you from %TO!
			return GENERALERROR;
		}

		if (city->isCitizen(targetCreature->getObjectID())) {
			creature->sendSystemMessage("@city/city:not_citizen_ban"); //You can't city ban a citizen of the city!
			return GENERALERROR;
		}

		city->addBannedPlayer(targetCreature->getObjectID());

		targetCreature->sendSystemMessage("@city/city:city_banned"); //You have been banned from the this city.  You may no longer use any city services.

		StringIdChatParameter params("city/city", "city_ban_done");
		params.setTT(targetCreature->getDisplayedName());
		creature->sendSystemMessage(params); //%TT has been banned from the city and is no longer able to access city services.

		return SUCCESS;
	}

};

#endif //CITYBANCOMMAND_H_
