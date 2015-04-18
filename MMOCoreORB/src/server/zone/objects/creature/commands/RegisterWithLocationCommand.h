/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REGISTERWITHLOCATIONCOMMAND_H_
#define REGISTERWITHLOCATIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class RegisterWithLocationCommand : public QueueCommand {
public:

	RegisterWithLocationCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* player, const uint64& target, const UnicodeString& arguments) const {

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

	void addPlayerToBuilding(CreatureObject* player) const {
		ManagedReference<BuildingObject*> building = player->getRootParent().get().castTo<BuildingObject*>();
		if (building != NULL) {
			Locker blocker(building, player);
			building->registerProfessional(player);
		}
	}

	bool isNoviceDoctor(CreatureObject* player) const {
		return player->hasSkill("science_doctor_novice");
	}

	bool isNoviceEntertainer(CreatureObject* player) const {
		return (player->hasSkill("social_musician_novice") ||
				player->hasSkill("social_dancer_novice"));
	}

	bool isInMedicalBuilding(CreatureObject* player) const {
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

	bool isInEntertainingBuilding(CreatureObject* player) const {
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
