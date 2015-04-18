/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GRANTZONINGRIGHTSCOMMAND_H_
#define GRANTZONINGRIGHTSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class GrantZoningRightsCommand : public QueueCommand {
public:

	GrantZoningRightsCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<SceneObject*> targetObject = creature->getZoneServer()->getObject(target);

		if (targetObject == NULL || !targetObject->isPlayerCreature() || targetObject == creature)
			return INVALIDTARGET;

		ManagedReference<CityRegion*> city = creature->getCityRegion().get();

		if (city == NULL || city != targetObject->getCityRegion().get()) {
			creature->sendSystemMessage("@city/city:not_in_city"); //You must be in a city to use this command.
			return GENERALERROR;
		}

		Locker clocker(city, creature);

		if (!city->isMilitiaMember(creature->getObjectID())) {
			creature->sendSystemMessage("@city/city:grant_rights_fail"); //You must be the mayor of the city or a member of the city militia to grant zoning rights.
		}

		CreatureObject* targetPlayer = cast<CreatureObject*>( targetObject.get());

		if (city->isMayor(target))
			return GENERALERROR; //Cannot revoke the rights of the mayor

		//Target already has zoning rights
		if (city->hasZoningRights(target)) {
			city->removeZoningRights(target);

			creature->sendSystemMessage("@city/city:rights_revoked"); //You have revoked their zoning rights.
			targetPlayer->sendSystemMessage("@city/city:rights_revoked_other"); //Your zoning rights have been revoked.
		} else {
			city->addZoningRights(target);

			StringIdChatParameter params;
			params.setStringId("@city/city:rights_granted"); //You have been granted zoning rights in the city of %TO for 24 hours.
			params.setTO(city->getRegionName());
			targetPlayer->sendSystemMessage(params);

			params.setStringId("@city/city:rights_granted_self"); //You have granted %TO zoning rights for 24 hours.
			params.setTO(targetPlayer->getDisplayedName());
			creature->sendSystemMessage(params);
		}

		return SUCCESS;
	}

};

#endif //GRANTZONINGRIGHTSCOMMAND_H_
