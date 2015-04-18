/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

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
