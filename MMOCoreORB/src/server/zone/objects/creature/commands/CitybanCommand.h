/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ZoneServer* zserv = creature->getZoneServer();

		ManagedReference<SceneObject*> targetObject = zserv->getObject(target);

		if (targetObject == NULL || !targetObject->isPlayerCreature() || targetObject == creature) {
			return INVALIDTARGET;
		}

		CreatureObject* targetCreature = cast<CreatureObject*>(targetObject.get());

		ManagedReference<CityRegion*> city = creature->getCityRegion().get();

		if (city == NULL || city != targetObject->getCityRegion().get()) {
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
		city->removeSpecializationModifiers(targetCreature);

		targetCreature->sendSystemMessage("@city/city:city_banned"); //You have been banned from the this city.  You may no longer use any city services.

		StringIdChatParameter params("city/city", "city_ban_done");
		params.setTT(targetCreature->getDisplayedName());
		creature->sendSystemMessage(params); //%TT has been banned from the city and is no longer able to access city services.

		return SUCCESS;
	}

};

#endif //CITYBANCOMMAND_H_
