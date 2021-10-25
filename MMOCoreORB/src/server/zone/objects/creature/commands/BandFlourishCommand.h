/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef BANDFLOURISHCOMMAND_H_
#define BANDFLOURISHCOMMAND_H_

#include "server/zone/objects/creature/ai/DroidObject.h"
#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/tangible/components/droid/DroidPlaybackModuleDataComponent.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/skill/PerformanceManager.h"

class BandFlourishCommand : public QueueCommand {
public:

	BandFlourishCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	static bool doBandFlourish(CreatureObject* player, int flourishNum, String& instrumentName) {
		ManagedReference<GroupObject*> group = player->getGroup();

		if (group == nullptr)
			return false;

		int instrumentType = 0;
		PerformanceManager* performanceManager = SkillManager::instance()->getPerformanceManager();

		if (!instrumentName.isEmpty()) {
			instrumentType = performanceManager->getInstrumentId(instrumentName);

			if (instrumentType < 0) {
				player->sendSystemMessage("@performance:flourish_instrument_unknown"); // You specified an unknown instrument for a band flourish.
				return false;
			}
		}

		if (flourishNum < 1 || flourishNum > 8) {
			player->sendSystemMessage("@performance:flourish_not_valid"); // That is not a valid flourish.
			return false;
		}

		//Make group members flourish.
		StringIdChatParameter params;
		params.setTT(player->getFirstName());

		ManagedReference<EntertainingSession *> session = player->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession *>();

		if (session == nullptr)
			return false;

		bool isLeadDancing = session->isDancing();
		bool isLeadPlaying = session->isPlayingMusic();

		if (!isLeadDancing && !isLeadPlaying) {
			player->sendSystemMessage("@performance:flourish_not_performing"); // You must be playing music or dancing in order to perform a flourish.
			return false;
		}

		player->unlock();

		try {
			Locker locker(group);

			for (int i = 0; i < group->getGroupSize(); i++) {
				Reference<CreatureObject*> groupMember = group->getGroupMember(i);

				if (groupMember == nullptr)
					continue;

				if (!groupMember->isInRange(player, 50.0f))
					continue;

				Locker clocker(groupMember, group);

				if (groupMember->isPlayerCreature()) {
					ManagedReference<EntertainingSession *> memberSession = groupMember->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession *>();

					if (memberSession == nullptr)
						continue;

					if (!memberSession->isAcceptingBandFlourishes())
						continue;

					if (!memberSession->isDancing() && !memberSession->isPlayingMusic())
						continue;

					if (instrumentType > 0) {
						if (!memberSession->isPlayingMusic())
							continue;

						int memberInstrumentType = 0;

						ManagedReference<Instrument*> memberInstrument = groupMember->getPlayableInstrument();

						if (memberInstrument != nullptr)
							memberInstrumentType = memberInstrument->getInstrumentType();

						if (memberInstrumentType != instrumentType)
							continue;

						memberSession->doFlourish(flourishNum, false);
					} else {
						if (isLeadDancing && !memberSession->isDancing())
							continue;
						else if (isLeadPlaying && !memberSession->isPlayingMusic())
							continue;

						memberSession->doFlourish(flourishNum, false);
					}

					if (groupMember == player) {
						player->sendSystemMessage("@performance:flourish_perform_band_self"); //"Your band performs a flourish."
					} else {
						params.setStringId("performance", "flourish_perform_band_member");
						groupMember->sendSystemMessage(params);
					}
				} else if (groupMember->isDroidObject()) {
					DroidObject* droid = cast<DroidObject*>(groupMember.get());

					if (droid == nullptr)
						continue;

					auto module = droid->getModule("playback_module");

					if (module == nullptr)
						continue;

					DroidPlaybackModuleDataComponent* playbackModule = cast<DroidPlaybackModuleDataComponent*>(module.get());

					if (playbackModule == nullptr)
						continue;

					if (!playbackModule->isPlayingMusic())
						continue;

					Performance* performance = performanceManager->getPerformanceFromIndex(playbackModule->getPerformanceIndex());

					if (performance == nullptr)
						continue;

					if (instrumentType == performance->getInstrumentAudioId() || (isLeadPlaying && instrumentType < 1))
						playbackModule->doFlourish(flourishNum);
				}

			}
		} catch (Exception& e) {
			player->wlock();

			throw;
		}

		player->wlock();

		return true;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		if (arguments.isEmpty()) {
			creature->sendSystemMessage("@performance:band_flourish_format");
			return GENERALERROR;
		}

		String tempString, instrumentName;
		int instrumentNum;

		StringTokenizer tokenizer(arguments.toString());
		tokenizer.setDelimeter(" ");
		tokenizer.getStringToken(tempString);
		tempString.toLowerCase();

		int flourishNum = Integer::valueOf(tempString);

		if (flourishNum > 0) {
			if (tokenizer.hasMoreTokens()) {
				tokenizer.getStringToken(instrumentName);
				instrumentName.toLowerCase();
			}

			if (doBandFlourish(creature, flourishNum, instrumentName))
				return SUCCESS;
			else
				return GENERALERROR;
		}

		ManagedReference<EntertainingSession *> session = creature->getActiveSession(SessionFacadeType::ENTERTAINING).castTo<EntertainingSession *>();

		if (session == nullptr) {
			creature->sendSystemMessage("@performance:flourish_not_performing"); // You must be playing music or dancing in order to perform a flourish.
			return GENERALERROR;
		}

		if (tempString == "on") {
			session->setAcceptingBandFlourishes(true);
			creature->sendSystemMessage("@performance:band_flourish_on");
		} else if (tempString == "off") {
			session->setAcceptingBandFlourishes(false);
			creature->sendSystemMessage("@performance:band_flourish_off");
		} else if (tempString == "status") {
			if (session->isAcceptingBandFlourishes()) {
				creature->sendSystemMessage("@performance:band_flourish_status_on");
			} else {
				creature->sendSystemMessage("@performance:band_flourish_status_off");
			}
		} else {
			creature->sendSystemMessage("@performance:band_flourish_format");
			return GENERALERROR;
		}

		return SUCCESS;
	}

	float getCommandDuration(CreatureObject* object, const UnicodeString& arguments) const {
		return 0;
	}

};

#endif //BANDFLOURISHCOMMAND_H_
