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

#ifndef BANDFLOURISHCOMMAND_H_
#define BANDFLOURISHCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/Instrument.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/managers/professions/ProfessionManager.h"
#include "server/zone/managers/professions/PerformanceManager.h"

class BandFlourishCommand : public QueueCommand {
public:

	BandFlourishCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	static void doBandFlourish(CreatureObject* leader, String& number, bool musicflourish, int instrumentType) {
		ManagedReference<GroupObject*> group = leader->getGroup();

		ManagedReference<Facade*> facade = leader->getActiveSession(SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*>(facade.get());

		ManagedReference<Instrument*> instrument = session->getInstrument(leader);
		int leaderInstrument = instrument == NULL ? -1 : instrument->getInstrumentType();

		//Make the leader flourish.
		if (group == NULL) { //leader is not in a group.
			if (instrumentType > 0) { //the leader specified a valid instrument.
				if (!leader->isPlayingMusic() || leaderInstrument != instrumentType) {
					return;
				}
			}

			if (session->isAcceptingBandFlourishes()) {
				session->doFlourish(Integer::valueOf(number));
			}

			return;

		} else { //leader is in a group.
			if (instrumentType > 0) { //the leader specified a valid instrument.
				if (!musicflourish) {
					return;
				}
				leader->sendSystemMessage("performance", "flourish_perform_band_self"); //"Your band performs a flourish."
				if (leader->isPlayingMusic() && leaderInstrument == instrumentType && session->isAcceptingBandFlourishes()) {
					session->doFlourish(Integer::valueOf(number));
				}

			} else { //no instrument specified.
				leader->sendSystemMessage("performance", "flourish_perform_band_self"); //"Your band performs a flourish."
				if (session->isAcceptingBandFlourishes()) {
					session->doFlourish(Integer::valueOf(number));
				}
			}
		}

		//Make group members flourish.
		StringIdChatParameter params;
		params.setTT(leader->getFirstName());


		leader->unlock();

		try {
			Locker locker(group);

			for (int i = 0; i < group->getGroupSize(); i++) {
				ManagedReference<CreatureObject*> groupMember = (CreatureObject*)group->getGroupMember(i);

				Locker clocker(groupMember, group);

				if (groupMember != leader && groupMember->isPlayerCreature()) {
					CreatureObject* player = (CreatureObject*)groupMember.get();

					ManagedReference<Facade*> pfacade = player->getActiveSession(SessionFacadeType::ENTERTAINING);

					ManagedReference<EntertainingSession*> psession = dynamic_cast<EntertainingSession*>(pfacade.get());

					if (psession == NULL)
						continue;

					ManagedReference<Instrument*> pinstrument = psession->getInstrument(player);
					int playerInstrumentType = pinstrument == NULL ? -1 : pinstrument->getInstrumentType();

					if (psession->isAcceptingBandFlourishes()) {

						//Handle dance flourish
						if (!musicflourish && psession->isDancing()) {
							params.setStringId("performance", "flourish_perform_band_member");
							player->sendSystemMessage(params);
							psession->doFlourish(Integer::valueOf(number));
						}

						//Handle music flourish
						if (musicflourish && psession->isPlayingMusic()) {
							if (instrumentType < 1 || (playerInstrumentType == instrumentType)) {
								params.setStringId("performance", "flourish_perform_band_member");
								player->sendSystemMessage(params);
								psession->doFlourish(Integer::valueOf(number));
							}
						}
					}
				}

			}
		} catch (Exception& e) {
			leader->wlock();

			throw;
		}

		leader->wlock();

		return;
	}


	static int determineInstrumentType(const String& instrument) {
		if (instrument == "traz") {
			return InstrumentImplementation::TRAZ;
		} else if (instrument == "slitherhorn") {
			return InstrumentImplementation::SLITHERHORN;
		} else if (instrument == "fanfar") {
			return InstrumentImplementation::FANFAR;
		} else if (instrument == "flutedroopy") {
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

	static bool parseOptions(CreatureObject* leader, const String& options, String& stringA, String& stringB) {
		if (options.isEmpty()) {
			leader->sendSystemMessage("performance", "band_flourish_format");
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
			leader->sendSystemMessage("performance", "band_flourish_format");
			return false;
		}

		return true;
	}

	static void changeStatus(CreatureObject* leader, bool newstatus) {
		ManagedReference<Facade*> facade = leader->getActiveSession(SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*>(facade.get());

		if (session->isAcceptingBandFlourishes()) {
			if (newstatus == true) {
				leader->sendSystemMessage("performance", "band_flourish_status_on");
			} else {
				session->setAcceptingBandFlourishes(false);
				leader->sendSystemMessage("performance", "band_flourish_off");
			}
		} else {
			if (newstatus == false) {
				leader->sendSystemMessage("performance", "band_flourish_status_off");
			} else {
				session->setAcceptingBandFlourishes(true);
				leader->sendSystemMessage("performance", "band_flourish_on");
			}
		}

		return;
	}

	void printStatus(CreatureObject* leader) {
		ManagedReference<Facade*> facade = leader->getActiveSession(SessionFacadeType::ENTERTAINING);
		ManagedReference<EntertainingSession*> session = dynamic_cast<EntertainingSession*>(facade.get());

		if (session->isAcceptingBandFlourishes()) {
			leader->sendSystemMessage("performance", "band_flourish_status_on");
		} else {
			leader->sendSystemMessage("performance", "band_flourish_status_off");
		}
		return;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidPostures(creature))
			return INVALIDPOSTURE;

		if (!creature->isPlayerCreature()) {
			return GENERALERROR;
		}

		String stringA, stringB;

		CreatureObject* leader = (CreatureObject*)creature;

		if (!creature->isEntertaining()) {
			leader->sendSystemMessage("performance", "flourish_not_performing");
			return GENERALERROR;
		}

		//Parse the options from the input string. This is the text the player entered after "/bandFlourish"
		if (!parseOptions(leader, arguments.toString(), stringA, stringB))
			return GENERALERROR;

		//Check if leader specified an instrument to flourish.
		int instrumentType = 0;
		if (!stringB.isEmpty()) {
			instrumentType = determineInstrumentType(stringB);

			if (instrumentType < 0) {
				leader->sendSystemMessage("performance", "flourish_instrument_unknown");
				return GENERALERROR;
			}
		}

		//Check if the player is doing a flourish.
		int number = Integer::valueOf(stringA);

		if (number > 0 && number < 9) {
			if (leader->isDancing()) {
				doBandFlourish(leader, stringA, false, instrumentType);

			} else if (leader->isPlayingMusic()) {
				doBandFlourish(leader, stringA, true, instrumentType);

			} else {
				leader->sendSystemMessage("performance", "flourish_not_performing");
				return GENERALERROR;
			}

			//Check if the player is changing an option.
		} else if (stringA == "on") {
			changeStatus(leader, true);

		} else if (stringA == "off") {
			changeStatus(leader, false);

		} else if (stringA == "status") {
			printStatus(leader);

		} else if (number > 8) {
			leader->sendSystemMessage("performance", "flourish_not_valid");
			return GENERALERROR;

		} else {
			leader->sendSystemMessage("performance", "band_flourish_format");
			return GENERALERROR;
		}

		return SUCCESS;
	}

};

#endif //BANDFLOURISHCOMMAND_H_
