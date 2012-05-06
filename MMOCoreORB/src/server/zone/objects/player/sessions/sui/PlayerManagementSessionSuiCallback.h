/*
 * FindSessionSuiCallback.h
 *
 *  Created on: Jun 24, 2011
 *      Author: polonel
 */

#ifndef PLAYERMANAGEMENTSESSIONSUICALLBACK_H_
#define PLAYERMANAGEMENTSESSIONSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/admin/PlayerManagementSession.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"

class PlayerManagementSessionSuiCallback : public SuiCallback {
public:
	PlayerManagementSessionSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {

		if(suiBox->getWindowType() == SuiWindowType::ADMIN_ACCOUNTINFO) {
			runAccountInfo(player, suiBox, cancelPressed, args);
			return;
		}

		if(suiBox->getWindowType() == SuiWindowType::ADMIN_BAN_DURATION) {
			runDurationCallback(player, suiBox, cancelPressed, args);
			return;
		}

		if(suiBox->getWindowType() == SuiWindowType::ADMIN_BAN_REASON) {
			runReasonCallback(player, suiBox, cancelPressed, args);
			return;
		}

		if(suiBox->getWindowType() == SuiWindowType::ADMIN_BAN_SUMMARY) {
			runSummaryCallback(player, suiBox, cancelPressed, args);
			return;
		}

		if(suiBox->getWindowType() == SuiWindowType::ADMIN_UNBAN_SUMMARY) {
			runUnbanSummaryCallback(player, suiBox, cancelPressed, args);
			return;
		}
	}

	void runAccountInfo(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::PLAYERMANAGEMENT);
		ManagedReference<PlayerManagementSession*> session = cast<PlayerManagementSession*>(facade.get());
		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		if (session == NULL || playerManager == NULL) {
			ManagedReference<CreatureObject*> pl = cast<CreatureObject*>( suiBox->getUsingObject());
			if (pl != NULL)
				pl->dropActiveSession(SessionFacadeType::PLAYERMANAGEMENT);

			return;
		}

		if (args->size() < 1 || cancelPressed) {
			session->cancelSession();
			return;
		}

		bool otherPressed = Bool::valueOf(args->get(0).toString());

		int index = Integer::valueOf(args->get(1).toString());
		String firstName = "";
		int tablevel = 0;

		if(index != -1) {
			SuiListBox* listBox = cast<SuiListBox*>( suiBox);

			String listString = listBox->getMenuItemName(index);
			while(listString.contains("\t")) {
				listString = listString.replaceFirst("\t", "");
				tablevel++;
			}

			listString = listString.trim();
			StringTokenizer tokenizer(listString);
			tokenizer.getStringToken(listString);

			String playerName = "";
			String galaxyName = "";

			if(tablevel == 1) {
				galaxyName = listString;
			}

			if(tablevel == 2) {
				galaxyName = getPlayerGalaxyName(listBox, index);
				playerName = listString;
			}



			if (otherPressed) {

				session->ban(tablevel, galaxyName, playerName);
				return;
			}
		}

		session->getPlayerInfo(tablevel, firstName);
	}

	String getPlayerGalaxyName(SuiListBox* listBox, int index) {

		while(index > 0) {
			index--;

			int tablevel = 0;

			String listString = listBox->getMenuItemName(index);
			while(listString.contains("\t")) {
				listString = listString.replaceFirst("\t", "");
				tablevel++;
			}

			listString = listString.trim();
			StringTokenizer tokenizer(listString);
			tokenizer.getStringToken(listString);

			if(tablevel == 1)
				return listString;

		}

		return "";

	}

	void runDurationCallback(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::PLAYERMANAGEMENT);
		ManagedReference<PlayerManagementSession*> session = cast<PlayerManagementSession*>(facade.get());
		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		if (session == NULL || playerManager == NULL) {
			ManagedReference<CreatureObject*> pl = cast<CreatureObject*>( suiBox->getUsingObject());
			if (pl != NULL)
				pl->dropActiveSession(SessionFacadeType::PLAYERMANAGEMENT);

			return;
		}

		if (!suiBox->isInputBox() || player == NULL || cancelPressed || args->size() <= 0) {
			session->sendAccountInfo();
			return;
		}

		String duration = args->get(0).toString();
		session->parseBanDuration(duration);
	}

	void runReasonCallback(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::PLAYERMANAGEMENT);
		ManagedReference<PlayerManagementSession*> session = cast<PlayerManagementSession*>(facade.get());
		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		if (session == NULL || playerManager == NULL) {
			ManagedReference<CreatureObject*> pl = cast<CreatureObject*>( suiBox->getUsingObject());
			if (pl != NULL)
				pl->dropActiveSession(SessionFacadeType::PLAYERMANAGEMENT);

			return;
		}

		if (!suiBox->isInputBox() || player == NULL || cancelPressed || args->size() <= 0) {
			session->sendAccountInfo();
			return;
		}

		String reason = args->get(0).toString();
		session->setBanReason(reason);
	}

	void runSummaryCallback(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::PLAYERMANAGEMENT);
		ManagedReference<PlayerManagementSession*> session = cast<PlayerManagementSession*>(facade.get());
		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		if (session == NULL || playerManager == NULL) {
			ManagedReference<CreatureObject*> pl = cast<CreatureObject*>( suiBox->getUsingObject());
			if (pl != NULL)
				pl->dropActiveSession(SessionFacadeType::PLAYERMANAGEMENT);

			return;
		}

		if (args->size() < 1 || cancelPressed) {
			return;
		}

		int index = Integer::valueOf(args->get(0).toString());

		if(index == 0) {
			session->sendBanDuration();
		} else if(index == 1) {
			session->sendBanReason();
		} else if(index == 2) {
			session->completeBan();
		} else {
			session->showBanSummary();
		}
	}

	void runUnbanSummaryCallback(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::PLAYERMANAGEMENT);
		ManagedReference<PlayerManagementSession*> session = cast<PlayerManagementSession*>(facade.get());
		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();

		if (session == NULL || playerManager == NULL) {
			ManagedReference<CreatureObject*> pl = cast<CreatureObject*>( suiBox->getUsingObject());
			if (pl != NULL)
				pl->dropActiveSession(SessionFacadeType::PLAYERMANAGEMENT);

			return;
		}

		if (args->size() < 1 || cancelPressed) {
			return;
		}

		session->completeBan();
	}
};

#endif /* PLAYERMANAGEMENTSESSIONSUICALLBACK_H_ */
