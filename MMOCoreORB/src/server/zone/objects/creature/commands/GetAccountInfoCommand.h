/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GETACCOUNTINFOCOMMAND_H_
#define GETACCOUNTINFOCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/login/account/Account.h"
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

		if(admin == NULL || !admin->isPrivileged())
			return INVALIDTARGET;

		if (admin->getAdminLevel() == 13) {
			creature->sendSystemMessage("QAs cant use this command");
			return GENERALERROR;
		}

		ManagedReference<PlayerManagementSession*> session = NULL;
		ManagedReference<CreatureObject* > targetCreature = NULL;
		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();
		ManagedReference<Account*> account = NULL;

		session = creature->getActiveSession(SessionFacadeType::PLAYERMANAGEMENT).castTo<PlayerManagementSession*>();

		if(session != NULL) {
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

				if (targetCreature != NULL)
					account = playerManager->getAccount(targetCreature->getPlayerObject()->getAccountID());
			} else if(type.toLowerCase() == "-a") {

				while(args.hasMoreTokens()) {
					String token;
					args.getStringToken(token);

					name += " " + token;
				}

				account = playerManager->getAccount(name);

				if(account == NULL) {
					try {
						account = playerManager->getAccount(Long::valueOf(name));
					} catch(Exception& e) {

					}
				}
			}  else if(type.toLowerCase() == "-b") {
				creature->sendSystemMessage("Coming soon");
				return GENERALERROR;
			} else {
				sendUsage(creature);
				return GENERALERROR;
			}

		} else {
			sendUsage(creature);
			return GENERALERROR;
		}

		if(account == NULL) {
			creature->sendSystemMessage("Account not found");
			return SUCCESS;
		}

		Time createdTime(account->getTimeCreated());

		CharacterList* characterList = account->getCharacterList();

		ManagedReference<SuiListBox*> box = new SuiListBox(creature, SuiWindowType::ADMIN_ACCOUNTINFO, SuiListBox::HANDLETHREEBUTTON);
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

			ManagedReference<Account*> adminAccount = playerManager->getAccount(account->getBanAdmin());

			if(adminAccount != NULL)
				header << "Banned by: " << adminAccount->getUsername() << endl;
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

			ManagedReference<PlayerObject* > ghost = NULL;
			
			CharacterListEntry* entry = &characterList->get(i);
			ManagedReference<ZoneClientSession*> charClient;

			if(entry->getGalaxyID() == server->getZoneServer()->getGalaxyID()) {
				targetCreature = playerManager->getPlayer(entry->getFirstName());

				if(targetCreature != NULL && targetCreature->isPlayerCreature()) {
					ghost = targetCreature->getPlayerObject();
					charClient = targetCreature->getClient();
				}
			}
			
			if (charClient != NULL) {
				BaseClientProxy* session = charClient->getSession();
				
				if (session != NULL) {
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

			if(ghost != NULL) {

				if(ghost->isOnline())
					line << " \\#00FF00(ONLINE)\\#FFFFFF ";
				else {
					line << " \\#AAAAAA(Last On: " << ghost->getLastLogout()->getFormattedTime() << ")\\#FFFFFF ";
				}
				/// last seen
				///ghost->getClientLastMovementStamp();
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
			if(galaxyBan != NULL)
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
				ManagedReference<Account*> otherAccount = playerManager->getAccount(loggedInAccounts.get(i));

				if (otherAccount != NULL) {
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
		creature->sendSystemMessage("	ex: /getAccountInfo -b -- Lists bans");
		creature->sendSystemMessage("	ex: /getAccountInfo -c <character first name>");
	}
};

#endif //GETACCOUNTINFOCOMMAND_H_
