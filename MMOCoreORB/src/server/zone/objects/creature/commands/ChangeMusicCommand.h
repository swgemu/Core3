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

#ifndef CHANGEMUSICCOMMAND_H_
#define CHANGEMUSICCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "StartMusicCommand.h"


class ChangeMusicCommand : public QueueCommand {
public:

	ChangeMusicCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<EntertainingSession*> session = creature->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

		if (session == NULL) {
			creature->sendSystemMessage("@performance:music_must_be_performing_self"); // You must be playing music before you can change the song.
			return GENERALERROR;
		}

		if (session->isDancing()) {
			session->stopDancing();
		}

		if (!session->isPlayingMusic()) {
			creature->sendSystemMessage("@performance:music_must_be_performing_self"); // You must be playing music before you can change the song.
			return GENERALERROR;
		}

		ManagedReference<Instrument*> instrument = session->getInstrument(creature);

		if (instrument == NULL) {
			creature->sendSystemMessage("@performance:music_no_instrument"); // You must have an instrument equipped to play music.
			return GENERALERROR;
		}

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		String args = arguments.toString();

		ManagedReference<GroupObject*> group = creature->getGroup();

		if (group != NULL) {
			bool otherPlaying = group->isOtherMemberPlayingMusic(creature);

			if (otherPlaying) {
				creature->sendSystemMessage("@performance:music_must_match_band"); // You cannot change your song now. You must play the same song as the band.
				return GENERALERROR;
			}
		}

		if (args.length() < 2) {
			StartMusicCommand::sendAvailableSongs(creature, ghost, SuiWindowType::MUSIC_CHANGE);
			return SUCCESS;
		}

		PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();

		String instr = performanceManager->getInstrument(instrument->getInstrumentType());

		if (!ghost->hasAbility(instr)) {
			creature->sendSystemMessage("@performance:music_lack_skill_instrument"); // You do not have the skill to use the currently equipped instrument.

			return GENERALERROR;
		}

		if (!performanceManager->hasInstrumentId(args)) {
			creature->sendSystemMessage("@performance:music_invalid_song"); // That is not a valid song name.
			return GENERALERROR;
		}

		String fullString = String("startMusic") + "+" + args;

		if (!ghost->hasAbility(fullString)) {
			creature->sendSystemMessage("@performance:music_lack_skill_song_self"); // You do not have the skill to perform that song.
			return GENERALERROR;
		}

		String instrumentAnimation;

		int instrid = performanceManager->getInstrumentId(args);
		instrid += performanceManager->getInstrumentAnimation(instrument->getInstrumentType(), instrumentAnimation);

		session->sendEntertainingUpdate(creature, /*0x3C4CCCCD*/0.0125, instrumentAnimation, 0x07339FF8, instrid);
		session->setPerformanceName(args);

		creature->notifyObservers(ObserverEventType::CHANGEENTERTAIN, creature);

		if (group != NULL) {
			Locker locker(group);

			group->setBandSong(args);
		}

		return SUCCESS;
	}

};

#endif //CHANGEMUSICCOMMAND_H_
