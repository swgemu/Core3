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

#ifndef BANDFLOURISHSKILL_H_
#define BANDFLOURISHSKILL_H_

#include "../SelfSkill.h"

class BandFlourishSkill : public SelfSkill {

public:
	BandFlourishSkill(const String& Name, ZoneProcessServerImplementation* serv) : SelfSkill(Name, "", ENTERTAIN, serv) {

	}

	void doSkill(CreatureObject* creature, String& options) {
		if (!creature->isPlayer()) {
			return;
		}

		String stringA, stringB;

		Player* leader = (Player*)creature;

		//Parse the options from the input string. This is the text the player entered after "/bandFlourish"
		if (!parseOptions(leader, options, stringA, stringB))
			return;

		//Check if leader specified an instrument to flourish.
		int instrumentType = 0;
		if (!stringB.isEmpty()) {
			instrumentType = determineInstrumentType(stringB);
			if (instrumentType < 0) {
				leader->sendSystemMessage("performance", "flourish_instrument_unknown");
				return;
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
				return;
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
			return;

		} else {
			leader->sendSystemMessage("performance", "band_flourish_format");
			return;
		}

	}


	bool parseOptions(Player* leader, String& options, String& stringA, String& stringB) {
		if (options.isEmpty()) {
			leader->sendSystemMessage("performance", "band_flourish_format");
			return false;
		}

		try {
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

		} catch (...) {
			System::out << "Unreported exception in BandFlourishSkill::parseOptions()\n";
		}

		return true;
	}


	void changeStatus(Player* leader, bool newstatus) {
		if (leader->isAcceptingBandFlourishes()) {
			if (newstatus == true) {
				leader->sendSystemMessage("performance", "band_flourish_status_on");
			} else {
				leader->setAcceptingBandFlourishes(false);
				leader->sendSystemMessage("performance", "band_flourish_off");
			}
		} else {
			if (newstatus == false) {
				leader->sendSystemMessage("performance", "band_flourish_status_off");
			} else {
				leader->setAcceptingBandFlourishes(true);
				leader->sendSystemMessage("performance", "band_flourish_on");
			}
		}

		return;
	}


	void printStatus(Player* leader) {
		if (leader->isAcceptingBandFlourishes()) {
			leader->sendSystemMessage("performance", "band_flourish_status_on");
		} else {
			leader->sendSystemMessage("performance", "band_flourish_status_off");
		}
		return;
	}


	int determineInstrumentType(String& instrument) {
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


	void doBandFlourish(Player* leader, String& number, bool musicflourish, int instrumentType) {
		GroupObject* group = leader->getGroupObject();

		//Make the leader flourish.
		if (group == NULL) { //leader is not in a group.
			if (instrumentType > 0) { //the leader specified a valid instrument.
				if (!leader->isPlayingMusic() || leader->getInstrumentType() != instrumentType) {
					return;
				}
			}

			if (leader->isAcceptingBandFlourishes()) {
				leader->doFlourish(number);
			}

			return;

		} else { //leader is in a group.
			if (instrumentType > 0) { //the leader specified a valid instrument.
				if (!musicflourish) {
					return;
				}
				leader->sendSystemMessage("performance", "flourish_perform_band_self"); //"Your band performs a flourish."
				if (leader->isPlayingMusic() && leader->getInstrumentType() == instrumentType && leader->isAcceptingBandFlourishes()) {
					leader->doFlourish(number);
				}

			} else { //no instrument specified.
				leader->sendSystemMessage("performance", "flourish_perform_band_self"); //"Your band performs a flourish."
				if (leader->isAcceptingBandFlourishes()) {
					leader->doFlourish(number);
				}
			}
		}

		//Make group members flourish.
		StfParameter* params = new StfParameter();
		params->addTT(leader->getFirstName());

		leader->unlock();

		try {
			group->wlock();

			for(int i = 0; i < group->getGroupSize(); i++) {
				CreatureObject* groupMember = (CreatureObject*)group->getGroupMember(i);

				try {

					groupMember->wlock(group);

					if (groupMember != leader && groupMember->isPlayer()) {
						Player* player = (Player*)groupMember;

						if (player->isAcceptingBandFlourishes()) {

							//Handle dance flourish
							if (!musicflourish && player->isDancing()) {
								player->sendSystemMessage("performance", "flourish_perform_band_member", params);
								player->doFlourish(number);
							}

							//Handle music flourish
							if (musicflourish && player->isPlayingMusic()) {
								if (instrumentType < 1 || (player->getInstrumentType() == instrumentType)) {
									player->sendSystemMessage("performance", "flourish_perform_band_member", params);
									player->doFlourish(number);
								}
							}
						}
					}

					groupMember->unlock();

				} catch (...) {
					groupMember->unlock();
				}
			}

			group->unlock();

		} catch (...) {
			group->unlock();
			System::out << "Exception in RetreatGroupSkill::doBandFlourish()\n";
		}

		leader->wlock();

		delete params;
		return;
	}


	bool calculateCost(CreatureObject* creature) {
		if (creature->isInCombat() || creature->isMounted())
			return false;
		else
			return true;
	}


	float calculateSpeed(CreatureObject* creature) {
		return 1.0;
	}
};

#endif /*BANDFLOURISHSKILL_H_*/
