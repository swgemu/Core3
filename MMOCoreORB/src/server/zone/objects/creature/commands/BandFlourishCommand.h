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

class BandFlourishCommand : public QueueCommand {
public:

	BandFlourishCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	static bool doBandFlourish(CreatureObject* player, String& number, String& instrumentName) {
		ManagedReference<GroupObject*> group = player->getGroup();

		if (group == nullptr)
			return false;

		int instrumentType = 0;
		if (!instrumentName.isEmpty()) {
			instrumentType = determineInstrumentType(instrumentName);

			if (instrumentType < 0) {
				player->sendSystemMessage("@performance:flourish_instrument_unknown");
				return false;
			}
		}

		//Make group members flourish.
		StringIdChatParameter params;
		params.setTT(player->getFirstName());

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::ENTERTAINING);

		if (facade == nullptr)
			return false;

		ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*>(facade.get());

		if (session == nullptr)
			return false;

		bool isLeadDancing = session->isDancing();
		bool isLeadPlaying = session->isPlayingMusic();

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
					ManagedReference<Facade*> memberFacade = groupMember->getActiveSession(SessionFacadeType::ENTERTAINING);
					ManagedReference<EntertainingSession*> memberSession = dynamic_cast<EntertainingSession*>(memberFacade.get());

					if (memberSession == nullptr)
						continue;

					if (!memberSession->isAcceptingBandFlourishes())
						continue;

					if (!memberSession->isDancing() && !memberSession->isPlayingMusic())
						continue;

					if (instrumentType > 0) {
						if (!memberSession->isPlayingMusic())
							continue;

						ManagedReference<Instrument*> memberInstrument = groupMember->getPlayableInstrument();
						int memberInstrumentType = memberInstrument == nullptr ? -1 : memberInstrument->getInstrumentType();

						if (memberInstrumentType != instrumentType)
							continue;

						memberSession->doFlourish(Integer::valueOf(number), false);
					} else {
						if (isLeadDancing && !memberSession->isDancing())
							continue;
						else if (isLeadPlaying && !memberSession->isPlayingMusic())
							continue;

						memberSession->doFlourish(Integer::valueOf(number), false);
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

					if (!playbackModule->isActive())
						continue;

					if (instrumentType == playbackModule->getCurrentInstrument() || (isLeadPlaying && instrumentType < 1))
						playbackModule->doFlourish(Integer::valueOf(number));
				}

			}
		} catch (Exception& e) {
			player->wlock();

			throw;
		}

		player->wlock();

		return true;
	}


	static int determineInstrumentType(const String& instrument) {
		if (instrument == "traz") {
			return InstrumentImplementation::TRAZ;
		} else if (instrument == "slitherhorn") {
			return InstrumentImplementation::SLITHERHORN;
		} else if (instrument == "fanfar") {
			return InstrumentImplementation::FANFAR;
		} else if (instrument == "chidinkalu") {
			return InstrumentImplementation::FLUTEDROOPY;
		} else if (instrument == "kloohorn") {
			return InstrumentImplementation::KLOOHORN;
		} else if (instrument == "fizz") {
			return InstrumentImplementation::FIZZ;
		} else if (instrument == "bandfill") {
			return InstrumentImplementation::BANDFILL;
		} else if (instrument == "omnibox") {
			return InstrumentImplementation::OMNIBOX;
		} else if (instrument == "nalargon") {
			return InstrumentImplementation::NALARGON;
		} else if (instrument == "mandoviol") {
			return InstrumentImplementation::MANDOVIOL;
		} else {
			return -1;
		}
	}

	static bool parseOptions(CreatureObject* player, const String& options, String& stringA, String& stringB) {
		if (options.isEmpty()) {
			player->sendSystemMessage("@performance:band_flourish_format");
			return false;
		}

		stringA = "";
		stringB = "";

		StringTokenizer tokenizer(options);
		tokenizer.setDelimeter(" ");
		tokenizer.getStringToken(stringA);
		stringA.toLowerCase();

		if (tokenizer.hasMoreTokens()) {
			tokenizer.getStringToken(stringB);
			stringB.toLowerCase();
		}

		if (tokenizer.hasMoreTokens()) {
			player->sendSystemMessage("@performance:band_flourish_format");
			return false;
		}

		return true;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		String stringA, instrumentName;

		//Parse the options from the input string. This is the text the player entered after "/bandFlourish"
		if (!parseOptions(creature, arguments.toString(), stringA, instrumentName))
			return GENERALERROR;

		int number = Integer::valueOf(stringA);

		if (number > 0) {
			if (!doBandFlourish(creature, stringA, instrumentName))
				return SUCCESS;
			else
				return GENERALERROR;
		}

		ManagedReference<Facade*> facade = creature->getActiveSession(SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*>(facade.get());

		if (stringA == "on") {
			session->setAcceptingBandFlourishes(true);
			creature->sendSystemMessage("@performance:band_flourish_on");
		} else if (stringA == "off") {
			session->setAcceptingBandFlourishes(false);
			creature->sendSystemMessage("@performance:band_flourish_off");
		} else if (stringA == "status") {
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

};

#endif //BANDFLOURISHCOMMAND_H_
