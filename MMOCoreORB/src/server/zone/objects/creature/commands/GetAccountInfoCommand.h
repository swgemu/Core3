/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETACCOUNTINFOCOMMAND_H_
#define GETACCOUNTINFOCOMMAND_H_

#include "server/login/account/AccountManager.h"
#include "server/zone/objects/player/sessions/sui/PlayerManagementSessionSuiCallback.h"

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
			} else if(type.toLowerCase() == "-i") {
				try {
					SortedVector<uint32> loggedInAccounts = server->getZoneServer()->getPlayerManager()->getOnlineZoneClientMap()->getAccountsLoggedIn(name);

					if (loggedInAccounts.size() > 0)
						account = AccountManager::getAccount(loggedInAccounts.get(0));
					else
						creature->sendSystemMessage("Did not find any online accounts with ip [" + name + "]");
				} catch(Exception& e) {
					// Do nothing
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

		// Get first logged in ip on this galaxy
		String loggedInIp;

		for(int i = 0; i < characterList->size(); ++i) {
			auto entry = &characterList->get(i);

			if(entry->getGalaxyID() == server->getZoneServer()->getGalaxyID()) {
				targetCreature = playerManager->getPlayer(entry->getFirstName());

				if(targetCreature != nullptr && targetCreature->isPlayerCreature()) {
					auto ghost = targetCreature->getPlayerObject();

					if (ghost != nullptr) {
						auto charClient = targetCreature->getClient();

						if (charClient != nullptr)
							loggedInIp = charClient->getIPAddress();
					}
				}
			}
		}

		if (!loggedInIp.isEmpty()) {
			header << endl;
			header << "logged from ip: " << loggedInIp << endl;

			box->addMenuItem("Accounts logged in from this ip: " + loggedInIp, 0);

			SortedVector<uint32> loggedInAccounts = server->getZoneServer()->getPlayerManager()->getOnlineZoneClientMap()->getAccountsLoggedIn(loggedInIp);

			for (int i = 0; i < loggedInAccounts.size(); ++i) {
				uint32 otherAccountID = loggedInAccounts.get(i);
				Reference<Account*> otherAccount = AccountManager::getAccount(otherAccountID);

				if (otherAccount != nullptr) {
					StringBuffer line;
					line << "\t\t\t" << otherAccount->getUsername() << ": " << otherAccountID;
					box->addMenuItem(line.toString(), otherAccountID);
				}
			}
		}

		String username = account->getUsername();
		if(account->isBanned())
			username += " \\#FF0000(BANNED)\\#FFFFFF ";
		box->addMenuItem("Account: " + username, 0);

		VectorMap<String, Vector<String> > characters;

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

			StringBuffer gname;
			gname << entry->getGalaxyID() << " : " << entry->getGalaxyName();

			if(!characters.contains(gname.toString()))
				characters.put(gname.toString(), Vector<String>());

			Vector<String>* galaxy = &characters.get(gname.toString());

			StringBuffer line;
			line << "\t\t" << entry->getFullName();

			if(ghost != nullptr) {
				if(ghost->isOnline())
					line << " \\#00FF00(ONLINE";
				else {
					line << " \\#AAAAAA(Last On: " << ghost->getLastLogout()->getFormattedTime();
				}
			} else {
				line << " \\#EE7600(n/a";
			}

			if(entry->isBanned()) {
				line << " \\#FF0000(BANNED: " << entry->getBanReason();
			}

			if (charClient != nullptr)
				line << "\\#00FF00; ip " << charClient->getIPAddress();

			line << ")\\#FFFFFF";

			galaxy->add(line.toString());
		}

		for(int i = 0; i < characters.size(); ++i) {
			Vector<String>* galaxy = &characters.get(i);

			String galaxyName = characters.elementAt(i).getKey();

			StringTokenizer tokenizer(galaxyName);

			uint32 galaxyID = tokenizer.getIntToken();

			const GalaxyBanEntry* galaxyBan = account->getGalaxyBan(galaxyID);
			if(galaxyBan != nullptr)
				galaxyName += " \\#FF0000(BANNED)\\#FFFFFF" + galaxyBan->getBanReason();

			box->addMenuItem("\t" + galaxyName, 0);

			for(int j = 0; j < galaxy->size(); ++j) {
				box->addMenuItem(galaxy->get(j), 0);
			}
		}

		box->setPromptText(header.toString());

		creature->sendMessage(box->generateMessage());

		return SUCCESS;
	}

	void sendUsage(CreatureObject* creature) const {
		creature->sendSystemMessage("Usage /getAccountInfo [-a|-c|-i] [args]");
		creature->sendSystemMessage("Example: /getAccountInfo -a <accountname>");
		creature->sendSystemMessage("Example: /getAccountInfo -c <character first name>");
		creature->sendSystemMessage("Example: /getAccountInfo -i <ip address>");
	}
};

#endif // GETACCOUNTINFOCOMMAND_H_
