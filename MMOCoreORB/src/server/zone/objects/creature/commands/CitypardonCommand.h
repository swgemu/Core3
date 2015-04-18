/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CITYPARDONCOMMAND_H_
#define CITYPARDONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class CitypardonCommand : public QueueCommand {
public:

	CitypardonCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ZoneServer* zserv = creature->getZoneServer();

		ManagedReference<SceneObject*> targetObject = zserv->getObject(target);

		if (targetObject == NULL || !targetObject->isPlayerCreature() || targetObject == creature)
			return INVALIDTARGET;

		CreatureObject* targetCreature = cast<CreatureObject*>(targetObject.get());

		ManagedReference<CityRegion*> city = creature->getCityRegion().get();

		if (city == NULL || city != targetObject->getCityRegion().get()) {
			creature->sendSystemMessage("@city/city:not_in_city"); //You must be in a city to use this command.
			return GENERALERROR;
		}

		Locker lock(city, creature);

		if (!city->isBanned(targetCreature->getObjectID()))
			return INVALIDTARGET; //They aren't even banned...

		if (!city->isMilitiaMember(creature->getObjectID())) {
			creature->sendSystemMessage("@city/city:not_militia"); //You must be a member of the city militia to use this command.
			return GENERALERROR;
		}

		city->removeBannedPlayer(targetCreature->getObjectID());
		city->applySpecializationModifiers(targetCreature);

		targetCreature->sendSystemMessage("@city/city:city_pardoned"); //You have been pardoned and are once again able to use city services.

		StringIdChatParameter params("city/city", "city_pardon_done"); //%TT has been pardoned and is now able to use city services.
		params.setTT(targetCreature->getDisplayedName());
		creature->sendSystemMessage(params);

		return SUCCESS;
	}

};

#endif //CITYPARDONCOMMAND_H_
