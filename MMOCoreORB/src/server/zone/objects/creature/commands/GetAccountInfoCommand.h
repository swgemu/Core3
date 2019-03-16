/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETACCOUNTINFOCOMMAND_H_
#define GETACCOUNTINFOCOMMAND_H_

#include "server/login/account/AccountManager.h"
#include "server/zone/objects/player/sessions/sui/PlayerManagementSessionSuiCallback.h"
#include "engine/service/proto/BaseClientProxy.h"

class GetAccountInfoCommand : public QueueCommand {
public:

	GetAccountInfoCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		Reference<PlayerObject*> admin = creature->getSlottedObject("ghost").castTo<PlayerObject*>();

		if(admin == nullptr)
			return GENERALERROR;

		Reference<PlayerManagementSession*> session;
		Reference<CreatureObject*> targetCreature;
		Reference<Account*> account;
		auto playerManager = server->getPlayerManager();

		session = creature->getActiveSession(SessionFacadeType::PLAYERMANAGEMENT).castTo<PlayerManagementSession*>();

		if(session != nullptr) {
			if(!admin->hasSuiBoxWindowType(SuiWindowType::ADMIN_ACCOUNTINFO))
				creature->dropActiveSession(SessionFacadeType::PLAYERMANAGEMENT);
			else {
				creature->sendSystemMessage("You are already viewing an account");
				return GENERALERROR;
			}
		}

		StringTokenizer args(arguments.toString());

		if(args.hasMoreTokens()) {
			String type;
			args.getStringToken(type);

			if(!args.hasMoreTokens()) {
				sendUsage(creature);
				return GENERALERROR;
			}

			String name;
			args.getStringToken(name);

			if(type.toLowerCase() == "-c") {
				targetCreature = playerManager->getPlayer(name);

				if (targetCreature != nullptr) {
				    auto ghost = targetCreature->getPlayerObject();

					if (ghost != nullptr)
							account = ghost->getAccount();
				}

				if (account != nullptr) {
					Locker accLocker(account);
					account->updateFromDatabase();
				} else {
					creature->sendSystemMessage("Error fetching Account Object from Player Object");
					return GENERALERROR;
				}
			} else if(type.toLowerCase() == "-a") {
				while(args.hasMoreTokens()) {
					String token;
					args.getStringToken(token);

					name += " " + token;
				}

				account = AccountManager::getAccount(name, true);

				if(account == nullptr) {
					try {
						account = AccountManager::getAccount(Long::valueOf(name), true);
					} catch(Exception& e) {

					}
				}
			} else {
				sendUsage(creature);
				return GENERALERROR;
			}
		} else {
			sendUsage(creature);
			return GENERALERROR;
		}

		if(account == nullptr) {
			creature->sendSystemMessage("Account not found");
			return SUCCESS;
		}

		Locker writeLock(account);

		Time createdTime(account->getTimeCreated());

		Reference<CharacterList*> characterList = account->getCharacterList();

		Reference<SuiListBox*> box = new SuiListBox(creature, SuiWindowType::ADMIN_ACCOUNTINFO, SuiListBox::HANDLETHREEBUTTON);
		box->setPromptTitle("Account Info");

		session = new PlayerManagementSession(account, creature);

		creature->addActiveSession(SessionFacadeType::PLAYERMANAGEMENT, session);

		session->addAccountSui(box);

		StringBuffer header;
		header << "Account Name: " << account->getUsername() << endl;
		header << "Account ID: " << String::valueOf(account->getAccountID()) << endl;
		header << "Station ID: " << String::valueOf(account->getStationID()) << endl;
		header << "Admin Level: " << String::valueOf(account->getAdminLevel()) << endl;
		header << "Created: " << createdTime.getFormattedTime() << endl;

		if(account->isBanned()) {
			header << "\\#FF0000 (BANNED)\\#FFFFFF " << endl;
			header << session->getBanDuration(account->getBanExpires());
			header << "Reason: "  << account->getBanReason() << endl;

			Reference<Account*> adminAccount = AccountManager::getAccount(account->getBanAdmin());

			if(adminAccount != nullptr) {
				Locker writeAdminLock(adminAccount);

				header << "Banned by: " << adminAccount->getUsername() << endl;
			}
		}

