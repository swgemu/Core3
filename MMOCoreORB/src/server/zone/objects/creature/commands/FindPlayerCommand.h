/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FINDPLAYERCOMMAND_H_
#define FINDPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/player/PlayerMap.h"

class FindPlayerCommand : public QueueCommand {
public:

	FindPlayerCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		try {
			Reference<SceneObject*> targetObject = NULL;

			StringTokenizer tokenizer(arguments.toString());
			String filter;

			if (tokenizer.hasMoreTokens()) {
				tokenizer.getStringToken(filter);
			}

			ChatManager* chatManager = server->getZoneServer()->getChatManager();
			Locker chatManagerLocker(chatManager);

			PlayerMap* playerMap = chatManager->getPlayerMap();
			playerMap->resetIterator(false);

			ManagedReference<SuiListBox*> findResults = new SuiListBox(creature, SuiWindowType::ADMIN_FIND_PLAYER);
			findResults->setCallback(new FindObjectSuiCallback(server->getZoneServer()));
			findResults->setPromptTitle("Find Player");
			findResults->setPromptText("Here are the online players that match your search:");
			findResults->setCancelButton(true, "");
			findResults->setOkButton(true, "@treasure_map/treasure_map:store_waypoint");
			findResults->setOtherButton(true, "@go");

			while (playerMap->hasNext(false)) {
				ManagedReference<CreatureObject*> player = playerMap->getNextValue(false);
				String name = player->getDisplayedName();

				if (filter.isEmpty() || name.toLowerCase().contains(filter.toLowerCase())) {
					findResults->addMenuItem(name, player->getObjectID());
				}
			}

			if (findResults->getMenuSize() < 1) {
				creature->sendSystemMessage("No players were found that matched that filter.");
				return SUCCESS;
			}

			ghost->addSuiBox(findResults);
			creature->sendMessage(findResults->generateMessage());

		} catch (Exception& e) {
			creature->sendSystemMessage("Syntax: /findplayer <string filter>");
		}

		return SUCCESS;
	}

};

#endif //FINDPLAYERCOMMAND_H_
