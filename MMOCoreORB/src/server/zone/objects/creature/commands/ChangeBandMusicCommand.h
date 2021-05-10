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

		ManagedReference<EntertainingSession*> session = creature->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

		if (session == nullptr || !session->isPlayingMusic()) {
			creature->sendSystemMessage("@performance:music_must_be_performing_self"); // You must be playing music before you can change the song.
			return GENERALERROR;
		}

		ManagedReference<Instrument*> instrument = creature->getPlayableInstrument();

		if (instrument == nullptr) {
			creature->sendSystemMessage("@performance:music_no_instrument"); // You must have an instrument equipped to play music.
			return GENERALERROR;
		}

		ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();

		if (ghost == nullptr)
			return GENERALERROR;

		// TODO: Outro check

		String args = arguments.toString();

		PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();

		if (args.length() < 1) {
			performanceManager->sendAvailableSongs(creature);
			return SUCCESS;
		}

		int instrumentType = instrument->getInstrumentType();

		int performanceIndex = performanceManager->getPerformanceIndex(PerformanceType::MUSIC, args, instrumentType);

		if (performanceIndex == 0) {
			creature->sendSystemMessage("@performance:music_invalid_song"); // That is not a valid song name.
			return GENERALERROR;
		}

		if (!performanceManager->canPlaySong(creature, performanceIndex)) {
			creature->sendSystemMessage("@performance:music_lack_skill_song_self"); // You do not have the skill to perform that song.
			return GENERALERROR;
		}

		session->sendEntertainingUpdate(creature, performanceIndex);
		creature->notifyObservers(ObserverEventType::CHANGEENTERTAIN, creature);

		ManagedReference<GroupObject*> group = creature->getGroup();

		bool bandMemberLacksSkill = false;

		if (group != nullptr) {
			for (int i = 0; i < group->getGroupSize(); ++i) {
				Reference<CreatureObject*> groupMember = group->getGroupMember(i);

				if (groupMember == nullptr || groupMember == creature || !groupMember->isPlayingMusic())
					continue;

				Locker clocker(groupMember, creature);

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
					groupMember->sendSystemMessage("@performance:music_lack_skill_instrument"); // You do not have the skill to use the currently equipped instrument.
					bandMemberSession->stopPlayingMusic();
					bandMemberLacksSkill = true;
					continue;
				}

				if (!performanceManager->canPlaySong(groupMember, memberPerformanceIndex)) {
					groupMember->sendSystemMessage("@performance:music_lack_skill_song_band"); // You do not have the skill to perform the song the band is performing.
					bandMemberSession->stopPlayingMusic();
					bandMemberLacksSkill = true;
					continue;
				}

				bandMemberSession->sendEntertainingUpdate(groupMember, memberPerformanceIndex);

				groupMember->notifyObservers(ObserverEventType::CHANGEENTERTAIN, groupMember);
			}
		}

		if (bandMemberLacksSkill)
			performanceManager->performanceMessageToSelf(creature, nullptr, "performance", "music_lack_skill_band_member"); // One of the band members lacked the skill to perform that song.

		return SUCCESS;
	}

};

#endif //CHANGEBANDMUSICCOMMAND_H_
