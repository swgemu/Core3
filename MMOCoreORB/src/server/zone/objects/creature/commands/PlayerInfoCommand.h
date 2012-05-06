/*
 * PlayerInfoCommand.h
 *
 *  Created on: 31/03/2012
 *      Author: victor
 */

#ifndef PLAYERINFOCOMMAND_H_
#define PLAYERINFOCOMMAND_H_

#include "engine/engine.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/creature/CreatureObject.h"

class PlayerInfoCommand {
public:
	static int executeCommand(CreatureObject* creature, uint64 target, const UnicodeString& arguments) {
		if (!creature->getPlayerObject()->isPrivileged())
			return 1;

		CreatureObject* targetObject = cast<CreatureObject*>(creature->getZoneServer()->getObject(creature->getTargetID()));

		if (targetObject == NULL || !targetObject->isPlayerCreature())
			targetObject = creature;

		PlayerObject* ghost = targetObject->getPlayerObject();

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, 0);

		box->setPromptTitle("Player Info"); //Register City
		//box->setPromptText("@city/city:register_d");

		StringBuffer msg;
		msg << "SkillMods:\n";

		SkillModList* skillModList = targetObject->getSkillModList();

		StringBuffer promptText;
		promptText << "SkillMods:" << endl;
		promptText << skillModList->getPrintableSkillModList() << endl;

		promptText << "Skills:" << endl;
		SkillList* list = targetObject->getSkillList();

		int totalSkillPointsWasted = 0;

		for (int i = 0; i < list->size(); ++i) {
			Skill* skill = list->get(i);
			promptText << skill->getSkillName() << " point cost:" << skill->getSkillPointsRequired() << endl;

			totalSkillPointsWasted += skill->getSkillPointsRequired();
		}

		promptText << "totalSkillPointsWasted = " << totalSkillPointsWasted;

		box->setPromptText(promptText.toString());

		creature->sendMessage(box->generateMessage());

		/*ManagedReference<PlayerManagementSession*> session =
				cast<PlayerManagementSession*>(creature->getActiveSession(SessionFacadeType::PLAYERMANAGEMENT));

		if(session == NULL) {
			session = new PlayerManagementSession(creature);
			creature->addActiveSession(SessionFacadeType::ACCOUNT_PLAYERMANAGEMENT, session);
		}

		ManagedReference<SuiListBox*> box = session->getPlayerInfoSui();
		if(box == NULL) {
			box = new SuiListBox(creature, SuiWindowType::PLAYER_INFO, SuiListBox::HANDLETHREEBUTTON);
			session->addPlayerInfoSui(box);
		}

		box->clearOptions();
		box->setPromptTitle("Player Info");

		StringBuffer header;
		header << "Account Name: " << account->getUsername() << endl;
		header << "Account ID: " << String::valueOf(account->getAccountID()) << endl;
		header << "Station ID: " << String::valueOf(account->getStationID()) << endl;
		header << "Admin Level: " << String::valueOf(account->getAdminLevel()) << endl;
		header << "Created: " << createdTime.getFormattedTime() << endl;
		if(account->isBanned()) {
			header << "\\#FF0000(BANNED)\\#FFFFFF " << endl;
			header << getBanDuration(account);
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
			username += "\\#FF0000(BANNED)\\#FFFFFF ";
		box->addMenuItem(username, 0);

		VectorMap<String, Vector<String> > characters;

		while(characterList->next()) {

			UnicodeString name;
			characterList->getCharacterName(name);

			targetCreature = playerManager->getPlayer(characterList->getCharacterFirstName());
			if(targetCreature == NULL || !targetCreature->isPlayerCreature())
				continue;

			ghost = targetCreature->getPlayerObject();

			if(!characters.contains(characterList->getGalaxyName()))
				characters.put(characterList->getGalaxyName(), Vector<String>());

			Vector<String>* galaxy = &characters.get(characterList->getGalaxyName());

			StringBuffer line;
			line << "\t\t" << name.toString();

			if(ghost->isLinkDead())
				line << " \\#EE7600(LD)\\#FFFFFF ";
			else if(ghost->isOnline())
				line << " \\#00FF00(ONLINE)\\#FFFFFF ";
			else
				line << " \\#AAAAAA(OFFLINE)\\#FFFFFF ";

			if(ghost->isBanned()) {
				line << " \\#FF0000(BANNED)\\#FFFFFF ";
			}

			galaxy->add(line.toString());
		}

		for(int i = 0; i < characters.size(); ++i) {
			Vector<String>* galaxy = &characters.get(i);

			box->addMenuItem("\t" + characters.elementAt(i).getKey(), 0);

			for(int j = 0; j < galaxy->size(); ++j) {
				box->addMenuItem(galaxy->get(j), 0);
			}
		}

		creature->sendMessage(box->generateMessage());*/


		return 0;
	}
};


#endif /* PLAYERINFOCOMMAND_H_ */