		box->setOtherButton(true, "@data Ban/Unban");
		box->setPromptText(header.toString());
		box->setOkButton(true, "@command_info");
		box->setCancelButton(true, "@cancel");
		box->setCallback(new PlayerManagementSessionSuiCallback(creature->getZoneServer()));
		box->setUsingObject(creature);
		admin->addSuiBox(box);

		String username = account->getUsername();
		if(account->isBanned())
			username += " \\#FF0000(BANNED)\\#FFFFFF ";
		box->addMenuItem(username, 0);

		VectorMap<String, Vector<String> > characters;

		String loggedInIp;

		for(int i = 0; i < characterList->size(); ++i) {
			CharacterListEntry* entry = &characterList->get(i);

			Reference<PlayerObject*> ghost;
			Reference<ZoneClientSession*> charClient;

			if(entry->getGalaxyID() == server->getZoneServer()->getGalaxyID()) {
				targetCreature = playerManager->getPlayer(entry->getFirstName());

				if(targetCreature != nullptr && targetCreature->isPlayerCreature()) {
					ghost = targetCreature->getPlayerObject();

					if (ghost != nullptr)
							charClient = targetCreature->getClient();
				}
			}

			if (charClient != nullptr) {
				BaseClientProxy* session = charClient->getSession();

				if (session != nullptr) {
					loggedInIp = session->getIPAddress();
				}
			}

			StringBuffer gname;
			gname << entry->getGalaxyID() << " : " << entry->getGalaxyName();

			if(!characters.contains(gname.toString()))
				characters.put(gname.toString(), Vector<String>());

			Vector<String>* galaxy = &characters.get(gname.toString());

			StringBuffer line;
			line << "\t\t" << entry->getFullName();

			if(ghost != nullptr) {
				if(ghost->isOnline())
					line << " \\#00FF00(ONLINE)\\#FFFFFF ";
				else {
					line << " \\#AAAAAA(Last On: " << ghost->getLastLogout()->getFormattedTime() << ")\\#FFFFFF ";
				}
			} else {
				line << " \\#EE7600(n/a)\\#FFFFFF ";
			}

			if(entry->isBanned()) {
				line << " \\#FF0000(BANNED)\\#FFFFFF " << entry->getBanReason();
			}

			galaxy->add(line.toString());
		}

		for(int i = 0; i < characters.size(); ++i) {
			Vector<String>* galaxy = &characters.get(i);

			String galaxyName = characters.elementAt(i).getKey();

			StringTokenizer tokenizer(galaxyName);

			uint32 galaxyID = tokenizer.getIntToken();

			GalaxyBanEntry* galaxyBan = account->getGalaxyBan(galaxyID);
			if(galaxyBan != nullptr)
				galaxyName += " \\#FF0000(BANNED)\\#FFFFFF" + galaxyBan->getBanReason();

			box->addMenuItem("\t" + galaxyName, 0);

			for(int j = 0; j < galaxy->size(); ++j) {
				box->addMenuItem(galaxy->get(j), 0);
			}
		}

		if (!loggedInIp.isEmpty()) {
			header << endl;
			header << "Accounts logged in from this ip: " << loggedInIp << endl;
			SortedVector<uint32> loggedInAccounts = server->getZoneServer()->getPlayerManager()->getOnlineZoneClientMap()->getAccountsLoggedIn(loggedInIp);

			for (int i = 0; i < loggedInAccounts.size(); ++i){
				Reference<Account*> otherAccount = AccountManager::getAccount(loggedInAccounts.get(i));

				if (otherAccount != nullptr) {
					header << "\t" << otherAccount->getUsername() << "|" << loggedInAccounts.get(i) << endl;
				}
			}
		}

		box->setPromptText(header.toString());

		creature->sendMessage(box->generateMessage());

		return SUCCESS;
	}

	void sendUsage(CreatureObject* creature) const {
		creature->sendSystemMessage("Usage /getAccountInfo [-a|-b|-c] [args]");
		creature->sendSystemMessage("	ex: /getAccountInfo -a <accountname>");
		creature->sendSystemMessage("	ex: /getAccountInfo -c <character first name>");
	}
};

#endif // GETACCOUNTINFOCOMMAND_H_
