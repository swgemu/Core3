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

#ifndef STARTBANDCOMMAND_H_
#define STARTBANDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class StartBandCommand : public QueueCommand {
public:

	StartBandCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<GroupObject*> group = creature->getGroup();

		if (group == NULL) {
			creature->sendSystemMessage("You must be the leader of a band to use that command.");
			return GENERALERROR;
		}

		Reference<CreatureObject*> leader = (group->getLeader()).castTo<CreatureObject*>();

		if (leader == NULL || creature != leader) {
			creature->sendSystemMessage("You must be the band leader to start the band playing.");
			return GENERALERROR;
		}

		ManagedReference<EntertainingSession*> session = creature->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

		if (session != NULL) {
			if (session->isDancing()) {
				session->stopDancing();
			}

			if (session->isPlayingMusic()) {
				creature->sendSystemMessage("@performance:already_performing_self"); // You are already performing.

				return GENERALERROR;
			}
		}

		if (!canPlayInstrument(creature, creature->getTargetID()))
			return GENERALERROR;

		Reference<PlayerObject*> ghost = creature->getSlottedObject("ghost").castTo<PlayerObject*> ();

		String args = arguments.toString();

		String bandSong = group->getBandSong();

		String fullString = String("startMusic") + "+" + args;

		if (args.length() < 2) {
			if (bandSong == "") {
				StartMusicCommand::sendAvailableSongs(creature, ghost, SuiWindowType::BAND_START);

				return SUCCESS;
			} else {
				args = bandSong;

				fullString = String("startMusic") + "+" + args;
				if (!ghost->hasAbility(fullString)) {
					creature->sendSystemMessage("@performance:music_lack_skill_song_band"); // You do not have the skill to perform the song the band is performing.
					return GENERALERROR;
				}
			}
		} else {
			if (bandSong != "" && args != bandSong) {
				creature->sendSystemMessage("@performance:music_join_band_stop"); // You must play the same song as the band.
				return GENERALERROR;
			}
		}

		PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();

		if (!performanceManager->hasInstrumentId(args)) {
			creature->sendSystemMessage("@performance:music_invalid_song"); // That is not a valid song name.
			return GENERALERROR;
		}

		if (!ghost->hasAbility(fullString)) {
			creature->sendSystemMessage("@performance:music_lack_skill_song_self"); // You do not have the skill to perform that song.
			return GENERALERROR;
		}

		creature->unlock();

		try {
			Locker locker(group);

			for (int i = 0; i < group->getGroupSize(); ++i) {
				Reference<CreatureObject*> groupMember = (group->getGroupMember(i)).castTo<CreatureObject*>();

				Locker clocker(groupMember, group);

				if (groupMember == NULL)
					continue;

				ManagedReference<EntertainingSession*> groupMemberSession = groupMember->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

				if (groupMemberSession != NULL)
					continue;

				if (!canPlayInstrument(groupMember, groupMember->getTargetID())) {
					continue;
				}

				ManagedReference<PlayerObject*> memberGhost = groupMember->getPlayerObject();

				if (!memberGhost->hasAbility(fullString)) {
					groupMember->sendSystemMessage("@performance:music_lack_skill_song_band"); // You do not have the skill to perform the song the band is performing.
					creature->sendSystemMessage("@performance:music_lack_skill_band_member"); // One of the band members lacked the skill to perform that song.
					continue;
				}

				Reference<Instrument*> instrument = groupMember->getSlottedObject("hold_r").castTo<Instrument*> ();
				bool targetedInstrument = false;

				if (instrument == NULL) {
					ManagedReference<SceneObject*> nala = server->getZoneServer()->getObject(groupMember->getTargetID());
					instrument = cast<Instrument*> (nala.get());
					targetedInstrument = true;
				}

				if (instrument == NULL)
					continue;

				Locker lockerInstr(instrument);

				if (instrument->isBeingUsed()) {
					groupMember->sendSystemMessage("Someone else is using this instrument");
					continue;
				} else {
					instrument->setBeingUsed(true);
				}

				if (targetedInstrument && (instrument->getParent() != NULL  || instrument->getSpawnerPlayer() != NULL)) {
					instrument->setDirection(*groupMember->getDirection());
					instrument->teleport(groupMember->getPositionX(), groupMember->getPositionZ(), groupMember->getPositionY(), groupMember->getParentID());
				}

				String instrumentAnimation;
				int instrid = performanceManager->getInstrumentId(args);
				instrid += performanceManager->getInstrumentAnimation(instrument->getInstrumentType(), instrumentAnimation);

				StartMusicCommand::startMusic(groupMember, args, instrumentAnimation, instrid, targetedInstrument);

				if (bandSong == "") {
					if (groupMember == leader)
						groupMember->sendSystemMessage("@performance:music_start_band_self"); // You prepare to start the band playing.
					else {
						StringIdChatParameter stringID;

						stringID.setTU(leader->getCustomObjectName());
						stringID.setStringId("performance", "music_start_band_members"); // %TU prepares to start your band playing.
						groupMember->sendSystemMessage(stringID);
					}
				} else {
					if (groupMember == leader)
						groupMember->sendSystemMessage("@performance:music_band_join_song_self"); // You prepare the band to join in with the currently performed song.
					else {
						StringIdChatParameter stringID;

						stringID.setTU(leader->getCustomObjectName());
						stringID.setStringId("performance", "music_band_join_song_members"); // %TU prepares your band to join in with the currently playing song.
						groupMember->sendSystemMessage(stringID);
					}
				}
			}

			if (bandSong == "")
				group->setBandSong(args);

		} catch (Exception& e) {
			creature->wlock();

			throw;
		}

		creature->wlock();

		return SUCCESS;
	}

	bool canPlayInstrument(CreatureObject* creature, const uint64& target) {
		Reference<PlayerObject*> ghost = creature->getSlottedObject("ghost").castTo<PlayerObject*> ();

		Reference<Instrument*> instrument = creature->getSlottedObject("hold_r").castTo<Instrument*> ();

		if (instrument == NULL) {
			ManagedReference<SceneObject*> nala = server->getZoneServer()->getObject(target);

			if (nala != NULL && dynamic_cast<Instrument*> (nala.get())) {
				instrument = cast<Instrument*> (nala.get());
				ManagedReference<SceneObject*> creatureParent = creature->getParent();

				if (creature->getDistanceTo(nala) >= 3 || nala->getZone()
						== NULL || (creatureParent == NULL && NULL
						!= nala->getParent().get())) {
					creature->sendSystemMessage("@elevator_text:too_far"); // You are too far away to use that.

					return false;
				}

				if (instrument->getSpawnerPlayer() != NULL
						&& instrument->getSpawnerPlayer() != creature) {
					creature->sendSystemMessage("You must be the owner of the instrument");

					return false;
				}

				if (instrument->isBeingUsed()) {
					creature->sendSystemMessage("Someone else is using this instrument");

					return false;
				}
			} else {
				creature->sendSystemMessage("@performance:music_no_instrument"); // You must have an instrument equipped to play music.

				return false;
			}
		}

		PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();
		String instr = performanceManager->getInstrument(instrument->getInstrumentType());

		if (!ghost->hasAbility(instr)) {
			creature->sendSystemMessage("@performance:music_lack_skill_instrument"); // You do not have the skill to use the currently equipped instrument.

			return false;
		}

		return true;
	}

};

#endif //STARTBANDCOMMAND_H_
