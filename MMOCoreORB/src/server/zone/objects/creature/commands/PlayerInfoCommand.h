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
		PlayerObject* ghost = creature->getPlayerObject();

		if (!ghost->isPrivileged())
			return 1;

		ManagedReference<SuiMessageBox*> box = new SuiMessageBox(creature, 0);

		box->setPromptTitle("Player Info"); //Register City
		//box->setPromptText("@city/city:register_d");

		StringBuffer msg;
		msg << "SkillMods:\n";

		SkillModList* skillModList = creature->getSkillModList();

		for (int i = 0; i < skillModList->size(); ++i) {
			String name = skillModList->getKeyAt(i);
			int skillMod = skillModList->getValueAt(i).getSkillMod();
			int bonus = skillModList->getValueAt(i).getSkillBonus();

			msg << name << ":" << skillMod << " (" << bonus << ")" << endl;
		}

		box->setPromptText(msg.toString());

		creature->sendMessage(box->generateMessage());

		return 0;
	}
};


#endif /* PLAYERINFOCOMMAND_H_ */
