/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REQUESTSTATMIGRATIONDATACOMMAND_H_
#define REQUESTSTATMIGRATIONDATACOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/sessions/MigrateStatsSession.h"
#include "server/zone/packets/player/StatMigrationTargetsMessage.h"

class RequestStatMigrationDataCommand : public QueueCommand {
public:

	RequestStatMigrationDataCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<Facade*> facade = creature->getActiveSession(SessionFacadeType::MIGRATESTATS);
		ManagedReference<MigrateStatsSession*> session = dynamic_cast<MigrateStatsSession*>(facade.get());

		if (session == NULL) {
			session = new MigrateStatsSession(creature);

			DeltaVector<int>* baseHam = creature->getBaseHAM();

			for (int i = 0; i < 9; ++i) {
				session->setAttributeToModify(i, baseHam->get(i));
			}

			creature->addActiveSession(SessionFacadeType::MIGRATESTATS, session);

			StatMigrationTargetsMessage* smtm = new StatMigrationTargetsMessage(creature);
			creature->sendMessage(smtm);
		} else {
			StatMigrationTargetsMessage* smtm = new StatMigrationTargetsMessage(creature, session);
			creature->sendMessage(smtm);
		}

		return SUCCESS;
	}

};

#endif //REQUESTSTATMIGRATIONDATACOMMAND_H_
