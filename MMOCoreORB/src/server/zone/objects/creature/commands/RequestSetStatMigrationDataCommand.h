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

#ifndef REQUESTSETSTATMIGRATIONDATACOMMAND_H_
#define REQUESTSETSTATMIGRATIONDATACOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sessions/MigrateStatsSession.h"
#include "server/zone/managers/player/creation/PlayerCreationManager.h"

class RequestSetStatMigrationDataCommand : public QueueCommand {
public:

	RequestSetStatMigrationDataCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	static uint32 getMaxAttribute(CreatureObject* creature, uint8 attribute) {
		return PlayerCreationManager::instance()->getMaximumAttributeLimit(creature->getSpeciesName(), attribute);
	}

	static uint32 getMinAttribute(CreatureObject* creature, uint8 attribute) {
		return PlayerCreationManager::instance()->getMinimumAttributeLimit(creature->getSpeciesName(), attribute);
	}

	static uint32 getTotalAttribPoints(CreatureObject* creature) {
		return PlayerCreationManager::instance()->getTotalAttributeLimit(creature->getSpeciesName());
	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* player = cast<CreatureObject*>(creature);
		PlayerObject* ghost = player->getPlayerObject();

		ManagedReference<Facade*> facade = creature->getActiveSession(SessionFacadeType::MIGRATESTATS);
		ManagedReference<MigrateStatsSession*> session = dynamic_cast<MigrateStatsSession*>(facade.get());

		if (session == NULL) {
			return GENERALERROR;
		}

		StringTokenizer tokenizer(arguments.toString());
		tokenizer.setDelimeter(" ");

		uint32 targetPointsTotal = 0;
		uint32 targetAttributes[9] = {0,0,0,0,0,0,0,0,0};

		for (int i = 0; tokenizer.hasMoreTokens() && i < 9; ++i) {
			uint32 value = tokenizer.getIntToken();

			if (value < getMinAttribute(player, i) || value > getMaxAttribute(player, i)) {
				creature->info("Suspected stat migration hacking attempt.");
				return GENERALERROR;
			}

			targetAttributes[i] = value;
			targetPointsTotal += value;
		}

		//Here we set the stat migration target attributes.
		//NOTE: We aren't actually migrating the stats at this point.
		if (targetPointsTotal == getTotalAttribPoints(player)) {
			for (int i = 0; i < 9; ++i) {
				session->setAttributeToModify(i, targetAttributes[i]);
			}
		} else {
			creature->error("targetPointsTotal = " + String::valueOf(targetPointsTotal));
			creature->error("totalAttribPoints = " + String::valueOf(getTotalAttribPoints(player)));
			creature->error("Trying to set migratory stats without assigning all available points.");
			return GENERALERROR;
		}

		//Player is in the tutorial zone and is allowed to migrate stats.
		Zone* zone = creature->getZone();

		if (zone != NULL && zone->getZoneName() == "tutorial")
			session->migrateStats();


		return SUCCESS;
	}

};

#endif //REQUESTSETSTATMIGRATIONDATACOMMAND_H_
