/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTSETSTATMIGRATIONDATACOMMAND_H_
#define REQUESTSETSTATMIGRATIONDATACOMMAND_H_

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
