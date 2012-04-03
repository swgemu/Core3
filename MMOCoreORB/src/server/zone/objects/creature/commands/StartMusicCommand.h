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

#ifndef STARTMUSICCOMMAND_H_
#define STARTMUSICCOMMAND_H_
#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/skill/PerformanceManager.h"
#include "server/zone/managers/skill/Performance.h"
#include "server/zone/objects/group/GroupObject.h"
#include "StartDanceCommand.h"

class StartMusicCommand: public QueueCommand {
public:

	StartMusicCommand(const String& name, ZoneProcessServer* server) :
		QueueCommand(name, server) {

	}

	static void startMusic(CreatureObject* creature, const String& song,
			const String& instrumentAnimation, int intid,
			bool targetInstrument = false) {
		ManagedReference<Facade*> facade = creature->getActiveSession(
				SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session =
				dynamic_cast<EntertainingSession*> (facade.get());

		if (session == NULL) {
			session = new EntertainingSession(creature);
			creature->addActiveSession(SessionFacadeType::ENTERTAINING, session);
		}

		session->setTargetInstrument(targetInstrument);
		session->startPlayingMusic(song, instrumentAnimation, intid);
	}

	static void sendAvailableSongs(CreatureObject* player, PlayerObject* ghost,
			int instrumentID, uint32 suiType = SuiWindowType::MUSIC_START) {

		ManagedReference<SuiListBox*> sui = new SuiListBox(player, suiType);
		sui->setPromptTitle("@performance:available_songs");
		sui->setPromptText("@performance:select_song");

		PerformanceManager* performanceManager =
				SkillManager::instance()->getPerformanceManager();
		Vector<Performance*> performanceList =
				performanceManager->getPerformanceListFromMod(
						"healing_music_ability", player->getSkillMod(
								"healing_music_ability"), instrumentID);

		for (int i = 0; i < performanceList.size(); i++) {
			String performanceName = performanceList.get(i)->getName();
			sui->addMenuItem(performanceName);
		}

		if (ghost != NULL) {
			ghost->addSuiBox(sui);
			player->sendMessage(sui->generateMessage());
		}
		return;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target,
			const UnicodeString& arguments) {

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
			if (session->isDancing()) {
				session->stopDancing();
			}

			if (session->isPlayingMusic()) {
				creature->sendSystemMessage(
						"@performance:already_performing_self");

				return GENERALERROR;
			}
		}

		PlayerObject
				* ghost =
						dynamic_cast<PlayerObject*> (creature->getSlottedObject(
								"ghost"));

		ManagedReference<Instrument*>
				instrument =
						dynamic_cast<Instrument*> (creature->getSlottedObject(
								"hold_r"));
		bool targetedInstrument = false;

		if (instrument == NULL) {
			ManagedReference<SceneObject*> nala =
					server->getZoneServer()->getObject(target);

			if (nala != NULL && dynamic_cast<Instrument*> (nala.get())) {
				targetedInstrument = true;
				instrument = cast<Instrument*> (nala.get());
				SceneObject* creatureParent = creature->getParent();

				if (creature->getDistanceTo(nala) >= 3 || nala->getZone()
						== NULL || (creatureParent == NULL && NULL
						!= nala->getParent())) {
					creature->sendSystemMessage("@elevator_text:too_far");

					return GENERALERROR;
				}

				if (instrument->getSpawnerPlayer() != NULL
						&& instrument->getSpawnerPlayer() != creature) {
					creature->sendSystemMessage(
							"You must be the owner of the instrument");

					return GENERALERROR;
				}

				if (instrument->isBeingUsed()) {
					creature->sendSystemMessage(
							"Someone else is using this instrument");

					return GENERALERROR;
				}

				instrument->setDirection(*creature->getDirection());
				instrument->teleport(creature->getPositionX(),
						creature->getPositionZ(), creature->getPositionY(),
						creature->getParentID());
			} else {
				creature->sendSystemMessage("@performance:music_no_instrument");

				return GENERALERROR;
			}
		}

		PerformanceManager* performanceManager =
				SkillManager::instance()->getPerformanceManager();
		String instr = performanceManager->getInstrument(
				instrument->getInstrumentType());

		if (!ghost->hasAbility(instr)) {
			creature->sendSystemMessage(
					"@performance:music_lack_skill_instrument");

			return GENERALERROR;
		}
		String args = arguments.toString();

		if (args.length() < 2) {
			sendAvailableSongs(player, ghost, instrument->getInstrumentType());

			return SUCCESS;
		}

		String fullString = String("startMusic") + "+" + args;

		if (!ghost->hasAbility(fullString)) {
			creature->sendSystemMessage(
					"@performance:music_lack_skill_song_self");
			return GENERALERROR;
		}

		if (!performanceManager->hasInstrumentId(args)) {
			creature->sendSystemMessage(
					"@performance:music_lack_skill_song_self");
			return GENERALERROR;
		}

		Locker lockerInstr(instrument);

		if (instrument->isBeingUsed()) {
			creature->sendSystemMessage("Someone else is using this instrument");

			return GENERALERROR;
		} else
			instrument->setBeingUsed(true);

		String instrumentAnimation;
		int instrid = performanceManager->getInstrumentId(args);
		instrid += performanceManager->getInstrumentAnimation(
				instrument->getInstrumentType(), instrumentAnimation);

		startMusic(creature, args, instrumentAnimation, instrid,
				targetedInstrument);

		return SUCCESS;
	}

};

#endif //STARTMUSICCOMMAND_H_
