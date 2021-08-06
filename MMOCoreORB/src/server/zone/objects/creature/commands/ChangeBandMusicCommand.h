/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHANGEBANDMUSICCOMMAND_H_
#define CHANGEBANDMUSICCOMMAND_H_

#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/skill/PerformanceManager.h"
#include "server/zone/objects/tangible/components/droid/DroidPlaybackModuleDataComponent.h"
#include "StartMusicCommand.h"

class ChangeBandMusicCommand : public QueueCommand {
public:

	ChangeBandMusicCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}


	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();

		ManagedReference<EntertainingSession*> session = creature->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

		if (session == nullptr || !session->isPlayingMusic()) {
			performanceManager->performanceMessageToSelf(creature, nullptr, "performance", "music_must_be_performing_self"); // You must be playing music before you can change the song.
			return GENERALERROR;
		}

		ManagedReference<Instrument*> instrument = creature->getPlayableInstrument();

		if (instrument == nullptr) {
			performanceManager->performanceMessageToSelf(creature, nullptr, "@performance", "music_no_instrument"); // You must have an instrument equipped to play music.
			return GENERALERROR;
		}

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		if (session->isPerformingOutro()) {
			performanceManager->performanceMessageToSelf(creature, nullptr, "@performance", "music_outro_wait"); // You must wait a moment before starting another song.
			return GENERALERROR;
		}

		String args = arguments.toString();

		if (args.length() < 1) {
			performanceManager->sendAvailablePerformances(creature, PerformanceType::MUSIC, true);
			return SUCCESS;
		}

		int instrumentType = instrument->getInstrumentType();

		int performanceIndex = performanceManager->getPerformanceIndex(PerformanceType::MUSIC, args, instrumentType);

		if (performanceIndex == 0) {
			performanceManager->performanceMessageToSelf(creature, nullptr, "performance", "music_invalid_song"); // That is not a valid song name.
			return GENERALERROR;
		}

		if (!performanceManager->canPlaySong(creature, performanceIndex)) {
			performanceManager->performanceMessageToSelf(creature, nullptr, "performance", "music_lack_skill_song_self"); // You do not have the skill to perform that song.
			return GENERALERROR;
		}

		session->sendEntertainingUpdate(creature, performanceIndex, true);
		creature->notifyObservers(ObserverEventType::CHANGEENTERTAIN, creature);

		ManagedReference<GroupObject*> group = creature->getGroup();

		bool bandMemberLacksSkill = false;

		if (group != nullptr) {
			for (int i = 0; i < group->getGroupSize(); ++i) {
				Reference<CreatureObject*> groupMember = group->getGroupMember(i);

				if (groupMember == nullptr || groupMember == creature)
					continue;

				Locker clocker(groupMember, creature);

				if (groupMember->isDroidObject()) {
					DroidObject* droid = cast<DroidObject*>(groupMember.get());

					if (droid == nullptr)
						continue;

					auto module = droid->getModule("playback_module");

					if (module == nullptr)
						continue;

					DroidPlaybackModuleDataComponent* playbackModule = cast<DroidPlaybackModuleDataComponent*>(module.get());

					if (playbackModule == nullptr)
						continue;

					int newDroidIndex = playbackModule->getMatchingIndex(droid, performanceIndex);

					if (newDroidIndex == 0) {
						performanceManager->performanceMessageToDroidOwner(droid, nullptr, "performance", "music_track_not_available"); // Your droid does not have a track recorded for the current song in progress.
						playbackModule->deactivate();
						continue;
					}

					ManagedReference<CreatureObject*> owner = droid->getLinkedCreature().get();

					playbackModule->playSong(owner, newDroidIndex);
					continue;
				}

				ManagedReference<EntertainingSession*> bandMemberSession = groupMember->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

				if (bandMemberSession == nullptr || !bandMemberSession->isPlayingMusic())
					continue;

				ManagedReference<Instrument*> memberInstrument = creature->getPlayableInstrument();

				if (memberInstrument == nullptr)
					continue;

				int memberInstrumentType = memberInstrument->getInstrumentType();
				int memberPerformanceIndex = performanceManager->getMatchingPerformanceIndex(performanceIndex, memberInstrumentType);

				if (memberPerformanceIndex == 0)
					continue;

				if (!performanceManager->canPlayInstrument(groupMember, memberInstrumentType)) {
					performanceManager->performanceMessageToSelf(groupMember, nullptr, "performance", "music_lack_skill_instrument"); // You do not have the skill to use the currently equipped instrument.
					bandMemberSession->stopMusic(true);
					bandMemberLacksSkill = true;
					continue;
				}

				if (!performanceManager->canPlaySong(groupMember, memberPerformanceIndex)) {
					performanceManager->performanceMessageToSelf(groupMember, nullptr, "performance", "music_lack_skill_song_band"); // You do not have the skill to perform the song the band is performing.
					bandMemberSession->stopMusic(true);
					bandMemberLacksSkill = true;
					continue;
				}

				if (groupMember->isPlayingMusic()) {
					bandMemberSession->sendEntertainingUpdate(groupMember, memberPerformanceIndex, true);
					groupMember->notifyObservers(ObserverEventType::CHANGEENTERTAIN, groupMember);
				} else {
					StartMusicCommand::startMusic(groupMember, memberPerformanceIndex, memberInstrument);
				}
			}
		}

		if (bandMemberLacksSkill)
			performanceManager->performanceMessageToSelf(creature, nullptr, "performance", "music_lack_skill_band_member"); // One of the band members lacked the skill to perform that song.

		return SUCCESS;
	}

};

#endif //CHANGEBANDMUSICCOMMAND_H_
