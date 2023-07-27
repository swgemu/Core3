/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef REGISTERWITHLOCATIONCOMMAND_H_
#define REGISTERWITHLOCATIONCOMMAND_H_

#include "templates/building/SharedBuildingObjectTemplate.h"

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

		ManagedReference<BuildingObject*> building = cast<BuildingObject*>(player->getRootParent());

		// If outside don't bother doing anything ...
		if (building == nullptr) {
			player->sendSystemMessage("@faction/faction_hq/faction_hq_response:no_support"); // This location does not support active/inactive registration status.
			return GENERALERROR;
		}

		bool medBuilding = isInMedicalBuilding(player, building);
		bool entBuilding = isInEntertainingBuilding(player, building);
		bool novDoc = isNoviceDoctor(player);
		bool novEnt = isNoviceEntertainer(player);

		if (medBuilding && entBuilding) {
			if (novDoc || novEnt) {
				addPlayerToBuilding(player, building);
				return SUCCESS;
			}
		} else if (medBuilding) {
			if (novDoc) {
				addPlayerToBuilding(player, building);
				return SUCCESS;
			} else {
				player->sendSystemMessage("@faction/faction_hq/faction_hq_response:no_skills"); // You lack the appropriate skill-set to activate this location.
				return GENERALERROR;
			}
		} else if (entBuilding) {
			if (novEnt) {
				addPlayerToBuilding(player, building);
				return SUCCESS;
			} else {
				player->sendSystemMessage("@faction/faction_hq/faction_hq_response:no_skills"); // You lack the appropriate skill-set to activate this location.
				return GENERALERROR;
			}
		} else {
			player->sendSystemMessage("@faction/faction_hq/faction_hq_response:no_support"); // This location does not support active/inactive registration status.
			return GENERALERROR;
		}

		return SUCCESS;
	}

	void addPlayerToBuilding(CreatureObject* player, BuildingObject* building) const {
		Locker blocker(building, player);
		building->registerProfessional(player);
	}

	bool isNoviceDoctor(CreatureObject* player) const {
		return player->hasSkill("science_doctor_novice");
	}

	bool isNoviceEntertainer(CreatureObject* player) const {
		return (player->hasSkill("social_musician_novice") || player->hasSkill("social_dancer_novice"));
	}

	bool isInMedicalBuilding(CreatureObject* player, BuildingObject* building) const {
		const PlanetMapCategory* pmc = building->getPlanetMapCategory();

		if (pmc == nullptr)
			return false;

		String categoryName = pmc->getName();

		if (categoryName == "medicalcenter" || categoryName == "tavern")
			return true;

		if (categoryName == "imperial" || categoryName == "rebel") {
			const SharedBuildingObjectTemplate* buildingTemplate = cast<const SharedBuildingObjectTemplate*>(building->getObjectTemplate());

			if (buildingTemplate != nullptr && buildingTemplate->getSkillMod("private_medical_rating") > 0) {
				return true;
			}
		}

		return false;
	}

	bool isInEntertainingBuilding(CreatureObject* player, BuildingObject* building) const {
		const PlanetMapCategory* pmc = building->getPlanetMapCategory();

		if (pmc == nullptr)
			return false;

		String categoryName = pmc->getName();

		if (categoryName == "hotel" || categoryName == "cantina" || categoryName == "theater" || categoryName == "guild_theater" || categoryName == "tavern")
			return true;

		if (categoryName == "imperial" || categoryName == "rebel") {
			const SharedBuildingObjectTemplate* buildingTemplate = cast<const SharedBuildingObjectTemplate*>(building->getObjectTemplate());

			if (buildingTemplate != nullptr && buildingTemplate->getSkillMod("private_med_battle_fatigue") > 0) {
				return true;
			}
		}

		return false;
	}

};

#endif //REGISTERWITHLOCATIONCOMMAND_H_
