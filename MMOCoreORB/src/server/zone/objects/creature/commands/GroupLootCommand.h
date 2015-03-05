/*
 * GroupLootCommand.h
 *
 *  Created on: Aug 26, 2011
 *      Author: dannuic
 */

#ifndef GROUPLOOTCOMMAND_H_
#define GROUPLOOTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/GroupLootRuleSuiCallback.h"

class GroupLootCommand : public QueueCommand {
public:

	GroupLootCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
		if (ghost == NULL)
			return GENERALERROR;

		//Check if player is in a group.
		ManagedReference<GroupObject*> group = creature->getGroup();
		if (group == NULL) {
			creature->sendSystemMessage("@group:group_only"); //"You can only set or check group looting options if you are in a group."
			return GENERALERROR;
		}

		//Check if player is the group leader. If not, give current loot rule and stop.
		if (group->getLeader() != creature) {
			switch (group->getLootRule()) {
			case GroupObject::FREEFORALL:
				creature->sendSystemMessage("@group:leader_only_free4all");
				break;
			case GroupObject::MASTERLOOTER:
				creature->sendSystemMessage("@group:leader_only_master");
				break;
			case GroupObject::LOTTERY:
				creature->sendSystemMessage("@group:leader_only_lottery");
				break;
			case GroupObject::RANDOM:
				creature->sendSystemMessage("@group:leader_only");
				creature->sendSystemMessage("@group:selected_random");
				break;
			default:
				break;
			}

			return GENERALERROR;
		}

		//Close SUI box if already open.
		ghost->closeSuiWindowType(SuiWindowType::GROUP_LOOT_RULE);

		//Create the Group Loot Selection SUI box.
		ManagedReference<SuiListBox*> sui = new SuiListBox(creature, SuiWindowType::GROUP_LOOT_RULE);
		sui->setPromptTitle("@group:set_loot_type_title"); //"CHOOSE GROUP LOOT TYPE"
		sui->setPromptText("@group:set_loot_type_text"); //"Choose from the following:"
		sui->setCancelButton(true, "@ui:cancel");
		sui->setOkButton(true, "@ui:ok");
		sui->setCallback(new GroupLootRuleSuiCallback(creature->getZoneServer()));

		sui->addMenuItem("Free For All"); //No string in client?
		sui->addMenuItem("Master Looter"); //No string in client?
		//sui->addMenuItem("@ui_lottery:title"); //"Lottery" *WIP, disabled for now*
		//sui->addMenuItem("@ui:random"); //"Random" *WIP, disabled for now*

		//Send group leader the SUI box.
		ghost->addSuiBox(sui);
		creature->sendMessage(sui->generateMessage());

		return SUCCESS;

	}

};

#endif /* GROUPLOOTCOMMAND_H_ */
