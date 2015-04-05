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

#ifndef STARTDANCECOMMAND_H_
#define STARTDANCECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/skill/PerformanceManager.h"

class StartDanceCommand: public QueueCommand {

public:
	StartDanceCommand(const String& name, ZoneProcessServer* server) :
		QueueCommand(name, server) {

	}

	static void startDance(CreatureObject* creature, const String& dance,
			const String& animation) {
		ManagedReference<Facade*> facade = creature->getActiveSession(
				SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session =
				dynamic_cast<EntertainingSession*> (facade.get());

		if (session == NULL) {
			session = new EntertainingSession(creature);
			creature->addActiveSession(SessionFacadeType::ENTERTAINING, session);
		}

		session->startDancing(dance, animation);
	}

	static void sendAvailableDances(CreatureObject* player, PlayerObject* ghost, uint32 suiType = SuiWindowType::DANCING_START) {
		ManagedReference<SuiListBox*> sui = new SuiListBox(player, suiType);
		sui->setPromptTitle("@performance:available_dances");
		sui->setPromptText("@performance:select_dance");

		AbilityList* list = ghost->getAbilityList();

		for (int i = 0; i < list->size(); ++i) {
			Ability* ability = list->get(i);

			String abilityName = ability->getAbilityName();

			if (abilityName.indexOf("startDance") != -1) {
				int args = abilityName.indexOf("+");

				if (args != -1) {
					String arg = abilityName.subString(args + 1);

					sui->addMenuItem(arg);
				}
			}
		}

		if (ghost != NULL) {
			ghost->addSuiBox(sui);
			player->sendMessage(sui->generateMessage());
		}

		return;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target,
			const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* player = cast<CreatureObject*> (creature);

		ManagedReference<Facade*> facade = creature->getActiveSession(
				SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session =
				dynamic_cast<EntertainingSession*> (facade.get());

		if (session != NULL) {
			if (session->isPlayingMusic()) {
				session->stopPlayingMusic();
			}

			if (session->isDancing()) {
				creature->sendSystemMessage(
						"@performance:already_performing_self");

				return GENERALERROR;
			}
		}

		Reference<PlayerObject*> ghost =
				creature->getSlottedObject(
						"ghost").castTo<PlayerObject*> ();

		String args = arguments.toString();

		PerformanceManager* performanceManager =
				SkillManager::instance()->getPerformanceManager();

		if (args.length() < 2) {
			sendAvailableDances(player, ghost);
			return SUCCESS;
		}

		String fullString = String("startDance") + "+" + args;

		if (!ghost->hasAbility(fullString)) {
			creature->sendSystemMessage("@performance:dance_lack_skill_self");
			return GENERALERROR;
		}

		if (!performanceManager->hasDanceAnimation(args)) {
			creature->sendSystemMessage("@performance:dance_lack_skill_self");
			return GENERALERROR;
		}

		startDance(creature, args, performanceManager->getDanceAnimation(args));

		return SUCCESS;
	}

};

#endif //STARTDANCECOMMAND_H_
