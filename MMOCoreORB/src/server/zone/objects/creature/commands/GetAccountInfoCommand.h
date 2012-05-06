/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef GETACCOUNTINFOCOMMAND_H_
#define GETACCOUNTINFOCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/login/account/Account.h"
#include "server/zone/objects/player/sessions/sui/PlayerManagementSessionSuiCallback.h"


class GetAccountInfoCommand : public QueueCommand {
public:

	GetAccountInfoCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		PlayerObject* admin = cast<PlayerObject*>(creature->getSlottedObject("ghost"));

		if(admin == NULL || !admin->isPrivileged())
			return INVALIDTARGET;

		ManagedReference<PlayerManagementSession*> session = NULL;
		ManagedReference<CreatureObject* > targetCreature = NULL;
		ManagedReference<PlayerObject* > ghost = NULL;
		ManagedReference<PlayerManager*> playerManager = server->getPlayerManager();
		ManagedReference<Account*> account = NULL;

		session = cast<PlayerManagementSession*>(creature->getActiveSession(SessionFacadeType::PLAYERMANAGEMENT));

		if(session != NULL) {
			creature->sendSystemMessage("You are already viewing an account");
			return GENERALERROR;
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

		if(targetCreature != NULL)
			ghost = targetCreature->getPlayerObject();

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

		for(int i = 0; i < characterList->size(); ++i) {

			CharacterListEntry* entry = &characterList->get(i);

			targetCreature = playerManager->getPlayer(entry->getFirstName());
			if(targetCreature == NULL || !targetCreature->isPlayerCreature())
				continue;

			ghost = targetCreature->getPlayerObject();

			if(!characters.contains(entry->getGalaxyName()))
				characters.put(entry->getGalaxyName(), Vector<String>());

			Vector<String>* galaxy = &characters.get(entry->getGalaxyName());

			StringBuffer line;
			line << "\t\t" << entry->getFullName();

			if(ghost->isLinkDead())
				line << " \\#EE7600(LD)\\#FFFFFF ";
			else if(ghost->isOnline())
				line << " \\#00FF00(ONLINE)\\#FFFFFF ";
			else
				line << " \\#AAAAAA(OFFLINE)\\#FFFFFF ";

			if(entry->isBanned()) {
				line << " \\#FF0000(BANNED)\\#FFFFFF " << entry->getBanReason();
			}

			galaxy->add(line.toString());
		}

		for(int i = 0; i < characters.size(); ++i) {
			Vector<String>* galaxy = &characters.get(i);

			String galaxyName = characters.elementAt(i).getKey();

			GalaxyBanEntry* galaxyBan = account->getGalaxyBan(galaxyName);
			if(galaxyBan != NULL)
				galaxyName += " \\#FF0000(BANNED)\\#FFFFFF" + galaxyBan->getBanReason();

			box->addMenuItem("\t" + galaxyName, 0);

			for(int j = 0; j < galaxy->size(); ++j) {
				box->addMenuItem(galaxy->get(j), 0);
			}
		}

		creature->sendMessage(box->generateMessage());

		return SUCCESS;
	}

	void sendUsage(CreatureObject* creature) {
		creature->sendSystemMessage("Usage /getAccountInfo [-a|-b|-c] [args]");
		creature->sendSystemMessage("	ex: /getAccountInfo -a <accountname>");
		creature->sendSystemMessage("	ex: /getAccountInfo -b -- Lists bans");
		creature->sendSystemMessage("	ex: /getAccountInfo -c <character first name>");
	}
};

#endif //GETACCOUNTINFOCOMMAND_H_
