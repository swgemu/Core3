/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FINDMYTRAINERCOMMAND_H_
#define FINDMYTRAINERCOMMAND_H_

class FindMyTrainerCommand : public QueueCommand {
public:
	FindMyTrainerCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		auto ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		if (ghost->getJediState() < 2 || !creature->hasSkill("force_title_jedi_rank_02"))
			return GENERALERROR;

		auto zoneServer = server->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		String planet = ghost->getTrainerZoneName();

		if (planet.isEmpty()) {
			// Pick a trainer for the Jedi
			setJediTrainer(zoneServer, ghost);

			// Retrieve trainer zone from the player object
			planet = ghost->getTrainerZoneName();
		} else {
			auto trainerZone = zoneServer->getZone(planet);

			if (trainerZone == nullptr) {
				setJediTrainer(zoneServer, ghost);
				planet = ghost->getTrainerZoneName();
			}
		}

		uint32 planetCRC = planet.hashCode();

		Vector3 coords = ghost->getJediTrainerCoordinates();

		String name = "@jedi_spam:trainer_waypoint_name";

		ManagedReference<WaypointObject*> waypointObj = (zoneServer->createObject(0xc456e788, 1)).castTo<WaypointObject*>();

		Locker locker(waypointObj);

		waypointObj->setPlanetCRC(planetCRC);
		waypointObj->setPosition(coords.getX(), 0, coords.getY());
		waypointObj->setCustomObjectName(name, false);

		ghost->addWaypoint(waypointObj, true, true);

		creature->sendSystemMessage("@jedi_spam:waypoint_created_to_trainer");

		return SUCCESS;
	}

	void setJediTrainer(ZoneServer* zoneServer, PlayerObject* ghost) const {
		if (ghost == nullptr || zoneServer == nullptr)
			return;

		Vector<ManagedReference<SceneObject*>> trainers;
		Vector<uint32> trainerTypes = {STRING_HASHCODE("trainer_brawler"), STRING_HASHCODE("trainer_artisan"), STRING_HASHCODE("trainer_scout"), STRING_HASHCODE("trainer_marksman"), STRING_HASHCODE("trainer_entertainer"), STRING_HASHCODE("trainer_medic")};

		// Get all trainers in galaxy and build list based on above trainer sub map categories
		for (int i = 0; i < zoneServer->getZoneCount(); ++i) {
			auto zone = zoneServer->getZone(i);

			if (zone == nullptr)
				continue;

			SortedVector<ManagedReference<SceneObject*>> objectList = zone->getPlanetaryObjectList("trainer");

			for (int j = 0; j < objectList.size(); ++j) {
				ManagedReference<SceneObject*> trainer = objectList.get(j);

				if (trainer == nullptr)
					continue;

				uint32 subCatCrc = trainer->getPlanetMapSubCategoryCRC();

				for (int k = 0; k < trainerTypes.size(); ++k) {
					uint32 typeHash = trainerTypes.get(k);

					if (subCatCrc == 0 || typeHash != subCatCrc)
						continue;

					trainers.add(trainer);

					break;
				}
			}
		}

		bool found = false;
		Vector3 coords;
		String zoneName = "";
		int size = trainers.size();

		if (size <= 0)
			return;

		while (!found) {
			SceneObject* trainer = trainers.get(System::random(size - 1));

			if (trainer == nullptr)
				continue;

			CreatureObject* trainerCreo = trainer->asCreatureObject();

			if (trainerCreo == nullptr)
				continue;

			Zone* trainerZone = trainerCreo->getZone();

			if (trainerZone == nullptr || trainerZone->getZoneName() == "tutorial")
				continue;

			if (!(trainerCreo->getOptionsBitmask() & OptionBitmask::CONVERSE))
				continue;

			ManagedReference<CityRegion*> city = trainerCreo->getCityRegion().get();

			// Make sure it's not a player-city trainer.
			if (city != nullptr && !city->isClientRegion())
				continue;

			zoneName = trainerZone->getZoneName();
			coords = trainerCreo->getWorldPosition();
			found = true;
		}

		ghost->setTrainerCoordinates(coords);
		ghost->setTrainerZoneName(zoneName); // For the waypoint.
	}
};

#endif // FINDMYTRAINERCOMMAND_H_
