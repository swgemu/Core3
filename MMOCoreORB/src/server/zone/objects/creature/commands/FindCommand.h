/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef FINDCOMMAND_H_
#define FINDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/chat/ChatManager.h"
#include "server/zone/Zone.h"

#include "server/zone/objects/creature/commands/QueueCommand.h"

#include "server/zone/objects/player/sessions/FindSession.h"

class FindCommand: public QueueCommand {

public:

	FindCommand(const String& name, ZoneProcessServer* server) :
		QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		try {

			CreatureObject* player = cast<CreatureObject*>(creature);
			StringTokenizer args(arguments.toString());
			String location;

			ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::FIND);
			ManagedReference<FindSession*> session = dynamic_cast<FindSession*>(facade.get());

			if (session == NULL) {
				session = new FindSession(player);
			}

			if (args.hasMoreTokens()) {
				args.getStringToken(location);
				location = location.toLowerCase();

				if (location == "clear") {
					PlayerObject* po = player->getPlayerObject();

					po->removeWaypointBySpecialType(WaypointObject::SPECIALTYPE_FIND, true);

					return SUCCESS;
				}

				String mapLocType = location;

				if (!mapLocType.isEmpty())
					session->findPlanetaryObject(mapLocType);

			} else {
				session->initalizeFindMenu();
				return SUCCESS;
			}

		} catch (Exception& e) {
			creature->sendSystemMessage("@base_player:find_general_error"); // /Find was unable to complete your request. Please try again.

		}

		return SUCCESS;
	}

};

#endif //FINDCOMMAND_H_
