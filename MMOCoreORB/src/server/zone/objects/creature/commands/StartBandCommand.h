/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STARTBANDCOMMAND_H_
#define STARTBANDCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

#include "StartMusicCommand.h"

class StartBandCommand : public QueueCommand {
public:

	StartBandCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		Reference<Instrument*> instrument = creature->getPlayableInstrument();

		if (instrument == nullptr) {
			creature->sendSystemMessage("@performance:music_no_instrument"); // You must have an instrument equipped to play music.
			return GENERALERROR;
		}

		// TODO: outro check

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

				ManagedReference<Facade*> facade = groupMember->getActiveSession(SessionFacadeType::ENTERTAINING);
				ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*> (facade.get());

				if (session == nullptr)
					continue;

				int memberPerformanceIndex = session->getPerformanceIndex();

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
				performanceManager->sendAvailableSongs(creature);
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

		if (!performanceManager->canPlaySong(creature, songToPlay)) {
			if (activeBandSong)
				creature->sendSystemMessage("@performance:music_lack_skill_song_band"); // You do not have the skill to perform the song the band is performing.
			else
				creature->sendSystemMessage("@performance:music_lack_skill_song_self"); // You do not have the skill to perform that song.

			return GENERALERROR;
		}

		StartMusicCommand::startMusic(creature, performanceIndex, instrument);

		bool bandMemberLacksSkill = false;

		if (group != nullptr) {
			for (int i = 0; i < group->getGroupSize(); i++) {
				ManagedReference<CreatureObject*> groupMember = group->getGroupMember(i);

				if (groupMember == nullptr || !groupMember->isPlayerCreature() || groupMember == creature || !groupMember->isInRange(creature, 50.0f))
					continue;

				Reference<Instrument*> memberInstrument = groupMember->getPlayableInstrument();

				if (memberInstrument == nullptr)
					continue;

				int memberInstrumentType = memberInstrument->getInstrumentType();

				int memberPerformanceIndex = performanceManager->getMatchingPerformanceIndex(performanceIndex, memberInstrumentType);

				if (memberPerformanceIndex == 0)
					continue;

				if (!performanceManager->canPlayInstrument(groupMember, memberInstrumentType)) {
					groupMember->sendSystemMessage("@performance:music_lack_skill_instrument"); // You do not have the skill to use the currently equipped instrument.
					bandMemberLacksSkill = true;
					continue;
				}

				if (!performanceManager->canPlaySong(groupMember, songToPlay)) {
					groupMember->sendSystemMessage("@performance:music_lack_skill_song_band"); // You do not have the skill to perform the song the band is performing.
					bandMemberLacksSkill = true;
					continue;
				}

				StartMusicCommand::startMusic(groupMember, memberPerformanceIndex, instrument);
			}
		}

		if (activeBandSong) {
			performanceManager->performanceMessageToSelf(creature, nullptr, "performance", "music_band_join_song_self"); // You prepare the band to join in with the currently performed song.
			performanceManager->performanceMessageToBand(creature, nullptr, "performance", "music_band_join_song_members"); // %TU prepares your band to join in with the currently playing song.
		} else {
			performanceManager->performanceMessageToSelf(creature, nullptr, "performance", "music_start_band_self"); // You prepare to start the band playing.
			performanceManager->performanceMessageToBand(creature, nullptr, "performance", "music_start_band_members"); // %TU prepares to start your band playing.
		}

		performanceManager->performanceMessageToBandPatrons(creature, nullptr, "performance", "music_start_band_other"); // %TU's band prepares to start playing.

		if (bandMemberLacksSkill)
			performanceManager->performanceMessageToSelf(creature, nullptr, "performance", "music_lack_skill_band_member"); // One of the band members lacked the skill to perform that song.

		return SUCCESS;
	}
};

#endif //STARTBANDCOMMAND_H_
