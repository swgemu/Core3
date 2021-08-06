/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHANGEMUSICCOMMAND_H_
#define CHANGEMUSICCOMMAND_H_

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

		if (session == nullptr || !session->isPlayingMusic()) {
			creature->sendSystemMessage("@performance:music_must_be_performing_self"); // You must be playing music before you can change the song.
			return GENERALERROR;
		}

		// TODO: outro check


		bool activeBandSong = false;

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

				activeBandSong = true;
				break;
			}
		}

		if (activeBandSong) {
			creature->sendSystemMessage("@performance:music_must_match_band"); // You cannot change your song now. You must play the same song as the band.
			return GENERALERROR;
		}

		String args = arguments.toString();

		PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();

		if (args.length() < 1) {
			performanceManager->sendAvailablePerformances(creature, PerformanceType::MUSIC, false);
			return SUCCESS;
		}

		ManagedReference<Instrument*> instrument = creature->getPlayableInstrument();

		if (instrument == nullptr) {
			creature->sendSystemMessage("@performance:music_no_instrument"); // You must have an instrument equipped to play music.
			return GENERALERROR;
		}

		int instrumentType = instrument->getInstrumentType();

		if (!performanceManager->canPlayInstrument(creature, instrumentType)) {
			creature->sendSystemMessage("@performance:music_lack_skill_instrument"); // You do not have the skill to use the currently equipped instrument.
			return GENERALERROR;
		}

		int performanceIndex = performanceManager->getPerformanceIndex(PerformanceType::MUSIC, args, instrumentType);

		if (performanceIndex == 0) {
			creature->sendSystemMessage("@performance:music_invalid_song"); // That is not a valid song name.
			return GENERALERROR;
		}

		if (!performanceManager->canPlaySong(creature, args)) {
			creature->sendSystemMessage("@performance:music_lack_skill_song_self"); // You do not have the skill to perform that song.
			return GENERALERROR;
		}

		session->sendEntertainingUpdate(creature, performanceIndex, true);
		creature->notifyObservers(ObserverEventType::CHANGEENTERTAIN, creature);

		return SUCCESS;
	}

};

#endif //CHANGEMUSICCOMMAND_H_
