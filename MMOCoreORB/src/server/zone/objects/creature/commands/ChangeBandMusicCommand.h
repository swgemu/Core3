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

	bool canPlaySong(CreatureObject* entertainer, const String& song) const {
		ManagedReference<EntertainingSession*> session = entertainer->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

		if (session == NULL || !session->isPlayingMusic())
			return false;

		ManagedReference<Instrument*> instrument = session->getInstrument(entertainer);

		if (instrument == NULL)
			return false;

		ManagedReference<PlayerObject*> ghost = entertainer->getPlayerObject();

		if (ghost == NULL)
			return false;

		PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();

		String instr = performanceManager->getInstrument(instrument->getInstrumentType());

		if (!ghost->hasAbility(instr))
			return false;

		if (!ghost->hasAbility(song))
			return false;

		return true;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		ManagedReference<GroupObject*> group = creature->getGroup();

		if (group == NULL) {
			creature->sendSystemMessage("You must be the leader of a band to use that command.");
			return GENERALERROR;
		}

		Reference<CreatureObject*> leader = group->getLeader();

		if (leader == NULL || creature != leader) {
			creature->sendSystemMessage("You must be the band leader to change the band's song.");
			return GENERALERROR;
		}

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

		if (args.length() < 2) {
			if (!group->isOtherMemberPlayingMusic(creature)) {
				StartMusicCommand::sendAvailableSongs(creature, ghost, SuiWindowType::MUSIC_CHANGE);
				return SUCCESS;
			} else {
				StartMusicCommand::sendAvailableSongs(creature, ghost, SuiWindowType::BAND_CHANGE);
				return SUCCESS;
			}
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

		creature->unlock();

		try {
			Locker locker(group);

			for (int i = 0; i < group->getGroupSize(); ++i) {
				Reference<CreatureObject*> groupMember = group->getGroupMember(i);

				if (groupMember == NULL || !groupMember->isPlayingMusic())
					continue;

				Locker clocker(groupMember, group);

				ManagedReference<EntertainingSession*> bandMemberSession = groupMember->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession*>();

				if (bandMemberSession == NULL || !bandMemberSession->isPlayingMusic())
					continue;

				if (!canPlaySong(groupMember, fullString)) {
					creature->sendSystemMessage("@performance:music_lack_skill_band_member"); // One of the band members lacked the skill to perform that song.
					groupMember->sendSystemMessage("@performance:music_lack_skill_song_band"); // You do not have the skill to perform the song the band is performing.
					bandMemberSession->stopPlayingMusic();
					continue;
				}

				ManagedReference<Instrument*> bandMemberInstrument = bandMemberSession->getInstrument(groupMember);
				String instrumentAnimation;

				int instrid = performanceManager->getInstrumentId(args);
				instrid += performanceManager->getInstrumentAnimation(bandMemberInstrument->getInstrumentType(), instrumentAnimation);

				bandMemberSession->sendEntertainingUpdate(groupMember, /*0x3C4CCCCD*/0.0125, instrumentAnimation, 0x07339FF8, instrid);
				bandMemberSession->setPerformanceName(args);

				groupMember->notifyObservers(ObserverEventType::CHANGEENTERTAIN, groupMember);
			}

			group->setBandSong(args);

		} catch (Exception& e) {
			creature->wlock();

			throw;
		}

		creature->wlock();

		return SUCCESS;
	}

};

#endif //CHANGEBANDMUSICCOMMAND_H_
