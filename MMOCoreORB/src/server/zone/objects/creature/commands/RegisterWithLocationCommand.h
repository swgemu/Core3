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

#ifndef REGISTERWITHLOCATIONCOMMAND_H_
#define REGISTERWITHLOCATIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class RegisterWithLocationCommand : public QueueCommand {
public:

	RegisterWithLocationCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* player, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(player))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(player))
			return INVALIDLOCOMOTION;

		if (!player->isPlayerCreature())
			return GENERALERROR;

		// If outside don't bother doing anything ...
		if(player->getParentID() != 0) {
			bool flagDoc = isNoviceDoctor(player);
			bool flagEnt = isNoviceEntertainer(player);

			if ( flagDoc || flagEnt ) {
				if (flagDoc && isInMedicalBuilding(player)) {
						addPlayerToBuilding(player);
						return SUCCESS;
				}
				// NOT else if! (Char is both a doctor and an entertainer, etc.)
				if (flagEnt && isInEntertainingBuilding(player)) {
						addPlayerToBuilding(player);
						return SUCCESS;
				}
				// Right profession, wrong place ...
				player->sendSystemMessage("This building is not a valid registration location for your profession.");
			}
			//  Client handles the 'else' scenario
		} else {
			// "You cannot register at a location that is not registered with the planetary map."
			player->sendSystemMessage("@faction/faction_hq/faction_hq_response:cannot_register");
		}

		return SUCCESS;
	}

	void addPlayerToBuilding(CreatureObject* player) {
		ManagedReference<BuildingObject*> building = player->getRootParent().get().castTo<BuildingObject*>();
		if (building != NULL) {
			Locker blocker(building, player);
			building->registerProfessional(player);
		}
	}

	bool isNoviceDoctor(CreatureObject* player) {
		return player->hasSkill("science_doctor_novice");
	}

	bool isNoviceEntertainer(CreatureObject* player) {
		return (player->hasSkill("social_musician_novice") ||
				player->hasSkill("social_dancer_novice"));
	}

	bool isInMedicalBuilding(CreatureObject* player) {
		ManagedReference<BuildingObject*> building = player->getRootParent().get().castTo<BuildingObject*>();
		if (building != NULL) {
			PlanetMapCategory* pmc = building->getPlanetMapSubCategory();

			if (pmc == NULL)
				pmc = building->getPlanetMapCategory();

			if (pmc == NULL)
				return false;

			String categoryName = pmc->getName();
			if (categoryName == "medicalcenter" || categoryName == "tavern")
				return true;
		}

		return false;
	}

	bool isInEntertainingBuilding(CreatureObject* player) {
		ManagedReference<BuildingObject*> building = player->getRootParent().get().castTo<BuildingObject*>();
		if (building != NULL) {
			PlanetMapCategory* pmc = building->getPlanetMapSubCategory();

			if (pmc == NULL)
				pmc = building->getPlanetMapCategory();

			if (pmc == NULL)
				return false;

			String categoryName = pmc->getName();
			if (categoryName == "hotel" || categoryName == "cantina" || categoryName == "theater" || categoryName == "guild_theater" || categoryName == "tavern")
				return true;
		}

		return false;
	}

};

#endif //REGISTERWITHLOCATIONCOMMAND_H_
