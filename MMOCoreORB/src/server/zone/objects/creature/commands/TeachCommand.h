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

#ifndef TEACHCOMMAND_H_
#define TEACHCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/PlayerTeachSuiCallback.h"
#include "server/zone/objects/player/sessions/PlayerTeachSession.h"

class TeachCommand : public QueueCommand {
public:

	TeachCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ZoneServer* zserv = creature->getZoneServer();

		ManagedReference<SceneObject*> targetObject = zserv->getObject(target);

		if (targetObject == NULL || !targetObject->isCreatureObject()) {
			return INVALIDTARGET; // Shouldn't get here, but...
		}

		CreatureObject* targetCreature = cast<CreatureObject*>(targetObject.get());


		Locker clocker(targetCreature, creature);

		// By now, the target player should have skills that the teaching player can teach. Let's add each skillbox to a vector.

		PlayerTeachSession* sessioncheck = cast<PlayerTeachSession* >(targetCreature->getActiveSession(SessionFacadeType::PLAYERTEACH));

		if (sessioncheck != NULL) {
			creature->sendSystemMessage("Your target already has an offer to teach.");
			targetCreature->dropActiveSession(SessionFacadeType::PLAYERTEACH);
			return GENERALERROR;
		}

		ManagedReference<PlayerTeachSession*> session = new PlayerTeachSession(targetCreature);
		targetCreature->addActiveSession(SessionFacadeType::PLAYERTEACH, session);

		SkillList* skillList = creature->getSkillList();

		for (int i = 0; i < skillList->size(); ++i) {
			Skill* skill = skillList->get(i);
			if (SkillManager::instance()->canLearnSkill(skill->getSkillName(), targetCreature, false)){
			session->addTeachableSkill(skill->getSkillName());
			}
		}

		// Now, we check to see if the training player has any skills the target can learn.

		if (session->getTeachableSkillsSize() == 0){
			StringIdChatParameter params("teaching", "no_skills_for_student"); // You have no skills that %TT can currently learn."
			params.setTT(targetCreature->getDisplayedName());
			creature->sendSystemMessage(params);
			targetCreature->dropActiveSession(SessionFacadeType::PLAYERTEACH);
			return GENERALERROR;
		}

		// Now, we display the teachable skills to the player offering teaching.

		ManagedReference<SuiListBox*> sui = new SuiListBox(creature, SuiWindowType::TEACH_SKILL);
		sui->setPromptTitle("@base_player:swg");
		sui->setPromptText("Select which skill you wish to teach..."); // TODO: Get actual strings.

		for (int i = 0; i < session->getTeachableSkillsSize(); i++) {
			String skillbox = session->getTeachableSkill(i);
			sui->addMenuItem("@skl_n:" + skillbox);
			sui->setCallback(new PlayerTeachSuiCallback(creature->getZoneServer(), skillbox));
		}


		sui->setCancelButton(true, "Cancel");
		sui->setUsingObject(targetCreature);

		sui->setForceCloseDistance(32);

		creature->getPlayerObject()->addSuiBox(sui);
		creature->sendMessage(sui->generateMessage());



		// Dump what was listed in the SUI box, since we've moved on!

			for (int i = 0; i < session->getTeachableSkillsSize() ; i++ ){
				String theBoxName = session->getTeachableSkill(i);
				session->dropTeachableSkill(theBoxName);
			}

		return SUCCESS;
	}

};

#endif //TEACHCOMMAND_H_
