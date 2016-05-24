/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef UNCONSENTCOMMAND_H_
#define UNCONSENTCOMMAND_H_

#include "server/zone/ZoneServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "QueueCommand.h"


class UnconsentCommand : public QueueCommand {
public:

	UnconsentCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	static void unconscent(CreatureObject* player, const String& name) {
		PlayerObject* ghost = player->getPlayerObject();
		ghost->removeFromConsentList(name);

		StringIdChatParameter stringId("base_player", "prose_unconsent"); //You revoke your consent from %TO.
		stringId.setTO(name);
		player->sendSystemMessage(stringId);
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

		if (arguments.isEmpty() && !creature->getTargetID()) {
			creature->sendSystemMessage("@error_message:syntax_unconsent"); //syntax: /unconsent {optionally, use commas to seperate several player names}
			return GENERALERROR;
		} //TODO: How can we allow unconsent to be fired from toolbar with the command icon??

		if (!arguments.isEmpty()) {
			StringTokenizer tokenizer(arguments.toString());
			tokenizer.setDelimeter(",");

			while (tokenizer.hasMoreTokens()) {
				String name = "";
				tokenizer.getStringToken(name);
				name = name.toLowerCase();

				PlayerManager* playerManager = server->getPlayerManager();
				bool validName = playerManager->existsName(name);

				if (!validName) {
					creature->sendSystemMessage("@ui_cmnty:friend_location_failed_noname"); //No player with that name exists.
					return GENERALERROR;
				}

				if (!ghost->hasInConsentList(name)) {
					player->sendSystemMessage("That player isn't on your consent list.");
					return GENERALERROR;
				}

				if (server->getZoneServer()->getPlayerManager()->existsName(name))
					unconscent(player, name);
			}
		} else {

			ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

			if (object == NULL || !object->isPlayerCreature() || object == creature)
				return INVALIDTARGET;

			CreatureObject* playerTarget = cast<CreatureObject*>( object.get());

			unconscent(player, playerTarget->getFirstName().toLowerCase());

			StringIdChatParameter stringId2("base_player", "prose_lost_consent"); //%TO no longer consents you.
			stringId2.setTO(creature->getObjectID());
			if (playerTarget->isPlayerCreature()) {
				playerTarget->sendSystemMessage(stringId2);
			}

		}

		return SUCCESS;
	}

};

#endif //UNCONSENTCOMMAND_H_
