/*
 				Copyright <SWGEmu>
		See file COPYING for copying conditions. */

#ifndef STARTMUSICCOMMAND_H_
#define STARTMUSICCOMMAND_H_

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/skill/PerformanceManager.h"
#include "server/zone/objects/group/GroupObject.h"

class StartMusicCommand: public QueueCommand {
public:

	StartMusicCommand(const String& name, ZoneProcessServer* server) :
		QueueCommand(name, server) {

	}

	static void startMusic(CreatureObject* creature, int performanceIndex, Instrument* instrument) {
		ManagedReference<Facade*> facade = creature->getActiveSession(SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*> (facade.get());

		if (session == nullptr) {
			session = new EntertainingSession(creature);
			creature->addActiveSession(SessionFacadeType::ENTERTAINING, session);
		}

		session->startPlayingMusic(performanceIndex, instrument);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		ManagedReference<Facade*> facade = creature->getActiveSession(SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*> (facade.get());

		if (session != nullptr && (session->isDancing() || session->isPlayingMusic())) {
			creature->sendSystemMessage("@performance:already_performing_self"); // You are already performing.
			return GENERALERROR;
		}

		Reference<Instrument*> instrument = creature->getPlayableInstrument();

		if (instrument == nullptr) {
			creature->sendSystemMessage("@performance:music_no_instrument"); // You must have an instrument equipped to play music.
			return GENERALERROR;
		}

		int instrumentType = instrument->getInstrumentType();

		PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();

		bool activeBandSong = false;
		int performanceIndex = 0;

		ManagedReference<GroupObject*> group = creature->getGroup();

		if (group != nullptr) {
			for (int i = 0; i < group->getGroupSize(); i++) {
				ManagedReference<CreatureObject*> groupMember = group->getGroupMember(i);

				if (groupMember == nullptr || !groupMember->isPlayerCreature() || groupMember == creature || !groupMember->isPlayingMusic())
					continue;

				ManagedReference<Facade*> memberFacade = groupMember->getActiveSession(SessionFacadeType::ENTERTAINING);
				ManagedReference<EntertainingSession*> memberSession = dynamic_cast<EntertainingSession*> (memberFacade.get());

				if (memberSession == nullptr)
					continue;

				int memberPerformanceIndex = memberSession->getPerformanceIndex();

				if (memberPerformanceIndex == 0)
					continue;

				performanceIndex = performanceManager->getMatchingPerformanceIndex(memberPerformanceIndex, instrumentType);
				activeBandSong = true;
				break;
			}
		}

		String songToPlay = arguments.toString();

		if (!activeBandSong) {
			if (songToPlay.length() < 1) {
				performanceManager->sendAvailablePerformances(creature, PerformanceType::MUSIC, false);
				return SUCCESS;
			}

			performanceIndex = performanceManager->getPerformanceIndex(PerformanceType::MUSIC, songToPlay, instrumentType);
		}

		if (performanceIndex == 0) {
			creature->sendSystemMessage("@performance:music_invalid_song"); // That is not a valid song name.
			return GENERALERROR;
		}

		String instrumentName = performanceManager->getInstrument(instrumentType);

		if (!performanceManager->canPlayInstrument(creature, instrumentType)) {
			creature->sendSystemMessage("@performance:music_lack_skill_instrument"); // You do not have the skill to use the currently equipped instrument.
			return GENERALERROR;
		}

		if (!performanceManager->canPlaySong(creature, performanceIndex)) {
			if (activeBandSong)
				creature->sendSystemMessage("@performance:music_lack_skill_song_band"); // You do not have the skill to perform the song the band is performing.
			else
				creature->sendSystemMessage("@performance:music_lack_skill_song_self"); // You do not have the skill to perform that song.

			return GENERALERROR;
		}

		creature->sendSystemMessage("@performance:music_start_self"); // You begin playing.
		startMusic(creature, performanceIndex, instrument);

		return SUCCESS;
	}

};

#endif //STARTMUSICCOMMAND_H_
