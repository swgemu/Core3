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

#ifndef GRANTZONINGRIGHTSCOMMAND_H_
#define GRANTZONINGRIGHTSCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "../../building/city/CityHallObject.h"

class GrantZoningRightsCommand : public QueueCommand {
public:

	GrantZoningRightsCommand(const String& name, ZoneProcessServer* server)
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

		ManagedReference<ActiveArea*> activeRegion = player->getActiveRegion();

		if (activeRegion == NULL || !activeRegion->isRegion()) {
			player->sendSystemMessage("@city/city:grant_rights_fail"); //You must be the mayor of the city or a member of the city militia to grant zoning rights.
			return GENERALERROR;
		}

		Region* region = (Region*) activeRegion.get();
		ManagedReference<CityHallObject*> cityHall = region->getCityHall();

		if (cityHall == NULL || (!cityHall->isMayor(player->getObjectID()) && !cityHall->isMilitiaMember(player->getObjectID()))) {
			player->sendSystemMessage("@city/city:grant_rights_fail"); //You must be the mayor of the city or a member of the city militia to grant zoning rights.
			return GENERALERROR;
		}

		if (cityHall->isMayor(targetPlayer->getObjectID()) || cityHall->isMilitiaMember(targetPlayer->getObjectID()))
			return GENERALERROR; //Cannot revoke the rights of the mayor or a militia member.

		Locker _locker(cityHall);

		//Target already has zoning rights
		if (cityHall->hasZoningRights(targetPlayer->getObjectID())) {
			cityHall->removeZoningRights(targetPlayer->getObjectID());

			player->sendSystemMessage("@city/city:rights_revoked"); //You have revoked their zoning rights.
			targetPlayer->sendSystemMessage("@city/city:rights_revoked_other"); //Your zoning rights have been revoked.
		} else {
			cityHall->addZoningRights(targetPlayer->getObjectID());

			StringIdChatParameter params;
			params.setStringId("@city/city:rights_granted"); //You have been granted zoning rights in the city of %TO for 24 hours.
			params.setTO(region->getObjectName());
			targetPlayer->sendSystemMessage(params);

			params.setStringId("@city/city:rights_granted_self"); //You have granted %TO zoning rights for 24 hours.
			params.setTO(targetPlayer);
			player->sendSystemMessage(params);
		}

		return SUCCESS;
	}

};

#endif //GRANTZONINGRIGHTSCOMMAND_H_
