/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef FINDCOMMAND_H_
#define FINDCOMMAND_H_

#include "server/zone/objects/player/sessions/FindSession.h"

class FindCommand : public QueueCommand {
public:
	FindCommand(const String& name, ZoneProcessServer* server) : QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		try {
			StringTokenizer args(arguments.toString());

			ManagedReference<Facade*> facade = creature->getActiveSession(SessionFacadeType::FIND);
			ManagedReference<FindSession*> session = dynamic_cast<FindSession*>(facade.get());

			if (session == nullptr) {
				session = new FindSession(creature);
			}

			if (args.hasMoreTokens()) {
				String mapCategory = "";

				args.getStringToken(mapCategory);

				mapCategory = mapCategory.toLowerCase();

				if (mapCategory == "clear") {
					return clearFind(creature);
				}

				if (mapCategory.contains(":"))
					mapCategory = mapCategory.replaceFirst(":", "_");

				String mapSubCategory = "";

				if (mapCategory.contains("_")) {
					mapSubCategory = mapCategory;

					StringTokenizer mapTokens(mapCategory);
					String mapCat;

					mapTokens.setDelimeter("_");
					mapTokens.getStringToken(mapCat);

					mapCategory = mapCat;
				}

				if (!mapCategory.isEmpty())
					session->findPlanetaryObject(mapCategory, mapSubCategory);

			} else {
				session->initalizeFindMenu();
				return SUCCESS;
			}

		} catch (Exception& e) {
			creature->sendSystemMessage("@base_player:find_general_error"); // /Find was unable to complete your request. Please try again.
		}

		return SUCCESS;
	}

	int clearFind(CreatureObject* player) const {
		if (player == nullptr || !player->isPlayerCreature())
			return GENERALERROR;

		PlayerObject* ghost = player->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		ghost->removeWaypointBySpecialType(WaypointObject::SPECIALTYPE_FIND, true);

		return SUCCESS;
	}
};

#endif // FINDCOMMAND_H_
